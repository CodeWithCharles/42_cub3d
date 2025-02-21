/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:21:42 by cpoulain          #+#    #+#             */
/*   Updated: 2025/02/21 17:01:26 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <stdbool.h>
# include <X11/keysym.h>
# include <math.h>

# include "libft.h"
# include "mlx.h"
# include "error.h"
# include "colors.h"
# include "utils.h"

//	Constants

//		Returns and error codes

# define RET_OK						0
# define RET_ERR					1

//		Screen

# define WIDTH						1920
# define HEIGHT						1280

//		Textures

# define TEX_SIZE					64

//		File extensions

# define EXT_XPM					".xpm"
# define EXT_CUB					".cub"

//	Enums

//		Faces

typedef enum e_face
{
	FACE_NO,
	FACE_SO,
	FACE_WE,
	FACE_EA,
	FACE_F,
	FACE_C,
	FACE_D
}	t_face;

//		Element type

typedef enum e_elem
{
	ELEM_VOID,
	ELEM_WALL,
	ELEM_SPAWN,
	ELEM_DOOR
}	t_elem;

//		Door state

typedef enum e_door_state
{
	DOOR_STATE_CLOSED,
	DOOR_STATE_OPEN
}	t_door_state;

//		Door anim state

typedef enum e_door_anim_state
{
	DOOR_ANIM_NONE,
	DOOR_ANIM_OPENING,
	DOOR_ANIM_CLOSING
}	t_door_anim_state;

//	Structures

//		2D Vector

typedef struct s_2d_vector
{
	int	x;
	int	y;
}	t_2d_vector;

//		Texture context

typedef struct s_tex_ctx
{
	char			*north_path;
	char			*south_path;
	char			*west_path;
	char			*east_path;
	char			*floor;
	char			*ceiling;
	int				map_width;
	int				map_height;
}	t_tex_ctx;

//		Map element

typedef struct s_map_element
{
	t_2d_vector	pos;
	t_elem		type;
	void		*data;
	int			is_end;
}	t_map_element;

//		Image data

typedef struct s_img
{
	void	*img;
	int		*pixels_ptr;
	int		bits_per_pixel;
	int		endianess;
	int		line_len;
}	t_img;

//		Main context

typedef struct s_game_ctx
{
	void			*mlx;
	void			*window;
	int				*(game_textures[7]);
	char			*p_name;
	int				is_ceil_rgb;
	int				is_floor_rgb;
	t_map_element	**map;
}	t_game_ctx;

//		Door

typedef struct s_door
{
	t_door_state		is_closed;
	t_door_anim_state	anim_state;
}	t_door;

//	Functions

//		Errors

void	print_arg_error(
			t_game_ctx *ctx,
			const char *error,
			const char *arg);

void	print_gen_error(
			t_game_ctx *ctx,
			const char *error);

//		Texturing

int		parse_str_to_hex(
			t_game_ctx *ctx,
			void **str);

//		File validator

int		check_file(
			t_game_ctx *ctx,
			char *str,
			bool is_cub);

#endif
