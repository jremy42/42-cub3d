/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <{fle-blay}@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 10:21:44 by fle-blay          #+#    #+#             */
/*   Updated: 2022/06/30 10:22:11 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# define NO_FD -1

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

void parsing(char **av, t_cub *cub);

#endif
