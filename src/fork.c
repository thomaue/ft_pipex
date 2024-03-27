/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:05:29 by tauer             #+#    #+#             */
/*   Updated: 2024/03/27 17:54:10 by tauer            ###   ########.fr       */
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
			// printf("path use in ft_exec: [%s]\n", out_path);
			if (execve(out_path, args, pip->envp) == -1)
				perror("exec\n");
		}
		else if (*type == brut_parsor || *type == param_acces
			|| *type == param_parsor)
		{
			// printf("[\033[38;5;76m%s\033[0m]", path_maker(out_path,
			// 		path_maker("/", args[0])));
			// if (args[1])
			// 	printf("{%s}\n", args[1]);
			// else
			// 	printf("\n");
			if (!execve(path_maker(out_path, path_maker("/", args[0])), args,
					pip->envp))
				perror("exec pars\n");
		}
	}
}

bool	forker(t_pipex *pip)
{
	pid_t	pid;
	t_type	type;
	int		tube[2];

	if (pipe(tube) == -1)
		return (free_tab(pip->path), false);
	pid = fork();
	if (pid < 0)
		return (free_tab(pip->path), false);
	else if (pid)
	{
		// enfant
		// if (pip->i == 1)
		// {
		// 	close(tube[0]);
		// 	close(tube[1]);
		// 	close(pip->in_fd);
		// }
		// if (pip->i == pip->nb_cmd)
		// {
		// 	close(tube[0]);
		// 	close(tube[1]);
		// 	dup2(pip->ou_fd, STDIN_FILENO);
		// }
		// else
		// {
			close(tube[1]);
			dup2(tube[0], STDIN_FILENO);
			close(tube[0]);
		// }
		ft_exec(pip, pip->i, &type);
	}
	else
	{
		
		if (pip->i == pip->nb_cmd - 2)
		{
			close(tube[0]);
			close(tube[1]);
			dup2(pip->ou_fd, STDOUT_FILENO);
			close(pip->ou_fd);
		}
		if (pip->i)
		{
			close(tube[0]);
			dup2(tube[1], STDOUT_FILENO);
			close(tube[1]);
		}
		waitpid(pid, NULL, 0);
	}
	// print_splited(pip, ft_split(pip->argv[pip->i], " "));
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
	if (pip->i == 0)
	{
		if (pip->i == 0)
		{
			dup2(pip->in_fd, STDIN_FILENO);
			close(pip->in_fd);
		}
	}
	pip->i++;
	printf("[%s]%zu -> %zu\n", pip->argv[pip->i], pip->i, pip->nb_cmd);
	if (!forker(pip))
		return ;
	recursive_execute(pip);
}
