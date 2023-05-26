/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:46:15 by jrouillo          #+#    #+#             */
/*   Updated: 2023/05/26 17:45:01 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_open_infile(char **argv)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		fd_error_message(argv[1]);
	return (fd);
}

int	ft_open_hd(char **argv)
{
	int		fd;
	char	*line;

	fd = open("here_doc", O_TRUNC | O_CREAT | O_WRONLY, 0644);
	if (fd < 0)
		fd_error_message("here_doc");
	while (1)
	{
		write(1, "pipe heredoc> ", 14);
		line = get_next_line(0);
		if (line)
		{
			if (!ft_strncmp(line, argv[2], ft_strlen(argv[2]) - 1)
				&& ft_strlen(line) - 1 == ft_strlen(argv[2]))
				break ;
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
		}
		free(line);
	}
	close(fd);
	fd = open("here_doc", O_RDONLY);
	if (fd < 0)
		fd_error_message("here_doc");
	return (fd);
}

int	ft_open_outfile(t_pipex *data, char **argv)
{
	int		i;
	int		fd;

	i = 0;
	while (argv[i])
		i++;
	if (data->hd_status)
		fd = open(argv[i - 1], O_APPEND | O_CREAT | O_WRONLY, 0777);
	else
		fd = open(argv[i - 1], O_TRUNC | O_CREAT | O_WRONLY, 0777);
	if (fd < 0)
		fd_error_message(argv[i - 1]);
	return (fd);
}

int	ft_open_fd(int i, char **argv, t_pipex *data)
{
	if (!i)
	{
		if (data->hd_status)
			return (ft_open_hd(argv));
		return (ft_open_infile(argv));
	}
	else if (!argv[i + 4 + data->hd_status])
		return (ft_open_outfile(data, argv));
	return (0);
}
