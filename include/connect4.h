/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect4.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:51:11 by mcutura           #+#    #+#             */
/*   Updated: 2024/08/04 22:56:24 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNECT4_H
# define CONNECT4_H

# include <stdint.h>
# include <stdlib.h>
# include <time.h>

# include "libft.h"
# include "messages.h"

# ifndef DEBUG
#  define DEBUG 0
# endif

# define NB_CHILD 7
# define NB_CHILD_QUEUE 2
# define FIRST 'X'
# define SECOND 'O'
# define MAX_NODE_NB 100000
# define THINK_TIME 5

# define MAX_SIZE 42
# define PRINTABLE_SIZE 21

typedef struct s_moves
{
	size_t	size;
	int		*moves;
}	t_moves;

typedef struct s_board
{
	char	**map;
	char	height;
	char	width;
	char	is_player;
	int		move;
	double	heuristic;
	int		wins;
	int		playouts;
	int		queue_idx;
	int		tree_idx;
	int		depth;
}	t_board;

typedef struct s_game
{
	char	player;
	char	bot;
	int		round;
}	t_game;

// init
int		init_game(t_board *board, char *av1, char *av2);
int		choose_turn(void);

// board_ops
// int		update_heuristic(t_board *new);
int		new_state(t_board *old, t_board *new, int col_nb, char player);
t_moves	*get_moves(t_board *board);

// game_state
int		is_gameover(t_board *board);
int		make_move(t_board *board, int move, char player);
void	game_loop(t_board *board);

// display
void	print_board(t_board *board);
int		prompt_user_move(t_board *board, char player);
void	display_gameover(t_board *board, int gameover, int player);
int	determine_first_player(t_game *game);

// utils
int		max(int a, int b);
void	free_map(t_board *node, int height);
void	free_maps(t_board *tree, int tree_size);
float	ln(int y);
double	sqroot(double n);

//queue.c
int		max_child(t_board **heap, int heap_size, int index);
void	queue_print(t_board **heap, int heap_size);
void	queue_push(t_board **heap, t_board *new, int *heap_size);
void	queue_pop(t_board **heap, int *heap_size);
void	queue_update(t_board **heap, int *heap_size, int index);
int		queue_assert(t_board **heap, int heap_size, char *operation);

// montecarlo
int		calculate_move(t_board *root, t_game *game);

#endif
