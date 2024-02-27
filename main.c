/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:57:14 by tauer             #+#    #+#             */
/*   Updated: 2024/02/26 21:08:18 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

bool	acces_bol(t_pipex *pip, const char *path)
{
	if (access(path, X_OK | F_OK) == -1)
		return (false);
	return (true);
}

bool	open_bol_in(t_pipex *pip, const char *path)
{
	int fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (false);
	pip->in_fd = fd;
	return (true);
}

bool	open_bol_ou(t_pipex *pip, const char *path)
{
	int fd;

	fd = open(path, O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (fd < 0)
		return (false);
	pip->ou_fd = fd;
	return (true);
}

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
	{
		printf("\nlesgo\n");
		return (true);
	}
	return (false);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pip;
	char	*out_path;
	t_type type;

	setup(envp, argv, argc, &pip);
	pipex(&pip);
	print_pipex(&pip);
	free_all(&pip);
	return (0);
}
