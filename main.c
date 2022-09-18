/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:21:21 by hkaddour          #+#    #+#             */
/*   Updated: 2022/09/18 16:56:28 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*the_usual(void *p)
{
	t_philo *philo;
	int	i;

	i = 0;
	philo = (t_philo *)p;
	//here an infinity loop and check if the thread is dead to break
	//another mutex if u wanna write a msg of sleep or some like that
	//while (24)
	//usleep(30);
	//if (philo->id % 2 == 0)
	//	usleep(100);
	while (philo->data->stop != 1)
	{
		if (philo->id % 2 == 0)
			usleep(100);
		eat(philo);
		//printf("hey\n");
		//printf("******%d\n", philo->data->stop);
		if (philo->data->stop == 1)
			return (0);
		goto_sleep(philo);
		msg(philo, "is thinking");
		//check_death(philo);
		//printf("%d\n", philo->data->stop);
		if (philo->data->stop == 1)
			return (0);
		//usleep(100);
			//break ;
	}
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
	pthread_mutex_init(&data->msg, NULL);
	while (trav)
	{
		trav->id = i + 1;
		//trav->r_fork = data->forks[i];
		//trav->fork = data->forks[i];
		pthread_mutex_init(&philo->fork, NULL);
		//if (i == 0)
		//	trav->l_fork = data->forks[data->n_philo - 1];
		//else
		//	trav->l_fork = data->forks[i - 1];
		//if (i == data->n_philo - 1)
		//	trav->l_fork = &data->forks[0];
		//else
		//	trav->l_fork = &data->forks[i + 1];
		trav->num_eat = 0;
		trav->last_meal = get_time();
		//trav->last_meal = 0;
		trav->start_philo = get_time();
		trav->data = data;
		trav->first = philo;
		pthread_create(&trav->th_philo, NULL, &the_usual, trav);
		//usleep(50);
		trav = trav->next;
		i++;
	}
	//printf("im out %d\n", i);
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

//void	init_philo(t_data *data, t_philo *philo)
//{
//	t_philo	*trav;
//
//	trav = philo;
//	while (trav)
//	{
//		trav = trav->next;
//	}
//}

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
		if (!parsing(&data))
			return (0);
		philo = init_node(&data);
		//init_philo(&data, philo);
		//init_thread(&data, philo);
		init_thread_helper(&data, philo);
		if (check_death(philo))
		{
			end_all_thread(philo);
			//printf("ylh 5erj\n");
			return (0);
		}
		//end_all_thread(philo);
	}
	else
		printf("Invalid number of arguments\n");
	return (0);
}
