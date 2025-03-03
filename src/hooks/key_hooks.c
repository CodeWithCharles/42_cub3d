/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:04:43 by cpoulain          #+#    #+#             */
/*   Updated: 2025/03/03 15:30:07 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Header implementations

int	key_pressed_hook(
	int key,
	t_game_ctx *ctx
)
{
	if (key == XK_Escape)
		quit_cube(ctx);
	if (key == XK_Left)
		ctx->player.rotate -= PLAYER_ROT_INCREMENT;
	if (key == XK_Right)
		ctx->player.rotate += PLAYER_ROT_INCREMENT;
	if (key == XK_Up)
		ctx->player.pitch -= PLAYER_PITCH_INCREMENT;
	if (key == XK_Down)
		ctx->player.pitch += PLAYER_PITCH_INCREMENT;
	if (key == XK_w)
		ctx->player.move.y = PLAYER_MOVE;
	if (key == XK_d)
		ctx->player.move.x = -PLAYER_MOVE;
	if (key == XK_s)
		ctx->player.move.y = -PLAYER_MOVE;
	if (key == XK_a)
		ctx->player.move.x = PLAYER_MOVE;
	return (0);
}

int	key_released_hook(
	int key,
	t_game_ctx *ctx
)
{
	if (key == XK_Escape)
		quit_cube(ctx);
	if (key == XK_w && ctx->player.move.y == 1)
		ctx->player.move.y = 0;
	if (key == XK_s && ctx->player.move.y == -1)
		ctx->player.move.y = 0;
	if (key == XK_d && ctx->player.move.x == -1)
		ctx->player.move.x += 1;
	if (key == XK_a && ctx->player.move.x == 1)
		ctx->player.move.x -= 1;
	if (key == XK_Left && ctx->player.rotate <= 1)
		ctx->player.rotate = 0;
	if (key == XK_Right && ctx->player.rotate >= -1)
		ctx->player.rotate = 0;
	if (ctx->player.pitch > WIN_HEIGHT)
		ctx->player.pitch = WIN_HEIGHT;
	else if (ctx->player.pitch < -WIN_HEIGHT)
		ctx->player.pitch = -WIN_HEIGHT;
	return (0);
}
