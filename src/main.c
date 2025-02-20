/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:21:30 by cpoulain          #+#    #+#             */
/*   Updated: 2025/02/20 18:06:41 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	void		*str;
	t_game_ctx	game;

	(void)argc;
	game = (t_game_ctx){};
	game.p_name = argv[0];
	str = ft_strdup("255,123,72");
	if (parse_str_to_hex(&game, &str) == RET_OK)
		printf("%lX\n", (unsigned long)(str));
	free(str);
	return (0);
}
