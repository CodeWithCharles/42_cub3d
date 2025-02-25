/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_game_ctx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:10:53 by mkaliszc          #+#    #+#             */
/*   Updated: 2025/02/25 17:34:07 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_texture(t_tex_ctx *textures, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		textures->north_path = ft_strdup(line + 3);
	if (ft_strncmp(line, "SO ", 3) == 0)
		textures->south_path = ft_strdup(line + 3);
	if (ft_strncmp(line, "WE ", 3) == 0)
		textures->west_path = ft_strdup(line + 3);
	if (ft_strncmp(line, "EA ", 3) == 0)
		textures->east_path = ft_strdup(line + 3);
	if (ft_strncmp(line, "F ", 2) == 0)
		textures->floor = ft_strdup(line + 2);
	if (ft_strncmp(line, "C ", 2) == 0)
		textures->ceiling = ft_strdup(line + 2);
}

t_map_element	set_map_elem_cur(int i, int j, char **map, int map_start)
{
	t_map_element	map_element;

	map_element.pos.x = j;
	map_element.pos.y = i - map_start;
	map_element.type = get_elem_type(map[i][j]);
	return (map_element);
}

t_tex_ctx	init_tex_ctx(char **map, int *start_of_minimap)
{
	int			i;
	int			nbr_textures_set;
	t_tex_ctx	textures;

	i = 0;
	nbr_textures_set = 0;
	while (map[i] && nbr_textures_set <= 6)
	{
		if (map[i][0] != '_')
		{
			set_texture(&textures, map[i]);
			nbr_textures_set++;
		}
		i++;
	}
	*start_of_minimap = i - 1;
	textures.is_ceil_rgb = true;
	textures.is_floor_rgb = true;
	return (textures);
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
	game->map = malloc(sizeof(t_map_element *) * game->m_height);
	ft_bzero(game->map, sizeof(t_map_element *) * game->m_height);
	while (i < game->m_height)
	{
		j = 0;
		game->map[i] = malloc(sizeof(t_map_element) * game->m_width);
		while (j < game->m_width)
			init_map_elem(&game->map[i][j++]);
		i++;
	}
}

void	fill_game_ctx(char **map, t_game_ctx *ptr)
{
	int	start_of_minimap;

	ptr->texctx = init_tex_ctx(map, &start_of_minimap);
	init_map_elems(ptr, map + start_of_minimap);
}
