/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 21:44:17 by tauer             #+#    #+#             */
/*   Updated: 2024/03/26 23:31:45 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX
# define PIPEX

# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum t_type
{
	no_cmd,
	brut_acces,
	brut_parsor,
	param_acces,
	param_parsor,
}			t_type;

typedef struct s_pipex
{
	size_t	nb_cmd;
	size_t	i;

	char	**envp;
	char	**argv;
	int		argc;
	char	**path;
	
	int		re_fd;
	int		wr_fd;
	int		in_fd;
	int		ou_fd;
}			t_pipex;

bool		check_no_quoted(t_pipex *pip);
bool		set_arg_tab(t_pipex *pip);
bool		ft_strncmp(const char *s1, const char *s2, size_t n);
char		*clear_quote(char *arg);
bool		acces_bol(const char *path);
char		*path_maker(const char *path, const char *exec_name);
void		free_all(t_pipex *pip);
bool		is_cmd(t_pipex *pip, char *arg, char **out_path, t_type *type);
void		free_tab(char **tab);
void		print_data(t_pipex *pip);
bool		setup(char **envp, char **argv, int argc, t_pipex *pip);
size_t		ft_strlen(const char *str);
char		**inoutput_split(char *str, char *charset);
char		**ft_split(char *str, char *charset);
void		print_pipex(t_pipex *pip);
bool		open_bol_in(t_pipex *pip, const char *path);
bool	forker(t_pipex *pip);
bool		open_bol_ou(t_pipex *pip, const char *path);
bool		is_param(t_pipex *pip, char *arg, char **out_path, t_type *type);
bool		is_brut(t_pipex *pip, char *arg, char **out_path, t_type *type);
void	print_splited(t_pipex *pip, char **arg);
bool	conditions(t_pipex *pip);
bool	pipex(t_pipex *pip);
void	recursive_execute(t_pipex *pip);
void	format_counter(t_pipex *pip, size_t *file, size_t *locker, size_t i);

#endif