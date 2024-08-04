/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 22:02:18 by mcutura           #+#    #+#             */
/*   Updated: 2024/08/04 22:55:15 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGES_H
# define MESSAGES_H

# define USAGE "./connect4 [HEIGHT] [WIDTH] <optional flags>\n"
# define PROMPT "Input the column number for your next move: "
# define BADMOVE "Bad move. Try again!\n"
# define BOARD_TOO_LARGE "Board size too large. Will not be printed.\n"
# define COIN_FLIP "Coin flip: "
# define PLAY_FIRST "You play the first move\n"
# define PLAY_SECOND "Opponent goes first\n"
# define THINKING "Opponent is thinking...\n"
# define OPPONENT_MOVE "Opponent played: "
# define GAMEOVER_MSG "GAME OVER!\n"
# define DRAW_MSG "DRAW!\n"
# define WIN_MSG "You WON the game!\n"
# define LOST_MSG "You LOST the game!\n"
# define ERR_PARAMS "Error: Invalid parameters.\nHeight between 6 and 42\nWidth between 7 and 42\n"
# define ERR_BADARG "Error: Invalid argument\n"
# define ERR_MALLOC "Error: failed memory allocation\n"

#endif
