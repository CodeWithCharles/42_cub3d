/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 16:46:38 by cpoulain          #+#    #+#             */
/*   Updated: 2025/03/19 15:10:44 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Static prototypes

static void			_get_texture_face(
						t_ray *ray);

static void			_door_handling(
						t_ray *ray);

static unsigned int	_get_pixel_color(
						t_game_ctx *ctx,
						t_ray *ray);

// Header implementations

void	update_screen_pixel(
	t_game_ctx *ctx,
	t_ray *ray,
	int x
)
{
	int				y;

	_get_texture_face(ray);
	ray->tex_cpt.bound.x = (int)(ray->wall_x * TEX_SIZE);
	if ((ray->side == 0 && ray->dir.x < 0)
		|| (ray->side == 1 && ray->dir.y > 0))
		ray->tex_cpt.bound.x = TEX_SIZE - ray->tex_cpt.bound.x - 1;
	_door_handling(ray);
	ray->tex_cpt.step = 1.0 * TEX_SIZE / ray->line_height;
	ray->tex_cpt.pos = (ray->draw_boundaries.x - (WIN_HEIGHT / 2
				+ ctx->player.pitch) + ray->line_height / 2)
		* ray->tex_cpt.step;
	y = ray->draw_boundaries.x;
	while (y < ray->draw_boundaries.y)
		ctx->screen_pixels[y++][x] = _get_pixel_color(ctx, ray);
}

// Static implementations

static void	_get_texture_face(
	t_ray *ray
)
{
	if (ray->side == 0)
	{
		if (ray->dir.x < 0)
			ray->tex_cpt.face = WEST;
		else
			ray->tex_cpt.face = EAST;
	}
	else
	{
		if (ray->dir.y > 0)
			ray->tex_cpt.face = SOUTH;
		else
			ray->tex_cpt.face = NORTH;
	}
}

static void	_door_handling(
	t_ray *ray
)
{
	double	shift;

	if (ray->door.hit)
	{
		shift = (TEX_SIZE / 2) * ray->door.timer;
		if (ray->door.type == ELEM_DOOR_H)
			ray->tex_cpt.bound.x += shift * (-(ray->dir.x <= 0));
		else if (ray->door.type == ELEM_DOOR_V)
			ray->tex_cpt.bound.y += shift * (-(ray->dir.y <= 0));
		ray->tex_cpt.bound.x = min(max(ray->tex_cpt.bound.x, 0), TEX_SIZE - 1);
		ray->tex_cpt.bound.y = min(max(ray->tex_cpt.bound.y, 0), TEX_SIZE - 1);
	}
}

static unsigned int	_get_pixel_color(
	t_game_ctx *ctx,
	t_ray *ray
)
{
	unsigned int	color;

	ray->tex_cpt.bound.y = min((int)ray->tex_cpt.pos, TEX_SIZE - 1);
	ray->tex_cpt.pos += ray->tex_cpt.step;
	if (ray->door.hit)
		color = ctx->game_textures[5]
		[TEX_SIZE * ray->tex_cpt.bound.y + ray->tex_cpt.bound.x];
	else
		color = ctx->game_textures[ray->tex_cpt.face]
		[TEX_SIZE * ray->tex_cpt.bound.y + ray->tex_cpt.bound.x];
	if (ray->door.hit || ray->tex_cpt.face == NORTH
		|| ray->tex_cpt.face == EAST)
		color = (color & 0xFEFEFE) >> 1;
	return (color);
}
