from pyfgb import FGB
from sympy import symbols, Poly, groebner


def _make_sum(prefix, variables):
    return reduce(lambda a, b: a + b, (
        symbols("{prefix}_{variable.name}".format(prefix=prefix, variable=variable)) * variable
        for variable in variables
    ), 0)


def _make_multiplier(prefix, variables, prev_results):
    multiplier \
        = _make_sum(prefix, variables) \
        + _make_sum(prefix, prev_results) \
        + symbols(prefix)
    return multiplier


def get_algorithm_conditions(polynomials, steps):
    variables = set()
    for polynomial in polynomials:
        variables.update(polynomial.free_symbols)
    variables = list(variables)
    substitutions = []
    step_results = []
    conditions = []
    for step in range(steps):
        left_multiplier = _make_multiplier("l_%d" % step, variables, step_results)
        right_multiplier = _make_multiplier("r_%d" % step, variables, step_results)
        step_result = symbols("s_{step}".format(step=step))
        condition = (left_multiplier * right_multiplier).expand()
        substitutions.append([step_result, condition])
        step_results.append(step_result)
    final_results = []
    for i, polynomial in enumerate(polynomials):
        condition = _make_multiplier("f_%d" % i, variables, step_results) - polynomial
        for substitution in reversed(substitutions):
            condition = condition.subs(*substitution).expand()
        condition = condition.collect(variables)
        poly = Poly(condition, variables)
        conditions.extend(poly.coeffs())
    #for condition in conditions:
    #    print condition
    return conditions

def is_computible(polynomials, steps):
    conditions = get_algorithm_conditions(polynomials, steps)
    coefficients = set()
    for condition in conditions:
        coefficients.update(condition.free_symbols)
    basis = groebner(conditions, coefficients, order="grevlex")
    return all(element != 1 for element in basis)

def is_computible_fgb(polynomials, steps):
    fgb = FGB()
    conditions = get_algorithm_conditions(polynomials, steps)
    num_polys = fgb.groebner(conditions)
    return num_polys > 1

if __name__ == "__main__":
    x, y = symbols("x y")
    expression = x ** 4
    print("Is x**4 computable with 1 multiplication (sympy): %s" % is_computible([expression], 1))
    print("Is x**4 computable with 2 multiplications (FGb): %s" % is_computible_fgb([expression], 2))
