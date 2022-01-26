"""Test evaluation of automatas."""
import unittest
from abc import ABC

from automata.automaton import FiniteAutomaton
from automata.utils import AutomataFormat, deterministic_automata_isomorphism
import os



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

    #test de prueba de moodle para probar funcionalidad
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

    #test para probar caso con dos finales distintos
    def test_case2(self) -> None:
        """Test Case 2."""
        automaton_str = """
        Automaton:
            Symbols: 01

            a final
            b final
            c

            --> a
            a -0->a
            a -1->c
            b -0->a
            b -1->c
            c -1->c
            c -0->a
        """

        automaton = AutomataFormat.read(automaton_str)

        expected_str = """
        Automaton:
            Symbols: 01

            Symbols: 01

            a final
            c

            --> a
            a -0->a
            a -1->c
            c -1->c
            c -0->a

        """

        expected = AutomataFormat.read(expected_str)

        self._check_transform(automaton, expected)

    #test nás exaustivo con varios finales diferentes
    def test_case3(self) -> None:
        """Test Case 3."""
        automaton_str = """
        Automaton:
            Symbols: abc

            a final
            b final
            c final
            d final
            e

            --> a
            a -a->b
            a -b->c
            a -c->b
            b -a->b
            b -b->c
            b -c->b
            c -a->b
            c -b->d
            c -c->b
            d -a->e
            d -b->e
            d -c->e
            e -a->e
            e -b->e
            e -c->e

        """
        automaton = AutomataFormat.read(automaton_str)

        expected_str = """
        Automaton:
            Symbols: abc

            a final
            b final
            c final
            d

            --> a
            a -a->a
            a -b->b
            a -c->a
            b -a->a
            b -b->c
            b -c->a
            c -a->d
            c -b->d
            c -c->d
            d -a->d
            d -b->d
            d -c->d

        """

        expected = AutomataFormat.read(expected_str)

        self._check_transform(automaton, expected)

    #test de prueba ejemplo 2 de moodle
    def test_case4(self) -> None:
        """Test Case 4."""
        automaton_str = """
        Automaton:
            Symbols: ab

            q0
            q1 final
            q2
            q3
            q4
            q5
            q6
            q7 final
            q8
            q9 final

            --> q0
            q0 -a-> q1
            q0 -b-> q6
            q1 -a-> q2
            q1 -b-> q3
            q2 -a-> q4
            q2 -b-> q2
            q3 -a-> q5
            q3 -b-> q3
            q4 -a-> q4
            q4 -b-> q8
            q5 -a-> q5
            q5 -b-> q4
            q6 -a-> q6
            q6 -b-> q7
            q7 -a-> q0
            q7 -b-> q7
            q8 -a-> q8
            q8 -b-> q9
            q9 -a-> q0
            q9 -b-> q9

        """

        automaton = AutomataFormat.read(automaton_str)

        expected_str = """
        Automaton:
            Symbols: ab

            q0
            q1 final
            q2
            q3
            q4
            q5
            q6q8
            q7q9 final

            --> q0
            q0 -a-> q1
            q0 -b-> q6q8
            q1 -a-> q2
            q1 -b-> q3
            q2 -a-> q4
            q2 -b-> q2
            q3 -a-> q5
            q3 -b-> q3
            q4 -a-> q4
            q4 -b-> q6q8
            q5 -a-> q5
            q5 -b-> q4
            q6q8 -a-> q6q8
            q6q8 -b-> q7q9
            q7q9 -a-> q0
            q7q9 -b-> q7q9

        """

        expected = AutomataFormat.read(expected_str)

        self._check_transform(automaton, expected)

    #test de prueba caso básico
    def test_case5(self) -> None:
        """Test Case 5."""
        automaton_str = """
        Automaton:
            Symbols: ab

            q0
            q1 final
            q2

            --> q0
            q0 -a-> q1
            q0 -b-> q0
            q1 -a-> q2
            q1 -b-> q1
            q2 -a-> q1
            q2 -b-> q2
            

        """

        automaton = AutomataFormat.read(automaton_str)

        expected_str = """
        Automaton:
            Symbols: ab

            q0
            q1 final

            --> q0
            q0 -a-> q1
            q0 -b-> q0
            q1 -a-> q0
            q1 -b-> q1

        """

        expected = AutomataFormat.read(expected_str)

        self._check_transform(automaton, expected)

    #test para probar casos de estados inalcanzables
    def test_case6(self) -> None:
        """Test Case 6."""
        automaton_str = """
        Automaton:
            Symbols: ab

            q0
            q1 final
            q2
            q3 final
            q4
            qx

            --> q0
            q0 -a-> q1
            q0 -b-> q3
            q1 -a-> q2
            q1 -b-> q1
            q2 -a-> q1
            q2 -b-> q2
            q3 -a-> q4
            q3 -b-> q3
            q4 -a-> q3
            q4 -b-> q4
            qx -a-> qx
            qx -b-> qx

        """

        automaton = AutomataFormat.read(automaton_str)

        expected_str = """
        Automaton:
            Symbols: ab

            q0
            q1q3 final
            q2q4

            --> q0
            q0 -a-> q1q3
            q0 -b-> q1q3
            q1q3 -a-> q2q4
            q1q3 -b-> q1q3
            q2q4 -a-> q1q3
            q2q4 -b-> q2q4

        """

        expected = AutomataFormat.read(expected_str)

        self._check_transform(automaton, expected)


if __name__ == '__main__':
    unittest.main()