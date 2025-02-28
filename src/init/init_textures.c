/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:43:35 by cpoulain          #+#    #+#             */
/*   Updated: 2025/02/28 17:18:28 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Static prototypes

static void			_init_texture_img(
						t_game_ctx *ctx,
						t_img *img,
						char *path);

static unsigned int	*_xpm_to_pixels(
						t_game_ctx *ctx,
						char *path);

// Header implementations

void	init_textures(
	t_game_ctx *ctx
)
{
	ctx->game_textures = ft_calloc(7 + (ctx->texctx.door_path != NULL),
			sizeof(ctx->game_textures));
	if (!ctx->texctx.is_ceil_rgb)
		_xpm_to_pixels(ctx, ctx->texctx.ceiling);
	if (!ctx->texctx.is_floor_rgb)
		_xpm_to_pixels(ctx, ctx->texctx.floor);
	ctx->game_textures[NORTH] = _xpm_to_pixels(ctx,
			ctx->texctx.north_path);
	ctx->game_textures[SOUTH] = _xpm_to_pixels(ctx,
			ctx->texctx.south_path);
	ctx->game_textures[WEST] = _xpm_to_pixels(ctx,
			ctx->texctx.west_path);
	ctx->game_textures[EAST] = _xpm_to_pixels(ctx,
			ctx->texctx.east_path);
}

// Static implementations

static unsigned int	*_xpm_to_pixels(
	t_game_ctx *ctx,
	char *path
)
{
	t_img			tmp;
	unsigned int	*buffer;
	int				x;
	int				y;

	_init_texture_img(ctx, &tmp, path);
	buffer = ft_calloc(1, sizeof(buffer) * TEX_SIZE * TEX_SIZE);
	y = 0;
	while (y < TEX_SIZE)
	{
		x = 0;
		while (x < TEX_SIZE)
		{
			buffer[y * TEX_SIZE + x] = tmp.pixels_ptr[y * TEX_SIZE + x];
			++x;
		}
		++y;
	}
	mlx_destroy_image(ctx->mlx, tmp.img);
	return (buffer);
}

static void	_init_texture_img(
	t_game_ctx *ctx,
	t_img *img,
	char *path
)
{
	int	tex_size;

	img->img = NULL;
	img->pixels_ptr = NULL;
	img->bits_per_pixel = 0;
	img->line_len = 0;
	img->endianess = 0;
	ft_bzero(img, sizeof(t_img));
	img->img = mlx_xpm_file_to_image(ctx->mlx, path, &tex_size, &tex_size);
	if (!img->img)
		clean_exit(ctx, ERR_LOADING_XPM, 1);
	img->pixels_ptr = (int *)mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_len, &img->endianess);
	return ;
}
