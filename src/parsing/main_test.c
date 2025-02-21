/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaliszc <mkaliszc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:29:56 by mkaliszc          #+#    #+#             */
/*   Updated: 2025/02/21 16:13:06 by mkaliszc         ###   ########.fr       */
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

bool	check_mini_map_format(char **map, int i)
{
	while (map[i][0] == '_')
		i++;
	if (map[i][0] != '_' && map[i][0] != ' ' && map[i][0] != '1' && map[i][0] != '0')
		return(fd_printf(2, "Error: wrong map param : %c\n", map[i][0]), false);
	return(true);
}

bool	check_map_format(char **map)
{
	t_bool_format	checker;
	int				i;

	i = 0;
	init_checker(&checker);
	while (map[i] && checker.all_texture_found == false)
	{
		if (map[i][0] == '_')
			i++;
		if (ft_strncmp(map[i], "NO ", 3) == 0)
		{
			if (map[i][3] != '\0')
				checker.n_texture = true;
			else
				return(ft_putstr_fd("Error: NO texture not set\n", 2), false);
		}
		else if (ft_strncmp(map[i], "SO ", 3) == 0 && checker.n_texture == true)
		{
			if (map[i][3] != '\0')
				checker.s_texture = true;
			else
				return(ft_putstr_fd("Error: SO texture not set\n", 2), false);
		}
		else if (ft_strncmp(map[i], "WE ", 3) == 0 && checker.s_texture == true)
		{
			if (map[i][3] != '\0')
				checker.w_texture = true;
			else
				return(ft_putstr_fd("Error: WE texture not set\n", 2), false);
		}
		else if (ft_strncmp(map[i], "EA ", 3) == 0 && checker.w_texture == true)
		{
			if (map[i][3] != '\0')
				checker.e_texture = true;
			else
				return(ft_putstr_fd("Error: EA texture not set\n", 2), false);
		}
		else if (ft_strncmp(map[i], "F ", 2) == 0 && checker.e_texture == true)
		{
			if (map[i][2] != '\0')
				checker.f_colors = true;
			else
				return(ft_putstr_fd("Error: F colors not set\n", 2), false);
		}
		else if (ft_strncmp(map[i], "C ", 2) == 0 && checker.f_colors == true)
		{
			if (map[i][2] != '\0')
			{
				checker.c_colors = true;
				checker.all_texture_found = true;
			}
			else
				return(ft_putstr_fd("Error: C colors not set\n", 2), false);
		}
		i++;
	}
	if (checker.all_texture_found == false && check_missing_texture(checker) == false)
		return (false);
	return(check_mini_map_format(map, i));
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
	if (check_map_format(map) == false) // ! invalid map format error
		return (ft_free_split(&map), NULL);
	return_pointer = malloc(sizeof(t_game_ctx));
	// init_game_ctx(map);
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