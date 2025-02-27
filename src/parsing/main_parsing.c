/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaliszc <mkaliszc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:29:56 by mkaliszc          #+#    #+#             */
/*   Updated: 2025/02/27 18:58:44 by mkaliszc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main_parsing(t_game_ctx *game, char **argv)
{
	char		**map;
	char		*buffer;

	buffer = fill_buffer(argv[1]);
	map = ft_split(buffer, '\n');
	free(buffer);
	if (check_map_format(map) == false)
		return (ft_free_split(&map), RET_ERR);
	fill_game_ctx(map, game);
	return (ft_free_split(&map), RET_OK);
}
