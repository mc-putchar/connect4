/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 22:08:26 by mcutura           #+#    #+#             */
/*   Updated: 2024/08/04 22:56:31 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "connect4.h"

int	determine_first_player(t_game *game)
{
	int const	coin = choose_turn();

	ft_printf("%s %s\n",COIN_FLIP, coin ? "HEADS" : "TAILS");
	ft_printf("%s\n", coin ? PLAY_FIRST : PLAY_SECOND);
	game->round = 1;
	game->player = coin ? FIRST : SECOND;
	game->bot = coin ? SECOND : FIRST;
	return (coin);
}

void	print_board(t_board *board)
{
	for (int i = 0; i < board->height; ++i)
	{
		ft_printf("|");
		for (int j = 0; j < board->width; ++j)
		{
			ft_printf("| %c |", board->map[i][j] ? board->map[i][j] : ' ');
		}
		ft_printf("|\n");
	}
	ft_printf("\n|");
	for (int i = 1; i <= board->width; ++i)
	{
		if (i < 10)
			ft_printf("| %d |", i);
		else
			ft_printf("| %d|", i);
	}
	ft_printf("|\n");
}

int	prompt_user_move(t_board *board, char player)
{
	int		move;
	char	*input;

	ft_printf(PROMPT);
	input = get_next_line(STDIN_FILENO);
	if (!input)
		return (1);
	move = ft_atoi(input);
	free(input);
	if (move < 1 || move > board->width || make_move(board, move - 1, player))
	{
		ft_printf(BADMOVE);
		return (1);
	}
	return (0);
}

void	display_gameover(t_board *board, int gameover, int player)
{
	if (board->width < PRINTABLE_SIZE)
		print_board(board);
	ft_printf(GAMEOVER_MSG);
	if (gameover < 0)
		ft_printf(DRAW_MSG);
	else if ((player && gameover == 1) || (!player && gameover == 2))
		ft_printf(WIN_MSG);
	else
		ft_printf(LOST_MSG);
}
