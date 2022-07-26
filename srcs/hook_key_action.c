/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_key_action.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deus <deus@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 13:13:45 by fle-blay          #+#    #+#             */
/*   Updated: 2022/07/26 11:19:44 by deus             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "keycodes.h"
#include "math.h"

int	__key_release(int keycode, t_cub *cub)
{
	if (keycode == KEY_A)
		cub->action &= ~(1 << 0);
	if (keycode == KEY_S || keycode == ARROW_DOWN)
		cub->action &= ~(1 << 1);
	if (keycode == KEY_D)
		cub->action &= ~(1 << 2);
	if (keycode == KEY_W || keycode == ARROW_UP)
		cub->action &= ~(1 << 3);
	if (keycode == SPACE_BAR)
		cub->action &= ~(1 << 4);
	if (keycode == ARROW_LEFT)
		cub->action &= ~(1 << 5);
	if (keycode == ARROW_RIGHT)
		cub->action &= ~(1 << 6);
	return (1);
}

int	__key_press(int keycode, t_cub *cub)
{
	if (keycode == KEY_A)
		cub->action |= 1 << 0;
	if (keycode == KEY_S || keycode == ARROW_DOWN)
		cub->action |= 1 << 1;
	if (keycode == KEY_D)
		cub->action |= 1 << 2;
	if (keycode == KEY_W || keycode == ARROW_UP)
		cub->action |= 1 << 3;
	if (keycode == SPACE_BAR)
		cub->action |= 1 << 4;
	if (keycode == ARROW_LEFT)
		cub->action |= 1 << 5;
	if (keycode == ARROW_RIGHT)
		cub->action |= 1 << 6;
	cub->last_key_press = keycode;
	if (keycode == KEY_ESC)
		return (__quit(cub, 0), 1);
	return (1);
}
