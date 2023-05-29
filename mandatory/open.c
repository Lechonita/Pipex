/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:38:34 by jrouillo          #+#    #+#             */
/*   Updated: 2023/05/29 13:49:39 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_open_infile(char **argv)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		fd_error_message(argv[1]);
	return (fd);
}

int	ft_open_outfile(char **argv)
{
	int		i;
	int		fd;

	i = 0;
	while (argv[i])
		i++;
	fd = open(argv[i - 1], O_TRUNC | O_CREAT | O_WRONLY, 0777);
	if (fd < 0)
		fd_error_message(argv[i - 1]);
	return (fd);
}

int	ft_open_fd(int i, char **argv)
{
	if (!i)
		return (ft_open_infile(argv));
	else if (!argv[i + 4])
		return (ft_open_outfile(argv));
	return (0);
}
