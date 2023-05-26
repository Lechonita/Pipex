/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_path_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 00:12:21 by lechon            #+#    #+#             */
/*   Updated: 2023/05/26 17:41:24 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_split_argv(char *argv)
{
	int		i;
	int		j;
	char	*res;
	int		size;

	i = 0;
	j = 0;
	while (argv[i] && (argv[i] == 32 || argv[i] == 9))
		i++;
	size = i;
	while (argv[size] && argv[size] != ' ')
		size++;
	res = malloc(sizeof(char) * (size - i + 1));
	if (!res)
		return (NULL);
	while (argv[i] && i < size)
	{
		res[j++] = argv[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}

int	determine_i(t_pipex *data)
{
	int	i;

	if (data->hd_status)
		i = 3;
	else
		i = 2;
	return (i);
}

void	ft_no_path(t_pipex *data, int argc, char **argv)
{
	int		i;
	int		flag;
	char	*res;

	i = determine_i(data) - 1;
	flag = 0;
	while (++i < argc - 1)
	{
		if (access(argv[i], F_OK | X_OK) != 0)
		{
			if (ft_strchr(argv[i], ' ') != 0)
			{
				argv[i] = ft_split_argv(argv[i]);
				flag = 1;
			}
			res = ft_strjoin(argv[i], ": command not found\n");
			ft_putstr_fd(res, 2);
			free(res);
			if (flag == 1)
			{
				free(argv[i]);
				flag = 0;
			}
		}
	}
}
