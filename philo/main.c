/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:21:21 by hkaddour          #+#    #+#             */
/*   Updated: 2022/09/22 13:59:27 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*the_usual(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (21)
	{
		if (philo->id % 2 == 0)
			usleep(100);
		eat(philo);
		goto_sleep(philo);
		msg(philo, "\e[95mis thinking");
		//if (philo->data->stop == 1)
		//	return (0);
	}
	return (0);
}

static void	init_thread(t_data *data, t_philo *philo)
{
	t_philo	*trav;
	int		i;

	i = 0;
	trav = philo;
	data->stop = 0;
	data->chk_t_eat = 0;
	pthread_mutex_init(&data->msg, NULL);
	while (trav)
	{
		trav->id = i + 1;
		pthread_mutex_init(&philo->fork, NULL);
		trav->num_eat = 0;
		trav->last_meal = get_time();
		trav->start_philo = get_time();
		trav->data = data;
		trav->first = philo;
		pthread_create(&trav->th_philo, NULL, &the_usual, trav);
		trav = trav->next;
		i++;
	}
}
//id need stop
int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philo;

	if (ac == 5 || ac == 6)
	{
		data.args = &av[1];
		data.len = ac;
		if (!parsing(&data))
			return (0);
		philo = init_node(&data);
		init_thread(&data, philo);
		if (check_death(philo))
		{
			end_all_thread(philo);
			return (0);
		}
	}
	else
		printf("Invalid number of arguments\n");
	return (0);
}
