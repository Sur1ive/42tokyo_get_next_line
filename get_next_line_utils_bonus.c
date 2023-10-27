/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:14:39 by yxu               #+#    #+#             */
/*   Updated: 2023/10/27 20:29:28 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	if (str == NULL)
		return (0);
	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*str;
	char	*start;
	size_t	i;

	str = (char *)malloc(ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1);
	if (str == NULL)
	{
		ft_free3(s1, s2, str);
		return (NULL);
	}
	start = str;
	i = 0;
	while (s1 && s1[i] != '\0')
		*str++ = s1[i++];
	i = 0;
	while (s2 && s2[i] != '\0')
		*str++ = s2[i++];
	*str = '\0';
	free(s1);
	free(s2);
	return (start);
}

void	*ft_free3(void *s1, void *s2, void *s3)
{
	free(s1);
	free(s2);
	free(s3);
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	slen;
	char	*substr;

	if (s == NULL)
		return (NULL);
	slen = ft_strlen((char *)s);
	if (start >= slen)
		len = 0;
	else if (len > slen - start)
		len = slen - start;
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (substr == NULL)
		return (NULL);
	substr[len] = '\0';
	while (len-- > 0)
		substr[len] = s[start + len];
	return (substr);
}
