/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:14:02 by mkaliszc          #+#    #+#             */
/*   Updated: 2025/03/18 17:26:16 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_2d_vector	find_start_pos(char **map)
{
	t_2d_vector	cur;

	cur.y = 0;
	while (map[cur.y])
	{
		cur.x = 0;
		while (map[cur.y][cur.x])
		{
			if (ft_strchr(_SPAWNS, map[cur.y][cur.x]))
				return (cur);
			else if (map[cur.y][cur.x] != _WALL && map[cur.y][cur.x] != _FLOOR
					&& !ft_strchr(_DOORS, map[cur.y][cur.x])
					&& map[cur.y][cur.x] != _VOID && map[cur.y][cur.x] != '\0')
				break ;
			cur.x++;
		}
		cur.y++;
	}
	cur.x = -1;
	cur.y = -1;
	return (cur);
}

void	get_map_size(t_game_ctx *game, char **map)
{
	unsigned int	line_size;

	line_size = 0;
	game->m_width = ft_strlen(map[game->m_height]);
	while (map[game->m_height])
	{
		line_size = ft_strlen(map[game->m_height]);
		if (game->m_width < line_size)
			game->m_width = line_size;
		game->m_height++;
	}
}

t_elem	get_elem_type(char pos)
{
	if (pos == _FLOOR)
		return (ELEM_FLOOR);
	else if (pos == _WALL)
		return (ELEM_WALL);
	else if (pos == _SPAWNS[0])
		return (ELEM_SPAWN_DIR_NORTH);
	else if (pos == _SPAWNS[1])
		return (ELEM_SPAWN_DIR_SOUTH);
	else if (pos == _SPAWNS[2])
		return (ELEM_SPAWN_DIR_EAST);
	else if (pos == _SPAWNS[3])
		return (ELEM_SPAWN_DIR_WEST);
	else if (pos == _DOORS[0])
		return (ELEM_DOOR_H);
	else if (pos == _DOORS[1])
		return (ELEM_DOOR_V);
	else
		return (ELEM_VOID);
}
