/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   learn_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:18:34 by hkaddour          #+#    #+#             */
/*   Updated: 2022/09/12 11:47:42 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	x = 0;
pthread_mutex_t	mutex;

typedef struct	l
{
	int	a;
} t_l;

void	*try(void *data)
{
	int	*id;
	int i;

	i = 0;
	id = (int *)data;
	//while (i < 100)
	//{
		pthread_mutex_lock(&mutex);
		printf("hey %d\n", *id);
		//i++;
		//x++;
		pthread_mutex_unlock(&mutex);
	//}
	//printf("%d\n", x);
	//printf("thread\n");
	return (0);
}

int	main(void)
{
	//pthread_t	th1;
	//pthread_t	th2;
	int	i;
	pthread_t th[10];

	i = 0;
	//thread in a while loop
	pthread_mutex_init(&mutex, NULL);
	while (i < 10)
	{
		pthread_create(&th[i], NULL, try, &i);
		i++;
	}
	i = 0;
	while (i < 10)
	{
		pthread_join(th[i], NULL);
		i++;
	}
	//printf("%d\n", x);
	pthread_mutex_destroy(&mutex);

	//this one to specific what this thread gonna do
	//**pthread_mutex_init(&mutex, NULL);
	//**pthread_create(&th1, NULL, try, NULL);
	//**printf("thread 1 started execution\n");
	//**pthread_create(&th2, NULL, try, NULL);
	//**printf("thread 2 started execution\n");
	//and this one to wait for the thread to finish it's execution and then u can end the process
	//**pthread_join(th1, NULL);
	//**printf("thread 1 finishes\n");
	//**pthread_join(th2, NULL);
	//**printf("thread 2 finishes\n");
	//**pthread_mutex_destroy(&mutex);
	//**printf("%d\n", x);
	return (0);
}


//time cmd show u how much ur program takes to run
