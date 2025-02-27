/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:45:42 by cpoulain          #+#    #+#             */
/*   Updated: 2025/02/27 17:02:19 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Static prototypes

static char	*get_current_texture(
	t_game_ctx *ctx,
	unsigned int index
)
{
	if (index == FACE_NO)
		return (ctx->texctx.north_path);
	else if (index == FACE_SO)
		return (ctx->texctx.south_path);
	else if (index == FACE_EA)
		return (ctx->texctx.east_path);
	else if (index == FACE_WE)
		return (ctx->texctx.west_path);
	else if (index == FACE_C)
		return (ctx->texctx.ceiling);
	else if (index == FACE_F)
		return (ctx->texctx.floor);
	else
		return (ctx->texctx.door_path);
}

// static int	load_texture(
// 	t_game_ctx *ctx,
// 	unsigned int **texture
// )
// {
// 	void	*texture_ptr;
// 	int		size;

// 	size = TEX_SIZE;
// 	texture_ptr = mlx_xpm_file_to_image(ctx->mlx,
// 			(char *)(*texture), &size, &size);
// 	if (!texture_ptr)
// 		return (print_gen_error(ERR_LOADING_XPM), RET_ERR);
// 	free(*texture);
// 	*texture = texture_ptr;
// 	return (RET_OK);
// }

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

static int	_get_hex_texture(
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

int	load_textures(
	t_game_ctx *ctx
)
{
	int				i;
	char			*curr_texture;
	unsigned int	malloc_size;

	i = FACE_NO;
	malloc_size = sizeof(unsigned int *) * (FACE_D
			+ (ctx->texctx.door_path != NULL));
	ctx->game_textures = malloc(malloc_size);
	ft_bzero(ctx->game_textures, malloc_size);
	while (i < FACE_D + 1)
	{
		curr_texture = get_current_texture(ctx, i);
		if (_get_hex_texture(ctx, i) == RET_ERR)
			clean_exit(ctx, RET_ERR);
		// else if (check_file(curr_texture, false) != 0)
		// 	return (RET_ERR);
		// else if ((i != FACE_D) != (ctx->texctx.door_path != NULL))
		// 	if (load_texture(ctx, &ctx->game_textures[i]) == RET_ERR)
		// 		return (RET_ERR);
		i++;
	}
	return (RET_OK);
}
