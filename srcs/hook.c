
#include "cub3d.h"
#include "mlx.h"
#include "keycodes.h"
#include "math.h"

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
	DEBUG && print_debug_info(cub);
	DEBUG && printf("Key pressed [%d]\n", keycode);
	if (keycode == KEY_ESC)
		return (__quit(cub));
	return (1);
}
