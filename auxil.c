/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxil.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:35:10 by fvieira           #+#    #+#             */
/*   Updated: 2023/03/29 15:35:13 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *nptr)
{
	int	nb;
	int	flag;
	int	count;

	flag = 0;
	nb = 0;
	count = 0;
	while (nptr[count] == '\t' || nptr[count] == '\n' || nptr[count] == '\r'
		|| nptr[count] == '\v' || nptr[count] == ' ' || nptr[count] == '\f')
		count++;
	if (nptr[count] == '+' && nptr[count + 1] != '-')
		count++;
	if (nptr[count] == '-')
	{
		flag = 1;
		count++;
	}
	while (nptr[count] >= 48 && nptr[count] <= 57)
	{
		nb = nb * 10 + nptr[count] - 48;
		count++;
	}
	if (flag == 1)
		nb *= -1;
	return (nb);
}
