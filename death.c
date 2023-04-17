/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 18:37:02 by fvieira           #+#    #+#             */
/*   Updated: 2023/04/15 18:37:03 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	any_death(t_both *both)
{
	int	temp;
	t_indiv	*templst;

	temp = both->indiv->nbr_philo;
	templst = both->indiv;
	if (both->indiv->is_dead == 1)
		return(1);
	templst = templst->next;
	while (templst->nbr_philo != temp)
	{
		if (templst->is_dead == 1)
		{
			while (templst->nbr_philo != temp)
				templst = templst->next;
			return(1);
		}
		templst = templst->next;
	}
	return(0);
}
