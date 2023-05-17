/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:46:15 by jrouillo          #+#    #+#             */
/*   Updated: 2023/05/17 13:44:47 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	ft_open_infile(char **argv)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error_message(argv[1]);
	return (fd);
}

// int	ft_open_hd()
// {
	
// }

static int	ft_open_outfile(char **argv)
{
	int	i;
	int	fd;

	i = 0;
	while (argv[i])
		i++;
	fd = open(argv[i - 1], O_TRUNC | O_CREAT | O_WRONLY, 0777);
	if (fd < 0)
		error_message(argv[i - 1]);
	return (fd);
}

int	ft_open_file(int i, char **argv, t_pipex *data)
{
	if (!i)
		// if (data->hd_status)
		// 	return();
		return (ft_open_infile(argv));
	else if (!argv[i + 4 + data->hd_status])
		return (ft_open_outfile(argv));
	return (0);
}
