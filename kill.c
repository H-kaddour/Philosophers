/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 15:47:14 by hkaddour          #+#    #+#             */
/*   Updated: 2022/09/16 14:28:39 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_if_dead(t_philo *philo)
{
	long	time;

	if (philo->data->chk_last_arg == 1)
	{
		//if (philo->data->chk_t_eat == philo->data->n_time_philo_eat)
		if (philo->num_eat == philo->data->n_time_philo_eat)
		{
			//printf("kids");
			philo->data->stop = 1;
			return (1);
		}
	}
	//time = get_time() - philo->data->start_time;
	time = get_time() - philo->last_meal;
	//if (time >= philo->data->t_die)
	if (time > philo->data->t_die)
	{
		//printf("la\n");
		philo->data->stop = 1;
		msg(philo, "is dead");
		return (1);
	}
	return (0);
}

void	*check_death(void *p)
{
	int		i;
	t_philo *philo;
	t_philo *trav;

	i = 0;
	philo = (t_philo *)p;
	trav = philo;
	while (trav)
	{
		if (check_if_dead(trav))
		{
			//printf("niggas in paris");
			//msg(philo, "is dead");
			return (0);
		}
		trav = trav->next;
	}
	return (0);
}

void	end_all_thread(t_philo *philo)
{
	int	i;
	t_philo	*trav;

	i = 0;
	trav = philo;
	//pthread_join(trav->data->dead, NULL);
	while (trav)
	{
		pthread_join(trav->th_philo, NULL);
		trav = trav->next;
	}
	while (i < philo->data->n_philo)
	{
		pthread_mutex_destroy(&philo->data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&philo->data->msg);
	//destroy the last mutex of msg
	//here free all nodes
}