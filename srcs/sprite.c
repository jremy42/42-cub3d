#include "cub3d.h"
#include "mlx.h"
#include "math.h"

float	vector_det(float u_x, float u_y, float v_x, float v_y)
{
	return (u_x * v_y - u_y * v_x);
}

float	vector_dot(float u_x, float u_y, float v_x, float v_y)
{
	return (u_x * v_x + u_y * v_y);
}

int	get_color_from_mlx_img(int x, int y, t_img *img)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel /8));
	return(*(unsigned int*)dst);
}

void 	draw_sprite(t_cub *cub, t_sprite *s)
{
	int		color;
	int		y;
	int		x;
	int		true_x;
	int		true_y;
	

	color = 0;
	x = s->screen_x_start- 1;
	if (s->do_not_display)
	{
		s->gun_hit = 0;
		return ;
	}
	while (++x < WIDTH && x < s->screen_x_end)
	{
		true_x = (x - s->screen_x_start )* s->sprite_img.width / s->screen_width; 
		if (x < 0)
			continue ;

		y = s->screen_y_start - 1;
		while (++y < HEIGHT && y < s->screen_y_end)
		{
			true_y = (y - s->screen_y_start) * s->sprite_img.height / s->screen_height; 
			if (y < 0)
				continue ;
			if (s->to_show && cub->player.perp_wall_dist[x] > s->dir_proj)
			// v3 OK ! if (s->to_show && cub->player.true_wall_dist[x] > s->dir_proj)
			// v2 if (s->to_show && cub->player.perp_wall_dist[x] > s->dir_proj)
			// v1 if (s->to_show && cub->player.perp_wall_dist[x] > s->norm)
			{
				color = get_color_from_mlx_img(true_x, true_y, &s->sprite_img);
				if (color >= 0)
					my_mlx_pixel_put(&cub->screen, x, y, color);
				if (x == WIDTH/2 && y == HEIGHT/2 && color >= 0)
					s->gun_hit = 1;
				else if (x == WIDTH/2 && y == HEIGHT/2)
					s->gun_hit = 0;
			}
		}
	}
}

void	calculate_sprite_info(t_cub *cub, t_sprite *sprite)
{
	if (sprite->do_not_display)
		return ;
	sprite->cam_pos_x = sprite->pos_x - cub->player.pos_x;
	sprite->cam_pos_y = sprite->pos_y - cub->player.pos_y;
	sprite->norm = sqrt(pow(sprite->cam_pos_x, 2) + pow(sprite->cam_pos_y, 2));
	sprite->plane_proj = vector_dot(sprite->cam_pos_x, sprite->cam_pos_y, cub->player.plane_x, cub->player.plane_y) / cub->player.plane_norm;
	sprite->dir_proj = vector_det(sprite->cam_pos_x, sprite->cam_pos_y, cub->player.plane_x, cub->player.plane_y) / cub->player.plane_norm;
	sprite->screen_x = (WIDTH/2) * (1 + sprite->plane_proj/(sprite->dir_proj * cub->player.plane_norm));
	// v2 sprite->screen_x = (WIDTH/2) * (1 + sprite->plane_proj/sprite->dir_proj);
	// v1 sprite->screen_x = (WIDTH/2) * (1 + sprite->plane_proj/sprite->norm);
	sprite->offset_y = (sprite->sprite_img.height/sprite->dir_proj) * cub->player.plane_norm;
	// v2 moyen OKsprite->offset_y = (sprite->sprite_img.height/sprite->norm) / cub->player.plane_norm;
	// v1 sprite->offset_y = (sprite->sprite_img.height/sprite->norm);
	sprite->screen_height = (HEIGHT / (sprite->norm * 1.2f));
	//sprite->screen_height = (HEIGHT / (sprite->norm * 1.2f));
	sprite->screen_width = sprite->screen_height * ((float)sprite->sprite_img.width/sprite->sprite_img.height);
	sprite->to_show = (sprite->dir_proj > 0);
	sprite->screen_x_start = sprite->screen_x - sprite->screen_width/2;
	sprite->screen_x_end = sprite->screen_x + sprite->screen_width/2;
	sprite->screen_y_start = HEIGHT/2 + sprite->offset_y - sprite->screen_height/2;
	sprite->screen_y_end = 	HEIGHT/2 + sprite->offset_y + sprite->screen_height/2;
}
	

int		print_sprite_info(t_sprite *sprite)
{
	printf("world pos_x/pos_y : [%f/%f]\n", sprite->pos_x, sprite->pos_y);
	printf("cam pos_x/pos_y : [%f/%f]\n", sprite->cam_pos_x, sprite->cam_pos_y);
	printf("norm/dir_proj/plane_proj : [%f/%f/%f]\n", sprite->norm, sprite->dir_proj, sprite->plane_proj);
	printf("screen_x/screen_height/screen_width/to_show : [%d/%d/%d/%d]\n", sprite->screen_x, sprite->screen_height,sprite->screen_width, sprite->to_show);
	printf(" screen_x_start/end: [%d][%d]\n", sprite->screen_x_start, sprite->screen_x_end);
	printf(" screen_y_start/end: [%d][%d]\n", sprite->screen_y_start, sprite->screen_y_end);
	printf("gun hit = [%d]\n", sprite->gun_hit);
	return (1);
}

void	update_sprite_order(t_cub *cub, t_sprite *s_tab, int s_count, int *s_order)
{
	int	i;
	int	j;
	int	tmp;

	i = -1;
	while (++i < s_count)
	{
		calculate_sprite_info(cub, &s_tab[i]);
		s_order[i] = i;
	}
	i = 0;
	while (i < s_count)
	{
		j = i + 1;
		while (j < s_count)
		{
			if (s_tab[s_order[j]].norm < s_tab[s_order[i]].norm)
			{
				tmp = s_order[i];
				s_order[i] = s_order[j];
				s_order[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
