/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:14:39 by yxu               #+#    #+#             */
/*   Updated: 2023/10/09 01:03:40 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_lines(int fd)
{
	void		*buf;
	ssize_t		flag;
	char		*lines;

	lines = NULL;
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	((char *)buf)[BUFFER_SIZE] = 0;
	while (1)
	{
		flag = read(fd, buf, BUFFER_SIZE);
		if (flag == 0)
			break ;
		lines = ft_strjoin(lines, buf);
		if (lines == NULL || flag == -1)
		{
			free(buf);
			free(lines);
			return (NULL);
		}
	}
	free(buf);
	return (lines);
}

char	*get_next_line(int fd)
{
	static char	*lines = NULL;
	int			i;
	char		*line;
	static int	index = 0;

	if (lines == NULL)
		lines = get_lines(fd);
	if (lines == NULL)
		return (NULL);
	i = index;
	if (lines[i] == '\0')
	{
		free(lines);
		return (NULL);
	}
	while (lines[i])
	{
		if (lines[i] == '\n')
		{
			line = ft_substr(lines, index, i - index + 1);
			index = i + 1;
			free(lines);
			return (line);
		}
		i++;
	}
	line = ft_substr(lines, index, i - index);
	index = i;
	free(lines);
	return (line);
}



// #include <fcntl.h>
// int	main()
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("test.txt", O_RDONLY);
// 	// fd = 1;
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		printf("line: %s", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// }
