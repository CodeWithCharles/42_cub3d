/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaliszc <mkaliszc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 19:26:31 by mkaliszc          #+#    #+#             */
/*   Updated: 2025/02/25 20:06:21 by mkaliszc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char **dup_map(char **map)
{
    int i;
	int	count;

	i = 0;
	count = 0;
    while (map[count])
        count++;
    char **new_map = malloc((count + 1) * sizeof(char *));
    if (!new_map)
        return NULL;
    while (i < count)
	{
        new_map[i] = strdup(map[i]);
		i++;
	}
    new_map[count] = NULL;
    return (new_map);
}
