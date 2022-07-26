/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycodes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deus <deus@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 10:17:20 by fle-blay          #+#    #+#             */
/*   Updated: 2022/07/26 09:30:54 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYCODES_H
# define KEYCODES_H

# ifdef __MACH__
#  define KEY_D 2
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_W 13
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
#  define KEY_D 100
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_W 119
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
