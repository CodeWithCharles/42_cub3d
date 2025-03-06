/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:16:22 by cpoulain          #+#    #+#             */
/*   Updated: 2025/03/06 13:56:39 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Header implementations

void	render_minimap(
	t_game_ctx *ctx
)
{
	t_minimap	mmap;
	int			img_size;

	mmap = init_minimap(ctx);
	img_size = MMAP_PIXEL_SIZE + mmap.tile_size;
	init_img(ctx, &ctx->minimap_img, img_size, img_size);
	draw_mmap(&mmap);
	draw_mmap_borders(&mmap);
	mlx_put_image_to_window(ctx->mlx, ctx->window, ctx->minimap_img.img,
		WIN_WIDTH - (mmap.tile_size * 2 + MMAP_PIXEL_SIZE), mmap.tile_size);
	if (ctx->minimap_img.img)
		mlx_destroy_image(ctx->mlx, ctx->minimap_img.img);
	if (mmap.map)
		free_tab((void **)mmap.map);
	mmap.map = NULL;
}
