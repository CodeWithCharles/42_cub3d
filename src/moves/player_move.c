/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:18:18 by cpoulain          #+#    #+#             */
/*   Updated: 2025/03/03 15:26:05 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Static prototypes

static int	_move_player(
				t_game_ctx *ctx,
				double move_x,
				double move_y);

// Header implementations

int	move_player_handler(
	t_game_ctx *ctx
)
{
	int			has_moved;
	t_player	*p;

	has_moved = 0;
	p = &ctx->player;
	if (p->move.y)
		has_moved += _move_player(ctx, p->dir.x * p->move.y,
				p->dir.y * p->move.y);
	if (p->move.x)
		has_moved += _move_player(ctx, p->dir.y * p->move.x,
				-p->dir.x * p->move.x);
	if (p->rotate)
		has_moved += rotate_player(ctx, p->rotate);
	return (has_moved);
}

// Static implementations

static int	_move_player(
	t_game_ctx *ctx,
	double move_x,
	double move_y
)
{
	t_2dd_vector	new_pos;

	new_pos.x = ctx->player.pos.x + move_x * PLAYER_MOVE_SPEED;
	new_pos.y = ctx->player.pos.y + move_y * PLAYER_MOVE_SPEED;
	return (validate_player_pos(ctx, new_pos));
}
