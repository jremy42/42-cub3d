/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deus <deus@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 12:33:48 by deus              #+#    #+#             */
/*   Updated: 2022/07/22 12:33:54 by deus             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "sprites.h"

int	load_gun_img(t_cub *cub)
{
	int	i;

	i = -1;
	while (++i < GUN_SPRITE_COUNT)
	{
		cub->gun_img[i].mlx_img = mlx_xpm_file_to_image(cub->mlx,
				cub->gun_img_file[i], &cub->gun_img[i].width,
				&cub->gun_img[i].height);
		if (!cub->gun_img[i].mlx_img)
			return (__putstr_fd("Failed to load a gun img\n", 2), 0);
		cub->gun_img[i].addr = mlx_get_data_addr(cub->gun_img[i].mlx_img,
				&cub->gun_img[i].bits_per_pixel,
				&cub->gun_img[i].line_length,
				&cub->gun_img[i].endian);
	}
	return (1);
}

int	load_guard_img(t_cub *cub)
{
	int	i;

	i = -1;
	while (++i < GUARD_SPRITE_COUNT)
	{
		cub->guard_img[i].mlx_img = mlx_xpm_file_to_image(cub->mlx,
				cub->guard_img_file[i], &cub->guard_img[i].width,
				&cub->guard_img[i].height);
		if (!cub->guard_img[i].mlx_img)
			return (__putstr_fd("Failed to load a guard img\n", 2), 0);
		cub->guard_img[i].addr = mlx_get_data_addr(cub->guard_img[i].mlx_img,
				&cub->guard_img[i].bits_per_pixel,
				&cub->guard_img[i].line_length,
				&cub->guard_img[i].endian);
	}
	return (1);
}

int	set_img_array_address_for_guard_sprites(t_cub *cub)
{
	int	i;

	i = -1;
	while (++i < cub->sprite_count)
		cub->sprite_tab[i].sprite_img_tab = &cub->guard_img;
	return (1);
}

int	load_textures(t_cub *cub)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 6)
		{
			cub->text_img[i][j].mlx_img = mlx_xpm_file_to_image(cub->mlx,
					cub->text[i][j], &cub->text_img[i][j].width,
					&cub->text_img[i][j].height);
			if (!cub->text_img[i][j].mlx_img)
				return (__putstr_fd("Failed to load texture\n", 2), 0);
			if (cub->text_img[i][j].width != cub->text_img[i][j].height)
				return (__putstr_fd("Not valid texture size\n", 2), 0);
			cub->text_img[i][j].addr = mlx_get_data_addr(
					cub->text_img[i][j].mlx_img,
					&cub->text_img[i][j].bits_per_pixel,
					&cub->text_img[i][j].line_length,
					&cub->text_img[i][j].endian);
		}
	}
	return (1);
}

int	load_images(t_cub *cub)
{
	if (!load_textures(cub))
		return (0);
	if (BONUS)
	{
		cub->door_img.mlx_img = mlx_xpm_file_to_image(cub->mlx, cub->door,
				&cub->door_img.width, &cub->door_img.height);
		if (!cub->door_img.mlx_img)
			return (__putstr_fd("Failed to load texture\n", 2), 0);
		if (cub->door_img.width != cub->door_img.height)
			return (__putstr_fd("Not valid texture size\n", 2), 0);
		cub->door_img.addr = mlx_get_data_addr(cub->door_img.mlx_img,
				&cub->door_img.bits_per_pixel,
				&cub->door_img.line_length, &cub->door_img.endian);
		if (!load_gun_img(cub) || !load_guard_img(cub))
			return (__putstr_fd("Error loading game sprites\n", 2), 0);
		set_img_array_address_for_guard_sprites(cub);
	}
	return (1);
}
