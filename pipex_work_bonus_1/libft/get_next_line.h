/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 02:18:37 by qdo               #+#    #+#             */
/*   Updated: 2024/04/21 12:36:18 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

char	*get_next_line(int fd);
char	*ft_strjoin_gnl(char *dst, char *src);
char	*ft_strchr(char *str, char to_find);
char	*ft_free_gnl(char *a, char *b, char **c);
char	*ft_before_after_nl(char *lstr, int ba);
char	*ft_read(int fd, char *lstr);
int		ft_read2(int fd, char **buf, char **lstr, int *read_bytes);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

#endif