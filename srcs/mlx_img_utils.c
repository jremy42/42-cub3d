/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_img_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 11:21:59 by fle-blay          #+#    #+#             */
/*   Updated: 2022/07/21 11:23:29 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	(DEBUG == 3) && printf("x : [%d], y : [%d]\n", x, y);
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	get_color_from_sprite(int y, int x, t_img *img)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel /8));
	return(*(unsigned int *)dst);
}
