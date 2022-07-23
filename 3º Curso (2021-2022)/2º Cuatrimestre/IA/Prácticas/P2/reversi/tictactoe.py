"""Implementatio of tic-tac-toe.

    Authors:
        Fabiano Baroni <fabiano.baroni@uam.es>,
        Alejandro Bellogin <alejandro.bellogin@uam.es>
        Alberto Suárez <alberto.suarez@uam.es>
"""

from __future__ import annotations  # For Python 3.7


import copy
from tkinter import *
from tkinter import messagebox
from typing import Any, Callable, List, Optional, Tuple

import numpy as np

from game import Player, TwoPlayerGame, TwoPlayerGameState


class TicTacToe(TwoPlayerGame):
    """Specific definitions for Tic-Tac-Toe."""

    def __init__(
        self,
        player1: Player,
        player2: Player,
        dim_board: int,
    ) -> None:
        super().__init__(
            "Tictactoe",
            player1,
            player2,
        )
        self.player1.label = 1
        self.player2.label = -1
        self.dim_board = dim_board
        self.max_score = 1
        self.min_score = -1

    # Private functions
    def _determine_player_label_complete_line(
        self,
        lines: List[np.ndarray],
    ) -> Optional[int]:

        player_label_complete_line = 0
        i = 0
        while (i < len(lines)) and (player_label_complete_line == 0):
            line = lines[i]
            i += 1
            unique_elements = np.unique(line)

            if (len(unique_elements) == 1) and (unique_elements[0] != 0):
                player_label_complete_line = unique_elements[0]
            else:
                player_label_complete_line = 0

        return player_label_complete_line

    def _player_label_to_index(self, label: int) -> int:
        return (1 - label) // 2

    # Public methods

    def initialize_board(self) -> np.ndarray:
        """Initialize board with standard configuration."""
        return np.zeros((self.dim_board, self.dim_board))


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
        successors = []

        n_rows, n_columns = np.shape(state.board)
        for i in range(n_rows):
            for j in range(n_columns):
                if (state.board[i, j] == 0):
                    # Prevent modification of the board
                    board_successor = copy.deepcopy(state.board)
                    assert isinstance(state.next_player, Player)
                    board_successor[i, j] = state.next_player.label
                    move_code = self._matrix_to_display_coordinates(i, j)
                    successor = state.generate_successor(
                        board_successor,
                        move_code,
                    )

                    successors.append(successor)

        return successors

    def _matrix_to_display_coordinates(
        self,
        i: int,
        j: int,
    ) -> str:
        return '({}, {})'.format(chr(ord('a') + i), j + 1)

    def score(
        self,
        state: TwoPlayerGameState,
    ) -> Tuple[bool, Optional[np.ndarray]]:
        """Determine whether a game state is terminal."""
        board = state.board
        diagonal = np.diagonal(board)
        reverse_diagonal = np.diagonal(np.fliplr(board))

        lines = [diagonal, reverse_diagonal]

        n_rows, n_columns = np.shape(board)

        for i in range(n_rows):
            lines.append(board[i, :])
        for j in range(n_columns):
            lines.append(board[:, j])

        player_label_complete_line = (
            self._determine_player_label_complete_line(lines)
        )

        end_of_game = (
            (player_label_complete_line != 0)  # player has completed a line
            or np.all(board != 0)  # Board is full
        )

        scores = np.zeros(self.n_players, dtype=float)
        players = (self.player1, self.player2)
        for player in players:
            if player_label_complete_line == player.label:
                scores[self._player_label_to_index(player.label)] = 1

        return end_of_game, scores

    def initialize_buttons(self, board: Any, gui_frame) -> Any:
        gui_buttons = {}
        # Put buttons and labels the first time this is called
        for row in range(-1, self.dim_board):
            for col in range(-1, self.dim_board):
                piece = Label(gui_frame)  # Dummy piece
                if col > -1 and row > -1:  # Actual buttons
                    color = ""
                    status = DISABLED
                    if board[row, col] == self.player1.label:
                        color = "white"
                    elif board[row, col] == self.player2.label:
                        color = "black"
                    else:
                        color = "green"
                        status = NORMAL
                    piece = Button(gui_frame, bg=color, state=status)
                    gui_buttons[(row, col)] = piece  # Record button
                if col == -1 and row > -1:  # Vertical number axis
                    row_label = chr(ord('a') + row)
                    piece = Label(gui_frame, text=row_label)
                if row == -1 and col > -1:  # Horizontal number axis
                    col_label = col + 1
                    piece = Label(gui_frame, text=col_label)
                # Place piece
                piece.grid(row=row+1, column=col+1)
        return gui_buttons

    def gui_update(self, state: TwoPlayerGameState, gui_buttons, gui_root, moves: list = [], click_function = None) -> None:
        board = state.board
        for row in range(0, self.dim_board):
            for col in range(0, self.dim_board):
                pos = (row, col)
                move_code = self._matrix_to_display_coordinates(row, col)
                if move_code in moves:  # Valid moves
                    gui_buttons[pos].configure(
                        bg="blue" if state.next_player.label == self.player1.label else "red", state=NORMAL)
                    if click_function:
                        gui_buttons[pos].bind(
                            "<Button-1>",
                            lambda event, move=move_code: click_function(move),
                        )
                else:  # Black and white
                    if board[pos] == self.player1.label:
                        color = "white"
                    elif board[pos] == self.player2.label:
                        color = "black"
                    else:
                        color = "green"
                    gui_buttons[pos].configure(bg=color, state=DISABLED)
        gui_root.update()  # Refresh UI
