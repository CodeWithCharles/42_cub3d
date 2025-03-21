/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:04:43 by cpoulain          #+#    #+#             */
/*   Updated: 2025/03/21 14:10:48 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Static prototypes

static void	_handle_door_interaction(
				t_game_ctx *ctx);

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
		ctx->player.pitch += PLAYER_PITCH_INCREMENT;
	if (key == XK_Down)
		ctx->player.pitch -= PLAYER_PITCH_INCREMENT;
	if (key == XK_w)
		ctx->player.move.y = PLAYER_MOVE;
	if (key == XK_d)
		ctx->player.move.x = -PLAYER_MOVE;
	if (key == XK_s)
		ctx->player.move.y = -PLAYER_MOVE;
	if (key == XK_a)
		ctx->player.move.x = PLAYER_MOVE;
	if (key == XK_e)
		_handle_door_interaction(ctx);
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

// Static implementations

static void	_handle_door_interaction(
	t_game_ctx *ctx
)
{
	t_map_element	*elem;
	double			px;
	double			py;
	t_door			*door;

	px = (int)ctx->player.pos.x;
	py = (int)ctx->player.pos.y;
	elem = &ctx->map[(int)round(py + ctx->player.dir.y)]
	[(int)round(px + ctx->player.dir.x)];
	if (elem->type && (elem->type == ELEM_DOOR_H || elem->type == ELEM_DOOR_V))
	{
		door = (t_door *)elem->data;
		if (door->anim_state == DOOR_CLOSED)
			door->anim_state = DOOR_OPENING;
		else if (door->anim_state == DOOR_OPENED)
			door->anim_state = DOOR_CLOSING;
	}
}
