/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:14:39 by yxu               #+#    #+#             */
/*   Updated: 2023/10/10 22:50:44 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*get_next_line_intialized(int fd, char *line, char *buf)
{
	ssize_t		flag;
	long long	i;

	i = BUFFER_SIZE;
	flag = 1;
	while (flag != 0 && !(buf && buf[i - 1] == '\n'))
	{
		if (i == BUFFER_SIZE)
		{
			line = ft_strjoin_free(line, buf);
			buf = (char *)malloc(BUFFER_SIZE + 1);
			if (line == NULL || buf == NULL)
				return (ft_free2(line, buf));
			buf[0] = 0;
			i = 0;
		}
		flag = read(fd, buf + i++, 1);
		if (flag == -1)
			return (ft_free2(line, buf));
		buf[i] = 0;
	}
	line = ft_strjoin_free(line, buf);
	if (ft_strlen(line) == 0 && flag == 0)
		return (ft_free2(line, NULL));
	return (line);
}

char	*get_next_line(int fd)
{
	static char	for_norm = 0;

	(void)for_norm;
	if ((long long)BUFFER_SIZE <= 0 || BUFFER_SIZE >= (long long)INT_MAX)
		return (NULL);
	return (get_next_line_intialized(fd, NULL, NULL));
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
// }
