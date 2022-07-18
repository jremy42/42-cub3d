#include "cub3d.h"
#include "mlx.h"

int	load_gun(t_cub *cub)
{
	cub->gun_img[0].mlx_img = mlx_xpm_file_to_image(cub->mlx, "./sprites/gun/pistol_0.xpm",
			       &cub->gun_img[0].width, &cub->gun_img[0].height);
	if(!cub->gun_img[0].mlx_img)
		return(__putstr_fd("Failed to load sprite 1\n", 2), 0);
	cub->gun_img[0].addr = mlx_get_data_addr(cub->gun_img[0].mlx_img, &cub->gun_img[0].bits_per_pixel,
			&cub->gun_img[0].line_length, &cub->gun_img[0].endian);

	cub->gun_img[1].mlx_img = mlx_xpm_file_to_image(cub->mlx, "./sprites/gun/pistol_1.xpm",
			       &cub->gun_img[1].width, &cub->gun_img[1].height);
	if(!cub->gun_img[1].mlx_img)
		return(__putstr_fd("Failed to load sprite 2\n", 2), 0);
	cub->gun_img[1].addr = mlx_get_data_addr(cub->gun_img[1].mlx_img, &cub->gun_img[1].bits_per_pixel,
			&cub->gun_img[1].line_length, &cub->gun_img[1].endian);

	cub->gun_img[2].mlx_img = mlx_xpm_file_to_image(cub->mlx, "./sprites/gun/pistol_2.xpm",
			       &cub->gun_img[2].width, &cub->gun_img[2].height);
	if(!cub->gun_img[2].mlx_img)
		return(__putstr_fd("Failed to load sprite 3\n", 2), 0);
	cub->gun_img[2].addr = mlx_get_data_addr(cub->gun_img[2].mlx_img, &cub->gun_img[2].bits_per_pixel,
			&cub->gun_img[2].line_length, &cub->gun_img[2].endian);

	cub->gun_img[3].mlx_img = mlx_xpm_file_to_image(cub->mlx, "./sprites/gun/pistol_3.xpm",
			       &cub->gun_img[3].width, &cub->gun_img[3].height);
	if(!cub->gun_img[3].mlx_img)
		return(__putstr_fd("Failed to load sprite 4\n", 2), 0);
	cub->gun_img[3].addr = mlx_get_data_addr(cub->gun_img[3].mlx_img, &cub->gun_img[3].bits_per_pixel,
			&cub->gun_img[3].line_length, &cub->gun_img[3].endian);

	cub->gun_img[4].mlx_img = mlx_xpm_file_to_image(cub->mlx, "./sprites/gun/pistol_1.xpm",
			       &cub->gun_img[4].width, &cub->gun_img[4].height);
	if(!cub->gun_img[2].mlx_img)
		return(__putstr_fd("Failed to load sprite 3\n", 2), 0);
	cub->gun_img[4].addr = mlx_get_data_addr(cub->gun_img[4].mlx_img, &cub->gun_img[4].bits_per_pixel,
			&cub->gun_img[4].line_length, &cub->gun_img[4].endian);
	return (1);
}
int	load_textures(t_cub *cub)
{

	int	i;

	i = 0;
	while (i < 4)
	{
		cub->text_img[i].mlx_img = mlx_xpm_file_to_image(cub->mlx, cub->text[i],
			       &cub->text_img[i].width, &cub->text_img[i].height);
		if(!cub->text_img[i].mlx_img)
			return(__putstr_fd("Failed to load texture\n", 2), 0);
		if (cub->text_img[i].width != cub->text_img[i].height)
			return(__putstr_fd("Not valid texture size\n", 2), 0);
		cub->text_img[i].addr = mlx_get_data_addr(cub->text_img[i].mlx_img, &cub->text_img[i].bits_per_pixel,
			   &cub->text_img[i].line_length, &cub->text_img[i].endian);
		i++;
	}
	if (BONUS)
	{
		cub->door_img.mlx_img = mlx_xpm_file_to_image(cub->mlx, cub->door,
			       &cub->door_img.width, &cub->door_img.height);
		if(!cub->door_img.mlx_img)
			return(__putstr_fd("Failed to load texture\n", 2), 0);
		if (cub->door_img.width != cub->door_img.height)
			return(__putstr_fd("Not valid texture size\n", 2), 0);
		cub->door_img.addr = mlx_get_data_addr(cub->door_img.mlx_img, &cub->door_img.bits_per_pixel,
			   &cub->door_img.line_length, &cub->door_img.endian);
		if(!load_gun(cub))
			return(__putstr_fd("Not valid gun sprites\n", 2), 0);
	}
	return (1);
}
