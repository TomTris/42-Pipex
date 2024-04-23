/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_man.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:21:54 by qdo               #+#    #+#             */
/*   Updated: 2024/04/23 13:09:14 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_cmd_execute(t_cmd_save *cmd_save, char **env, int i, int fd_to_close)
{
	char	*temp;
	int		j;

	j = 0;
	while (cmd_save[0].path_save[j] && j >= 0)
	{
		temp = ft_strjoin(cmd_save[0].path_save[j], cmd_save[i].cmd[0]);
		if (temp == 0)
			return (perror("Malloc"), ft_free(0, cmd_save), exit(1), -99);
		if (access(temp, F_OK) == 0)
			if (execve(temp, cmd_save[i].cmd, env) == -1)
				return (perror("execve"), close(fd_to_close),
					free(temp), ft_free(0, cmd_save), exit(1), -99);
		free(temp);
		j++;
	}
	perror(cmd_save[i].cmd[0]);
	close(fd_to_close);
	return (ft_free(0, cmd_save), exit(1), -99);
}

int	ft_pid_equal_0(t_cmd_save *cmd_save, int i, int fd_in, int *pipe_fd_new)
{
	if (close(pipe_fd_new[0]) == -1)
		return (close(fd_in), close(pipe_fd_new[1]),
			ft_free(0, cmd_save), exit(1), -99);
	if (dup2(fd_in, STDIN_FILENO) == -1
		|| dup2(pipe_fd_new[1], STDOUT_FILENO) == -1)
		return (close(fd_in), close(pipe_fd_new[1]),
			ft_free(0, cmd_save), exit(1), -99);
	return (ft_cmd_execute(cmd_save, cmd_save[0].env,
			i, pipe_fd_new[1]), exit(1), -99);
}

int	ft_recursion_fork_pid(t_cmd_save *cmd_save, int i, int fd_in)
{
	int		pipe_fd_new[2];
	pid_t	pid;

	if (pipe(pipe_fd_new) == -1)
		return (close(fd_in), ft_free(0, cmd_save), -1);
	pid = fork();
	if (pid == -1)
		return (close(pipe_fd_new[0]), close(pipe_fd_new[1]),
			close(fd_in), ft_free(0, cmd_save), -1);
	if (pid != 0)
		if (ft_pid_create(pid) == NULL)
			return (close(fd_in), close(pipe_fd_new[0]),
				close(pipe_fd_new[1]), ft_free(0, cmd_save), -1);
	if (i == 1)
		return (ft_i_1_or_last(cmd_save, -1, pipe_fd_new, pid));
	if (i == cmd_save[0].ac - 3)
		return (ft_i_1_or_last(cmd_save, fd_in, pipe_fd_new, pid));
	if (pid == 0)
		return (ft_pid_equal_0(cmd_save, i, fd_in, pipe_fd_new), -99);
	if (close(fd_in) == -1)
		return (close(pipe_fd_new[0]), close(pipe_fd_new[1]),
			ft_free(0, cmd_save), -1);
	if (close(pipe_fd_new[1]) == -1)
		return (close(pipe_fd_new[0]), ft_free(0, cmd_save), -1);
	return (pipe_fd_new[0]);
}

void	ft_wait_pid(void)
{
	t_pid_wait	*temp;
	int			i;

	temp = ft_pid_create(-2);
	i = 0;
	while (++i <= temp[0].nbr)
		waitpid(temp[i].pid, NULL, 0);
}

//path_save has already '/' at the end, like /usr/bin/, just join cmd to it.
int	main_manda(int ac, const char **av, char **env)
{
	t_cmd_save	*cmd_save;
	int			i;
	int			fd_in;

	cmd_save = ft_cmd_save_create(ac, av);
	ft_create_path_save(env, cmd_save);
	i = 0;
	fd_in = -1;
	while (++i <= ac - 3)
	{
		fd_in = ft_recursion_fork_pid(cmd_save, i, fd_in);
		if (fd_in == -1)
			return (ft_wait_pid(), exit(1), -99);
	}
	ft_wait_pid();
	ft_free(0, cmd_save);
	return (0);
}
