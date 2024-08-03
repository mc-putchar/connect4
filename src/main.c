/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:50:17 by mcutura           #+#    #+#             */
/*   Updated: 2024/08/03 20:22:28 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "connect4.h"
#include "libft.h"

int	main(int ac, char **av)
{
	if (ac != 3)
	{
		ft_dprintf(2, "error: wrong number of arguments\n");
		return (EXIT_FAILURE);
	}

	const int		height = ft_atoi(av[1]);
	const int		width = ft_atoi(av[2]);
	
	if (height < 6 || width < 7)
	{
		ft_dprintf(2, "error: arguments are too smol\n");
		return (EXIT_FAILURE);
	}

	t_board			tree[MAX_NODE_NB];

	tree[0].map = malloc(height * sizeof(char *));
	for (int i = 0; i < height; i++)
	{
		tree[0].map[i] = ft_calloc(width, sizeof(char));
	}
	tree[0].width = width;
	tree[0].height = height;
	tree[0].move = -1;
	// time_t	start = time(NULL);
	int i = 0;
	while (i < MAX_NODE_NB)// && (time(NULL) - start < 2)
	{
		tree[i].map = ft_calloc(height, sizeof(char *));
		i++;
	}
	ft_printf("%i\n", i);
	// for (i = 0; i < MAX_NODE_NB; i++)
	// {

	// }

	return (EXIT_SUCCESS);
}


