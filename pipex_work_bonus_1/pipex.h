/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 23:44:49 by qdo               #+#    #+#             */
/*   Updated: 2024/04/23 16:52:28 by qdo              ###   ########.fr       */
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

typedef struct s_save_bn
{
	int			ac;
	const char	**av;
	char		***cmd;
	char		**path_save;
	char		**env;
}	t_save_bn;

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
int			main_manda(int ac, const char **av, char **env);

int			ft_input_read_n_create_bn(const char **av);
void		ft_free_bn(char **split, t_save_bn *save_bn);
void		ft_zero_save(int ac, const char **av, char **env,
				t_save_bn *save_bn);
int			ft_create_path_save_bn(char **env, t_save_bn *save_bn,
				int fd_to_close, int i);
int			ft_cmd_save_create_bn(const char **av, t_save_bn *save_bn,
				int fd_to_close);
int			ft_strcmp_pipex(char *str1, char *str2);
int			ft_usage(void);
pid_t		*ft_wait_pid_bn(pid_t pid, int check);
int			ft_execute_1(t_save_bn *save_bn, int pipe_old);
int			ft_execute_2(t_save_bn *save_bn, int pipe_old);

#endif