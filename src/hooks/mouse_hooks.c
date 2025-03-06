/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:46:31 by cpoulain          #+#    #+#             */
/*   Updated: 2025/03/06 16:16:10 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Static prototypes

static void	_mouse_pos_handler(
				t_game_ctx *ctx,
				int x,
				int y);

// Header implementations

int	mouse_move_hook(
	int x,
	int y,
	t_game_ctx *ctx
)
{
	static t_2d_vector	_prev_pos = (t_2d_vector){WIN_WIDTH / 2,
		WIN_HEIGHT / 2};
	t_2dd_vector		delta;

	_mouse_pos_handler(ctx, x, y);
	delta.x = (x - _prev_pos.x) * MOUSE_ROT_SENSITIVITY;
	delta.y = (y - _prev_pos.y) * MOUSE_PITCH_SENSITIVITY;
	if (!(fabs(delta.x) > MOUSE_EDGE_RESET_OFFSET
			|| fabs(delta.y) > MOUSE_EDGE_RESET_OFFSET))
	{
		if (delta.x != 0)
			ctx->player.has_moved += rotate_player(ctx, delta.x);
		if (delta.y)
			ctx->player.pitch -= delta.y;
		if (ctx->player.pitch > WIN_HEIGHT)
			ctx->player.pitch = WIN_HEIGHT;
		if (ctx->player.pitch < -WIN_HEIGHT)
			ctx->player.pitch = -WIN_HEIGHT;
	}
	_prev_pos.y = y;
	_prev_pos.x = x;
	return (0);
}

// Static implementations

static void	_mouse_pos_handler(
	t_game_ctx *ctx,
	int x,
	int y
)
{
	if (x > WIN_WIDTH - MOUSE_EDGE_RESET_OFFSET)
	{
		x = MOUSE_EDGE_RESET_OFFSET;
		mlx_mouse_move(ctx->mlx, ctx->window, x, y);
	}
	if (x < MOUSE_EDGE_RESET_OFFSET)
	{
		x = WIN_WIDTH - MOUSE_EDGE_RESET_OFFSET;
		mlx_mouse_move(ctx->mlx, ctx->window, x, y);
	}
	if (y > WIN_HEIGHT - MOUSE_EDGE_RESET_OFFSET)
	{
		y = MOUSE_EDGE_RESET_OFFSET;
		mlx_mouse_move(ctx->mlx, ctx->window, x, y);
	}
	if (y < MOUSE_EDGE_RESET_OFFSET)
	{
		y = WIN_HEIGHT - MOUSE_EDGE_RESET_OFFSET;
		mlx_mouse_move(ctx->mlx, ctx->window, x, y);
	}
}
