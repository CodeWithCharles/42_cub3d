/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_player_pos.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:28:33 by cpoulain          #+#    #+#             */
/*   Updated: 2025/03/03 13:43:54 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Static prototypes

static int	_is_valid_pos(
				t_game_ctx *ctx,
				double x,
				double y);

// Header implementations

int	validate_player_pos(
	t_game_ctx *ctx,
	t_2dd_vector new_pos
)
{
	int	has_moved;

	has_moved = 0;
	if (_is_valid_pos(ctx, new_pos.x, ctx->player.pos.y))
	{
		ctx->player.pos.x = new_pos.x;
		has_moved = 1;
	}
	if (_is_valid_pos(ctx, ctx->player.pos.x, new_pos.y))
	{
		ctx->player.pos.y = new_pos.y;
		has_moved = 1;
	}
	return (has_moved);
}

// Static implementations

static int	_is_valid_pos(
	t_game_ctx *ctx,
	double x,
	double y
)
{
	if (x < RAY_BOUND_MIN_OFFSET || x >= ctx->m_width - RAY_BOUND_MAX_OFFSET
		|| y < RAY_BOUND_MIN_OFFSET
		|| y >= ctx->m_height - RAY_BOUND_MIN_OFFSET)
		return (0);
	return (ctx->map[(int)y][(int)x].type != ELEM_WALL);
}
