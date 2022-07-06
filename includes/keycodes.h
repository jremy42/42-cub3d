/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycodes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <{fle-blay}@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 10:17:20 by fle-blay          #+#    #+#             */
/*   Updated: 2022/07/06 10:21:01 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYCODES_H
# define KEYCODES_H

# ifdef __MACH__
#  define KEY_R 2
#  define KEY_L 0
#  define KEY_D 1
#  define KEY_U 13
#  define KEY_ESC 53
# endif

# ifdef __linux__
#  define KEY_R 100
#  define KEY_L 97
#  define KEY_D 115
#  define KEY_U 119
#  define KEY_ESC 65307
# endif

#endif
