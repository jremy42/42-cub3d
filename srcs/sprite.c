/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deus <deus@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 12:45:23 by deus              #+#    #+#             */
/*   Updated: 2022/07/25 15:43:32 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "math.h"

static void	calculate_draw_info(t_cub *cub, t_sprite *sprite)
{
	sprite->screen_x_start = sprite->screen_x - sprite->screen_width / 2;
	sprite->screen_x_end = sprite->screen_x + sprite->screen_width / 2;
	sprite->screen_y_start = HEIGHT / 2
		+ sprite->offset_y - sprite->screen_height / 2;
	sprite->screen_y_end = HEIGHT / 2
		+ sprite->offset_y + sprite->screen_height / 2;
	get_sprite_frame(sprite);
	if (sprite->current_frame == 3 && ((sprite->count_animate) % 15 > 7))
		cub->hit_by_guard = 1 * (sprite->animate == 1);
}

static void	calculate_sprite_info(t_cub *cub, t_sprite *sprite)
{
	sprite->cam_pos_x = sprite->pos_x - cub->player.pos_x;
	sprite->cam_pos_y = sprite->pos_y - cub->player.pos_y;
	sprite->norm = sqrt(pow(sprite->cam_pos_x, 2) + pow(sprite->cam_pos_y, 2));
	sprite->plane_proj = vector_dot(sprite->cam_pos_x, sprite->cam_pos_y,
			cub->player.plane_x, cub->player.plane_y) / cub->player.plane_norm;
	sprite->dir_proj = vector_det(sprite->cam_pos_x, sprite->cam_pos_y,
			cub->player.plane_x, cub->player.plane_y) / cub->player.plane_norm;
	sprite->screen_x = (WIDTH / 2) * (1 + sprite->plane_proj
			/ (sprite->dir_proj * cub->player.plane_norm));
	sprite->offset_y = ((*sprite->sprite_img_tab)[sprite->current_frame].height
			/ sprite->dir_proj) * cub->player.plane_norm;
	sprite->screen_height = (HEIGHT / (sprite->norm * 1.2f));
	sprite->screen_width = sprite->screen_height
		* ((float)(*sprite->sprite_img_tab)[sprite->current_frame].width
			/ (*sprite->sprite_img_tab)[sprite->current_frame].height);
	sprite->to_show = (sprite->dir_proj > 0);
	calculate_draw_info(cub, sprite);
}

void	calculate_all_sprite_info(t_cub *cub)
{
	int	i;

	i = -1;
	while (++i < cub->sprite_count)
	{
		calculate_sprite_info(cub, &cub->sprite_tab[i]);
		(DEBUG == 2) && print_sprite_info(&cub->sprite_tab[i]);
		cub->sprite_order[i] = i;
	}
}

static void	update_death_guard_info(t_cub *cub, t_sprite *s)
{
	s->animate = 2;
	s->count_animate = 0;
	cub->maps[(int)floor(s->pos_y)][(int)floor(s->pos_x)] = '0';
}

void	handle_sprite(t_cub *cub)
{
	int	i;
	int	true_sprite;
	int	to_kill;

	i = cub->sprite_count - 1;
	to_kill = -1;
	while (i >= 0)
	{
		true_sprite = cub->sprite_order[i];
		if (cub->sprite_tab[true_sprite].dir_proj >= 0)
			draw_sprite(cub, &cub->sprite_tab[true_sprite]);
		if (cub->gun_frame == 1 && cub->sprite_tab[true_sprite].gun_hit
			&& cub->sprite_tab[true_sprite].animate < 2)
			to_kill = true_sprite;
		if (!cub->sprite_tab[true_sprite].to_show
			&& cub->sprite_tab[true_sprite].animate < 2)
		{
			cub->sprite_tab[true_sprite].animate = 0;
			cub->sprite_tab[true_sprite].count_animate = 0;
		}
		i--;
	}
	if (to_kill >= 0)
		update_death_guard_info(cub, &cub->sprite_tab[to_kill]);
}
