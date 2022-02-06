/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 18:56:30 by acousini          #+#    #+#             */
/*   Updated: 2022/02/04 21:14:17 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_each_philo(t_philo *philo, int id, t_base *base)
{
	philo->id = id + 1;
	philo->alive = 1;
	philo->base = base;
	philo->meals_count = 0;
	philo->last_meal = 0;
	if (pthread_mutex_init(&philo->meal_check, NULL))
		return (1);
	if (pthread_mutex_init(&philo->alive_check, NULL))
		return (1);
	return (0);
}

int	init_philosophers(t_base *base, int i)
{
	t_philo	*phil;

	phil = malloc(sizeof(t_philo) * base->nb_phils);
	if (!phil)
		return (1);
	base->malloced = 1;
	base->philosophers = phil;
	base->start = time_now_in_ms();
	base->inited = 1;
	while (++i < base->nb_phils)
		init_fork(base, i);
	i = -1;
	while (++i < base->nb_phils)
	{
		if (init_each_philo(&base->philosophers[i], i, base))
			return (1);
		if (pthread_create(&base->philosophers[i].thread_id, NULL, routine,
				(void *)&base->philosophers[i]))
			return (1);
		usleep(20);
	}
	i = -1;
	while (++i < base->nb_phils)
		pthread_join(base->philosophers[i].thread_id, NULL);
	return (0);
}

int	ft_fill_mutexes(t_base *base)
{
	if (pthread_mutex_init(&base->running_check, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&base->screen_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&base->die_lock, NULL) != 0)
		return (1);
	base->is_dead = 0;
	base->malloced = 0;
	base->printed_death = 0;
	base->running = 1;
	return (0);
}

void	fill_base(t_base *base, char **str, int i)
{
	if (ft_fill_mutexes(base))
		return (clean_base(base, "Failed init mutexes. Exit\n"));
	base->nb_phils = ft_atoi(str[0]);
	if (base->nb_phils < 1)
		return (clean_base(base, "Wrong number of philosophers. Exit\n"));
	base->ttd = ft_atoi(str[1]);
	if (base->ttd <= 59)
		return (clean_base(base, "Wrong value of time to die. Exit\n"));
	base->tte = ft_atoi(str[2]);
	if (base->tte <= 59)
		return (clean_base(base, "Wrong value of time to eat. Exit\n"));
	base->tts = ft_atoi(str[3]);
	if (base->tts <= 59)
		return (clean_base(base, "Wrong value of time to sleep. Exit\n"));
	if (i == 6)
	{
		base->nb_eats = ft_atoi(str[4]);
		if (base->nb_eats <= 0)
			return (clean_base(base, "Wrong value of meals needed. Exit\n"));
	}
	else
		base->nb_eats = -1;
	if (init_philosophers(base, -1))
		return (clean_base(base, "Problem init phils. Exit\n"));
	clean_base(base, "");
}
