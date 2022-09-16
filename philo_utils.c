/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 11:40:19 by hkaddour          #+#    #+#             */
/*   Updated: 2022/09/15 16:30:17 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	rslt;

	i = 0;
	sign = 1;
	rslt = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		rslt = (rslt * 10) + (str[i] - '0');
		i++;
	}
	return (rslt * sign);
}

int	only_numbers(t_data *data)
{
	int i;
	int j;
	
	i = 0;
	while (data->args[i])
	{
		j = 0;
		while (data->args[i][j])
		{
			if (!(data->args[i][j] >= '0' && data->args[i][j] <= '9'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

t_philo	*init_node(t_data *data)
{
	int	i;
	t_philo	*head;
	t_philo	*node;
	t_philo	*tmp;

	i = 1;
	head = malloc(sizeof(t_philo));
	//data->info = head;
	tmp = head;
	head->next = NULL;
	while (i < data->n_philo)
	{
		node = malloc(sizeof(t_philo));
		head->next = node;
		head = node;
		i++;
	}
	head->next = NULL;
	return (tmp);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2 && *s1 && *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
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
	//if (ft_strcmp(msg, "is dead"))
	//	pthread_mutex_unlock(&philo->data->msg);
	//else
	//{
	//	//exit(0);
	//	return ;
	//}
	pthread_mutex_unlock(&philo->data->msg);
	//if (philo->data->stop == 0)
	//	pthread_mutex_unlock(&philo->data->msg);
	//else
	//{
	//	//exit(0);
	//	//pthread_mutex_destroy(&philo->data->msg);
	//	return ;
	//}
}

int	get_time(void)
{
	long		time;
	struct timeval	recent_time;

	gettimeofday(&recent_time, NULL);
	time = (recent_time.tv_sec * 1000) + (recent_time.tv_usec / 1000);
	//time = (recent_time.tv_sec * 1000 + recent_time.tv_usec) / 1000;
	return (time);
}
