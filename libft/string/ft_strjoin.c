/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*+:+ +:+ +:+ */
/*   By: jremy <jremy@student.42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2021/11/23 18:06:59 by jremy #+##+# */
/*   Updated: 2022/03/30 09:36:39 by fle-blay         ###   ########.fr       */
/**/
/* ************************************************************************** */

#include "libft.h"

static char	*__strcpy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

static char	*__strcat(char *dst, const char *src)
{
	__strcpy(dst + __strlen(dst), src);
	return (dst);
}

char	*__strjoin(char const *s1, char const *s2)
{
	size_t	size;
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	size = __strlen(s1) + __strlen(s2);
	result = __calloc(size + 1, sizeof(char));
	if (!result)
	{
		free((char *)s1);
		return (NULL);
	}
	result = __strcpy(result, s1);
	result = __strcat(result, s2);
	free((char *)s1);
	return (result);
}

char	*__old_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	size = __strlen(s1) + __strlen(s2);
	result = __calloc(size + 1, sizeof(char));
	if (!result)
		return (NULL);
	result = __strcpy(result, s1);
	result = __strcat(result, s2);
	return (result);
}

char	*__strjoin2(char const *s1, char const *s2, char const *s3)
{
	size_t	size;
	char	*result;

	if (!s1 || !s2 || !s3)
		return (NULL);
	size = __strlen(s1) + __strlen(s2) + __strlen(s3);
	result = __calloc(size + 1, sizeof(char));
	if (!result)
	{
		free((char *)s1);
		return (NULL);
	}
	result = __strcpy(result, s1);
	result = __strcat(result, s2);
	result = __strcat(result, s3);
	free((char *)s1);
	return (result);
}
