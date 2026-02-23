/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchemali <gchemali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:38:44 by gchemali          #+#    #+#             */
/*   Updated: 2025/06/12 18:20:09 by gchemali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*array;
	size_t	size_max;

	size_max = (size_t)-1;
	if (nmemb != 0 && size > size_max / nmemb)
		return (NULL);
	array = malloc(nmemb * size);
	if (array == NULL)
		return (NULL);
	ft_bzero(array, (nmemb * size));
	return (array);
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// int main(void)
// {
// 	size_t nmemb = 5;
// 	size_t size = sizeof(int);
// 	int *arr = (int *)ft_calloc(nmemb, size);

// 	if (arr == NULL)
// 	{
// 		printf("Memory allocation failed.\n");
// 		return 1;
// 	}

// 	// Check that memory is zero-initialized
// 	printf("Allocated array elements:\n");
// 	for (size_t i = 0; i < nmemb; i++)
// 	{
// 		printf("arr[%zu] = %d\n", i, arr[i]);
// 	}

// 	free(arr);
// 	return 0;
// }