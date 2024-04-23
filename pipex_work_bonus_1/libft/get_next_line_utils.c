/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 02:18:38 by qdo               #+#    #+#             */
/*   Updated: 2024/04/23 20:36:52 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_gnl(char *dst, char *src)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	if (dst != 0)
		while (dst[i])
			i++;
	while (src[j])
		j++;
	ret = (char *)malloc(j + i + 1);
	if (ret == 0)
		return (0);
	i = -1;
	j = -1;
	if (dst != 0)
		while (dst[++i])
			ret[i] = dst[i];
	if (i == -1)
		i = 0;
	while (src[++j])
		ret[i++] = src[j];
	ret[i] = 0;
	return (ret);
}

char	*ft_strchr(char *str, char to_find)
{
	int	i;

	i = 0;
	if (str == 0)
		return (NULL);
	while (str[i])
		if (str[i++] == to_find)
			return (str);
	return (NULL);
}

char	*ft_free_gnl(char *a, char *b, char **c)
{
	if (a != 0)
		free(a);
	if (b != 0)
		free(b);
	if (c != 0 && *c != 0)
	{
		free(*c);
		*c = 0;
	}
	return (0);
}

char	*ft_before_after_nl(char *lstr, int ba)
{
	int		i;
	char	*ret;

	if (lstr == 0)
		return (0);
	i = 0;
	while (lstr[i])
		if (lstr[i++] == '\n')
			break ;
	if (ba == -1)
	{
		lstr[i] = 0;
		ret = ft_strjoin_gnl(0, lstr);
		if (ret == 0)
			return (0);
		if (*ret == 0)
		{
			free(ret);
			return (0);
		}
		return (ret);
	}
	else
		ret = ft_strjoin_gnl(0, lstr + i);
	return (ret);
}
