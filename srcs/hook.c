
#include "cub3d.h"
#include "mlx.h"
#include "keycodes.h"
#include "math.h"

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
		printf("side dist_x/side_dist_y : (%f:%f)\n", side_dist_x, side_dist_y);
		if (side_dist_x < side_dist_y)
		{
			printf("next hit is on x side with %d\n", hit+1);
			coord_x += step_x;
			side_dist_x += p->delta_dist_x;
			side = -1;
		}
		else
		{
			printf("next hit is on y side with %d\n", hit+1);
			coord_y += step_y;
			side_dist_y += p->delta_dist_y;
			side = 1;
		}
		tab_coord_x = (int)floor(coord_x);
		tab_coord_y = (int)floor(coord_y);
		if (tab_coord_x > 4 || tab_coord_y > 4 || tab_coord_x < -4 || tab_coord_y < - 4)
			break ;
		printf("fill in %d:%d\n", tab_coord_x + 4, tab_coord_y + 4);
		p->vector[tab_coord_y + 4 ][tab_coord_x + 4 ] = (hit + 1) * side;
		hit++;
	}
	return(printf("End of loop\n"));
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
}

void	__hookleft(t_cub *cub)
{
	rotate(cub, -ROTATE_ANGLE);
	update_slope(cub);
    DEBUG && printf("left\n");
}

void	__hookright(t_cub *cub)
{
	rotate(cub, ROTATE_ANGLE);
	update_slope(cub);
    DEBUG && printf("right\n");

}

void	__hookdown(t_cub *cub)
{
    cub->player.pos_x -= SPEED * cub->player.dir_x;
    cub->player.pos_y -= SPEED * cub->player.dir_y;
    DEBUG && printf("down\n");

}

void	__hookup(t_cub *cub)
{
	(void)cub;
    cub->player.pos_x += SPEED * cub->player.dir_x;
    cub->player.pos_y += SPEED * cub->player.dir_y;
    DEBUG && printf("up\n");
}

int	__key_press(int keycode, t_cub *cub)
{
    void	(*f_hook[4])(t_cub *cub);

    clear_screen();
	f_hook[UP] = __hookup;
	f_hook[DOWN] = __hookdown;
	f_hook[LEFT] = __hookleft;
	f_hook[RIGHT] = __hookright;
	if (keycode == KEY_L || keycode == 123)
		f_hook[LEFT](cub);
	if (keycode == KEY_D || keycode == 125)
		f_hook[DOWN](cub);
	if (keycode == KEY_R || keycode == 124)
		f_hook[RIGHT](cub);
	if (keycode == KEY_U || keycode == 126)
		f_hook[UP](cub);
	DEBUG && print_coord_hit(cub);
	DEBUG && print_vector(cub);
	DEBUG && print_debug_info(cub);
	DEBUG && printf("Key pressed [%d]\n", keycode);
	if (keycode == KEY_ESC)
		return (__quit(cub));
	return (1);
}
