/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:45:42 by cpoulain          #+#    #+#             */
/*   Updated: 2025/03/26 15:58:23 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Static prototypes

void	hex_to_texture(
	unsigned int **texture,
	unsigned int hex
)
{
	int	i;

	i = 0;
	*texture = malloc(sizeof(unsigned int) * (TEX_SIZE * TEX_SIZE));
	while (i < TEX_SIZE * TEX_SIZE)
		(*texture)[i++] = hex;
}
