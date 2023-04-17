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

t_indiv	*new(int i, struct timeval time_eaten, int nbr_eat)
{
	t_indiv	*indiv;

	indiv = (t_indiv *) malloc(sizeof(t_indiv));
	indiv->nbr_philo = i;
	indiv->time_eaten = time_eaten;
	indiv->next = NULL;
	indiv->nbr_eaten = nbr_eat;
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

t_indiv	*connectthem(t_philo *philo, struct timeval teatn)
{
	int		c;
	t_indiv	*temp;
	t_indiv	*indiv;

	c = 1;
	indiv = new(c, teatn, philo->nbr_eat);
	temp = indiv;
	while (c++ < philo->nbr_philo - 1)
		lstadd_back(&indiv, new(c, teatn, philo->nbr_eat));
	while (indiv->next != NULL)
		indiv = indiv->next;
	indiv->next = temp;
	indiv = temp;
	c = 0;
	while (indiv->nbr_philo != philo->nbr_philo - 1)
	{
		philo->indivarray[c] = indiv;
		c++;
		indiv = indiv->next;
	}
	philo->indivarray[c] = indiv;
	indiv = indiv->next;
	return (indiv);
}

void	freelst(t_both *both)
{
	t_indiv	*sublst;
	t_indiv	*next;
	int		c;

	if (!both->indiv)
		return ;
	sublst = both->indiv;
	c = -1;
	while (++c < both->philo->nbr_philo - 1)
	{
		pthread_join(both->philo->thread_id[c], NULL);
		pthread_detach(both->philo->thread_id[c]);
		pthread_mutex_destroy(&sublst->fork_L);
		next = sublst->next;
		sublst->next = NULL;
		//free(both->indiv);
		sublst = next;
	}
	//pthread_detach(both->philo->thread_id[c - 1]);
	both->indiv = NULL;
}
