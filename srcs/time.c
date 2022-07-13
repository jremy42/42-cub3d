#include <sys/time.h>
#include "cub3d.h"

size_t	__get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((size_t)(time.tv_sec * 1000) + (size_t)(time.tv_usec / 1000));
}