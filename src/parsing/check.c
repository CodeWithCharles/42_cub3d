/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaliszc <mkaliszc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:32:34 by mkaliszc          #+#    #+#             */
/*   Updated: 2025/02/26 17:31:24 by mkaliszc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_good_format(char *filename)
{
	if (ft_strncmp(&filename[ft_strlen(filename) - 4], ".cub", 4) != 0)
		return (1);
	return (0);
}

bool	check_missing_texture(t_bool_format checker)
{
	if (checker.n_texture == false)
		return (fd_printf(2, "Error: NO texture not found\n"), false);
	else if (checker.s_texture == false)
		return (fd_printf(2, "Error: SO texture not found\n"), false);
	else if (checker.w_texture == false)
		return (fd_printf(2, "Error: WE texture not found\n"), false);
	else if (checker.e_texture == false)
		return (fd_printf(2, "Error: EA texture not found\n"), false);
	else if (checker.f_colors == false)
		return (fd_printf(2, "Error: F colors not found\n"), false);
	else if (checker.c_colors == false)
		return (fd_printf(2, "Error: C colors not found\n"), false);
	return (true);
}

bool	check_mini_map_format(char **map, int i, bool door)
{
	int			valid;
	char		**cpy_map;
	t_2d_vector	start_pos;
	t_2d_vector	test;

	valid = 1;
	while (map[i][0] == '_')
		i++;
	if (map[i][0] != '1')
		return (fd_printf(2, "Error: invalid char in config file\n"), false);
	cpy_map = dup_map(map + i);
	start_pos = find_start_pos(cpy_map);
	if (start_pos.x == -1 && start_pos.y == -1)
		return (fd_printf(2, "Error: player spawn point not found\n"), false);
	cpy_map[start_pos.y][start_pos.x] = '0';
	if (door == true)
		flood_fill_parse_door(cpy_map, start_pos.x, start_pos.y, &valid);
	else
		flood_fill_parse(cpy_map, start_pos.x, start_pos.y, &valid);
	if (valid == 0)
		return (fd_printf(2, "Error: map not valid\n"), false);
	test = find_start_pos(cpy_map);
	if (test.x != -1 && test.y != -1)
		return (fd_printf(2, "Error: Multpile spawn points found\n", false));
	return (true);
}

bool	check_map_format(char **map)
{
	t_bool_format	checker;
	int				i;

	i = 0;
	init_checker(&checker);
	while (map[i])
	{
		if (map[i][0] == '_' && map[i][1] == '\0')
			i++;
		else if (map[i][0] == '1')
			break ;
		else
			set_bool_texture(map[i++], &checker);
	}
	if (check_missing_texture(checker) == false
		|| checker.wrong_param_found == true)
		return (false);
	return (check_mini_map_format(map, i, checker.d_texture));
}
