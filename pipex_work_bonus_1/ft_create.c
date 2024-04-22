/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:46:18 by qdo               #+#    #+#             */
/*   Updated: 2024/04/22 20:25:52 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_create_path_save(char **env, t_cmd_save *cmd_save)
{
	char	**ret;
	int		i;
	char	*temp;

	i = -1;
	while (env[++i])
		if (env[i][0] == 'P' && env[i][1] == 'A' && env[i][2] == 'T'
			&& env[i][3] == 'H' && env[i][4] == '=' && env[i][5] == '/')
			break ;
	if (env[i] == 0)
		return (perror("Path not found in env\n"), exit(1), 1);
	ret = ft_split(env[i] + 5, ':');
	if (ret == 0)
		return (perror("Malloc\n"), ft_free(0, cmd_save), exit(1), 1);
	i = -1;
	while (ret[++i])
	{
		temp = ft_strjoin(ret[i], "/");
		if (temp == 0)
			return (perror("Malloc\n"), ft_free(0, cmd_save), exit(1), 1);
		free(ret[i]);
		ret[i] = temp;
	}
	cmd_save[0].path_save = ret;
	return (cmd_save[0].env = env, 0);
}

void	ft_free(char **split, t_cmd_save *cmd_save)
{
	int			i;
	t_pid_wait	*pid_wait;

	if (split != 0)
	{
		i = -1;
		while (split[++i])
			free(split[i]);
		free(split);
	}
	if (cmd_save != 0)
	{
		ft_free(cmd_save[0].path_save, NULL);
		i = 0;
		while (++i <= cmd_save[0].nbr)
			ft_free(cmd_save[i].cmd, NULL);
		free(cmd_save);
	}
	pid_wait = ft_pid_create(-3);
}

static void	ft_calloc_cmd_save(t_cmd_save *ret, int ac, const char **av)
{
	int	i;

	ret[0].nbr = 0;
	ret[0].path_save = 0;
	ret[0].av_1 = av[1];
	ret[0].ac = ac;
	ret[0].av_last = av[ac - 1];
	i = -1;
	while (++i <= ac - 3)
		ret[i].cmd = 0;
}

t_cmd_save	*ft_cmd_save_create(int ac, const char **av)
{
	t_cmd_save	*ret;
	int			i;

	if (ac < 5)
		return (printf("Need more args\n"), exit(1), NULL);
	ret = (t_cmd_save *)malloc((ac - 3 + 1) * sizeof(t_cmd_save));
	if (ret == 0)
		return (NULL);
	ft_calloc_cmd_save(ret, ac, av);
	i = 0;
	while (++i <= ac - 3)
	{
		ret[i].cmd = ft_split(av[i + 1], ' ');
		if (ret[i].cmd == 0 || ret[i].cmd[0] == 0)
		{
			if (ret[i].cmd)
				free(ret[i].cmd);
			return (perror("Malloc or empty command"),
				ft_free(0, ret), exit(1), NULL);
		}
		ret[0].nbr++;
		ret[i].nbr = ret[0].nbr;
	}
	return (ret);
}

t_pid_wait	*ft_pid_create(pid_t pid_to_add)
{
	static t_pid_wait	*pid_wait = NULL;
	t_pid_wait			*temp;
	int					i;

	if (pid_to_add == -2)
		return (pid_wait);
	if (pid_to_add == -3)
		return (free(pid_wait), pid_wait = 0, NULL);
	if (pid_wait == NULL)
	{
		pid_wait = (t_pid_wait *)malloc(1 * sizeof(t_pid_wait));
		if (pid_wait == 0)
			return (NULL);
		pid_wait[0].nbr = 0;
	}
	temp = (t_pid_wait *)malloc((pid_wait[0].nbr + 2) * sizeof(t_pid_wait));
	if (temp == 0)
		return (free(pid_wait), pid_wait = NULL, NULL);
	i = 0;
	while (++i <= pid_wait[0].nbr)
		temp[i].pid = pid_wait[i].pid;
	temp[0].nbr = pid_wait[0].nbr + 1;
	temp[i].pid = pid_to_add;
	return (free(pid_wait), pid_wait = temp, pid_wait);
}
