/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaliszc <mkaliszc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:29:56 by mkaliszc          #+#    #+#             */
/*   Updated: 2025/02/21 20:55:33 by mkaliszc         ###   ########.fr       */
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
		buffer = ft_strjoin(buffer, line);
		free(line);
		line = get_next_line(fd);
	}
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
	fd_printf(2, "Error: player spawn point not found\n");
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
	else if (map[y][x] != 'N' && map[y][x] != 'S'
			&& map[y][x] != 'W'  && map[y][x] != 'E')
		*valid = 0;
	flood_fill_parse(map, x + 1, y, valid);
	flood_fill_parse(map, x - 1, y, valid);
	flood_fill_parse(map, x, y + 1, valid);
	flood_fill_parse(map, x, y - 1, valid);
}

bool	check_mini_map_format(char **map, int i)
{
	int	valid;
	t_2d_vector	start_pos;

	valid = 1;
	while (map[i][0] == '_')
		i++;
	start_pos = find_start_pos(map + i);
	if (start_pos.x == -1 && start_pos.y == -1)
		return(false);
	flood_fill_parse(map + i, start_pos.x, start_pos.y, &valid);
	if (valid == 0)
		return(fd_printf(2, "Error: Wrong map param\n"), false);
	return(true);
}
void	set_bool_texture(char *line, t_bool_format *checker)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		if (line[3] != '\0')
				checker->n_texture = true;
	if (ft_strncmp(line, "SO ", 3) == 0)
		if (line[3] != '\0')
				checker->s_texture = true;
	if (ft_strncmp(line, "WE ", 3) == 0)
		if (line[3] != '\0')
				checker->w_texture = true;
	if (ft_strncmp(line, "EA ", 3) == 0)
		if (line[3] != '\0')
				checker->e_texture = true;
	if (ft_strncmp(line, "F ", 2) == 0)
		if (line[2] != '\0')
				checker->f_colors = true;
	if (ft_strncmp(line, "C ", 2) == 0)
		if (line[2] != '\0')
				checker->c_colors = true;
	if(checker->c_colors == true && checker->n_texture == true
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
	if (checker.all_texture_found == false && check_missing_texture(checker) == false)
		return (false);
	return(check_mini_map_format(map, i));
}

void	set_texture(bool *texture_set, t_tex_ctx *textures, char *line)
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

t_tex_ctx	init_tex_ctx(char **map)
{
	int			i;
	bool		texture_set;
	t_tex_ctx	textures;

	i = 0;
	texture_set = false;
	while (map[i] && texture_set == false)
	{
		if (map[i][0] != '_')
			set_texture(&texture_set, &textures, map[i]);
		i++;
	}
	// TODO init map_element
}

void	init_game_ctx(char **map, t_game_ctx *ptr)
{
	ptr->texctx = init_tex_ctx(map);
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
	if (check_map_format(map) == false) // ! invalid map format error
		return (ft_free_split(&map), NULL);
	return_pointer = malloc(sizeof(t_game_ctx));
	// init_game_ctx(map, return_pointer);
	return (return_pointer);
}

int	main(int argc, char **argv)
{
	if (main_parsing(argc, argv))
	{
		printf("gg boy\n");
		return (0);
	}
	return(1);
}