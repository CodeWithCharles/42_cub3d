/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:43:30 by cpoulain          #+#    #+#             */
/*   Updated: 2025/02/28 12:51:56 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Static prototypes

static void	render_raycasting(
				t_game_ctx *ctx);

// Header implementations

// TODO: Implement other things, enemies, doors, etc.
void	render_screen(
	t_game_ctx *ctx
)
{
	render_raycasting(ctx);
}

// Static implementations

static void	render_raycasting(
	t_game_ctx *ctx
)
{
	refresh_screen_pixels(ctx);
	ctx->ray = (t_ray){};
}
