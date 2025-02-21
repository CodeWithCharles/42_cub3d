/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:21:30 by cpoulain          #+#    #+#             */
/*   Updated: 2025/02/21 17:44:12 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	void		*str;
	t_game_ctx	game;

	(void)argc;
	init_game(argv[0], &game);
	str = ft_strdup("255,123,a");
	if (parse_str_to_hex(&game, &game.hex_ceiling, str) == RET_OK)
		printf("%X\n", game.hex_ceiling);
	free(str);
	return (0);
}
