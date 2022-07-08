/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deus <deus@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 10:21:44 by fle-blay          #+#    #+#             */
/*   Updated: 2022/07/08 11:39:24 by deus             ###   ########.fr       */
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
# define UP 0
# define DOWN 1
# define LEFT 2
# define RIGHT 3
# define WIDTH 1280
# define HEIGHT 720
# define SPEED 0.5f
# define SIZE_MINI_MAP 16
# define SIZE_PLAYER 16
# define ROTATE_ANGLE M_PI/32
# define FOV 0.9f
# define X_HIT 1
# define Y_HIT 2
# define X_HIT_COLOR 0xEA6A36
# define Y_HIT_COLOR 0xf08c25 

enum {
	NO,
	SO,
	EA,
	WE
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
}				t_img;


typedef struct s_cub
{
	void		*text[4];
	void		*color[2];
	t_color		ceiling;
	t_color		floor;
	char		**maps;
	t_player	player;
	t_list		*input;
	void		*mlx;
	void		*win;
	t_img		screen;
	t_img		minimap;
	t_img		backgd;
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
#endif
