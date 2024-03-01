/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 20:20:58 by tauer             #+#    #+#             */
/*   Updated: 2024/03/01 20:21:53 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

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

bool	format_no_quoted(t_pipex *pip)
{
	if (pip->argc >= 4 && check_no_quoted(pip))
		return (true);
	return (false);
}

bool	conditions(t_pipex *pip)
{
	if (pip->i >= pip->nb_cmd)
		return (false);
	return (true);
}

bool	pipex(t_pipex *pip)
{
	if (format_no_quoted(pip))
		return (true);
	return (false);
}
