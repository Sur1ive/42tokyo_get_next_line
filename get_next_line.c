/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:14:39 by yxu               #+#    #+#             */
/*   Updated: 2023/10/23 00:43:22 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*remain = "";
	char		*buf;
	char		*line;
	ssize_t		read_byte;
	size_t		i;
	size_t		lenremain = ft_strlen(remain);

	if ((long long)BUFFER_SIZE <= 0 || BUFFER_SIZE >= (long long)INT_MAX)
		return (NULL);
	i = 0;
	line = NULL;
	if (remain != NULL && *remain != '\0')
	{
		while (i < lenremain && remain[i] != '\n')
			i++;
		if (i != lenremain)
		{
			buf = ft_substr(remain, 0, i + 1);
			if (buf == NULL)
			{
				ft_free2(buf, remain);
				remain = NULL;
				return (NULL);
			}
			line = ft_strjoin_free(line, buf);
			buf = ft_substr(remain, i + 1, lenremain - i - 1);
			if (buf == NULL)
			{
				ft_free2(buf, remain);
				remain = NULL;
				return (NULL);
			}
			free(remain);
			remain = buf;
			return (line);
		}
		line = ft_strjoin_free(remain, NULL);
		remain = NULL;
	}
	read_byte = 1;
	while (1)
	{
		buf = (char *)malloc(BUFFER_SIZE + 1);
		if (buf == NULL)
		{
			ft_free2(remain, buf);
			remain = NULL;
			return (NULL);
		}
		buf[BUFFER_SIZE] = '\0';
		read_byte = read(fd, buf, BUFFER_SIZE);
		if (read_byte == -1)
		{
			ft_free2(buf, remain);
			remain = NULL;
			return (NULL);
		}
		if (read_byte == 0)
		{
			ft_free2(buf, remain);
			remain = NULL;
			return (line);
		}
		i = 0;
		while ((ssize_t)i < read_byte && buf[i] != '\n')
			i++;
		if ((ssize_t)i != read_byte)
		{
			remain = ft_substr(buf, 0, i + 1);
			if (remain == NULL)
			{
				ft_free2(buf, remain);
				remain = NULL;
				return (NULL);
			}
			line = ft_strjoin_free(line, remain);
			remain = ft_substr(buf, i + 1, read_byte - i - 1);
			if (remain == NULL)
			{
				ft_free2(buf, remain);
				remain = NULL;
				return (NULL);
			}
			free(buf);
			buf = NULL;
			return (line);
		}
		line = ft_strjoin_free(line, buf);
	}

	return (line);
}

// #include <stdio.h>
// #include <fcntl.h>
// int	main()
// {
// 	int		fd;
// 	char	*line;
// 	int		i;

// 	fd = open("test.txt", O_RDONLY);
// 	// fd = 1;
// 	line = get_next_line(fd);
// 	i = 0;
// 	while (line != NULL)
// 	{
// 		printf("line%d: %s", i, line);
// 		free(line);
// 		line = get_next_line(fd);
// 		i++;
// 	}
// 	close(fd);
// }
