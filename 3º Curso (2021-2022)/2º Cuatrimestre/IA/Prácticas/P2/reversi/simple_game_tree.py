"""Play a simple game defined by a game tree.

   Author:
        Alberto Suárez <alberto.suarez@uam.es>
"""
from __future__ import annotations  # For Python 3.7


from typing import Any, List, Optional, Tuple

import numpy as np

from game import Player, TwoPlayerGame, TwoPlayerGameState


class SimpleGame(TwoPlayerGame):
    """Abstract class for a two player game."""

    def __init__(
        self,
        player1: Player,
        player2: Player,
    ) -> None:
        super().__init__("SimpleGameTree", player1, player2)
        """self._successor_lists = {
            'A': ['B', 'C', 'D'],
            'B': ['E', 'F'],
            'C': ['G', 'H'],
            'D': ['I', 'J'],
            'G': ['K', 'L'],
            'J': ['M','N','O','P']
        }
        self._terminal_state_scores = {
            'E': [4, 0],
            'F': [3, 0],
            'H': [5, 0],
            'I': [5, 0],
            'K': [2, 0],
            'L': [1, 0],
            'M': [4, 0],
            'N': [2, 0],
            'O': [6, 0],
            'P': [1, 0],
        }
        """
        self._successor_lists = {
            'A': ['B', 'C'],
            'B': ['D', 'E', 'F', 'G'],
            'C': ['H', 'I', 'J', 'K'],
            'H': ['L', 'M'],
            'I': ['N', 'O', 'P'],
            'J': ['Q', 'R', 'S'],
            'K': ['T', 'U', 'V'],
        }
        self._terminal_state_scores = {
            'D': [8, 0],
            'E': [6, 0],
            'F': [7, 0],
            'G': [5, 0],
            'L': [9, 0],
            'M': [2, 0],
            'N': [8, 0],
            'O': [10, 0],
            'P': [2, 0],
            'Q': [3, 0],
            'R': [2, 0],
            'S': [4, 0],
            'T': [0, 0],
            'U': [5, 0],
            'V': [6, 0],
        }
        self.player1.label = 'Player 1'
        self.player2.label = 'Player 2'


    def initialize_board(self) -> str:
        """Initialize board with standard configuration."""
        return 'A'

    def display(self, state: TwoPlayerGameState, gui: bool = False) -> None:
        """Display the game state."""
        super().display(state, gui)
        print(state.board)
        print()

    def generate_successors(
        self,
        state: TwoPlayerGameState,
    ) -> List[TwoPlayerGameState]:
        """Generate the list of successors of a game state."""
        super().generate_successors(state)
        successors = []
        if state.board in self._successor_lists:
            successor_list = self._successor_lists.get(state.board)
            assert isinstance(successor_list, List)
            for board_successor in successor_list:
                move_code = state.board + board_successor
                successor = state.generate_successor(
                    board_successor=board_successor,
                    move_code=move_code,
                )
                successors.append(successor)
        return successors

    def score(
        self,
        state: TwoPlayerGameState,
    ) -> Tuple[bool, Optional[np.ndarray]]:
        """Determine scores."""
        end_of_game = state.board in self._terminal_state_scores

        if end_of_game:
            scores = self._terminal_state_scores.get(state.board)
        else:
            scores = None

        return end_of_game, scores

    def initialize_buttons(self, board: Any, gui_frame) -> Any:
        raise Exception("This method is not implemented (yet)")

    def gui_update(self, state: TwoPlayerGameState, gui_buttons, gui_root, moves: list = [], click_function = None) -> None:
        raise Exception("This method is not implemented (yet)")
