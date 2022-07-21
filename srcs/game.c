/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jremy <jremy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 10:10:34 by fle-blay          #+#    #+#             */
/*   Updated: 2022/07/21 16:37:55 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "math.h"

void	update_gun_frame(t_cub *cub)
{
	if (cub->gun_animate != 0)
		cub->gun_frame++;
	if (cub->gun_frame > 4 * 2)
	{
		cub->gun_animate = 0;
		cub->gun_frame = 0;
	}
}

void	draw_gun(t_cub *cub)
{
	int	x;
	int	y;
	int	color;
	int	x1;
	int	y1;

	y = 0;
	x1 = (WIDTH - cub->gun_img[(cub->gun_frame / 2) % 5].width * GUN_SIZE) / 2;
	y1 = (HEIGHT - cub->gun_img[(cub->gun_frame / 2) % 5].height * GUN_SIZE);
	while (y < cub->gun_img[(cub->gun_frame / 2) % 5].height * GUN_SIZE - 1)
	{
		x = 0;
		while (x < cub->gun_img[(cub->gun_frame / 2) % 5].width * GUN_SIZE - 1)
		{
			color = get_color_from_sprite(y / GUN_SIZE, x / GUN_SIZE,
					&(cub->gun_img[(cub->gun_frame / 2) % 5]));
			if (color >= 0)
				my_mlx_pixel_put(&cub->screen, x + x1, y + y1, color);
			x++;
		}
		y++;
	}
}

void	draw_target(t_cub *cub)
{
	int	x;
	int	y;

	y = HEIGHT / 2 - 2;
	while (y < HEIGHT / 2 + 2)
	{
		x = WIDTH / 2 - 2;
		while (x < WIDTH / 2 + 2)
		{
			my_mlx_pixel_put(&cub->screen, x, y, 0xFF00000);
			x++;
		}
		y++;
	}
}

void	handle_sprite(t_cub *cub)
{
	int	i;
	int	true_sprite;
	int	to_kill;

	i = cub->sprite_count - 1;
	to_kill = -1;
	while (i >= 0)
	{
		true_sprite = cub->sprite_order[i];
		draw_sprite(cub, &cub->sprite_tab[true_sprite]);
		if (cub->gun_frame == 1 && cub->sprite_tab[true_sprite].gun_hit
			&& !cub->sprite_tab[true_sprite].do_not_display
			&& cub->sprite_tab[true_sprite].animate < 2)
			to_kill = true_sprite;
		i--;
	}
	if (to_kill >= 0)
	{
		cub->sprite_tab[to_kill].animate = 2;
		cub->sprite_tab[to_kill].count_animate = 0;
		cub->maps[(int)floor(cub->sprite_tab[to_kill].pos_y)]
		[(int)floor(cub->sprite_tab[to_kill].pos_x)] = '0';
	}
}

void	color_screen(t_cub *cub, int color_hex)
{
	unsigned int	x;
	unsigned int	y;
	unsigned int	color;

	y = 0;
	while (y < HEIGHT - 1)
	{
		x = 0;
		while (x < WIDTH - 1)
		{
			color = get_color_from_mlx_img(x, y, &cub->screen);
			color |= color_hex;
			my_mlx_pixel_put(&cub->screen, x, y, color);
			x++;
		}
		y++;
	}
}

int	print_render_frame_debug_info(t_cub *cub)
{
	clear_screen();
	DEBUG && print_coord_hit(cub);
	DEBUG && print_vector(cub);
	DEBUG && print_debug_info(cub);
	DEBUG && printf("last key pressed : [%d]\n", cub->last_key_press);
	return (1);
}

void	do_actions(t_cub *cub)
{
	int	i;

	i = -1;
	while (++i < 5)
	{
		if (cub->action & (1 << i))
			cub->hook_fx[i](cub);
	}
}

void	colorize_screen(t_cub *cub)
{
	if (cub->gun_frame == 1)
	{
		color_screen(cub, YELLOW_HEX);
		__putstr_fd("\a", 1);
	}
	else if (cub->hit_by_guard)
		color_screen(cub, RED_HEX);
	cub->hit_by_guard = 0;
}

void	calculate_all_sprite_info(t_cub *cub)
{
	int	i;

	i = -1;
	while (++i < cub->sprite_count)
	{
		calculate_sprite_info(cub, &cub->sprite_tab[i]);
		(DEBUG == 2) && print_sprite_info(&cub->sprite_tab[i]);
		cub->sprite_order[i] = i;
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
		update_gun_frame(c);
		draw_gun(c);
		draw_target(c);
		colorize_screen(c);
		mlx_put_image_to_window(c->mlx, c->win, c->screen.mlx_img, 0, 0);
		mlx_put_image_to_window(c->mlx, c->win, c->minimap.mlx_img, 0, 0);
	}
	return (1);
}
