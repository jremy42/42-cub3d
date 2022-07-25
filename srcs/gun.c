/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jremy <jremy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 15:14:06 by fle-blay          #+#    #+#             */
/*   Updated: 2022/07/25 16:14:46 by jremy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "math.h"

static void	color_screen(t_cub *cub, int color_hex)
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

static void	update_gun_frame(t_cub *cub)
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

	update_gun_frame(cub);
	y = 0;
	x1 = (WIDTH - cub->gun_img[(cub->gun_frame / 2) % 5].width * GUN_SIZE) / 2;
	y1 = (HEIGHT - cub->gun_img[(cub->gun_frame / 2) % 5].height * GUN_SIZE);
	while (y < cub->gun_img[(cub->gun_frame / 2) % 5].height * GUN_SIZE - 1)
	{
		x = 0;
		while (x < cub->gun_img[(cub->gun_frame / 2) % 5].width * GUN_SIZE - 1)
		{
			color = get_color_from_mlx_img(x / GUN_SIZE, y / GUN_SIZE,
					&(cub->gun_img[(cub->gun_frame / 2) % 5]));
			if (color >= 0)
				my_mlx_pixel_put(&cub->screen, x + x1, y + y1, color);
			x++;
		}
		y++;
	}
}
