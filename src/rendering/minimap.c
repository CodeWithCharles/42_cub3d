/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:16:22 by cpoulain          #+#    #+#             */
/*   Updated: 2025/03/21 17:19:31 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Header implementations

void	render_minimap(
	t_game_ctx *ctx
)
{
	t_minimap	mmap;

	mmap = init_minimap(ctx);
	draw_mmap(&mmap);
	draw_mmap_borders(&mmap);
	ctx->minimap_img.img = NULL;
	if (mmap.map)
		free_tab((void **)mmap.map);
	mmap.map = NULL;
}
