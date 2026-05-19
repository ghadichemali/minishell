/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchemali <gchemali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:27:01 by gchemali          #+#    #+#             */
/*   Updated: 2025/06/14 21:06:15 by gchemali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_sub;
	size_t	s_len;
	size_t	copy_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	copy_len = 0;
	if (start >= s_len)
		return (ft_strdup(""));
	copy_len = s_len - start;
	if (copy_len > len)
		copy_len = len;
	new_sub = malloc(sizeof(char) * (copy_len + 1));
	if (!new_sub)
		return (NULL);
	ft_strlcpy(new_sub, s + start, copy_len + 1);
	return (new_sub);
}

// #include <stdio.h>
// #include <stdlib.h>
// int main(void)
// {
// 	struct {
// 		const char *input;
// 		unsigned int start;
// 		size_t len;
// 	} tests[] = {
// 		{"Hello, world!", 0, 5},
// 		{"Hello, world!", 7, 5},
// 		{"Hello, world!", 13, 5}, // start beyond end
// 		{"Short", 2, 10},
// 		{"Substring test", 5, 0},
// 		{"", 0, 5}
// 	};
// 	size_t count = sizeof(tests) / sizeof(tests[0]);
// 	for (size_t i = 0; i < count; i++)
// 	{
// 		char *sub = ft_substr(tests[i].input, tests[i].start, tests[i].len);
// 		if (!sub)
// 		{
// 			printf("ft_substr failed for: \"%s\", start = %u, len = %zu\n",
// 			       tests[i].input, tests[i].start, tests[i].len);
// 			continue;
// 		}
// 		printf("Input: \"%s\" | start: %u | len: %zu | Substring: \"%s\"\n",
// 		       tests[i].input, tests[i].start, tests[i].len, sub);
// 		free(sub);
// 	}
// 	return 0;
// }