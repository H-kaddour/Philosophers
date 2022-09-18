/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 15:47:14 by hkaddour          #+#    #+#             */
/*   Updated: 2022/09/18 09:18:52 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_if_dead(t_philo *philo)
{
	long	time;

	if (philo->data->chk_last_arg == 1)
	{
		//if (philo->data->chk_t_eat == philo->data->n_time_philo_eat)
		//if (philo->num_eat == philo->data->n_time_philo_eat)
		//printf("%d == %d\n", philo->num_eat, philo->data->n_time_philo_eat);
		//if (philo->num_eat == philo->data->n_time_philo_eat)
		if (philo->data->n_philo == philo->data->chk_t_eat)
		{
			//printf("ylh\n");
			//tl3 chi msg
			//printf("err eat\n");
			//printf("%d == %d\n", philo->num_eat, philo->data->n_time_philo_eat);
			philo->data->stop = 1;
			//msg(philo, "equal max meal");
			return (1);
		}
	}
	//time = get_time() - philo->data->start_time;
	time = get_time() - philo->last_meal;
	//printf("%ld\n", time);
	//if (time >= philo->data->t_die)
	//check if the thread didn't eat and equal 0 time should - to start of that thread instead of last_meal
	//if ((get_time() - philo->last_meal) >= philo->data->t_die)
	if (time >= philo->data->t_die)
	{
		//printf("la\n");
		philo->data->stop = 1;
		//no need for stop
		msg(philo, "is dead");
		return (1);
	}
	return (0);
}

int	check_death(t_philo *philo)
{
	int		i;
	long	time;
	//t_philo *philo;
	t_philo *trav;

	i = 0;
	//philo = (t_philo *)p;
	trav = philo;
	//printf("just entered check death func\n");
	//while (trav)
	//while (1)
	while (trav)
	{
		//if (check_if_dead(trav))
		//{
		//	//printf("niggas in paris");
		//	//msg(philo, "is dead");
		//	//end_all_thread(philo);
		//	return (1);
		//}
		if (philo->data->chk_last_arg == 1)
		{
			if (philo->data->n_philo == philo->data->chk_t_eat)
			{
				philo->data->stop = 1;
				return (1);
			}
		}
		//printf("%ld\n", philo->last_meal);
		//if (philo->last_meal == 0)
		//	time = get_time() - philo->start_philo;
		//else
		//	time = get_time() - philo->last_meal;
		//usleep(30);
		time = get_time() - philo->last_meal;
		//printf("%ld\n", time);
		//printf("\n");
		//printf("");
		//if (time >= philo->data->t_die)
		//if ((get_time() - philo->last_meal) >= philo->data->t_die)
		if (time >= philo->data->t_die)
		{
			philo->data->stop = 1;
			msg(philo, "is dead");
			return (1);
		}
		//
		trav = trav->next;
		if (!trav)
			trav = philo;
	}
	//printf("Im out of this fucn death\n");
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
