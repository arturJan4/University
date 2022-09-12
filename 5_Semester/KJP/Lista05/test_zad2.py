import unittest
from unittest import TestCase

from zad2 import *

if __name__ == '__main__':
    unittest.main()

T = Const(True)
F = Const(False)
a = Var("a")
b = Var("b")
c = Var("c")
x = Var("x")
y = Var("y")
z = Var("z")


class TestFormula(TestCase):
    def test_get_variables(self):
        formulas = [
            (T, []),
            (F, []),
            (Imp(a, b), ['a', 'b']),
            (a, ['a']),
            (Or(Imp(a, b), Or(T, c)), ['a', 'b', 'c']),
        ]

        for f, expected in formulas:
            with self.subTest():
                actual = f.get_variables()
                self.assertCountEqual(actual, expected)  # order may be different

    def test_evaluate(self):
        formulas = [
            (T, {}, True),
            (F, {}, False),
            (Imp(a, b), {'a': 1, 'b': 0}, False),
            (Imp(a, b), {'a': 1, 'b': 1}, True),
            (a, {'a': 1}, True),
            (a, {'a': 0, 'b': 1}, False),
            (Not(a), {'a': 0}, True),
            (Or(a, b), {'a': 0, 'b': 1}, True),
            (And(a, b), {'a': 0, 'b': 1}, False),
            (Or(Imp(a, b), T), {'a': 1, 'b': 0}, True),
        ]

        for f, variables, expected in formulas:
            with self.subTest():
                actual = f.evaluate(variables)
                self.assertEqual(actual, expected)

    def test_simplify(self):
        formulas = [
            (T, T),
            (a, a),
            (Or(T, T), T),
            (And(T, T), T),
            (And(a, T), a),
            (And(T, a), a),
            (Or(a, F), a),
            (And(F, a), F),
            (And(F, F), F)
        ]

        for f, expected in formulas:
            with self.subTest():
                actual = f.simplify()
                self.assertEqual(actual, expected)

    def test_print(self):
        formulas = [
            (T, "⊤"),
            (F, '⊥'),
            (F >> T, '⊥ → ⊤'),
            (a+b, 'a ∨ b'),
            (a*b, 'a ∧ b'),
            (~a, '¬a'),
            (Imp(a, (Imp(b, c))), "a → (b → c)"),
            (Imp(Imp(a, b), c), "(a → b) → c"),
            (Or(a, And(b, c)), "a ∨ (b ∧ c)"),
            (Or(Not(Var("x")), And(Var("y"), Const("True"))), "¬x ∨ (y ∧ ⊤)"),
            (Or(Or(a, b), c), "(a ∨ b) ∨ c")
        ]

        for f, expected in formulas:
            with self.subTest():
                actual = str(f)
                self.assertEqual(actual, expected)

    def test_tautology_true(self):
        formulas = [
            T,
            Or(T, a),
            And(T, T),
            Or(a, Not(a)),
            Imp(And(Imp(a, b), Imp(b, c)), Imp(a, c)),
            Imp(Or(a, b), Or(a, b)),
            Imp(And(Imp(Not(a), b), Imp(Not(a), Not(b))), a)
        ]
        expected = "Formula is a tautology."

        for f in formulas:
            with self.subTest():
                actual = Formula.tautology(f)
                self.assertEqual(actual, expected)

    def test_tautology_false(self):
        formulas = [
            F,
            a,
            Imp(a, b),
            Or(a, b),
            And(a, b),
            And(T, F),
            And(Imp(b, a), Imp(a, Or(a, Not(Imp(b, a))))),
        ]
        expected = "Formula is not a tautology."

        for f in formulas:
            with self.subTest():
                actual = Formula.tautology(f)
                self.assertEqual(actual, expected)

    def test_raise_misleading_name(self):
        formulas = [
            (lambda: Var("true"), MisleadingNameError),
            (lambda: Var("false"), MisleadingNameError),
        ]

        for f, err in formulas:
            with self.subTest():
                self.assertRaises(err, f)
