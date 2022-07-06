/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jremy <jremy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 10:53:50 by jremy             #+#    #+#             */
/*   Updated: 2022/07/06 09:07:11 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"
#include "mlx.h"

int	create_image(t_cub *cub, t_img *img, int width, int height)
{
	img->mlx_img = mlx_new_image(cub->mlx, width, height);
	if (!img->mlx_img)
		return (0);
	img->addr = mlx_get_data_addr(img->mlx_img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	DEBUG && printf("img addr [%p]\n bits_per_pixel [%d]\n line_length [%d]\n endian [%d]", img->mlx_img, img->bits_per_pixel, img->line_length, img->endian);
	return (1);
}

int	create_cub_images(t_cub *cub)
{
	if (!create_image(cub, &cub->screen, WIDTH, HEIGHT))
		return (0);
	if (!create_image(cub, &cub->backgd, WIDTH, HEIGHT))
		return (0);
	if (!create_image(cub, &cub->minimap, WIDTH, HEIGHT))
		return (0);
	return (1);
}
