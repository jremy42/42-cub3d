/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <{fle-blay}@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:39:06 by fle-blay          #+#    #+#             */
/*   Updated: 2022/07/22 11:56:46 by fle-blay         ###   ########.fr       */
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

void	calculate_ray_features(t_player *player, int x)
{
	player->cam_x = (2 * x / (float)WIDTH) - 1;
	player->r_dir_x = player->dir_x + player->plane_x * player->cam_x;
	player->r_dir_y = player->dir_y + player->plane_y * player->cam_x;
	player->r_slope_dir = player->r_dir_y / player->r_dir_x;
	player->r_delta_dist_x = sqrt(1 + pow(player->r_slope_dir, 2));
	player->r_delta_dist_y = sqrt(1 + pow(1 / player->r_slope_dir, 2));
}

void	init_step_and_side_dist(t_p *p)
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

void	find_coef(t_player *player)
{
	if (player->r_side_hit == Y_HIT)
	{
		player->r_hit_y = (float)player->r_map_y;
		if (player->r_dir_y < 0)
			player->r_hit_y += 1;
		player->r_hit_x = (player->r_hit_y - player->pos_y)
			/ player->r_slope_dir + player->pos_x;
		player->r_hit_coef = player->r_hit_x - floor(player->r_hit_x);
	}
	else
	{
		player->r_hit_x = (float)player->r_map_x;
		if (player->r_dir_x < 0)
			player->r_hit_x += 1;
		player->r_hit_y = (player->r_hit_x - player->pos_x)
			* player->r_slope_dir + player->pos_y;
		player->r_hit_coef = player->r_hit_y - floor(player->r_hit_y);
	}
}

int	find_orientation(t_player *player)
{
	if (player->r_side_hit == X_HIT)
	{
		if (player->r_dir_x < 0)
			return (EA);
		else
			return (WE);
	}
	else
	{
		if (player->r_dir_y < 0)
			return (SO);
		else
			return (NO);
	}
}

int	dda(t_player *player, char **map, float **door_map)
{
	int		hit;
	char	map_text;
	float	door_value;

	hit = 0;
	while (!hit)
	{
		if (player->r_side_dist_x < player->r_side_dist_y)
		{
			player->r_side_dist_x += player->r_delta_dist_x;
			player->r_map_x += player->r_step_x;
			player->r_side_hit = X_HIT;
		}
		else
		{
			player->r_side_dist_y += player->r_delta_dist_y;
			player->r_map_y += player->r_step_y;
			player->r_side_hit = Y_HIT;
		}
		map_text = map[player->r_map_y][player->r_map_x];
		if (map_text == '1' || map_text == '2' || map_text == '3' || map_text == '4' || map_text == '5' || map_text == '6')
		{
			find_coef(player);
			player->current_orientation = find_orientation(player);
			player->current_text = map_text - 49;
			hit = 1;
		}
		else if (map_text == 'D')
		{
			find_coef(player);
			door_value = door_map[player->r_map_y][player->r_map_x];
			if (player->r_hit_coef < door_value - floor(door_value)
				|| (door_value == 2 ))
				hit = 1;
			player->current_orientation = DO;
		}
	}
	return (hit);
}

void	calculate_wall_height(t_player *player, int x)
{
	int		wall_height;
	float	perpWallDist;
	float	trueWallDist;;

	if (player->r_side_hit == X_HIT)
		trueWallDist = (player->r_side_dist_x - player->r_delta_dist_x);
	else
		trueWallDist = (player->r_side_dist_y - player->r_delta_dist_y);
	perpWallDist = trueWallDist * player->cos_alpha;
	player->perp_wall_dist[x] = perpWallDist;
	//player->true_wall_dist[x] = trueWallDist;
	wall_height = HEIGHT/perpWallDist;
	player->wall_height = wall_height;
	player->r_wall_y_start = (HEIGHT / 2) - (wall_height / 2);
	player->r_wall_y_end = (HEIGHT / 2) + (wall_height / 2);
	/*
	if (player->r_wall_y_start < 0)
		player->r_wall_y_start = 0;

	if (player->r_wall_y_end > HEIGHT -1)
		player->r_wall_y_end = HEIGHT - 1;
	*/
}

int	get_color_from_text(float step, float r_hit_coef, t_img *img, t_cub *cub)
{
	char	*dst;
	int 	x;
	int		y;
	float	door_value;

	/*
	if (r_hit_coef < 0)
		r_hit_coef = 1 - fabs(r_hit_coef);
	x = (r_hit_coef) * (img->width - 0);
	*/
	door_value = cub->door_map[cub->player.r_map_y][cub->player.r_map_x];
	if (cub->player.current_orientation == DO && door_value != 2)
		x = (r_hit_coef + 1 - door_value + floor(door_value))* img->width;
	else
		x = r_hit_coef * img->width;
	// check x value;
	//if (cub->player.r_side_hit == X_HIT)
		//printf("x = [%d] | r_hit_coef[%f] img->width = [%d]\n",x, r_hit_coef, img->width);
	y = (int)floor(step);
	//printf("x = [%d] y =  [%d]\n", x, y);
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel /8));
	//(DEBUG == 4)  && printf("x : [%d], y : [%d] step : [%f] r_hit_coef : [%f] img->width [%d]\n", x , y, step, r_hit_coef, img->width);
	return(*(unsigned int*)dst);
}

void 	draw_wall_hit(int x, t_player *player, t_cub *cub)
{
	int		color;
	int		y;
	float	step;

	y = player->r_wall_y_start;
	y = 0;
	step = 0;
	if (player->r_side_hit == X_HIT)
		color = X_HIT_COLOR;
	else
		color = Y_HIT_COLOR;
	(DEBUG == 3) && printf("r_wall_y_start/end (%d/%d) | y : %d\n", player->r_wall_y_start, player->r_wall_y_end, y);
	while (y < player->r_wall_y_end && y < HEIGHT)
	{

		if (y >= player->r_wall_y_start && y >= 0 && y < HEIGHT)
		{
			if (player->current_orientation == DO)
			{
				step = (y - player->r_wall_y_start) * (cub->door_img.height - 0) * 1.0f / (cub->player.wall_height - 0);
				color = get_color_from_text(step, cub->player.r_hit_coef, &cub->door_img, cub);
			}
			else
			{
				step = (y - player->r_wall_y_start) * (cub->text_img[player->current_orientation][player->current_text].height - 0) * 1.0f / (cub->player.wall_height - 0);
				color = get_color_from_text(step, cub->player.r_hit_coef, &cub->text_img[player->current_orientation][player->current_text], cub);
			}
			if (player->r_side_hit == Y_HIT)
			{
				color >>= 1;
				color &= (127 << 16 | 127 << 8 | 127);
			}
			my_mlx_pixel_put(&cub->screen, x, y, color);
			//if (y == HEIGHT/2)
			//	DEBUG && printf(" x: [%d] | r_wall_y_start [%d] | text_img.height [%d]  / wall_height: [%d] step = [%f] r_hit_coef[%f]\n",x , player->r_wall_y_start, cub->text_img[0].height, cub->player.wall_height, step, cub->player.r_hit_coef);
		}
		//else
		//	my_mlx_pixel_put(&cub->screen, x, y,0);
		y++;
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
		//DEBUG && printf("side:[%f] | X:[%d] | hit_coef: %f\n",cub->player.r_side_hit, x, cub->player.r_hit_coef);
	}
	(DEBUG == 2) && printf("dda done for x\n");
	return (0);
}

