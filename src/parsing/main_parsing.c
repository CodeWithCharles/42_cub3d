/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:29:56 by mkaliszc          #+#    #+#             */
/*   Updated: 2025/02/25 17:26:52 by cpoulain         ###   ########.fr       */
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

// * debugging/test function

// void	print_map_elem(t_map_element *map)
// {
// 	int i = 0;

// 	while(map[i].is_end != true)
// 	{
// 		printf("at y = %d and x = %d\n type = %d\n-------------------------\n", map[i].pos.y, map[i].pos.x, map[i].type);
// 		i++;
// 	}
// 	printf("at y = %d and x = %d\n type = %d\n-------------------------\n", map[i].pos.y, map[i].pos.x, map[i].type);
// }

// void	print_texture(t_tex_ctx test)
// {
// 	printf("North : %s\n", test.north_path);
// 	printf("South : %s\n", test.south_path);
// 	printf("West : %s\n", test.west_path);
// 	printf("East : %s\n", test.east_path);
// 	printf("floor : %s\n", test.floor);
// 	printf("ceilling : %s\n", test.ceiling);
// }

// int	main(int argc, char **argv)
// {
// 	t_game_ctx	*return_pointer;

// 	return_pointer = main_parsing(argc, argv);
// 	if (return_pointer)
// 	{
// 		print_map_elem(return_pointer->map);
// 		print_texture(return_pointer->texctx);
// 		printf("gg boy\n");
// 		return (0);
// 	}
// 	return(1);
// }
