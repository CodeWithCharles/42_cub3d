/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:21:42 by cpoulain          #+#    #+#             */
/*   Updated: 2025/03/17 17:34:04 by cpoulain         ###   ########.fr       */
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

//	Global variables

extern char	*g_pname;

//	Constants

//		Returns and error codes

# define RET_OK						0
# define RET_ERR					1

//		Screen

# define WIN_WIDTH					1920
# define WIN_HEIGHT					1080

//		Textures

# define TEX_SIZE					64

//		File extensions

# define EXT_XPM					".xpm"
# define EXT_CUB					".cub"

//		Directions

# define DIR_INIT_POSITIVE			1
# define DIR_INIT_NEGATIVE			-1

# define PLANE_INIT_POSITIVE_ANGLE	0.66
# define PLANE_INIT_NEGATIVE_ANGLE	-0.66

//		Raycasting

# ifndef RAYCASTING_RAY_COUNT
#  define RAYCASTING_RAY_COUNT		WIN_WIDTH
# endif

# define RAY_BOUND_MIN_OFFSET		0.25
# define RAY_BOUND_MAX_OFFSET		1.25

//		Movements
//			Pitch
# define MAX_PITCH	90
# define MIN_PITCH	-90
//			Mouse
# define MOUSE_EDGE_RESET_OFFSET	200
//				Rotation
# define MOUSE_ROT_SENSITIVITY		0.05
//				Pitch
# define MOUSE_PITCH_SENSITIVITY	4
//			Player
# define PLAYER_MOVE_SPEED			0.0725
# define PLAYER_MOVE				1
//				Pitch
# define PLAYER_PITCH_INCREMENT		10
//				Rotation
# define PLAYER_ROT_INCREMENT		1

//		Map elements

# define _WALL						'1'
# define _VOID						' '
# define _FLOOR						'0'
# define _PLAYER					'P'
# define _SPAWNS					"NSEW"
# define _DOORS						"HV"

//		Minimap

# define MMAP_PIXEL_SIZE			128
# define MMAP_VIEW_DIST				4
# define MMAP_BORDER_PADDING		5

//			Colors

# define MMAP_COLOR_WALL			0xFFFFFF
# define MMAP_COLOR_PLAYER			0x0000FF
# define MMAP_COLOR_FLOOR			0xCCCCCC
# define MMAP_COLOR_VOID			0x999999
# define MMAP_COLOR_SPAWN			0x00FF00
# define MMAP_COLOR_BORDER			0x222222

//	Enums

//		Faces

typedef enum e_face
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	FLOOR,
	CEILING,
	DOOR
}	t_face;

//		Element type

typedef enum e_elem
{
	ELEM_VOID,
	ELEM_WALL,
	ELEM_SPAWN_DIR_NORTH,
	ELEM_SPAWN_DIR_SOUTH,
	ELEM_SPAWN_DIR_WEST,
	ELEM_SPAWN_DIR_EAST,
	ELEM_FLOOR,
	ELEM_DOOR_H,
	ELEM_DOOR_V
}	t_elem;

//		Door anim state

typedef enum e_door_state
{
	DOOR_CLOSED,
	DOOR_OPENING,
	DOOR_CLOSING,
	DOOR_OPENED
}	t_door_state;

//	Structures

//		2D Vector

typedef struct s_2d_vector
{
	int	x;
	int	y;
}	t_2d_vector;

typedef struct s_2dd_vector
{
	double	x;
	double	y;
}	t_2dd_vector;

//		Player

typedef struct s_player
{
	t_elem			spawn_dir;
	t_2dd_vector	pos;
	t_2dd_vector	dir;
	t_2dd_vector	plane;
	int				has_moved;
	int				rotate;
	double			pitch;
	t_2d_vector		move;
}	t_player;

//		Raycasting

//			Texture computer

typedef struct s_tex_computer
{
	t_face			face;
	t_2d_vector		bound;
	double			pos;
	double			step;
}	t_tex_computer;

//			Ray

typedef struct s_ray
{
	double			cam_x;
	t_2dd_vector	dir;
	t_2d_vector		map;
	t_2d_vector		step;
	t_2dd_vector	side_dist;
	t_2dd_vector	delta_dist;
	double			wall_dist;
	double			wall_x;
	int				side;
	int				line_height;
	t_2d_vector		draw_boundaries;
	t_tex_computer	tex_cpt;
	struct s_door_helper
	{
		int				hit;
		t_elem			type;
		double			timer;
	}	door;
}	t_ray;

//		Texture context

typedef struct s_tex_ctx
{
	char			*north_path;
	char			*south_path;
	char			*west_path;
	char			*east_path;
	char			*floor;
	char			*ceiling;
	char			*door_path;
	bool			is_floor_rgb;
	bool			is_ceil_rgb;
}	t_tex_ctx;

//		Map element

typedef struct s_map_element
{
	t_2d_vector	pos;
	t_elem		type;
	void		*data;
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
	unsigned int	**game_textures;
	unsigned int	**screen_pixels;
	unsigned int	hex_floor;
	unsigned int	hex_ceiling;
	t_map_element	**map;
	t_map_element	*doors;
	unsigned int	m_width;
	unsigned int	m_height;
	t_player		player;
	t_ray			ray;
	t_img			minimap_img;
	int				has_mouse_jumped;
}	t_game_ctx;

//		Door

typedef struct s_door
{
	t_door_state		anim_state;
	double				timer;
}	t_door;

//		Minimap

typedef struct s_minimap
{
	char			**map;
	t_img			*img;
	unsigned int	size;
	t_2d_vector		offset;
	unsigned int	view_dist;
	unsigned int	tile_size;
}	t_minimap;

// bool parsing

typedef struct s_bool_format
{
	bool	map_found;
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

void		init_game(
				t_game_ctx *ctx);

void		refresh_screen_pixels(
				t_game_ctx *ctx);

void		init_mlx(
				t_game_ctx *ctx);

void		init_textures(
				t_game_ctx *ctx);

int			init_hex_texture(
				t_game_ctx *ctx,
				int index);

void		init_checker(
				t_bool_format *checker);

void		init_player_data(
				t_game_ctx *ctx,
				char **map);

void		init_player_dir(
				t_player *player);

void		init_img(
				t_game_ctx *ctx,
				t_img *img,
				int width,
				int height);

t_minimap	init_minimap(
				t_game_ctx *ctx);

//		Errors & Exits

void		print_arg_error(
				const char *error,
				const char *arg);

void		print_gen_error(
				const char *error);

void		clean_exit(
				t_game_ctx *game,
				char *error,
				int code);

int			quit_cube(
				t_game_ctx *ctx);

//		Texturing

int			parse_str_to_hex(
				t_game_ctx *ctx,
				unsigned int *var,
				char *str);

void		set_image_pixel(
				t_img *img,
				int x,
				int y,
				int color);

void		hex_to_texture(
				unsigned int **texture,
				unsigned int hex);

//		File validator

int			check_file(
				char *str,
				bool is_cub);

int			validate_files(
				t_game_ctx *ctx);

// check.c

bool		check_map_format(
				char **map);

int			is_good_format(
				char *filename);

//	fill_game_ctx.c

void		fill_game_ctx(
				char **map,
				t_game_ctx *ptr);

//	getter.c

t_2d_vector	find_start_pos(
				char **map);

void		get_map_size(
				t_game_ctx *game,
				char **map);

t_elem		get_elem_type(
				char pos);

// setter.c

char		*fill_buffer(
				char *filename);

void		set_bool_texture(
				char *line,
				t_bool_format *checker);

int			main_parsing(
				t_game_ctx *game,
				char **argv);

void		set_texture(
				t_tex_ctx *textures,
				char *line);

char		**dup_map(
				char **map);

void		set_map_elem_cur(
				t_map_element *curr,
				unsigned int i,
				unsigned int j,
				char curr_char);

// fill.c

void		flood_fill_parse(
				char **map,
				int x,
				int y,
				int *valid);

void		flood_fill_parse_door(
				char **map,
				int x,
				int y,
				int *valid);

void		fill_map_line(
				t_map_element *map_line,
				char *line,
				unsigned int m_width,
				unsigned int i);

void		fill_map(
				t_game_ctx *game,
				char **map);

//		Raycasting

int			raycasting(
				t_game_ctx *ctx);

void		init_ray_dir(
				t_ray *ray);

int			is_ray_in_bound(
				t_game_ctx *ctx,
				t_ray *ray);

//		Rendering

void		update_screen_pixel(
				t_game_ctx *ctx,
				t_ray *ray,
				int x);

void		render_screen(
				t_game_ctx *ctx);

int			render(
				t_game_ctx *ctx);

void		render_minimap(
				t_game_ctx *ctx);

//		Movements

int			rotate_player(
				t_game_ctx *ctx,
				double rot_dir);

int			validate_player_pos(
				t_game_ctx *ctx,
				t_2dd_vector new_pos);

int			move_player_handler(
				t_game_ctx *ctx);

//		Hooks

void		init_hooks(
				t_game_ctx *ctx);

int			mouse_move_hook(
				int x,
				int y,
				t_game_ctx *ctx);

int			key_pressed_hook(
				int key,
				t_game_ctx *ctx);

int			key_released_hook(
				int key,
				t_game_ctx *ctx);

void		fill_map(
				t_game_ctx *game,
				char **map);

void		set_map_elem_cur(
				t_map_element *curr,
				unsigned int i,
				unsigned int j,
				char curr_char);

char		*skip_space(
				char *line);

//		Minimap

//			Image

void		draw_mmap_borders(
				t_minimap *mmap);

void		draw_mmap(
				t_minimap *mmap);

void		draw_mmap_tile(
				t_minimap *mmap,
				unsigned int x,
				unsigned int y);

void		set_tile_pixels(
				t_minimap *mmap,
				unsigned int x,
				unsigned int y,
				unsigned int color);

//			Maker

int			get_mmap_offset(
				t_minimap *mmap,
				unsigned int map_size,
				unsigned int pos);

char		get_mmap_tile(
				t_game_ctx *ctx,
				t_minimap *mmap,
				unsigned int x,
				unsigned int y);

char		*generate_mmap_line(
				t_game_ctx *ctx,
				t_minimap *mmap,
				unsigned int y);

char		**generate_mmap(
				t_game_ctx *ctx,
				t_minimap *mmap);

#endif
