/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 22:02:18 by mcutura           #+#    #+#             */
/*   Updated: 2024/08/04 01:22:10 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGES_H
# define MESSAGES_H

# define USAGE "./connect4 [HEIGHT] [WIDTH] <optional flags>\n"
# define PROMPT "Input the column number for your next move: "
# define BADMOVE "Bad move. Try again!\n"
# define COIN_FLIP "Coin flip: "
# define PLAY_FIRST "You play the first move\n"
# define PLAY_SECOND "Opponent goes first\n"
# define GAMEOVER_MSG "GAME OVER!\n"
# define DRAW_MSG "DRAW!\n"
# define WIN_MSG "You WON the game!\n"
# define LOST_MSG "You LOST the game!\n"
# define ERR_PARAMS "Error: Invalid parameters.\nHeight >= 6\nWidth >= 7\n"
# define ERR_BADARG "Error: Invalid argument\n"
# define ERR_MALLOC "Error: failed memory allocation\n"

#endif
