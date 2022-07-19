#include "cub3d.h"
#include "mlx.h"
#include "keycodes.h"
#include "math.h"

void __move(t_cub *cub, float move_dir_x, float move_dir_y)
{
	float	next_pos_x;
	float	next_pos_y;
	char	type_pos;
	float	door_value;

	next_pos_x = cub->player.pos_x + (SPEED + (0.05 * SIZE_PLAYER/2)) * move_dir_x;
	next_pos_y = cub->player.pos_y + (SPEED + (0.05 * SIZE_PLAYER/2))* move_dir_y;
	// type_pos = cub->maps[(int)floor(next_pos_y)][(int)floor(next_pos_x)];
	// door_value = cub->door_map[(int)floor(next_pos_y)][(int)floor(next_pos_x)];
	type_pos = cub->maps[(int)floor(next_pos_y)][(int)floor(next_pos_x)];
	door_value = cub->door_map[(int)floor(next_pos_y)][(int)floor(next_pos_x)];
	
	printf("move_dir_x:[%f]\n", move_dir_x);
	printf("move_dir_y:[%f]\n", move_dir_y);
	printf("next_pos_x/y: [%f][%f]\n", next_pos_x, next_pos_y);
	printf("floor next_pos_x/y: [%d][%d]\n", (int)round(next_pos_x), (int)round(next_pos_y));

	if (type_pos == '0' || (type_pos == 'D' && door_value == 0.0f))
	{	
		cub->player.pos_x = next_pos_x;
		cub->player.pos_y = next_pos_y;
		return ;
	}
	type_pos = cub->maps[(int)floor(cub->player.pos_y)][(int)floor(next_pos_x)];
	door_value = cub->door_map[(int)floor(cub->player.pos_y)][(int)floor(next_pos_x)];
	if (type_pos == '0' || (type_pos == 'D' && door_value == 0.0f))
	{
		cub->player.pos_x = next_pos_x;
		return ;
	}
	type_pos = cub->maps[(int)floor(next_pos_y)][(int)floor(cub->player.pos_x)];
	door_value = cub->door_map[(int)floor(next_pos_y)][(int)floor(cub->player.pos_x)];
	if (type_pos == '0' || (type_pos == 'D' && door_value == 0.0f))
		cub->player.pos_y = next_pos_y;
}

int	print_vector(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < 9)
	{
		j = 0;
		while (j < 9)
		{
			if(cub->player.vector[i][j] == 42)
			{
				printf("\e[34m");
				printf("0 ");
				printf("\e[0m");
			}
			else if(cub->player.vector[i][j] > 0)
			{
				printf("\e[32m");
				printf("%d ",abs(cub->player.vector[i][j]));
				printf("\e[0m");
			}
			else if(cub->player.vector[i][j] < 0 )
			{
				printf("\e[33m");
				printf("%d ",abs(cub->player.vector[i][j]));
				printf("\e[0m");
			}
			else
				printf("0 ");
			j++;
		}
		printf("\n");
		i++;
	}
	return(printf("\n"));
}

int	print_coord_hit(t_cub *cub)
{
	int		hit;
	float	side_dist_x;
	float	side_dist_y;
	float	coord_x;
	float	coord_y;
	int		tab_coord_x;
	int		tab_coord_y;
	int		step_y;
	int		step_x;
	int		side;

	t_player	*p;
	p = &cub->player;
	if (p->dir_x > 0)
		step_x = 1;
	else
		step_x = -1;
	if (p->dir_y > 0)
		step_y = 1;
	else
		step_y = -1;

	side_dist_x = p->delta_dist_x;
	side_dist_y = p->delta_dist_y;

	coord_x = 0;
	coord_y = 0;
	hit = 0;

	__memset(p->vector, 0, sizeof(p->vector));

	p->vector[4][4] = 42;
	while (1)
	{
		//printf("side dist_x/side_dist_y : (%f:%f)\n", side_dist_x, side_dist_y);
		if (side_dist_x < side_dist_y)
		{
			//printf("next hit is on x side with %d\n", hit+1);
			coord_x += step_x;
			side_dist_x += p->delta_dist_x;
			side = -1;
		}
		else
		{
			//printf("next hit is on y side with %d\n", hit+1);
			coord_y += step_y;
			side_dist_y += p->delta_dist_y;
			side = 1;
		}
		tab_coord_x = (int)floor(coord_x);
		tab_coord_y = (int)floor(coord_y);
		if (tab_coord_x > 4 || tab_coord_y > 4 || tab_coord_x < -4 || tab_coord_y < - 4)
			break ;
		//printf("fill in %d:%d\n", tab_coord_x + 4, tab_coord_y + 4);
		p->vector[tab_coord_y + 4 ][tab_coord_x + 4 ] = (hit + 1) * side;
		hit++;
	}
	return(1);
}

void	update_slope(t_cub *cub)
{
	cub->player.slope_dir = cub->player.dir_y / cub->player.dir_x;
	cub->player.delta_dist_x = sqrt(1 + pow(cub->player.slope_dir,2));
	cub->player.delta_dist_y = sqrt(1 + pow(1/cub->player.slope_dir,2));
}

void	rotate(t_cub *cub, float angle)
{
	float	old_dir_x;
	float	old_dir_y;
	float	old_plane_x;
	float	old_plane_y;

	old_dir_x = cub->player.dir_x;
	old_dir_y = cub->player.dir_y;
	old_plane_x = cub->player.plane_x;
	old_plane_y = cub->player.plane_y;

	cub->player.dir_x = old_dir_x * cos(angle)
						-old_dir_y * sin(angle);
	cub->player.dir_y = old_dir_x * sin(angle)
						+old_dir_y * cos(angle);
	cub->player.plane_x = old_plane_x * cos(angle)
						-old_plane_y * sin(angle);
	cub->player.plane_y = old_plane_x * sin(angle)
						+old_plane_y * cos(angle);
	//cub->player.dir_norm = sqrt(pow(cub->player.dir_x, 2) + pow(cub->player.dir_y, 2));
	cub->player.plane_norm = sqrt(pow(cub->player.plane_x, 2) + pow(cub->player.plane_y, 2));
}

void	__hookleft(t_cub *cub)
{
	__move(cub, -cub->player.plane_x, -cub->player.plane_y);
	/*
	rotate(cub, -0.1f);
	update_slope(cub);
	*/
    (DEBUG == 2) && printf("left\n");
}

void	__hookright(t_cub *cub)
{
	__move(cub, cub->player.plane_x, cub->player.plane_y);
	/*
	rotate(cub, 0.1f);
	update_slope(cub);
	*/
    (DEBUG == 2) && printf("right\n");

}



void	__hookdown(t_cub *cub)
{
  	__move(cub, -cub->player.dir_x, -cub->player.dir_y);

	(DEBUG == 2) && printf("down\n");

}

void	__hookup(t_cub *cub)
{
  	__move(cub, cub->player.dir_x, cub->player.dir_y);
	(DEBUG == 2) && printf("up\n");

}

void load_background(t_cub *cub)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if(y < HEIGHT/2)
				my_mlx_pixel_put(&cub->screen,x, y, cub->ceiling.trgb);
			else
				my_mlx_pixel_put(&cub->screen, x, y, cub->floor.trgb);
			x++;
		}
		y++;
	}
}

void	__switch_door(t_cub *cub)
{
	int	x_try;
	int y_try;

	x_try = floor(cub->player.pos_x);
	y_try = floor(cub->player.pos_y);


	//if (cub->maps[y_try][x_try] == 'D' && cub->door_map[y_try][x_try] == 2.0f)
			//cub->door_map[y_try][x_try] = 1.99f;
	if (cub->maps[y_try - 1][x_try] == 'D' && cub->door_map[y_try - 1][x_try] == 2.0f)
			cub->door_map[y_try - 1][x_try] = 1.99f;
	if (cub->maps[y_try][x_try - 1] == 'D' && cub->door_map[y_try][x_try - 1] == 2.0f)
			cub->door_map[y_try][x_try - 1] = 1.99f;
	if (cub->maps[y_try - 1][x_try - 1] == 'D' && cub->door_map[y_try - 1][x_try - 1] == 2.0f)
			cub->door_map[y_try - 1][x_try - 1] = 1.99f;
	if (cub->maps[y_try + 1][x_try] == 'D' && cub->door_map[y_try + 1][x_try] == 2.0f)
			cub->door_map[y_try + 1][x_try] = 1.99f;
	if (cub->maps[y_try][x_try + 1] == 'D' && cub->door_map[y_try][x_try + 1] == 2.0f)
			cub->door_map[y_try][x_try + 1] = 1.99f;
	if (cub->maps[y_try + 1][x_try + 1] == 'D' && cub->door_map[y_try + 1][x_try + 1] == 2.0f)
			cub->door_map[y_try + 1][x_try + 1] = 1.99f;

	//if (cub->maps[y_try][x_try] == 'D' && cub->door_map[y_try][x_try] == 0.0f)
			//cub->door_map[y_try][x_try] = 0.01f;
	if (cub->maps[y_try - 1][x_try] == 'D' && cub->door_map[y_try - 1][x_try] == 0.0f)
			cub->door_map[y_try - 1][x_try] = 0.01f;
	if (cub->maps[y_try][x_try - 1] == 'D' && cub->door_map[y_try][x_try - 1] == 0.0f)
			cub->door_map[y_try][x_try - 1] = 0.01f;
	if (cub->maps[y_try - 1][x_try - 1] == 'D' && cub->door_map[y_try - 1][x_try - 1] == 0.0f)
			cub->door_map[y_try - 1][x_try - 1] = 0.01f;
	if (cub->maps[y_try + 1][x_try] == 'D' && cub->door_map[y_try + 1][x_try] == 0.0f)
			cub->door_map[y_try + 1][x_try] = 0.01f;
	if (cub->maps[y_try][x_try + 1] == 'D' && cub->door_map[y_try][x_try + 1] == 0.0f)
			cub->door_map[y_try][x_try + 1] = 0.01f;
	if (cub->maps[y_try + 1][x_try + 1] == 'D' && cub->door_map[y_try + 1][x_try + 1] == 0.0f)
			cub->door_map[y_try + 1][x_try + 1] = 0.01f;
	DEBUG && printf("open\n");
}

void	__update_door_value(t_cub *cub)
{
	int	x;
	int y;

	y = 0;

	while (cub->maps[y])
	{
		x = 0;
		while (cub->maps[y][x])
		{
			if (cub->maps[y][x] == 'D' && cub->door_map[y][x] < 2.0f && cub->door_map[y][x] >= 1.0f)
			{
				cub->door_map[y][x] -= 0.02f;
				if (cub->door_map[y][x] < 1.0f)
					cub->door_map[y][x] = 0.0f;
			}
			if (cub->maps[y][x] == 'D' && cub->door_map[y][x] <= 1.0f && cub->door_map[y][x] > 0.0f)
			{
				cub->door_map[y][x] += 0.02f;
				if (cub->door_map[y][x] > 1.0f)
					cub->door_map[y][x] = 2.0f;
			}
			x++;
		}
		y++;
	}
}

int	__key_release(int keycode, t_cub *cub)
{
	if (keycode == KEY_L || keycode == ARROW_LEFT)
		cub->action &= ~(1 << 0);
	if (keycode == KEY_D || keycode == ARROW_DOWN)
			cub->action &= ~(1 << 1);
	if (keycode == KEY_R || keycode == ARROW_RIGHT)
			cub->action &= ~(1 << 2);
	if (keycode == KEY_U || keycode == ARROW_UP)
			cub->action &= ~(1 << 3);
	if (keycode == SPACE_BAR)
			cub->action &= ~(1 << 4);
	return (1);
}

int	__key_press(int keycode, t_cub *cub)
{
	if (keycode == KEY_L || keycode == ARROW_LEFT)
		cub->action |= 1 << 0;
	if (keycode == KEY_D || keycode == ARROW_DOWN)
			cub->action |= 1 << 1;
	if (keycode == KEY_R || keycode == ARROW_RIGHT)
			cub->action |= 1 << 2;
	if (keycode == KEY_U || keycode == ARROW_UP)
			cub->action |= 1 << 3;
	if (keycode == SPACE_BAR)
			cub->action |= 1 << 4;
	cub->last_key_press = keycode;
	/*
	load_background(cub);
	raycast(cub);
	update_minimap(cub);
	mlx_put_image_to_window(cub->mlx,cub->win, cub->screen.mlx_img, 0, 0);
	
	mlx_put_image_to_window(cub->mlx,cub->win, cub->minimap.mlx_img, 0, 0);
	*/
	if (keycode == KEY_ESC)
		return (__quit(cub));
	return (1);
}
