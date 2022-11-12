/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 15:47:14 by hkaddour          #+#    #+#             */
/*   Updated: 2022/09/22 14:01:22 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo)
{
	t_philo	*trav;

	trav = philo;
	while (trav)
	{
		if (philo->data->chk_last_arg == 1)
		{
			if (philo->data->n_philo == philo->data->chk_t_eat)
			{
				philo->data->stop = 1;
				return (1);
			}
		}
		if ((get_time() - philo->last_meal) > philo->data->t_die)
		{
			philo->data->stop = 1;
			msg(philo, "\e[91mis dead");
			return (1);
		}
		trav = trav->next;
		if (!trav)
			trav = philo;
	}
	return (0);
}

void	end_all_thread(t_philo *philo)
{
	t_philo	*trav;
	int		i;

	i = 0;
	trav = philo;
	while (trav)
	{
		pthread_detach(trav->th_philo);
		trav = trav->next;
	}
	trav = philo;
	while (trav)
	{
		pthread_mutex_destroy(&philo->fork);
		free(trav);
		trav = trav->next;
	}
	pthread_mutex_destroy(&philo->data->msg);
}
