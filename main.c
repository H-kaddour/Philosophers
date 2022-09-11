/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:21:21 by hkaddour          #+#    #+#             */
/*   Updated: 2022/09/11 20:34:22 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	data_init(t_data *data)
{
	data->n_philo = ft_atoi(data->args[0]);
	data->t_die = ft_atoi(data->args[1]);
	data->t_eat = ft_atoi(data->args[2]);
	data->t_sleep = ft_atoi(data->args[3]);
	if (data->chk_last_arg == 1)
		data->n_time_philo_die = ft_atoi(data->args[4]);
	else
		data->n_time_philo_die = 0;
}

static int	parsing(t_data *data)
{
	int	i;

	i = 0;
	if (data->len == 5)
		data->chk_last_arg = 0;
	else if (data->len == 6)
		data->chk_last_arg = 1;
	if (only_numbers(data))
	{
		printf("Only numbers\n");
		return (0);
	}
	while (i < data->len - 1)
	{
		if (ft_atoi(data->args[i]) <= 0)
		{
			printf("Numbers should be bigger than 0\n");
			return (0);
		}
		i++;
	}
	data_init(data);
	return (1);
}

static void	get_time(t_data *data)
{
	struct timeval	recent_time;

	gettimeofday(&recent_time, NULL);
	//data->time = (recent_time.tv_sec * 1000) + (recent_time.tv_usec / 1000);
	data->time = (recent_time.tv_sec * 1000 + recent_time.tv_usec) / 1000;
}

void	*the_usual(void *d)
{
	t_data *data;

	data = (t_data *)d;
	//data->len = 4;
	pthread_mutex_lock(&data->info.l_fork);
	pthread_mutex_lock(&data->info.r_fork);
	printf("hey %d\n", data->info.id);
	pthread_mutex_unlock(&data->info.l_fork);
	pthread_mutex_unlock(&data->info.r_fork);
	//printf("hey %d", data->info.id);
	return (0);
}

void	init_thread_helper(t_data *data)
{
	int	i;

	i = 0;
	get_time(data);
	//printf("%ld\n", data->time);
	while (i < data->n_philo)
	{
		data->info.id = i + 1;
		data->info.l_fork = data->forks[i];
		if (i == data->n_philo)
			data->info.r_fork = data->forks[0];
		else
			data->info.r_fork = data->forks[i + 1];
		data->info.num_eat = 0;
		data->info.last_meal = 0;
		pthread_create(&data->info.th_philo[i], NULL, &the_usual, data);
		//pthread_join(data->info.th_philo[i], NULL);
		i++;
	}
	i = 0;
	while (i < data->n_philo)
	{
		pthread_join(data->info.th_philo[i], NULL);
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
}

void	init_thread(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	while (i < data->n_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	init_thread_helper(data);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		data.args = &av[1];
		data.len = ac;
		if (!parsing(&data))
			return (0);
		init_thread(&data);
	}
	else
		printf("Invalid number of arguments\n");
	return (0);
}
