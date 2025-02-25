/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaliszc <mkaliszc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:21:42 by cpoulain          #+#    #+#             */
/*   Updated: 2025/02/25 15:56:30 by mkaliszc         ###   ########.fr       */
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

# define WIN_WIDTH					1920
# define WIN_HEIGHT					1280

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
	ELEM_FLOOR, // ? missing elem
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
	bool			is_floor_rgb;
	bool			is_ceil_rgb;
	int				map_width; // ? irregular map 
	int				map_height; // ? same 
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
	char			*p_name;
	void			*mlx;
	void			*window;
	t_tex_ctx		texctx;
	int				*game_textures[7];
	int				**screen_pixels;
	unsigned int	hex_floor;
	unsigned int	hex_ceiling;
	t_map_element	*map; // * replaced for a single pointer so to access pos map[cur].pos
}	t_game_ctx;

//		Door

typedef struct s_door
{
	t_door_state		is_closed;
	t_door_anim_state	anim_state;
}	t_door;

// bool parsing

typedef struct s_bool_format
{
	bool	all_texture_found;
	bool	wrong_param_found;
	bool	n_texture;
	bool	s_texture;
	bool	w_texture;
	bool	e_texture;
	bool	f_colors;
	bool	c_colors;
	bool	d_texture;
}	t_bool_format;

//	Functions

//		Inits

void	init_game(
			char *p_name,
			t_game_ctx *ctx);

void	refresh_screen_pixels(
			t_game_ctx *ctx);

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
			unsigned int *var,
			char *str);

//		File validator

int		check_file(
			t_game_ctx *ctx,
			char *str,
			bool is_cub);

// * parsing function

t_game_ctx	*main_parsing(
			int argc,
			char **argv);

// check.c

bool	check_map_format(
			char **map);

int		is_good_format(
			char *filename);

//	fill_game_ctx.c

void	fill_game_ctx(
			char **map,
			t_game_ctx **ptr);

//	getter.c

t_2d_vector	find_start_pos(
			char **map);

int	get_nbr_of_pos(
			char **map);

t_elem	get_elem_type(
			char pos);

// setter.c

void	init_checker(
			t_bool_format *checker);

char	*fill_buffer(
			char *filename);

void	set_bool_texture(
			char *line,
			t_bool_format *checker);

#endif
