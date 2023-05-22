/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:39:59 by jrouillo          #+#    #+#             */
/*   Updated: 2023/05/22 18:25:25 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

bool	ft_check_args(int argc, char **argv)
{
	if (argc < 5)
		return (false);
	if (!ft_strncmp(argv[1], "here_doc", 9) && argc < 6)
		return (false);
	return (true);
}

void	ft_exec(char *argv, t_pipex *data)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	if (!cmd)
		error_free_exit(data, argv, "command not found");
	if (ft_strchr(cmd[0], '/') != 0)
		path = cmd[0];
	else
		path = find_cmd_path(cmd[0], data);
	// printf("A ce stade, path = %s\n", path);
	if (path && access(path, F_OK | X_OK) == 0)
		execve(path, cmd, data->split_path);
	ft_printf("%s: command not found\n", cmd[0]);
	ft_free_split_path(data);
	ft_free_pipes(data);
	exit(127);
	// printf("je n'execute pas la cmd\n");
}

pid_t	ft_child(int i, char **argv, t_pipex *data)
{
	pid_t	pid;
	int		fd;

	pid = fork();
	if (!pid)
	{
		fd = ft_open_fd(i, argv, data);
		if (fd < 0)
			exit(1);
		ft_dup2(fd, i, argv, data);
		// ft_printf("je passe par la  aevc : %s\n", argv[i + 2 + data->hd_status]);
		ft_exec(argv[i + 2 + data->hd_status], data);
	}
	return (pid);
}

int    ft_return_status(pid_t last_pid)
{
    pid_t	wpid;
    int		wstatus;
    int		return_value;

    while (true)
    {
        wpid = wait(&wstatus);
        if (wpid < 0)
            break ;
        if (wpid == last_pid)
        {
            if (WIFEXITED(wstatus))
                return_value = WEXITSTATUS(wstatus);
            else
                return_value = 128 + WTERMSIG(wstatus);
        }
    }
    return (return_value);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	data;
	pid_t	last_pid;
	int		i;

	if (!ft_check_args(argc, argv))
		return (ft_putstr_fd("Invalid number of arguments\n", 2), 1);
	init_struct(&data, argc, argv, env);
	i = 0;
	while (i < argc - 3 - data.hd_status)
	{
		last_pid = ft_child(i, argv, &data);
		i++;
	}
	ft_close_pipe(&data, argv);
	return (ft_return_status(last_pid));
}