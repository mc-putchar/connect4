/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:50:17 by mcutura           #+#    #+#             */
/*   Updated: 2024/08/04 18:45:33 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "connect4.h"

int	main(int ac, char **av)
{
	t_board		board;

	if (ac != 3)
	{
		ft_dprintf(STDERR_FILENO, USAGE);
		return (EXIT_FAILURE);
	}
	if (init_game(&board, av[1], av[2]))
		return (EXIT_FAILURE);
	
	game_loop(&board);

	for (int i = 0; i < board.height; ++i)
		free(board.map[i]);
	free(board.map);
	return (EXIT_SUCCESS);
}


