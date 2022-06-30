#include "libft.h"
#include "cub3d.h"


void __print_error(char *error, t_list *lst, int fd)
{
	__lstclear(&lst, free);
	if (fd >= 0)
		close(fd);
	__putendl_fd("Error", 2);
	__putendl_fd(error, 2);
	exit(1);
}

void __printer(void *content)
{
	__putstr_fd((char *) content, 2);
}

t_list *get_input(char **av)
{
	t_list	*new_input;
	t_list	*input;
	char	*r_readline;
	int		fd;
	int ret;

	ret = 2;
	input = NULL;
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		__print_error("open error", NULL, fd);
	while (ret > 0)
	{
		ret = sget_next_line(&r_readline, fd);
		if (ret == 0)
			break;
		if (ret < 0)
			__print_error("gnl error", input, fd);
		new_input = __lstnew(r_readline);
		if (!new_input)
			__print_error("Malloc error", input, fd);
		__lstadd_back(&input, new_input);
	}
	close(fd);
	return (input);
}

int missing_info_cub(t_cub *cub)
{
	int	i;

	i = 0;

	while(i < 4)
	{
		if (!cub->text[i])
			return (1);
		i++;
	}
	i = 0;
	while(i < 2)
	{
		if (!cub->color[i])
			return (1);
		i++;
	}
	return (0);
}

int load_info(char **ret, t_cub *cub)
{
	int pos;

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

int size_split(char **ret)
{
	int	i;

	if (!ret)
		return (-1);
	i = 0;
	while (ret[i])
		i++;
	return (i);
}

void print_cub(t_cub *cub)
{
	int	i;

	i = 0;

	while(i < 4)
	{
		printf("text[%d] %s\n", i, (char *)cub->text[i]);
		i++;
	}
	i = 0;
	while(i < 2)
	{
		printf("color[%d] %s\n", i, (char *)cub->color[i]);
		i++;
	}

}

void get_info(t_list *input, t_cub *cub)
{
	char	**ret;
	char	*curent_string;
	while (input && missing_info_cub(cub))
	{
		curent_string = (char *)input->content;
		ret = __split_charset(curent_string, " \f\t\n\r\v");
		printf("size split = [%d]\n", size_split(ret));
		if (__strlen(curent_string) && !ret)
			__print_error("malloc error", input, NO_FD);
		if (size_split(ret)== 0)
		{
			free_split(ret);
			input = input->next;
			continue;
		}
		if (size_split(ret) != 2)
			return (free_split(ret), __print_error("wrong info format", input, NO_FD));
		if (!load_info(ret, cub))
			return (free_split(ret), __print_error("parsing error", input, NO_FD));
		print_cub(cub);
		input = input->next;
	}

}

void parsing(char **av, t_cub *cub)
{
	t_list	*input;

	input = get_input(av);
	get_info(input, cub);
	//__lstiter(input, __printer);
}