/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:50:08 by tauer             #+#    #+#             */
/*   Updated: 2024/02/27 09:59:32 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	free_all(t_pipex *pip)
{
	if (pip)
	{
		if (pip->path)
			free_tab(pip->path);
	}
	if (pip->in_fd)
		close(pip->in_fd);
	if (pip->ou_fd)
		close(pip->ou_fd);
}