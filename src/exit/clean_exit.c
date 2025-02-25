/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:07:25 by cpoulain          #+#    #+#             */
/*   Updated: 2025/02/25 15:14:28 by cpoulain         ###   ########.fr       */
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
}

void	clean_exit(
	t_game_ctx *game,
	int code
)
{
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
