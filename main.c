/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:21:21 by hkaddour          #+#    #+#             */
/*   Updated: 2022/09/16 14:26:09 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*the_usual(void *p)
{
	t_philo *philo;
	int	i;

	i = 0;
	philo = (t_philo *) p;
	//here an infinity loop and check if the thread is dead to break
	//another mutex if u wanna write a msg of sleep or some like that
	//while (philo->data->stop != 1)
	//{
		eat(philo);
		//if (philo->data->stop == 1)
		//	return (0);
		goto_sleep(philo);
		msg(philo, "is thinking");
		//check_death(philo);
		//printf("%d\n", philo->data->stop);
		//if (philo->data->stop == 1)
		//	return (0);
			//break ;
	//}
	return (0);
}

void	init_thread_helper(t_data *data, t_philo *philo)
{
	int	i;
	t_philo	*trav;

	i = 0;
	trav = philo;
	data->stop = 0;
	data->chk_t_eat = 0;
	data->start_time = get_time();
	while (trav)
	{
		trav->id = i + 1;
		trav->r_fork = data->forks[i];
		if (i == 0)
			trav->l_fork = data->forks[data->n_philo - 1];
		else
			trav->l_fork = data->forks[i - 1];
		//if (i == data->n_philo - 1)
		//	trav->l_fork = data->forks[0];
		//else
		//	trav->l_fork = data->forks[i + 1];
		trav->num_eat = 0;
		trav->last_meal = get_time();
		trav->data = data;
		pthread_create(&trav->th_philo, NULL, &the_usual, trav);
		usleep(30);
		trav = trav->next;
		i++;
	}
	//check_death(philo);
	//pthread_create(&data->dead, NULL, &check_death, philo);
	//i should get a time when the threads start for dying
	//end_all_thread(philo);
}

void	init_thread(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	(void)philo;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	while (i < data->n_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->msg, NULL);
	//init_thread_helper(data, philo);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philo;
	int	i;

	i = 0;
	if (ac == 5 || ac == 6)
	{
		data.args = &av[1];
		data.len = ac;
		//here check int max and min and " sjfkj"
		if (!parsing(&data))
			return (0);
		philo = init_node(&data);
		init_thread(&data, philo);
		while (1)
		{
			//init_thread(&data, philo);
			init_thread_helper(&data, philo);
			check_death(philo);
			if (data.stop == 1)
				return (0);
		}
		//fix death of 1 philo
		end_all_thread(philo);
	}
	else
		printf("Invalid number of arguments\n");
	return (0);
}
