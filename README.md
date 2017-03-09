# pyfgb

This is Python wrapping of [FGb](http://www-polsys.lip6.fr/~jcf/FGb/index.html),
the library for computing Groebner bases written by
[Jean-Charles Faugère](http://www-salsa.lip6.fr/~jcf/) and implementing his F4
and F5 algorithms.

# Making it run

Ensure you have developer's version of GNU MP library and a C/C++ compiler with
OpenMP support (in particular, default Xcode version of clang is not one of
    those; see Troubleshooting section if this is the case).

    # cd to repo folder
    python -m virtualenv venv
    source venv/bin/activate
    pip install sympy numpy cython
    python setup.py install
    python examples/operational_complexity.py  # this may be REALLY slow

# Troubleshooting

You may experience issues if your Python distribution has been compiled as a
"fat binary" (that is, supporing multiple architectures at once) and the GNU MP
library is not. In that case try to install pyfgb like

    ARCHFLAGS="-arch x86_64" python setup.py install

(replace `x86_64` with your machine architecture). You can also specify path to
compiler if your system's default one does not support OpenMP:

    ARCHFLAGS="-arch x86_64" CC=clang LDFLAGS=-L/usr/local/opt/llvm/lib  python setup.py install

# Contributing

This package is a work in progess. In particular, I haven't implemented
returning found Groebner basis polynomials from FGb yet (it currently only
returns the number of elements in basis, which is enough to determine whether
the system of polynomial equations has solution or not).

# Licensing

Everything that regards the Python wrapping is licensed under the MIT license.
However, binaries of the original FGb library (`*.a`) and all `*.h` and `*.c`
files are distributed by Jean-Charles Faugère on unspecified terms, though for
free. Please don't use them in commercial products without contacting him.

-----
Tigran Saluev, 2017.
