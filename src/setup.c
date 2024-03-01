/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:44:17 by tauer             #+#    #+#             */
/*   Updated: 2024/02/28 15:59:55 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	null_data(t_pipex *pip)
{
	pip->path = NULL;
	pip->argv = NULL;
	pip->argc = 0;
	pip->envp = NULL;
	pip->in_fd = 0;
	pip->ou_fd = 0;
	pip->nb_cmd = 0;
}

bool	set_arg(char **argv, char **const envp, int argc, t_pipex *pip)
{
	pip->argc = argc - 1;
	if (argv)
		pip->argv = argv + 1;
	if (envp[0])
		pip->envp = envp;
	else
		pip->envp = NULL;
	return (false);
}

bool	set_var(char *const envp[], char **out_var, const char *name_var)
{
	size_t	i;
	size_t	size;

	if (!envp || !name_var)
		return (true);
	i = 0;
	size = ft_strlen(name_var) - 1;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name_var, size))
		{
			*out_var = envp[i] + size + 1;
			return (false);
		}
		i++;
	}
	return (true);
}

bool	set_path(t_pipex *pip)
{
	char	*path;

	path = NULL;
	if (!pip->envp || set_var(pip->envp, &path, "PATH="))
		return (true);
	pip->path = ft_split(path, ":");
	if (!pip->path)
		return (true);
	return (false);
}

bool	setup(char **envp, char **argv, int argc, t_pipex *pip)
{
	null_data(pip);
	pip->i = 0;
	if (set_arg(argv, envp, argc, pip) == false && envp)
	{
		if (set_path(pip))
		{
			return (false);
		}
		return (true);
	}
	return (false);
}

