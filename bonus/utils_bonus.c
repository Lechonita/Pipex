/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:42:56 by jrouillo          #+#    #+#             */
/*   Updated: 2023/05/23 18:01:14 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

/* Closing all piped one by one.
	Finding size will allow to know how many pipes had been open,
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
			error_free_exit(data, 0, "Error closing read pipe");
		if (close(data->pipe[i][1]) < 0)
			error_free_exit(data, 0, "Error closing write pipe");
	}
}
