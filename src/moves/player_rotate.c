/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:50:27 by cpoulain          #+#    #+#             */
/*   Updated: 2025/03/06 15:02:11 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Static prototypes

// Header implementations

int	rotate_player(
	t_game_ctx *ctx,
	double rot_dir
)
{
	double		rot_speed;
	t_player	*p;
	double		tmp_x;

	rot_speed = fmax(fmin(rot_dir * MOUSE_ROT_SENSITIVITY, 0.2), -0.2);
	p = &ctx->player;
	tmp_x = p->dir.x;
	p->dir.x = p->dir.x * cos(rot_speed) - p->dir.y * sin(rot_speed);
	p->dir.y = tmp_x * sin(rot_speed) + p->dir.y * cos(rot_speed);
	tmp_x = p->plane.x;
	p->plane.x = p->plane.x * cos(rot_speed) - p->plane.y * sin(rot_speed);
	p->plane.y = tmp_x * sin(rot_speed) + p->plane.y * cos(rot_speed);
	return (1);
}
