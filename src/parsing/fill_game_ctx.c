/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_game_ctx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:10:53 by mkaliszc          #+#    #+#             */
/*   Updated: 2025/03/26 16:03:20 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	set_map_elem_cur(
	t_map_element *curr,
	unsigned int i,
	unsigned int j,
	char curr_char
)
{
	t_door	*door;

	curr->pos.x = j;
	curr->pos.y = i;
	curr->type = get_elem_type(curr_char);
	curr->data = NULL;
	if (curr->type == ELEM_DOOR_H || curr->type == ELEM_DOOR_V)
	{
		door = malloc(sizeof(t_door));
		door->anim_state = DOOR_CLOSED;
		door->timer = 0.0;
		curr->data = door;
	}
}

void	init_tex_ctx(
	t_game_ctx *ctx,
	char **map,
	int *start_of_minimap
)
{
	int			i;
	t_tex_ctx	textures;

	textures = (t_tex_ctx){};
	i = 0;
	while (map[i])
	{
		if (map[i][0] != '_' && map[i][0] != _WALL
			&& map[i][0] != _VOID && map[i][0] != _FLOOR)
			set_texture(&textures, map[i]);
		else if (map[i][0] == _WALL || map[i][0] == _VOID
			|| map[i][0] == _FLOOR)
			break ;
		i++;
	}
	*start_of_minimap = i;
	ctx->texctx = textures;
	ctx->texctx.is_ceil_valid = !parse_str_to_hex(&ctx->hex_ceiling,
			textures.ceiling);
	ctx->texctx.is_floor_valid = !parse_str_to_hex(&ctx->hex_floor,
			textures.floor);
}

void	init_map_elem(t_map_element *map_element)
{
	map_element->data = NULL;
	map_element->pos = (t_2d_vector){};
	map_element->type = ELEM_VOID;
}

void	init_map_elems(t_game_ctx *game, char **map)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	get_map_size(game, map);
	game->map = malloc(sizeof(t_map_element *) * (game->m_height + 1));
	ft_bzero(game->map, sizeof(t_map_element *) * (game->m_height + 1));
	while (i < game->m_height)
	{
		j = 0;
		game->map[i] = malloc(sizeof(t_map_element) * game->m_width);
		while (j < game->m_width)
			init_map_elem(&game->map[i][j++]);
		++i;
	}
	game->map[i] = NULL;
}

void	fill_game_ctx(char **map, t_game_ctx *ptr)
{
	int	start_of_minimap;

	init_tex_ctx(ptr, map, &start_of_minimap);
	init_map_elems(ptr, map + start_of_minimap);
	fill_map(ptr, map + start_of_minimap);
	init_player_data(ptr, map + start_of_minimap);
}
