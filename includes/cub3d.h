/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jremy <jremy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 10:21:44 by fle-blay          #+#    #+#             */
/*   Updated: 2022/07/25 15:50:48 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sprites.h"

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
# define ROTATE_ANGLE M_PI / 32
# define FOV 0.9f
# define X_HIT 1
# define Y_HIT 2
# define MINIMAP_WC 0xFFFFFF
# define MINIMAP_DC 0x7a7a7a
# define MINIMAP_PC 0x7e0b80
# define MINIMAP_EC 0x212e26
# define MINIMAP_GC 0xe6e6e6
# define FPS 60
# define VIEW_MM 1.0f / SIZE_MINI_MAP
# define GUN_SIZE 3
# define RED_HEX 0x00ff0000
# define YELLOW_HEX 0x00777700
# define G_DETECT_DIST 10
# define MOUSE_HIDE 1

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
	// form int to float
	float	perp_wall_dist[WIDTH];
	// check if needed;
	//float	true_wall_dist[WIDTH];
	int		current_orientation;
	int		current_text; // A RENOMMER -> CONFUSION !!!!!!!!!!
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
	//old
	//t_img	sprite_img;
	//NEW
	t_img	(*sprite_img_tab)[];
	int		current_frame;
	int		animate;
	int		count_animate;
	//NEW
	//int		do_not_display;
	int		offset_y;
	int		screen_x_start;
	int		screen_x_end;
	int		screen_y_start;
	int		screen_y_end;
	int		gun_hit;
}	t_sprite;

typedef struct	s_vector
{
	int		hit;
	float	side_dist_x;
	float	side_dist_y;
	float	coord_x;
	float	coord_y;
	int		tab_coord_x;
	int		tab_coord_y;
	int		step_y;
	int		step_x;
	int		side;
}	t_vector;

typedef struct s_cub
{
	void		*text[4][6];
	void		*door;
	void		*gun;
	t_img		door_img;
	char		*gun_img_file[GUN_SPRITE_COUNT];
	t_img		gun_img[GUN_SPRITE_COUNT];

	//NEW
	char		*guard_img_file[GUARD_SPRITE_COUNT];
	t_img		guard_img[GUARD_SPRITE_COUNT];
	//NEW
	int			gun_frame;
	int			gun_animate;
	int			nb_l_maps;
	void		*color[2];
	t_color		ceiling;
	t_color		floor;
	char		**maps;
	float		**door_map;
	int			size_door_map;
	t_player	player;
	t_list		*input;
	void		*mlx;
	void		*win;
	t_img		screen;
	t_img		backgd;
	t_img		text_img[4][6];
	void		(*hook_fx[5])();
	int			action;
	int			minimap_height;
	int			minimap_width;
	t_sprite	*sprite_tab;
	int			last_key_press;
	int			sprite_count;
	int			*sprite_order;
	int			hit_by_guard;
	t_vector	hit_vector;
}	t_cub;

void	parsing(char **av, t_cub *cub);
int		check_wall(char **maps, int i, int j, int nb_l);
int		load_maps(t_list *input, t_cub *cub);
int		check_maps(t_cub *cub);
t_list	*adjust_input(t_list *input);
int		maps_size(char **maps);
int		check_player(t_cub *cub, int i, int j, int nb_l);
void	load_player_info(t_cub *cub);
int		load_info(char **ret, t_cub *cub);
int		load_texture_path(void *text[6], char **ret);
int		get_pos(char **ret);
int		missing_info_cub(t_cub *cub);
void	__exit_error(char *error, t_cub *cub);
void	__exit_error_get_input(char *error, t_list *lst, int fd);
void	destroy_cub_data(t_cub *cub);

int	__mouse_hook(int button, int x, int y, t_cub *cub);
int	__mouse_move(t_cub *cub);
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
void	update_minimap(t_cub *cub);

void	update_minimap(t_cub *cub);
size_t	__get_time(void);
int		render_frame(t_cub *cub);
void	__update_door_value(t_cub *cub);

void	__hookleft(t_cub *cub);
void	__hookright(t_cub *cub);
void	__hookdown(t_cub *cub);
void	__hookup(t_cub *cub);
void	__switch_door(t_cub *cub);
int		__key_release(int keycode, t_cub *cub);
void	update_minimap(t_cub *cub);
int		print_coord_hit(t_cub *cub);
int		print_vector(t_cub *cub);

// SPRITE AND VECTOR MATH
int		get_color_from_text(int y_in_text, float r_hit_coef, t_img *img, t_cub *cub);
float	vector_det(float u_x, float u_y, float v_x, float v_y);
float	vector_dot(float u_x, float u_y, float v_x, float v_y);
int		print_sprite_info(t_sprite *sprite);
void 	draw_sprite(t_cub *cub, t_sprite *s);
void	update_sprite_order(t_sprite *s_tab, int s_count, int *s_order);
void	get_info(t_list *input, t_cub *cub);
void	load_player_info(t_cub *cub);
int		get_color_from_mlx_img(int x, int y, t_img *img);
int		load_images(t_cub *cub);
int		print_sprite_info(t_sprite *sprite);
void	get_sprite_frame(t_sprite *sprite);
float	vector_det(float u_x, float u_y, float v_x, float v_y);
float	vector_dot(float u_x, float u_y, float v_x, float v_y);
void	handle_sprite(t_cub *cub);



									 //SORTED




// MLX UTILS
int	get_color_from_mlx_img(int x, int y, t_img *img);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
int	get_color_from_text(int y_in_text, float r_hit_coef, t_img *img, t_cub *cub);

// exit

int		__quit(t_cub *cub);
void	destroy_mlx_data(t_cub *cub);
void	destroy_cub_text(t_cub *cub);


//MINIMAP
void	update_minimap(t_cub *cub);

//INIT

void	set_ressources_file_names(t_cub *cub);
void	set_hook_fx(t_cub *cub);
int		init_game(t_cub *cub);

// DDA

int	dda(t_player *player, char **map, float **door_map);

// COLORS
int	dim_color(int *color_ptr);

// RAYCASTING UTILS
void	update_cos_of_r_dir_and_dir(t_player *p);
void	calculate_ray_features(t_player *player, int x);
int		print_ray_info(t_cub *cub);

// RAYCAST
int		raycast(t_cub *cub);

//HOOK MOVE
void	__move(t_cub *cub, float move_dir_x, float move_dir_y);

// SIGHT_VECTOR
int	print_sight_vector(t_cub *cub);

//HOOK DOOR
void	__switch_door(t_cub *cub);
void	__update_door_value(t_cub *cub);

// HOOK KEY ACTION

int	__key_release(int keycode, t_cub *cub);
int	__key_press(int keycode, t_cub *cub);

// HOOK DIRECTION

void	__hookleft(t_cub *cub);
void	__hookright(t_cub *cub);
void	__hookdown(t_cub *cub);
void	__hookup(t_cub *cub);

//HANDLE MOUSE
void	rotate(t_cub *cub, float angle);
int	__mouse_hook(int button, int x, int y, t_cub *cub);
int	__mouse_move(t_cub *cub);


//GUN
void	draw_target(t_cub *cub);
void	draw_gun(t_cub *cub);
void	colorize_screen(t_cub *cub);

//GAME
int	render_frame(t_cub *c);

//CREATE IMG
int	create_image(t_cub *cub, t_img *img, int width, int height);
int	create_cub_images(t_cub *cub);

//DRAW SPRITE
void	draw_sprite(t_cub *cub, t_sprite *s);

//LOAD TEXTURES
int	load_images(t_cub *cub);

//QUIT
int	__quit(t_cub *cub);
void	destroy_cub_sprite(t_cub *cub);
void	destroy_cub_text(t_cub *cub);
void	destroy_mlx_data(t_cub *cub);

//SPRITE
void	calculate_all_sprite_info(t_cub *cub);
void	handle_sprite(t_cub *cub);

//SPRITE UTILS
float	vector_det(float u_x, float u_y, float v_x, float v_y);
float	vector_dot(float u_x, float u_y, float v_x, float v_y);
int	print_sprite_info(t_sprite *sprite);
void	get_sprite_frame(t_sprite *sprite);

//TIME
size_t	__get_time(void);

#endif
