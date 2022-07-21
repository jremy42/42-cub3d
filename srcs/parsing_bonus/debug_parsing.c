/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jremy <jremy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 09:46:35 by jremy             #+#    #+#             */
/*   Updated: 2022/07/21 12:08:37 by jremy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "colors.h"
#include <unistd.h>
#include <stdio.h>
#include <libft.h>

void	clear_screen(void)
{
	__putstr_fd("\x1b[2J", 1);
	__putstr_fd("\x1b[1;1H", 1);
}

int	print_debug_info(t_cub *cub)
{
	t_player	*p;

	p = &cub->player;
	printf("pos_x/pos_y: (%f:%f)\n", p->pos_x, p->pos_y);
	printf("dir_x/dir_y: (%f:%f)\n", p->dir_x, p->dir_y);
	printf("plane_x/plane_y: (%f:%f)\n", p->plane_x, p->plane_y);
	printf("pente y/x : (%f)\n", p->slope_dir);
	printf("delta_dist_x/delta_dist_y: (%f:%f)\n",
		p->delta_dist_x, p->delta_dist_y);
	return (1);
}

int	print_cub(t_cub *cub)
{
	int	i;

	i = -1;
	while (++i < 4)
		printf("text[%d] %s\n", i, (char *)cub->text[i]);
	i = -1;
	while (++i < 2)
		printf("color[%d] %s\n", i, (char *)cub->color[i]);
	printf("Color ceiling r:[%d] g:[%d] b:[%d]\n", cub->ceiling.r,
		cub->ceiling.g, cub->ceiling.b);
	printf("Color floor r:[%d] g:[%d] b:[%d]\n",
		cub->floor.r, cub->floor.g, cub->floor.b);
	printf("Player start status : [%c] @ (%f:%f)\n",
		cub->player.start_orientation,
		cub->player.pos_x, cub->player.pos_y);
	print_maps(cub);
	return (1);
}

int	print_maps(t_cub *cub)
{
	int	i;

	i = 0;
	while (cub->maps[i])
		printf("%s\n", cub->maps[i++]);
	return (1);
}

int	print_maps_error(t_cub *cub, int error_i, int error_j)
{
	int	i;
	int	j;

	i = 0;
	while (cub->maps[i])
	{
		j = 0;
		while (cub->maps[i][j])
		{
			if (j == error_j && i == error_i)
			{
				__putstr_fd(BACK_RED, 2);
				__putchar_fd(cub->maps[i][j], 2);
				__putstr_fd(RESET, 2);
			}
			else
				__putchar_fd(cub->maps[i][j], 2);
			j++;
		}
		__putstr_fd("\n", 2);
		i++;
	}
	__putstr_fd("\n", 2);
	return (1);
}
