/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:18:09 by cpoulain          #+#    #+#             */
/*   Updated: 2025/03/21 15:42:46 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_minimap	init_minimap(
	t_game_ctx *ctx
)
{
	t_minimap	mmap;

	mmap = (t_minimap){};
	mmap.img = &ctx->minimap_img;
	mmap.view_dist = MMAP_VIEW_DIST;
	mmap.size = (2 * MMAP_VIEW_DIST) + 1;
	mmap.tile_size = MMAP_PIXEL_SIZE / (2 * MMAP_VIEW_DIST);
	mmap.offset.x = get_mmap_offset(&mmap, ctx->m_width,
			(int)ctx->player.pos.x);
	mmap.offset.y = get_mmap_offset(&mmap, ctx->m_height,
			(int)ctx->player.pos.y);
	mmap.img_width_offset = WIN_WIDTH - (mmap.tile_size * 2 + MMAP_PIXEL_SIZE);
	mmap.map = generate_mmap(ctx, &mmap);
	return (mmap);
}
