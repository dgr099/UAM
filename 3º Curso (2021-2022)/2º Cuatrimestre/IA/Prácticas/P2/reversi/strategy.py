"""Strategies for two player games.

   Authors:
        Fabiano Baroni <fabiano.baroni@uam.es>,
        Alejandro Bellogin Kouki <alejandro.bellogin@uam.es>
        Alberto Suárez <alberto.suarez@uam.es>
"""

from __future__ import annotations  # For Python 3.7


from abc import ABC, abstractmethod
from cmath import inf
from typing import List

import numpy as np

from game import TwoPlayerGame, TwoPlayerGameState
from heuristic import Heuristic


class Strategy(ABC):
    """Abstract base class for player's strategy."""

    def __init__(self, verbose: int = 0) -> None:
        """Initialize common attributes for all derived classes."""
        self.verbose = verbose

    @abstractmethod
    def next_move(
        self,
        state: TwoPlayerGameState,
        gui: bool = False,
    ) -> TwoPlayerGameState:
        """Compute next move."""

    def generate_successors(
        self,
        state: TwoPlayerGameState,
    ) -> List[TwoPlayerGameState]:
        """Generate state successors."""
        assert isinstance(state.game, TwoPlayerGame)
        successors = state.game.generate_successors(state)
        assert successors  # Error if list is empty
        return successors


class RandomStrategy(Strategy):
    """Strategy in which moves are selected uniformly at random."""

    def next_move(
        self,
        state: TwoPlayerGameState,
        gui: bool = False,
    ) -> TwoPlayerGameState:
        """Compute next move."""
        successors = self.generate_successors(state)
        return np.random.choice(successors)


class ManualStrategy(Strategy):
    """Strategy in which the player inputs a move."""

    def next_move(
        self,
        state: TwoPlayerGameState,
        gui: bool = False,
    ) -> TwoPlayerGameState:
        """Compute next move"""
        successors = self.generate_successors(state)

        assert isinstance(state.game, TwoPlayerGame)
        if gui:
            index_successor = state.game.graphical_input(state, successors)
        else:
            index_successor = state.game.manual_input(successors)

        next_state = successors[index_successor]

        if self.verbose > 0:
            print('My move is: {:s}'.format(str(next_state.move_code)))

        return next_state


class MinimaxStrategy(Strategy):
    """Minimax strategy."""

    def __init__(
        self,
        heuristic: Heuristic,
        max_depth_minimax: int,
        verbose: int = 0,
    ) -> None:
        super().__init__(verbose)
        self.heuristic = heuristic
        self.max_depth_minimax = max_depth_minimax

        self.explored_nodes = 0

    def next_move(
        self,
        state: TwoPlayerGameState,
        gui: bool = False,
    ) -> TwoPlayerGameState:
        """Compute the next state in the game."""

        minimax_value, minimax_successor = self._max_value(
            state,
            self.max_depth_minimax,
        )

        if self.verbose > 0:
            if self.verbose > 1:
                print('\nGame state before move:\n')
                print(state.board)
                print()
            print('Minimax value = {:.2g}'.format(minimax_value))

        if minimax_successor:
            minimax_successor.minimax_value = minimax_value

        return minimax_successor

    def _min_value(
        self,
        state: TwoPlayerGameState,
        depth: int,
    ) -> float:
        """Min step of the minimax algorithm."""

        self.explored_nodes += 1

        if state.end_of_game or depth == 0:
            minimax_value = self.heuristic.evaluate(state)
            minimax_successor = None
        else:
            minimax_value = np.inf

            for successor in self.generate_successors(state):
                if self.verbose > 1:
                    print('{}: {}'.format(state.board, minimax_value))

                successor_minimax_value, _ = self._max_value(
                    successor,
                    depth - 1,
                )

                if (successor_minimax_value < minimax_value):
                    minimax_value = successor_minimax_value
                    minimax_successor = successor

        if self.verbose > 1:
            print('{}: {}'.format(state.board, minimax_value))

        return minimax_value, minimax_successor

    def _max_value(
        self,
        state: TwoPlayerGameState,
        depth: int,
    ) -> float:
        """Max step of the minimax algorithm."""

        self.explored_nodes += 1

        if state.end_of_game or depth == 0:
            minimax_value = self.heuristic.evaluate(state)
            minimax_successor = None
        else:
            minimax_value = -np.inf

            for successor in self.generate_successors(state):
                if self.verbose > 1:
                    print('{}: {}'.format(state.board, minimax_value))

                successor_minimax_value, _ = self._min_value(
                    successor,
                    depth - 1,
                )
                if (successor_minimax_value > minimax_value):
                    minimax_value = successor_minimax_value
                    minimax_successor = successor

        if self.verbose > 1:
            print('{}: {}'.format(state.board, minimax_value))

        return minimax_value, minimax_successor

    def get_explored_nodes(self) -> int:
        return self.explored_nodes

    def set_explored_nodes(self, num_nodes):
        self.explored_nodes = num_nodes


class MinimaxAlphaBetaStrategy(Strategy):
    """Minimax alpha-beta strategy."""

    def __init__(
        self,
        heuristic: Heuristic,
        max_depth_minimax: int,
        verbose: int = 0,
    ) -> None:
        super().__init__(verbose)
        self.heuristic = heuristic
        self.max_depth_minimax = max_depth_minimax
        
        self.explored_nodes = 0

    def next_move(
        self,
        state: TwoPlayerGameState,
        gui: bool = False,
    ) -> TwoPlayerGameState:
        """Compute the next state in the game."""

        minimax_value, minimax_successor = self.max_value(
            state,
            -np.inf,
            np.inf,
            self.max_depth_minimax,
        )

        """
        # Use this code snippet to trace the execution of the algorithm
        if self.verbose > 1:
            print('{}: [{:.2g}, {:.2g}]'.format(
                    state.board,
                    alpha,
                    beta,
                )
            )
        """

        if minimax_successor:
            minimax_successor.minimax_value = minimax_value

        return minimax_successor

    def max_value(self, state: TwoPlayerGame, alpha, beta, depth) -> float:
        
        self.explored_nodes += 1

        max_successor = None

        if state.end_of_game or depth == 0:
            return self.heuristic.evaluate(state), max_successor

        for successor in self.generate_successors(state):
            if self.verbose > 1:
                print('{}: [{:.2g}, {:.2g}]'.format(
                        state.board,
                        alpha,
                        beta,
                    )
                )
            aux_alpha, _ = self.min_value(successor, alpha, beta, depth-1)
            if aux_alpha >= beta:
                return aux_alpha, successor
            if alpha < aux_alpha:
                alpha = aux_alpha
                max_successor = successor

        return alpha, max_successor


    def min_value(self, state: TwoPlayerGame, alpha, beta, depth) -> int:
        
        self.explored_nodes += 1

        min_successor = None

        if state.end_of_game or depth == 0:
            return self.heuristic.evaluate(state), min_successor

        for successor in self.generate_successors(state):
            if self.verbose > 1:
                print('{}: [{:.2g}, {:.2g}]'.format(
                        state.board,
                        alpha,
                        beta,
                    )
                )
            aux_beta, _ = self.max_value(successor, alpha, beta, depth-1)
            if aux_beta <= alpha:
                return aux_beta, successor
            if beta > aux_beta:
                beta = aux_beta
                min_successor = successor

        return beta, min_successor

    def get_explored_nodes(self) -> int:
        return self.explored_nodes

    def set_explored_nodes(self, num_nodes):
        self.explored_nodes = num_nodes