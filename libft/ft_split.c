/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:55:27 by jrouillo          #+#    #+#             */
/*   Updated: 2023/04/26 17:11:10 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_strs(char **strs)
{
	size_t	i;

	if (strs)
	{
		i = -1;
		while (strs[++i])
			free((void *)strs[i]);
		free(strs);
	}
}

int	word_count(char const *s, char c)
{
	size_t	i;
	size_t	counter;

	i = 0;
	counter = 0;
	if (!s || !s[0])
		return (0);
	if (s[0] == c)
		i++;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			counter++;
		i++;
	}
	return (counter);
}

int	word_len(const char *s, char c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i + len] && s[i + len] != c)
		len++;
	return (len);
}

char	*word_generator(const char **s, char c)
{
	size_t		len;
	char		*word;

	while (**s == c)
		(*s)++;
	len = word_len(*s, c);
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (word)
		ft_strlcpy(word, *s, len + 1);
	*s += len;
	return (word);
}

char	**ft_split(char const *s, char c)
{
	size_t		i;
	size_t		counter;
	char		**res;

	i = -1;
	if (!s)
		return (NULL);
	counter = word_count(s, c);
	res = (char **)malloc(sizeof(char *) * (counter + 1));
	if (res)
	{
		res[counter] = NULL;
		while (++i < counter)
		{
			res[i] = word_generator(&s, c);
			if (!res[i])
			{
				free_strs(res);
				res = NULL;
				break ;
			}
		}
	}
	return (res);
}
