/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchemali <gchemali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:27:05 by gchemali          #+#    #+#             */
/*   Updated: 2025/06/12 21:40:13 by gchemali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen(int n)
{
	int	len;

	len = (n <= 0);
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	nb;
	int		len;

	nb = n;
	len = ft_numlen(n);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	str[len--] = '\0';
	if (nb == 0)
		str[0] = '0';
	if (nb < 0)
	{
		str[0] = '-';
		nb *= -1;
	}
	while (nb > 0)
	{
		str[len--] = (nb % 10) + '0';
		nb /= 10;
	}
	return (str);
}

// #include <stdio.h>
// #include <stdlib.h>
// int main(void)
// {
// 	int test_values[] = {0, 123, -456, 2147483647, -2147483648};
// 	size_t num_tests = sizeof(test_values) / sizeof(test_values[0]);

// 	for (size_t i = 0; i < num_tests; i++)
// 	{
// 		char *result = ft_itoa(test_values[i]);
// 		if (result == NULL)
// 		{
// 			printf("ft_itoa failed for input %d\n", test_values[i]);
// 		}
// 		else
// 		{
// 			printf("ft_itoa(%d) = %s\n", test_values[i], result);
// 			free(result);
// 		}
// 	}
// 	return 0;
// }