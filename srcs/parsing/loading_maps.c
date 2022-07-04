

#include "cub3d.h"

int	load_maps(t_list *input, t_cub *cub)
{
	int	size;
	int	i;

	i = 0;
	while (input)
	{
		if (!__strcmp((char *)input->content, "\n"))
		{
			input = input->next;
			break ;
		}
		input = input->next;
	}
	size = __lstsize(input);
	cub->maps = malloc(sizeof(char *) * (size + 1));
	cub->maps[size] = NULL;
	if (!cub->maps)
		return (0);
	while (input)
	{
		cub->maps[i] = (char *)input->content;
		input = input->next;
		i++;
	}
	return (1);
}

int	check_wall(char **maps, int i, int j, int size_c)
{
	DEBUG && printf("check wall %c\n", maps[j][i]);
	if (i == 0 || i == ((int)__strlen(maps[j]) - 1)
		|| j == 0 || j == size_c - 1)
		return (1);
	DEBUG && printf("i = %d strlen j+1 = %d, strlen j - 1 = %d\n", i, (int)__strlen(maps[j+1]), (int)__strlen(maps[j-1] - 2));
	DEBUG && printf("maps[j+1] = [%s]\n",maps[j+1]);
	if (i >= ((int)__strlen(maps[j + 1]) - 2)
		|| i >= ((int)__strlen(maps[j - 1]) - 2))
		return (1);
	if (maps[j + 1][i] == ' '
		|| maps[j + 1][i + 1] == ' '
		|| maps[j][i + 1] == ' '
		|| maps[j][i - 1] == ' ')
		return (1);
	return (0);
}

int	check_maps(t_cub *cub)
{
	int	size_l;
	int	size_c;
	int	i;
	int	j;

	i = 0;
	j = 0;
	size_c = 0;
	while (cub->maps[size_c])
	{
		if (!__strcmp(cub->maps[size_c], "\n"))
			break ;
		size_c++;
	}
	while (j < size_c && cub->maps[j])
	{			
		size_l = __strlen(cub->maps[j]);
		while (cub->maps[j][i])
		{
			printf("[%c]\n", cub->maps[j][i]);
			if (!__strchr(" \n10NSEW", cub->maps[j][i]))
				return (0);
			if (cub->maps[j][i] == '0'
				&& check_wall(cub->maps, i, j, size_c))
				return (0);
			i++;
		}
		i = 0;
		j++;
	}
	return (1);
}
