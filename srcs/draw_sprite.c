/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deus <deus@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 16:26:49 by deus              #+#    #+#             */
/*   Updated: 2022/07/22 16:47:26 by deus             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

void	update_animate(t_sprite *s)
{
	s->animate = 0;
	s->current_frame = 0;
	s->count_animate = 0;
}

void	draw_pixel_in_screen(t_cub *cub, t_sprite *s, int true_x, int x)
{
	int	y;
	int	true_y;
	int	color;

	y = s->screen_y_start - 1;
	while (++y < HEIGHT && y < s->screen_y_end)
	{
		true_y = (y - s->screen_y_start)
			* (*s->sprite_img_tab)[s->current_frame].height / s->screen_height;
		if (y < 0)
			continue ;
		if (s->to_show && cub->player.perp_wall_dist[x] > s->dir_proj)
		{
			color = get_color_from_mlx_img(true_x, true_y,
					&(*s->sprite_img_tab)[s->current_frame]);
			if (color >= 0)
				my_mlx_pixel_put(&cub->screen, x, y, color);
			if (x == s->screen_x && s->norm < G_DETECT_DIST && s->animate == 0)
					s->animate = 1;
			if (x == WIDTH / 2 && y == HEIGHT / 2 && color >= 0)
				s->gun_hit = 1;
		}
		else if (s->animate == 1)
			update_animate(s);
	}
}

void	draw_sprite(t_cub *cub, t_sprite *s)
{
	int		x;
	int		true_x;

	x = s->screen_x_start - 1;
	s->gun_hit = 0;
	while (++x < WIDTH && x < s->screen_x_end)
	{
		true_x = (x - s->screen_x_start)
			* (*s->sprite_img_tab)[s->current_frame].width / s->screen_width;
		if (x < 0)
			continue ;
		draw_pixel_in_screen(cub, s, true_x, x);
	}
}
