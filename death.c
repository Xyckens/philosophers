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

	temp = both->indiv->nbr_philo;
	if (both->indiv->is_dead == 1)
		return(1);
	both->indiv = both->indiv->next;
	while (both->indiv->nbr_philo != temp)
	{
		if (both->indiv->is_dead == 1)
		{
			while (both->indiv->nbr_philo != temp)
				both->indiv = both->indiv->next;
			return(1);
		}
		both->indiv = both->indiv->next;
	}
	return(0);
}
