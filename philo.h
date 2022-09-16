/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:19:23 by hkaddour          #+#    #+#             */
/*   Updated: 2022/09/15 15:50:14 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <strings.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct	s_data
{
	char		**args;
	int			len;
	int			n_philo;
	int			t_die;
	int			t_eat;
	int			t_sleep;
	int			n_time_philo_eat;
	int			chk_last_arg;
	int			chk_t_eat;
	long		start_time;
	long		p_time;
	int			stop;
	pthread_t	dead;
	pthread_mutex_t	msg;
	pthread_mutex_t *forks;
} t_data;

typedef struct	s_philo
{
	int							id;
	int							num_eat;
	long						last_meal;
	//maybe here i should take a time of starting dial thread for dying time
	t_data					*data;
	pthread_t				th_philo;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	r_fork;
	struct s_philo	*next;
} t_philo;

/*********** Utils ***********/
int			ft_atoi(const char *str);
int			only_numbers(t_data *data);
t_philo	*init_node(t_data *data);
int			ft_strcmp(const char *s1, const char *s2);
void		msg(t_philo *philo, char *msg);
int			get_time(void);

/*********** Parsing ***********/
int		parsing(t_data *data);

/*********** Eat ***********/
void	eat(t_philo *philo);
void	goto_sleep(t_philo *philo);

/*********** Kill ***********/
void	*check_death(void *p);
void	end_all_thread(t_philo *philo);


#endif
