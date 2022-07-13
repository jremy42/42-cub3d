#include "cub3d.h"
#include "mlx.h"
#include "math.h"


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

float square(float a)
{
	return (a * a);
}

float sq_dist(float x1, float y1, float x2, float y2)
{
	float dist_x;
	float dist_y;

	dist_x = square(x1 - x2);
	dist_y = square(y1 - y2);
	return (dist_x + dist_y);
}

int is_in_circle(float x, float y)
{
	float	distance;
	float	distance_sqrt;

	distance_sqrt = sqrtf(sq_dist(x, y, SIZE_PLAYER/2, SIZE_PLAYER/2));
	distance = distance_sqrt - 7;
	if (distance <= 0.00000000)
	{
		if (distance <= -1.00000000)
			return (1); // Inside
		return (2);		// Border
	}
	return (0);
}

void	player_square_put(t_img *img, int x, int y, int color)
{
	int		offset_y;
	int		offset_x;
	int		is_in;

	offset_y = 0;
	while (offset_y < SIZE_PLAYER)
	{
		offset_x = 0;
		while (offset_x < SIZE_PLAYER)
		{

			is_in = is_in_circle((float)offset_x, (float)offset_y);
			if (is_in)
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

int	render_frame(t_cub *cub)
{
	(void)cub;
	static size_t	next_frame = 0;
	static size_t	first_get_time = 0;
	size_t			current_time;

	current_time = __get_time();

	if (!next_frame)
		first_get_time = current_time;

	if (current_time >= next_frame)
	{		
		next_frame = current_time + 1000/FPS;
		__mouse_move(cub);
		load_background(cub);
		raycast(cub);
		update_minimap(cub);
		mlx_put_image_to_window(cub->mlx,cub->win, cub->screen.mlx_img, 0, 0);
		mlx_put_image_to_window(cub->mlx,cub->win, cub->minimap.mlx_img, 0, 0);
		//printf("next_frame = [%lu]\n", next_frame - first_get_time);
	}
	/*
	update_minimap(cub);
	mlx_put_image_to_window(cub->mlx,cub->win, cub->backgd.mlx_img, 0, 0);
	mlx_put_image_to_window(cub->mlx,cub->win, cub->screen.mlx_img, 0, 0);
	mlx_put_image_to_window(cub->mlx,cub->win, cub->minimap.mlx_img, 0, 0);
	*/
	return (1);
}
