/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   security.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 11:48:27 by tauer             #+#    #+#             */
/*   Updated: 2024/02/26 21:06:50 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

bool check_no_quoted(t_pipex *pip)
{
    size_t locker;
    size_t file;
    size_t i;
    char *out_path;
    t_type type;

    locker = 0;
    file = 0;
    i = 0;
    type = no_cmd;
    while (pip->argv[i])
    {
        if (file == 0 && !is_cmd(pip, pip->argv[0], &out_path, &type) && open_bol_in(pip, pip->argv[0]))
            file++;
        else if (locker < pip->argc - 2 && is_cmd(pip, pip->argv[i], &out_path, &type))
            locker++;
        else if (pip->argv[i + 1] == NULL && !is_cmd(pip, pip->argv[i], &out_path, &type) && open_bol_ou(pip, pip->argv[i]))
            file++;
        i++;
    }
    if (pip->argc == file + locker)
        return (true);
    return (false);
}

