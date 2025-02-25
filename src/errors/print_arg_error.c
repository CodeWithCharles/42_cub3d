/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arg_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:31:40 by cpoulain          #+#    #+#             */
/*   Updated: 2025/02/25 14:50:41 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	print_arg_error(
	const char *error,
	const char *arg
)
{
	fd_printf(STDERR_FILENO, error,
		TERM_RED,
		g_pname,
		arg,
		TERM_RESET);
}
