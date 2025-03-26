/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:57:13 by cpoulain          #+#    #+#             */
/*   Updated: 2025/03/26 16:02:38 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Header implementations

int	validate_files(
	t_game_ctx *ctx
)
{
	if (check_file(ctx->texctx.north_path, false)
		|| check_file(ctx->texctx.south_path, false)
		|| check_file(ctx->texctx.east_path, false)
		|| check_file(ctx->texctx.west_path, false)
		|| (ctx->texctx.door_path && check_file(ctx->texctx.door_path, 0)))
		return (RET_ERR);
	return (RET_OK);
}
