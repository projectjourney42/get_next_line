/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haranivo <haranivo@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:07:54 by haranivo          #+#    #+#             */
/*   Updated: 2026/03/10 10:29:13 by haranivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*add_to_stock(char *stock, int fd)
{
	char	*new_stock;
	char	buf[BUFFER_SIZE + 1];
	ssize_t	read_value;

	if (!stock)
		return (NULL);
	read_value = read(fd, buf, BUFFER_SIZE);
	if (read_value > 0)
	{
		buf[read_value] = '\0';
		new_stock = ft_strjoin(stock, buf);
		free(stock);
		stock = new_stock;
	}
	if (read_value < 0)
		return (NULL);
	if (read_value == 0)
		return (stock);
	return (stock);
}

static char	*find_nl_transfer(char *stock)
{
	char	*next;
	char	*new_stock;
	char	*to_print;

	if (!stock)
		return (NULL);
	next = ft_strchr(stock, '\n');
	if (next)
	{
		to_print = ft_substr(stock, 0, (next - stock) + 1);
		if (*(next + 1) == '\0')
			return (stock);
		new_stock = ft_strdup(next);
	}
	to_print = ft_strdup(stock);
	new_stock = NULL;
	free(stock);
	stock = new_stock;
	return (to_print);
}

char	*get_next_line(int fd)
{
	static char	**stock;
	char		buf[BUFFER_SIZE + 1];
	char		*to_print;
	ssize_t		read_value;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		read_value = read(fd, buf, BUFFER_SIZE);
		if (read_value < 0)
			return (NULL);
		if (read_value == 0)
			return (*stock);
		if (read_value > 0)
		{
			*stock = add_to_stock(*stock, fd);
			to_print = find_nl_transfer(*stock);
		}
		if (!stock)
			return (NULL);
	}
	return (to_print);
}
