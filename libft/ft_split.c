/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchemali <gchemali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:26:37 by gchemali          #+#    #+#             */
/*   Updated: 2025/09/02 20:16:42 by gchemali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	is_sep(char c, char sep)
{
	return (c == sep);
}

static int	word_count(const char *s, char sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && is_sep(s[i], sep))
			i++;
		if (s[i])
			count++;
		while (s[i] && !is_sep(s[i], sep))
			i++;
	}
	return (count);
}

static char	*word_dup(const char *s, char sep)
{
	int		len;
	char	*word;
	int		i;

	len = 0;
	while (s[len] && !is_sep(s[len], sep))
		len++;
	word = malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		i;

	i = 0;
	result = malloc((word_count(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (*s)
	{
		while (*s && is_sep(*s, c))
			s++;
		if (*s)
		{
			result[i++] = word_dup(s, c);
			while (*s && !is_sep(*s, c))
				s++;
		}
	}
	result[i] = NULL;
	return (result);
}
