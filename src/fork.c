/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:05:29 by tauer             #+#    #+#             */
/*   Updated: 2024/03/01 20:19:41 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	ft_exec(t_pipex *pip, int i, t_type *type)
{
	char	**args;
	char	*out_path;

	args = ft_split(pip->argv[i], " ");
	if (!args)
		exit(1);
	if (is_cmd(pip, pip->argv[i], &out_path, type))
	{
		if (*type == brut_acces)
		{
			printf("path use in ft_exec: [%s]\n", out_path);
			execve(out_path, args, pip->envp);
		}
		else if (*type == brut_parsor || *type == param_acces
			|| *type == param_parsor)
		{
			printf("[\033[38;5;76m%s\033[0m]\n", path_maker(out_path,
					path_maker("/", args[0])));
			execve(path_maker(out_path, path_maker("/", args[0])), args,
				pip->envp);
		}
	}
}

bool	forker(t_pipex *pip)
{
	pid_t	pid;
	t_type	type;

	// printf("\n");
	pid = fork();
	if (pid < 0)
	{
		free_tab(pip->path);
		return (false);
	}
	else if (pid == 0)
	{
		// child
		print_splited(pip, ft_split(pip->argv[pip->i], " "));
		ft_exec(pip, pip->i, &type);
	}
	else
	{
		// parent
		waitpid(pid, NULL, 0);
	}
	return (true);
}

void	recursive_execute(t_pipex *pip)
{
	if (!conditions(pip))
	{
		free_tab(pip->path);
		pip->path = NULL;
		return ;
	}
	pip->i++;
	if (!forker(pip))
		return ;
	recursive_execute(pip);
}
