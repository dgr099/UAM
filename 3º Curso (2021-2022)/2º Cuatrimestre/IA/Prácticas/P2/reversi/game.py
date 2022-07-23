"""Infrastructure for two-player games.

    Authors:
        Fabiano Baroni <fabiano.baroni@uam.es>,
        Alejandro Bellogin Kouki <alejandro.bellogin@uam.es>
        Alberto Suárez <alberto.suarez@uam.es>
"""

from __future__ import annotations  # For Python 3.7

import copy
import time
from abc import ABC, abstractmethod
from tkinter import Frame, Tk, messagebox
from typing import Any, Callable, List, Optional, Sequence, Tuple

import numpy as np

"""
# Skipped to avoid circular import
from strategy import (
    Strategy,
)
"""

import _thread
import threading
from contextlib import contextmanager


class Player(object):
    """Player properties."""

    def __init__(
        self,
        name: str,
        strategy: "Strategy",
        delay : int = 0,
    ) -> None:
        self.label: Any = None
        self.name = name
        self.strategy = strategy
        self.delay = delay

    def move(
        self,
        state: TwoPlayerGameState,
        gui: bool = False,
    ) -> TwoPlayerGameState:
        """Player's move."""
        if self.delay > 0:
            time.sleep(self.delay)
        return self.strategy.next_move(state, gui)


class TwoPlayerGameState(object):
    """State of a two-player game."""

    def __init__(
        self,
        game: Optional[TwoPlayerGame] = None,
        initial_player: Optional[Player] = None,
        player_max: Optional[Player] = None,
        board: Any = None,
        move_code: Any = None,
        parent: Optional[TwoPlayerGameState] = None,
    ) -> None:
        self.game = game
        self.player_max = player_max
        self.next_player = initial_player
        self.end_of_game: Optional[bool] = None
        self.scores: Optional[np.ndarray] = None
        self.board = board
        self.move_code = move_code
        self.parent = parent
        # variables for GUI:
        self.gui_root = None
        self.gui_frame = None
        self.gui_buttons = None
        self.gui_thread = None

    @property
    def previous_player(self) -> Player:
        if self.parent:
            return self.parent.next_player

    @property
    def player1(self) -> Player:
        """Player 1 in the game"""
        assert isinstance(self.game, TwoPlayerGame)
        return self.game.player1

    @property
    def player2(self) -> Player:
        """Player 2 in the game."""
        assert isinstance(self.game, TwoPlayerGame)
        return self.game.player2

    def setup_match(self, gui: bool = False) -> TwoPlayerGameState:
        """Set game state up for match."""

        self.player_max = self.next_player

        assert isinstance(self.game, TwoPlayerGame)
        if self.board is None:
            self.board = self.game.initialize_board()
        if gui:
            class GuiThread(threading.Thread):
                def __init__(self, game: TwoPlayerGame, board: Any):
                    threading.Thread.__init__(self)
                    self.game = game
                    self.board = board
                    self.gui_root = None
                    self.gui_frame = None
                    self.gui_buttons = None
                    self.setDaemon(True)
                    self.start()
                def run(self):
                    self.gui_root = Tk()
                    self.gui_root.title(self.game.name)
                    def on_closing():
                        if messagebox.askokcancel("Quit", "Do you want to quit?"):
                            self.gui_root.destroy()
                            self.gui_root.quit()
                            self.gui_root = None
                    self.gui_root.protocol("WM_DELETE_WINDOW", on_closing)
                    self.gui_frame = Frame(self.gui_root)
                    self.gui_frame.pack()
                    self.gui_buttons = self.game.initialize_buttons(self.board, self.gui_frame)
                    self.gui_root.mainloop()
            self.gui_thread = GuiThread(self.game, self.board)
            self.gui_frame = self.gui_thread.gui_frame
            self.gui_root = self.gui_thread.gui_root
            self.gui_buttons = self.gui_thread.gui_buttons
        return self

    def is_player_max(self, player: Player) -> bool:
        """Determine wheteher a player is MAX."""
        assert isinstance(self.player_max, Player)
        return player.label == self.player_max.label

    def clone(self) -> TwoPlayerGameState:
        c = TwoPlayerGameState()
        c.game = copy.deepcopy(self.game)
        c.player_max = copy.deepcopy(self.player_max)
        c.next_player = copy.deepcopy(self.next_player)
        c.board = copy.deepcopy(self.board)
        c.move_code = copy.deepcopy(self.move_code)
        c.parent = self.parent

        c.end_of_game = self.end_of_game
        c.scores = self.scores

        c.gui_root = self.gui_root
        c.gui_frame = self.gui_frame
        c.gui_buttons = self.gui_buttons
        c.gui_thread = self.gui_thread

        return c

    def generate_successor(
        self,
        board_successor: Any = None,
        move_code: Any = None,
    ) -> TwoPlayerGameState:
        """Generate one successor."""
        successor = TwoPlayerGameState(
            game=self.game,
            player_max = self.player_max,
        )
        #successor = self.clone()

        # Exchange the roles of players
        assert isinstance(self.game, TwoPlayerGame)
        assert isinstance(self.next_player, Player)
        successor.next_player = self.game.opponent(self.next_player)

        # Update successor
        successor.board = board_successor
        successor.move_code = move_code
        successor.parent = self

        end_of_game, scores = self.game.score(successor)
        successor.end_of_game = end_of_game
        successor.scores = scores

        successor.gui_root = self.gui_root
        successor.gui_frame = self.gui_frame
        successor.gui_buttons = self.gui_buttons
        successor.gui_thread = self.gui_thread

        return successor

    def move(self, gui: bool = False) -> TwoPlayerGameState:
        """Make move."""
        assert isinstance(self.next_player, Player)
        next_state = self.next_player.move(self, gui)
        if gui:
            self.gui_root = self.gui_thread.gui_root
            self.gui_buttons = self.gui_thread.gui_buttons
            self.game.gui_update(state=next_state, gui_buttons=self.gui_buttons, gui_root=self.gui_root, moves=[], click_function=None)
        assert isinstance(self.game, TwoPlayerGame)
        assert isinstance(self.player_max, Player)

        return next_state.setup_match()

    def display(self, gui: bool = False) -> None:
        """Display the game state."""
        assert isinstance(self.game, TwoPlayerGame)
        self.game.display(self, gui)


class TwoPlayerGame(ABC):
    """Abstract class for a two player game."""

    def __init__(
        self,
        name: str,
        player1: Player,
        player2: Player,
    ) -> None:
        self.n_players: int = 2
        self.name = name
        self.player1 = player1
        self.player2 = player2
        self.player1.label = 1
        self.player2.label = -1
        self.max_score: float = np.inf
        self.min_score: float = -np.inf

    def opponent(self, player: Player) -> Player:
        """Return the opponent in the match."""
        if player.label == self.player1.label:
            player = self.player2
        elif player.label == self.player2.label:
            player = self.player1
        else:
            raise Exception('The opponent has to be one of the players')

        return player

    def manual_input(self, successors: List[TwoPlayerGameState]) -> int:
        """Get move from user input."""
        moves = ''
        for n, successor in enumerate(successors):
            moves = moves + '{:d}: {}  '.format(n, successor.move_code)
        print(moves)

        min_index_successor = 0
        max_index_successor = len(successors) - 1
        error_msg = 'Enter a number between {} and {}'.format(
            min_index_successor,
            max_index_successor
        )

        while True:
            try:
                index_successor = int(input('Enter your move: '))
            except ValueError:
                print(error_msg)
            else:
                if (
                    index_successor < min_index_successor
                    or index_successor > max_index_successor
                ):
                    print(error_msg)
                else:
                    break

        return index_successor

    def graphical_input(self, state: TwoPlayerGameState, successors: List[TwoPlayerGameState]) -> int:
        """Get move from GUI."""
        if state.end_of_game:
            return -1
        index_successor = 0
        moves = [successor.move_code for successor in successors]
        print(moves)
        # check for empty successors
        if len(moves) == 1 and moves[0] is None:
            return index_successor

        next_move = None
        def get_move(move):
            nonlocal next_move
            next_move = move

        gui_root = state.gui_thread.gui_root
        gui_buttons = state.gui_thread.gui_buttons
        self.gui_update(state=state, gui_buttons=gui_buttons, gui_root=gui_root, moves=moves, click_function=get_move)

        print('waiting for click...')
        while next_move is None:
            time.sleep(0.1)

        for n, successor in enumerate(successors):
            if successor.move_code == next_move:
                index_successor = n

        return index_successor

    def display(self, state: TwoPlayerGameState, gui: bool = False) -> None:
        """Display the game state."""
        if state.move_code:
            print('\nPlayer \'{:s}\' [{:s}] moves {:s}.\n'.format(
                state.previous_player.name,
                str(state.previous_player.label),
                str(state.move_code),
            ))

    @abstractmethod
    def initialize_board(self) -> Any:
        """Initialize board with standard configuration."""
        pass

    @abstractmethod
    def initialize_buttons(self, board: Any, gui_frame: Frame) -> dict:
        pass

    @abstractmethod
    def gui_update(self, state: TwoPlayerGameState, gui_buttons: dict, gui_root: Tk, moves: list = [], click_function: Callable[[Any], None] = None) -> None:
        pass

    @abstractmethod
    def generate_successors(
        self,
        state: TwoPlayerGameState,
    ) -> List[TwoPlayerGameState]:
        """Generate the list of successors of a game state."""
        pass
    #   NOTE return list of successors

    @abstractmethod
    def score(
        self,
        state: TwoPlayerGameState,
    ) -> Tuple[bool, Optional[np.ndarray]]:
        """Determine whether a game is terminal and score a game."""
        pass
    #   NOTE return end_of_game and scores


class TwoPlayerMatch(object):
    """Infrastructure for a match between two players."""

    def __init__(
        self,
        initial_state: Optional[TwoPlayerGameState] = None,
        n_moves_max: int = 500,
        max_seconds_per_move: float = 5,
        gui: bool = False,
    ) -> None:
        self.initial_state = initial_state
        self.n_moves_max = n_moves_max
        self._verbose = (
            initial_state.player1.strategy.verbose > 0
            or initial_state.player2.strategy.verbose > 0
            or gui
        )
        if (
            initial_state.player1.strategy.verbose == 3
            or initial_state.player2.strategy.verbose == 3
        ):
            self._verbose = 3 # to skip user input

        self.max_seconds_per_move = max_seconds_per_move
        self.gui = gui

    @contextmanager
    def time_limit(self, seconds: float):
        timer = threading.Timer(seconds, lambda: _thread.interrupt_main())
        timer.start()
        try:
            yield
        except KeyboardInterrupt:
            pass
        finally:
            # if the action ends in specified time, timer is canceled
            timer.cancel()

    def play_match(self) -> Optional[np.ndarray]:
        """Play a match."""
        if (self.initial_state is None):
            raise ValueError('Please, provide an initial state')

        state = self.initial_state.setup_match(self.gui)
        if (self._verbose > 0):
            print('\nLet\'s play %s!\n' % (self.initial_state.game.name))
            if self._verbose != 3:
                input('Press any key to start playing. ')

        n_moves = 0
        while (n_moves < self.n_moves_max) and not state.end_of_game:

            strategy = state.next_player.strategy

            # NOTE <alberto.suarez@uam.es> Ugly hack.
            is_next_player_manual = (
                (strategy.__class__.__module__, strategy.__class__.__name__)
                == ('strategy', 'ManualStrategy')
            )

            if (is_next_player_manual or self._verbose > 0):
                state.display(self.gui)
                message = (
                    'It is the turn of player \'{:s}\' [{:s}].\n'.format(
                        state.next_player.name,
                        str(state.next_player.label)
                    )
                )
                print(message)

            if (strategy.verbose > 0 and strategy.verbose != 3):
                user_input = input(
                    'Press "s" to save the state of the game, '
                    + 'any other key to continue. '
                )
                if (user_input.lower() == 's'):
                    file_name = input('Input a file name: ')
                    f = open(file_name, 'a')
                    f.write(message)
                    f.write('\nThe state of the board is:\n')
                    f.write(str(state.board))
                    f.write('\n\n\n')
                    f.close()
                    user_input = input('Press any key to continue. ')

                print()

            # limit maximum seconds for this move
            finished = False
            with self.time_limit(self.max_seconds_per_move):
                state = state.move(self.gui)
                finished = True

            if not finished:
                print("Match cancelled because player %s used too much time" % (state.next_player.label))
                scores = np.zeros(2, dtype=float)
                if state.next_player == state.player1:
                    scores[0] = -1
                else:
                    scores[1] = -1
                return scores

            n_moves += 1

        if self._verbose > 0:
            state.display(self.gui)

            print('Game over.\n')

        if state.scores is None:
            raise Warning('Score cannot be computed.')
        else:
            if self._verbose > 0:
                print(
                    'Player {:s} [{:s}]: {:g}\nPlayer {:s} [{:s}]: {:g}\n'.format(
                        state.game.player1.name,
                        str(state.game.player1.label),
                        state.scores[0],
                        str(state.game.player2.name),
                        str(state.game.player2.label),
                        state.scores[1],
                    ),
                )

        if (n_moves == self.n_moves_max) and not state.end_of_game:
            raise Warning(
                'Game did not finish in {:d} moves.\n'.format(self.n_moves_max),
            )

        return state.scores