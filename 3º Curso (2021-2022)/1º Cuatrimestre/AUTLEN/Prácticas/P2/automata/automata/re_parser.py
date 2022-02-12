"""Conversion from regex to automata."""
from automata.automaton import FiniteAutomaton
from automata.re_parser_interfaces import AbstractREParser

import automata.automaton as aut
from typing import Sequence, Set


class REParser(AbstractREParser):
    """Class for processing regular expressions in Kleene's syntax."""

    def _create_automaton_empty(
        self,
    ) -> FiniteAutomaton:
        initial_state: aut.State
        states: Set[aut.State] = set()
        symbols: Set[str] = set()
        transitions: Set[aut.Transition] = set()

        initial_state = aut.State(name="Empty", is_final=False)
        states.add(initial_state)
        states.add(aut.State(name="Final", is_final=True))

        return FiniteAutomaton(
            initial_state=initial_state,
            states=states,
            symbols=symbols,
            transitions=transitions,
            )


    def _create_automaton_lambda(
        self,
    ) -> FiniteAutomaton:
        initial_state: aut.State
        states: Set[aut.State] = set()
        symbols: Set[str] = set()
        transitions: Set[aut.Transition] = set()

        initial_state = aut.State(name="Empty", is_final=True)
        states.add(initial_state)
        transitions.add(aut.Transition(initial_state, None, initial_state))

        return FiniteAutomaton(
            initial_state=initial_state,
            states=states,
            symbols=symbols,
            transitions=transitions,
            )


    def _create_automaton_symbol(
        self,
        symbol: str,
    ) -> FiniteAutomaton:
        initial_state: aut.State
        states: Set[aut.State] = set()
        symbols: Set[str] = set()
        transitions: Set[aut.Transition] = set()

        initial_state = aut.State(name="Empty", is_final=False)
        final_state = aut.State(name=symbol, is_final=True)
        states.add(initial_state)
        states.add(final_state)
        transitions.add(aut.Transition(initial_state, symbol, final_state))
        symbols.add(symbol)

        return FiniteAutomaton(
            initial_state=initial_state,
            states=states,
            symbols=symbols,
            transitions=transitions,
            )

        
    def _create_automaton_star(
        self,
        automaton: FiniteAutomaton,
    ) -> FiniteAutomaton:
        initial_state: aut.State
        states: Set[aut.State] = set()
        symbols: Set[str] = set()
        transitions: Set[aut.Transition] = set()

        initial_state = aut.State(name="Empty", is_final=False)
        final_state = aut.State(name="Final", is_final=True)
        states.add(initial_state)
        states.add(final_state)
        for s in automaton.states:
            if s.is_final:
                s.is_final = False
                transitions.add(aut.Transition(s, None, final_state))
            s.name += '0'
            states.add(s)
        transitions.add(aut.Transition(initial_state, None, automaton.initial_state))
        transitions.update(automaton.transitions)
        transitions.add(aut.Transition(initial_state, None, final_state))
        transitions.add(aut.Transition(final_state, None, initial_state))
        symbols.update(automaton.symbols)

        return FiniteAutomaton(
            initial_state=initial_state,
            states=states,
            symbols=symbols,
            transitions=transitions,
            )


    def _create_automaton_union(
        self,
        automaton1: FiniteAutomaton,
        automaton2: FiniteAutomaton,
    ) -> FiniteAutomaton:
        initial_state: aut.State
        states: Set[aut.State] = set()
        symbols: Set[str] = set()
        transitions: Set[aut.Transition]  = set()

        initial_state = aut.State(name="Empty", is_final=False)
        final_state = aut.State(name="Final", is_final=True)

        states.add(initial_state)
        states.add(final_state)
        for s in automaton1.states:
            if s.is_final and s != final_state:
                s.is_final = False
                transitions.add(aut.Transition(s, None, final_state))
            s.name += '1'
            states.add(s)
        for s in automaton2.states:
            if s.is_final and s != final_state:
                s.is_final = False
                transitions.add(aut.Transition(s, None, final_state))
            s.name += '2'
            states.add(s)
        transitions.add(aut.Transition(initial_state, None, automaton1.initial_state))
        transitions.add(aut.Transition(initial_state, None, automaton2.initial_state))
        transitions.update(automaton1.transitions)
        transitions.update(automaton2.transitions)
        symbols.update(automaton1.symbols)
        symbols.update(automaton2.symbols)
        return FiniteAutomaton(
            initial_state=initial_state,
            states=states,
            symbols=symbols,
            transitions=transitions,
            )


    def _create_automaton_concat(
        self,
        automaton1: FiniteAutomaton,
        automaton2: FiniteAutomaton,
    ) -> FiniteAutomaton:
        initial_state: aut.State
        states: Set[aut.State] = set()
        symbols: Set[str] = set()
        transitions: Set[aut.Transition] = set()

        initial_state = automaton1.initial_state
        for s in automaton1.states:
            if s.is_final:
                s.is_final = False
                transitions.add(aut.Transition(s, None, automaton2.initial_state))
            s.name += '1'
            states.add(s)
        for s in automaton2.states:
            s.name += '2'
            states.add(s)
        transitions = transitions.union(automaton1.transitions)
        transitions = transitions.union(automaton2.transitions)
        symbols.update(automaton1.symbols)
        symbols.update(automaton2.symbols)

        return FiniteAutomaton(
            initial_state=initial_state,
            states=states,
            symbols=symbols,
            transitions=transitions,
            )
