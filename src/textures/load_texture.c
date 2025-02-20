/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:45:42 by cpoulain          #+#    #+#             */
/*   Updated: 2025/02/20 17:57:57 by cpoulain         ###   ########.fr       */
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
	texture_ptr = mlx_xpm_file_to_image(ctx->mlx_data.mlx,
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
		if (((i == FACE_F && ctx->is_floor_rgb)
				|| (i == FACE_C && ctx->is_ceil_rgb)))
			parse_str_to_hex(ctx, &ctx->game_textures[i]);
		else
		{
			if (check_file(ctx, (char *)(ctx->game_textures[i]), false) != 0)
				return (RET_ERR);
			else
				if (load_texture(ctx, &ctx->game_textures[i]) != RET_OK)
					return (RET_ERR);
		}
		i++;
	}
	return (RET_OK);
}
