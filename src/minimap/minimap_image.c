/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:20:09 by cpoulain          #+#    #+#             */
/*   Updated: 2025/03/21 15:43:26 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Header implementations

void	set_tile_pixels(
	t_minimap *mmap,
	unsigned int x,
	unsigned int y,
	unsigned int color
)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < mmap->tile_size)
	{
		j = 0;
		while (j < mmap->tile_size)
		{
			set_image_pixel(mmap->img, x + j + mmap->img_width_offset,
				y + i + mmap->tile_size, color);
			++j;
		}
		++i;
	}
}

// TODO: Door color
void	draw_mmap_tile(
	t_minimap *mmap,
	unsigned int x,
	unsigned int y
)
{
	int	color;

	if (mmap->map[y][x] == _PLAYER)
		color = MMAP_COLOR_PLAYER;
	else if (mmap->map[y][x] == _WALL)
		color = MMAP_COLOR_WALL;
	else if (mmap->map[y][x] == _FLOOR)
		color = MMAP_COLOR_FLOOR;
	else if (mmap->map[y][x] == _SPAWNS[0])
		color = MMAP_COLOR_SPAWN;
	else
		color = MMAP_COLOR_VOID;
	set_tile_pixels(mmap, x * mmap->tile_size, y * mmap->tile_size, color);
}

void	draw_mmap(
	t_minimap *mmap
)
{
	unsigned int	x;
	unsigned int	y;

	y = 0;
	while (y < mmap->size)
	{
		x = 0;
		while (x < mmap->size)
		{
			if (!mmap->map[y] || !mmap->map[y][x])
				break ;
			draw_mmap_tile(mmap, x, y);
			++x;
		}
		++y;
	}
}

void	draw_mmap_borders(
	t_minimap *mmap
)
{
	unsigned int	size;
	unsigned int	x;
	unsigned int	y;
	const int		padding = MMAP_BORDER_PADDING;

	size = MMAP_PIXEL_SIZE + mmap->tile_size;
	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			if (x < padding || x > size - padding
				|| y < padding || y > size - MMAP_BORDER_PADDING)
				set_image_pixel(mmap->img, x + mmap->img_width_offset,
					y + mmap->tile_size, MMAP_COLOR_BORDER);
			++x;
		}
		++y;
	}
}
