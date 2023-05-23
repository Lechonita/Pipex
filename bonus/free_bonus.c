/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:37:53 by jrouillo          #+#    #+#             */
/*   Updated: 2023/05/23 18:00:38 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	error_free_exit(t_pipex *data, char *argv, char *error_message)
{
	char	*res;
	char	*tmp;

	res = NULL;
	tmp = NULL;
	if (argv != 0)
	// {
		tmp = ft_freejoin(argv, ": ");
		// ft_putstr_fd(argv, 2);
		// ft_putstr_fd(": ", 2);
	// }
	if (tmp)
	{
		res = ft_strjoin(tmp, error_message);
		res = ft_freejoin(res, "\n");
	}
	else
	{
		res = ft_strjoin(error_message, "\n");
		res = ft_freejoin(res, "\0");
	}
	// ft_putstr_fd(error_message, 2);
	// ft_putchar_fd('\n', 2);
	ft_putstr_fd(res, 2);
	if (tmp)
		free(tmp);
	free(res);
	ft_free(data);
	exit (1);
	printf("IS IT HERE\n");
}

/* Write error message for fd*/

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
