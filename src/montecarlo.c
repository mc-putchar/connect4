/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   montecarlo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:54:06 by mcutura           #+#    #+#             */
/*   Updated: 2024/08/04 22:40:49 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "connect4.h"

t_board	*select_node(t_board *node)
{
	return (node);
}

int	generate_random_state(t_board *board, t_board *new, char player)
{
	t_moves	*moves = get_moves(board);

	if (!moves)
		return (-1);
	new->width = board->width;
	new->height = board->height;
	if (!moves->size)
		return (free(moves), -1);
	int	next_move = rand() % moves->size;
	int res = new_state(board, new, moves->moves[next_move], player);
	free(moves->moves);
	free(moves);
	return (res);
}

static char	**new_map(int width, int height)
{
	char	**map = malloc(height * sizeof(char *));

	for (int i = 0; i < height; ++i)
	{
		map[i] = ft_calloc(width, sizeof(char));
	}
	return (map);
}

static void	copy_node(t_board *lhs, t_board *rhs)
{
	ft_memcpy(lhs, rhs, sizeof(t_board));
}

static void	update_heuristic(t_board *node, int parent_playouts)
{
	if (!node->playouts)
	{
		node->heuristic = MAX_NODE_NB;
		return ;
	}
	node->heuristic = (double)node->wins / node->playouts + sqroot(2 * ln(parent_playouts) / node->playouts);
}

void	simulate(t_board *node, t_game *game)
{
	t_board			old_state;
	t_board			new_state;
	char			player = (game->round + node->depth) & 1 ? FIRST : SECOND;
	int				ret;

	copy_node(&old_state, node);
	old_state.map = new_map(node->width, node->height);
	new_state.map = new_map(node->width, node->height);
	while ((ret = generate_random_state(&old_state, &new_state, player)) != 0)
	{
		player = player == FIRST ? SECOND : FIRST;
		copy_node(&old_state, &new_state);
	}
	node->playouts++;
	if ((game->bot == FIRST && ret == 1) || ret == 2)
		++node->wins;
	free_map(&old_state, node->height);
	free_map(&new_state, node->height);
}

void	backpropagate(t_board *curr_node, t_board *tree, t_board **queue, int *queue_size)
{
	int	new_index = curr_node->tree_idx;
	int				parity = 0;

	update_heuristic(curr_node, tree[(curr_node->tree_idx - 1) / NB_CHILD].playouts);
	queue_update(queue, queue_size, 0);
	while (new_index && (new_index = (new_index - 1) / NB_CHILD) >= 0)
	{
		parity = (parity + 1) & 1;
		tree[new_index].playouts++;
		tree[new_index].wins += !parity ? 1 : 0;
		update_heuristic(&tree[new_index], tree[(new_index - 1) / NB_CHILD].playouts);
		queue_update(queue, queue_size, tree[new_index].queue_idx);
	}
}

void	expand(t_board **queue, t_board *tree, int *queue_size, int *tree_size, t_game *game)
{
	t_board	new_states[NB_CHILD];
	char	player = (game->round + queue[0]->depth) & 1 ? FIRST : SECOND;

	if (is_gameover(queue[0]))
		return ;

	for (int i = 0; i < NB_CHILD; i++)
	{
		new_states[i].map = new_map(tree[0].width, tree[0].height);
		generate_random_state(queue[0], &new_states[i], player);//make sure theyre different
	}
	queue_pop(queue, queue_size);
	for (int i = 0; i < NB_CHILD; i++)
	{
		copy_node(&tree[*tree_size + i], &new_states[i]);
		tree[*tree_size + i].tree_idx = *tree_size + i;
		queue_push(queue, &tree[*tree_size + i], queue_size);
	}
	(*tree_size) += NB_CHILD;
}

int get_best_move(t_board *tree, int tree_size)
{
	int	max_heuristic = -1;
	int	max_index;
	
	for (int i = 1; i <= NB_CHILD; i++)
	{
		if (i < tree_size && max_heuristic < tree[i].heuristic)
		{
			max_index = i;
			max_heuristic = tree[i].heuristic;
		}
	}

	return (tree[max_index].move);
}

int	calculate_move(t_board *root, t_game *game)//assign_player
{
	time_t const	start_time = time(NULL);
	t_board			*tree = ft_calloc(MAX_NODE_NB, sizeof(t_board));
	t_board			**queue = ft_calloc(MAX_NODE_NB, sizeof(t_board *));
	int				queue_size = 0;
	int				tree_size = 0;

	copy_node(&tree[0], root);
	tree[0].heuristic = 0;
	tree[0].depth = 0;
	tree[0].tree_idx = 0;
	tree[0].queue_idx = 0;
	tree_size++;
	queue_push(queue, &tree[0], &queue_size);

	while ((time(NULL) - start_time < THINK_TIME))
	{
		while ((queue[0]->heuristic - MAX_NODE_NB) < 2 && (queue[0]->heuristic - MAX_NODE_NB) > -2)
		{
			simulate(queue[0], game);//todo: multiple simulations
			simulate(queue[0], game);
			simulate(queue[0], game);
			backpropagate(queue[0], tree, queue, &queue_size);
		}
		expand(queue, tree, &queue_size, &tree_size, game);
	}
	int	move = get_best_move(tree, tree_size);
	if (DEBUG)
		ft_printf("number of nodes %i\n", tree_size);
	free_maps(tree, tree_size);
	free(tree);
	free(queue);
	return (move);
}
