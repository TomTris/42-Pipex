/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_bn2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 23:05:15 by qdo               #+#    #+#             */
/*   Updated: 2024/04/23 17:39:18 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_cmd_save_create_bn(const char **av, t_save_bn *save_bn, int fd_to_close)
{
	save_bn->cmd = (char ***)malloc(3 * sizeof(char **));
	if (save_bn->cmd == 0)
		return (perror("malloc"), close(fd_to_close),
			ft_free_bn(0, save_bn), exit(1), -99);
	save_bn->cmd[1] = 0;
	save_bn->cmd[2] = 0;
	save_bn->cmd[0] = ft_split(av[3], ' ');
	if (save_bn->cmd[0] == 0 || save_bn->cmd[0][0] == 0)
		return (perror("cmd faild"), close(fd_to_close),
			ft_free_bn(0, save_bn), exit(1), -99);
	save_bn->cmd[1] = ft_split(av[4], ' ');
	if (save_bn->cmd[1] == 0 || save_bn->cmd[1][0] == 0)
		return (perror("cmd faild"), close(fd_to_close),
			ft_free_bn(0, save_bn), exit(1), -99);
	return (1);
}

int	ft_create_path_save_bn(char **env, t_save_bn *save_bn,
		int fd_to_close, int i)
{
	char	**ret;
	char	*temp;

	while (env[++i])
		if (env[i][0] == 'P' && env[i][1] == 'A' && env[i][2] == 'T'
			&& env[i][3] == 'H' && env[i][4] == '=' && env[i][5] == '/')
			break ;
	if (env[i] == 0)
		return (perror("Path not found in env\n"), close(fd_to_close),
			ft_free_bn(0, save_bn), exit(1), 1);
	ret = ft_split(env[i] + 5, ':');
	if (ret == 0)
		return (perror("Malloc\n"), close(fd_to_close),
			ft_free_bn(0, save_bn), exit(1), 1);
	i = -1;
	while (ret[++i])
	{
		temp = ft_strjoin(ret[i], "/");
		if (temp == 0)
			return (perror("Malloc\n"), close(fd_to_close),
				ft_free_bn(ret, save_bn), exit(1), 1);
		free(ret[i]);
		ret[i] = temp;
	}
	return (save_bn->path_save = ret, save_bn->env = env, 0);
}

int	ft_input_read(const char **av, int *pipe_in)
{
	char	*buf;
	char	*stop;

	if (close(pipe_in[0]) == -1)
		return (perror("close"), close(pipe_in[1]), exit(1), -99);
	if (dup2(pipe_in[1], STDOUT_FILENO) == -1)
		return (perror("dup2"), close(pipe_in[1]), exit(1), -99);
	buf = get_next_line(0);
	stop = ft_strjoin((char *)av[2], "\n");
	if (stop == 0)
		return (perror("close"), free(buf), close(pipe_in[1]), exit(1), -99);
	while (ft_strcmp_pipex(buf, stop) != 1 && buf != 0)
	{
		free(buf);
		buf = get_next_line(0);
		if (buf != 0)
			if (ft_printf("%s", buf) == -1)
				return (free(stop), free(buf), close(pipe_in[1]), exit(1), -99);
	}
	if (close(pipe_in[1]) == -1)
		return (free(stop), free(buf), exit(1), -99);
	return (free(stop), free(buf), exit(0), -99);
}

int	ft_input_read_n_create_bn(const char **av)
{
	int		pipe_in[2];
	pid_t	pid;
	pid_t	pid_check;

	if (pipe(pipe_in) == -1)
		return (perror("pipe"), exit(1), -99);
	pid = fork();
	if (pid == -1)
		return (close(pipe_in[0]), close(pipe_in[1]), exit(1), -99);
	if (pid == 0)
		ft_input_read(av, pipe_in);
	pid_check = waitpid(pid, 0, 0);
	if (pid_check == -1)
		return (close(pipe_in[0]), close(pipe_in[1]), exit(1), -99);
	if (close(pipe_in[1]) == -1)
		return (perror("close"), close(pipe_in[0]), exit(1), -99);
	return (pipe_in[0]);
}

pid_t	*ft_wait_pid_bn(pid_t pid, int check)
{
	static pid_t	*pid_save = 0;
	static int		i = 0;

	if (check == -3)
		return (free(pid_save), pid_save = 0, NULL);
	if (pid_save == 0)
	{
		pid_save = (pid_t *)malloc(3 * sizeof(pid_t));
		if (pid_save == 0)
			return (NULL);
		pid_save[0] = 0;
		pid_save[1] = 0;
		pid_save[2] = 0;
	}
	if (check == -2)
		return (pid_save);
	if (i == 0 || i == 1)
	{
		pid_save[i] = pid;
		i++;
		return (pid_save);
	}
	return (free(pid_save), pid_save = 0, NULL);
}
