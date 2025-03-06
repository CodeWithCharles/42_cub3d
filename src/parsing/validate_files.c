/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:57:13 by cpoulain          #+#    #+#             */
/*   Updated: 2025/03/06 16:55:35 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Static prototypes

// Header implementations

int	validate_files(
	t_game_ctx *ctx
)
{
	if (!ctx->texctx.is_ceil_rgb)
	{
		if (ft_strchr(ctx->texctx.ceiling, ',') != 0)
			return (print_arg_error(ERR_RGB, ctx->texctx.ceiling), RET_ERR);
		else if (check_file(ctx->texctx.ceiling, false))
			return (RET_ERR);
	}
	else if (!ctx->texctx.is_floor_rgb)
	{
		if (ft_strchr(ctx->texctx.floor, ',') != 0)
			return (print_arg_error(ERR_RGB, ctx->texctx.floor), RET_ERR);
		else if (check_file(ctx->texctx.floor, false))
			return (RET_ERR);
	}
	if (check_file(ctx->texctx.north_path, false)
		|| check_file(ctx->texctx.south_path, false)
		|| check_file(ctx->texctx.east_path, false)
		|| check_file(ctx->texctx.west_path, false)
		|| (ctx->texctx.door_path && check_file(ctx->texctx.door_path, 0)))
		return (RET_ERR);
	return (RET_OK);
}
