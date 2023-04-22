/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:43:24 by fvieira           #+#    #+#             */
/*   Updated: 2023/03/29 14:43:25 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philostruct_init(t_both *both, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] == '-')
				return (!printf("No Negative Numbers Please! 🥰🥰\n"));
			if (!is_digit_or_signal(argv[i][j++]))
				return (!printf("Invalid Input! 😡🤬\n"));
		}
	}
	both->philo = malloc(sizeof(t_philo));
	both->philo->nbr_philo = ft_atoi(argv[1]) + 1;
	both->philo->ttd = ft_atoi(argv[2]);
	both->philo->tte = ft_atoi(argv[3]);
	both->philo->tts = ft_atoi(argv[4]);
	both->philo->thrd = malloc((ft_atoi(argv[1]) + 1) * sizeof(pthread_t));
	pthread_mutex_init(&both->philo->deaths, NULL);
	both->philo->any_dead = 0;
	return (1);
}

void	mutex_changestate(t_indiv *indiv, char state)
{
	if (state == 'l')
	{
		pthread_mutex_lock(indiv->fork_r);
		pthread_mutex_lock(indiv->fork_l);
		pickingfork(indiv);
	}
	else if (state == 'u')
	{
		pthread_mutex_unlock(indiv->fork_r);
		pthread_mutex_unlock(indiv->fork_l);
	}
}

void	*f(void *arg)
{
	t_indiv	*indiv;

	indiv = (t_indiv *)arg;
	while (indiv->nbr_eaten != 0)
	{
		if (death(indiv, 0) == 1)
			break ;
		mutex_changestate(indiv, 'l');
		if (death(indiv, 1) == 1)
		{
			mutex_changestate(indiv, 'u');
			break ;
		}
		eating(indiv);
		mutex_changestate(indiv, 'u');
		if (death(indiv, 0) == 1)
			break ;
		sleeping(indiv);
		if (death(indiv, 0) == 1)
			break ;
		thinking(indiv);
	}
	return (NULL);
}

void	mutexinit(t_both *both)
{
	int	i;

	i = -1;
	while (both->philo->nbr_philo > 2 && ++i < both->philo->nbr_philo - 1)
	{
		pthread_mutex_init(&both->philo->forkmut[i], NULL);
		both->indivarray[i]->fork_r = &both->philo->forkmut[i];
		if (i < both->philo->nbr_philo - 1)
			both->indivarray[i + 1]->fork_l = &both->philo->forkmut[i];
		if (i + 1 == both->philo->nbr_philo - 1)
		{
			both->indivarray[0]->fork_l = &both->philo->forkmut[i];
			both->indivarray[i]->fork_l = &both->philo->forkmut[i];
			both->indivarray[i]->fork_r = &both->philo->forkmut[i - 1];
		}
	}
	if (both->philo->nbr_philo == 2)
	{
		pthread_mutex_init(&both->philo->forkmut[0], NULL);
		both->indivarray[0]->fork_r = &both->philo->forkmut[0];
		pthread_create(&both->philo->thrd[0], NULL, &d, both->indivarray[0]);
		pthread_join(both->philo->thrd[0], NULL);
	}
}

int	main(int argc, char **argv)
{
	t_both			both;
	int				i;
	struct timeval	begin;

	if (argc >= 5 && argc <= 6)
	{
		if (philostruct_init(&both, argv))
		{	
			if (argc >= 6)
				both.philo->nbr_eat = ft_atoi(argv[5]);
			else
				both.philo->nbr_eat = -1;
			gettimeofday(&begin, NULL);
			both.philo->begin = begin;
			both.indivarray = connectthem(&both, begin);
			mutexinit(&both);
			i = -1;
			while (both.philo->nbr_philo > 2 && ++i < both.philo->nbr_philo - 1)
				pthread_create(&both.philo->thrd[i], 0, &f, both.indivarray[i]);
			freelst(&both);
		}
	}
	else
		printf("Wrong Number of Args! 🤭🤭\n");
	return (0);
}
//grab fork, eat, leave fork, sleep, think, repeat
