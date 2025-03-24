/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:09:04 by cpoulain          #+#    #+#             */
/*   Updated: 2025/03/06 13:27:11 by cpoulain         ###   ########.fr       */
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

// TODO: Change clean exit to proper error message
void	init_img(
	t_game_ctx *ctx,
	t_img *img,
	int width,
	int height
)
{
	ft_bzero(img, sizeof(t_img));
	img->img = mlx_new_image(ctx->mlx, width, height);
	if (!img->img)
		clean_exit(ctx, NULL, RET_ERR);
	img->pixels_ptr = (int *)mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_len, &img->endianess);
}
