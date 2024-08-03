/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 19:50:01 by mcutura           #+#    #+#             */
/*   Updated: 2024/08/03 20:21:31 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "connect4.h"

//todo: Lap
//priority queue for leafs
////pop
////push
////update

//todo: Martin
//check end state
//simulation function
//bakpropagation function
//calculating UCB/UCT
//update struct
////win states, all states, index in the queue

int	update_heuristic(t_board *new)
{
	int i;
	for (i = 0; i < new->height; i++)
	{
		if (new->map[i][new->move])
			break;
	}
	
	int counter_col = 0;
	int j = i;
	while (j < new->height && new->map[j++][new->move] == new->map[i][new->move])
		counter_col++;
	
	int counter_row_left = 0;
	j = 1;
	while (new->move - j > 0 && new->map[i][new->move - j++] == new->map[i][new->move])
		counter_row_left++;
	
	int counter_row_right = 0;
	j = 1;
	while (new->move + j < new->width && new->map[i][new->move + j++] == new->map[i][new->move])
		counter_row_right++;
	
	return (max(new->heuristic, max(counter_col, counter_row_right + counter_row_left + 1)));
}

int	new_state(t_board *old, t_board *new, int col_nb, char player)//pass col_nb - 1
{
	if (col_nb < 0 || col_nb > old->width || old->map[0][col_nb] != 0)
	{
		ft_dprintf(2, "error: wrong argument\n");
		return (EXIT_FAILURE);
	}
	for (int i = 0; i < old->height; i++)
	{
		for (int j = 0; j < old->width; j++)
		{
			new->map[i][j] = old->map[i][j];
		}
	}
	for (int i = 0; i < old->height; i++)
	{
		if (old->map[i][col_nb] == 0)
		{
			new->map[i][col_nb] = player;
			new->move = col_nb;
			new->heuristic = old->heuristic;
			new->heuristic = update_heuristic(new);
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_FAILURE);
}