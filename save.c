

// void	ft_exec(t_pipex *pip, int i, t_type *type)
// {
// 	char **args;
// 	char *out_path;
	
// 	args = ft_split(pip->argv[i], " ");
// 	if (!args)
// 		exit(1);
// 	if (is_cmd(pip, pip->argv[i], &out_path, type))
// 	{
// 		if (*type == brut_acces)
// 		{
// 			printf("bru acces{%s}\n", out_path);
// 			execve(out_path, args, pip->envp);
// 		}
// 		else if (*type == brut_parsor || *type == param_acces || *type == param_parsor)
// 		{
// 			printf("{%s}\n", path_maker(out_path, path_maker("/", args[0])));
// 			execve(path_maker(out_path, path_maker("/", args[0])), args,
// 				pip->envp);
// 		}
// 	}
// }

// void	forker(t_pipex *pip, int i)
// {
// 	pid_t	id;
// 	// t_type	type;
// 	int		p_fd[2];
// 	// int		ret;

// 	printf("av %d -> [%s] -nb_cmd-> %d\n", i,pip->argv[i], pip->argc - 2);
// 	if (pipe(p_fd) == -1)
// 	{
// 		exit(EXIT_FAILURE);
// 	}
// 	id = fork();
// 	if (id < 0)
// 	{
// 		perror("fork");
// 		printf("NO MORE FORK PLS...\n");
// 		free_tab(pip->path);
// 		exit(EXIT_FAILURE);
// 	}
// 	else if (id == 0)
// 	{
// 		// dup2(p_fd[1], STDIN_FILENO);
// 		close(p_fd[1]);
// 		dup2(p_fd[0], 0);
// 		close(p_fd[0]);
// 		write(0, "cc 1\n", 6);
// 		// ft_exec(pip, i, &type);
// 		// close(p_fd[0]);
// 		exit(EXIT_SUCCESS);
// 	}
// 	else
// 	{
// 		// dup2()
// 		// dup2(p_fd[0], STDOUT_FILENO);
// 		close(p_fd[0]);
// 		dup2(p_fd[1], 1);
// 		close(p_fd[1]);
// 		write(1, "cc 2\n", 5);
// 		// waitpid(-1, NULL, 0);
// 		free_tab(pip->path);
// 		// ft_exec(pip, i, &type);
// 		exit (EXIT_SUCCESS);
// 	}
// }

# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>


int	main(void)
{
	char buffer[7+1];
	int	fd[2];
	
	pipe(fd);

	write(fd[1], "Hello World\n", 13);

	read(fd[0], buffer, 7+1);
	printf("%s\n", buffer);
	return (0);
}