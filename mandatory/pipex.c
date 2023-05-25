/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:02:50 by jrouillo          #+#    #+#             */
/*   Updated: 2023/05/25 17:32:23 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exec(char *argv, t_pipex *data)
{
	char	*path;
	char	**cmd;

	cmd = ft_split(argv, ' ');
	if (!cmd)
	{
		ft_putstr_fd(argv, 2);
		ft_putstr_fd(": ", 2);
		error_free_exit(data, "command not found");
	}
	if (ft_strchr(cmd[0], '/') != 0)
		path = cmd[0];
	else
		path = find_cmd_path(cmd[0], data);
	if (path && access(path, F_OK | X_OK) == 0)
		execve(path, cmd, data->split_path);
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	ft_free(data);
	return (free(cmd), exit(127));
}

pid_t	ft_child(int i, char **argv, t_pipex *data)
{
	pid_t	pid;
	int		fd;

	pid = fork();
	if (pid < 0)
		error_free_exit(data, "Allocation failed: fork");
	if (!pid)
	{
		fd = ft_open_fd(i, argv);
		ft_dup2(fd, i, argv, data);
		ft_exec(argv[i + 2], data);
	}
	return (pid);
}

void	init_struct(t_pipex *data, int argc, char **env)
{
	int	i;

	data->path = get_path(env);
	if (!data->path)
		ft_no_path(data, argc, argv);
	else
	{
		data->split_path = ft_split(data->path, ':');
		if (!data->split_path)
			error_free_exit(data, "Allocation failed: split path");
	}
	i = 0;
	while (i < argc - 4)
	{
		pipe(data->pipe[i]);
		i++;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	data;
	pid_t	last_pid;
	int		i;

	last_pid = 0;
	if (argc == 5)
	{
		init_struct(&data, argc, env);
		i = 0;
		while (i < argc - 3)
		{
			last_pid = ft_child(i, argv, &data);
			i++;
		}
		ft_close_pipes(&data, argv);
		ft_free(&data);
	}
	return (ft_return_status(last_pid));
}
