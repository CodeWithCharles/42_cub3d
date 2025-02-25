/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_game_ctx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaliszc <mkaliszc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:10:53 by mkaliszc          #+#    #+#             */
/*   Updated: 2025/02/25 15:40:59 by mkaliszc         ###   ########.fr       */
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
	map_element.is_end = false;
	return (map_element);
}

t_tex_ctx	init_tex_ctx(char **map, char **start_of_minimap)
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
	*start_of_minimap = ft_strdup(map[i - 1]);
	textures.is_ceil_rgb = true;
	textures.is_floor_rgb = true;
	return (textures);
}

t_map_element	*init_map_elem(char **map, char *mini)
{
	t_map_element	*map_element;
	int				i;
	int				j;
	int				cur;
	int				map_start;

	i = 0;
	cur = 0;
	while (ft_strcmp(map[i], mini) != 0)
		i++;
	map_element = malloc(sizeof(t_map_element) * get_nbr_of_pos(map + i));
	map_start = i;
	while (map[i])
	{
		j = 0;
		while (map[i][j] && map[i][j] != '_')
		{
			map_element[cur] = set_map_elem_cur(i, j, map, map_start);
			cur++;
			j++;
		}
		i++;
	}
	map_element[cur - 1].is_end = true;
	return (map_element);
}

void	fill_game_ctx(char **map, t_game_ctx **ptr)
{
	char	*start_of_minimap;

	start_of_minimap = NULL;
	(*ptr)->texctx = init_tex_ctx(map, &start_of_minimap);
	(*ptr)->map = init_map_elem(map, start_of_minimap);
	free(start_of_minimap);
}
