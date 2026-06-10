import sys
from setuptools import setup, Extension
from Cython.Build import cythonize
import numpy as np

if sys.platform == "win32":
    extra_c_comp_args = ["/O2", "/arch:AVX2", "/fp:fast"]
elif sys.platform == "darwin":
    extra_c_comp_args = ["-std=c11", "-O3", "-ffast-math"]
else:
    extra_c_comp_args = ["-std=c11", "-O3", "-march=native", "-ffast-math"]

ext_module = Extension(
    name="xgsimulation",
    sources=[
        "xgsimulation.pyx",
        "src/c/geometry.c",
        "src/c/football.c",
        "src/c/random_number.c",
        "src/c/simulation.c",
    ],
    include_dirs=[
        "src/c",
        np.get_include(),
    ],
    extra_compile_args=extra_c_comp_args
)

setup(
    ext_modules=cythonize([ext_module], language_level=3),
)