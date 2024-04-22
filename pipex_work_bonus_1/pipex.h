/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 23:44:49 by qdo               #+#    #+#             */
/*   Updated: 2024/04/22 20:36:08 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>
# include "libft/ft_printf.h"
# include <errno.h>

typedef struct s_cmd_save
{
	int			nbr;
	char		**cmd;
	char		**path_save;
	char		**env;
	int			ac;
	const char	*av_1;
	const char	*av_last;
}	t_cmd_save;

typedef struct s_pid_wait
{
	int		nbr;
	pid_t	pid;
}	t_pid_wait;

int			ft_create_path_save(char **env, t_cmd_save *cmd_save);
void		ft_free(char **split, t_cmd_save *cmd_save);
t_cmd_save	*ft_cmd_save_create(int ac, const char **av);
int			ft_i_1_or_last(t_cmd_save *cmd_save, int fd_in,
				int *pipe_fd_new, pid_t pid);
t_pid_wait	*ft_pid_create(pid_t pid);
int			ft_cmd_execute(t_cmd_save *cmd_save, char **env,
				int i, int fd_to_close);
t_pid_wait	*ft_pid_create(pid_t pid_to_add);

#endif