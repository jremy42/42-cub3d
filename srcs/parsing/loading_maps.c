

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
	if (i == 0 || i == ((int)__strlen(maps[j]) - 1)
		|| j == 0 || j == nb_l - 1)
		return (__putstr_fd("0 on border\n", 2), 0);
	//DEBUG && printf("i = %d strlen j+1 = %d, strlen j - 1 = %d\n", i, (int)__strlen(maps[j+1]), (int)__strlen(maps[j-1] - 2));
	//DEBUG && printf("maps[j+1] = [%s]\n",maps[j+1]);
	if (i >= ((int)__strlen(maps[j + 1]) - 2)
		|| i >= ((int)__strlen(maps[j - 1]) - 2))
		return (__putstr_fd("surrouding wall missing\n", 2), 0);
	if (maps[j + 1][i] == ' '
		|| maps[j + 1][i + 1] == ' '
		|| maps[j][i + 1] == ' '
		|| maps[j - 1][i + 1] == ' '
		|| maps[j - 1][i] == ' '
		|| maps[j - 1][i - 1] == ' '
		|| maps[j][i - 1] == ' '
		|| maps[j + 1][i - 1] == ' ')
		return (__putstr_fd("space near 0\n", 2), 0);
	return (1);
}

int	check_player(t_cub *cub, int i, int j, int nb_l)
{
	if (cub->player.dir)
		return (__putstr_fd("to many player\n", 2), 0);
	printf("char = [%c]\n", cub->maps[j][i]);
	if (i == 0 || i == ((int)__strlen(cub->maps[j]) - 1)
		|| j == 0 || j == nb_l - 1)
		return (__putstr_fd("player on border\n", 2), 0);
	if (i >= ((int)__strlen(cub->maps[j + 1]) - 2)
		|| i >= ((int)__strlen(cub->maps[j - 1]) - 2))
		return (__putstr_fd("surrouding wall missing near player\n", 2), 0);
	if (cub->maps[j + 1][i] == ' '
		|| cub->maps[j + 1][i + 1] == ' '
		|| cub->maps[j][i + 1] == ' '
		|| cub->maps[j - 1][i + 1] == ' '
		|| cub->maps[j - 1][i] == ' '
		|| cub->maps[j - 1][i - 1] == ' '
		|| cub->maps[j][i - 1] == ' '
		|| cub->maps[j + 1][i - 1] == ' ')
		return (__putstr_fd("space near player\n", 2), 0);
	cub->player.dir = cub->maps[j][i];
	cub->player.i = i;
	cub->player.j = j;
	return (1);
}

int	check_maps(t_cub *cub)
{
	int	nb_l;
	int	i;
	int	j;

	j = 0;
	nb_l = 0;
	while (cub->maps[nb_l])
	{
		if (!__strcmp(cub->maps[nb_l], "\n"))
			break ;
		nb_l++;
	}
	while (j < nb_l && cub->maps[j])
	{			
		i = 0;
		while (cub->maps[j][i])
		{
			if (!__strchr(" \n10NSEW", cub->maps[j][i]))
				return (__putstr_fd("wrong char\n", 2), print_maps_error(cub, j, i), 0);
			if (__strchr("NSEW", cub->maps[j][i]) && !check_player(cub, i, j, nb_l))
				return (print_maps_error(cub, j, i), 0);
			else if(cub->maps[j][i] == '0'
				&& !check_wall(cub->maps, i, j, nb_l))
				return (print_maps_error(cub, j, i), 0);
			i++;
		}
		j++;
	}
	if (!cub->player.dir)
		return (__putstr_fd("missing player\n", 2), 0);
	return (1);
}
