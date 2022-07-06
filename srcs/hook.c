
#include "cub3d.h"
#include "mlx.h"
#include "keycodes.h"

void	__hookleft(t_cub *cub)
{
    (void)cub;

    DEBUG && printf("left\n");
}

void	__hookright(t_cub *cub)
{
    (void)cub;
        cub->player.dir_x -= ROTATE_ANGLE;
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
	DEBUG && print_debug_info(cub);
	DEBUG && printf("Key pressed [%d]\n", keycode);
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
	if (keycode == KEY_ESC)
		return (__quit(cub));
	return (1);
}
