/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchemali <gchemali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:26:52 by gchemali          #+#    #+#             */
/*   Updated: 2025/06/12 18:25:26 by gchemali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	length;
	char			*result;

	if (!s)
		return (NULL);
	length = ft_strlen(s);
	result = malloc(length * sizeof(char) + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (i < length)
	{
		result[i] = (*f)(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}

// #include <stdio.h>
// #include <stdlib.h>

// char example_map(unsigned int i, char c)
// {
// 	// Capitalize characters at even indexes, lowercase at odd
// 	if (i % 2 == 0 && c >= 'a' && c <= 'z')
// 		return c - 32;
// 	else if (i % 2 != 0 && c >= 'A' && c <= 'Z')
// 		return c + 32;
// 	return c;
// }

// int main(void)
// {
// 	const char *test_strings[] = {
// 		"abcdef",
// 		"HelloWorld",
// 		"42Network",
// 		"",
// 		"MiXeD CaSe"
// 	};
// 	size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);

// 	for (size_t i = 0; i < num_tests; i++)
// 	{
// 		char *mapped = ft_strmapi(test_strings[i], example_map);
// 		if (!mapped)
// 		{
// 			printf("ft_strmapi failed for input: \"%s\"\n", test_strings[i]);
// 			continue;
// 		}
// 		printf("Original: \"%s\" | Mapped: \"%s\"\n", test_strings[i], mapped);
// 		free(mapped);
// 	}
// 	return 0;
// }