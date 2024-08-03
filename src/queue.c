/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nam-vu <nam-vu@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 20:31:17 by nam-vu            #+#    #+#             */
/*   Updated: 2024/08/03 20:31:28 by nam-vu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/connect4.h"

static void	swap_nodes(t_board **a, t_board **b)
{
	t_board	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static int max_child(t_board **heap, int heap_size, int index)
{
	int	max;
	int	res = -1;

	if ((index * NB_CHILD) > heap_size)
		return (-1);

	for (int i = 1; i <= NB_CHILD; i++)
	{
		if (heap[index * NB_CHILD + i])
		{
			max = heap[index * NB_CHILD]->heuristic;
			res = index * NB_CHILD + i;
			break ;
		}
	}

	for (int i = 1; i <= NB_CHILD; i++)
	{
		if (((index * NB_CHILD + i) < heap_size) && heap[index * NB_CHILD + i] && (max < heap[index * NB_CHILD + i]->heuristic))
		{
			max = heap[index * NB_CHILD + i]->heuristic;
			res = i;
		}
	}
	return (res);
}

int	queue_assert(t_board **heap, int heap_size)
{
	for (int i = 0; NB_CHILD * i + 1 < heap_size; i++)
	{
		for (int j = 1; j <= NB_CHILD; j++)
		{
//			printf("here\n");
			if ((i * NB_CHILD + j < heap_size) && heap[i] && heap[i * NB_CHILD + j] && heap[i]->heuristic < heap[i * NB_CHILD + j]->heuristic)
			{
				dprintf(2, "ti eblan\n");
				exit(EXIT_FAILURE);
			}
		}
	}
	return (EXIT_SUCCESS);
}

void	queue_print(t_board **heap, int heap_size)
{
	for (int k = 0; k < heap_size; k++)
	{
		printf("priority = %d\n", heap[k]->heuristic);
	}
}

void	queue_push(t_board **heap, t_board *new, int *heap_size)
{
	int		new_index;


	if (*heap_size == 0)
	{
		(*heap_size)++;
		heap[0] = new;
		return ;
	}
	new_index = *heap_size;
	heap[new_index] = new;
	(*heap_size)++;

	while (new_index > 0 && ((heap[(new_index - 1) / NB_CHILD])->heuristic < new->heuristic))
	{
		swap_nodes(&(heap[(new_index - 1) / NB_CHILD]), &(heap[new_index]));
		new_index = (new_index - 1) / NB_CHILD;
	}
	queue_assert(heap, *heap_size);
}

void	queue_pop(t_board **heap, int *heap_size)
{
	int		index;
	int		new_index;

	if (*heap_size == 0)
		return ;

	if (*heap_size == 1)
	{
		(*heap_size)--;
		heap[0] = NULL;
		return ;
	}

	index = 0;
	heap[0] = heap[*heap_size - 1];
	heap[*heap_size - 1] = 0;
	(*heap_size)--;
	while ((new_index = max_child(heap, *heap_size, index)) != -1)
	{
		if (heap[index]->heuristic > heap[new_index]->heuristic)
		{
			queue_assert(heap, *heap_size);
			return ;
		}

		swap_nodes(&heap[index], &heap[new_index]);
		index = new_index;
	}
	queue_assert(heap, *heap_size);
}

void	queue_update(t_board **heap, int *heap_size, int index)
{
	int		new_index;

	if (index >= *heap_size || *heap_size <= 1)
		return ;

	if (heap[(index - 1) / NB_CHILD]->heuristic < heap[index]->heuristic)
	{
		new_index = index;
		while (heap[(new_index - 1) / NB_CHILD]->heuristic < heap[index]->heuristic)
		{
			new_index = (new_index - 1) / NB_CHILD;
			swap_nodes(&heap[new_index], &heap[index]);
			index = new_index;
		}
	}
	else
	{
		while ((new_index = max_child(heap, *heap_size, index)) != -1)
		{
			if (heap[index]->heuristic > heap[new_index]->heuristic)
			{
				queue_assert(heap, *heap_size);
				return ;
			}
			swap_nodes(&heap[index], &heap[new_index]);
			index = new_index;
		}
	}
	queue_assert(heap, *heap_size);
}
