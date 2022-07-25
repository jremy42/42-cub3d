/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sight_vector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 13:01:11 by fle-blay          #+#    #+#             */
/*   Updated: 2022/07/25 13:10:19 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "keycodes.h"
#include "math.h"

static void	update_hit_vector_attributes(t_cub *cub)
{
	if (cub->player.dir_x > 0)
		cub->hit_vector.step_x = 1;
	else
		cub->hit_vector.step_x = -1;
	if (cub->player.dir_y > 0)
		cub->hit_vector.step_y = 1;
	else
		cub->hit_vector.step_y = -1;
	cub->hit_vector.side_dist_x = cub->player.delta_dist_x;
	cub->hit_vector.side_dist_y = cub->player.delta_dist_y;
	cub->hit_vector.coord_x = 0;
	cub->hit_vector.coord_y = 0;
	cub->hit_vector.hit = 0;
	__memset(cub->player.vector, 0, sizeof(cub->player.vector));
	cub->player.vector[4][4] = 42;
}

static void	go_to_next_closest_line_or_column(t_cub *cub)
{
	if (cub->hit_vector.side_dist_x < cub->hit_vector.side_dist_y)
	{
		cub->hit_vector.coord_x += cub->hit_vector.step_x;
		cub->hit_vector.side_dist_x += cub->player.delta_dist_x;
		cub->hit_vector.side = -1;
	}
	else
	{
		cub->hit_vector.coord_y += cub->hit_vector.step_y;
		cub->hit_vector.side_dist_y += cub->player.delta_dist_y;
		cub->hit_vector.side = 1;
	}
}

static int	calculate_sight_vector_hit(t_cub *cub)
{
	update_hit_vector_attributes(cub);
	while (1)
	{
		go_to_next_closest_line_or_column(cub);
		cub->hit_vector.tab_coord_x = (int)floor(cub->hit_vector.coord_x);
		cub->hit_vector.tab_coord_y = (int)floor(cub->hit_vector.coord_y);
		if (cub->hit_vector.tab_coord_x > 4
			|| cub->hit_vector.tab_coord_y > 4
			|| cub->hit_vector.tab_coord_x < -4
			|| cub->hit_vector.tab_coord_y < -4)
			break ;
		cub->player.vector[cub->hit_vector.tab_coord_y + 4]
		[cub->hit_vector.tab_coord_x + 4]
			= (cub->hit_vector.hit + 1) * cub->hit_vector.side;
		cub->hit_vector.hit++;
	}
	return (1);
}


int	print_sight_vector(t_cub *cub)
{
	int	i;
	int	j;

	calculate_sight_vector_hit(cub);
	i = 0;
	while (i < 9)
	{
		j = 0;
		while (j < 9)
		{
			if (cub->player.vector[i][j] == 42)
				printf("\e[34m0 \e[0m");
			else if (cub->player.vector[i][j] > 0)
				printf("\e[32m%d \e[0m", abs(cub->player.vector[i][j]));
			else if (cub->player.vector[i][j] < 0)
				printf("\e[33m%d \e[0m", abs(cub->player.vector[i][j]));
			else
				printf("0 ");
			j++;
		}
		printf("\n");
		i++;
	}
	return (printf("\n"));
}
