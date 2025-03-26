/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:22:11 by cpoulain          #+#    #+#             */
/*   Updated: 2025/03/26 16:33:21 by cpoulain         ###   ########.fr       */
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
	ray->cam_x = 2 * (ray_index + 0.5) / (double)WIN_WIDTH - 1;
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
	ray->step.x = !(ray->dir.x < 0) - (ray->dir.x < 0);
	ray->step.y = !(ray->dir.y < 0) - (ray->dir.y < 0);
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
	t_map_element	*elem;
	t_door			*door;
	double			opening_fraction;

	while (is_ray_in_bound(ctx, ray))
	{
		init_ray_dir(ray);
		elem = &ctx->map[ray->map.y][ray->map.x];
		if (elem->type == ELEM_WALL
			|| elem->type == ELEM_VOID)
			break ;
		if (elem->type == ELEM_DOOR_H || elem->type == ELEM_DOOR_V)
		{
			door = (t_door *)elem->data;
			ray->door.timer = door->timer;
			ray->door.type = elem->type;
			_calculate_line_length(ray, &ctx->player);
			opening_fraction = (door->timer / 2.0);
			if (ray->wall_x < (0.5 + opening_fraction)
				&& ray->wall_x > (0.5 - opening_fraction))
				continue ;
			ray->door.hit = 1;
			break ;
		}
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
	ray->draw_boundaries.x = max(0, -(ray->line_height) / 2
			+ WIN_HEIGHT / 2 + player->pitch);
	ray->draw_boundaries.y = min(WIN_HEIGHT - 1, ray->line_height / 2
			+ WIN_HEIGHT / 2 + player->pitch);
	if (ray->draw_boundaries.y >= WIN_HEIGHT)
		ray->draw_boundaries.y = WIN_HEIGHT - 1;
	if (ray->side == 0)
		ray->wall_x = player->pos.y + ray->wall_dist * ray->dir.y;
	else
		ray->wall_x = player->pos.x + ray->wall_dist * ray->dir.x;
	ray->wall_x -= floor(ray->wall_x);
}
