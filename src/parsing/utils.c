/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaliszc <mkaliszc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 19:26:31 by mkaliszc          #+#    #+#             */
/*   Updated: 2025/03/03 12:43:32 by mkaliszc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*skip_space(char *line)
{
	while (*line == ' ')
		line++;
	return (line);
}

char	**dup_map(char **map)
{
	char	**new_map;
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (map[count])
		count++;
	new_map = malloc((count + 1) * sizeof(char *));
	if (!new_map)
		return (NULL);
	while (i < count)
	{
		new_map[i] = strdup(map[i]);
		i++;
	}
	new_map[count] = NULL;
	return (new_map);
}

