/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deus <deus@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:39:06 by fle-blay          #+#    #+#             */
/*   Updated: 2022/07/26 18:02:59 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "math.h"
#include "colors.h"

static void	init_step_and_side_dist(t_player *p)
{
	p->r_map_x = (int)floor(p->pos_x);
	p->r_map_y = (int)floor(p->pos_y);
	if (p->r_dir_x < 0)
	{
		p->r_step_x = -1;
		p->r_side_dist_x = (p->pos_x - p->r_map_x) * p->r_delta_dist_x;
	}
	else
	{
		p->r_step_x = 1;
		p->r_side_dist_x = (p->r_map_x + 1 - p->pos_x) * p->r_delta_dist_x;
	}
	if (p->r_dir_y < 0)
	{
		p->r_step_y = -1;
		p->r_side_dist_y = (p->pos_y - p->r_map_y) * p->r_delta_dist_y;
	}
	else
	{
		p->r_step_y = 1;
		p->r_side_dist_y = (p->r_map_y + 1 - p->pos_y) * p->r_delta_dist_y;
	}
}

static void	calculate_wall_height(t_player *player, int x)
{
	int		wall_height;
	float	perp_wall_dist;
	float	true_wall_dist;

	if (player->r_side_hit == X_HIT)
		true_wall_dist = (player->r_side_dist_x - player->r_delta_dist_x);
	else
		true_wall_dist = (player->r_side_dist_y - player->r_delta_dist_y);
	perp_wall_dist = true_wall_dist * player->cos_alpha;
	player->perp_wall_dist[x] = perp_wall_dist;
	wall_height = HEIGHT / perp_wall_dist;
	player->wall_height = wall_height;
	player->r_wall_y_start = (HEIGHT / 2) - (wall_height / 2);
	player->r_wall_y_end = (HEIGHT / 2) + (wall_height / 2);
}

static void	draw_wall_hit(int x, t_player *player, t_cub *cub)
{
	int		color;
	int		y;
	float	y_in_text;
	t_img	*text;

	y = -1;
	(DEBUG >= 3) && printf("r_wall_y_start/end (%d/%d) | y : %d\n",
		player->r_wall_y_start, player->r_wall_y_end, y);
	while (++y < player->r_wall_y_end && y < HEIGHT)
	{
		if (y >= 0 && y > player->r_wall_y_start)
		{
			if (player->current_orientation == DO)
				text = &cub->door_img;
			else
				text = &cub->text_img[player->current_orientation]
				[player->current_text];
			y_in_text = (y - player->r_wall_y_start)
				* (float)text->height / cub->player.wall_height;
			color = get_color_from_text(y_in_text, cub->player.r_hit_coef,
					text, cub);
			(player->r_side_hit == Y_HIT) && dim_color(&color);
			my_mlx_pixel_put(&cub->screen, x, y, color);
		}
	}
}

int	raycast(t_cub *cub)
{
	int	x;

	x = -1;
	while (++x < WIDTH)
	{
		calculate_ray_features(&cub->player, x);
		init_step_and_side_dist(&cub->player);
		dda(&cub->player, cub->maps, cub->door_map);
		update_cos_of_r_dir_and_dir(&cub->player);
		calculate_wall_height(&cub->player, x);
		draw_wall_hit(x, &cub->player, cub);
		(DEBUG >= 2) && printf("side:[%f] | X:[%d] | hit_coef: %f\n",
			cub->player.r_side_hit, x, cub->player.r_hit_coef);
	}
	(DEBUG >= 2) && printf("dda done for x\n");
	return (0);
}
