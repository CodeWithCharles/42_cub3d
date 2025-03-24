/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:03:03 by cpoulain          #+#    #+#             */
/*   Updated: 2025/03/17 17:05:32 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Header implementations

void	init_ray_dir(t_ray *ray)
{
	if (ray->side_dist.x < ray->side_dist.y)
	{
		ray->side_dist.x += ray->delta_dist.x;
		ray->map.x += ray->step.x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist.y += ray->delta_dist.y;
		ray->map.y += ray->step.y;
		ray->side = 1;
	}
}

int	is_ray_in_bound(t_game_ctx *ctx, t_ray *ray)
{
	return (ray->map.y >= RAY_BOUND_MIN_OFFSET
		&& ray->map.x >= RAY_BOUND_MIN_OFFSET
		&& ray->map.y <= ctx->m_height - RAY_BOUND_MIN_OFFSET
		&& ray->map.x <= ctx->m_width - RAY_BOUND_MAX_OFFSET);
}
