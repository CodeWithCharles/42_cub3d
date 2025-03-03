/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:22:11 by cpoulain          #+#    #+#             */
/*   Updated: 2025/03/03 12:05:04 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Static prototypes

static void	_init_raycasting_ray(
				t_ray *ray,
				t_player *player,
				int ray_index);

static void	_init_dda(
				t_ray *ray,
				t_player *player);

static void	_perform_dda(
				t_game_ctx *ctx,
				t_ray *ray);

static void	_calculate_line_length(
				t_ray *ray,
				t_player *player);

// Header implementations

int	raycasting(
	t_game_ctx *ctx
)
{
	t_ray	ray;
	int		x;

	x = 0;
	ray = ctx->ray;
	while (x < WIN_WIDTH)
	{
		_init_raycasting_ray(&ray, &ctx->player, x);
		_init_dda(&ray, &ctx->player);
		_perform_dda(ctx, &ray);
		_calculate_line_length(&ray, &ctx->player);
		update_screen_pixel(ctx, &ray, x);
		++x;
	}
	return (RET_OK);
}

// Static implementations

static void	_init_raycasting_ray(
	t_ray *ray,
	t_player *player,
	int ray_index
)
{
	ft_bzero(ray, sizeof(t_ray));
	ray->cam_x = 2 * ray_index / (double)WIN_WIDTH - 1;
	ray->dir.x = player->dir.x + player->plane.x * ray->cam_x;
	ray->dir.y = player->dir.y + player->plane.y * ray->cam_x;
	ray->map.x = (int)player->pos.x;
	ray->map.y = (int)player->pos.y;
	ray->delta_dist.x = fabs(1 / ray->dir.x);
	ray->delta_dist.y = fabs(1 / ray->dir.y);
}

static void	_init_dda(
	t_ray *ray,
	t_player *player
)
{
	ray->step.x = !(ray->dir.x < 0) - 1 * (ray->dir.x < 0);
	ray->step.y = !(ray->dir.y < 0) - 1 * (ray->dir.y < 0);
	if (ray->dir.x < 0)
		ray->side_dist.x = (player->pos.x - ray->map.x) * ray->delta_dist.x;
	else
		ray->side_dist.x = (ray->map.x + 1.0 - player->pos.x)
			* ray->delta_dist.x;
	if (ray->dir.y < 0)
		ray->side_dist.y = (player->pos.y - ray->map.y) * ray->delta_dist.y;
	else
		ray->side_dist.y = (ray->map.y + 1.0 - player->pos.y)
			* ray->delta_dist.y;
}

static void	_perform_dda(
	t_game_ctx *ctx,
	t_ray *ray
)
{
	while (ray->map.y >= RAY_BOUND_MIN_OFFSET
		&& ray->map.x >= RAY_BOUND_MIN_OFFSET
		&& ray->map.y <= ctx->m_height - RAY_BOUND_MIN_OFFSET
		&& ray->map.x <= ctx->m_width - RAY_BOUND_MAX_OFFSET)
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
		if (ctx->map[ray->map.y][ray->map.x].type == ELEM_WALL
			|| ctx->map[ray->map.y][ray->map.x].type == ELEM_VOID)
			break ;
	}
}

static void	_calculate_line_length(
	t_ray *ray,
	t_player *player
)
{
	ray->wall_dist = (ray->side_dist.x - ray->delta_dist.x) * (ray->side == 0)
		+ (ray->side_dist.y - ray->delta_dist.y) * (ray->side != 0);
	ray->line_height = (int)(WIN_HEIGHT / ray->wall_dist);
	ray->draw_boundaries.x = -(ray->line_height) / 2 + WIN_HEIGHT / 2;
	ray->draw_boundaries.x *= !(ray->draw_boundaries.x < 0);
	ray->draw_boundaries.y = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_boundaries.y >= WIN_HEIGHT)
		ray->draw_boundaries.y = WIN_HEIGHT - 1;
	if (ray->side == 0)
		ray->wall_x = player->pos.y + ray->wall_dist * ray->dir.y;
	else
		ray->wall_x = player->pos.x + ray->wall_dist * ray->dir.x;
	ray->wall_x -= floor(ray->wall_x);
}
