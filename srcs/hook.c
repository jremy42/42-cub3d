
#include "cub3d.h"
#include "mlx.h"

void	__hookleft(t_cub *cub)
{
    (void)cub;
    fprintf(stderr,"left\n");
}

void	__hookright(t_cub *cub)
{
    (void)cub;
    fprintf(stderr,"right\n");

}

void	__hookdown(t_cub *cub)
{
    (void)cub;
    fprintf(stderr,"down\n");

}

void	__hookup(t_cub *cub)
{
	(void)cub;
    fprintf(stderr,"up\n");
}

int	hooking(int keycode, t_cub *cub)
{
	void	(*f_hook[4])(t_cub *cub);

	f_hook[UP] = __hookup;
	f_hook[DOWN] = __hookdown;
	f_hook[LEFT] = __hookleft;
	f_hook[RIGHT] = __hookright;
	
	if (keycode == 0 || keycode == 123)
		f_hook[LEFT](cub);
	if (keycode == 1 || keycode == 125)
		f_hook[DOWN](cub);
	if (keycode == 2 || keycode == 124)
		f_hook[RIGHT](cub);
	if (keycode == 13 || keycode == 126)
		f_hook[UP](cub);
	if (keycode == 53)
		exit(1);    // <- a modifier
	return (0);
}
