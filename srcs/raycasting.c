#include "cub3d.h"
#include "mlx.h"
#include "math.h"

int	print_ray_info(t_cub *cub)
{
	printf("cam_x coeff : %f\n", cub->player.cam_x);
	printf("r_dir_x/r_dir_y : %f:%f\n", cub->player.r_dir_x, cub->player.r_dir_y);
	printf("r_slope : %f\n", cub->player.r_slope_dir);
	printf("r_delta_dist_x/r_delta_dist_y : %f:%f\n", cub->player.r_delta_dist_x, cub->player.r_delta_dist_y);
	return (1);
}

void	calculate_ray_features(t_player *player, int x)
{
	player->cam_x = (2 * x / (float)WIDTH) - 1;
	player->r_dir_x = player->dir_x + player->plane_x * player->cam_x;
	player->r_dir_y = player->dir_y + player->plane_y * player->cam_x;
	player->r_slope_dir = player->r_dir_y / player->r_dir_x;
	player->r_delta_dist_x = sqrt(1 + pow(player->r_slope_dir,2));
	player->r_delta_dist_y = sqrt(1 + pow(1/player->r_slope_dir,2));
}

void	init_step_and_side_dist(t_player *player)
{
	player->r_map_x = (int)floor(player->pos_x);
	player->r_map_y = (int)floor(player->pos_y);
	if (player->r_dir_x < 0)	
	{
		player->r_step_x = -1;
		player->r_side_dist_x = (player->pos_x - player->r_map_x) * player->r_delta_dist_x;
	}
	else
	{
		player->r_step_x = 1;
		player->r_side_dist_x = (player->r_map_x + 1 - player->pos_x) * player->r_delta_dist_x;
	}
	if (player->r_dir_y < 0)	
	{
		player->r_step_y = -1;
		player->r_side_dist_y = (player->pos_y - player->r_map_y) * player->r_delta_dist_y;
	}
	else
	{
		player->r_step_y = 1;
		player->r_side_dist_y = (player->r_map_y + 1 - player->pos_y) * player->r_delta_dist_y;
	}
}

int	dda(t_player *player, char **map)
{
	int	hit;

	hit = 0;
	while (!hit)
	{	
		if (player->r_side_dist_x < player->r_delta_dist_y)
		{
			player->r_side_dist_x += player->r_delta_dist_x;
			player->r_map_x += player->r_step_x;
			player->r_side_hit = X_HIT;
		}
		else
		{
			player->r_side_dist_y += player->r_delta_dist_y;
			player->r_map_y += player->r_step_y;
			player->r_side_hit = Y_HIT;
		}
		if(map[player->r_map_y][player->r_map_x] == '1')
			hit = 1;
	}
	return (hit);
}
int	raycast(t_cub *cub)
{
	int	x;

	x = -1;
	while (++x < WIDTH)
	{
		calculate_ray_features(&cub->player, x);
		//DEBUG && print_ray_info(cub);	
		init_step_and_side_dist(&cub->player);
		dda(&cub->player, cub->maps);
	}
	printf("dda done for x\n");
	return (0);
}