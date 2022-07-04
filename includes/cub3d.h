/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jremy <jremy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 10:21:44 by fle-blay          #+#    #+#             */
/*   Updated: 2022/07/04 10:12:11 by jremy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft.h"
# define NO_FD -1
# define DEBUG 0

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

typedef struct s_cub
{
	void	*text[4];
	void	*color[2];
	char	**maps;
}	t_cub;

void	parsing(char **av, t_cub *cub);
int		check_wall(char **maps, int i, int j, int size_c);
int		load_maps(t_list *input, t_cub *cub);
int		check_maps(t_cub *cub);

//DEBUG PARSING 
int	print_cub(t_cub *cub);
void	printer(void *content);
int		print_maps(t_cub *cub);

#endif
