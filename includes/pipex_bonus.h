/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:03:20 by jrouillo          #+#    #+#             */
/*   Updated: 2023/05/17 14:02:15 by jrouillo         ###   ########.fr       */
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
// # define ERROR_FD_IN "dup fd_in"
// # define ERROR_FD_OUT "dup fd_out"

# define BUFFER_SIZE BUFSIZ

typedef struct s_pipex
{
	int			**pipe;
	int			hd_status;
	char		*path;
	char		**split_path;
}	t_pipex;

/* PIPEX_BONUS */
pid_t	ft_pipe(t_pipex *data, char *argv, char **env, int i);
pid_t	do_bonus(int argc, char **argv, char **env);
pid_t	do_mandatory(int argc, char **argv, char **env);

/* INIT_BONUS*/
void	infile_input(t_pipex *data, int argc, char **argv);
void	init_struct_bonus(t_pipex *data, int argc, char **env);
void	init_struct(t_pipex *data, int argc, char **argv, char **env);

/* UTILS_BONUS */
int		ft_waitpid(pid_t last_pid);
void	ft_dup2(int fd, int i, char **argv, t_pipex *data);
void	ft_close_pipe(t_pipex *data, char **argv);
void	ft_open(t_pipex *data);

/* PATH_BONUS */
char	*ft_freejoin(char *s1, char *s2);
char	*new_path(char *split_path, char *cmd);
char	*find_cmd_path(char *cmd, t_pipex *data);
char	*get_cmd_path(t_pipex *data, int i);
char	*get_path(char **env);

/* GNL_BONUS */
char	*get_line(char *str, char *tmp);
char	*get_line_store(char *str);
char	*get_str(int fd, char *str);
char	*get_next_line(int fd);

/* FREE_BONUS */
void	free_cmd(t_pipex *data);
void	free_path(t_pipex *data);
void	ft_free(t_pipex *data);
void	exit_message(t_pipex *data, char *error, char	*str);
void	ft_perror(t_pipex *data, char *str);
void	error_message(char *str);

/* OPEN */
int		ft_open_file(int i, char **argv, t_pipex *data);

#endif