/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arg_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:31:40 by cpoulain          #+#    #+#             */
/*   Updated: 2025/02/20 17:08:27 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	print_arg_error(
	t_game_ctx *ctx,
	const char *error,
	const char *arg
)
{
	fd_printf(STDERR_FILENO, error,
		TERM_RED,
		ctx->p_name,
		arg,
		TERM_RESET);
}
