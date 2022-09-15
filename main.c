/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:21:21 by hkaddour          #+#    #+#             */
/*   Updated: 2022/09/15 08:57:46 by hkaddour         ###   ########.fr       */
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
		data->n_time_philo_eat = ft_atoi(data->args[4]);
	else
		data->n_time_philo_eat = 0;
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

void	msg(t_philo *philo, char *msg)
{
	//usleep(1000);
	philo->data->p_time = get_time() - philo->data->start_time;
	//printf("%d\n", get_time());
	//printf("%ld\n", philo->data->time);
	//printf("%ld\n", philo->data->p_time);
	pthread_mutex_lock(&philo->data->msg);
	printf("%ld		%d		%s\n", philo->data->p_time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->msg);
}

void	lock_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->r_fork);
		msg(philo, "has taken a fork");
		pthread_mutex_lock(&philo->l_fork);
		msg(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->l_fork);
		msg(philo, "has taken a fork");
		pthread_mutex_lock(&philo->r_fork);
		msg(philo, "has taken a fork");
	}
}

void	unlock_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->r_fork);
		pthread_mutex_unlock(&philo->l_fork);
	}
	else
	{
		pthread_mutex_unlock(&philo->l_fork);
		pthread_mutex_unlock(&philo->r_fork);
	}
}

void	time_eat(t_philo *philo)
{
	usleep(philo->data->t_eat);
}

void	eat(t_philo *philo)
{
	lock_fork(philo);
	msg(philo, "is eating");
	philo->last_meal = get_time();
	philo->num_eat++;
	//i should count all time eating in all the philo nodes
	//if (philo->data->chk_last_arg == 1)
	//{
	//	philo->data->chk_t_eat++;
	//}
	time_eat(philo);
	//time_eat(philo);
	//here check if the time u eat equal the lst arg so to stop
	//**goto_sleep(philo);
	//and then start thinking
	//and check if the thread is dead
	unlock_fork(philo);
}

void	goto_sleep(t_philo *philo)
{
	usleep(philo->data->t_sleep);
	msg(philo, "is sleeping");
}

void	*the_usual(void *p)
{
	t_philo *philo;
	int	i;

	i = 0;
	philo = (t_philo *) p;
	//here an infinity loop and check if the thread is dead to break
	//another mutex if u wanna write a msg of sleep or some like that
	while (philo->data->stop == 0)
	{
		eat(philo);
		goto_sleep(philo);
		msg(philo, "is thinking");
		if (philo->data->stop == 1)
			break ;
	}
	return (0);
}

void	end_all_thread(t_philo *philo)
{
	int	i;
	t_philo	*trav;

	i = 0;
	trav = philo;
	while (trav)
	{
		pthread_join(trav->th_philo, NULL);
		trav = trav->next;
	}
	//pthread_join(trav->data->dead, NULL);
	while (i < philo->data->n_philo)
	{
		pthread_mutex_destroy(&philo->data->forks[i]);
		i++;
	}
	//pthread_mutex_destroy(&philo->data->msg);
	//destroy the last mutex of msg
	//here free all nodes
}

int	check_if_dead(t_philo *philo)
{
	long	time;

	if (philo->data->chk_last_arg == 1)
	{
		if (philo->num_eat == philo->data->n_time_philo_eat)
		{
			//printf("kids");
			philo->data->stop = 1;
			return (1);
		}
	}
	time = get_time() - philo->data->start_time;
	if (time >= philo->data->t_die)
	{
		//printf("lala");
		philo->data->stop = 1;
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
			msg(philo, "is dead");
			return (0);
		}
		trav = trav->next;
	}
	return (0);
}

void	init_thread_helper(t_data *data, t_philo *philo)
{
	int	i;
	t_philo	*trav;

	i = 0;
	data->start_time = get_time();
	data->stop = 0;
	trav = philo;
	while (trav)
	{
		trav->id = i + 1;
		trav->r_fork = data->forks[i];
		if (i == data->n_philo - 1)
			trav->l_fork = data->forks[0];
		else
			trav->l_fork = data->forks[i + 1];
		trav->num_eat = 0;
		trav->last_meal = get_time();
		trav->data = data;
		pthread_create(&trav->th_philo, NULL, &the_usual, trav);
		trav = trav->next;
		i++;
	}
	pthread_create(&data->dead, NULL, &check_death, philo);
	//if (data->stop == 1)
	//	pthread_join(data->dead, NULL);
	//i should get a time when the threads start for dying
	end_all_thread(philo);
}

void	init_thread(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	while (i < data->n_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->msg, NULL);
	init_thread_helper(data, philo);
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
		if (!parsing(&data))
			return (0);
		philo = init_node(&data);
		init_thread(&data, philo);
	}
	else
		printf("Invalid number of arguments\n");
	return (0);
}
