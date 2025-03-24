/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:21:30 by cpoulain          #+#    #+#             */
/*   Updated: 2025/03/24 15:20:01 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*g_pname = NULL;

static int	parse_args(t_game_ctx *game, char **argv)
{
	if (check_file(argv[1], true) == RET_ERR)
		return (RET_ERR);
	if (main_parsing(game, argv) == RET_ERR)
		return (RET_ERR);
	if (validate_files(game) == RET_ERR)
		return (RET_ERR);
	return (RET_OK);
}

int	main(int argc, char **argv)
{
	t_game_ctx	game;

	g_pname = ft_strrchr(argv[0], '/');
	if (g_pname)
		g_pname++;
	else
		g_pname = argv[0];
	if (argc != 2)
		return (print_gen_error(ERR_ARGS), RET_ERR);
	init_game(&game);
	if (parse_args(&game, argv) == RET_ERR)
		clean_exit(&game, NULL, RET_ERR);
	init_textures(&game);
	render_screen(&game);
	init_hooks(&game);
	mlx_mouse_hide(game.mlx, game.window);
	mlx_loop_hook(game.mlx, render, &game);
	mlx_loop(game.mlx);
	return (0);
}
