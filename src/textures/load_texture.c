/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:45:42 by cpoulain          #+#    #+#             */
/*   Updated: 2025/02/28 11:23:14 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Static prototypes

static void	_hex_to_texture(
	unsigned int **texture,
	unsigned int hex
)
{
	int	i;

	i = 0;
	*texture = malloc(sizeof(unsigned int) * (TEX_SIZE * TEX_SIZE));
	while (i < TEX_SIZE * TEX_SIZE)
		(*texture)[i++] = hex;
}

int	init_hex_texture(
	t_game_ctx *ctx,
	int index
)
{
	unsigned int	*hex_value;
	char			*texture;

	texture = NULL;
	if (index == FACE_F && ctx->texctx.is_floor_rgb)
	{
		hex_value = &ctx->hex_floor;
		texture = ctx->texctx.floor;
	}
	else if (index == FACE_C && ctx->texctx.is_ceil_rgb)
	{
		hex_value = &ctx->hex_ceiling;
		texture = ctx->texctx.ceiling;
	}
	if (texture && parse_str_to_hex(hex_value, texture) == RET_ERR)
		return (RET_ERR);
	if (texture && hex_value)
		_hex_to_texture(&ctx->game_textures[index], *hex_value);
	return (RET_OK);
}
