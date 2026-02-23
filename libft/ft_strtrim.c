/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchemali <gchemali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:26:58 by gchemali          #+#    #+#             */
/*   Updated: 2025/06/14 21:13:43 by gchemali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_start(char const *s1, char const *set)
{
	size_t	start;

	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	return (start);
}

static size_t	get_end(char const *s1, char const *set, size_t start)
{
	size_t	end;

	end = ft_strlen(s1);
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	len;
	char	*trimmed;
	size_t	i;

	if (!s1 || !set)
		return (NULL);
	start = get_start(s1, set);
	end = get_end(s1, set, start);
	if (end <= start)
		return (ft_strdup(""));
	len = end - start;
	trimmed = malloc(len + 1);
	if (!trimmed)
		return (NULL);
	i = 0;
	while (i < len)
		trimmed[i++] = s1[start++];
	trimmed[i] = '\0';
	return (trimmed);
}

// #include <stdio.h>
// #include <stdlib.h>
// int main(void)
// {
// 	const char *tests[][2] = {
// 		{"   hello world   ", " "},
// 		{"***example***", "*"},
// 		{"--trim--", "-"},
// 		{"!!wow!!", "!"},
// 		{"nothing to trim", ""},
// 		{"", " "},
// 		{"   ", " "}
// 	};

// 	size_t count = sizeof(tests) / sizeof(tests[0]);

// 	for (size_t i = 0; i < count; i++)
// 	{
// 		const char *s1 = tests[i][0];
// 		const char *set = tests[i][1];
// 		char *trimmed = ft_strtrim(s1, set);
// 		if (!trimmed)
// 		{
// 			printf("ft_strtrim failed for: \"%s\" with set \"%s\"\n", s1, set);
// 			continue;
// 		}
// 		printf("Original: \"%s\" | Set: \"%s\" | Trimmed: \"%s\"\n"
// , s1, set, trimmed);
// 		free(trimmed);
// 	}
// 	return 0;
// }
