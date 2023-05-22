/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:08:17 by jrouillo          #+#    #+#             */
/*   Updated: 2023/05/22 18:15:42 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// void	infile_input(t_pipex *data, int argc, char **argv)
// {
// 	char	*line;

// 	while (1)
// 	{
// 		write(1, "pipe heredoc> ", 14);
// 		line = get_next_line(0);
// 		if (line)
// 		{
// 			if (!ft_strncmp(line, argv[2], ft_strlen(argv[2])))
// 				break ;
// 			else
// 			{
// 				write(data->infile, line, ft_strlen(line));
// 				write(data->infile, "\n", 1);
// 			}
// 		}
// 		free(line);
// 		// close(data->infile);
// 		// data->infile = open("here_doc", O_RDONLY);
// 		// if (data->infile < 0)
// 			// fd_error("infile");
// 		data->outfile = open(argv[argc - 1], O_APPEND | O_CREAT | O_RDWR, 0777);
// 		if (data->outfile < 0)
// 			fd_error(argv[argc - 1]);
// 	}
// }

// void	init_struct_bonus(t_pipex *data, int argc, char **env)
// {
// 	data->infile = open("here_doc", O_TRUNC | O_CREAT | O_WRONLY, 0644);
// 	if (data->infile < 0)
// 		fd_error("here_doc");
// 	data->nb_cmd = argc - 4;
// 	data->path = get_path(env);
// 	if (!data->path)
// 	{
// 		ft_putstr_fd("command not found: ", 2);
// 		ft_putstr_fd(PATH, 2);
// 		ft_putchar_fd('\n', 2);
// 	}
// 	data->split_path = ft_split(data->path, ':');
// 	if (!data->split_path)
// 		exit_message(data, "command not found", PATH);
// 	data->split_path = ft_split(data->path, ':');
// 	data->split_cmd = ft_calloc((data->nb_cmd), sizeof(char **));
// 	data->cmd_path = ft_calloc((data->nb_cmd), sizeof(char *));
// }

void	init_struct(t_pipex *data, int argc, char **argv, char **env)
{
	int	i;

	if (!ft_strncmp(argv[1], "here_doc", 9))
		data->hd_status = 1;
	else
		data->hd_status = 0;
	data->path = get_path(env);
	if (data->path)
	{
		data->split_path = ft_split(data->path, ':');
		{
			if (!data->split_path)
				error_free_exit(data, 0, "Allocation failed: data->split_path\n");
		}
	}
	data->pipe = malloc(sizeof(int *) * (argc - 4 - data->hd_status));
	// data->pipe = NULL; // TESTING HERE
	if (!data->pipe)
		error_free_exit(data, 0, "Allocation failed: data->pipe");
	i = 0;
	// printf("je passe par ici, avant de piper mes pipes\n");
	while (i < argc - 4 - data->hd_status)
	{
		data->pipe[i] = malloc(sizeof(int) * 2);
		pipe(data->pipe[i]);
		// printf("ici le data->pipe[%d][0] = %d\n", i, data->pipe[i][0]);
		// printf("et  le data->pipe[%d][1] = %d\n", i, data->pipe[i][1]);
		i++;
	}
}
