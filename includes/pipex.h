/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:03:20 by jrouillo          #+#    #+#             */
/*   Updated: 2023/05/26 17:25:41 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include "ft_printf.h"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_pipex
{
	int			pipe[FOPEN_MAX][2];
	char		*path;
	char		**split_path;
}	t_pipex;

/* PIPEX */
void	ft_exec(char *argv, t_pipex *data);
pid_t	ft_child(int i, char **argv, t_pipex *data);
void	init_struct(t_pipex *data, int argc, char **argv, char **env);

/* OPEN */
int		ft_open_infile(char **argv);
int		ft_open_outfile(char **argv);
int		ft_open_fd(int i, char **argv);

/* UTILS */
int		ft_return_status(pid_t last_pid);
void	ft_dup2(int fd, int i, char **argv, t_pipex *data);
void	ft_close_pipes(t_pipex *data, char **argv);

/* PATH */
char	*ft_freejoin(char *s1, char *s2);
char	*new_path(char *split_path, char *cmd);
char	*find_cmd_path(char *cmd, t_pipex *data);
char	*get_path(char **env);

/* NO PATH */
char	*ft_split_argv(char *argv);
void	ft_no_path(int argc, char **argv);

/* FREE */
void	ft_free_cmd(char **cmd);
void	ft_free(t_pipex *data);
void	error_free_exit(t_pipex *data, char *error_message);
void	fd_error_message(char *str);

#endif