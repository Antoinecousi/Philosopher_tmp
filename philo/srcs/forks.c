/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 12:37:34 by acousini          #+#    #+#             */
/*   Updated: 2022/02/04 21:03:09 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	init_fork(t_base *base, int i)
{
	pthread_mutex_t	*fork;

	fork = malloc(sizeof(pthread_mutex_t));
	if (!fork)
		return (1);
	if (pthread_mutex_init(fork, NULL) != 0)
		return (1);
	base->philosophers[i].left_fork = fork;
	if (i > 0)
		base->philosophers[i - 1].right_fork = base->philosophers[i].left_fork;
	if (i == base->nb_phils - 1)
		base->philosophers[i].right_fork = base->philosophers[0].left_fork;
	base->inited += 1;
	return (0);
}

int	take_fork(pthread_mutex_t *fork, t_philo *philo)
{
	pthread_mutex_lock(fork);
	mutex_screen(philo, "has taken a fork\n");
	return (1);
}

int	philo_start_eat(t_philo *philo)
{
	if ((philo->id + 1) % 2 == 0)
	{
		take_fork(philo->left_fork, philo);
		take_fork(philo->right_fork, philo);
	}
	else
	{
		take_fork(philo->right_fork, philo);
		take_fork(philo->left_fork, philo);
	}
	pthread_mutex_lock(&philo->meal_check);
	philo->meals_count++;
	philo->last_meal = time_from_beginning(philo->base->start);
	pthread_mutex_unlock(&philo->meal_check);
	mutex_screen(philo, "is eating\n");
	wait_in_ms(philo->base->tte);
	unlock_forks(philo);
	return (1);
}

void	unlock_forks(t_philo *philo)
{
	if ((philo->id + 1) % 2 == 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}
