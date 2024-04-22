/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:52:00 by qdo               #+#    #+#             */
/*   Updated: 2024/03/14 12:59:32 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <ctype.h>
# include "get_next_line.h"

int		ft_printf(const char *str_o, ...);
int		ft_putp(unsigned long n);
int		ft_putc(char c);
int		ft_putdi(int n);
int		ft_puts(char *s);
int		ft_putu(unsigned int n);
int		ft_putx(unsigned int n);
int		ft_putxx(unsigned int n);
size_t	ft_strlen(char *str);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(char *str);
char	*ft_strcpy(char *s1, char *s2);
#endif
