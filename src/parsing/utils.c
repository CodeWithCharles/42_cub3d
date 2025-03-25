/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaliszc <mkaliszc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 19:26:31 by mkaliszc          #+#    #+#             */
/*   Updated: 2025/03/25 14:23:50 by mkaliszc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	valid_char(char c)
{
	return (c == _FLOOR || c == _WALL || c == _VOID
		|| ft_strchr(_SPAWNS, c) != 0 || ft_strchr(_DOORS, c) != 0);
}

static int	validate_line(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (valid_char(line[i]) == 0)
			return (RET_ERR);
		i++;
	}
	return (RET_OK);
}

bool	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0')
		return (true);
	return (false);
}

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
	while (i < count)
	{
		if (ft_strcmp(map[i], "_") == 0 || validate_line(map[i]) == RET_ERR
			|| is_empty_line(map[i]) == true)
			invalid = true;
		new_map[i] = ft_strdup(map[i]);
		i++;
	}
	new_map[count] = NULL;
	if (invalid)
		return (free_tab((void **)new_map), NULL);
	return (new_map);
}
