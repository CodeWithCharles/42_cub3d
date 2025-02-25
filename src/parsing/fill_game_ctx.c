/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_game_ctx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaliszc <mkaliszc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:10:53 by mkaliszc          #+#    #+#             */
/*   Updated: 2025/02/25 20:34:34 by mkaliszc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	set_texture(t_tex_ctx *textures, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		textures->north_path = ft_strdup(line + 3);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		textures->south_path = ft_strdup(line + 3);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		textures->west_path = ft_strdup(line + 3);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		textures->east_path = ft_strdup(line + 3);
	else if (ft_strncmp(line, "F ", 2) == 0)
		textures->floor = ft_strdup(line + 2);
	else if (ft_strncmp(line, "C ", 2) == 0)
		textures->ceiling = ft_strdup(line + 2);
	else if (ft_strncmp(line, "DO ", 3) == 0)
		textures->door_path = ft_strdup(line + 3);
}

void	set_map_elem_cur(
	t_map_element *curr,
	unsigned int i,
	unsigned int j,
	char curr_char
)
{
	curr->pos.x = j;
	curr->pos.y = i;
	curr->type = get_elem_type(curr_char);
}

t_tex_ctx	init_tex_ctx(char **map, int *start_of_minimap)
{
	int			i;
	t_tex_ctx	textures;

	i = 0;
	while (map[i])
	{
		if (map[i][0] != '_' && map[i][0] != '1')
			set_texture(&textures, map[i]);
		else if (map[i][0] == '1')
			break ;
		i++;
	}
	*start_of_minimap = i;
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

void	fill_map_line(
	t_map_element *map_line,
	char *line,
	unsigned int m_width,
	unsigned int i
)
{
	unsigned int	j;

	j = 0;
	while (j < m_width)
	{
		set_map_elem_cur(&map_line[j], i, j, line[j]);
		j++;
	}
}

void	fill_map(t_game_ctx *game, char **map)
{
	unsigned int	i;

	i = 0;
	while (i < game->m_height)
	{
		fill_map_line(game->map[i], map[i], game->m_width, i);
		i++;
	}
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
	fill_map(ptr, map + start_of_minimap);
}
