"""Illustration of a tic-tac-toe match.

    Authors:
        Fabiano Baroni <fabiano.baroni@uam.es>,
        Alejandro Bellogin <alejandro.bellogin@uam.es>
        Alberto Suárez <alberto.suarez@uam.es>
"""
from __future__ import annotations  # For Python 3.7


import numpy as np

from game import Player, TwoPlayerGameState, TwoPlayerMatch
from heuristic import heuristic
from strategy import (ManualStrategy, MinimaxAlphaBetaStrategy,
                      MinimaxStrategy, RandomStrategy)
from tictactoe import TicTacToe
player_manual = Player(
    name='Manual',
    strategy=ManualStrategy(verbose=0),
)

player_minimax3_1 = Player(
    name='IA 1 (minimax, 3)',
    strategy=MinimaxStrategy(
        heuristic=heuristic,
        max_depth_minimax=3,
        verbose=0,
    ),
    delay=0,
)

player_minimax3_2 = Player(
    name='IA 2 (minimax, 3)',
    strategy=MinimaxStrategy(
        heuristic=heuristic,
        max_depth_minimax=3,
        verbose=1,
    ),
    delay=0,
)

player_alphabeta = Player(
    name='IA 3 (alphabeta, 1)',
    strategy=MinimaxAlphaBetaStrategy(
        heuristic=heuristic,
        max_depth_minimax=3,
        verbose=1,
    ),
    delay=0,
)

player_random = Player(
    name='IA (minimax, 3)',
    strategy=RandomStrategy(),
    delay=0,
)

dim_board = 3

# Random vs minimax player
# player_a, player_b = player_random, player_minimax3_1

# Manual vs minimax player
player_a, player_b = player_manual, player_minimax3_1

# Minimax vs minimax with alpha beta pruning player
# player_a, player_b = player_minimax3_2, player_alphabeta

# Initialize a tic-tac-toe game.
game = TicTacToe(
    player1=player_a,
    player2=player_b,
    dim_board=dim_board,
)

"""
Here you can initialize board and player that moves first
to any valid state. E.g,, it can be an intermediate state.
"""
initial_board = np.zeros((dim_board, dim_board))
""" Modification of initial board.
initial_board[1, 1] = -1
initial_board[1, 2] = 1
initial_board[0, 0] = 1
"""
initial_player = player_a

# Initialize a game state.
game_state = TwoPlayerGameState(
    game=game,
    board=initial_board,
    initial_player=initial_player,
)

# Initialize a match.
match = TwoPlayerMatch(
    game_state,
    max_seconds_per_move=1000,
    n_moves_max=500,
    gui=True,
)

# Play a match.
scores = match.play_match()
input('Press any key to finish.')
