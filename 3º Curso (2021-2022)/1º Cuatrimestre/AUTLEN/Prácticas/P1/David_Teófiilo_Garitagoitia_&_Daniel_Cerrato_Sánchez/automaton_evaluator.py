"""Evaluation of automata."""
from typing import Set


from automata.automaton import FiniteAutomaton, State
from automata.interfaces import AbstractFiniteAutomatonEvaluator


class FiniteAutomatonEvaluator(
    AbstractFiniteAutomatonEvaluator[FiniteAutomaton, State],
):
    """Evaluator of an automaton."""

    def process_symbol(self, symbol: str) -> None:
        newStates: Set[State] = set()
        if symbol not in self.automaton.symbols:
            raise ValueError(
                    f"Symbol {symbol} is not in the set of symbols",
                )
        for state in self.current_states:
            for transition in self.automaton.transitions:
                if transition.initial_state == state and transition.symbol == symbol:
                    newStates.add(transition.final_state)
        self._complete_lambdas(newStates)
        self.current_states = newStates

    def _complete_lambdas(self, set_to_complete: Set[State]) -> None:
        queue = []
        for state in set_to_complete:
            queue.append(state)
        while len(queue) != 0:
            state = queue.pop()
            for transition in self.automaton.transitions:
                if transition.initial_state == state and transition.symbol is None:
                    if transition.final_state not in set_to_complete:
                        queue.append(transition.final_state)
                    set_to_complete.add(transition.final_state)
        

    def is_accepting(self) -> bool:
        for state in self.current_states:
            if state.is_final:
                return True
        return False
