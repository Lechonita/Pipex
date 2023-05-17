/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:58:00 by jrouillo          #+#    #+#             */
/*   Updated: 2023/04/27 12:07:13 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_freejoin(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	return (res);
}

/* This function joins data->split[i] & data->split_cmd[0]
	and joins them together, separated with  '/'.
	Return = "data->split_path[i]/data->split_cmd[0]" */

char	*new_path(char *split_path, char *cmd)
{
	char	*cmd_path;

	cmd_path = NULL;
	if (split_path)
	{
		cmd_path = ft_strjoin(split_path, "/");
		cmd_path = ft_freejoin(cmd_path, cmd);
	}
	cmd_path[ft_strlen(cmd_path)] = '\0';
	return (cmd_path);
}

char	*find_cmd_path(t_pipex *data, int i)
{
	char	*cmd_path;
	int		n;

	n = -1;
	while (data->split_path[++n])
	{
		cmd_path = new_path(data->split_path[n], data->split_cmd[i][0]);
		if (!cmd_path)
			return (NULL);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
	}
	return (NULL);
}

char	*get_cmd_path(t_pipex *data, int i)
{
	char	*cmd_path;

	if (!data->split_cmd[i])
		return (NULL);
	cmd_path = NULL;
	if (ft_strchr(data->split_cmd[i][0], '/') != 0)
		return (data->split_cmd[i][0]);
	else
		cmd_path = find_cmd_path(data, i);
	return (cmd_path);
}

char	*get_path(char **env)
{
	while (ft_strncmp("PATH=", *env, 5))
		env++;
	return (*env + 5);
}
