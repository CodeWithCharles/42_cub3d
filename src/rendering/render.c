/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:43:30 by cpoulain          #+#    #+#             */
/*   Updated: 2025/03/21 15:37:01 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Static prototypes

static void	_render_raycasting(
				t_game_ctx *ctx);

static void	_render_frame(
				t_game_ctx *ctx);

static void	_set_frame_image_pixel(
				t_game_ctx *ctx,
				t_img *img,
				int x,
				int y);

// Header implementations

// TODO: Implement other things, enemies, doors, etc.
void	render_screen(
	t_game_ctx *ctx
)
{
	_render_raycasting(ctx);
}

int	render(
	t_game_ctx *ctx
)
{
	ctx->player.has_moved += move_player_handler(ctx);
	update_doors(ctx, (double)(DOOR_DT_FACTOR / (double)TEX_SIZE));
	if (ctx->player.has_moved == 0)
		return (0);
	render_screen(ctx);
	return (0);
}

// Static implementations

static void	_render_raycasting(
	t_game_ctx *ctx
)
{
	refresh_screen_pixels(ctx);
	ctx->ray = (t_ray){};
	raycasting(ctx);
	_render_frame(ctx);
}

static void	_render_frame(
	t_game_ctx *ctx
)
{
	t_img	img;
	int		x;
	int		y;

	img.img = NULL;
	init_img(ctx, &img, WIN_WIDTH, WIN_HEIGHT);
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			_set_frame_image_pixel(ctx, &img, x, y);
			++x;
		}
		++y;
	}
	ctx->minimap_img = img;
	render_minimap(ctx);
	mlx_put_image_to_window(ctx->mlx, ctx->window, img.img, 0, 0);
	mlx_destroy_image(ctx->mlx, img.img);
}

static void	_set_frame_image_pixel(
	t_game_ctx *ctx,
	t_img *img,
	int x,
	int y
)
{
	if (ctx->screen_pixels[y][x] > 0)
		set_image_pixel(img, x, y, ctx->screen_pixels[y][x]);
	else if (y < WIN_HEIGHT / 2 + ctx->player.pitch)
		set_image_pixel(img, x, y, ctx->hex_ceiling);
	else if (y >= WIN_HEIGHT / 2 + ctx->player.pitch)
		set_image_pixel(img, x, y, ctx->hex_floor);
}
