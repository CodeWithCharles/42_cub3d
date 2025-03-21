/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:51:53 by cpoulain          #+#    #+#             */
/*   Updated: 2025/02/28 12:10:50 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Static prototypes

static int	_str_to_color_tab(
				char *str,
				int (*color_tab)[3]);

static int	_check_valid_rgb(
				int color_tab[3]);

// Header implementation

int	parse_str_to_hex(
	t_game_ctx *ctx,
	unsigned int *var,
	char *str
)
{
	int				colors_tab[3];

	colors_tab[0] = -1;
	colors_tab[1] = -1;
	colors_tab[2] = -1;
	_str_to_color_tab(str, &colors_tab);
	if (colors_tab[0] == -1 || colors_tab[1] == -1 || colors_tab[2] == -1)
		return (RET_ERR);
	if (_check_valid_rgb(colors_tab))
		clean_exit(ctx, ERR_INVALID_RGB_DATA, 1);
	*var = ((colors_tab[0] & 0xff) << 16)
		+ ((colors_tab[1] & 0xff) << 8) + (colors_tab[2] & 0xff);
	return (RET_OK);
}

// Static implementations

static int	_str_to_color_tab(
	char *str,
	int (*color_tab)[3]
)
{
	char	**str_split;
	int		i;
	int		j;

	str_split = ft_split(str, ',');
	if (!str_split)
		return (RET_ERR);
	if (!str_split[0])
		return (ft_free_split(&str_split), RET_ERR);
	i = 0;
	while (i < 3 && str_split[i])
	{
		j = 0;
		while (str_split[i][j])
			if (!ft_isdigit(str_split[i][j++]))
				return (ft_free_split(&str_split), RET_ERR);
		(*color_tab)[i] = ft_atoi(str_split[i]);
		i++;
	}
	ft_free_split(&str_split);
	return (!(i == 3));
}

static int	_check_valid_rgb(
	int color_tab[3]
)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (color_tab[i] < 0 || color_tab[i] > 255)
			return (RET_ERR);
		i++;
	}
	return (RET_OK);
}
