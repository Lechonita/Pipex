/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:42:56 by jrouillo          #+#    #+#             */
/*   Updated: 2023/05/17 13:56:24 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// int	ft_waitpid(pid_t last_pid)
// {
// 	pid_t	pid;
// 	int		status;
// 	int		ret_value;

// 	while (1)
// 	{
// 		pid = wait(&status);
// 		dprintf(2, "pid = %d\n", pid);
// 		if (pid < 0)
// 			break ;
// 		if (pid == last_pid)
// 		{
// 			if (WIFEXITED(status))
// 				ret_value = WEXITSTATUS(status);
// 			else
// 				ret_value = 128 + WTERMSIG(status);
// 		}
// 	}
// 	return (ret_value);
// }

void	ft_dup2(int fd, int i, char **argv, t_pipex *data)
{
	// printf("j'arrive ici avec un fd de %d\n", fd);
	if (!i)
	{
		// printf("je suis %s et je passe par le chemin de la premiere cmd\n", argv[i + 2 + data->hd_status]);
		dup2(fd, STDIN_FILENO);
		dup2(data->pipe[i][1], STDOUT_FILENO);
		ft_close_pipe(data, argv);
	}
	else if (argv[i + 4 + data->hd_status])
	{	
		// printf("je suis %s et je passe par le chemin median cmd\n", argv[i + 2 + data->hd_status]);
		dup2(data->pipe[i - 1][0], STDIN_FILENO);
		dup2(data->pipe[i][1], STDOUT_FILENO);
		ft_close_pipe(data, argv);
	}
	else
	{
		// printf("je suis %s et je passe par le chemin de la derniere cmd\n", argv[i + 2 + data->hd_status]);
		dup2(data->pipe[i - 1][0], STDIN_FILENO);
		ft_close_pipe(data, argv);
		dup2(fd, STDOUT_FILENO);
	}
	// printf("venez me chercher\n");
}

void	ft_close_pipe(t_pipex *data, char **argv)
{
	int	i;
	int	size;

	size = 0;
	while (argv[size])
		size++;
	i = -1;
	// printf("j'ai %d pipes\n", size - 4 - data->hd_status);
	while (++i < size - 4 - data->hd_status)
	{
		close(data->pipe[i][0]);
		close(data->pipe[i][1]);
	}
}

// void	ft_open(t_pipex *data)
// {
// 	int	i;

// 	i = -1;
// 	// dprintf(2, "--------------OPEN----------------\n");
// 	while (++i < data->nb_cmd)
// 	{
// 		if (pipe(data->pipe + (i * 2)) < 0)
// 			ft_perror(data, PIPE);
// 		// dprintf(2, "data->pipe[%d] = %d\n", i, data->pipe[i]);
// 		// dprintf(2, "data->pipe[%d] = %d\n", i + 1, data->pipe[i + 1]);
// 	}
// }
