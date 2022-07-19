/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deus <deus@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 10:21:44 by fle-blay          #+#    #+#             */
/*   Updated: 2022/07/19 12:19:40 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft.h"
# define DEBUG 1
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
# define SPEED 0.05f
# define SIZE_MINI_MAP 16
# define SIZE_PLAYER 8
# define ROTATE_ANGLE M_PI/32
# define FOV 0.9f
# define X_HIT 1
# define Y_HIT 2
# define X_HIT_COLOR 0xEA6A36
# define Y_HIT_COLOR 0xf08c25
# define MINIMAP_WALL_COLOR 0xFFFFFF
# define MINIMAP_DOOR_COLOR 0x7a7a7a
# define MINIMAP_PLAYER_COLOR 0x7e0b80
# define MINIMAP_EMPTY_COLOR 0x212e26
# define MINIMAP_GROUND_COLOR 0xe6e6e6
# define FPS 60
# define SIZE_WEAPON 3

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
 	//float	dir_norm;
	float	slope_dir;
	float	delta_dist_x;
	float	delta_dist_y;
	float	plane_x;
	float	plane_y;
	float	plane_norm;
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
	int		perp_wall_dist[WIDTH];

	int		sprite; // A RENOMMER -> CONFUSION !!!!!!!!!!
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

typedef struct s_sprite
{
	float	norm;
	float	pos_x;
	float	pos_y;
	float	cam_pos_x;
	float	cam_pos_y;
	float	plane_proj;
	float	dir_proj;
	int		screen_x;
	int		screen_height;
	int		screen_width;
	int		to_show;
	t_img	sprite_img;
	int		do_not_display;
	int		offset_y;
	int		screen_x_start;
	int		screen_x_end;
	int		screen_y_start;
	int		screen_y_end;
	int		gun_hit;
}	t_sprite;


typedef struct s_cub
{
	void		*text[4];
	void		*door;
	void		*gun;
	t_img		door_img;
	t_img		gun_img[5];
	int			gun_current_sprite;
	int			gun_animate;
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
	int			minimap_height;
	int			minimap_width;
	t_sprite	sprite1;
	t_sprite	*sprite_tab;
	int			last_key_press;
	int			sprite_count;
	int			*sprite_order;
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
int		render_frame(t_cub *cub);
int __mouse_move(t_cub *cub);
void	load_background(t_cub *cub);
void	__update_door_value(t_cub *cub);

void	__hookleft(t_cub *cub);
void	__hookright(t_cub *cub);
void	__hookdown(t_cub *cub);
void	__hookup(t_cub *cub);
void	__switch_door(t_cub *cub);
int		__key_release(int keycode, t_cub *cub);
void	update_minimap(t_cub *cub);
int	print_coord_hit(t_cub *cub);
int	print_vector(t_cub *cub);

// SPRITE AND VECTOR MATH
void	calculate_sprite_info(t_cub *cub, t_sprite *sprite);
int		get_color_from_text(float step, float r_hit_coef, t_img *img, t_cub *cub);
float	vector_det(float u_x, float u_y, float v_x, float v_y);
float	vector_dot(float u_x, float u_y, float v_x, float v_y);
int		print_sprite_info(t_sprite *sprite);
void 	draw_sprite(t_cub *cub, t_sprite *s);
void	update_sprite_order(t_cub *cub, t_sprite *s_tab, int s_count, int *s_order);

#endif
