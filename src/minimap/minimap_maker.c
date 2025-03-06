/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_maker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:44:44 by cpoulain          #+#    #+#             */
/*   Updated: 2025/03/06 14:45:36 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Header implementations

int	get_mmap_offset(
	t_minimap *mmap,
	unsigned int map_size,
	unsigned int pos
)
{
	if (pos > mmap->view_dist)
	{
		if (map_size - pos > mmap->view_dist + 1)
			return (pos - mmap->view_dist);
		if (map_size - pos <= mmap->view_dist + 1)
			return (map_size - mmap->size);
	}
	return (0);
}

char	get_mmap_tile(
	t_game_ctx *ctx,
	t_minimap *mmap,
	unsigned int x,
	unsigned int y
)
{
	t_2d_vector	map_offset;
	t_elem		elem;

	map_offset.x = x + mmap->offset.x;
	map_offset.y = y + mmap->offset.y;
	if ((unsigned int)map_offset.y >= ctx->m_height
		|| (unsigned int)map_offset.x >= ctx->m_width)
		return (_VOID);
	if ((int)ctx->player.pos.x == map_offset.x
		&& (int)ctx->player.pos.y == map_offset.y)
		return (_PLAYER);
	elem = ctx->map[map_offset.y][map_offset.x].type;
	if (elem == ELEM_DOOR)
		return (_DOOR);
	else if (elem == ELEM_FLOOR)
		return (_FLOOR);
	else if (elem == ELEM_WALL)
		return (_WALL);
	else if (elem == ELEM_SPAWN_DIR_NORTH || elem == ELEM_SPAWN_DIR_SOUTH
		|| elem == ELEM_SPAWN_DIR_EAST || elem == ELEM_SPAWN_DIR_WEST)
		return (_SPAWNS[0]);
	else
		return (_VOID);
}

char	*generate_mmap_line(
	t_game_ctx *ctx,
	t_minimap *mmap,
	unsigned int y
)
{
	char			*line;
	unsigned int	x;

	line = ft_calloc(mmap->size + 1, sizeof(char));
	x = 0;
	while (x < mmap->size && x < ctx->m_width)
	{
		line[x] = get_mmap_tile(ctx, mmap, x, y);
		++x;
	}
	line[x] = '\0';
	return (line);
}

char	**generate_mmap(
	t_game_ctx *ctx,
	t_minimap *mmap
)
{
	char			**minimap;
	unsigned int	y;

	minimap = ft_calloc(mmap->size + 1, sizeof(minimap));
	y = 0;
	while (y < mmap->size && y < ctx->m_height)
	{
		minimap[y] = generate_mmap_line(ctx, mmap, y);
		++y;
	}
	minimap[y] = NULL;
	return (minimap);
}
