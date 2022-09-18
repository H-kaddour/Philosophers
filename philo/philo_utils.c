/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 11:40:19 by hkaddour          #+#    #+#             */
/*   Updated: 2022/09/18 18:13:56 by hkaddour         ###   ########.fr       */
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
	int	i;
	int	j;

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
	t_philo	*head;
	t_philo	*node;
	t_philo	*tmp;
	int		i;

	i = 1;
	head = malloc(sizeof(t_philo));
	if (!head)
		return (0);
	tmp = head;
	head->next = 0;
	while (i < data->n_philo)
	{
		node = malloc(sizeof(t_philo));
		if (!node)
			return (0);
		head->next = node;
		head = node;
		i++;
	}
	head->next = 0;
	return (tmp);
}

void	msg(t_philo *philo, char *msg)
{
	philo->data->p_time = get_time() - philo->start_philo;
	pthread_mutex_lock(&philo->data->msg);
	printf("\e[1m\e[94m%ld ms		\e[93m%d	%s\n\e[0m", \
			philo->data->p_time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->msg);
}

long	get_time(void)
{
	long			time;
	struct timeval	recent_time;

	gettimeofday(&recent_time, NULL);
	time = (recent_time.tv_sec * 1000000 + recent_time.tv_usec) / 1000;
	return (time);
}
