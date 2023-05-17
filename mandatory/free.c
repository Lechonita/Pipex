/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:49:52 by jrouillo          #+#    #+#             */
/*   Updated: 2023/05/02 14:56:53 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_cmd(t_pipex *data)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	if (!data)
		return ;
	if (data->split_cmd)
	{
		while (data->split_cmd[++i])
		{
			while (data->split_cmd[i][++j])
				free(data->split_cmd[i][j]);
		}
		free(data->split_cmd);
	}
	return ;
}

void	free_path(t_pipex *data)
{
	int	i;

	i = -1;
	if (!data)
		return ;
	if (data->split_path)
	{
		while (data->split_path[++i])
			free(data->split_path[i]);
		free(data->split_path);
	}
	i = -1;
	if (data->cmd_path)
	{
		while (data->cmd_path[++i])
			free(data->cmd_path[i]);
		free(data->cmd_path);
	}
	return ;
}

void	ft_free(t_pipex *data)
{
	if (data->infile > 0)
		close(data->infile);
	if (data->outfile)
		close(data->outfile);
	ft_close(data);
	free_path(data);
	free_cmd(data);
	if (data)
		free(data);
	return ;
}

void	exit_message(t_pipex *data, char *error, char	*str)
{
	ft_printf("%s: %s\n", error, str);
	ft_free(data);
	exit (1);
	return ;
}

void	ft_perror(t_pipex *data, char	*str)
{
	// static 
	ft_printf("%s: %s\n", strerror(errno), str);
	ft_free(data);
	exit (errno);
	return ;
}
