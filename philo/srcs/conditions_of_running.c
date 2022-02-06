/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions_of_running.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:14:19 by acousini          #+#    #+#             */
/*   Updated: 2022/02/04 21:06:41 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	is_dead(t_philo *philo)
{
	int		ret;

	ret = 1;
	pthread_mutex_lock(&philo->alive_check);
	ret = philo->alive;
	pthread_mutex_unlock(&philo->alive_check);
	return (ret);
}

int	is_running(t_philo *philo)
{
	int		ret;

	ret = 1;
	pthread_mutex_lock(&philo->base->running_check);
	ret = philo->base->running;
	pthread_mutex_unlock(&philo->base->running_check);
	return (ret);
}

int	has_eaten(t_philo *philo)
{
	unsigned long		last_meal;
	int					is_alive;

	is_alive = 1;
	pthread_mutex_lock(&philo->meal_check);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->meal_check);
	if ((time_from_beginning(philo->base->start)
			- last_meal > (unsigned long long int)philo->base->ttd))
	{
		pthread_mutex_lock(&philo->alive_check);
		philo->alive = 0;
		pthread_mutex_unlock(&philo->alive_check);
		write_dead(philo);
		pthread_mutex_lock(&philo->base->running_check);
		philo->base->running = 0;
		pthread_mutex_unlock(&philo->base->running_check);
		is_alive = 0;
	}
	return (is_alive);
}

int	has_eaten_enough(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_check);
	if (philo->meals_count == philo->base->nb_eats)
	{
		pthread_mutex_unlock(&philo->meal_check);
		pthread_mutex_lock(&philo->alive_check);
		philo->alive = 0;
		pthread_mutex_unlock(&philo->alive_check);
		return (1);
	}		
	pthread_mutex_unlock(&philo->meal_check);
	return (0);
}
