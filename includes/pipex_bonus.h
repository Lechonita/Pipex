/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:03:20 by jrouillo          #+#    #+#             */
/*   Updated: 2023/05/25 13:58:36 by jrouillo         ###   ########.fr       */
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

# define ERROR_ARGS "Invalid number of arguments\n"
# define PIPE "pipe"
# define FORK "fork"
# define PATH "path"

# define BUFFER_SIZE BUFSIZ

typedef struct s_pipex
{
	int			hd_status;
	int			pipe[FOPEN_MAX][2];
	char		*path;
	char		**split_path;
}	t_pipex;

/* PIPEX_BONUS */
void	ft_exec(char *argv, t_pipex *data);
pid_t	ft_child(int i, char **argv, t_pipex *data);
void	init_struct(t_pipex *data, int argc, char **argv, char **env);
bool	ft_check_args(int argc, char **argv);

/* OPEN BONUS */
int		ft_open_infile(char **argv);
// int		ft_open_hd(t_pipex *data);
int		ft_open_outfile(char **argv);
int		ft_open_fd(int i, char **argv, t_pipex *data);

/* UTILS_BONUS */
int		ft_return_status(pid_t last_pid);
void	ft_dup2(int fd, int i, char **argv, t_pipex *data);
void	ft_close_pipes(t_pipex *data, char **argv);

/* PATH_BONUS */
char	*ft_freejoin(char *s1, char *s2);
char	*new_path(char *split_path, char *cmd);
char	*find_cmd_path(char *cmd, t_pipex *data);
char	*get_path(char **env);

/* GNL_BONUS */
char	*get_line(char *str, char *tmp);
char	*get_line_store(char *str);
char	*get_str(int fd, char *str);
char	*get_next_line(int fd);

/* FREE BONUS */
void	ft_free(t_pipex *data);
void	ft_write_error_message(t_pipex *data, int i, int argc, char *str);
void	error_free_exit(t_pipex *data, char *error_message);
void	fd_error_message(char *str);

#endif