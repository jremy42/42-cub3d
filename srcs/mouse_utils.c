/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <fle-blay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 17:35:30 by fle-blay          #+#    #+#             */
/*   Updated: 2022/07/26 17:40:46 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

#ifdef __linux__

int	center_mouse(t_cub *cub)
{
	mlx_mouse_move(cub->mlx, cub->win, WIDTH / 2, HEIGHT / 2);
	return (1);
}

void	wrapper_mouse_get_pos(t_cub *cub, int *x, int *y)
{
	mlx_mouse_get_pos(cub->mlx, cub->win, x, y);
}

#endif
#ifdef __MACH__

int	center_mouse(t_cub *cub)
{
	mlx_mouse_move(cub->win, WIDTH / 2, HEIGHT / 2);
	return (1);
}

void	wrapper_mouse_get_pos(t_cub *cub, int *x, int *y)
{
	mlx_mouse_get_pos(cub->win, x, y);
}

#endif

