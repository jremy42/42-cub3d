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
	return (1);
}