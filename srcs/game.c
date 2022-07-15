#include "cub3d.h"
#include "mlx.h"
#include "math.h"


void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	(DEBUG == 3) && printf("x : [%d], y : [%d]\n", x, y);
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel /8));
	*(unsigned int*)dst = color;
}



int	render_frame(t_cub *cub)
{
	static size_t	next_frame = 0;
	size_t			current_time;
	int				i;

	i = -1;
	current_time = __get_time();

	//if (!next_frame)
	//	first_get_time = current_time;
	//printf("current time =  %lu\n", current_time);
	DEBUG && printf("Rendering : time ok\n");
	if (current_time >= next_frame)
	{
		while (++i < 5)
		{
			if (cub->action & (1 << i))
				cub->hook_fx[i](cub);
		}
		calculate_sprite_info(cub, &cub->sprite1);
		DEBUG && print_sprite_info(&cub->sprite1);
		next_frame = current_time + 1000/FPS;
		__update_door_value(cub);
		//__mouse_move(cub);
		load_background(cub);
		(DEBUG == 3) && printf("Rendering : background ok\n");
		raycast(cub);
		(DEBUG == 3) && printf("Rendering : raycasting ok\n");
		update_minimap(cub);
		(DEBUG == 3) && printf("Rendering : minimap ok\n");
		mlx_put_image_to_window(cub->mlx,cub->win, cub->screen.mlx_img, 0, 0);
		mlx_put_image_to_window(cub->mlx,cub->win, cub->minimap.mlx_img, 0, 0);
		//printf("next_frame = [%lu]\n", next_frame - first_get_time);
	}
	// exit(0);
	/*
	update_minimap(cub);
	mlx_put_image_to_window(cub->mlx,cub->win, cub->backgd.mlx_img, 0, 0);
	mlx_put_image_to_window(cub->mlx,cub->win, cub->screen.mlx_img, 0, 0);
	mlx_put_image_to_window(cub->mlx,cub->win, cub->minimap.mlx_img, 0, 0);
	*/
	return (1);
}
