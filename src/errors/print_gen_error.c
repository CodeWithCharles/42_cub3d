/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_gen_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:05:24 by cpoulain          #+#    #+#             */
/*   Updated: 2025/02/25 14:50:30 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	print_gen_error(
	const char *error
)
{
	fd_printf(STDERR_FILENO, error,
		TERM_RED,
		g_pname,
		TERM_RESET);
}
