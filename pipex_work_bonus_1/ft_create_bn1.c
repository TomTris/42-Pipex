/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_bn1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 21:46:03 by qdo               #+#    #+#             */
/*   Updated: 2024/04/23 17:22:25 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_zero_save(int ac, const char **av, char **env, t_save_bn *save_bn)
{
	save_bn->ac = ac;
	save_bn->av = av;
	save_bn->env = env;
	save_bn->cmd = 0;
	save_bn->path_save = 0;
}

void	ft_free_bn(char **split, t_save_bn *save_bn)
{
	int	i;

	if (split)
	{
		i = -1;
		while (split[++i])
			free(split[i]);
		free(split);
	}
	if (save_bn)
	{
		i = -1;
		if (save_bn->cmd)
		{
			while (save_bn->cmd[++i])
				ft_free_bn(save_bn->cmd[i], 0);
			free(save_bn->cmd);
		}
		i = -1;
		if (save_bn->path_save)
			ft_free_bn(save_bn->path_save, 0);
	}
	ft_wait_pid_bn(0, -3);
}

int	ft_strcmp_pipex(char *str1, char *str2)
{
	int	i;

	if (str1 == 0 || str2 == 0)
		return (0);
	i = 0;
	while (str1[i])
	{
		if (str1[i] == str2[i])
			i++;
		else
			return (0);
	}
	if (str2[i] == 0)
		return (1);
	return (0);
}

int	ft_usage(void)
{
	ft_printf("< | > command, at least 5 arguments neededn\n");
	ft_printf("<< | >> command, 6 arguments needed\n");
	return (1);
}
