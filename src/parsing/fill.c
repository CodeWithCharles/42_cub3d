/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:31:03 by mkaliszc          #+#    #+#             */
/*   Updated: 2025/03/06 16:34:45 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	flood_fill_parse_door(char **map, int x, int y, int *valid)
{
	if (x < 0 || y < 0 || map[y] == NULL || x >= (int)ft_strlen(map[y]))
	{
		*valid = 0;
		return ;
	}
	if (map[y][x] == '1' || map[y][x] == '2')
		return ;
	else if (map[y][x] == '0' || map[y][x] == 'D')
		map[y][x] = '2';
	else
		*valid = 0;
	flood_fill_parse_door(map, x + 1, y, valid);
	flood_fill_parse_door(map, x - 1, y, valid);
	flood_fill_parse_door(map, x, y + 1, valid);
	flood_fill_parse_door(map, x, y - 1, valid);
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
