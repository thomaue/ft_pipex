/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:52:52 by tauer             #+#    #+#             */
/*   Updated: 2024/02/28 02:13:37 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

bool	parsor(t_pipex *pip, char **out_var, const char *execname)
{
	size_t	i;
	char	*filename;
	char	*path;

	filename = NULL;
	path = NULL;
	*out_var = NULL;
	i = 0;
	while (pip->path[i])
	{
		path = path_maker(pip->path[i], "/");
		filename = path_maker(path, execname);
		if (acces_bol(filename))
		{
			*out_var = pip->path[i];
			free(filename);
			free(path);
			return (true);
		}
		free(filename);
		free(path);
		i++;
	}
	return (false);
}

bool	is_brut(t_pipex *pip, char *arg, char **out_path, t_type *type)
{
	if (acces_bol(arg))
	{
		*type = brut_acces;
		*out_path = arg; 
		return (true);
	}
	else if (pip->envp && parsor(pip, out_path, arg))
	{
		*type = brut_parsor;
		return (true);
	}
	return (false);
}

bool	is_param(t_pipex *pip, char *arg, char **out_path, t_type *type)
{
	char	**args;

	args = ft_split(arg, " ");
	if (!args)
		return (false);
	if (acces_bol(args[0]))
	{
		*type = param_acces;
		*out_path = args[0];
		free_tab(args);
		return (true);
	}
	else if (pip->envp && parsor(pip, out_path, args[0]))
	{
		*type = param_parsor;
		free_tab(args);
		return (true);
	}
	free_tab(args);
	return (false);
}

bool	is_cmd(t_pipex *pip, char *arg, char **out_path, t_type *type)
{
	size_t	size;

	*out_path = NULL;
	*type = no_cmd;
	size = ft_strlen(arg);
	if (size < 2)
		return (false);
	if (is_brut(pip, arg, out_path, type))
		return (true);
	else if (is_param(pip, arg, out_path, type))
		return (true);
	return (false);
}
