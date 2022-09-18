/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 15:35:50 by hkaddour          #+#    #+#             */
/*   Updated: 2022/09/18 16:52:02 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_fork(t_philo *philo)
{
  pthread_mutex_lock(&philo->fork);
  msg(philo, "has taken a fork");
	if (philo->id == philo->data->n_philo)
  	pthread_mutex_lock(&philo->first->fork);
	else
  	pthread_mutex_lock(&philo->next->fork);
  msg(philo, "has taken a fork");
  //if (philo->id != philo->data->n_philo - 1)
  //{
  //    pthread_mutex_lock(&philo->data->forks[philo->id]);
  //    msg(philo, "has taken a fork");
  //    pthread_mutex_lock(&philo->data->forks[philo->id + 1]);
  //    msg(philo, "has taken a fork");
  //}
  //else
  //{
  //    pthread_mutex_lock(&philo->data->forks[philo->id]);
  //    msg(philo, "has taken a fork");
  //    pthread_mutex_lock(&philo->data->forks[0]);
  //    msg(philo, "has taken a fork");
  //}
	//if (philo->id % 2 == 0)
	//{
	//	pthread_mutex_lock(&philo->fork);
	//	msg(philo, "has taken a fork");
	//	if (!philo->next)
	//		pthread_mutex_unlock(&philo->first->fork);
	//	else
	//		pthread_mutex_lock(&philo->next->fork);
	//	msg(philo, "has taken a fork");
	//}
	//else
	//{
	//	if (!philo->next)
	//		pthread_mutex_unlock(&philo->first->fork);
	//	else
	//		pthread_mutex_lock(&philo->next->fork);
	//	msg(philo, "has taken a fork");
	//	pthread_mutex_lock(&philo->fork);
	//	msg(philo, "has taken a fork");
	//}
}

void	unlock_fork(t_philo *philo)
{
  pthread_mutex_unlock(&philo->fork);
	if (philo->id == philo->data->n_philo)
  	pthread_mutex_unlock(&philo->first->fork);
	else
  	pthread_mutex_unlock(&philo->next->fork);
  //if (philo->id != philo->data->n_philo - 1)
  //{
  //    pthread_mutex_unlock(&philo->data->forks[philo->id]);
  //    pthread_mutex_unlock(&philo->data->forks[philo->id + 1]);
  //}
  //else
  //{
  //    pthread_mutex_unlock(&philo->data->forks[philo->id]);
  //    pthread_mutex_unlock(&philo->data->forks[0]);
  //}
	//if (philo->id % 2 == 0)
	//{
	//	pthread_mutex_unlock(&philo->fork);
	//	if (!philo->next)
	//		pthread_mutex_unlock(&philo->first->fork);
	//	else
	//		pthread_mutex_unlock(&philo->next->fork);
	//}
	//else
	//{
	//	if (!philo->next)
	//		pthread_mutex_unlock(&philo->first->fork);
	//	else
	//		pthread_mutex_unlock(&philo->next->fork);
	//	pthread_mutex_unlock(&philo->fork);
	//}
}

void	ft_uusleep(long time)
{
	long	t;

	t = 0;
	t = get_time();
	while ((get_time() - t) < time)
		usleep(50);
	return ;
}

void	goto_sleep(t_philo *philo)
{
	//usleep(philo->data->t_sleep);
	msg(philo, "is sleeping");
	usleep(philo->data->t_sleep * 1000);
	//ft_uusleep(philo->data->t_sleep);
}

void	eat(t_philo *philo)
{
	lock_fork(philo);
  //**pthread_mutex_lock(&philo->data->forks[philo->id]);
  //**msg(philo, "has taken a fork");
	//**if (philo->id == philo->data->n_philo)
  //**	pthread_mutex_lock(&philo->data->forks[0]);
	//**else
  //**	pthread_mutex_lock(&philo->data->forks[philo->id + 1]);
  //**msg(philo, "has taken a fork");
  //pthread_mutex_lock(&philo->fork);
  //msg(philo, "has taken a fork");
	//if (philo->id == philo->data->n_philo)
  //	pthread_mutex_lock(&philo->first->fork);
	//else
  //	pthread_mutex_lock(&philo->next->fork);
  //msg(philo, "has taken a fork");
	msg(philo, "is eating");
	if (philo->data->stop == 1)
		return ;
	philo->last_meal = get_time();
	philo->num_eat++;
	if (philo->data->chk_last_arg == 1)
	{
		if (philo->num_eat == philo->data->n_time_philo_eat)
			philo->data->chk_t_eat++;
	}
	//i should count all time eating in all the philo nodes
	//if (philo->data->chk_last_arg == 1)
	//{
	//	philo->data->chk_t_eat++;
	//}
	//ft_uusleep(philo->data->t_eat);
	usleep(philo->data->t_eat * 1000);
	//time_eat(philo);
	//time_eat(philo);
	//here check if the time u eat equal the lst arg so to stop
	//**goto_sleep(philo);
	//and then start thinking
	//and check if the thread is dead
	//if (philo->data->stop != 1)
	unlock_fork(philo);
	//printf("ylh tle9t ferchita %d\n", philo->id);
  //**pthread_mutex_unlock(&philo->fork);
	//**if (philo->id == philo->data->n_philo)
  //**	pthread_mutex_unlock(&philo->first->fork);
	//**else
  //**	pthread_mutex_unlock(&philo->next->fork);
  //pthread_mutex_unlock(&philo->data->forks[philo->id]);
	//if (philo->id == philo->data->n_philo)
  //	pthread_mutex_unlock(&philo->data->forks[0]); else
  //	pthread_mutex_unlock(&philo->data->forks[philo->id + 1]);
	if (philo->data->stop == 1)
		return ;
	//printf("%d\n", philo->data->stop);
}
