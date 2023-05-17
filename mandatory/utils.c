/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:42:56 by jrouillo          #+#    #+#             */
/*   Updated: 2023/04/28 14:53:05 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_waitpid(pid_t last_pid)
{
	pid_t	pid;
	int		status;
	int		ret_value;

	while (1)
	{
		pid = wait(&status);
		if (pid < 0)
			break ;
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				ret_value = WEXITSTATUS(status);
			else
				ret_value = 128 + WTERMSIG(status);
		}
	}
	return (ret_value);
}

void	ft_dup2(int new_read, int new_write, t_pipex *data)
{
	int	dup_in;
	int	dup_out;

	dup_in = dup2(new_read, STDIN_FILENO);
	if (dup_in < 0)
		ft_perror(data, ERROR_FD_IN);
	dup_out = dup2(new_write, STDOUT_FILENO);
	if (dup_out < 0)
		ft_perror(data, ERROR_FD_OUT);
	return ;
}

void	ft_close(t_pipex *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_cmd * 2)
	{
		if (data->pipe[i] && data->pipe[i] > 0)
		{
			if (close(data->pipe[i]) == -1)
				ft_perror(data, "close");
		}
	}
	return ;
}

void	ft_open(t_pipex *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_cmd)
	{
		if (pipe(data->pipe + (i * 2)) < 0)
			ft_perror(data, PIPE);
	}
}
