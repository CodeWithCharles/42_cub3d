/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ctx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:30:32 by cpoulain          #+#    #+#             */
/*   Updated: 2025/02/25 15:44:22 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Header implementations

void	init_game(
	t_game_ctx *ctx
)
{
	ctx->hex_ceiling = 0x0;
	ctx->hex_floor = 0x0;
	ctx->map = NULL;
	ctx->mlx = NULL;
	ctx->window = NULL;
	ctx->texctx = (t_tex_ctx){};
	ctx->screen_pixels = NULL;
	refresh_screen_pixels(ctx);
}

void	refresh_screen_pixels(
	t_game_ctx *ctx
)
{
	int	i;

	if (ctx->screen_pixels)
		free_tab((void **)ctx->screen_pixels);
	ctx->screen_pixels = ft_calloc(WIN_HEIGHT + 1, sizeof(int *));
	i = 0;
	while (i < WIN_HEIGHT)
		ctx->screen_pixels[i++] = ft_calloc(WIN_WIDTH + 1, sizeof(int));
}
