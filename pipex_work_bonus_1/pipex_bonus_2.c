/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:50:13 by qdo               #+#    #+#             */
/*   Updated: 2024/04/23 18:00:01 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main_here_doc(int ac, const char **av, char **env)
{
	t_save_bn	save_bn[1];
	int			fd_midle;
	pid_t		*pid_save;

	ft_zero_save(ac, av, env, save_bn);
	fd_midle = ft_input_read_n_create_bn(av);
	ft_cmd_save_create_bn(av, save_bn, fd_midle);
	ft_create_path_save_bn(env, save_bn, fd_midle, -1);
	fd_midle = ft_execute_1(save_bn, fd_midle);
	ft_execute_2(save_bn, fd_midle);
	pid_save = ft_wait_pid_bn(0, -2);
	waitpid(pid_save[0], 0, 0);
	waitpid(pid_save[1], 0, 0);
	ft_free_bn(0, save_bn);
	return (0);
}

int	main(int ac, const char **av, char **env)
{
	if (ac < 5)
		return (ft_usage(), exit(1), -99);
	if (ac == 6 && ft_strcmp_pipex((char *)av[1], "here_doc") == 1)
	{
		return (main_here_doc(ac, av, env));
	}
	else
		return (main_manda(ac, av, env));
}
