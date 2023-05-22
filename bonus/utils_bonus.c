/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:42:56 by jrouillo          #+#    #+#             */
/*   Updated: 2023/05/22 16:08:44 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
		if (close(data->pipe[i][0]) < 0)
			error_free_exit(data, 0, "Error closing read pipe");
		if (close(data->pipe[i][1]))
			error_free_exit(data, 0, "Error closing write pipe");
	}
}
