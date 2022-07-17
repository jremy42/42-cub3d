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

void	calculate_sprite_info(t_cub *cub, t_sprite *sprite)
{
	sprite->cam_pos_x = sprite->pos_x - cub->player.pos_x;
	sprite->cam_pos_y = sprite->pos_y - cub->player.pos_y;
	sprite->norm = sqrt(pow(sprite->cam_pos_x, 2) + pow(sprite->cam_pos_y, 2));
	sprite->plane_proj = vector_dot(sprite->cam_pos_x, sprite->cam_pos_y, cub->player.plane_x, cub->player.plane_y) / cub->player.plane_norm;
	sprite->dir_proj = vector_det(sprite->cam_pos_x, sprite->cam_pos_y, cub->player.plane_x, cub->player.plane_y) / cub->player.plane_norm;
}

int		print_sprite_info(t_sprite *sprite)
{
	printf("world pos_x/pos_y : [%d/%d]\n", sprite->pos_x, sprite->pos_y);
	printf("cam pos_x/pos_y : [%f/%f]\n", sprite->cam_pos_x, sprite->cam_pos_y);
	printf("norm/dir_proj/plane_proj : [%f/%f/%f]\n", sprite->norm, sprite->dir_proj, sprite->plane_proj);
	return (1);
}
