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

t_indiv	*new(t_philo *philo, int i, struct timeval time_eaten)
{
	t_indiv	*indiv;

	(void)philo;
	indiv = (t_indiv *) malloc(sizeof(t_indiv));
	indiv->nbr_philo = i;
	indiv->time_eaten = time_eaten;
	indiv->next = NULL;
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
	indiv = new(philo, c, teatn);
	temp = indiv;
	while (c++ < philo->nbr_philo - 1)
	{
		lstadd_back(&indiv, new(philo, c, teatn));
	}
	while (indiv->next != NULL)
		indiv = indiv->next;
	indiv->next = temp;
	indiv = temp;
	return (indiv);
}

void	freelst(t_indiv **indiv)
{
	t_indiv	*sublst;
	t_indiv	*next;

	if (!indiv)
		return ;
	sublst = *indiv;
	while (sublst)
	{
		next = sublst->next;
		pthread_mutex_destroy(&sublst->fork_L);
		pthread_detach(sublst->thread_id);
		free(sublst);
		sublst->next = NULL;
		sublst = next;
	}
	*indiv = NULL;
}

void	printstats(t_indiv *indiv, int len)
{
	int	temp;

	temp = len;
	while (temp-- > 1 && indiv != NULL)
	{
		printf("nbr %d\n", indiv->nbr_philo);
		printf("thread %lu\n", indiv->thread_id);
		//printf("fork direito  %p\n", indiv->fork_R);
		//printf("fork esquerdo %p\n", indiv->fork_L);
		indiv = indiv->next;
	}
}
