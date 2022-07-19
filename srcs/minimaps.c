#include <math.h>
#include "cub3d.h"
#include "mlx.h"


float sq_dist(float x1, float y1, float x2, float y2)
{
	float dist_x;
	float dist_y;

	dist_x = pow(x1 - x2, 2);
	dist_y = pow(y1 - y2, 2);
	return (dist_x + dist_y);
}

int is_in_circle(float x, float y)
{
	float	distance;
	float	distance_sqrt;

	distance_sqrt = sqrtf(sq_dist(x, y, SIZE_PLAYER/2, SIZE_PLAYER/2));
	distance = distance_sqrt - 3;
	if (distance <= 0.0)
	{
		if (distance <= -1.0)
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
				my_mlx_pixel_put(img, x + offset_x, y + offset_y, color);
			offset_x++;
		}
		offset_y++;	
	}
}

void    draw_minimap(t_cub *cub, int pixel_x, int pixel_y)
{
    float x;
    float y;

    x = cub->player.pos_x - ((1.0f/SIZE_MINI_MAP) * (cub->minimap_width/2 - pixel_x));
    y = cub->player.pos_y - ((1.0f/SIZE_MINI_MAP) * (cub->minimap_height/2 - pixel_y));
    if(x < 0 || y < 0)
    {
        my_mlx_pixel_put(&cub->minimap, pixel_x, pixel_y, MINIMAP_EMPTY_COLOR);
        return ;
    }
    if ((int)y > size_split(cub->maps) - 1)
    {
        my_mlx_pixel_put(&cub->minimap, pixel_x, pixel_y, MINIMAP_EMPTY_COLOR);
        return;
    }
    if ((int)floor(x) > (int)__strlen(cub->maps[(int)floor(y)]) - 1)
        my_mlx_pixel_put(&cub->minimap, pixel_x, pixel_y, MINIMAP_EMPTY_COLOR);
    else
    {
       
        if (cub->maps[(int)floor(y)][(int)floor(x)] == '1')
            my_mlx_pixel_put(&cub->minimap, pixel_x, pixel_y, MINIMAP_WALL_COLOR);
        if (cub->maps[(int)floor(y)][(int)floor(x)] == 'D')
            my_mlx_pixel_put(&cub->minimap, pixel_x, pixel_y, MINIMAP_DOOR_COLOR);
		 if (cub->maps[(int)floor(y)][(int)floor(x)] == '0' || cub->maps[(int)floor(y)][(int)floor(x)] == 'G')
            my_mlx_pixel_put(&cub->minimap, pixel_x, pixel_y, MINIMAP_GROUND_COLOR);
    }
}

void	update_minimap(t_cub *cub)
{
	int	pixel_x;
	int	pixel_y;

	pixel_y = 0;

    while (pixel_y < cub->minimap_height - 1)
    {
        pixel_x = 0;
        while (pixel_x < cub->minimap_width - 1)
        {
            draw_minimap(cub, pixel_x, pixel_y);
            // my_mlx_pixel_put(&cub->minimap, pixel_x, pixel_y, X_HIT_COLOR);
            pixel_x++;
        }
        pixel_y++;
    }
    //printf("width heigth player [%d]/[%d]\n", (cub->minimap_width)/2 -4, (cub->minimap_height)/2 -4);
    player_square_put(&cub->minimap, cub->minimap_width /2 - 4, cub->minimap_height/2 - 4, MINIMAP_PLAYER_COLOR);
	// while (cub->maps[y])
	// {
	// 	x = 0;
	// 	while (cub->maps[y][x])
	// 	{

	// 		if (cub->maps[y][x] == ' ')
	// 			minimap_square_put(&cub->minimap, x, y, 0xFF << 16);
	// 		if (cub->maps[y][x] == '1')
	// 			minimap_square_put(&cub->minimap, x, y, 0xFF << 8);
	// 		if (cub->maps[y][x] == '0' || cub->maps[y][x] == 'N')
	// 			minimap_square_put(&cub->minimap, x, y, 0xFF << 0);
	// 		if ((int)cub->player.pos_x == x && (int)cub->player.pos_y == y)
	// 			player_square_put(&cub->minimap, x, y, 0xFFaef8);
	// 		x++;
	// 	}
	// 	y++;
	// }
}
