/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 20:57:55 by fvieira           #+#    #+#             */
/*   Updated: 2023/04/03 20:57:56 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_indiv	*new(int i, struct timeval time_eaten, t_philo *philo)
{
	t_indiv	*indiv;

	indiv = (t_indiv *) malloc(sizeof(t_indiv));
	indiv->nbr_philo = i + 1;
	indiv->time_eaten = time_eaten;
	indiv->next = NULL;
	indiv->nbr_eaten = philo->nbr_eat;
	indiv->philo = philo;
	indiv->is_dead = 0;
	return (indiv);
}

void	lstadd_back(t_indiv **lst, t_indiv *new)
{
	t_indiv	*going_to_end;

	if (!*lst)
	{
		(*lst) = new;
		return ;
	}
	going_to_end = *lst;
	while (going_to_end->next != NULL)
		going_to_end = going_to_end->next;
	going_to_end->next = new;
}

t_indiv	**connectthem(t_both *both, struct timeval teatn)
{
	int		c;

	both->indivarray = malloc((both->philo->nbr_philo + 1) * sizeof(t_indiv *));
	c = 0;
	both->indivarray[0] = new(c, teatn, both->philo);
	while (c++ < both->philo->nbr_philo - 1)
		both->indivarray[c] = new(c, teatn, both->philo);
	return (both->indivarray);
}

void	freelst(t_both *both)
{
	int		c;

	if (!both->indivarray[0])
		return ;
	c = -1;
	while (++c < both->philo->nbr_philo - 1)
	{
		pthread_join(both->philo->thread_id[c], NULL);
		pthread_detach(both->philo->thread_id[c]);
		pthread_mutex_destroy(&both->philo->forkstate[c]);
	}
}
