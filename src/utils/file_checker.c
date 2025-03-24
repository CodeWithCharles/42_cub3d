/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:23:07 by cpoulain          #+#    #+#             */
/*   Updated: 2025/03/06 16:49:47 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Static prototypes

static int	_is_dir(
				char *str);

static int	_validate_extension(
				const char *str,
				const char *ext);

// Header implementations

int	check_file(
	char *str,
	bool is_cub
)
{
	int	fd;

	if (_is_dir(str))
		return (print_gen_error(ERR_FILE_IS_DIR), RET_ERR);
	fd = open(str, O_RDONLY);
	if (fd == INVALID_FD)
		return (print_arg_error(ERR_NO_FILE, str), RET_ERR);
	close(fd);
	if (is_cub && _validate_extension(str, EXT_CUB))
		return (RET_ERR);
	if (!is_cub && _validate_extension(str, EXT_XPM))
		return (RET_ERR);
	return (RET_OK);
}

// Static implementations

static int	_is_dir(
	char *str
)
{
	int		fd;
	int		ret;

	fd = open(str, __O_DIRECTORY);
	ret = (fd >= 0);
	if (fd >= 0)
		close (fd);
	return (ret);
}

static int	_validate_extension(
	const char *str,
	const char *ext
)
{
	size_t	str_len;
	size_t	ext_len;

	str_len = ft_strlen(str);
	ext_len = ft_strlen(ext);
	if (str_len < ext_len + 1 || ft_strcmp(str + (str_len - ext_len), ext))
		return (RET_ERR);
	return (RET_OK);
}
