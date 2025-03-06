/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:45:25 by cpoulain          #+#    #+#             */
/*   Updated: 2025/03/03 13:12:11 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Header implementations

void	init_hooks(
	t_game_ctx *ctx
)
{
	mlx_hook(ctx->window, 33, 0L, quit_cube, ctx);
	mlx_hook(ctx->window, 02, (1L << 0), key_pressed_hook, ctx);
	mlx_hook(ctx->window, 03, (1L << 1), key_released_hook, ctx);
	mlx_hook(ctx->window, 6, (1L << 6), mouse_move_hook, ctx);
}
