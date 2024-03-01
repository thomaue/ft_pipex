/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:57:14 by tauer             #+#    #+#             */
/*   Updated: 2024/03/01 20:22:03 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

//  ./pipex file1 cmd1 cmd2 file2


int	main(int argc, char **argv, char **envp)
{
	t_pipex	pip;

	setup(envp, argv, argc, &pip);
	if (pipex(&pip))
		recursive_execute(&pip);
	free_all(&pip);
	return (0);
}
