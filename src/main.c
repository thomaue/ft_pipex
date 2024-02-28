/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:57:14 by tauer             #+#    #+#             */
/*   Updated: 2024/02/28 09:53:03 by tauer            ###   ########.fr       */
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

void	ft_exec(t_pipex *pip, int i, t_type *type, int p_fd[2])
{
	char **args;
	char *out_path;
	
	args = ft_split(pip->argv[i], " ");
	if (!args)
		exit(1);
	if (is_cmd(pip, pip->argv[i], &out_path, type))
	{
		if (*type == brut_acces)
			execve(out_path, args, pip->envp);
		else if (*type == brut_parsor)
			execve(path_maker(out_path, path_maker("/", args[0])), args,
				pip->envp);
		else if (*type == param_acces)
			execve(path_maker(out_path, path_maker("/", args[0])), args,
				pip->envp);
		else if (*type == param_parsor)
		{
			execve(path_maker(out_path, path_maker("/", args[0])), args,
				pip->envp);
		}
	}
}

void	forker(t_pipex *pip, int i)
{
	pid_t	id;
	t_type	type;
	int		p_fd[2];

	printf("%d : [%s] - %d\n", i,pip->argv[i], pip->argc - 2);
	if (pipe(p_fd) == -1)
		exit(EXIT_FAILURE);
	id = fork();
	if (id == -1)
	{
		perror("fork");
		printf("NO MORE FORK PLS...\n");
		free_tab(pip->path);
		exit(EXIT_FAILURE);
	}
	else if (id == 0)
	{
		dup2();
		close(p_fd[0]);
		ft_exec(pip, i, &type, p_fd);
		// exit(EXIT_SUCCESS);
	}
	else
	{
		
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pip;
	size_t	i;

	i = 0;
	setup(envp, argv, argc, &pip);
	if (pipex(&pip))
	{
		while (i < pip.nb_cmd)
		{
			forker(&pip, ++i);
			printf("Working on %s\n", pip.argv[i]);
		}
	}		
	i = 0;
	free_all(&pip);
	
	return (0);
}
