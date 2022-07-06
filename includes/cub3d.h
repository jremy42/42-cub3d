/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jremy <jremy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 10:21:44 by fle-blay          #+#    #+#             */
/*   Updated: 2022/07/06 13:57:21 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft.h"

# ifndef DEBUG
#  define DEBUG 0
# endif
# define UP 0
# define DOWN 1
# define LEFT 2
# define RIGHT 3
# define WIDTH 640
# define HEIGHT 480
# define SPEED 0.5f
# define SIZE_MINI_MAP 8
# define SIZE_PLAYER 8
# define ROTATE_ANGLE M_PI/32

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

#endif
