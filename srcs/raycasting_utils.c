/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 12:39:21 by fle-blay          #+#    #+#             */
/*   Updated: 2022/07/25 12:55:16 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "math.h"
#include "colors.h"

void	update_cos_of_r_dir_and_dir(t_player *p)
{
	float	r_dir_dot_dir;
	float	r_dir_norm;
	float	dir_norm;

	r_dir_dot_dir = vector_dot(p->r_dir_x, p->r_dir_y,
			p->dir_x, p->dir_y);
	r_dir_norm = sqrt(p->r_dir_x * p->r_dir_x + p->r_dir_y * p->r_dir_y);
	dir_norm = sqrt(p->dir_x * p->dir_x + p->dir_y * p->dir_y);
	p->cos_alpha = r_dir_dot_dir / (r_dir_norm * dir_norm);
}

void	calculate_ray_features(t_player *player, int x)
{
	player->cam_x = (2 * x / (float)WIDTH) - 1;
	player->r_dir_x = player->dir_x + player->plane_x * player->cam_x;
	player->r_dir_y = player->dir_y + player->plane_y * player->cam_x;
	player->r_slope_dir = player->r_dir_y / player->r_dir_x;
	player->r_delta_dist_x = sqrt(1 + pow(player->r_slope_dir, 2));
	player->r_delta_dist_y = sqrt(1 + pow(1 / player->r_slope_dir, 2));
}

int	print_ray_info(t_cub *cub)
{
	printf("cam_x coeff : %f\n", cub->player.cam_x);
	printf("r_dir_x/r_dir_y : %f:%f\n", cub->player.r_dir_x,
		cub->player.r_dir_y);
	printf("r_slope : %f\n", cub->player.r_slope_dir);
	printf("r_delta_dist_x/r_delta_dist_y : %f:%f\n", cub->player.r_delta_dist_x,
		cub->player.r_delta_dist_y);
	return (1);
}
