/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 11:40:19 by hkaddour          #+#    #+#             */
/*   Updated: 2022/09/11 15:28:17 by hkaddour         ###   ########.fr       */
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