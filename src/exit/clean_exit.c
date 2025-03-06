/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:07:25 by cpoulain          #+#    #+#             */
/*   Updated: 2025/03/06 16:24:24 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	free_game_ctx(
	t_game_ctx *game
)
{
	if (game->game_textures)
		free_tab((void **)game->game_textures);
	if (game->screen_pixels)
		free_tab((void **)game->screen_pixels);
	if (game->texctx.ceiling)
		free(game->texctx.ceiling);
	if (game->texctx.floor)
		free(game->texctx.floor);
	if (game->texctx.north_path)
		free(game->texctx.north_path);
	if (game->texctx.south_path)
		free(game->texctx.south_path);
	if (game->texctx.east_path)
		free(game->texctx.east_path);
	if (game->texctx.west_path)
		free(game->texctx.west_path);
	if (game->texctx.door_path)
		free(game->texctx.door_path);
	if (game->map)
		free_tab((void **)game->map);
}

void	clean_exit(
	t_game_ctx *game,
	char *error,
	int code
)
{
	if (error)
		print_gen_error(error);
	if (!game)
		exit(code);
	if (game->window && game->mlx)
		mlx_destroy_window(game->mlx, game->window);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		mlx_loop_end(game->mlx);
		free(game->mlx);
	}
	free_game_ctx(game);
	exit (code);
}

int	quit_cube(
	t_game_ctx *ctx
)
{
	clean_exit(ctx, NULL, 0);
	return (0);
}
