/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 01:25:37 by qdo               #+#    #+#             */
/*   Updated: 2024/04/22 19:34:51 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
int	ft_check_input(int ac, const char **av)
{
	int	i;
	int	j;

	i = open(av[1], O_RDONLY, 0644);
	if (i == -1)
		perror(av[1]);
	j = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (j == -1)
		perror(av[ac - 1]);
	if (i == -1 || i == -1)
		exit(127);
	return (0);
}

int	main2(int ac, const char **av, char **env)
{
	int	i;

	i = 0;
	if (env)
		i++;
	ft_check_input(ac, av);
	return (0);
}

int	main(void)
{
	printf("%d\n", close(-1));
	return (1);
}