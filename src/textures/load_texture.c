/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:45:42 by cpoulain          #+#    #+#             */
/*   Updated: 2025/02/25 15:37:56 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Static prototypes

static int	load_texture(
	t_game_ctx *ctx,
	unsigned int **texture
)
{
	void	*texture_ptr;
	int		size;

	size = TEX_SIZE;
	texture_ptr = mlx_xpm_file_to_image(ctx->mlx,
			(char *)(*texture), &size, &size);
	if (!texture_ptr)
		return (print_gen_error(ERR_LOADING_XPM), RET_ERR);
	free(*texture);
	*texture = texture_ptr;
	return (RET_OK);
}

static int	_get_hex_texture(
	t_game_ctx *ctx,
	int index
)
{
	if (index == FACE_F && ctx->texctx.is_floor_rgb)
	{
		if (parse_str_to_hex(&ctx->hex_floor, ctx->texctx.floor) == RET_ERR)
			return (RET_ERR);
	}
	else if (index == FACE_C && ctx->texctx.is_ceil_rgb)
	{
		if (parse_str_to_hex(&ctx->hex_ceiling, ctx->texctx.ceiling) == RET_ERR)
			return (RET_ERR);
	}
	return (RET_OK);
}

int	load_textures(
	t_game_ctx *ctx
)
{
	int		i;

	i = FACE_NO;
	while (i < FACE_D + 1)
	{
		if (_get_hex_texture(ctx, i) == RET_ERR)
			clean_exit(ctx, 1);
		else if (check_file((char *)(ctx->game_textures[i]), false) != 0)
			return (RET_ERR);
		else
		{
			if (load_texture(ctx, &ctx->game_textures[i]) == RET_ERR)
				return (RET_ERR);
		}
		i++;
	}
	return (RET_OK);
}
