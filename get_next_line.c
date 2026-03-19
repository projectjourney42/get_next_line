/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haranivo <haranivo@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:07:54 by haranivo          #+#    #+#             */
/*   Updated: 2026/03/20 01:45:24 by haranivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] == s2[i])
			i++;
		else
			return (0);
	}
	return (1);
}

void	free_stock(char **stock)
{
	free(*stock);
	*stock = NULL;
}

static char	*add_to_stock(char **stock, int fd)
{
	char	*new_stock;
	char	buf[BUFFER_SIZE + 1];
	ssize_t	read_value;

	read_value = read(fd, buf, BUFFER_SIZE);
	if (read_value != 0)
	{
		if (read_value == -1)
			return (NULL);
		buf[read_value] = '\0';
		new_stock = ft_strjoin(*stock, buf);
		free_stock(stock);
		*stock = new_stock;
		return (*stock);
	}
	if (read_value == 0)
	{
		new_stock = ft_strdup(*stock);
		free_stock(stock);
		return (new_stock);
	}
	return (NULL);
}

static char	*find_nl_transfer(char **stock, int fd)
{
	char	*next;
	char	*new_stock;
	char	*old_stock;
	char	*to_print;

	if (!*stock || !**stock)
		return (NULL);
	next = ft_strchr(*stock, '\n');
	while (!ft_strchr(*stock, '\n'))
	{
		old_stock = ft_strdup(*stock);
		new_stock = add_to_stock(stock, fd);
		free_stock(stock);
		*stock = new_stock;
		if (ft_strcmp(new_stock, old_stock))
			return (new_stock);
	}
	if (next)
	{
		to_print = ft_substr(*stock, 0, (next - *stock) + 1);
		new_stock = ft_strdup(next + 1);
		free_stock(stock);
		*stock = new_stock;
	}
	return (to_print);
}

char	*get_next_line(int fd)
{
	static char	*stock;
	char		buf[BUFFER_SIZE + 1];
	char		*to_print;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stock)
		stock = ft_strdup("");
	stock = add_to_stock(&stock, fd);
	to_print = find_nl_transfer(&stock, fd);
	if (!stock)
	{
		free_stock(&stock);
		stock = ft_strdup("");
		return (NULL);
	}
	return (to_print);
}
