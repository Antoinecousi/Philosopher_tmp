/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 11:08:50 by acousini          #+#    #+#             */
/*   Updated: 2022/02/06 20:35:25 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	output_state(t_philo *philo, char *str)
{
	printf("%lldms  Philosopher %d %s",
		time_from_beginning(philo->base->start), philo->id, str);
}

void	mutex_screen(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->base->screen_lock);
	if (is_dead(philo) && is_running(philo))
		output_state(philo, str);
	pthread_mutex_unlock(&philo->base->screen_lock);
}

void	write_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->base->die_lock);
	pthread_mutex_lock(&philo->base->screen_lock);
	if ((is_dead(philo) == 0 || is_running(philo) == 0)
		&& philo->base->printed_death == 0)
	{
		output_state(philo, "died\n");
		philo->base->printed_death = 1;
	}
	pthread_mutex_unlock(&philo->base->die_lock);
	pthread_mutex_unlock(&philo->base->screen_lock);
}
