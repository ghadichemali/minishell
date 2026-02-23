/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchemali <gchemali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:26:45 by gchemali          #+#    #+#             */
/*   Updated: 2025/06/14 20:57:31 by gchemali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	copy_str(char *dest, const char *src, size_t *i)
{
	size_t	j;

	j = 0;
	while (src[j])
	{
		dest[*i] = src[j];
		(*i)++;
		j++;
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	size_t	len1;
	size_t	len2;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	joined = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!joined)
		return (NULL);
	i = 0;
	copy_str(joined, s1, &i);
	copy_str(joined, s2, &i);
	joined[i] = '\0';
	return (joined);
}

// #include <stdio.h>
// #include <stdlib.h>
// int main(void)
// {
// 	const char *tests[][2] = {
// 		{"Hello", "World"},
// 		{"", "Non-empty"},
// 		{"Non-empty", ""},
// 		{"", ""},
// 		{"123", "456"},
// 		{"Join ", "me!"}
// 	};

// 	size_t num_tests = sizeof(tests) / sizeof(tests[0]);

// 	for (size_t i = 0; i < num_tests; i++)
// 	{
// 		const char *s1 = tests[i][0];
// 		const char *s2 = tests[i][1];
// 		char *joined = ft_strjoin(s1, s2);
// 		if (joined == NULL)
// 		{
// 			printf("ft_strjoin failed for: \"%s\" + \"%s\"\n", s1, s2);
// 			continue;
// 		}
// 		printf("ft_strjoin(\"%s\", \"%s\") = \"%s\"\n", s1, s2, joined);
// 		free(joined);
// 	}
// 	return 0;
// }
