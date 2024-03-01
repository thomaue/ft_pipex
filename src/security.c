/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   security.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 11:48:27 by tauer             #+#    #+#             */
/*   Updated: 2024/03/01 15:10:26 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

bool	acces_bol(const char *path)
{
	if (access(path, X_OK | F_OK) == -1)
		return (false);
	return (true);
}

bool	open_bol_in(t_pipex *pip, const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (false);
	pip->in_fd = fd;
	return (true);
}

bool	open_bol_ou(t_pipex *pip, const char *path)
{
	int	fd;

	fd = open(path, O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (fd < 0)
		return (false);
	pip->ou_fd = fd;
	return (true);
}

void	format_counter(t_pipex *pip, size_t *file, size_t *locker, size_t i)
{
	char	*out_path;
	t_type	type;

	if (*file == 0 && !is_cmd(pip, pip->argv[0], &out_path, &type)
		&& open_bol_in(pip, pip->argv[0]))
		(*file)++;
	else if (*locker < (size_t)pip->argc - 2 && is_cmd(pip, pip->argv[i],
			&out_path, &type))
		(*locker)++;
	else if (pip->argv[i + 1] == NULL && !is_cmd(pip, pip->argv[i], &out_path,
			&type) && open_bol_ou(pip, pip->argv[i]))
		(*file)++;
}

bool	check_no_quoted(t_pipex *pip)
{
	size_t	locker;
	size_t	file;
	size_t	i;
	// t_type	type;

	locker = 0;
	file = 0;
	i = 0;
	// type = no_cmd;
	while (pip->argv[i])
	{
		format_counter(pip, &file, &locker, i);
		i++;
	}
	if ((size_t)pip->argc == file + locker)
	{
		pip->nb_cmd = locker;	
		return (true);
	}
	return (false);
}
