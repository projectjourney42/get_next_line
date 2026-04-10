/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haranivo <haranivo@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 17:16:22 by haranivo          #+#    #+#             */
/*   Updated: 2026/04/10 18:39:22 by haranivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	free_stock(char **stock)
{
	free(*stock);
	*stock = NULL;
}

char	*add_to_stock(char **stock, int fd)
{
	char	*buf;
	char	*new_stock;
	ssize_t	read_value;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (free_stock(stock), NULL);
	read_value = 1;
	while (*stock && !ft_strchr(*stock, '\n') && read_value > 0)
	{
		read_value = read(fd, buf, BUFFER_SIZE);
		if (read_value <= 0)
			break ;
		buf[read_value] = '\0';
		new_stock = ft_strjoin(*stock, buf);
		if (!new_stock)
			return (free_stock(stock), free(buf), NULL);
		free_stock(stock);
		*stock = new_stock;
	}
	free(buf);
	if (read_value < 0 || (read_value == 0 && (!*stock || !**stock)))
		return (free_stock(stock), NULL);
	return (*stock);
}

char	*find_nl_transfer(char **stock)
{
	char	*next;
	char	*new_stock;
	char	*to_print;

	if (!*stock || !**stock)
		return (NULL);
	next = ft_strchr(*stock, '\n');
	if (!ft_strchr(*stock, '\n'))
	{
		new_stock = ft_strdup(*stock);
		free_stock(stock);
		return (new_stock);
	}
	to_print = ft_substr(*stock, 0, (next - *stock) + 1);
	if (*(next + 1) == '\0')
		return (free_stock(stock), to_print);
	new_stock = ft_strdup(next + 1);
	free_stock(stock);
	*stock = new_stock;
	return (to_print);
}

char	*get_next_line(int fd)
{
	static char	*stock[1024];
	char		*to_print;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stock[fd])
		stock[fd] = ft_strdup("");
	stock[fd] = add_to_stock(&stock[fd], fd);
	if (!stock[fd])
		return (NULL);
	to_print = find_nl_transfer(&stock[fd]);
	if (!to_print)
	{
		free_stock(&stock[fd]);
		free(to_print);
		return (NULL);
	}
	return (to_print);
}
