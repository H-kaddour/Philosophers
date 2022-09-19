/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 15:35:50 by hkaddour          #+#    #+#             */
/*   Updated: 2022/09/19 08:59:19 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	lock_fork(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->fork) != 0)
		return ;
	msg(philo, "\e[96mhas taken a fork");
	if (philo->id == philo->data->n_philo)
	{
		if (pthread_mutex_lock(&philo->first->fork) != 0)
			return ;
	}
	else
	{
		if (pthread_mutex_lock(&philo->next->fork) != 0)
			return ;
	}
	msg(philo, "\e[96mhas taken a fork");
}

static void	unlock_fork(t_philo *philo)
{
	if (pthread_mutex_unlock(&philo->fork) != 0)
		return ;
	if (philo->id == philo->data->n_philo)
	{
		if (pthread_mutex_unlock(&philo->first->fork) != 0)
			return ;
	}
	else
	{
		if (pthread_mutex_unlock(&philo->next->fork) != 0)
			return ;
	}
}

void	goto_sleep(t_philo *philo)
{
	msg(philo, "\e[92mis sleeping");
	usleep(philo->data->t_sleep * 1000);
}

void	eat(t_philo *philo)
{
	lock_fork(philo);
	msg(philo, "is eating");
	philo->last_meal = get_time();
	philo->num_eat++;
	if (philo->data->chk_last_arg == 1)
	{
		if (philo->num_eat == philo->data->n_time_philo_eat)
			philo->data->chk_t_eat++;
	}
	usleep(philo->data->t_eat * 1000);
	unlock_fork(philo);
}
