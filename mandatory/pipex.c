/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:02:50 by jrouillo          #+#    #+#             */
/*   Updated: 2023/05/03 14:52:16 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

pid_t	ft_pipe(t_pipex *data, char *argv, char **env, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_perror(data, FORK);
	else if (pid == 0)
	{
		data->split_cmd[i] = ft_split(argv, ' ');
		data->cmd_path[i] = get_cmd_path(data, i);
		if (!data->cmd_path[i] || access(data->cmd_path[i], F_OK | X_OK) != 0)
			ft_perror(data, data->split_cmd[i][0]);
		if (i == 0)
			ft_dup2(data->infile, data->pipe[1], data);
		else if (i == (data->nb_cmd - 1))
			ft_dup2(data->pipe[(i - 1) * 2], data->outfile, data);
		else
			ft_dup2(data->pipe[(i - 1) * 2], data->pipe[i * 2 + 1], data);
		ft_close(data);
		if (execve(data->cmd_path[i], data->split_cmd[i], env) < 0)
			ft_perror(data, data->split_cmd[i][0]);
	}
	return (pid);
}

void	init_struct(t_pipex *data, int argc, char **argv, char **env)
{
	data->infile = open(argv[1], O_RDONLY);
	if (data->infile < 0)
		ft_printf("%s: %s\n", strerror(errno), argv[1]);
	data->outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0777);
	if (data->outfile < 0)
		ft_printf("%s: %s\n", strerror(errno), argv[argc - 1]);
	// 	ft_perror(data, argv[argc - 1]);
	// if (data->infile < 0)
	// {
	// 	ft_free(data);
	// 	exit (1);
	// }
	data->nb_cmd = argc - 3;
	data->path = get_path(env);
	if (!data->path)
		exit_message(data, "data not found", ERROR_PATH);
	data->split_path = ft_split(data->path, ':');
	if (!data->split_path)
		exit_message(data, "data not found", ERROR_PATH);
	data->split_cmd = ft_calloc((data->nb_cmd), sizeof(char **));
	data->cmd_path = ft_calloc((data->nb_cmd), sizeof(char *));
	return ;
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	*data;
	int		n;
	int		i;
	pid_t	last_pid;

	last_pid = 0;
	if (argc == 5)
	{
		data = ft_calloc(1, sizeof(t_pipex));
		init_struct(data, argc, argv, env);
		ft_open(data);
		n = 1;
		i = 0;
		while (++n < (argc - 1))
		{
			last_pid = ft_pipe(data, argv[n], env, i);
			i++;
		}
		ft_free(data);
		while (waitpid(-1, NULL, 0) != -1)
			;
	}
	else
		ft_putstr_fd(ERROR_ARGS, 2);
	return (ft_waitpid(last_pid));
}
