/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:09:04 by cpoulain          #+#    #+#             */
/*   Updated: 2025/02/28 11:29:49 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Header implementations

// TODO: Init mouse movements
void	init_mlx(
	t_game_ctx *ctx
)
{
	ctx->mlx = mlx_init();
	if (!ctx->mlx)
		return (clean_exit(ctx, ERR_INIT_MLX, 1));
	ctx->window = mlx_new_window(ctx->mlx, WIN_WIDTH, WIN_HEIGHT, "Star3D");
	if (!ctx->window)
		return (clean_exit(ctx, ERR_WIN_MLX, 1));
}
