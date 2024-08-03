/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:50:17 by mcutura           #+#    #+#             */
/*   Updated: 2024/08/04 01:06:58 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "connect4.h"
#include "libft.h"

int	main(int ac, char **av)
{
	t_board		tree[MAX_NODE_NB];

	if (ac != 3)
	{
		ft_dprintf(STDERR_FILENO, USAGE);
		return (EXIT_FAILURE);
	}
	if (init_game(&(tree[0]), av[1], av[2]))
		return (EXIT_FAILURE);

	game_loop(&(tree[0]));

	for (int i = 0; i < tree[0].height; ++i)
		free(tree[0].map[i]);
	free(tree[0].map);
	return (EXIT_SUCCESS);
}


