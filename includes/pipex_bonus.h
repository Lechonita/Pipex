/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:03:20 by jrouillo          #+#    #+#             */
/*   Updated: 2023/05/26 17:46:48 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft.h"
# include "ft_printf.h"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdbool.h>

# define BUFFER_SIZE BUFSIZ

typedef struct s_pipex
{
	int			hd_status;
	int			pipe[FOPEN_MAX][2];
	char		*path;
	char		**split_path;
}	t_pipex;

/* PIPEX BONUS */
void	ft_exec(char *argv, t_pipex *data);
pid_t	ft_child(int i, char **argv, t_pipex *data);
void	init_struct(t_pipex *data, int argc, char **argv, char **env);
bool	ft_check_args(int argc, char **argv);

/* OPEN BONUS */
int		ft_open_infile(char **argv);
int		ft_open_hd(char **argv);
int		ft_open_outfile(t_pipex *data, char **argv);
int		ft_open_fd(int i, char **argv, t_pipex *data);

/* UTILS BONUS */
int		ft_return_status(t_pipex *data, pid_t last_pid);
void	ft_dup2(int fd, int i, char **argv, t_pipex *data);
void	ft_close_pipes(t_pipex *data, char **argv);

/* PATH BONUS */
char	*ft_freejoin(char *s1, char *s2);
char	*new_path(char *split_path, char *cmd);
char	*find_cmd_path(char *cmd, t_pipex *data);
char	*get_path(char **env);

/* NO PATH BONUS */
char	*ft_split_argv(char *argv);
int		determine_i(t_pipex *data);
void	ft_no_path(t_pipex *data, int argc, char **argv);

/* GNL BONUS */
char	*get_line(char *str, char *tmp);
char	*get_line_store(char *str);
char	*get_str(int fd, char *str);
char	*get_next_line(int fd);

/* FREE BONUS */
void	ft_free_cmd(char **cmd);
void	ft_free(t_pipex *data);
void	error_free_exit(t_pipex *data, char *error_message);
void	fd_error_message(char *str);

#endif