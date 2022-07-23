"""Implementation of Reversi.

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


class Reversi(TwoPlayerGame):
    """Specific definitions for Reversi."""

    def __init__(
        self,
        player1: Player,
        player2: Player,
        height: int,
        width: int,
    ) -> None:
        super().__init__(
            "Reversi",
            player1,
            player2,
        )
        self.player1.label = 'B'
        self.player2.label = 'W'
        self.height = height
        self.width = width
        self.max_score = height*width
        self.min_score = - self.max_score

    # Private functions
    def _capture_enemy_in_dir(self, board: dict, move, player_label: Any, delta_x_y) -> list:
        enemy = self.player2.label if player_label == self.player1.label else self.player1.label
        (delta_x, delta_y) = delta_x_y
        x, y = move
        x, y = x + delta_x, y + delta_y
        enemy_list_0 = []
        while board.get((x, y)) == enemy:
            enemy_list_0.append((x, y))
            x, y = x + delta_x, y + delta_y
        if board.get((x, y)) != player_label:
            del enemy_list_0[:]
        x, y = move
        x, y = x - delta_x, y - delta_y
        enemy_list_1 = []
        while board.get((x, y)) == enemy:
            enemy_list_1.append((x, y))
            x, y = x - delta_x, y - delta_y
        if board.get((x, y)) != player_label:
            del enemy_list_1[:]
        return enemy_list_0 + enemy_list_1

    def _enemy_captured_by_move(self, board: dict, move, player_label: Any) -> list:
        return self._capture_enemy_in_dir(board, move, player_label, (0, 1)) \
               + self._capture_enemy_in_dir(board, move, player_label, (1, 0)) \
               + self._capture_enemy_in_dir(board, move, player_label, (1, -1)) \
               + self._capture_enemy_in_dir(board, move, player_label, (1, 1))

    def _get_valid_moves(self, board: dict, player_label: Any) -> list:
        """Returns a list of valid moves for the player judging from the board."""
        return [(x, y) for x in range(1, self.width + 1)
                for y in range(1, self.height + 1)
                if (x, y) not in board.keys() and
                self._enemy_captured_by_move(board, (x, y), player_label)]

    def _player_coins(self, board: dict, player_label: Any) -> float:
        return sum(x == player_label for x in board.values())

    def _coin_diff(self, board: dict) -> float:
        """Difference in the number of coins."""
        return 100 * (self._player_coins(board, self.player2.label) - self._player_coins(board, self.player1.label)) / len(board)

    def _choice_diff(self, board: dict) -> float:
        """Difference in the number of choices available."""
        black_moves_num = len(self._get_valid_moves(board, self.player1.label))
        white_moves_num = len(self._get_valid_moves(board, self.player2.label))
        if (black_moves_num + white_moves_num) != 0:
            return 100 * (black_moves_num - white_moves_num) / (black_moves_num + white_moves_num)
        else:
            return 0

    def _corner_diff(self, board: dict) -> float:
        """Difference in the number of corners captured."""
        corner = [board.get((1, 1)), board.get((1, self.height)), board.get((self.width, 1)),
                  board.get((self.width, self.height))]
        black_corner = corner.count(self.player1.label)
        white_corner = corner.count(self.player2.label)
        if (black_corner + white_corner) != 0:
            return 100 * (black_corner - white_corner) / (black_corner + white_corner)
        else:
            return 0

    def _compute_utility(self, board: dict, player_label: Any) -> float:
        if len(self._get_valid_moves(board, player_label)) == 0:
            return +100 if player_label == self.player2.label else -100
        else:
            return 0.4 * self._coin_diff(board) + 0.3 * self._choice_diff(board) + 0.3 * self._corner_diff(board)

    def _utility(self, board: dict, player_label: Any) -> float:
        utility = self._compute_utility(board, player_label)
        return utility if player_label == self.player2.label else - utility

        # end

    # Public methods

    def initialize_board(self) -> dict:
        """Initialize board with standard configuration."""
        initial_x = self.width // 2
        initial_y = self.height // 2
        init_white_pos = [(initial_x, initial_y), (initial_x+1, initial_y+1)]
        init_black_pos = [(initial_x, initial_y+1), (initial_x+1, initial_y)]
        init_white_board = dict.fromkeys(init_white_pos, self.player2.label)
        init_black_board = dict.fromkeys(init_black_pos, self.player1.label)
        board = {**init_white_board, **init_black_board}
        return board

    def display(self, state: TwoPlayerGameState, gui: bool = False) -> None:
        """Display state of the board."""
        super().display(state, gui)
        board = state.board
        moves = self._get_valid_moves(board, state.next_player.label)

        # Console display

        print('coins: %s=%d <-> %s=%d' % (self.player1.label, self._player_coins(board, self.player1.label),
                                        self.player2.label, self._player_coins(board, self.player2.label)))
        for y in range(0, self.height + 1):
            for x in range(0, self.width + 1):
                if x > 0 and y > 0:
                    if (x, y) in moves:
                        print(board.get((x, y), '_',), end=' ')
                    else:
                        print(board.get((x, y), '.',), end=' ')
                if x == 0:
                    if y > 0:
                        print(y, end=' ')
                if y == 0:
                    print(chr(x+96), end=' ') if x > 0 else print(' ', end=' ')
            print()
        print()

        # GUI display
        if gui:
            moves = [
                self._matrix_to_display_coordinates(move) for move in moves
            ]
            gui_root = state.gui_thread.gui_root
            gui_buttons = state.gui_thread.gui_buttons
            state.game.gui_update(state=state, gui_buttons=gui_buttons, gui_root=gui_root, moves=moves, click_function=None)


    def  _matrix_to_display_coordinates(
        self,
        move: Tuple
    ) -> str:
        return '({}, {})'.format(move[1], chr(ord('a') - 1 + move[0]))

    def generate_successors(
        self,
        state: TwoPlayerGameState,
    ) -> List[TwoPlayerGameState]:
        """Generate the list of successors of a game state."""
        successors = []
        board = state.board
        moves = self._get_valid_moves(board, state.next_player.label)

        for move in moves:
            board_successor = copy.deepcopy(state.board)
            assert isinstance(state.next_player, Player)
            # show the move on the board
            board_successor[move] = state.next_player.label
            # flip enemy
            for enemy in self._enemy_captured_by_move(board, move, state.next_player.label):
                board_successor[enemy] = state.next_player.label
            move_code = self._matrix_to_display_coordinates(move)
            successor = state.generate_successor(
                board_successor,
                move_code,
            )

            successors.append(successor)

        if not successors:
            board_successor = copy.deepcopy(state.board)
            move_code = None
            no_movement = state.generate_successor(
                board_successor,
                move_code,
            )
            successors = [ no_movement ]

        return successors

    def score(
        self,
        state: TwoPlayerGameState,
    ) -> Tuple[bool, Optional[np.ndarray]]:
        """Determine whether a game state is terminal."""
        board = state.board
        moves = self._get_valid_moves(board, state.next_player.label)

        end_of_game = (len(
            self._get_valid_moves(board, self.player1.label) +
            self._get_valid_moves(board, self.player2.label)
            ) == 0)

        scores = np.zeros(self.n_players, dtype=float)
        players = (self.player1, self.player2)
        for i in range(len(players)):
            scores[i] = self._player_coins(board, players[i].label)

        return end_of_game, scores

    def initialize_buttons(self, board: Any, gui_frame: Frame) -> dict:
        assert (board is not None)
        assert (gui_frame is not None)
        gui_buttons = {}
        # Put buttons and labels the first time this is called
        for row in range(0, self.height + 1):
            for col in range(0, self.width + 1):
                piece = Label(gui_frame)  # Dummy piece
                if col > 0 and row > 0:  # Actual buttons
                    if (col, row) in board:  # Black and white
                        piece = Button(gui_frame, bg="black" if board.get(
                            (col, row)) == self.player1.label else 'white', state=DISABLED)
                    else:  # Background
                        piece = Button(gui_frame, bg="green", state=DISABLED)
                    gui_buttons[(col, row)] = piece  # Record button
                if col == 0 and row > 0:  # Vertical number axis
                    piece = Label(gui_frame, text=str(row))
                if row == 0 and col > 0:  # Horizontal letter axis
                    piece = Label(gui_frame, text=chr(col+96))
                # Place piece
                piece.grid(row=row, column=col)
        return gui_buttons

    def gui_update(self, state: TwoPlayerGameState, gui_buttons: dict, gui_root: Tk, moves: list = [], click_function: Callable[[Any], None] = None) -> None:
        assert (gui_buttons is not None)
        assert (gui_root is not None)
        board = state.board
        for row in range(1, self.height + 1):
            for col in range(1, self.width + 1):
                pos = (col, row)
                move_code = self._matrix_to_display_coordinates(pos)
                if pos in board:  # Black and white
                    color = board.get(pos)
                    gui_buttons[pos].configure(
                        bg="black" if color == self.player1.label else "white", state=DISABLED)
                elif move_code in moves:  # Valid moves
                    gui_buttons[pos].configure(
                        bg="blue" if state.next_player.label == self.player1.label else "red", state=NORMAL)
                    if click_function:
                        gui_buttons[pos].bind(
                            "<Button-1>",
                            lambda event, move=move_code: click_function(move),
                        )
                else:  # Background
                    gui_buttons[pos].configure(bg="green", state=DISABLED)
        gui_root.update()  # Refresh UI


def from_array_to_dictionary_board(board_array):
    """Create a state from an initial board."""
    if board_array is None:
        return None

    n_rows = len(board_array)
    n_columns = len(board_array[0])
    try:
        board_dictionary = dict(
            [((j + 1, i + 1), board_array[i][j])
            for i in range(n_rows) for j in range(n_columns)
            if board_array[i][j] != '.']
        )
    except IndexError:
        raise IndexError('Wrong configuration of the board')
    else:
        return board_dictionary


def from_dictionary_to_array_board(board_dictionary, height, width):
    """From dictionary to array representation."""
    board_array = []

    for i in range(height):
        board_array.append('')
        for j in range(width):
            key =  (j + 1, i + 1)
            if key in board_dictionary:
                board_array[i] += board_dictionary[key]
            else:
                board_array[i] += '.'

    return board_array
