/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaliszc <mkaliszc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:14:02 by mkaliszc          #+#    #+#             */
/*   Updated: 2025/02/25 15:38:54 by mkaliszc         ###   ########.fr       */
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
			cur.x++;
		}
		cur.y++;
	}
	cur.x = -1;
	cur.y = -1;
	return (cur);
}

int	get_nbr_of_pos(char **map)
{
	int	i;
	int	tot;

	i = 0;
	tot = 0;
	while (map[i] && map[i][0] != '_')
		tot += ft_strlen(map[i++]);
	return (tot);
}

t_elem	get_elem_type(char pos)
{
	if (pos == '2' || pos == '0')
		return (ELEM_FLOOR);
	else if (pos == '1')
		return (ELEM_WALL);
	else if (pos == 'N' || pos == 'W' || pos == 'E' || pos == 'S')
		return (ELEM_SPAWN);
	else
		return (ELEM_VOID);
}
