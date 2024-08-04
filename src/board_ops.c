/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 19:50:01 by mcutura           #+#    #+#             */
/*   Updated: 2024/08/04 21:59:43 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "connect4.h"

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
	for (int i = old->height - 1; i >= 0; --i)
	{
		if (old->map[i][col_nb] == 0)
		{
			new->map[i][col_nb] = player;
			new->move = col_nb;
			new->playouts = 0;
			new->wins = 0;
			new->heuristic = MAX_NODE_NB;
			new->depth = old->depth + 1;
			// new->heuristic = update_heuristic(new);
			// if (DEBUG)
			// 	print_board(new);
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_FAILURE);
}

t_moves	*get_moves(t_board *board)
{
	t_moves	*moves;
	size_t	n;

	moves = malloc(sizeof(t_moves));
	if (!moves)
		return (NULL);
	n = 0;
	for (int i = 0; i < board->width; ++i)
		n += (board->map[0][i] == 0);
	moves->moves = malloc(n * sizeof(int));
	if (!moves->moves)
		return (free(moves), NULL);
	moves->size = n;
	for (int i = board->width - 1; i >= 0; --i)
		if (!board->map[0][i])
			moves->moves[--n] = i;
	return (moves);
}
