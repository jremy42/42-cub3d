/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jremy <jremy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 13:56:26 by fle-blay          #+#    #+#             */
/*   Updated: 2022/07/25 13:14:06 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "keycodes.h"
#include "math.h"

void	update_slope(t_cub *cub)
{
	cub->player.slope_dir = cub->player.dir_y / cub->player.dir_x;
	cub->player.delta_dist_x = sqrt(1 + pow(cub->player.slope_dir, 2));
	cub->player.delta_dist_y = sqrt(1 + pow(1 / cub->player.slope_dir, 2));
}

void	rotate(t_cub *cub, float angle)
{
	float	old_dir_x;
	float	old_dir_y;
	float	old_plane_x;
	float	old_plane_y;

	old_dir_x = cub->player.dir_x;
	old_dir_y = cub->player.dir_y;
	old_plane_x = cub->player.plane_x;
	old_plane_y = cub->player.plane_y;
	cub->player.dir_x = old_dir_x * cos(angle)
		- old_dir_y * sin(angle);
	cub->player.dir_y = old_dir_x * sin(angle)
		+ old_dir_y * cos(angle);
	cub->player.plane_x = old_plane_x * cos(angle)
		- old_plane_y * sin(angle);
	cub->player.plane_y = old_plane_x * sin(angle)
		+ old_plane_y * cos(angle);
	cub->player.plane_norm = sqrt(pow(cub->player.plane_x, 2)
			+ pow(cub->player.plane_y, 2));
}

void	__hookleft(t_cub *cub)
{
	__move(cub, -cub->player.plane_x, -cub->player.plane_y);
	(DEBUG == 2) && printf("left\n");
}

void	__hookright(t_cub *cub)
{
	__move(cub, cub->player.plane_x, cub->player.plane_y);
	(DEBUG == 2) && printf("right\n");
}

void	__hookdown(t_cub *cub)
{
	__move(cub, -cub->player.dir_x, -cub->player.dir_y);
	(DEBUG == 2) && printf("down\n");
}

void	__hookup(t_cub *cub)
{
	__move(cub, cub->player.dir_x, cub->player.dir_y);
	(DEBUG == 2) && printf("up\n");
}

void	load_background(t_cub *cub)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				my_mlx_pixel_put(&cub->screen, x, y, cub->ceiling.trgb);
			else
				my_mlx_pixel_put(&cub->screen, x, y, cub->floor.trgb);
			x++;
		}
		y++;
	}
}
