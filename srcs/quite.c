/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quite.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jremy <jremy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 14:01:59 by jremy             #+#    #+#             */
/*   Updated: 2022/07/21 16:55:24 by jremy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "sprites.h"

#ifdef __linux__

void	destroy_mlx_data(t_cub *cub)
{
	free(cub->sprite_tab);
	free(cub->sprite_order);
	DEBUG && printf("mlx pointer = [%p], win pointer = [%p]\n",
		cub->mlx, cub->win);
	if (cub->backgd.mlx_img)
		mlx_destroy_image(cub->mlx, cub->backgd.mlx_img);
	if (cub->screen.mlx_img)
		mlx_destroy_image(cub->mlx, cub->screen.mlx_img);
	if (cub->minimap.mlx_img)
		mlx_destroy_image(cub->mlx, cub->minimap.mlx_img);
	//mlx_mouse_show(cub->mlx, cub->win);
	if (cub->win)
		mlx_destroy_window(cub->mlx, cub->win);
	mlx_do_key_autorepeaton(cub->mlx);
	if (cub->mlx)
	{
		DEBUG && printf("LINUX : Destroying display\n");
		mlx_destroy_display(cub->mlx);
	}
	free(cub->mlx);
	DEBUG && printf("Mlx data successfully destroyed\n");
	exit(0);
}
#endif

#ifdef __MACH__

void	destroy_mlx_data(t_cub *cub)
{
	DEBUG && printf("mlx pointer = [%p], win pointer = [%p]\n", cub->mlx, cub->win);
	if (cub->backgd.mlx_img)
		mlx_destroy_image(cub->mlx, cub->backgd.mlx_img);
	if (cub->screen.mlx_img)
		mlx_destroy_image(cub->mlx, cub->screen.mlx_img);
	if (cub->minimap.mlx_img)
		mlx_destroy_image(cub->mlx, cub->minimap.mlx_img);
	if (cub->win)
		mlx_destroy_window(cub->mlx, cub->win);
	mlx_do_key_autorepeaton(cub->mlx);
	free(cub->mlx);
	DEBUG && printf("Mlx data successfully destroyed\n");
	exit(0);
}

#endif

void	destroy_cub_text(t_cub *cub)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 6)
		{
			if (&cub->text_img[i][j])
				mlx_destroy_image(cub->mlx, cub->text_img[i][j].mlx_img);
		}	
	}
	mlx_destroy_image(cub->mlx, cub->door_img.mlx_img);
}

void	destroy_cub_sprite(t_cub *cub)
{
	int	i;

	i = -1;
	while (++i < GUARD_SPRITE_COUNT)
	{
		if (&cub->guard_img[i])
			mlx_destroy_image(cub->mlx, cub->guard_img[i].mlx_img);
	}
	i = -1;
	while (++i < GUN_SPRITE_COUNT)
	{
		if (&cub->gun_img[i])
			mlx_destroy_image(cub->mlx, cub->gun_img[i].mlx_img);
	}
}

int	__quit(t_cub *cub)
{
	destroy_cub_data(cub);
	destroy_cub_text(cub);
	destroy_cub_sprite(cub);
	destroy_mlx_data(cub);
	return (0);
}
