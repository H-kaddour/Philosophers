/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:21:21 by hkaddour          #+#    #+#             */
/*   Updated: 2022/09/12 15:14:44 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	nn = 0;

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

static int	get_time(void)
{
	long		time;
	struct timeval	recent_time;

	gettimeofday(&recent_time, NULL);
	//data->time = (recent_time.tv_sec * 1000) + (recent_time.tv_usec / 1000);
	time = (recent_time.tv_sec * 1000 + recent_time.tv_usec) / 1000;
	return (time);
}

void	msg(t_data *data, char *msg)
{
	data->p_time = get_time() - data->time;
	usleep(1);
	printf("%ld		%d		%s\n", data->p_time, data->info->id, msg);
}

void	eat(t_data *data)
{
	pthread_mutex_lock(&data->info->l_fork);
	msg(data, "has taken a fork");
	pthread_mutex_lock(&data->info->r_fork);
	msg(data, "has taken a fork");
	msg(data, "is eating");
	pthread_mutex_unlock(&data->info->l_fork);
	pthread_mutex_unlock(&data->info->r_fork);
}

void	*the_usual(void *d)
{
	t_data *data;
	int	i;

	i = 0;
	data = (t_data *)d;
	eat(data);
	//pthread_mutex_lock(&data->info->l_fork);
	//pthread_mutex_lock(&data->info->r_fork);
	//while (i < 10000)
	//{
	//	i++;
	//	nn++;
	//}
	//printf("hey %d\n", data->info->id);
	//pthread_mutex_unlock(&data->info->l_fork);
	//pthread_mutex_unlock(&data->info->r_fork);
	//printf("hey %d", data->info.id);
	return (0);
}

void	init_thread_helper(t_data *data)
{
	int	i;
	t_philo	*trav;

	i = 0;
	trav = data->info;
	data->time = get_time();
	//printf("%ld\n", data->time);
	//while (i < data->n_philo)
	//while (trav)
	while (i < data->n_philo)
	{
		trav->id = i + 1;
		trav->l_fork = data->forks[i];
		if (i == 0)
			data->info->r_fork = data->forks[data->n_philo - 1];
		else
			data->info->r_fork = data->forks[i - 1];
		//if (i == data->n_philo)
		//	data->info->r_fork = data->forks[0];
		//else
		//	data->info->r_fork = data->forks[i + 1];
		trav->num_eat = 0;
		trav->last_meal = 0;
		pthread_create(&trav->th_philo, NULL, &the_usual, data);
		//pthread_join(data->info.th_philo[i], NULL);
		trav = trav->next;
		i++;
	}
	i = 0;
	trav = data->info;
	while (i < data->n_philo)
	{
		pthread_join(trav->th_philo, NULL);
		//pthread_mutex_destroy(&data->forks[i]);
		trav = trav->next;
		i++;
	}
	i = 0;
	trav = data->info;
	while (i < data->n_philo)
	{
		//pthread_join(trav->th_philo, NULL);
		pthread_mutex_destroy(&data->forks[i]);
		trav = trav->next;
		i++;
	}
	//printf("%d\n", nn);
	//pthread_mutex_destroy(&data->info.l_fork);
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
	//pthread_mutex_init(&data->info.l_fork, NULL);
	init_thread_helper(data);
}

int	main(int ac, char **av)
{
	t_data	data;
	int	i;

	i = 0;
	if (ac == 5 || ac == 6)
	{
		data.args = &av[1];
		data.len = ac;
		if (!parsing(&data))
			return (0);
		init_node(&data);
		//while (data.info)
		//{
		//	printf("%d\n", i);
		//	i++;
		//	data.info = data.info->next;
		//}
		init_thread(&data);
	}
	else
		printf("Invalid number of arguments\n");
	return (0);
}
