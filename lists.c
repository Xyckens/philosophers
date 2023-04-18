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
	indiv->nbr_philo = i;
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
	t_indiv	*temp;
	t_indiv	*indiv;

	c = 1;
	indiv = new(c, teatn, both->philo);
	temp = indiv;
	both->indivarray = malloc((both->philo->nbr_philo) * sizeof(t_indiv *));
	while (c++ < both->philo->nbr_philo - 1)
		lstadd_back(&indiv, new(c, teatn, both->philo));
	while (indiv->next != NULL)
		indiv = indiv->next;
	indiv->next = temp;
	indiv = temp;
	c = 0;
	printf("indiv->nbr_philo %d\n", indiv->nbr_philo);
	while (indiv->nbr_philo != both->philo->nbr_philo - 1)
	{
		printf("CCCCCCC %d\n", c);
		both->indivarray[c] = indiv;
		indiv = indiv->next;
		c++;
	}
	both->indivarray[c] = indiv;
	indiv = indiv->next;
	return (both->indivarray);
}

void	freelst(t_both *both)
{
	t_indiv	*sublst;
	t_indiv	*next;
	int		c;

	if (!both->indivarray[0])
		return ;
	sublst = both->indivarray[0];
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
	//both->indiv = NULL;
}
