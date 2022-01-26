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
        transformed = automaton.to_deterministic()
        equiv_map = deterministic_automata_isomorphism(
            expected,
            transformed,
        )
        self.assertTrue(equiv_map is not None)


    #caso de prueba para ver si añade satisfactoriamente los trash
    def test_case1(self) -> None:
        """Test Case 1."""
        automaton_str = """
        Automaton:
            Symbols: 01

            q0
            qf final

            --> q0
            q0 -0-> qf
        """

        automaton = AutomataFormat.read(automaton_str)

        expected_str = """
        Automaton:
            Symbols: 01

            q0
            qf final
            empty

            --> q0
            q0 -0-> qf
            q0 -1-> empty
            qf -0-> empty
            qf -1-> empty
            empty -0-> empty
            empty -1-> empty

        """

        expected = AutomataFormat.read(expected_str)

        self._check_transform(automaton, expected)

    #caso base 2 para probar si reconoce al estado resultante de unir 2 como final
    def test_case2(self) -> None:
        """Test Case 2."""
        automaton_str = """
        Automaton:
            Symbols: 01

            q0
            q1
            q2 final

            --> q0
            q0 -1-> q1
            q1 -0->q1
            q1 -1->q1
            q1 -1->q2
            q2 -1->q2
        """

        automaton = AutomataFormat.read(automaton_str)

        expected_str = """
        Automaton:
            Symbols: 01

            0
            1
            2 final
            trash

            --> 0
            0 -0->trash
            0 -1->1
            1 -0->1
            1 -1->2
            2 -0->1
            2 -1->2
            trash -0->trash
            trash -1->trash

        """

        expected = AutomataFormat.read(expected_str)

        self._check_transform(automaton, expected)

    #caso para probar resultado en caso de no ser necesario el estado trash
    def test_case3(self) -> None:
        """Test Case 3."""
        automaton_str = """
        Automaton:
            Symbols: ab

            q0
            q1
            q2
            q3 final

            --> q0
            q0 -a-> q0
            q0 -b-> q0
            q0 -a->q1
            q1 -b->q2
            q2 -a->q3
        """

        automaton = AutomataFormat.read(automaton_str)

        expected_str = """
        Automaton:
            Symbols: ab

            q0
            q1
            q2
            q3 final

            --> q0
            q0 -a-> q1
            q0 -b-> q0
            q1 -a->q1
            q1 -b->q2
            q2 -b->q0
            q2 -a->q3
            q3 -a->q1
            q3 -b->q2
        """

        expected = AutomataFormat.read(expected_str)

        self._check_transform(automaton, expected)

    #caso de prueba de ejercicios teóricos
    def test_case4(self) -> None:
        """Test Case 4."""
        automaton_str = """
        Automaton:
            Symbols: 01

            a
            b
            c final
            d 

            --> a
            a -1->b
            b -0->b
            b -0->d
            b -1->a
            b -1->c
            c -0->b
        """

        automaton = AutomataFormat.read(automaton_str)

        expected_str = """
        Automaton:
            Symbols: 01

            a
            b
            ac final
            bd
            Trash

            --> a
            a -0->Trash
            Trash -0->Trash
            Trash -1->Trash
            a -1->b
            b -1->ac
            b -0->bd
            ac -0->b
            ac -1->b
            bd -0->bd
            bd -1->ac
        """

        expected = AutomataFormat.read(expected_str)

        self._check_transform(automaton, expected)

    #caso con muchos símbolos para probar
    def test_case5(self) -> None:
        """Test Case 5."""
        automaton_str = """
        Automaton:
            Symbols: 0123

            a
            b
            c final
            d final

            --> a
            a -0-> a
            a -1-> b
            a -1-> c
            b -0-> a
            c -0-> a
            c -1-> b
            c -1-> c
            d -0-> c
            d -0-> a
        """

        automaton = AutomataFormat.read(automaton_str)

        expected_str = """
        Automaton:
            Symbols: 0123

            0
            1 final
            Trash

            --> 0
            0 -0-> 0
            0 -1-> 1
            0 -2-> Trash
            0 -3-> Trash
            1 -0-> 0
            1 -1-> 1
            1 -2-> Trash
            1 -3-> Trash
            Trash -0-> Trash
            Trash -1-> Trash
            Trash -2-> Trash
            Trash -3-> Trash
        """
        expected = AutomataFormat.read(expected_str)

        self._check_transform(automaton, expected)

if __name__ == '__main__':
    unittest.main()