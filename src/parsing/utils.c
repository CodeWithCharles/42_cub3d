/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 19:26:31 by mkaliszc          #+#    #+#             */
/*   Updated: 2025/03/21 14:28:30 by cpoulain         ###   ########.fr       */
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
	bool	invalid;

	i = 0;
	count = 0;
	invalid = false;
	while (map[count])
		count++;
	new_map = malloc((count + 1) * sizeof(char *));
	if (!new_map)
		return (NULL);
	while (i < count)
	{
		if (ft_strcmp(map[i], "_") == 0)
			invalid = true;
		new_map[i] = strdup(map[i]);
		i++;
	}
	new_map[count] = NULL;
	if (invalid)
		return (free_tab((void **)new_map), NULL);
	return (new_map);
}
