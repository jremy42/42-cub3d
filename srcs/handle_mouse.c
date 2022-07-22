/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deus <deus@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 14:35:04 by jremy             #+#    #+#             */
/*   Updated: 2022/07/22 17:31:54 by deus             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"
#include "mlx.h"
#include "keycodes.h"
#include "math.h"

int	__mouse_hook(int button, int x, int y, t_cub *cub)
{
	printf("button pressed : [%d]\n", button);
	printf("Mouse coordinates x/y : (%d:%d)\n", x, y);
	printf("cub player = %p\n", &cub->player);
	printf("cub player.fov = %f\n", cub->player.fov);
	if (button == SCROLL_UP)
	{
		cub->player.fov += 0.05;
	}
	if (button == SCROLL_DOWN)
	{
		cub->player.fov -= 0.05;
	}
	if (button == 1)
		cub->gun_animate = 1;
	cub->player.plane_x = (-cub->player.dir_y) * cub->player.fov;
	cub->player.plane_y = cub->player.dir_x * cub->player.fov;
	return (1);
}

#ifdef __linux__

int	__mouse_move(t_cub *cub)
{
	int	x;
	int	y;

	x = WIDTH / 2;
	y = 0;
	y++;
	mlx_mouse_get_pos(cub->mlx, cub->win, &x, &y);
	if (x != WIDTH / 2)
		rotate(cub, ((ROTATE_ANGLE) * 0.02 * (x - WIDTH / 2)));
	else
		return (1);
	update_slope(cub);
	mlx_mouse_move(cub->mlx, cub->win, WIDTH / 2, HEIGHT / 2);
	return (1);
}
#endif

#ifdef __MACH__

int	__mouse_move(t_cub *cub)
{
	int	x;
	int	y;

	x = WIDTH / 2;
	y = 0;
	y++;
	mlx_mouse_get_pos(cub->win, &x, &y);
	if (x != WIDTH / 2)
		rotate(cub, ((ROTATE_ANGLE) * 0.02 * (x - WIDTH / 2)));
	else
		return (1);
	update_slope(cub);
	mlx_mouse_move(cub->win, WIDTH / 2, HEIGHT / 2);
	return (1);
}
#endif
