/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:31:03 by mkaliszc          #+#    #+#             */
/*   Updated: 2025/03/19 15:07:57 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	_check_door_valid(char **map, int x, int y)
{
	if (map[y][x] == _DOORS[1])
	{
		if (!map[y - 1] || map[y - 1][x] == _VOID
			|| !map[y + 1] || map[y + 1][x] == _VOID)
			return (1);
		if (map[y - 1][x] != _WALL || map[y + 1][x] != _WALL)
			return (1);
		if (map[y][x - 1] != _FILLER && map[y][x + 1] != _FILLER)
			return (1);
	}
	else
	{
		if (!map[y] || x - 1 < 0 || x + 1 >= (int)ft_strlen(map[y])
			|| map[y][x - 1] == _VOID || map[y][x + 1] == _VOID)
			return (1);
		if (map[y][x - 1] != _WALL || map[y][x + 1] != _WALL)
			return (1);
		if (!map[y - 1] || !map[y + 1]
			|| (map[y - 1][x] != _FILLER && map[y + 1][x] != _FILLER))
			return (1);
	}
	return (0);
}

void	flood_fill_parse(
	char **map,
	t_2d_vector p,
	bool has_door,
	int *valid
)
{
	if (p.x < 0 || p.y < 0 || map[p.y] == NULL
		|| p.x >= (int)ft_strlen(map[p.y]))
	{
		*valid = 0;
		return ;
	}
	if (map[p.y][p.x] == _WALL || map[p.y][p.x] == _FILLER)
		return ;
	else if (map[p.y][p.x] == _FLOOR)
		map[p.y][p.x] = _FILLER;
	else if (ft_strchr(_DOORS, map[p.y][p.x]))
	{
		if (has_door && _check_door_valid(map, p.x, p.y))
		{
			*valid = 0;
			return ;
		}
	}
	else
		*valid = 0;
	flood_fill_parse(map, (t_2d_vector){p.x + 1, p.y}, has_door, valid);
	flood_fill_parse(map, (t_2d_vector){p.x - 1, p.y}, has_door, valid);
	flood_fill_parse(map, (t_2d_vector){p.x, p.y + 1}, has_door, valid);
	flood_fill_parse(map, (t_2d_vector){p.x, p.y - 1}, has_door, valid);
}

void	fill_map_line(
	t_map_element *map_line,
	char *line,
	unsigned int m_width,
	unsigned int i
)
{
	unsigned int	j;

	j = 0;
	while (j < m_width && line[j])
	{
		set_map_elem_cur(&map_line[j], i, j, line[j]);
		j++;
	}
}

void	fill_map(t_game_ctx *game, char **map)
{
	unsigned int	i;

	i = 0;
	while (i < game->m_height)
	{
		fill_map_line(game->map[i], map[i], game->m_width, i);
		i++;
	}
}
