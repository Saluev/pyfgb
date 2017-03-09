import sys
from Cython.Build import cythonize
from distutils.core import setup
from numpy.distutils.misc_util import get_numpy_include_dirs
from distutils.extension import Extension


ext_modules=[
    Extension("pyfgb",
              sources=["src/pyfgb.pyx", "src/fgb_symbols.c", "src/protocol_maple.c"],
              define_macros=[
                  ("USE_MY_OWN_IO", "1"),
              ],
              extra_compile_args=["-m64", "-Wno-unused-function", "-Wno-macro-redefined", "-fopenmp"],
              extra_link_args=["-fopenmp"],
              include_dirs=["include"] + get_numpy_include_dirs(),
              libraries=["fgb", "fgbexp", "gb", "gbexp", "minpoly", "minpolyvgf", "gmp", "m"],
              library_dirs=[sys.platform],
    )
]

setup(
    name="pyfgb",
    ext_modules=cythonize(ext_modules),
)
