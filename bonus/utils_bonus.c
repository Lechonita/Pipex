/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:42:56 by jrouillo          #+#    #+#             */
/*   Updated: 2023/05/26 17:30:15 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/* Function that :
	1/ waits for all child processes to finish before doing parent process
	2/ returns the correct errno in the standard output
	3/ In the case of here_doc, closes the temporary here_doc file */

int	ft_return_status(t_pipex *data, pid_t last_pid)
{
	pid_t	wpid;
	int		status;
	int		res;

	while (true)
	{
		wpid = wait(&status);
		if (wpid < 0)
			break ;
		if (wpid == last_pid)
		{
			if (WIFEXITED(status))
				res = WEXITSTATUS(status);
			else
				res = 128 + WTERMSIG(status);
		}
	}
	if (access("here_doc", F_OK) != -1)
	{
		if (unlink("here_doc") < 0)
			error_free_exit(data, "Unlink error: here_doc");
	}
	return (res);
}

/* Function that uses dup2() to change the new write fd (1) and the
	new read fd (0).
	New write fd and New read fd depend on the order of the command.
	If it's the first command (i = 0), the original input is infile,
	the new read fd is data->pipe[0][1].
	If it's neither the first nor the last command, the read fd is
	data->pipe[i - 1][0] and the write fd is data->pipe[i][1].
	If it's the last command, the read fd is data->pipe[i - 1][0]
	and the write fd is the outfile. */

void	ft_dup2(int fd, int i, char **argv, t_pipex *data)
{
	if (!i)
	{
		dup2(fd, STDIN_FILENO);
		dup2(data->pipe[i][1], STDOUT_FILENO);
		ft_close_pipes(data, argv);
		if (fd < 3)
			return (ft_free(data), exit(EXIT_FAILURE));
	}
	else if (argv[i + 4 + data->hd_status])
	{
		dup2(data->pipe[i - 1][0], STDIN_FILENO);
		dup2(data->pipe[i][1], STDOUT_FILENO);
		ft_close_pipes(data, argv);
	}
	else
	{
		dup2(data->pipe[i - 1][0], STDIN_FILENO);
		ft_close_pipes(data, argv);
		dup2(fd, STDOUT_FILENO);
		if (fd < 3)
			return (ft_free(data), exit(EXIT_FAILURE));
	}
}

/* Closing all pipes one by one.
	Finding "size" will allow to know how many pipes had been open
	based on the number of arguments,
	therefore we'll know how many pipes to close. */

void	ft_close_pipes(t_pipex *data, char **argv)
{
	int	i;
	int	size;

	size = 0;
	while (argv[size])
		size++;
	i = -1;
	while (++i < size - 4 - data->hd_status)
	{
		if (close(data->pipe[i][0]) < 0)
			error_free_exit(data, "Error closing read pipe");
		if (close(data->pipe[i][1]) < 0)
			error_free_exit(data, "Error closing write pipe");
	}
}
