from itertools import product, combinations, izip
from sympy import symbols, Poly, groebner
from pyfgb import FGB

def _make_operand(prefix, values, conditions):
    coefficients = [
        symbols("{prefix}_{value.name}".format(prefix=prefix, value=value))
        for value in values
    ]
    free_coefficient = symbols("{prefix}_const".format(prefix=prefix))
    operand = reduce(lambda a, b: a + b, (
        coef * value for coef, value in zip(coefficients, values)
    ), 0) + free_coefficient
    coefficients.append(free_coefficient)
    for c1, c2 in combinations(coefficients, 2):
        conditions.append(c1 * c2)
    return operand

def get_algorithm_conditions(polynomials, steps):
    assert(steps >= len(polynomials))
    variables = set()
    for polynomial in polynomials:
        variables.update(polynomial.free_symbols)
    variables = list(variables)
    for operations in product(["+", "*"], repeat=steps):
        substitutions = []
        conditions = []
        step_results = []
        for step, operation in enumerate(operations):
            computed_values = variables + step_results
            left_operand = _make_operand("l_%d" % step, computed_values, conditions)
            right_operand = _make_operand("r_%d" % step, computed_values, conditions)
            step_result = symbols("s_%d" % step)
            if operation == "*":
                rhs = (left_operand * right_operand).expand()
            elif operation == "+":
                rhs = left_operand + right_operand
            substitutions.append([step_result, rhs])
            step_results.append(step_result)
        for polynomial, step_result in izip(polynomials, reversed(step_results)):
            condition = step_result - polynomial
            for substitution in reversed(substitutions):
                condition = condition.subs(*substitution).expand()
            condition = condition.collect(variables)
            poly = Poly(condition, variables)
            conditions.extend(poly.coeffs())
        yield operations, conditions

def is_computible(polynomials, steps):
    for operations, conditions in get_algorithm_conditions(polynomials, steps):
        coefficients = set()
        for condition in conditions:
            #print condition
            coefficients.update(condition.free_symbols)
        basis = groebner(conditions, coefficients, order="grevlex")
        if all(element != 1 for element in basis):
            print("Succeded with following operations order: %s" % " ".join(operations))
            return True
    return False

def is_computible_fgb(polynomials, steps):
    fgb = FGB()
    for operations, conditions in get_algorithm_conditions(polynomials, steps):
        num_polys = fgb.groebner(conditions)
        if num_polys > 1:
            print("Succeded with following operations order: %s" % " ".join(operations))
            return True
    return False

if __name__ == "__main__":
    x, y = symbols("x y")
    expression = x ** 32
    print("Is x**32 computable with 2 operations (sympy): %s" % is_computible([expression], 2))
    print("Is x**32 computable with 3 operations (FGb): %s" % is_computible_fgb([expression], 3))
