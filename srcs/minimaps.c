/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jremy <jremy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 10:10:42 by jremy             #+#    #+#             */
/*   Updated: 2022/07/20 19:16:51 by jremy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d.h"
#include "mlx.h"

float	sq_dist(float x1, float y1, float x2, float y2)
{
	float	dist_x;
	float	dist_y;

	dist_x = pow(x1 - x2, 2);
	dist_y = pow(y1 - y2, 2);
	return (dist_x + dist_y);
}

int	is_in_circle(float x, float y)
{
	float	distance;
	float	distance_sqrt;

	distance_sqrt = sqrtf(sq_dist(x, y, SIZE_PLAYER / 2, SIZE_PLAYER / 2));
	distance = distance_sqrt - 3;
	if (distance <= 0.0)
	{
		if (distance <= -1.0)
			return (1);
		return (2);
	}
	return (0);
}

void	player_square_put(t_img *img, int x, int y, int color)
{
	int		offset_y;
	int		offset_x;
	int		is_in;

	offset_y = 0;
	while (offset_y < SIZE_PLAYER)
	{
		offset_x = 0;
		while (offset_x < SIZE_PLAYER)
		{
			is_in = is_in_circle((float)offset_x, (float)offset_y);
			if (is_in)
				my_mlx_pixel_put(img, x + offset_x, y + offset_y, color);
			offset_x++;
		}
		offset_y++;
	}
}

void	draw_minimap(t_cub *cub, int pixel_x, int pixel_y, int size_current_l)
{
	float	x;
	float	y;
	char	current_char;

	x = cub->player.pos_x - ((VIEW_MM) * (cub->minimap_width / 2 - pixel_x));
	y = cub->player.pos_y - ((VIEW_MM) * (cub->minimap_height / 2 - pixel_y));
	if (x < 0 || y < 0)
		my_mlx_pixel_put(&cub->minimap, pixel_x, pixel_y, MINIMAP_EC);
	else if ((int)y > cub->nb_l_maps)
		my_mlx_pixel_put(&cub->minimap, pixel_x, pixel_y, MINIMAP_EC);
	else if (size_current_l == -1 || (int)floor(x) > size_current_l)
		my_mlx_pixel_put(&cub->minimap, pixel_x, pixel_y, MINIMAP_EC);
	else
	{
		current_char = cub->maps[(int)floor(y)][(int)floor(x)];
		if (current_char == '1' || current_char == '2' || current_char == '3' || current_char == '4')
			my_mlx_pixel_put(&cub->minimap, pixel_x, pixel_y, MINIMAP_WC);
		else if (current_char == 'D')
			my_mlx_pixel_put(&cub->minimap, pixel_x, pixel_y, MINIMAP_DC);
		else if (current_char == '0'
			|| current_char == 'G')
			my_mlx_pixel_put(&cub->minimap, pixel_x, pixel_y, MINIMAP_GC);
		else
			my_mlx_pixel_put(&cub->minimap, pixel_x, pixel_y, MINIMAP_EC);
	}
}

void	update_minimap(t_cub *cub)
{
	int	pixel_x;
	int	pixel_y;
	int	size_current_l;
	float y;

	pixel_y = 0;
	while (pixel_y < cub->minimap_height - 1)
	{
		pixel_x = 0;
		y = cub->player.pos_y - ((VIEW_MM) * (cub->minimap_height / 2 - pixel_y));
		if (y > 0 && y < cub->nb_l_maps)
			size_current_l = (int)__strlen(cub->maps[(int)floor(y)] ) - 1;
		else 
			size_current_l = -1;
		while (pixel_x < cub->minimap_width - 1)
		{
			draw_minimap(cub, pixel_x, pixel_y, size_current_l);
			pixel_x++;
		}
		pixel_y++;
	}
	player_square_put(&cub->minimap, cub->minimap_width / 2 - 4,
		cub->minimap_height / 2 - 4, MINIMAP_PC);
}
