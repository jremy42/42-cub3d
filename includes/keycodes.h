/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycodes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deus <deus@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 10:17:20 by fle-blay          #+#    #+#             */
/*   Updated: 2022/07/15 17:18:36 by deus             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYCODES_H
# define KEYCODES_H

# ifdef __MACH__
#  define KEY_R 2
#  define KEY_L 0
#  define KEY_D 1
#  define KEY_U 13
#  define ARROW_UP 126
#  define ARROW_DOWN 125
#  define ARROW_LEFT 123
#  define ARROW_RIGHT 124
#  define SCROLL_UP 5
#  define SCROLL_DOWN 4
#  define KEY_ESC 53
#  define SPACE_BAR 49
# endif

# ifdef __linux__
#  define KEY_R 100
#  define KEY_L 97
#  define KEY_D 115
#  define KEY_U 119
#  define ARROW_UP 65362
#  define ARROW_DOWN 65364
#  define ARROW_LEFT 65361
#  define ARROW_RIGHT 65363
#  define SCROLL_UP 5
#  define SCROLL_DOWN 4
#  define KEY_ESC 65307
#  define SPACE_BAR 32
# endif

#endif
