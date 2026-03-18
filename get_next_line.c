/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haranivo <haranivo@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:07:54 by haranivo          #+#    #+#             */
/*   Updated: 2026/03/18 16:09:30 by haranivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_stock(char **stock)
{
	free(stock);
	*stock = ft_strdup("");
	return (NULL);
}

// char	no_more_read(char *stock, ssize_t read_value)
// {

// }

static char	*add_to_stock(char *stock, int fd)
{
	char	*new_stock;
	char	buf[BUFFER_SIZE + 1];
	ssize_t	read_value;

	read_value = read(fd, buf, BUFFER_SIZE);
	while (read_value != 0)
	{
		if (read_value == -1)
			return (NULL);
		buf[read_value] = '\0';
		new_stock = ft_strjoin(stock, buf);
		free(stock);
		stock = new_stock;
		return (stock);
	}
	if (read_value == 0)
		return (stock);
	return (stock);
}

static char	*find_nl_transfer(char **stock, int fd)
{
	char	*next;
	char	*new_stock;
	char	*to_print;
	char	buf[BUFFER_SIZE + 1];
	ssize_t	read_value;

	next = ft_strchr(*stock, '\n');
	if (next)
	{
		to_print = ft_substr(*stock, 0, (next - *stock) + 1);
		new_stock = ft_strdup(next + 1);
		free(*stock);
		*stock = new_stock;
	}
	else
	{
		read_value = read(fd, buf, BUFFER_SIZE);
		if (read_value > 0)
		{
			buf[read_value] = '\0';
			new_stock = ft_strjoin(*stock, buf);
			return (find_nl_transfer(&new_stock, fd));
		}
		return (*stock);
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
	stock = add_to_stock(stock, fd);
	to_print = find_nl_transfer(&stock, fd);
	if (!stock)
	{
		free(stock);
		stock = ft_strdup("");
		return (NULL);
	}
	return (to_print);
}
