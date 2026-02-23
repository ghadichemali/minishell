/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchemali <gchemali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:33:48 by gchemali          #+#    #+#             */
/*   Updated: 2025/06/12 20:50:42 by gchemali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	size_t	size;
	char	*dest;

	size = ft_strlen(src);
	dest = malloc(size * sizeof(char) + 1);
	if (dest == NULL)
		return (0);
	ft_memcpy(dest, src, size);
	dest[size] = '\0';
	return (dest);
}

// #include <stdio.h>
// #include <stdlib.h>

// int main(void)
// {
// 	const char *originals[] = {
// 		"Hello, world!",
// 		"",
// 		"This is a longer test string.",
// 		"1234567890",
// 		"Duplicate me!"
// 	};

// 	size_t count = sizeof(originals) / sizeof(originals[0]);

// 	for (size_t i = 0; i < count; i++)
// 	{
// 		char *dup = ft_strdup(originals[i]);
// 		if (dup == NULL)
// 		{
// 			printf("ft_strdup failed for input: \"%s\"\n", originals[i]);
// 			continue;
// 		}
// 		printf("Original: \"%s\" | Duplicate: \"%s\"\n", originals[i], dup);
// 		free(dup);
// 	}
// 	return 0;
// }