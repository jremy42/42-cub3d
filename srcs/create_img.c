/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jremy <jremy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 10:53:50 by jremy             #+#    #+#             */
/*   Updated: 2022/07/05 14:54:29 by jremy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"
#include "mlx.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	create_image(t_cub *cub, t_img *img, int width, int height)
{
	img->mlx_img = mlx_new_image(cub->mlx, width, height);
	if (!img->mlx_img)
		return (0);
	img->addr = mlx_get_data_addr(img->mlx_img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	//fprintf(stderr, "addr [%p]\n bits_per_pixel [%d]\n line_length [%d] \n endian [%d]", cub->img.mlx_img, cub->img.bits_per_pixel, cub->img.line_length, cub->img.endian);
	return (1);
}

int	create_cub_images(t_cub *cub)
{
	if (!create_image(cub, &cub->screen, WIDTH, HEIGHT))
		return (0);
	if (!create_image(cub, &cub->backgd, WIDTH, HEIGHT))
		return (0);
	if (!create_image(cub, &cub->minimap, WIDTH/8, HEIGHT/8))
		return (0);
	return (1);
}


/*
while (y < 480)
	{
			int x;
	int	y;

	x = 0;
	y = 0;
		x = 0;
		while (x < 640)
		{	
			my_mlx_pixel_put(&cub->img, x, y, cub->floor.trgb);
			x++;
		}
		y++;
	}

	create_minimaps(cub);
	mlx_put_image_to_window(cub->mlx,cub->win, cub->img.mlx_img, 0, 0);

*/
