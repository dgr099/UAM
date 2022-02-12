"""Test evaluation of automatas."""
import unittest
from abc import ABC

from automata.automaton import FiniteAutomaton
from automata.utils import AutomataFormat, deterministic_automata_isomorphism


class TestTransform(ABC, unittest.TestCase):
    """Base class for string acceptance tests."""

    def _check_transform(
        self,
        automaton: FiniteAutomaton,
        expected: FiniteAutomaton,
    ) -> None:
        """Test that the transformed automaton is as the expected one."""
        transformed = automaton.to_minimized()
        equiv_map = deterministic_automata_isomorphism(
            expected,
            transformed,
        )

        self.assertTrue(equiv_map is not None)

    def test_case1(self) -> None:
        """Test Case 1."""
        automaton_str = """
        Automaton:
            Symbols: 01

            a
            b
            c final
            d
            e
            f
            g
            h

            --> a
            a -0-> b
            a -1-> f
            b -0-> g
            b -1-> c
            c -0-> a
            c -1-> c
            d -0-> c
            d -1-> g
            e -0-> h
            e -1-> f
            f -0-> c
            f -1-> g
            g -0-> g
            g -1-> e
            h -0-> g
            h -1-> c
        """

        automaton = AutomataFormat.read(automaton_str)

        expected_str = """
        Automaton:
            Symbols: 01

            ae
            bh
            c final
            f
            g

            --> ae
            ae -0-> bh
            ae -1-> f
            bh -0-> g
            bh -1-> c
            c -0-> ae
            c -1->c
            f -0-> c
            f -1-> g
            g -0-> g
            g -1-> ae

        """

        expected = AutomataFormat.read(expected_str)

        self._check_transform(automaton, expected)


if __name__ == '__main__':
    unittest.main()