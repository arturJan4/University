import itertools
from abc import ABC, abstractmethod


class DefinitionError(Exception):
    def __init__(self, val, message=None):
        if message is None:
            message = f"variable <{val}> is not defined in variables assignment dictionary."
        super().__init__(message)


class MisleadingNameError(Exception):
    pass


# Formulas are defined inductively as either:
# - a variable -> to which we can assign True/False
# - a const -> True/False
# - unary operator applied to 1 formula
# - binary operator applied to 2 formulas

class Formula(ABC):
    @abstractmethod
    def evaluate(self, variables={}):
        """Evaluates given formula using variables to a boolean value"""
        pass

    @abstractmethod
    def get_variables(self):
        """:returns a lists of all variables used in a formula"""
        pass

    @abstractmethod
    def simplify(self):
        """:returns formula simplified by application of logic laws"""
        pass

    def __str__(self):
        """
        Uses parentheses to signify order of operations following the logic formula
        decomposition to a binary tree (operators are internal nodes, leaves are consts and variables).
        :returns string representation of formula
        """
        return str(self)

    def __add__(self, other):
        """f1 + f2 == f1 ∨ f2"""
        return Or(self, other)

    def __mul__(self, other):
        """f1 * f2 == f1 ∧ f2"""
        return And(self, other)

    def __invert__(self):
        """~f = ¬f"""
        return Not(self)

    def __rshift__(self, other):
        """f1 → f2 == f1 >> f2"""
        return Imp(self, other)

    @staticmethod
    def tautology(formula):
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
    Represents a variable with given name
    """
    def __init__(self, val):
        if isinstance(val, str):
            if val.strip().lower() in ["true", "false"]:
                raise MisleadingNameError("misleading variable name, use Const instead to define Truth/False")
            self.val = val
        else:
            raise TypeError("variable name should be a string")

    def __str__(self):
        return self.val

    def evaluate(self, variables=None):
        """:arg variables: is a dict of variable:boolean pairs"""
        if variables is None:  # because of mutability of dict
            variables = {}

        try:
            dict_value = variables[self.val]
        except KeyError as inst:
            print(inst)
            raise DefinitionError(val=self.val)

        return Const(dict_value).evaluate()

    def get_variables(self):
        return [self.val]

    def simplify(self):
        return self


def Const(val=None):
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

    def __init__(self, formula):
        if type(self) == Unop:
            raise Exception("Unop must be subclassed.")

        self.formula = formula

    def evaluate(self, variables=None):
        pass

    def __str__(self):
        if isinstance(self.formula, (TrueConst, FalseConst, Var)):
            return self.symbol + str(self.formula)
        else:
            return self.symbol + "(" + str(self.formula) + ")"

    def get_variables(self):
        return self.formula.get_variables()

    def simplify(self):
        return self


class Binop(Formula, ABC):
    """Binary operations (form1 <symbol> form2)"""
    symbol = "<default symbol>"

    def __init__(self, form1, form2):
        if type(self) == Binop:
            raise Exception("Binop must be subclassed.")

        self.form1 = form1
        self.form2 = form2

    def evaluate(self, variables=None):
        self.evaluate(variables)

    def get_variables(self):
        return self.form1.get_variables() + self.form2.get_variables()

    def simplify(self):
        return self

    def __str__(self):
        str_form1 = str(self.form1)
        str_form2 = str(self.form2)

        if not isinstance(self.form1, (TrueConst, FalseConst, Var, Unop)):
            str_form1 = "(" + str_form1 + ")"

        if not isinstance(self.form2, (TrueConst, FalseConst, Var, Unop)):
            str_form2 = "(" + str_form2 + ")"

        return str_form1 + " " + self.symbol + " " + str_form2


class BoolConst(Formula, ABC):
    def __init__(self):
        if type(self) == BoolConst:
            raise Exception("BoolConst must be subclassed.")

    def simplify(self):
        return self

    def get_variables(self):
        return []

    def __eq__(self, other):
        return type(self) == type(other)


class TrueConst(BoolConst):
    def __str__(self):
        return "⊤"

    def evaluate(self, variables=None):
        return True


class FalseConst(BoolConst):
    def __str__(self):
        return "⊥"

    def evaluate(self, variables=None):
        return False


class Not(Unop):
    symbol = "¬"

    def evaluate(self, variables=None):
        if variables is None:
            variables = {}
        return not self.formula.evaluate(variables)


class Or(Binop):
    symbol = '∨'

    def __init__(self, form1, form2):
        super().__init__(form1, form2)

    def evaluate(self, variables=None):
        if variables is None:
            variables = {}

        return self.form1.evaluate(variables) or self.form2.evaluate(variables)

    def simplify(self):
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
    symbol = '∧'

    def evaluate(self, variables=None):
        if variables is None:
            variables = {}

        return self.form1.evaluate(variables) and self.form2.evaluate(variables)

    def simplify(self):
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
    symbol = '→'

    def evaluate(self, variables=None):
        if variables is None:
            variables = {}
        # using logical equivalence
        return not self.form1.evaluate(variables) or self.form2.evaluate(variables)

    def simplify(self):
        form1 = self.form1.simplify()
        form2 = self.form2.simplify()

        if isinstance(form1, FalseConst):
            return TrueConst()
        if isinstance(form1, TrueConst):
            return form2

        return self