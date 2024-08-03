/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect4.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:51:11 by mcutura           #+#    #+#             */
/*   Updated: 2024/08/03 20:23:14 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNECT4_H
# define CONNECT4_H

# include <stdlib.h>
# include <time.h>
# include <stdio.h>
# include "libft.h"

typedef struct s_board
{
	char	**map;
	char	height;
	char	width;
	int		move;
	int		heuristic;
}	t_board;

# define NB_CHILD 3
# define FIRST 'X'
# define SECOND 'O'
# define MAX_NODE_NB 300000

int	max(int a, int b);

int	update_heuristic(t_board *new);
int	new_state(t_board *old, t_board *new, int col_nb, char player);

//queue.c
void	queue_print(t_board **heap, int heap_size);
void	queue_push(t_board **heap, t_board *new, int *heap_size);
void	queue_pop(t_board **heap, int *heap_size);
void	queue_update(t_board **heap, int *heap_size, int index);
int		queue_assert(t_board **heap, int heap_size);

#endif
