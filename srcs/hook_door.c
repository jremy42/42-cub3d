/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_door.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 13:11:10 by fle-blay          #+#    #+#             */
/*   Updated: 2022/07/25 13:11:31 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "keycodes.h"
#include "math.h"

void	__switch_door(t_cub *cub)
{
	int	x_try;
	int	y_try;
	int	i;
	int	j;

	x_try = floor(cub->player.pos_x);
	y_try = floor(cub->player.pos_y);
	i = -2;
	while (++i < 2)
	{
		j = -2;
		while (++j < 2)
		{
			if (!i && !j)
				continue ;
			if (cub->maps[y_try + i][x_try + j] == 'D'
				&& cub->door_map[y_try + i][x_try + j] == 2.0f)
				cub->door_map[y_try + i][x_try + j] = 1.99f;
			if (cub->maps[y_try + i][x_try + j] == 'D'
				&& cub->door_map[y_try + i][x_try + j] == 0.0f)
				cub->door_map[y_try + i][x_try + j] = 0.01f;
		}
	}
	DEBUG && printf("open\n");
}

void	__update_door_value(t_cub *cub)
{
	int	x;
	int	y;

	y = -1;
	while (cub->maps[++y])
	{
		x = -1;
		while (cub->maps[y][++x])
		{
			if (cub->maps[y][x] == 'D' && cub->door_map[y][x] < 2.0f
				&& cub->door_map[y][x] >= 1.0f)
			{
				cub->door_map[y][x] -= 0.02f;
				if (cub->door_map[y][x] < 1.0f)
					cub->door_map[y][x] = 0.0f;
			}
			if (cub->maps[y][x] == 'D' && cub->door_map[y][x] <= 1.0f
				&& cub->door_map[y][x] > 0.0f)
			{
				cub->door_map[y][x] += 0.02f;
				if (cub->door_map[y][x] > 1.0f)
					cub->door_map[y][x] = 2.0f;
			}
		}
	}
}

