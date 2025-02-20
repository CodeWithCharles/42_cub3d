/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:06:01 by cpoulain          #+#    #+#             */
/*   Updated: 2025/02/20 17:07:20 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define RET_OK					0
# define RET_ERR				1

# define CODE_CMD_NOT_FOUND			127
# define CODE_CMD_NOT_EXECUTABLE	126
# define CODE_CANNOT_ALLOC			12
# define CODE_EXEC_FAILED			256

# define ERR_INVALID_RGB_DATA		"%s%s:\t%s\t: Invalid rgb data.%s\n"

#endif
