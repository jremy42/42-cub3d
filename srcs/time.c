/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jremy <jremy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 12:35:45 by jremy             #+#    #+#             */
/*   Updated: 2022/07/26 10:09:18 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "cub3d.h"

#ifdef BONUS

size_t	__get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((size_t)(time.tv_sec * 1000) + (size_t)(time.tv_usec / 1000));
}

#else

size_t	__get_time(void)
{
	static struct timeval	time = {};

	time.tv_sec += 1;
	return ((size_t)(time.tv_sec * 1000) + (size_t)(time.tv_usec / 1000));
}

#endif
