/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaliszc <mkaliszc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:14:02 by mkaliszc          #+#    #+#             */
/*   Updated: 2025/03/03 12:47:29 by mkaliszc         ###   ########.fr       */
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
			if (map[cur.y][cur.x] == 'N' || map[cur.y][cur.x] == 'E'
					|| map[cur.y][cur.x] == 'S' || map[cur.y][cur.x] == 'W')
				return (cur);
			else if (map[cur.y][cur.x] != '1' && map[cur.y][cur.x] != '0'
					&& map[cur.y][cur.x] != 'D' && map[cur.y][cur.x] != ' '
					&& map[cur.y][cur.x] != '\0')
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
	if (pos == '0')
		return (ELEM_FLOOR);
	else if (pos == '1')
		return (ELEM_WALL);
	else if (pos == 'N')
		return (ELEM_SPAWN_N);
	else if (pos == 'S')
		return (ELEM_SPAWN_S);
	else if (pos == 'W')
		return (ELEM_SPAWN_W);
	else if (pos == 'E')
		return (ELEM_SPAWN_E);
	else if (pos == 'D')
		return (ELEM_DOOR);
	else
		return (ELEM_VOID);
}
