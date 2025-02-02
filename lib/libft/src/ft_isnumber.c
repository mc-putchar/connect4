/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 23:15:24 by mcutura           #+#    #+#             */
/*   Updated: 2024/06/22 02:39:39 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isnumber(char const *str)
{
	if (*str == '-' || *str == '+')
		++str;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		++str;
	}
	return (1);
}
