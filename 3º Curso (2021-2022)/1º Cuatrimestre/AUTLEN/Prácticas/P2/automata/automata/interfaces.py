"""General interfaces for automatas."""
from abc import ABC, abstractmethod
from typing import (
    AbstractSet,
    Collection,
    Generic,
    Optional,
    Sequence,
    Set,
    TypeVar,
)


class AbstractState(ABC):
    """
    Abstract definition of an automaton state.

    Args:
        name: Name of the state.
        is_final: Whether the state is a final state or not.

    """

    name: str
    is_final: bool

    def __init__(self, name: str, *, is_final: bool = False) -> None:
        self.name = name
        self.is_final = is_final

    def __eq__(self, other: object) -> bool:
        if not isinstance(other, type(self)):
            return NotImplemented

        return (
            self.name == other.name
            and self.is_final == other.is_final
        )

    def __repr__(self) -> str:
        return (
            f"{type(self).__name__}({self.name!r}, is_final={self.is_final!r})"
        )

    def __hash__(self) -> int:
        return hash((self.name, self.is_final))


_State = TypeVar("_State", bound=AbstractState, covariant=True)


class AbstractTransition(ABC, Generic[_State]):
    """
    Abstract definition of an automaton transition.

    Args:
        initial_state: Initial state of the transition.
        symbol: Symbol consumed in the transition.
            ``None`` for a lambda transition.
        final_state: Final state of the transition.

    """

    initial_state: _State
    symbol: Optional[str]
    final_state: _State

    def __init__(
        self,
        initial_state: _State,
        symbol: Optional[str],
        final_state: _State,
    ) -> None:
        self.initial_state = initial_state
        self.symbol = symbol
        self.final_state = final_state

    def __eq__(self, other: object) -> bool:
        if not isinstance(other, type(self)):
            return NotImplemented

        return (
            self.initial_state == other.initial_state
            and self.symbol == other.symbol
            and self.final_state == other.final_state
        )

    def __repr__(self) -> str:
        return (
            f"{type(self).__name__}("
            f"{self.initial_state!r}, {self.symbol!r}, {self.final_state!r})"
        )

    def __hash__(self) -> int:
        return hash((self.initial_state, self.symbol, self.final_state))


_Transition = TypeVar(
    "_Transition",
    bound=AbstractTransition[AbstractState],
    covariant=True,
)
_SelfType = TypeVar(
    "_SelfType",
    bound="AbstractFiniteAutomaton[AbstractState, AbstractTransition[AbstractState]]",
)


class AbstractFiniteAutomaton(
    ABC,
    Generic[_State, _Transition],
):
    """
    Abstract definition of an automaton.

    Args:
        initial_state: The initial state of the automaton.
        states: Collection of states of the automaton. It is converted to a
            tuple internally.
        symbols: Collection of symbols of the automaton. It is converted to a
            tuple internally.
        transitions: Collection of transitions of the automaton. It is
            converted to a tuple internally.

    """

    initial_state: _State
    states: Sequence[_State]
    symbols: Sequence[str]
    transitions: Sequence[_Transition]

    def __init__(
        self,
        *,
        initial_state: _State,
        states: Collection[_State],
        symbols: Collection[str],
        transitions: Collection[_Transition],
    ) -> None:
        if initial_state not in states:
            raise ValueError(
                f"Initial state {initial_state.name} "
                f"is not in the set of states",
            )

        for t in transitions:
            for s in (t.initial_state, t.final_state):
                if s not in states:
                    raise ValueError(
                        f"State {s} from transition {t}"
                        f"is not in the set of states",
                    )

            if t.symbol is not None and t.symbol not in symbols:
                raise ValueError(
                    f"Symbol {t.symbol} from transition {t}"
                    f"is not in the set of symbols",
                )

        if len(set(states)) != len(states):
            raise ValueError(
                "There are repeated states",
            )

        if len(set(symbols)) != len(symbols):
            raise ValueError(
                "There are repeated symbols",
            )

        if len(set(transitions)) != len(transitions):
            raise ValueError(
                "There are repeated transitions",
            )

        self.initial_state = initial_state
        self.states = tuple(states)
        self.symbols = tuple(symbols)
        self.transitions = tuple(transitions)

    def __eq__(self, other: object) -> bool:
        if not isinstance(other, type(self)):
            return NotImplemented

        # We use sets as the order should not matter
        return (
            self.initial_state == other.initial_state
            and set(self.states) == set(other.states)
            and set(self.symbols) == set(other.symbols)
            and set(self.transitions) == set(other.transitions)
        )

    def __repr__(self) -> str:
        return (
            f"{type(self).__name__}("
            f"initial_state={self.initial_state!r}, "
            f"states={self.states!r}, "
            f"symbols={self.symbols!r}, "
            f"transitions={self.transitions!r})"
        )

    @abstractmethod
    def to_deterministic(
        self: _SelfType,
    ) -> _SelfType:
        """
        Return a equivalent deterministic automaton.

        Returns:
            Equivalent deterministic automaton.

        """
        raise NotImplementedError("This method must be implemented.")

    @abstractmethod
    def to_minimized(
        self: _SelfType,
    ) -> _SelfType:
        """
        Return a equivalent minimal automaton.

        Returns:
            Equivalent minimal automaton.

        """
        raise NotImplementedError("This method must be implemented.")


_Automaton = TypeVar(
    "_Automaton",
    bound=AbstractFiniteAutomaton[
        AbstractState,
        AbstractTransition[AbstractState],
    ],
)


class AbstractFiniteAutomatonEvaluator(
    ABC,
    Generic[_Automaton, _State],
):
    """
    Abstract definition of an automaton evaluator.

    Args:
        automaton: Automaton to evaluate.

    Attributes:
        current_states: Set of current states of the automata.

    """

    automaton: _Automaton
    current_states: AbstractSet[_State]

    def __init__(self, automaton: _Automaton) -> None:
        self.automaton = automaton
        current_states: Set[_State] = {
            self.automaton.initial_state,  # type: ignore[arg-type]
        }
        self._complete_lambdas(current_states)
        self.current_states = current_states

    @abstractmethod
    def process_symbol(self, symbol: str) -> None:
        """
        Process one symbol.

        Args:
            symbol: Symbol to consume.

        """
        raise NotImplementedError("This method must be implemented.")

    @abstractmethod
    def _complete_lambdas(self, set_to_complete: Set[_State]) -> None:
        """
        Add states reachable with lambda transitions to the set.

        Args:
            set_to_complete: Current set of states to be completed.
        """
        raise NotImplementedError("This method must be implemented.")

    def process_string(self, string: str) -> None:
        """
        Process a full string of symbols.

        Args:
            string: String to process.

        """
        for symbol in string:
            self.process_symbol(symbol)

    @abstractmethod
    def is_accepting(self) -> bool:
        """Check if the current state is an accepting one."""
        raise NotImplementedError("This method must be implemented.")

    def accepts(self, string: str) -> bool:
        """
        Return if a string is accepted without changing state.

        Note: This function is NOT thread-safe.

        """
        old_states = self.current_states
        try:
            self.process_string(string)
            accepted = self.is_accepting()
        finally:
            self.current_states = old_states

        return accepted
