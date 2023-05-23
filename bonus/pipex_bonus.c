/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:39:59 by jrouillo          #+#    #+#             */
/*   Updated: 2023/05/23 17:52:14 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_exec(char *argv, t_pipex *data)
{
	char	*path;
	char	**cmd;

	cmd = ft_split(argv, ' ');
	if (!cmd)
		error_free_exit(data, argv, "command not found");
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
		error_free_exit(data, 0, "Allocation failed: fork\n");
	if (!pid)
	{
		fd = ft_open_fd(i, argv, data);
		ft_dup2(fd, i, argv, data);
		ft_exec(argv[i + 2 + data->hd_status], data);
	}
	return (pid);
}

void	init_struct(t_pipex *data, int argc, char **argv, char **env)
{
	int	i;

	if (!ft_strncmp(argv[1], "here_doc", 9))
		data->hd_status = 1;
	else
		data->hd_status = 0;
	data->path = get_path(env);
	if (data->path)
	{
		data->split_path = ft_split(data->path, ':');
		if (!data->split_path)
			error_free_exit(data, 0, "Allocation failed: split path\n");
	}
	i = 0;
	while (i < argc - 4 - data->hd_status)
	{
		pipe(data->pipe[i]);
		i++;
	}
}

bool	ft_check_args(int argc, char **argv)
{
	if (argc < 5)
		return (false);
	if (!ft_strncmp(argv[1], "here_doc", 9) && argc < 6)
		return (false);
	return (true);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	data;
	pid_t	last_pid;
	int		i;

	if (!ft_check_args(argc, argv))
		return (ft_putstr_fd("Invalid number of arguments\n", 2), 0);
	init_struct(&data, argc, argv, env);
	i = 0;
	while (i < argc - 3 - data.hd_status)
	{
		last_pid = ft_child(i, argv, &data);
		i++;
	}
	ft_close_pipes(&data, argv);
	ft_free(&data);
	return (ft_return_status(last_pid));
}
