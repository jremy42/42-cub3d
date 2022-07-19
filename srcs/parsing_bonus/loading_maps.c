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
	cub->door_map = malloc (sizeof(float *) * (size + 1));
	if (!cub->maps || !cub->door_map)
		return (free(cub->maps), free(cub->door_map), 0);
	while (input)
	{
		cub->maps[i] = (char *)input->content;
		if (__strlen(cub->maps[i]) > 1 && __strrchr(cub->maps[i], '\n'))
			cub->maps[i][__strlen(cub->maps[i]) - 1] = 0;
		cub->door_map[i] = malloc (sizeof(float) * __strlen(cub->maps[i]));
		__memset(cub->door_map[i], 0, __strlen(cub->maps[i]));
		// MALLOC CHECK	
		input = input->next;
		i++;
	}

	return (1);
}

int	check_wall(char **maps, int i, int j, int nb_l)
{
	if (j == 0 || j == ((int)__strlen(maps[i]) - 1)
		|| i == 0 || i == nb_l - 1)
		return (__putstr_fd("0 on border\n", 2), 0);
	if (j >= ((int)__strlen(maps[i + 1]) - 1)
		|| j >= ((int)__strlen(maps[i - 1]) - 1))
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
	if (cub->player.start_orientation)
		return (__putstr_fd("to many player\n", 2), 0);
	if (j == 0 || j == ((int)__strlen(cub->maps[i]) - 1)
		|| i == 0 || i == nb_l - 1)
		return (__putstr_fd("player on border\n", 2), 0);
	if (j >= ((int)__strlen(cub->maps[i + 1]) - 1)
		|| j >= ((int)__strlen(cub->maps[i - 1]) - 1))
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
	cub->player.start_orientation = cub->maps[i][j];
	cub->player.pos_x = j;
	cub->player.pos_y = i;
	cub->maps[i][j] = '0';
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
		if (__strcmp(maps[j], "\n"))
			return (-1);
		j++;
	}
	return (i);
}

int	get_enemy_postion(t_cub *cub, int nb_l)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	printf("sprite_count = [%d]\n", cub->sprite_count);
	cub->sprite_tab = malloc(sizeof(t_sprite) * cub->sprite_count);
	if (!cub->sprite_tab)
		return (0);
	__memset(cub->sprite_tab, 0, sizeof(t_sprite) * cub->sprite_count);
	cub->sprite_order = malloc(sizeof(int) * cub->sprite_count);
	if (!cub->sprite_order)
		return(0);
	while (i < nb_l && cub->maps[i])
	{			
		j = 0;
		while (cub->maps[i][j])
		{
			if (cub->maps[i][j] == 'G')
			{
				cub->sprite_order[k] = k;
				cub->sprite_tab[k].pos_x = j + 0.5f;
				cub->sprite_tab[k].pos_y = i + 0.5f;
				k++;
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	check_maps(t_cub *cub)
{
	int	nb_l;
	int	i;
	int	j;

	i = 0;
	nb_l = maps_size(cub->maps);
	if (nb_l == 0)
		return (__putstr_fd("empty map\n", 2), 0);
	if (nb_l < 0)
		return (__putstr_fd("info after map end\n", 2), 0);
	while (i < nb_l && cub->maps[i])
	{			
		j = 0;
		while (cub->maps[i][j])
		{
			if (!__strchr(" GD3210NSEW", cub->maps[i][j]))
				return (__putstr_fd("wrong char\n", 2), print_maps_error(cub, i, j), 0);
			if (__strchr("NSEW", cub->maps[i][j]) && !check_player(cub, i, j, nb_l))
				return (print_maps_error(cub, i, j), 0);
			else if((cub->maps[i][j] == '0' || cub->maps[i][j] == 'G' || cub->maps[i][j] == 'D')
				&& !check_wall(cub->maps, i, j, nb_l))
				return (print_maps_error(cub, i, j), 0);
			if (cub->maps[i][j] == 'D')
				cub->door_map[i][j] = 2;
			if (cub->maps[i][j] == 'G')
				cub->sprite_count++;
			j++;
		}
		i++;
	}
	if (!get_enemy_postion(cub, nb_l))
		return (__putstr_fd("Malloc error\n", 2), 0);
	if (!cub->player.start_orientation)
		return (__putstr_fd("missing player\n", 2),  0);
	return (1);
}
