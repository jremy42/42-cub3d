#include "cub3d.h"
#include "mlx.h"




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
	}
	return (1);
}