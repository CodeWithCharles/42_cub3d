/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:46:31 by cpoulain          #+#    #+#             */
/*   Updated: 2025/03/03 13:14:39 by cpoulain         ###   ########.fr       */
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
	static int	_prev_x_pos = WIN_WIDTH / 2;

	_mouse_pos_handler(ctx, x, y);
	if (x == _prev_x_pos)
		return (0);
	else if (x < _prev_x_pos)
		ctx->player.has_moved += rotate_player(ctx, -1);
	else if (x > _prev_x_pos)
		ctx->player.has_moved += rotate_player(ctx, 1);
	_prev_x_pos = x;
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
}
