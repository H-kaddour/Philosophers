/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 15:37:55 by hkaddour          #+#    #+#             */
/*   Updated: 2022/09/15 15:51:36 by hkaddour         ###   ########.fr       */
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
		data->n_time_philo_eat = ft_atoi(data->args[4]);
	else
		data->n_time_philo_eat = 0;
}

int	parsing(t_data *data)
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
