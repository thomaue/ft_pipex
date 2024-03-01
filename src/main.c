/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:57:14 by tauer             #+#    #+#             */
/*   Updated: 2024/03/01 15:14:53 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

//  ./pipex file1 cmd1 cmd2 file2

bool	format_no_quoted(t_pipex *pip)
{
	if (pip->argc >= 4 && check_no_quoted(pip))
		return (true);
	return (false);
}

bool	pipex(t_pipex *pip)
{
	if (format_no_quoted(pip))
		return (true);
	return (false);
}

bool	conditions(t_pipex *pip)
{
	if (pip->i >= pip->nb_cmd)
		return (false);
	return (true);
}

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

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pip;

	setup(envp, argv, argc, &pip);
	if (pipex(&pip))
		recursive_execute(&pip);
	free_all(&pip);
	return (0);
}
