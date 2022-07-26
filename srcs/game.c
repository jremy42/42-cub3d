/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deus <deus@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 10:10:34 by fle-blay          #+#    #+#             */
/*   Updated: 2022/07/26 15:08:40 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "math.h"

static int	print_render_frame_debug_info(t_cub *cub)
{
	clear_screen();
	DEBUG && print_sight_vector(cub);
	DEBUG && print_debug_info(cub);
	DEBUG && printf("last key pressed : [%d]\n", cub->last_key_press);
	return (1);
}

static void	do_actions(t_cub *cub)
{
	int	i;

	i = -1;
	while (++i < 7)
	{
		if (cub->action & (1 << i))
			cub->hook_fx[i](cub);
	}
}

static void	load_background(t_cub *cub)
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

int	render_frame(t_cub *c)
{
	static size_t	next_frame = 0;
	size_t			current_time;

	current_time = __get_time();
	if (current_time >= next_frame)
	{
		do_actions(c);
		DEBUG && print_render_frame_debug_info(c);
		next_frame = current_time + 1000 / FPS;
		__update_door_value(c);
		__mouse_move(c);
		load_background(c);
		raycast(c);
		calculate_all_sprite_info(c);
		update_sprite_order(c->sprite_tab, c->sprite_count, c->sprite_order);
		handle_sprite(c);
		update_minimap(c);
		draw_gun(c);
		draw_target(c);
		colorize_screen(c);
		mlx_put_image_to_window(c->mlx, c->win, c->screen.mlx_img, 0, 0);
	}
	return (1);
}
