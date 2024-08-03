/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_state.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 23:06:03 by mcutura           #+#    #+#             */
/*   Updated: 2024/08/04 01:11:39 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "connect4.h"

int	is_gameover(t_board *board)
{
	const int	h = board->height;
	const int	w = board->width;
	int 		counter;
	char		token;

	for (int i = 0; i < h; ++i)
	{
		counter = 0;
		token = 0;
		for (int j = 0; j < w; ++j)
		{
			if (board->map[i][j] != token)
			{
				token = board->map[i][j];
				counter = 1;
			} else if (token)
			{
				if (++counter == 4)
					return (1 + (token == SECOND));
			}
		}
	}
	for (int i = 0; i < w; ++i)
	{
		counter = 0;
		token = 0;
		for (int j = h - 1; j >= 0; --j)
		{
			if (board->map[j][i] != token)
			{
				token = board->map[j][i];
				counter = 1;
			} else if (token)
			{
				if (++counter == 4)
					return (1 + (token == SECOND));
			}
		}
	}
	for (int i = 3; i < w; ++i)
	{
		counter = 0;
		token = 0;
		for (int j = 0; j < h && i - j >= 0; ++j)
		{
			if (board->map[j][i - j] != token)
			{
				token = board->map[j][i - j];
				counter = 1;
			} else if (token)
			{
				if (++counter == 4)
					return (1 + (token == SECOND));
			}
		}
	}
	for (int i = w - 4; i >= 0; --i)
	{
		counter = 0;
		token = 0;
		for (int j = 0; j < h && i + j < w; ++j)
		{
			if (board->map[j][i + j] != token)
			{
				token = board->map[j][i + j];
				counter = 1;
			} else if (token)
			{
				if (++counter == 4)
					return (1 + (token == SECOND));
			}
		}
	}
	for (int i = 0; i < w; ++i)
	{
		if (!board->map[0][i])
			return (0);
	}
	return (-1);
}

int	make_move(t_board *board, int move, char player)
{
	int	i;

	if (!board->map[0][move])
	{
		i = 1;
		while (i < board->height && !board->map[i][move])
			++i;
		board->map[i - 1][move] = player;
		return (0);
	}
	return (1);
}

void	game_loop(t_board *board)
{
	int const	player_first = determine_first_player();
	int			gameover = 0;
	int			round = 1;

	while (!(gameover = is_gameover(board)))
	{
		print_board(board);
		if ((round & 1) == player_first)
		{
			while (prompt_user_move(board, (round & 1) ? FIRST : SECOND))
				;
		} else {
			; // TODO: bot move
		}
		++round;
	}
	display_gameover(board, gameover, player_first);
}
