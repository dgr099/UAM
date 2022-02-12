"""Interfaces for parsing regex to automata."""
from abc import ABC, abstractmethod
from typing import List

from automata.automaton import FiniteAutomaton


def _re_to_rpn(re_string: str) -> str:
    """
    Convert re to reverse polish notation (RPN).

    Does not check that the input re is syntactically correct.

    Args:
        re_string: Regular expression in infix notation.

    Returns:
        Regular expression in reverse polish notation.

    """
    stack: List[str] = []
    rpn_string = ""
    for x in re_string:
        if x == "+":
            while len(stack) > 0 and stack[-1] != "(":
                rpn_string += stack.pop()
            stack.append(x)
        elif x == ".":
            while len(stack) > 0 and stack[-1] == ".":
                rpn_string += stack.pop()
            stack.append(x)
        elif x == "(":
            stack.append(x)
        elif x == ")":
            while stack[-1] != "(":
                rpn_string += stack.pop()
            stack.pop()
        else:
            rpn_string += x

    while len(stack) > 0:
        rpn_string += stack.pop()

    return rpn_string


class AbstractREParser(ABC):
    """Abstract class for parsing regular expressions in Kleene's syntax."""

    state_counter: int

    def __init__(
        self,
    ) -> None:
        super().__init__()
        self.state_counter = 0

    @abstractmethod
    def _create_automaton_empty(
        self,
    ) -> FiniteAutomaton:
        """
        Create an automaton that accepts the empty language.

        Returns:
            Automaton that accepts the empty language.

        """
        raise NotImplementedError("This method must be implemented.")

    @abstractmethod
    def _create_automaton_lambda(
        self,
    ) -> FiniteAutomaton:
        """
        Create an automaton that accepts the empty string.

        Returns:
            Automaton that accepts the empty string.

        """
        raise NotImplementedError("This method must be implemented.")

    @abstractmethod
    def _create_automaton_symbol(
        self,
        symbol: str,
    ) -> FiniteAutomaton:
        """
        Create an automaton that accepts one symbol.

        Args:
            symbol: Symbol that the automaton should accept.

        Returns:
            Automaton that accepts a symbol.

        """
        raise NotImplementedError("This method must be implemented.")

    @abstractmethod
    def _create_automaton_star(
        self,
        automaton: FiniteAutomaton,
    ) -> FiniteAutomaton:
        """
        Create an automaton that accepts the Kleene star of another.

        Args:
            automaton: Automaton whose Kleene star must be computed.

        Returns:
            Automaton that accepts the Kleene star.

        """
        raise NotImplementedError("This method must be implemented.")

    @abstractmethod
    def _create_automaton_union(
        self,
        automaton1: FiniteAutomaton,
        automaton2: FiniteAutomaton,
    ) -> FiniteAutomaton:
        """
        Create an automaton that accepts the union of two automata.

        Args:
            automaton1: First automaton of the union.
            automaton2: Second automaton of the union.

        Returns:
            Automaton that accepts the union.

        """
        raise NotImplementedError("This method must be implemented.")

    @abstractmethod
    def _create_automaton_concat(
        self,
        automaton1: FiniteAutomaton,
        automaton2: FiniteAutomaton,
    ) -> FiniteAutomaton:
        """
        Create an automaton that accepts the concatenation of two automata.

        Args:
            automaton1: First automaton of the concatenation.
            automaton2: Second automaton of the concatenation.

        Returns:
            Automaton that accepts the concatenation.

        """
        raise NotImplementedError("This method must be implemented.")

    def create_automaton(
        self,
        re_string: str,
    ) -> FiniteAutomaton:
        """
        Create an automaton from a regex.

        Args:
            re_string: String with the regular expression in Kleene notation.

        Returns:
            Automaton equivalent to the regex.

        """
        if not re_string:
            return self._create_automaton_empty()
        
        rpn_string = _re_to_rpn(re_string)

        stack: List[FiniteAutomaton] = []
        self.state_counter = 0
        for x in rpn_string:
            if x == "*":
                aut = stack.pop()
                stack.append(self._create_automaton_star(aut))
            elif x == "+":
                aut2 = stack.pop()
                aut1 = stack.pop()
                stack.append(self._create_automaton_union(aut1, aut2))
            elif x == ".":
                aut2 = stack.pop()
                aut1 = stack.pop()
                stack.append(self._create_automaton_concat(aut1, aut2))
            elif x == "λ":
                stack.append(self._create_automaton_lambda())
            else:
                stack.append(self._create_automaton_symbol(x))

        return stack.pop()
