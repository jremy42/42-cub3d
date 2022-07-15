/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jremy <jremy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 10:21:44 by fle-blay          #+#    #+#             */
/*   Updated: 2022/07/15 16:01:11 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft.h"
# define DEBUG 2
# ifndef DEBUG
#  define DEBUG 0
# endif
# define BONUS 1
# define UP 3
# define DOWN 1
# define LEFT 0
# define RIGHT 2
# define OPEN_DOOR 4
# define WIDTH 1280
# define HEIGHT 720
# define SPEED 0.1f
# define SIZE_MINI_MAP 16
# define SIZE_PLAYER 16
# define ROTATE_ANGLE M_PI/32
# define FOV 0.9f
# define X_HIT 1
# define Y_HIT 2
# define X_HIT_COLOR 0xEA6A36
# define Y_HIT_COLOR 0xf08c25
# define FPS 60

enum {
	NO,
	SO,
	EA,
	WE,
	DO
};

enum {
	F,
	C
};

typedef struct s_player
{
	char	start_orientation;
	float	dir_x;
	float	dir_y;
	float	slope_dir;
	float	delta_dist_x;
	float	delta_dist_y;
	float	plane_x;
	float	plane_y;
	float	pos_x;
	float	pos_y;
	int		vector[9][9];

	float	r_dir_x;
	float	r_dir_y;
	float	r_slope_dir;
	float	r_delta_dist_x;
	float	r_delta_dist_y;
	float	r_step_x;
	float	r_step_y;
	float	r_side_dist_x;
	float	r_side_dist_y;
	float	cam_x;
	int		r_map_x;
	int		r_map_y;
	float	r_side_hit;
	int		r_wall_y_start;
	int		r_wall_y_end;
	float	cos_alpha;
	float	fov;
	//texture
	float	r_hit_x;
	float	r_hit_y;
	float	r_hit_coef;
	int		wall_height;
	int		perp_wall_dist;
	int		sprite;

}	t_player;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	t;
	int	trgb;
}	t_color;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		height;
	int		width;
}				t_img;


typedef struct s_cub
{
	void		*text[4];
	void		*door;
	t_img		door_img;
	void		*color[2];
	t_color		ceiling;
	t_color		floor;
	char		**maps;
	float		**door_map;
	t_player	player;
	t_list		*input;
	void		*mlx;
	void		*win;
	t_img		screen;
	t_img		minimap;
	t_img		backgd;
	t_img		text_img[4];
	void		(*hook_fx[5])();
	int			action;
}	t_cub;

void	parsing(char **av, t_cub *cub);
int		check_wall(char **maps, int i, int j, int nb_l);
int		load_maps(t_list *input, t_cub *cub);
int		check_maps(t_cub *cub);

//DEBUG PARSING 
void	clear_screen(void);
int		print_debug_info(t_cub *cub);
int		print_cub(t_cub *cub);
void	printer(void *content);
int		print_maps(t_cub *cub);
int		print_maps_error(t_cub *cub, int error_j, int error_i);
void	destroy_cub_data(t_cub *cub);

void	__exit_error_get_input(char *error, t_list *lst, int fd);
void	__exit_error(char *error, t_cub *cub);

int		check_color(t_cub *cub);
int		__key_press(int keycode, t_cub *cub);

int		create_cub_images(t_cub *cub);
int		game(t_cub *cub);
int		__quit(t_cub *cub);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
int raycast(t_cub *cub);
void	update_minimap(t_cub *cub);
int	load_textures(t_cub *cub);

void	rotate(t_cub *cub, float angle);
void	update_minimap(t_cub *cub);
void	update_slope(t_cub *cub);
size_t	__get_time(void);
int	render_frame(t_cub *cub);
int __mouse_move(t_cub *cub);
void	load_background(t_cub *cub);
void	__update_door_value(t_cub *cub);

void	__hookleft(t_cub *cub);
void	__hookright(t_cub *cub);
void	__hookdown(t_cub *cub);
void	__hookup(t_cub *cub);
void	__switch_door(t_cub *cub);
int	__key_release(int keycode, t_cub *cub);
#endif
