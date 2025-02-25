/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:06:01 by cpoulain          #+#    #+#             */
/*   Updated: 2025/02/25 14:54:39 by cpoulain         ###   ########.fr       */
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

# define ERR_ARGS					"%s%s:\tUsage: ./cub3d <path/to/map.cub>"
# define ERR_INVALID_RGB_DATA		"%s%s:\t%s: Invalid rgb data.%s\n"
# define ERR_FATAL_ALLOC			"%s%s:\t%s: Could not allocate memory.%s\n"
# define ERR_FILE_IS_DIR			"%s%s:\t%s: File is a directory.%s\n"
# define ERR_ERRNO					"%s%s:\t: %s%s\n"
# define ERR_LOADING_XPM			"%s%s:\t: Error loading xpm file.%s\n"

#endif
