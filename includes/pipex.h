/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:03:20 by jrouillo          #+#    #+#             */
/*   Updated: 2023/05/02 14:56:53 by jrouillo         ###   ########.fr       */
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

# define ERROR_ARGS "input: Invalid number of arguments\n"
# define PIPE "pipe"
# define FORK "fork"
# define ERROR_PATH "path"
# define ERROR_FD_IN "dup fd_in"
# define ERROR_FD_OUT "dup fd_out"

# define BUFFER_SIZE BUFSIZ

typedef struct s_pipex
{
	int			infile;
	int			outfile;
	int			pipe[2];
	int			nb_cmd;
	char		*path;
	char		**split_path;
	char		***split_cmd;
	char		**cmd_path;
}	t_pipex;

/* PIPEX */

pid_t	ft_pipe(t_pipex *data, char *argv, char **env, int i);
void	init_struct(t_pipex *data, int argc, char **argv, char **env);

/* UTILS */
int		ft_waitpid(pid_t last_pid);
void	ft_dup2(int new_read, int new_write, t_pipex *data);
void	ft_close(t_pipex *data);
void	ft_open(t_pipex *data);

/* PATH */
char	*ft_freejoin(char *s1, char *s2);
char	*new_path(char *split_path, char *cmd);
char	*find_cmd_path(t_pipex *data, int i);
char	*get_cmd_path(t_pipex *data, int i);
char	*get_path(char **env);

/* FREE */
void	free_cmd(t_pipex *data);
void	free_path(t_pipex *data);
void	ft_free(t_pipex *data);
void	exit_message(t_pipex *data, char *error, char	*str);
void	ft_perror(t_pipex *data, char	*str);

#endif