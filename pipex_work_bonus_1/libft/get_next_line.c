/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 02:18:35 by qdo               #+#    #+#             */
/*   Updated: 2024/04/21 01:36:38 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_read2(int fd, char **buf, char **lstr, int *read_bytes)
{
	char	*temp;

	temp = 0;
	*read_bytes = read(fd, *buf, BUFFER_SIZE);
	if (*read_bytes < 0)
	{
		if (temp == 0)
			return (free(*lstr), ft_free_gnl(*buf, 0, 0), 0);
		return (free(*lstr), ft_free_gnl(*buf, 0, 0), 0);
	}
	(*buf)[*read_bytes] = 0;
	temp = *lstr;
	*lstr = ft_strjoin_gnl(*lstr, *buf);
	if (*lstr == 0)
		return (ft_free_gnl(*buf, temp, 0), 0);
	free(temp);
	return (1);
}

char	*ft_read(int fd, char *lstr)
{
	char	*buf;
	int		read_bytes;

	buf = (char *)malloc((BUFFER_SIZE + 1));
	if (buf == 0)
		return (free(lstr), NULL);
	read_bytes = 0;
	while (read_bytes <= BUFFER_SIZE)
		buf[read_bytes++] = 0;
	read_bytes = BUFFER_SIZE;
	while (ft_strchr(lstr, '\n') == 0 && read_bytes > 0)
		if (ft_read2(fd, &buf, &lstr, &read_bytes) != 1)
			return (NULL);
	free(buf);
	return (lstr);
}

char	*get_next_line(int fd)
{
	static char	*lstr = 0;
	char		*ret;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	lstr = ft_read(fd, lstr);
	if (lstr == 0)
		return (0);
	temp = lstr;
	lstr = ft_before_after_nl(lstr, 1);
	if (lstr == 0)
		return (ft_free_gnl(temp, 0, 0));
	ret = ft_before_after_nl(temp, -1);
	if (ret == 0)
		return (ft_free_gnl(temp, 0, &lstr));
	ft_free_gnl(temp, 0, 0);
	return (ret);
}
