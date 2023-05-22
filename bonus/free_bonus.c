/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:37:53 by jrouillo          #+#    #+#             */
/*   Updated: 2023/05/22 17:51:24 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// void	free_cmd(t_pipex *data)
// {
// 	int	i;
// 	int	j;

// 	i = -1;
// 	j = -1;
// 	if (!data)
// 		return ;
// 	if (data->split_cmd)
// 	{
// 		while (data->split_cmd[++i])
// 		{
// 			while (data->split_cmd[i][++j])
// 				free(data->split_cmd[i][j]);
// 		}
// 		free(data->split_cmd);
// 	}
// 	return ;
// }

// void	free_path(t_pipex *data)
// {
// 	int	i;

// 	i = -1;
// 	if (!data)
// 		return ;
// 	if (data->split_path)
// 	{
// 		while (data->split_path[++i])
// 			free(data->split_path[i]);
// 		free(data->split_path);
// 	}
// 	i = -1;
// 	if (data->cmd_path)
// 	{
// 		while (data->cmd_path[++i])
// 			free(data->cmd_path[i]);
// 		free(data->cmd_path);
// 	}
// 	return ;
// }

/* Free & close */

// void	ft_free(t_pipex *data)
// {
// 	if (data->infile)
// 		close(data->infile);
// 	if (data->outfile)
// 		close(data->outfile);
// 	free_path(data);
// 	free_cmd(data);
// 	ft_close(data);
// 	// if (data)
// 	// free(data);
// 	return ;
// }

/* Write error message, free, close, exit */

// void	exit_message(t_pipex *data, char *error, char *str)
// {
// 	ft_putstr_fd(error, 2);
// 	ft_putstr_fd(": ", 2);
// 	ft_putstr_fd(str, 2);
// 	ft_putchar_fd('\n', 2);
// 	// ft_printf("%s: %s\n", error, str);
// 	ft_close(data);
// 	ft_free(data);
// 	exit (1);
// 	return ;
// }

/* Write error message, free, exit */

// void	ft_perror(t_pipex *data, char *str)
// {
// 	ft_putstr_fd(strerror(errno), 2);
// 	ft_putstr_fd(": ", 2);
// 	ft_putstr_fd(str, 2);
// 	ft_putchar_fd('\n', 2);
// 	// ft_printf("%s: %s\n", strerror(errno), str);
// 	ft_free(data);
// 	exit (errno);
// 	return ;
// }

/* Free data->pipe (int **) */

void	ft_free_pipes(t_pipex *data)
{
	int	i;

	// printf("Je passe par la\n");
	if (!data->pipe)
		return ;
	i = -1;
	while (data->pipe[++i])
		free(data->pipe[i]);
	free(data->pipe);
}

/* Free data->split_path (char **) */

void	ft_free_split_path(t_pipex *data)
{
	int	i;

	if (!data->split_path)
		return ;
	i = -1;
	while (data->split_path[++i])
		free(data->split_path[i]);
	free(data->split_path);
}

/* Write error message, free, exit */

void	error_free_exit(t_pipex *data, char *argv, char *error_message)
{
	if (argv != 0)
	{
		ft_putstr_fd(argv, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(error_message, 2);
	ft_putchar_fd('\n', 2);
	ft_free_split_path(data);
	ft_free_pipes(data);
	exit (errno);
}

/* Write error message */

void	fd_error(char *str)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
	return;
}
