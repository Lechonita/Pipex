/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:49:52 by jrouillo          #+#    #+#             */
/*   Updated: 2023/05/26 17:21:05 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_cmd(char **cmd)
{
	int	i;

	if (cmd)
	{
		i = -1;
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
	}
}

/* Free data->split_path & free data->cmd ( both char **) */

void	ft_free(t_pipex *data)
{
	int	i;

	if (data->split_path)
	{
		i = -1;
		while (data->split_path[++i])
			free(data->split_path[i]);
		free(data->split_path);
	}
}

/* Write error message, free and exit */

void	error_free_exit(t_pipex *data, char *error_message)
{
	char	*res;

	res = ft_strjoin(error_message, "\n");
	ft_putstr_fd(res, 2);
	free(res);
	ft_free(data);
	exit (1);
}

/* Write error message for fd */

void	fd_error_message(char *str)
{
	char	*res;

	res = ft_strjoin("pipex: ", str);
	res = ft_freejoin(res, ": ");
	res = ft_freejoin(res, strerror(errno));
	res = ft_freejoin(res, "\n");
	ft_putstr_fd(res, 2);
	free(res);
}
