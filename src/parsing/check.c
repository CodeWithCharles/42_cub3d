/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:32:34 by mkaliszc          #+#    #+#             */
/*   Updated: 2025/03/24 15:57:56 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_good_format(char *filename)
{
	if (ft_strncmp(&filename[ft_strlen(filename) - 4], EXT_CUB, 4) != 0)
		return (1);
	return (0);
}

void	check_if_start_of_map(char *line, t_bool_format *checker)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] != _WALL && line[i] != _FLOOR)
		checker->wrong_param_found = true;
	else if (line[i] == _WALL || line[i] == _FLOOR)
		checker->map_found = true;
}

bool	check_missing_texture(t_bool_format checker)
{
	if (checker.n_texture == false)
		return (print_gen_error(ERR_MIS_NO), false);
	else if (checker.s_texture == false)
		return (print_gen_error(ERR_MIS_SO), false);
	else if (checker.w_texture == false)
		return (print_gen_error(ERR_MIS_WE), false);
	else if (checker.e_texture == false)
		return (print_gen_error(ERR_MIS_EA), false);
	else if (checker.f_colors == false)
		return (print_gen_error(ERR_MIS_F), false);
	else if (checker.c_colors == false)
		return (print_gen_error(ERR_MIS_C), false);
	return (true);
}

bool	check_mini_map_format(
	char **map,
	int i,
	bool door
)
{
	int			valid;
	char		**cpy_map;
	t_2d_vector	start_pos;
	t_2d_vector	test;

	valid = 1;
	cpy_map = dup_map(map + i);
	if (cpy_map == NULL)
		return (print_gen_error(ERR_MAP), 0);
	start_pos = find_start_pos(cpy_map);
	if (start_pos.x == -1 && start_pos.y == -1)
		return (free_tab((void **)cpy_map), print_gen_error(ERR_NO_SPAWN), 0);
	cpy_map[start_pos.y][start_pos.x] = _FLOOR;
	flood_fill_parse(cpy_map, start_pos, door, &valid);
	if (valid == 0)
		return (free_tab((void **)cpy_map), print_gen_error(ERR_MAP), 0);
	test = find_start_pos(cpy_map);
	if (test.x != -1 && test.y != -1)
		return (free_tab((void **)cpy_map), print_gen_error(ERR_MORE_SPAWN), 0);
	return (ft_free_split(&cpy_map), true);
}

bool	check_map_format(
	char **map
)
{
	t_bool_format	checker;
	int				i;

	i = 0;
	init_checker(&checker);
	while (map[i] && checker.wrong_param_found == false
		&& checker.map_found == false)
	{
		if (map[i][0] == '_' && map[i][1] == '\0')
			i++;
		else if (map[i][0] == _WALL || map[i][0] == _FLOOR)
			checker.map_found = true;
		else if (map[i][0] == _VOID)
			check_if_start_of_map(map[i], &checker);
		else
			set_bool_texture(map[i++], &checker);
	}
	if (check_missing_texture(checker) == false
		|| checker.wrong_param_found == true)
		return (print_gen_error(ERR_CONFIG), false);
	return (check_mini_map_format(map, i, checker.d_texture));
}
