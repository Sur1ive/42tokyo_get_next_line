/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:14:39 by yxu               #+#    #+#             */
/*   Updated: 2023/10/27 20:02:42 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_lines	*get_line(char *str)
{
	t_lines	*lines;
	size_t	i;

	i = 0;
	lines = (t_lines *)malloc(sizeof(t_lines *));
	while (str && str[i])
	{
		if (str[i] == '\n')
		{
			lines->line = ft_substr(str, 0, i + 1);
			lines->remain = ft_substr(str, i + 1, ft_strlen(str) - i - 1);
			if (lines->line == NULL || lines->remain == NULL)
				return (ft_free3(lines->line, lines->remain, lines));
			if (*lines->remain == '\0')
				lines->remain = ft_free3(lines->remain, NULL, NULL);
			return (lines);
		}
		i++;
	}
	lines->line = NULL;
	lines->remain = str;
	if (str && *str == 0)
		lines->remain = NULL;
	return (lines);
}

char	*deal_line(char *buf, char **remain, char **line)
{
	t_lines	*lines;

	lines = get_line(buf);
	if (lines == NULL)
		return (NULL);
	if (lines->line)
	{
		*remain = lines->remain;
		*line = ft_strjoin_free(*line, lines->line);
		free(buf);
		free(lines);
		return (*line);
	}
	*line = ft_strjoin_free(*line, lines->remain);
	free(lines);
	// if (*line == NULL)
	// 	return (NULL);
	return ("");
}

char	*get_next_line_init(int fd, char *buf, char *line)
{
	static char	*remain = NULL;
	ssize_t		read_byte;
	char		*result;

	buf = remain;
	while (1)
	{
		result = deal_line(buf, &remain, &line);
		if (result == NULL)
			return (NULL);
		if (*result)
			return (result);
		buf = (char *)malloc(BUFFER_SIZE + 1);
		read_byte = read(fd, buf, BUFFER_SIZE);
		if (read_byte == -1)
			return (remain = ft_free3(buf, line, NULL));
		if (read_byte == 0)
		{
			remain = ft_free3(buf, NULL, NULL);
			return (line);
		}
		buf[read_byte] = '\0';
	}
}

char	*get_next_line(int fd)
{
	if ((long long)BUFFER_SIZE <= 0 || BUFFER_SIZE >= (long long)INT_MAX)
		return (NULL);
	return (get_next_line_init(fd, NULL, NULL));
}

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
