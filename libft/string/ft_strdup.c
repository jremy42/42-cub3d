/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*+:+ +:+ +:+ */
/*   By: jremy <jremy@student.42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2021/11/23 17:52:01 by jremy #+##+# */
/*   Updated: 2022/02/11 13:56:23 by fle-blay         ###   ########.fr       */
/**/
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*__strdup(const char *src)
{
	int		i;
	char	*result;

	i = 0;
	if (!src)
		return (NULL);
	result = malloc(sizeof(char) * (__strlen(src) + 1));
	if (!result)
		return (NULL);
	while (src[i])
	{
		result[i] = src[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*__strndup(const char *src, size_t n)
{
	size_t		i;
	char		*result;
	size_t		len;

	i = 0;
	if (!src)
		return (NULL);
	len = __strnlen(src, n);
	if (len > n)
		len = n;
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	result[len] = '\0';
	while (i < len && src[i])
	{
		result[i] = src[i];
		i++;
	}
	return (result);
}
