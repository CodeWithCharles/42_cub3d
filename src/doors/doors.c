/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:36:55 by cpoulain          #+#    #+#             */
/*   Updated: 2025/03/17 17:42:29 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Static prototypes

void	_update_door_timer(
			t_door *door,
			double dt);

// Header imlementations

void	update_doors(
	t_game_ctx *ctx,
	double dt // Delta time
)
{
	int				y;
	int				x;
	t_map_element	*elem;
	t_door			*door;

	y = 0;
	x = 0;
	while (y < ctx->m_height)
	{
		while (x < ctx->m_width)
		{
			elem = &ctx->map[y][x];
			if (elem->type == ELEM_DOOR_H || elem->type == ELEM_DOOR_V)
			{
				door = (t_door *)elem->data;
				_update_door_timer(door, dt);
			}
		}
	}
}

// Static implementations

void	_update_door_timer(
	t_door *door,
	double dt
)
{
	if (door->anim_state == DOOR_OPENING)
	{
		door->timer += dt;
		if (door->timer > 1.0)
		{
			door->timer = 1.0;
			door->anim_state = DOOR_OPENED;
		}
	}
	else if (door->anim_state == DOOR_CLOSING)
	{
		door->timer -= dt;
		if (door->timer <= 0)
		{
			door->timer = 0.0;
			door->anim_state = DOOR_CLOSED;
		}
	}
}
