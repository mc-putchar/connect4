/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 00:21:30 by mcutura           #+#    #+#             */
/*   Updated: 2024/08/04 01:07:12 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "connect4.h"
#include "libft.h"

int	init_game(t_board *board, char *av1, char *av2)
{
	int const	height = ft_atoi(av1);
	int const	width = ft_atoi(av2);
	
	if (height < 6 || width < 7)
	{
		ft_dprintf(STDERR_FILENO, ERR_PARAMS);
		return (1);
	}
	board->map = malloc(height * sizeof(char *));
	if (!board->map)
	{
		ft_dprintf(STDERR_FILENO, ERR_MALLOC);
		return (1);
	}
	for (int i = 0; i < height; i++)
	{
		board->map[i] = ft_calloc(width, sizeof(char));
		if (!board->map[i])
		{
			while (i--)
				free(board->map[i]);
			free(board->map);
			ft_dprintf(STDERR_FILENO, ERR_MALLOC);
			return (1);
		}
	}
	board->width = width;
	board->height = height;
	board->move = -1;
	return (0);
}

int	choose_turn(void)
{
	unsigned int	seed;

	seed = (unsigned int)(time(NULL));
	srand(seed);
	return (rand() & 1);
}
