/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_key_action.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 13:13:45 by fle-blay          #+#    #+#             */
/*   Updated: 2022/07/25 13:14:07 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "keycodes.h"
#include "math.h"

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
	if (keycode == KEY_ESC)
		return (__quit(cub));
	return (1);
}
