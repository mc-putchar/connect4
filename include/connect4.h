/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect4.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:51:11 by mcutura           #+#    #+#             */
/*   Updated: 2024/08/04 01:07:32 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNECT4_H
# define CONNECT4_H

# include <stdlib.h>
# include <time.h>

# include "messages.h"

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

// init
int		init_game(t_board *board, char *av1, char *av2);
int		choose_turn(void);

// board_ops
int		update_heuristic(t_board *new);
int		new_state(t_board *old, t_board *new, int col_nb, char player);

// game_state
int		is_gameover(t_board *board);
int		make_move(t_board *board, int move, char player);
void	game_loop(t_board *board);

// display
void	print_board(t_board *board);
int		prompt_user_move(t_board *board, char player);
void	display_gameover(t_board *board, int gameover, int player);
int		determine_first_player(void);

// utils
int		max(int a, int b);

#endif
