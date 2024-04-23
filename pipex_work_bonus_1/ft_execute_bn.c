/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_bn.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:55:22 by qdo               #+#    #+#             */
/*   Updated: 2024/04/23 20:32:32 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_cmd_execute_bn(t_save_bn *save_bn, char **env,
		int i, int fd_to_close)
{
	char	*temp;
	int		j;

	j = 0;
	while (save_bn->path_save[j])
	{
		temp = ft_strjoin(save_bn->path_save[j], save_bn->cmd[i][0]);
		if (temp == 0)
			return (perror("Malloc"), ft_free_bn(0, save_bn), exit(1), -99);
		if (access(temp, F_OK) == 0)
		{
			if (execve(temp, save_bn->cmd[i], env) == -1)
				return (perror("execve"), close(fd_to_close),
					free(temp), ft_free_bn(0, save_bn), exit(1), -99);
		}
		free(temp);
		j++;
	}
	perror(save_bn->cmd[i][0]);
	close(fd_to_close);
	return (ft_free_bn(0, save_bn), exit(1), -99);
}

static int	ft_execute_2_pid_0(int pipe_old, t_save_bn *save_bn)
{
	int	outfile_fd;

	if (dup2(pipe_old, STDIN_FILENO) == -1)
		return (perror("dup2"), close(pipe_old),
			ft_free_bn(0, save_bn), exit(1), -99);
	outfile_fd = open(save_bn->av[save_bn->ac - 1],
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (outfile_fd == -1)
		return (perror("open"), close(pipe_old), ft_free_bn(0, save_bn),
			close(outfile_fd), exit(1), -99);
	if (dup2(outfile_fd, STDOUT_FILENO) == -1)
		return (perror("dup2"), close(pipe_old), ft_free_bn(0, save_bn),
			close(outfile_fd), exit(1), -99);
	return (ft_cmd_execute_bn(save_bn, save_bn->env, 1, outfile_fd), -99);
}

int	ft_execute_2(t_save_bn *save_bn, int pipe_old)
{
	pid_t	pid;
	pid_t	*pid_save;

	pid_save = ft_wait_pid_bn(0, -2);
	pid = fork();
	if (pid == -1)
		return (waitpid(pid_save[0], 0, 0), perror("fork"),
			close(pipe_old), ft_free_bn(0, save_bn), exit(1), -99);
	if (pid == 0)
		return (ft_execute_2_pid_0(pipe_old, save_bn), -99);
	ft_wait_pid_bn(pid, 0);
	if (close(pipe_old) == -1)
		return (waitpid(pid_save[0], 0, 0), waitpid(pid, 0, 0),
			perror("close"), ft_free_bn(0, save_bn), exit(1), -99);
	return (1);
}

int	ft_execute_1_pid_0(int pipe_old, t_save_bn *save_bn, int *pipe_new)
{
	if (dup2(pipe_old, STDIN_FILENO) == -1)
		return (perror("dup2"), close(pipe_old), close(pipe_new[0]),
			close(pipe_new[1]), ft_free_bn(0, save_bn), exit(1), -99);
	if (close(pipe_new[0]) == -1)
		return (perror("close"), close(pipe_old), close(pipe_new[1]),
			ft_free_bn(0, save_bn), exit(1), -99);
	if (dup2(pipe_new[1], STDOUT_FILENO) == -1)
		return (perror("dup2"), close(pipe_old), close(pipe_new[1]),
			ft_free_bn(0, save_bn), exit(1), -99);
	return (ft_cmd_execute_bn(save_bn, save_bn->env, 0, pipe_new[1]), -99);
}

int	ft_execute_1(t_save_bn *save_bn, int pipe_old)
{
	int		pipe_new[2];
	pid_t	pid;

	if (pipe(pipe_new) == -1)
		return (perror("pipe"), close(pipe_old),
			ft_free_bn(0, save_bn), exit(1), -99);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), close(pipe_old), close(pipe_new[0]),
			close(pipe_new[1]), ft_free_bn(0, save_bn), exit(1), -99);
	if (pid == 0)
		return (ft_execute_1_pid_0(pipe_old, save_bn, pipe_new), -99);
	if (ft_wait_pid_bn(pid, 0) == NULL)
		return (perror("malloc"), waitpid(pid, 0, 0), close(pipe_old),
			close(pipe_new[0]), close(pipe_new[1]),
			ft_free_bn(0, save_bn), exit(1), -99);
	if (close(pipe_new[1]) == -1)
		return (perror("close"), close(pipe_old), close(pipe_new[0]),
			ft_free_bn(0, save_bn), exit(1), -99);
	if (close(pipe_old) == -1)
		return (perror("close"), close(pipe_new[0]),
			ft_free_bn(0, save_bn), exit(1), -99);
	return (pipe_new[0]);
}
