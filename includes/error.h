/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:06:01 by cpoulain          #+#    #+#             */
/*   Updated: 2025/03/26 16:04:29 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define INVALID_FD				-1
# define RET_OK					0
# define RET_ERR				1

# define CODE_CMD_NOT_FOUND			127
# define CODE_CMD_NOT_EXECUTABLE	126
# define CODE_CANNOT_ALLOC			12
# define CODE_EXEC_FAILED			256

# define ERR_ARGS				"%sError\n%s:\tUsage: ./cub3d <path/to/map.cub>"
# define ERR_INVALID_RGB_DATA	"%sError\n%s: Invalid rgb data.%s\n"
# define ERR_FATAL_ALLOC	"%sError\n%s:\t%s: Could not allocate memory.%s\n"
# define ERR_FILE_IS_DIR		"%sError\n%s:\t%s: File is a directory.%s\n"
# define ERR_NO_FILE	"%sError\n%s:\t%s\t: No such file or directory.%s\n"
# define ERR_ERRNO				"%sError\n%s:\t%s%s\n"
# define ERR_LOADING_XPM		"%sError\n%s:\tError loading xpm file.%s\n"
# define ERR_INIT_MLX			"%sError\n%s:\tCould not initialize mlx.%s\n"
# define ERR_WIN_MLX		"%sError\n%s:\tCould not initialize window.%s\n"
# define ERR_NO_SPAWN	"%sError:\n%s:\tPlayer spawn point not found.%s\n"
# define ERR_MORE_SPAWN	"%sError:\n%s:\tMultiple spawn points.%s\n"
# define ERR_MAP	"%sError:\n%s:\tInvalid map.%s\n"
# define ERR_CONFIG	"%sError:\n%s:\tInvalid configuration file.%s\n"
# define ERR_RGB	"%sError:\n%s:\t%s:\tInvalid rgb value.%s\n"
# define ERR_FILE_EMPTY	"%sError:\n%s:\tConfig File Empty.%s\n"

// Textures

# define ERR_MIS_NO	"%sError:\n%s:\tNO texture not found.%s\n"
# define ERR_MIS_SO	"%sError:\n%s:\tSO texture not found.%s\n"
# define ERR_MIS_EA	"%sError:\n%s:\tEA texture not found.%s\n"
# define ERR_MIS_WE	"%sError:\n%s:\tWE texture not found.%s\n"
# define ERR_MIS_F	"%sError:\n%s:\tF texture or color not found.%s\n"
# define ERR_MIS_C	"%sError:\n%s:\tC texture or color not found.%s\n"

#endif
