#include "cub3d.h"
#include "mlx.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel /8));
	*(unsigned int*)dst = color;
}

void	minimap_square_put(t_img *img, int x, int y, int color)
{
	int		offset_y;
	int		offset_x;

	offset_x = 0;
	offset_y = 0;
	while (offset_y < SIZE_MINI_MAP)
	{
		offset_x = 0;
		while (offset_x < SIZE_MINI_MAP)
		{
			my_mlx_pixel_put(img, x * SIZE_MINI_MAP + offset_x, y * SIZE_MINI_MAP + offset_y, color);
			offset_x++;
		}
		offset_y++;	
	}
}

void	player_square_put(t_img *img, int x, int y, int color)
{
	int		offset_y;
	int		offset_x;

	offset_x = 0;
	offset_y = 0;
	while (offset_y < SIZE_PLAYER)
	{
		offset_x = 0;
		while (offset_x < SIZE_PLAYER)
		{
			my_mlx_pixel_put(img, x * SIZE_MINI_MAP + offset_x, y * SIZE_MINI_MAP + offset_y, color);
			offset_x++;
		}
		offset_y++;	
	}
}

void	update_minimap(t_cub *cub)
{
	int	x;
	int	y;

	y = 0;
	while (cub->maps[y])
	{
		x = 0;
		while (cub->maps[y][x])
		{
			if (cub->maps[y][x] == ' ')
				minimap_square_put(&cub->minimap, x, y, 0xFF << 16);
			if (cub->maps[y][x] == '1')
				minimap_square_put(&cub->minimap, x, y, 0xFF << 8);
			if (cub->maps[y][x] == '0' || cub->maps[y][x] == 'N')
				minimap_square_put(&cub->minimap, x, y, 0xFF << 0);
			if ((int)cub->player.pos_x == x && (int)cub->player.pos_y == y)
				player_square_put(&cub->minimap, x, y, 0xFFaef8);
			x++;
		}
		y++;
	}
}

int	game(t_cub *cub)
{
	(void)cub;
	/*
	update_minimap(cub);
	mlx_put_image_to_window(cub->mlx,cub->win, cub->backgd.mlx_img, 0, 0);
	mlx_put_image_to_window(cub->mlx,cub->win, cub->screen.mlx_img, 0, 0);
	mlx_put_image_to_window(cub->mlx,cub->win, cub->minimap.mlx_img, 0, 0);
	*/
	return (1);
}
