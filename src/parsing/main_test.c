/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaliszc <mkaliszc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:29:56 by mkaliszc          #+#    #+#             */
/*   Updated: 2025/02/24 20:08:33 by mkaliszc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"
# include "parsing.h"

int	is_good_format(char *filename)
{
	if (ft_strncmp(&filename[ft_strlen(filename) - 4], ".cub", 4) != 0)
		return (1);
	return (0);
}

char	*fill_buffer(char *filename)
{
	char	*buffer;
	char	*line;
	char	*tmp;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return(ft_putstr_fd("Error: can't open the file", 2), NULL);
	buffer = get_next_line(fd);
	line = get_next_line(fd);
	while (line)
	{
		if (ft_strcmp(line, "\n") == 0)
		{
			free(line);
			line = ft_strdup("_\n");
		}
		tmp = buffer;
		buffer = ft_strjoin(tmp, line);
		free(tmp);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (buffer);
}

void	init_checker(t_bool_format *checker)
{
	checker->d_texture = false;
	checker->e_texture = false;
	checker->f_colors = false;
	checker->c_colors = false;
	checker->w_texture = false;
	checker->s_texture = false;
	checker->n_texture = false;
	checker->all_texture_found = false;
	checker->wrong_param_found = false;
}

bool	check_missing_texture(t_bool_format checker)
{
	if (checker.n_texture == false)
		return(fd_printf(2, "Error: NO texture not found\n"), false);
	else if (checker.s_texture == false)
		return(fd_printf(2, "Error: SO texture not found\n"), false);
	else if (checker.w_texture == false)
		return(fd_printf(2, "Error: WE texture not found\n"), false);
	else if (checker.e_texture == false)
		return(fd_printf(2, "Error: EA texture not found\n"), false);
	else if (checker.f_colors == false)
		return(fd_printf(2, "Error: F colors not found\n"), false);
	else if (checker.c_colors == false)
		return(fd_printf(2, "Error: C colors not found\n"), false);
	return (true);
}

t_2d_vector	find_start_pos(char **map)
{
	t_2d_vector	cur;
	
	cur.y = 0;
	while (map[cur.y])
	{
		cur.x = 0;
		while (map[cur.y][cur.x])
		{
			if (map[cur.y][cur.x] == 'N' || map[cur.y][cur.x] == 'E'
					|| map[cur.y][cur.x] == 'S' || map[cur.y][cur.x] == 'W')
				return (cur);
			cur.x++;
		}
		cur.y++;
	}
	cur.x = -1;
	cur.y = -1;
	return(cur);
}

void	flood_fill_parse(char **map, int x, int y, int *valid)
{
	if (x < 0 || y < 0 || map[y] == NULL || x >= (int)ft_strlen(map[y]))
	{
		*valid = 0;
		return ;
	} 
	if (map[y][x] == '1' || map[y][x] == '2')
		return ;
	else if (map[y][x] == '0')
		map[y][x] = '2';
	else
		*valid = 0;
	flood_fill_parse(map, x + 1, y, valid);
	flood_fill_parse(map, x - 1, y, valid);
	flood_fill_parse(map, x, y + 1, valid);
	flood_fill_parse(map, x, y - 1, valid);
}

bool	check_mini_map_format(char **map, int i)
{
	int			valid;
	char		tmp;
	t_2d_vector	start_pos;
	t_2d_vector	test;

	valid = 1;
	while (map[i][0] == '_')
		i++;
	if (map[i][0] != '1')\
		return(fd_printf(2, "Error: invalid character in configuration file\n"), false);
	start_pos = find_start_pos(map + i);
	if (start_pos.x == -1 && start_pos.y == -1)
		return(fd_printf(2, "Error: player spawn point not found\n"), false);
	tmp = map[i + start_pos.y][start_pos.x];
	map[i + start_pos.y][start_pos.x] = '0';
	flood_fill_parse(map + i, start_pos.x, start_pos.y, &valid);
	if (valid == 0)
		return(fd_printf(2, "Error: map not valid\n"), false);
	test = find_start_pos(map + i);
	if (test.x != -1 && test.y != -1)
		return(fd_printf(2, "Error: Multpile spawn points found\n", false));
	map[i + start_pos.y][start_pos.x] = tmp;
	return(true);
}

void	set_bool_pain(bool *pain, char *line)
{
	if (line[3] != '\0')
		*pain = true;
}

void	set_bool_pain_2(bool *pain, char *line)
{
	if (line[2] != '\0')
		*pain = true;
}

void	set_bool_texture(char *line, t_bool_format *checker)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		set_bool_pain(&(checker->n_texture), line);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		set_bool_pain(&(checker->s_texture), line);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		set_bool_pain(&(checker->w_texture), line);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		set_bool_pain(&(checker->e_texture), line);
	else if (ft_strncmp(line, "F ", 2) == 0)
		set_bool_pain_2(&(checker->f_colors), line);
	else if (ft_strncmp(line, "C ", 2) == 0)
		set_bool_pain_2(&(checker->c_colors), line);
	else if (checker->wrong_param_found != true && checker->all_texture_found == false)
	{
		checker->wrong_param_found = true;
		fd_printf(2, "Error: Wrong map param\n");
	}
	if (checker->c_colors == true && checker->n_texture == true
			&& checker->f_colors == true && checker->s_texture == true
			&& checker->e_texture == true && checker->w_texture == true)
		checker->all_texture_found = true;
}

bool	check_map_format(char **map)
{
	t_bool_format	checker;
	int				i;

	i = 0;
	init_checker(&checker);
	while (map[i] && checker.all_texture_found == false)
	{
		if (map[i][0] == '_' && map[i][1] == '\0')
			i++;
		else
			set_bool_texture(map[i++], &checker);
	}
	if (checker.all_texture_found == false
			|| check_missing_texture(checker) == false
			|| checker.wrong_param_found == true)
		return (false);
	return(check_mini_map_format(map, i));
}

void	set_texture(t_tex_ctx *textures, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		textures->north_path = ft_strdup(line + 3);
	if (ft_strncmp(line, "SO ", 3) == 0)
		textures->south_path = ft_strdup(line + 3);
	if (ft_strncmp(line, "WE ", 3) == 0)
		textures->west_path = ft_strdup(line + 3);
	if (ft_strncmp(line, "EA ", 3) == 0)
		textures->east_path = ft_strdup(line + 3);
	if (ft_strncmp(line, "F ", 2) == 0)
		textures->floor = ft_strdup(line + 2);
	if (ft_strncmp(line, "C ", 2) == 0)
		textures->ceiling = ft_strdup(line + 2);
}

t_tex_ctx	init_tex_ctx(char **map, char **start_of_minimap)
{
	int			i;
	int			nbr_textures_set;
	t_tex_ctx	textures;

	i = 0;
	nbr_textures_set = 0;
	while (map[i] && nbr_textures_set <= 6)
	{
		if (map[i][0] != '_')
		{
			set_texture(&textures, map[i]);
			nbr_textures_set++;
		}
		i++;
	}
	*start_of_minimap = ft_strdup(map[i - 1]);
	textures.is_ceil_rgb = true;
	textures.is_floor_rgb = true;
	return(textures);
}

int	get_nbr_of_pos(char **map)
{
	int	i;
	int	tot;

	i = 0;
	tot = 0;
	while (map[i] && map[i][0] != '_')
		tot += ft_strlen(map[i++]);
	return(tot);
}

t_elem	get_elem_type(char pos)
{
	if (pos == '2' || pos == '0')
		return (ELEM_FLOOR);
	else if (pos == '1')
		return(ELEM_WALL);
	else if (pos == 'N' || pos == 'W' || pos == 'E' || pos == 'S')
		return(ELEM_SPAWN);
	else
		return (ELEM_VOID);
}

t_map_element	set_map_elem_cur(int i, int j, char **map, int map_start)
{
	t_map_element	map_element;

	map_element.pos.x = j;
	map_element.pos.y = i - map_start;
	map_element.type = get_elem_type(map[i][j]);
	map_element.is_end = false;
	return (map_element);
}

t_map_element	*init_map_elem(char **map, char *mini)
{
	t_map_element *map_element;
	int				i;
	int				j;
	int				cur;
	int				map_start;

	i = 0;
	cur = 0;
	while (ft_strcmp(map[i], mini) != 0)
		i++;
	map_element = malloc(sizeof(t_map_element) * get_nbr_of_pos(map + i));
	map_start = i;
	while(map[i])
	{
		j = 0;
		while(map[i][j] && map[i][j] != '_')
		{
			map_element[cur] = set_map_elem_cur(i, j, map, map_start);
			cur++;
			j++;
		}
		i++;
	}
	map_element[cur - 1].is_end = true;
	return (map_element);
}

void	init_game_ctx(char **map, t_game_ctx **ptr)
{
	char	*start_of_minimap;

	start_of_minimap = NULL;
	(*ptr)->texctx = init_tex_ctx(map, &start_of_minimap);
	(*ptr)->map = init_map_elem(map, start_of_minimap);
	free(start_of_minimap);
}

t_game_ctx	*main_parsing(int argc, char **argv)
{
	char		**map;
	char		*buffer;
	t_game_ctx	*return_pointer;

	if (argc != 2 || is_good_format(argv[1]))
	{
		ft_putstr_fd("Error: wrong number of arguments\n", 2);
		ft_putstr_fd("Valid format: <map>.cub\n", 2);
		exit(1);
	}
	buffer = fill_buffer(argv[1]);
	map = ft_split(buffer, '\n');
	free(buffer);
	if (check_map_format(map) == false)
		return (ft_free_split(&map), NULL);
	return_pointer = malloc(sizeof(t_game_ctx));
	init_game_ctx(map, &return_pointer);
	return (ft_free_split(&map), return_pointer);
}

// * debugging/test function

// void	print_map_elem(t_map_element *map)
// {
// 	int i = 0;

// 	while(map[i].is_end != true)
// 	{
// 		printf("at y = %d and x = %d\n type = %d\n-------------------------\n", map[i].pos.y, map[i].pos.x, map[i].type);
// 		i++;
// 	}
// 	printf("at y = %d and x = %d\n type = %d\n-------------------------\n", map[i].pos.y, map[i].pos.x, map[i].type);
// }

// void	print_texture(t_tex_ctx test)
// {
// 	printf("North : %s\n", test.north_path);
// 	printf("South : %s\n", test.south_path);
// 	printf("West : %s\n", test.west_path);
// 	printf("East : %s\n", test.east_path);
// 	printf("floor : %s\n", test.floor);
// 	printf("ceilling : %s\n", test.ceiling);
// }

// int	main(int argc, char **argv)
// {
// 	t_game_ctx	*return_pointer;

// 	return_pointer = main_parsing(argc, argv);
// 	if (return_pointer)
// 	{
// 		print_map_elem(return_pointer->map);
// 		print_texture(return_pointer->texctx);
// 		printf("gg boy\n");
// 		return (0);
// 	}
// 	return(1);
// }
