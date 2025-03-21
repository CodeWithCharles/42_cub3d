/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:45:42 by cpoulain          #+#    #+#             */
/*   Updated: 2025/03/03 18:41:49 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Static prototypes

void	hex_to_texture(
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
	if (index == FLOOR && ctx->texctx.is_floor_rgb)
	{
		hex_value = &ctx->hex_floor;
		texture = ctx->texctx.floor;
	}
	else if (index == CEILING && ctx->texctx.is_ceil_rgb)
	{
		hex_value = &ctx->hex_ceiling;
		texture = ctx->texctx.ceiling;
	}
	if (texture && parse_str_to_hex(ctx, hex_value, texture) == RET_ERR)
		return (RET_ERR);
	return (RET_OK);
}
