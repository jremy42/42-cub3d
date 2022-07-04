/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jremy <jremy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 10:21:44 by fle-blay          #+#    #+#             */
/*   Updated: 2022/07/04 13:19:22 by jremy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft.h"
# define DEBUG 0
# define RESET   "\033[0m"

# define BLACK   "\033[30m"      /* Black */
# define RED     "\033[31m"      /* Red */
# define GREEN   "\033[32m"      /* Green */
# define YELLOW  "\033[33m"      /* Yellow */
# define BLUE    "\033[34m"      /* Blue */
# define MAGENTA "\033[35m"      /* Magenta */
# define CYAN    "\033[36m"      /* Cyan */
# define WHITE   "\033[37m"      /* White */

# define BACK_BLACK   "\033[40m"      /* Black */
# define BACK_RED     "\033[41m"      /* Red */
# define BACK_GREEN   "\033[42m"      /* Green */
# define BACK_YELLOW  "\033[43m"      /* Yellow */
# define BACK_BLUE    "\033[44m"      /* Blue */
# define BACK_MAGENTA "\033[45m"      /* Magenta */
# define BACK_CYAN    "\033[46m"      /* Cyan */
# define BACK_WHITE   "\033[47m"      /* White */

# define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
# define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
# define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
# define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
# define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
# define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
# define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
# define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

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
	char	dir;
	int		i;
	int		j;
}	t_player;
typedef struct s_cub
{
	void		*text[4];
	void		*color[2];
	char		**maps;
	t_player	player;
	t_list		*input;
}	t_cub;

void	parsing(char **av, t_cub *cub);
int		check_wall(char **maps, int i, int j, int nb_l);
int		load_maps(t_list *input, t_cub *cub);
int		check_maps(t_cub *cub);

//DEBUG PARSING 
int	print_cub(t_cub *cub);
void	printer(void *content);
int		print_maps(t_cub *cub);
int	print_maps_error(t_cub *cub, int error_j, int error_i);
void	destroy_cub_data(t_cub *cub);


void	__exit_error_get_input(char *error, t_list *lst, int fd);
void	__exit_error(char *error, t_cub *cub);
#endif
