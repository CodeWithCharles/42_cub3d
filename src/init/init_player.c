/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:30:36 by cpoulain          #+#    #+#             */
/*   Updated: 2025/02/28 15:14:02 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Header implementations

void	init_player_dir(
	t_player *player
)
{
	player->dir.x = (DIR_INIT_POSITIVE
			* (player->spawn_dir == ELEM_SPAWN_DIR_EAST)
			+ DIR_INIT_NEGATIVE
			* (player->spawn_dir == ELEM_SPAWN_DIR_WEST));
	player->dir.y = (DIR_INIT_POSITIVE
			* (player->spawn_dir == ELEM_SPAWN_DIR_SOUTH)
			+ DIR_INIT_NEGATIVE
			* (player->spawn_dir == ELEM_SPAWN_DIR_NORTH));
	player->plane.x = (PLANE_INIT_POSITIVE_ANGLE
			* (player->spawn_dir == ELEM_SPAWN_DIR_NORTH)
			+ PLANE_INIT_NEGATIVE_ANGLE
			* (player->spawn_dir == ELEM_SPAWN_DIR_SOUTH));
	player->plane.y = (PLANE_INIT_POSITIVE_ANGLE
			* (player->spawn_dir == ELEM_SPAWN_DIR_EAST)
			+ PLANE_INIT_NEGATIVE_ANGLE
			* (player->spawn_dir == ELEM_SPAWN_DIR_WEST));
}

void	init_player_data(
	t_game_ctx *ctx,
	char **map
)
{
	t_2d_vector	start_pos;

	start_pos = find_start_pos(map);
	ctx->player = (t_player){};
	ctx->player.pos.x = start_pos.x + 0.5;
	ctx->player.pos.y = start_pos.y + 0.5;
	ctx->player.spawn_dir = ctx->map[start_pos.y][start_pos.x].type;
	init_player_dir(&ctx->player);
}
