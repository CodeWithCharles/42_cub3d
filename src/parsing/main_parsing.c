/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaliszc <mkaliszc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:29:56 by mkaliszc          #+#    #+#             */
/*   Updated: 2025/03/03 18:46:17 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	test_game(t_game_ctx game)
{
	unsigned int	x = 0;
	unsigned int	y = 0;
	printf("%s\n", game.texctx.door_path);
	printf("%s\n", game.texctx.north_path);
	printf("%s\n", game.texctx.south_path);
	printf("%s\n", game.texctx.east_path);
	printf("%s\n", game.texctx.west_path);
	printf("%s\n", game.texctx.floor);
	printf("%s\n", game.texctx.ceiling);
	printf("%d && %d\n\n", game.m_height, game.m_width);
	while (y < game.m_height)
	{
		x = 0;
		while (x < game.m_width)
		{
			printf("%d", game.map[y][x].type);
			x++;
		}
		printf("\n");
		y++;
	}
}

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
	//test_game(*game);
	return (ft_free_split(&map), RET_OK);
}
