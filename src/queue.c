/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 20:31:17 by nam-vu            #+#    #+#             */
/*   Updated: 2024/08/04 22:47:57 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "connect4.h"

// static void	swap_nodes(t_board **a, t_board **b)
// {
// 	t_board	*temp;

// 	(*a)->queue_idx ^= (*b)->queue_idx;
// 	(*b)->queue_idx ^= (*a)->queue_idx;
// 	(*a)->queue_idx ^= (*b)->queue_idx;
// 	temp = *a;
// 	*a = *b;
// 	*b = temp;
// }

// int	queue_assert(t_board **heap, int heap_size, char *operation)
// {
// 	for (int j = 0; j < heap_size; j++)
// 	{
// 		if (heap[j]->queue_idx != j)
// 		{
// 			ft_dprintf(2, "%s failed; idx\n", operation);
// 			queue_print(heap, heap_size);
// 		}
// 	}

// 	for (int j = 0; j < heap_size - 1; j++)
// 	{
// 		if (heap[j]->heuristic < heap[j + 1]->heuristic)
// 		{
// 			ft_dprintf(2, "%s failed\n", operation);
// 			queue_print(heap, heap_size);
// 		}
// 	}
// 	return (EXIT_SUCCESS);
// }

// void	queue_print(t_board **heap, int heap_size)
// {
// 	for (int k = 0; k < heap_size; k++)
// 	{
// 		ft_printf("idx = %i priority = %f\n", heap[k]->queue_idx, heap[k]->heuristic);
// 	}
// }

static void	update_idx(t_board **heap, int *heap_size)
{
	for (int i = 0; i < *heap_size; i++)
	{
		heap[i]->queue_idx = i;
	}
}

void	queue_push(t_board **heap, t_board *new, int *heap_size)
{
	int i;

	// queue_assert(heap, *heap_size, "push in");
	if (*heap_size == 0)
	{
		heap[0] = new;
		heap[0]->queue_idx = 0;
		(*heap_size)++;
		// queue_assert(heap, *heap_size, "push");
		return ;
	}
	for (i = 0; i < *heap_size; i++)
	{
		if (heap[i]->heuristic < new->heuristic)
			break;
	}
	if (i < *heap_size)
	{
		ft_memmove(heap + i + 1, heap + i, (*heap_size - i) * sizeof(t_board *));
	}
	heap[i] = new;
	(*heap_size)++;
	update_idx(heap, heap_size);
	// queue_assert(heap, *heap_size, "push");
}

void	queue_pop(t_board **heap, int *heap_size)
{
	// queue_assert(heap, *heap_size, "pop in");
	if (*heap_size == 0)
	{
			// queue_assert(heap, *heap_size, "pop");
			return ;
	}

	ft_memmove(heap, heap + 1, (*heap_size - 1) * sizeof(t_board *));
	(*heap_size)--;
	update_idx(heap, heap_size);
	// queue_assert(heap, *heap_size, "pop");
}

void	queue_update(t_board **heap, int *heap_size, int index)
{
	if (index < 0 || index >= *heap_size)
	{
		// queue_assert(heap, *heap_size, "update");
		return ;
	}

	t_board	*new = heap[index];
	if (index < *heap_size - 1)
		ft_memmove(heap + index, heap + index + 1, (*heap_size - index - 1) * sizeof(t_board *));
	(*heap_size)--;
	// queue_assert(heap, *heap_size, "push before update");
	queue_push(heap, new, heap_size);
}

// void	queue_push(t_board **heap, t_board *new, int *heap_size)
// {
// 	int		new_index;
// 	int		index;

// 	if (*heap_size == 0)
// 	{
// 		heap[0] = new;
// 		heap[0]->queue_idx = 0;
// 		(*heap_size)++;
// 		return ;
// 	}
// 	index = *heap_size;
// 	new_index = *heap_size;
// 	heap[index] = new;
// 	heap[index]->queue_idx = new_index;
// 	(*heap_size)++;
// 	while (heap[new_index = ((new_index - 1) / 2)]->heuristic < new->heuristic)
// 	{
// 		swap_nodes(&heap[index], &heap[new_index]);
// 		index = (index - 1) / 2;
// 		new_index = index;
// 	}
// 	queue_assert(heap, *heap_size, "push");
// }

// void	queue_pop(t_board **heap, int *heap_size)
// {
// 	int		index;
// 	int		new_index;

// 	if (*heap_size == 0)
// 		return ;

// 	if (*heap_size == 1)
// 	{
// 		heap[0] = 0;
// 		(*heap_size)--;
// 		return;
// 	}

// 	index = 0;
// 	heap[0] = heap[*heap_size - 1];
// 	(*heap_size)--;
// 	if (index * 2 + 2 < *heap_size && heap[index * 2 + 1] && heap[index * 2 + 2])
// 	{
// 		new_index = index * 2 + 1;
// 		if (heap[index * 2 + 2]->heuristic > heap[new_index]->heuristic)
// 			new_index = index * 2 + 2;
// 	}
// 	else if ((index * 2 + 2 < *heap_size) && heap[index * 2 + 2])
// 		new_index = index * 2 + 2;
// 	else if ((index * 2 + 1 < *heap_size) && heap[index * 2 + 1])
// 		new_index = index * 2 + 1;
// 	else
// 	{
// 		ft_printf("weird pop\n");
// 		exit(0);
// 	}

// 	while (heap[index] < heap[new_index])
// 	{
// 		swap_nodes(&heap[index], &heap[new_index]);
// 		index = new_index;

// 		if ((index * 2 + 2 < *heap_size) && heap[index * 2 + 1] && heap[index * 2 + 2])
// 		{
// 			new_index = index * 2 + 1;
// 			if ((heap[index * 2 + 2]->heuristic) > heap[new_index]->heuristic)
// 				new_index = index * 2 + 2;
// 		}
// 		else if ((index * 2 + 2) < *heap_size && heap[index * 2 + 2])
// 			new_index = index * 2 + 2;
// 		else if ((index * 2 + 1) < *heap_size && heap[index * 2 + 1])
// 			new_index = index * 2 + 1;
// 	}
// 	(*heap_size)--;
// 		queue_assert(heap, *heap_size, "pop");
// }

// void	queue_update(t_board **heap, int *heap_size, int index)
// {
// 	int		new_index;

// 	if (index >= *heap_size || *heap_size <= 1)
// 		return ;
	
// 	if ((index - 1) / 2 >= 0)
// 	{
// 		new_index = (index - 1) / 2;
// 		if (heap[new_index]->heuristic < heap[index]->heuristic)
// 		{
// 			new_index = index;
// 			while (heap[(new_index - 1) / 2]->heuristic < heap[index]->heuristic)
// 			{
// 				new_index = (new_index - 1) / 2;
// 				swap_nodes(&heap[new_index], &heap[index]);
// 				index = new_index;
// 			}
// 		}
// 		else
// 		{
// 			if (index * 2 + 2 < *heap_size && heap[index * 2 + 1] && heap[index * 2 + 2])
// 			{
// 				new_index = index * 2 + 1;
// 				if (heap[index * 2 + 2]->heuristic > heap[new_index]->heuristic)
// 					new_index = index * 2 + 2;
// 			}
// 			else if ((index * 2 + 2 < *heap_size) && heap[index * 2 + 2])
// 				new_index = index * 2 + 2;
// 			else if ((index * 2 + 1 < *heap_size) && heap[index * 2 + 1])
// 				new_index = index * 2 + 1;
// 			else
// 				return;


// 			while (heap[index] < heap[new_index])
// 			{
// 				swap_nodes(&heap[index], &heap[new_index]);
// 				index = new_index;

// 				if ((index * 2 + 2 < *heap_size) && heap[index * 2 + 1] && heap[index * 2 + 2])
// 				{
// 					new_index = index * 2 + 1;
// 					if ((heap[index * 2 + 2]->heuristic) > heap[new_index]->heuristic)
// 						new_index = index * 2 + 2;
// 				}
// 				else if ((index * 2 + 2) < *heap_size && heap[index * 2 + 2])
// 					new_index = index * 2 + 2;
// 				else if ((index * 2 + 1) < *heap_size && heap[index * 2 + 1])
// 					new_index = index * 2 + 1;
// 			}
// 		}
// 	}
	
// 	queue_assert(heap, *heap_size, "update");
// }
