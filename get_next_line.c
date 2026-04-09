/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haranivo <haranivo@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:07:54 by haranivo          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/04/09 16:55:47 by haranivo         ###   ########.fr       */
=======
/*   Updated: 2026/04/09 16:03:22 by haranivo         ###   ########.fr       */
>>>>>>> 37457c9 (deleted all static in fuction and added all fucnction to the .h)
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*stock;
	char		*to_print;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stock)
		stock = ft_strdup("");
	stock = add_to_stock(&stock, fd);
	if (!stock)
		return (NULL);
	to_print = find_nl_transfer(&stock);
	if (!to_print)
	{
		free_stock(&stock);
		free(to_print);
		return (NULL);
	}
	return (to_print);
}
