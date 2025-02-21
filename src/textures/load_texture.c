/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:45:42 by cpoulain          #+#    #+#             */
/*   Updated: 2025/02/21 17:29:40 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Static prototypes

static int	load_texture(
	t_game_ctx *ctx,
	void **texture
)
{
	void	*texture_ptr;
	int		size;

	size = TEX_SIZE;
	texture_ptr = mlx_xpm_file_to_image(ctx->mlx,
			(char *)(*texture), &size, &size);
	if (!texture_ptr)
		return (print_gen_error(ctx, ERR_LOADING_XPM), RET_ERR);
	free(*texture);
	*texture = texture_ptr;
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
		if (i == FACE_F && ctx->texctx.is_floor_rgb)
			if (parse_str_to_hex(ctx, ctx->texctx.floor) == RET_ERR)
				return (RET_ERR);
		else if (i == FACE_C && ctx->texctx.is_ceil_rgb)
			if (parse_str_to_hex(ctx, ctx->texctx.ceiling) == RET_ERR)
				return (RET_ERR);
		else
		{
			if (check_file(ctx, (char *)(ctx->game_textures[i]), false) != 0)
				return (RET_ERR);
			else
				if (load_texture(ctx, &ctx->game_textures[i]) == RET_ERR)
					return (RET_ERR);
		}
		i++;
	}
	return (RET_OK);
}
