/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:19:23 by hkaddour          #+#    #+#             */
/*   Updated: 2022/09/18 18:23:09 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <strings.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	char			**args;
	int				len;
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_time_philo_eat;
	int				chk_last_arg;
	int				chk_t_eat;
	long			p_time;
	int				stop;
	pthread_mutex_t	msg;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				num_eat;
	long			last_meal;
	long			start_philo;
	t_data			*data;
	pthread_t		th_philo;
	struct s_philo	*first;
	pthread_mutex_t	fork;
	struct s_philo	*next;
}	t_philo;

/*********** Utils ***********/
int		ft_atoi(const char *str);
int		only_numbers(t_data *data);
void	msg(t_philo *philo, char *msg);
long	get_time(void);
t_philo	*init_node(t_data *data);

/*********** Parsing ***********/
int		parsing(t_data *data);

/*********** Eat ***********/
void	eat(t_philo *philo);
void	goto_sleep(t_philo *philo);

/*********** Kill ***********/
int		check_death(t_philo *philo);
void	end_all_thread(t_philo *philo);

#endif
