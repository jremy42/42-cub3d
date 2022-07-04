#include "libft.h"
#include "cub3d.h"

void	__exit_error(char *error, t_cub *cub)
{
	destroy_cub_data(cub);
	__putendl_fd("Error", 2);
	__putendl_fd(error, 2);
	exit(1);
}

void	__exit_error_get_input(char *error, t_list *lst, int fd)
{
	__lstclear(&lst, free);
	if (fd >= 0)
		close(fd);
	__putendl_fd("Error", 2);
	__putendl_fd(error, 2);
	exit(1);
}

t_list	*get_input(char **av)
{
	t_list	*new_input;
	t_list	*input;
	char	*r_readline;
	int		fd;
	int		ret;

	ret = 2;
	input = NULL;
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		__exit_error_get_input("open error", NULL, fd);
	while (ret > 0)
	{
		ret = sget_next_line(&r_readline, fd);
		if (ret == 0)
			break ;
		if (ret < 0)
			__exit_error_get_input("gnl error", input, fd);
		new_input = __lstnew(r_readline);
		if (!new_input)
			__exit_error_get_input("Malloc error", input, fd);
		__lstadd_back(&input, new_input);
	}
	close(fd);
	return (input);
}

int	missing_info_cub(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!cub->text[i])
			return (1);
		i++;
	}
	i = 0;
	while (i < 2)
	{
		if (!cub->color[i])
			return (1);
		i++;
	}
	return (0);
}

int	load_info(char **ret, t_cub *cub)
{
	int	pos;

	pos = !__strcmp(ret[0], "NO") * 1
		+ !__strcmp(ret[0], "SO") * 2
		+ !__strcmp(ret[0], "EA") * 3
		+ !__strcmp(ret[0], "WE") * 4
		+ !__strcmp(ret[0], "F") * 5
		+ !__strcmp(ret[0], "C") * 6;
	if (!pos)
		return (__putstr_fd("No such a info\n", 2), 0);
	if (pos > 0 && pos < 5)
		cub->text[pos - 1] = ret[1];
	else
		cub->color[pos - 5] = ret[1];
	free(ret[0]);
	ret[0] = NULL;
	free(ret);
	return (1);
}

void	get_info(t_list *input, t_cub *cub)
{
	char	**ret;
	char	*curent_string;

	while (input && missing_info_cub(cub))
	{
		curent_string = (char *)input->content;
		ret = __split_charset(curent_string, " \f\t\n\r\v");
		DEBUG && printf("size split = [%d]\n", size_split(ret));
		if (__strlen(curent_string) && !ret)
			__exit_error("malloc error", cub);
		if (size_split(ret) == 0)
		{
			free_split(ret);
			input = input->next;
			continue ;
		}
		if (size_split(ret) != 2)
			return (free_split(ret), __exit_error("wrong info format", cub));
		if (!load_info(ret, cub))
			return (free_split(ret), __exit_error("parsing error", cub));
		DEBUG && print_cub(cub);
		input = input->next;
	}
	if (!load_maps(input, cub))
		return (__exit_error("malloc error", cub));
}

void	destroy_cub_data(t_cub *cub)
{
	int	i;

	i = -1;
	while (++i < 2)
		free(cub->color[i]);
	i = -1;
	while (++i < 4)
		free(cub->text[i]);
	free(cub->maps);
	__lstclear(&cub->input, free);
	DEBUG && printf("Cub data successfully destroyed\n");
}

void	parsing(char **av, t_cub *cub)
{
	t_list	*input;

	input = get_input(av);
	cub->input = input;
	get_info(input, cub);
	//print_maps(cub);
	if (!check_maps(cub))
		__exit_error("Invalid map 1", cub);
	//__lstiter(input, __printer);
}
