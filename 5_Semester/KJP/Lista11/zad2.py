# lista 11 (5 zad 2)

# docs generation:
# "pydoc3 -w zad2" or "python<version> -m pydoc -w zad2"

import itertools
from typing import Union, Dict, List
from abc import ABC, abstractmethod


class DefinitionError(Exception):
    """Thrown when variable was not defined before it's usage."""
    def __init__(self, val: Union[str, None], message: Union[str, None] = None):
        if message is None:
            message = f"variable <{val}> is not defined in variables assignment dictionary."
        super().__init__(message)


class MisleadingNameError(Exception):
    """Empty wrapper"""
    pass


class Formula(ABC):
    """
    Abstract method encompassing all formulas.
    Formulas are defined inductively as either:
     - a variable -> to which we can assign True/False
     - a const -> True/False
     - unary operator applied to 1 formula
     - binary operator applied to 2 formulas
    """
    @abstractmethod
    def evaluate(self, variables: Dict[str, bool] = {}) -> bool:
        """:returns evaluation of given formula using variables to a boolean value"""
        pass

    @abstractmethod
    def get_variables(self):
        """:returns a lists of all variables used in a formula"""
        pass

    @abstractmethod
    def simplify(self):
        """:returns formula simplified by application of logic laws"""
        pass

    def __str__(self) -> str:
        """
        Uses parentheses to signify order of operations following the logic formula decomposition to a binary tree
        (operators are internal nodes, leaves are consts and variables).
        :returns string representation of formula
        """
        return str(self)

    def __add__(self, other: 'Formula') -> 'Formula':
        """f1 + f2 == f1 ∨ f2"""
        return Or(self, other)

    def __mul__(self, other: 'Formula') -> 'Formula':
        """f1 * f2 == f1 ∧ f2"""
        return And(self, other)

    def __invert__(self) -> 'Formula':
        """~f == ¬f"""
        return Not(self)

    def __rshift__(self, other: 'Formula') -> 'Formula':
        """f1 → f2 == f1 >> f2"""
        return Imp(self, other)

    @staticmethod
    def tautology(formula: 'Formula') -> str:
        """checks if given formula is a true for all assignments of variables"""
        variables = formula.get_variables()
        possible_values = [True, False]

        # check every permutation of True/False assignment for vars
        assignments = itertools.product(possible_values, repeat=len(variables))
        for assign in assignments:
            vars_dict = dict()

            for i, key in enumerate(variables):
                vars_dict[key] = assign[i]  # create a variables dictionary

            if not formula.evaluate(vars_dict):
                return "Formula is not a tautology."

        return "Formula is a tautology."


class Var(Formula):
    """
    Represents a variable with given name.
    """
    def __init__(self, val: str) -> None:
        if isinstance(val, str):
            if val.strip().lower() in ["true", "false"]:
                raise MisleadingNameError("misleading variable name, use Const instead to define Truth/False")
            self.val = val
        else:
            raise TypeError("variable name should be a string")

    def __str__(self) -> str:
        return self.val

    def evaluate(self, variables: Dict[str, bool] = None) -> bool:
        """:arg variables: is a dict of variable:boolean pairs"""
        if variables is None:  # because of mutability of dict
            variables = {}

        try:
            dict_value = variables[self.val]
        except KeyError as inst:
            print(inst)
            raise DefinitionError(val=self.val)

        return Const(dict_value).evaluate()

    def get_variables(self) -> List[str]:
        """List of only one variable."""
        return [self.val]

    def simplify(self) -> Formula:
        """Cannot simplify further."""
        return self


def Const(val: Union[str, bool, int] = None) -> Union['TrueConst', 'FalseConst']:
    """
    Const values are either True or False
    Factory pattern -> Const creates objects of TrueConst or FalseConst types.
    This makes it easier to differentiate them, with just __eq__ method.
    """
    # user entered string
    if isinstance(val, str):
        if val.strip().lower() == "true":
            return TrueConst()
        elif val.strip().lower() == "false":
            return FalseConst()

    # user entered boolean value
    if isinstance(val, bool):
        if val:
            return TrueConst()
        else:
            return FalseConst()

    # user entered a number 0/1
    if isinstance(val, int):
        if val == 1:
            return TrueConst()
        elif val == 0:
            return FalseConst()

    raise KeyError(f"Const accepts string or boolean values or 0/1, received {val}")


class Unop(Formula, ABC):
    """Unary operations (e.g. !f)"""
    symbol = "<default symbol>"

    def __init__(self, formula: Formula) -> None:
        if type(self) == Unop:
            raise Exception("Unop must be subclassed.")

        self.formula = formula

    def evaluate(self, variables: Dict[str, bool] = None) -> None:
        """Evaluation is not needed in the parent class."""
        pass

    def __str__(self) -> str:
        if isinstance(self.formula, (TrueConst, FalseConst, Var)):
            return self.symbol + str(self.formula)
        else:
            return self.symbol + "(" + str(self.formula) + ")"

    def get_variables(self) -> None:
        """Get variables from underlying formula (in an universal way)."""
        return self.formula.get_variables()

    def simplify(self) -> 'Unop':
        """Cannot simplify unary operation (not knowing which one is it)."""
        return self


class Binop(Formula, ABC):
    """Binary operations (form1 <symbol> form2)"""
    symbol = "<default symbol>"

    def __init__(self, form1: Formula, form2: Formula) -> None:
        if type(self) == Binop:
            raise Exception("Binop must be subclassed.")

        self.form1 = form1
        self.form2 = form2

    def evaluate(self, variables: Dict[str, bool] = None) -> bool:
        """Binop's are not evaluated directly."""
        pass

    def get_variables(self) -> List[str]:
        """Binop has two formulas so just recursively concatenate two lists."""
        return self.form1.get_variables() + self.form2.get_variables()

    def simplify(self) -> Formula:
        """No universal rules for simplification of Binop's."""
        return self

    def __str__(self) -> str:
        """
        Use some evaluation order inference to limit number of '(' and ')' symbols.
        :return: string representation of formula without too much parentheses
        """
        str_form1 = str(self.form1)
        str_form2 = str(self.form2)

        if not isinstance(self.form1, (TrueConst, FalseConst, Var, Unop)):
            str_form1 = "(" + str_form1 + ")"

        if not isinstance(self.form2, (TrueConst, FalseConst, Var, Unop)):
            str_form2 = "(" + str_form2 + ")"

        return str_form1 + " " + self.symbol + " " + str_form2


class BoolConst(Formula, ABC):
    """
    Abstract type for own Boolean values.
    We want the Truth and Falsehood to be of different types.
    We also want to separate from Python's True/False boolean values.
    """
    def __init__(self) -> None:
        if type(self) == BoolConst:
            raise Exception("BoolConst must be subclassed.")

    def simplify(self) -> Formula:
        """Cannot be simplified further."""
        return self

    def get_variables(self) -> List:
        """Boolean is not a variable."""
        return []

    def __eq__(self, other: Formula) -> bool:
        return type(self) == type(other)


class TrueConst(BoolConst):
    """Specific type representing true values."""
    def __str__(self) -> str:
        return "⊤"

    def evaluate(self, variables: Dict[str, bool] = None) -> bool:
        """Translate own boolean true to Python's type system."""
        return True


class FalseConst(BoolConst):
    """Specific type representing false values."""
    def __str__(self) -> str:
        return "⊥"

    def evaluate(self, variables: Dict[str, bool] = None) -> bool:
        """Translate own boolean false to Python's type system."""
        return False


class Not(Unop):
    """Unary operator negating value of encompassed formula."""
    symbol = "¬"

    def evaluate(self, variables: Dict[str, bool] = None) -> bool:
        """Evaluate recursively and then 'not' result using Python's logic."""
        if variables is None:
            variables = {}
        return not self.formula.evaluate(variables)


class Or(Binop):
    """Represents typical or operator (at least one preposition must be true).
    0 ∨ 1 == True
    0 ∨ 0 == False
    1 ∨ 1 == True
    1 ∨ 0 == True
    """
    symbol = '∨'

    def __init__(self, form1, form2):
        super().__init__(form1, form2)

    def evaluate(self, variables: Dict[str, bool] = None):
        """Evaluate both formulas recursively and then use Python's inbuilt or operator."""
        if variables is None:
            variables = {}

        return self.form1.evaluate(variables) or self.form2.evaluate(variables)

    def simplify(self) -> Formula:
        """
        Using two rules (and mirrored versions).
        False ∨ a == a
        True  ∨ a == True
        """
        form1 = self.form1.simplify()
        form2 = self.form2.simplify()

        if isinstance(form1, FalseConst):
            return form2
        if isinstance(form1, TrueConst):
            return TrueConst()
        if isinstance(form2, FalseConst):
            return form1
        if isinstance(form2, TrueConst):
            return TrueConst()

        return self


class And(Binop):
    """Represents typical and operator (both prepositions must be true).
    0 ∧ 1 == False
    0 ∧ 0 == False
    1 ∧ 1 == True
    1 ∧ 0 == False
    """
    symbol = '∧'

    def evaluate(self, variables: Dict[str, bool] = None) -> bool:
        """Evaluate both formulas recursively and then use Python's inbuilt and operator."""
        if variables is None:
            variables = {}

        return self.form1.evaluate(variables) and self.form2.evaluate(variables)

    def simplify(self) -> Formula:
        """
        Using two rules (and mirrored versions).
        False ∧ a == False
        True  ∧ a == a
        """
        form1 = self.form1.simplify()
        form2 = self.form2.simplify()

        if isinstance(form1, FalseConst):
            return FalseConst()
        if isinstance(form1, TrueConst):
            return form2
        if isinstance(form2, FalseConst):
            return FalseConst()
        if isinstance(form2, TrueConst):
            return form1

        return self


class Imp(Binop):
    """
    Represents typical implication.
    0 → 1 == True
    0 → 0 == True
    1 → 1 == True
    1 → 0 == False
    """
    symbol = '→'

    def evaluate(self, variables: Dict[str, bool] = None) -> bool:
        """
        using logic rules: a -> b === ~a v b
        :param variables: dict of 'var name': 'var bool value'
        :return: boolean value of evaluated formula
        """
        if variables is None:
            variables = {}
        # using logical equivalence
        return not self.form1.evaluate(variables) or self.form2.evaluate(variables)

    def simplify(self) -> Formula:
        """
        1) If assumption is false then implication always evaluates to truth.
        2) If assumption is true then boolean value of formula depends only on the consequence.
        :return: simplified implication formula
        """
        form1 = self.form1.simplify()
        form2 = self.form2.simplify()

        if isinstance(form1, FalseConst):
            return TrueConst()
        if isinstance(form1, TrueConst):
            return form2

        return self
