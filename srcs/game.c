/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <{fle-blay}@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 10:10:34 by fle-blay          #+#    #+#             */
/*   Updated: 2022/07/19 10:10:54 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	get_color_from_sprite(int y, int x, t_img *img, t_cub *cub)
{
	char	*dst;

	(void)cub;
	// check x value;
	y /= SIZE_WEAPON;
	x /= SIZE_WEAPON;
	//if (cub->player.r_side_hit == X_HIT)
	//printf("x = [%d] [%d]\n",x,y);
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel /8));
	//(DEBUG == 3)  && printf("x : [%d], y : [%d] step : [%f] r_hit_coef : [%f] img->width [%d]\n", x , y, step, r_hit_coef, img->width);
	return(*(unsigned int*)dst);
}

void draw_gun(t_cub *cub)
{
	int x;
	int y;
	int color;
	int offset_x;
	int offset_y;

	y = 0;
	if (cub->gun_animate != 0)
		cub->gun_current_sprite++;
	if (cub->gun_current_sprite > 4*2)
	{
		cub->gun_animate = 0;
		cub->gun_current_sprite = 0;
	}
	offset_x = (WIDTH - cub->gun_img[(cub->gun_current_sprite/2)%5].width * SIZE_WEAPON)/2;
	offset_y = (HEIGHT - cub->gun_img[(cub->gun_current_sprite/2)%5].height * SIZE_WEAPON);
	while (y < cub->gun_img[(cub->gun_current_sprite/2)%5].height * SIZE_WEAPON - 1)
	{
		x = 0;
		while(x < cub->gun_img[(cub->gun_current_sprite/2)%5].width * SIZE_WEAPON - 1)
		{
			color = get_color_from_sprite(y, x, &(cub->gun_img[(cub->gun_current_sprite/2)%5]), cub);
			if (color >= 0)
				my_mlx_pixel_put(&cub->screen, x +  offset_x, y + offset_y, color);
			x++;
		}
		y++;
	}
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
	(DEBUG == 2) && printf("Rendering : time ok\n");
	if (current_time >= next_frame)
	{		
		clear_screen();
		while (++i < 5)
		{
			if (cub->action & (1 << i))
				cub->hook_fx[i](cub);
		}
		DEBUG && print_coord_hit(cub);
		DEBUG && print_vector(cub);
		DEBUG && print_debug_info(cub);
		DEBUG && print_sprite_info(&cub->sprite1);
		DEBUG && printf("last key pressed : [%d]\n", cub->last_key_press);
		next_frame = current_time + 1000/FPS;
		__update_door_value(cub);
		__mouse_move(cub);
		load_background(cub);
		(DEBUG == 3) && printf("Rendering : background ok\n");
		raycast(cub);
		calculate_sprite_info(cub, &cub->sprite1);
		draw_sprite(cub, &cub->sprite1);
		if (cub->gun_animate == 1 && cub->sprite1.gun_hit)
		{
			cub->sprite1.do_not_display = 1;
			cub->maps[(int)cub->sprite1.pos_y][(int)cub->sprite1.pos_x] = '0';
		}
		(DEBUG == 3) && printf("Rendering : raycasting ok\n");
		update_minimap(cub);
		(DEBUG == 3) && printf("Rendering : minimap ok\n");
		draw_gun(cub);
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
