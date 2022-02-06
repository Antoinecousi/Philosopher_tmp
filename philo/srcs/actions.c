/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 19:07:32 by acousini          #+#    #+#             */
/*   Updated: 2022/02/06 20:33:32 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	philo_start_thinking(t_philo *philo)
{
	if (is_dead(philo) || is_running(philo))
		mutex_screen(philo, "is thinking\n");
	else
		write_dead(philo);
	if (philo->base->nb_phils % 2 == 1)
		wait_in_ms((philo->base->ttd - philo->base->tts
				- philo->base->tte) / 2);
}

void	philo_start_sleep(t_philo *philo)
{
	if (is_dead(philo) || is_running(philo))
	{
		mutex_screen(philo, "is sleeping\n");
		wait_in_ms(philo->base->tts);
	}
	else
		write_dead(philo);
}
