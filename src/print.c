/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:53:48 by tauer             #+#    #+#             */
/*   Updated: 2024/03/01 20:19:07 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	print_data(t_pipex *pip)
{
	if (pip->argv)
		printf("\n[ARGV] : ✅\n");
	else
		printf("\n[ARGV] : ❌\n");
	if (pip->envp)
		printf("[ENVP] : ✅\n");
	else
		printf("[ENVP] : ❌\n");
	if (pip->path)
		printf("[path] : ✅\n");
	else
		printf("[path] : ❌\n");
	if (pip->nb_cmd)
		printf("[nb_cmd] : %zu\n", pip->nb_cmd);
	else
		printf("[nb_cmd] : ❌\n");
	if (pip->in_fd > 0)
		printf("[fd in] : %d\n", pip->in_fd);
	else
		printf("[fd in] : ❌\n");
	if (pip->ou_fd > 0)
		printf("[fd ou] : %d\n", pip->ou_fd);
	else
		printf("[fd ou] : ❌\n\n");
	printf("i : %zu\n\n", pip->i);
}

void	print_param(t_pipex *pip, char *out_path, t_type *type, int i)
{
	char	**args;
	size_t	index;

	index = 0;
	args = ft_split(pip->argv[i], " ");
	if (!args)
		return ;
	if (is_cmd(pip, pip->argv[i], &out_path, type) && *type == param_acces)
	{
		while (args[index])
		{
			if (index == 0)
				printf("\033[38;5;21m %s\033[0m ", args[index]);
			else
				printf("\033[38;5;90m %s\033[0m |", args[index]);
			index++;
		}
	}
	else if (is_cmd(pip, pip->argv[i], &out_path, type)
		&& *type == param_parsor)
	{
		while (args[index])
		{
			if (index == 0)
				printf("\033[38;5;21m %s\033[0m ", args[index]);
			else
				printf("\033[38;5;90m %s\033[0m |", args[index]);
			index++;
		}
	}
	free_tab(args);
}

void	print_cmd(t_pipex *pip, int i)
{
	char	*out_path;
	t_type	type;

	type = no_cmd;
	if ((i == 0 && !is_cmd(pip, pip->argv[0], &out_path, &type)))
		printf("\033[38;5;226m %s\033[0m |", pip->argv[i]);
	else if (i == pip->argc - 1 && !is_cmd(pip, pip->argv[pip->argc - 1],
			&out_path, &type))
		printf("\033[38;5;226m %s\033[0m", pip->argv[i]);
	else if (!is_cmd(pip, pip->argv[i], &out_path, &type))
		printf("\033[38;5;196m %s\033[0m ", pip->argv[i]);
	else if (is_cmd(pip, pip->argv[i], &out_path, &type) && type == brut_parsor)
		printf("\033[38;5;21m %s\033[0m |", pip->argv[i]);
	else if (is_cmd(pip, pip->argv[i], &out_path, &type) && type == brut_acces)
		printf("\033[38;5;21m %s\033[0m |", pip->argv[i]);
	else
		print_param(pip, out_path, &type, i);
}

void	print_pipex(t_pipex *pip)
{
	size_t	i;

	i = 0;
	// if (!pip->envp)
	// 	return ;
	printf("\n============================================================\n");
	printf(" >");
	while (pip->argv[i])
	{
		print_cmd(pip, i);
		i++;
	}
	printf("\n============================================================");
	print_data(pip);
	printf("============================================================\n");
}

void	print_upercase(char *str)
{
	size_t	i;
	char	current;

	i = 0;
	printf("[");
	while (str[i] && str[i] >= 'a' && str[i] <= 'z')
	{
		current = str[i] - 32;
		printf("\033[38;5;196m%c\033[0m", current);
		i++;
	}
	printf("]");
}

void	print_splited(t_pipex *pip, char **arg)
{
	size_t	i;

	i = 0;
	printf("> \033[38;5;93mCHILD\033[0m \033[38;5;20m%zu\033[0m |   ", pip->i);
	while (arg[i])
	{
		if (i == 0)
			print_upercase(arg[i++]);
		else
			printf(" [\033[38;5;160m%s\033[0m]", arg[i++]);
	}
	printf("\n");
	free_tab(arg);
}

