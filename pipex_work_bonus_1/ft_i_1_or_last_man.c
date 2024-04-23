/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_i_1_or_last.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:39:41 by qdo               #+#    #+#             */
/*   Updated: 2024/04/22 20:16:55 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//fd_in is just for declaring, the value doesn't matter
static int	ft_i_1(t_cmd_save *cmd_save, int *pipe_fd_new, pid_t pid, int fd_in)
{
	if (pid == 0)
	{
		fd_in = open(cmd_save[0].av_1, O_RDONLY);
		if (fd_in == -1)
			return (perror(cmd_save[0].av_1), ft_free(0, cmd_save),
				close(pipe_fd_new[0]), close(pipe_fd_new[1]), exit(1), -99);
		if (dup2(fd_in, STDIN_FILENO) == -1)
			return (perror("dup2"), ft_free(0, cmd_save), close(fd_in),
				close(pipe_fd_new[0]), close(pipe_fd_new[1]), exit(1), -99);
		if (close(fd_in) == -1)
			return (perror("close"), ft_free(0, cmd_save),
				close(pipe_fd_new[0]), close(pipe_fd_new[1]), exit(1), -99);
		if (dup2(pipe_fd_new[1], STDOUT_FILENO) == -1)
			return (perror("dup2"), ft_free(0, cmd_save),
				close(pipe_fd_new[0]), close(pipe_fd_new[1]), exit(1), -99);
		if (close(pipe_fd_new[0]) == -1)
			return (perror("close"), ft_free(0, cmd_save),
				close(pipe_fd_new[1]), exit(1), -99);
		return (ft_cmd_execute(cmd_save, cmd_save[0].env,
				1, pipe_fd_new[1]), -99);
	}
	if (close(pipe_fd_new[1]) == -1)
		return (perror("close"), ft_free(0, cmd_save),
			close(pipe_fd_new[0]), -1);
	return (pipe_fd_new[0]);
}

static int	ft_i_last(t_cmd_save *cmd_save,
		int *pipe_fd_new, pid_t pid, int fd_in)
{
	int	fd_out;

	if (close(pipe_fd_new[1]) == -1)
		return (perror("close"), ft_free(0, cmd_save),
			close(pipe_fd_new[0]), close(fd_in), -1);
	if (close(pipe_fd_new[0]) == -1)
		return (perror("close"), ft_free(0, cmd_save), close(fd_in), -1);
	if (pid == 0)
	{
		fd_out = open(cmd_save[0].av_last, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out == -1)
			return (perror(cmd_save[0].av_last), ft_free(0, cmd_save),
				close(fd_in), exit(1), -99);
		if (dup2(fd_out, STDOUT_FILENO) == -1
			|| dup2(fd_in, STDIN_FILENO) == -1)
			return (perror("dup2"), ft_free(0, cmd_save), close(fd_in),
				close(fd_out), exit(1), -99);
		if (close(fd_in) == -1)
			return (perror("dup2"), ft_free(0, cmd_save),
				close(fd_out), exit(1), -99);
		return (ft_cmd_execute(cmd_save, cmd_save[0].env,
				cmd_save[0].ac - 3, fd_out), -99);
	}
	return (close(fd_in));
}

int	ft_i_1_or_last(t_cmd_save *cmd_save, int fd_in, int *pipe_fd_new, pid_t pid)
{
	if (fd_in == -1)
		return (ft_i_1(cmd_save, pipe_fd_new, pid, 0));
	return (ft_i_last(cmd_save, pipe_fd_new, pid, fd_in));
}
