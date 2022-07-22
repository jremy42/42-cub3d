/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deus <deus@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 16:59:04 by deus              #+#    #+#             */
/*   Updated: 2022/07/22 17:15:16 by deus             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "math.h"

int	print_sprite_info(t_sprite *sprite)
{
	printf("world pos_x/pos_y : [%f/%f]\n", sprite->pos_x, sprite->pos_y);
	printf("cam pos_x/pos_y : [%f/%f]\n", sprite->cam_pos_x, sprite->cam_pos_y);
	printf("norm/dir_proj/plane_proj : [%f/%f/%f]\n",
		sprite->norm, sprite->dir_proj, sprite->plane_proj);
	printf("screen_x/screen_height/screen_width/to_show : [%d/%d/%d/%d]\n",
		sprite->screen_x, sprite->screen_height,
		sprite->screen_width, sprite->to_show);
	printf(" screen_x_start/end: [%d][%d]\n",
		sprite->screen_x_start, sprite->screen_x_end);
	printf(" screen_y_start/end: [%d][%d]\n",
		sprite->screen_y_start, sprite->screen_y_end);
	printf("gun hit = [%d]\n", sprite->gun_hit);
	printf("animate/current_frame/count_animage : [%d][%d][%d]\n",
		sprite->animate,
		sprite->current_frame, sprite->count_animate);
	printf("to show : [%d]\n", sprite->to_show);
	return (1);
}

float	vector_det(float u_x, float u_y, float v_x, float v_y)
{
	return (u_x * v_y - u_y * v_x);
}

float	vector_dot(float u_x, float u_y, float v_x, float v_y)
{
	return (u_x * v_x + u_y * v_y);
}

void	get_sprite_frame(t_sprite *sprite)
{
	if (sprite->animate == 1)
	{
		sprite->count_animate++;
		if (sprite->count_animate > 15)
			sprite->current_frame = ((sprite->count_animate) / 15) % 2 + 2;
		else
			sprite->current_frame = 1;
	}
	else if (sprite->animate == 2)
	{
		sprite->count_animate++;
		sprite->current_frame = ((sprite->count_animate) / 5) + 4;
		if (sprite->count_animate > 5 * 3)
			sprite->animate = 3;
	}
	else if (sprite->animate == 3)
		sprite->current_frame = 7;
}

void	update_sprite_order(t_sprite *s_tab, int s_count, int *s_order)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	while (i < s_count)
	{
		j = i + 1;
		while (j < s_count)
		{
			if (s_tab[s_order[j]].norm < s_tab[s_order[i]].norm)
			{
				tmp = s_order[i];
				s_order[i] = s_order[j];
				s_order[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
