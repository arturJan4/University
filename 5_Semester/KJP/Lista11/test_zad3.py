import io
import unittest.mock
from unittest import TestCase
from unittest import TestSuite
from unittest import TextTestRunner

from zad3 import *


class TestValidNumbers(TestCase):
    grid = []

    def setUp(self) -> None:
        self.grid = [[0, 7, 0, 0, 5, 0, 0, 9, 2],
                     [2, 5, 9, 1, 0, 0, 6, 3, 4],
                     [0, 0, 0, 4, 0, 2, 5, 0, 0],
                     [3, 0, 2, 7, 1, 6, 0, 0, 0],
                     [5, 0, 1, 2, 0, 0, 0, 0, 0],
                     [0, 0, 0, 5, 0, 0, 0, 2, 3],
                     [6, 2, 0, 0, 0, 0, 0, 0, 5],
                     [0, 0, 7, 0, 0, 0, 0, 0, 6],
                     [0, 8, 5, 0, 0, 4, 0, 1, 0]]

    def test_simple(self):
        x, y = 0, 0

        actual = valid_numbers(self.grid, x, y)
        expected = [1, 4, 8]

        # order indifference in tests
        self.assertEqual(actual, expected)

    def test_filled(self):
        x, y = 1, 0

        actual = valid_numbers(self.grid, x, y)
        expected = 7  # returns already filled value

        # order indifference in tests
        self.assertEqual(actual, expected)

    def test_edge_case(self):
        x, y = 9, 0
        self.assertRaises(IndexError, lambda: valid_numbers(self.grid, x, y))


class TestSolveSudoku(TestCase):
    def test_simple(self):
        example_easy = [[0, 7, 0, 0, 5, 0, 0, 9, 2],
                        [2, 5, 9, 1, 0, 0, 6, 3, 4],
                        [0, 0, 0, 4, 0, 2, 5, 0, 0],
                        [3, 0, 2, 7, 1, 6, 0, 0, 0],
                        [5, 0, 1, 2, 0, 0, 0, 0, 0],
                        [0, 0, 0, 5, 0, 0, 0, 2, 3],
                        [6, 2, 0, 0, 0, 0, 0, 0, 5],
                        [0, 0, 7, 0, 0, 0, 0, 0, 6],
                        [0, 8, 5, 0, 0, 4, 0, 1, 0]]

        expected = [[1, 7, 4, 6, 5, 3, 8, 9, 2],
                    [2, 5, 9, 1, 8, 7, 6, 3, 4],
                    [8, 3, 6, 4, 9, 2, 5, 7, 1],
                    [3, 9, 2, 7, 1, 6, 4, 5, 8],
                    [5, 4, 1, 2, 3, 8, 7, 6, 9],
                    [7, 6, 8, 5, 4, 9, 1, 2, 3],
                    [6, 2, 3, 8, 7, 1, 9, 4, 5],
                    [4, 1, 7, 9, 2, 5, 3, 8, 6],
                    [9, 8, 5, 3, 6, 4, 2, 1, 7]]

        actual = solve_sudoku(example_easy)
        self.assertEqual(actual, expected)

    def test_hard(self):
        example_hard = [[0, 0, 0, 0, 0, 0, 6, 8, 0],
                        [0, 0, 0, 0, 7, 3, 0, 0, 9],
                        [3, 0, 9, 0, 0, 0, 0, 4, 5],
                        [4, 9, 0, 0, 0, 0, 0, 0, 0],
                        [8, 0, 3, 0, 5, 0, 9, 0, 2],
                        [0, 0, 0, 0, 0, 0, 0, 3, 6],
                        [9, 6, 0, 0, 0, 0, 3, 0, 8],
                        [7, 0, 0, 6, 8, 0, 0, 0, 0],
                        [0, 2, 8, 0, 0, 0, 0, 0, 0]]

        expected = [[1, 7, 2, 5, 4, 9, 6, 8, 3],
                    [6, 4, 5, 8, 7, 3, 2, 1, 9],
                    [3, 8, 9, 2, 6, 1, 7, 4, 5],
                    [4, 9, 6, 3, 2, 7, 8, 5, 1],
                    [8, 1, 3, 4, 5, 6, 9, 7, 2],
                    [2, 5, 7, 1, 9, 8, 4, 3, 6],
                    [9, 6, 4, 7, 1, 5, 3, 2, 8],
                    [7, 3, 1, 6, 8, 2, 5, 9, 4],
                    [5, 2, 8, 9, 3, 4, 1, 6, 7]]

        actual = solve_sudoku(example_hard)
        self.assertEqual(actual, expected)

    def test_wrong(self):
        example_wrong = [[0, 0, 0, 0, 0, 0, 6, 0, 8],
                         [0, 0, 0, 0, 7, 3, 0, 0, 9],
                         [3, 0, 9, 0, 0, 0, 0, 4, 5],
                         [4, 9, 0, 0, 0, 0, 0, 0, 0],
                         [8, 0, 3, 0, 5, 0, 9, 0, 2],
                         [0, 0, 0, 0, 0, 0, 0, 3, 6],
                         [9, 6, 0, 0, 0, 0, 3, 0, 8],
                         [7, 0, 0, 6, 8, 0, 0, 0, 0],
                         [0, 2, 8, 0, 0, 0, 0, 0, 0]]

        expected = None
        actual = solve_sudoku(example_wrong)
        self.assertEqual(actual, expected)


class TestPrettyPrintSudoku(TestCase):
    @unittest.mock.patch('sys.stdout', new_callable=io.StringIO)
    def test_simple(self, mock_stdout):
        grid = [[1, 7, 4, 6, 5, 3, 8, 9, 2],
                [2, 5, 9, 1, 8, 7, 6, 3, 4],
                [8, 3, 6, 4, 9, 2, 5, 7, 1],
                [3, 9, 2, 7, 1, 6, 4, 5, 8],
                [5, 4, 1, 2, 3, 8, 7, 6, 9],
                [7, 6, 8, 5, 4, 9, 1, 2, 3],
                [6, 2, 3, 8, 7, 1, 9, 4, 5],
                [4, 1, 7, 9, 2, 5, 3, 8, 6],
                [9, 8, 5, 3, 6, 4, 2, 1, 7]]
        expected = """=============================
|| 1 7 4 || 6 5 3 || 8 9 2 || 
|| 2 5 9 || 1 8 7 || 6 3 4 || 
|| 8 3 6 || 4 9 2 || 5 7 1 || 
=============================
|| 3 9 2 || 7 1 6 || 4 5 8 || 
|| 5 4 1 || 2 3 8 || 7 6 9 || 
|| 7 6 8 || 5 4 9 || 1 2 3 || 
=============================
|| 6 2 3 || 8 7 1 || 9 4 5 || 
|| 4 1 7 || 9 2 5 || 3 8 6 || 
|| 9 8 5 || 3 6 4 || 2 1 7 || 
============================="""
        pretty_print_sudoku(grid)

        # check if the string is in captured default IO output
        self.assertIn(expected, mock_stdout.getvalue())

    @unittest.mock.patch('sys.stdout', new_callable=io.StringIO)
    def test_unfilled(self, mock_stdout):
        grid = [[1, 0, 4, 6, 5, 3, 8, 9, 0],
                [2, 5, 9, 1, 0, 7, 0, 3, 0],
                [8, 3, 6, 4, 9, 2, 5, 7, 0],
                [3, 0, 0, 0, 0, 6, 4, 5, 0],
                [5, 4, 0, 2, 0, 8, 7, 6, 0],
                [7, 0, 0, 5, 0, 9, 1, 2, 0],
                [6, 2, 3, 8, 0, 0, 0, 0, 0],
                [0, 1, 0, 9, 0, 5, 3, 8, 6],
                [9, 8, 5, 3, 0, 4, 2, 1, 7]]
        expected = """=============================
|| 1   4 || 6 5 3 || 8 9   || 
|| 2 5 9 || 1   7 ||   3   || 
|| 8 3 6 || 4 9 2 || 5 7   || 
=============================
|| 3     ||     6 || 4 5   || 
|| 5 4   || 2   8 || 7 6   || 
|| 7     || 5   9 || 1 2   || 
=============================
|| 6 2 3 || 8     ||       || 
||   1   || 9   5 || 3 8 6 || 
|| 9 8 5 || 3   4 || 2 1 7 || 
============================="""
        pretty_print_sudoku(grid)

        # check if the string is in captured default IO output
        self.assertIn(expected, mock_stdout.getvalue())


if __name__ == '__main__':
    # suite just for exercise purposes
    # unittest.main()
    backend_tests = [TestValidNumbers(), TestSolveSudoku()]
    frontend_tests = [TestPrettyPrintSudoku()]
    all_tests = backend_tests + frontend_tests

    TextTestRunner(verbosity=3).run(TestSuite(all_tests))
