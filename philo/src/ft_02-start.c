/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_02-start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woliveir                                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:03:59 by woliveir          #+#    #+#             */
/*   Updated: 2022/12/30 12:52:55 by woliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_philosopher.h"

static	t_philo	*ft_start_philosophers_aux(long n_p, t_philo *phi, t_pth *m_th);

t_philo	*ft_start_philosophers(long nbr_phi, t_philo *phi)
{
	long	i;
	t_pth	m_th;

	i = 0;
	phi->data->firststamp = ft_timestamp();
	while (i < nbr_phi)
	{
		if (pthread_create(&phi[i].th, NULL, &ft_actions, &phi[i]) != 0)
		{
			(phi->data)->ret = -6;
			ft_error(phi->data);
			return (phi);
		}
		i++;
	}
	if (pthread_create(&m_th, NULL, &ft_monitor, phi) != 0)
	{
		(phi->data)->ret = -6;
		ft_error(phi->data);
		return (phi);
	}
	ft_start_philosophers_aux(nbr_phi, phi, &m_th);
	return (phi);
}

static t_philo	*ft_start_philosophers_aux(long n_ph, t_philo *phi, t_pth *m_th)
{
	long			i;

	i = 0;
	while (i < n_ph)
	{
		if (pthread_join(phi[i].th, NULL) != 0)
		{
			(phi->data)->ret = -7;
			ft_error(phi->data);
			return (phi);
		}
		i++;
	}
	if (pthread_join(*m_th, NULL) != 0)
	{
		(phi->data)->ret = -7;
		ft_error(phi->data);
		return (phi);
	}
	return (phi);
}
