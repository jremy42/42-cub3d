/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 12:47:27 by fle-blay          #+#    #+#             */
/*   Updated: 2022/07/25 12:55:09 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "math.h"
#include "colors.h"

static void	find_coef(t_player *player)
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

static void	find_orientation(t_player *player, char map_char)
{
	player->current_text = map_char - 49;
	if (player->r_side_hit == X_HIT)
	{
		if (player->r_dir_x < 0)
			player->current_orientation = EA;
		else
			player->current_orientation = WE;
	}
	else
	{
		if (player->r_dir_y < 0)
			player->current_orientation = SO;
		else
			player->current_orientation = NO;
	}
}

static void	go_to_next_line_or_column(t_player *player)
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
}

int	dda(t_player *player, char **map, float **door_map)
{
	int		hit;
	char	map_char;
	float	door_value;

	hit = 0;
	while (!hit)
	{
		go_to_next_line_or_column(player);
		map_char = map[player->r_map_y][player->r_map_x];
		find_coef(player);
		if (map_char >= '1' && map_char <= '6')
		{
			find_orientation(player, map_char);
			hit = 1;
		}
		else if (map_char == 'D')
		{
			door_value = door_map[player->r_map_y][player->r_map_x];
			if (player->r_hit_coef < door_value - floor(door_value)
				|| (door_value == 2))
				hit = 1;
			player->current_orientation = DO;
		}
	}
	return (hit);
}
