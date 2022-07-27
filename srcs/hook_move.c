/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jremy <jremy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 12:57:13 by fle-blay          #+#    #+#             */
/*   Updated: 2022/07/27 09:54:50 by jremy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "keycodes.h"
#include "math.h"

static void	try_move_x_axis(t_cub *cub, float try_x)
{
	char	type_pos;
	float	door_val;

	type_pos = cub->maps[(int)floor(cub->player.pos_y)][(int)floor(try_x)];
	door_val = cub->door_map[(int)floor(cub->player.pos_y)][(int)floor(try_x)];
	if (type_pos == '0' || (type_pos == 'D' && door_val == 0.0f))
		cub->player.pos_x = try_x;
}

static void	try_move_y_axis(t_cub *cub, float try_y)
{
	char	type_pos;
	float	door_val;

	type_pos = cub->maps[(int)floor(try_y)][(int)floor(cub->player.pos_x)];
	door_val = cub->door_map[(int)floor(try_y)][(int)floor(cub->player.pos_x)];
	if (type_pos == '0' || (type_pos == 'D' && door_val == 0.0f))
		cub->player.pos_y = try_y;
}

void	__move(t_cub *cub, float move_dir_x, float move_dir_y)
{
	float	try_x;
	float	try_y;

	try_x = cub->player.pos_x + (SPEED + (0.05 * SIZE_PLAYER / 2)) * move_dir_x;
	try_y = cub->player.pos_y + (SPEED + (0.05 * SIZE_PLAYER / 2)) * move_dir_y;
	try_move_x_axis(cub, try_x);
	try_move_y_axis(cub, try_y);
}
