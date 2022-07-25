/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_img_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deus <deus@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 11:21:59 by fle-blay          #+#    #+#             */
/*   Updated: 2022/07/25 15:36:54 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <math.h>

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	(DEBUG == 3) && printf("x : [%d], y : [%d]\n", x, y);
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	get_color_from_mlx_img(int x, int y, t_img *img)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

int	get_color_from_text(int y_in_text, float r_hit_coef, t_img *img, t_cub *cub)
{
	char	*dst;
	int		x;
	float	door_value;

	door_value = cub->door_map[cub->player.r_map_y][cub->player.r_map_x];
	if (cub->player.current_orientation == DO && door_value != 2)
		x = (r_hit_coef + 1 - door_value + floor(door_value)) * img->width;
	else
		x = r_hit_coef * img->width;
	dst = img->addr + (y_in_text * img->line_length + x
			* (img->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}
