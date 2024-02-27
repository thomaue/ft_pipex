/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:57:14 by tauer             #+#    #+#             */
/*   Updated: 2024/02/27 13:04:48 by tauer            ###   ########.fr       */
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

void	set_id(t_pipex *pip, pid_t id)
{
	if (id == 0)
		pip->id_fat = id;
	else
		pip->id_son = id;
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pip;
	pid_t	id;
	size_t	i;

	i = 0;
	id = 0;
	setup(envp, argv, argc, &pip);
	if (pipex(&pip))
	{
		while (i < pip.nb_cmd)
		{
			id = fork();
			set_id(&pip, id);
			pip.i = i;
			// printf("%d\n", id);
			printf("%d -> id : %d\n", i, id);
			if (id == 0)
			{
				// printf("ok\n");
				 print_pipex(&pip);
				// free_all(&pip);
				return (0);
			}
			// else
			// {
			// 	print_pipex(&pip);
			// }
			i++;
		}
		// waitpid(pip.id_2, NULL, 0);
	}
	free_all(&pip);
	return (0);
}
