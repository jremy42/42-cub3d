/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jremy <jremy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 13:56:26 by fle-blay          #+#    #+#             */
/*   Updated: 2022/07/22 11:03:16 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "keycodes.h"
#include "math.h"

int	try_move_x_and_y_axis(t_cub *cub, float try_x, float try_y)
{
	char	type_pos;
	float	door_value;

	type_pos = cub->maps[(int)floor(try_y)][(int)floor(try_x)];
	door_value = cub->door_map[(int)floor(try_y)][(int)floor(try_x)];
	if (type_pos == '0' || (type_pos == 'D' && door_value == 0.0f))
	{
		cub->player.pos_x = try_x;
		cub->player.pos_y = try_y;
		return (1);
	}
	return (0);
}

int	try_move_x_axis(t_cub *cub, float try_x)
{
	char	type_pos;
	float	door_val;

	type_pos = cub->maps[(int)floor(cub->player.pos_y)][(int)floor(try_x)];
	door_val = cub->door_map[(int)floor(cub->player.pos_y)][(int)floor(try_x)];
	if (type_pos == '0' || (type_pos == 'D' && door_val == 0.0f))
	{
		cub->player.pos_x = try_x;
		return (1);
	}
	return (0);
}

int	try_move_y_axis(t_cub *cub, float try_y)
{
	char	type_pos;
	float	door_val;

	type_pos = cub->maps[(int)floor(try_y)][(int)floor(cub->player.pos_x)];
	door_val = cub->door_map[(int)floor(try_y)][(int)floor(cub->player.pos_x)];
	if (type_pos == '0' || (type_pos == 'D' && door_val == 0.0f))
	{
		cub->player.pos_y = try_y;
		return (1);
	}
	return (0);
}

void	__move(t_cub *cub, float move_dir_x, float move_dir_y)
{
	float	try_x;
	float	try_y;

	try_x = cub->player.pos_x + (SPEED + (0.05 * SIZE_PLAYER / 2)) * move_dir_x;
	try_y = cub->player.pos_y + (SPEED + (0.05 * SIZE_PLAYER / 2)) * move_dir_y;
	if (try_move_x_and_y_axis(cub, try_x, try_y))
		return ;
	if (try_move_x_axis(cub, try_x))
		return ;
	if (try_move_y_axis(cub, try_y))
		return ;
}

int	print_vector(t_cub *cub)
{
	int	i;
	int	j;

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

void	update_hit_vector_attributes(t_cub *cub)
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

void	go_to_next_closest_line_or_column(t_cub *cub)
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

int	print_coord_hit(t_cub *cub)
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

int	__key_release(int keycode, t_cub *cub)
{
	if (keycode == KEY_L || keycode == ARROW_LEFT)
		cub->action &= ~(1 << 0);
	if (keycode == KEY_D || keycode == ARROW_DOWN)
			cub->action &= ~(1 << 1);
	if (keycode == KEY_R || keycode == ARROW_RIGHT)
			cub->action &= ~(1 << 2);
	if (keycode == KEY_U || keycode == ARROW_UP)
			cub->action &= ~(1 << 3);
	if (keycode == SPACE_BAR)
			cub->action &= ~(1 << 4);
	return (1);
}

int	__key_press(int keycode, t_cub *cub)
{
	if (keycode == KEY_L || keycode == ARROW_LEFT)
		cub->action |= 1 << 0;
	if (keycode == KEY_D || keycode == ARROW_DOWN)
			cub->action |= 1 << 1;
	if (keycode == KEY_R || keycode == ARROW_RIGHT)
			cub->action |= 1 << 2;
	if (keycode == KEY_U || keycode == ARROW_UP)
			cub->action |= 1 << 3;
	if (keycode == SPACE_BAR)
			cub->action |= 1 << 4;
	cub->last_key_press = keycode;
	if (keycode == KEY_ESC)
		return (__quit(cub));
	return (1);
}
