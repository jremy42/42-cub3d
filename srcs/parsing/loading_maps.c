

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

int	check_wall(char **maps, int i, int j, int nb_l)
{
	//DEBUG && printf("check wall %c\n", maps[j][i]);
	if (j == 0 || j == ((int)__strlen(maps[i]) - 1)
		|| i == 0 || i == nb_l - 1)
		return (__putstr_fd("0 on border\n", 2), 0);
	//DEBUG && printf("i = %d strlen j+1 = %d, strlen j - 1 = %d\n", i, (int)__strlen(maps[j+1]), (int)__strlen(maps[j-1] - 2));
	//DEBUG && printf("maps[j+1] = [%s]\n",maps[j+1]);
	if (j >= ((int)__strlen(maps[i + 1]) - 2)
		|| j >= ((int)__strlen(maps[i - 1]) - 2))
		return (__putstr_fd("surrouding wall missing\n", 2), 0);
	if (maps[i + 1][j] == ' '
		|| maps[i + 1][j + 1] == ' '
		|| maps[i][j + 1] == ' '
		|| maps[i - 1][j + 1] == ' '
		|| maps[i - 1][j] == ' '
		|| maps[i - 1][j - 1] == ' '
		|| maps[i][j - 1] == ' '
		|| maps[i + 1][j - 1] == ' ')
		return (__putstr_fd("space near 0\n", 2), 0);
	return (1);
}

int	check_player(t_cub *cub, int i, int j, int nb_l)
{
	if (cub->player.dir)
		return (__putstr_fd("to many player\n", 2), 0);
	if (j == 0 || j == ((int)__strlen(cub->maps[i]) - 1)
		|| i == 0 || i == nb_l - 1)
		return (__putstr_fd("player on border\n", 2), 0);
	if (j >= ((int)__strlen(cub->maps[i + 1]) - 2)
		|| j >= ((int)__strlen(cub->maps[i - 1]) - 2))
		return (__putstr_fd("surrouding wall missing near player\n", 2), 0);
	if (cub->maps[i + 1][j] == ' '
		|| cub->maps[i + 1][j + 1] == ' '
		|| cub->maps[i][j + 1] == ' '
		|| cub->maps[i - 1][j + 1] == ' '
		|| cub->maps[i - 1][j] == ' '
		|| cub->maps[i - 1][j - 1] == ' '
		|| cub->maps[i][j - 1] == ' '
		|| cub->maps[i + 1][j - 1] == ' ')
		return (__putstr_fd("space near player\n", 2), 0);
	cub->player.dir = cub->maps[i][j];
	cub->player.i = i;
	cub->player.j = j;
	return (1);
}

int	maps_size(char **maps)
{
	int	i;
	int	j;

	i = 0;
	while (maps[i])
	{
		if (!__strcmp(maps[i], "\n"))
			break ;
		i++;
	}
	j = i;
	while (maps[j])
	{
		if (!__strcmp(maps[j], "\n"))
			return (-1) ;
		j++;
	}
	return (i);
}

int	check_maps(t_cub *cub)
{
	int	nb_l;
	int	i;
	int	j;

	i = 0;
	nb_l = maps_size(cub->maps);
	if (nb_l <= 0)
		return (__putstr_fd("wrong maps size\n", 2), 0);
	while (i < nb_l && cub->maps[i])
	{			
		j = 0;
		while (cub->maps[i][j])
		{
			if (!__strchr(" \n10NSEW", cub->maps[i][j]))
				return (__putstr_fd("wrong char\n", 2), print_maps_error(cub, i, j), 0);
			if (__strchr("NSEW", cub->maps[i][j]) && !check_player(cub, i, j, nb_l))
				return (print_maps_error(cub, i, j), 0);
			else if(cub->maps[i][j] == '0'
				&& !check_wall(cub->maps, i, j, nb_l))
				return (print_maps_error(cub, i, j), 0);
			j++;
		}
		i++;
	}
	if (!cub->player.dir)
		return (__putstr_fd("missing player\n", 2), 0);
	return (1);
}
