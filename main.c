/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haranivo <haranivo@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 10:21:21 by haranivo          #+#    #+#             */
/*   Updated: 2026/03/20 01:44:01 by haranivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int fd;
	char *line;

	fd = open("text.save", O_RDONLY, 0644);
	if (fd < 0)
		return (10);

	/*first line*/
	line = get_next_line(fd);
	printf("1-----> %s\n", line);
	free(line);

	/*second line*/
	line = get_next_line(fd);
	printf("2-----> %s\n", line);
	free(line);

	/*third line*/
	line = get_next_line(fd);
	printf("3-----> %s\n", line);
	free(line);

	/*forth line*/
	line = get_next_line(fd);
	printf("4-----> %s\n", line);
	free(line);

	/*fifth line*/
	line = get_next_line(fd);
	printf("5-----> %s\n", line);
	free(line);

	/*sixth line*/
	line = get_next_line(fd);
	printf("6-----> %s\n", line);
	free(line);

	close(fd);
	return (0);
}