jrl-mal
=======

This software provides abstraction of the matrix representation and by
consequence of the matrix manipulation library.

This library has been designed to allow algorithms to communicate with
different frameworks using different matrix types without the cost of
a copy to convert from one type to another one.

Please note that *the direct use of Boost.uBLAS is prefered* to the
use of this compatibility layer when possible. Boost.uBLAS is the
reference matrix library at JRL and in the GEPETTO group at LAAS-CNRS.


Setup
-----

To compile this package, it is recommended to create a separate build
directory:

    mkdir _build
    cd _build
    cmake [OPTIONS] ..
    make install

Please note that CMake produces a `CMakeCache.txt` file which should
be deleted to reconfigure a package from scratch.


### Dependencies

The matrix abstract layer depends on several packages which
have to be available on your machine.

 - Libraries:
  - Boost (>= 1.33.1)
    Its detection is controled by the `BOOST_ROOT` variable, see next section
    for more information.
  - Lapack library
    Use the generic purpose `CMAKE_CXX_FLAGS` and `CMAKE_EXE_LINKER_FLAGS`
    to insert the flags required for the compiler to find your Lapack library
    if it is installed in a non-standard directory.
  - t3d or [jrl-mathtools][jrl-mathtools] (through pkg-config).
    One of these two small matrix manipulation library can be used. They
    are both shipped with a pkg-config file which is used for their detection.
    Make sure your `PKG_CONFIG_PATH` is correct if CMake cannot detect them.
 - System tools:
  - CMake (>=2.6)
  - pkg-config
  - usual compilation tools (GCC/G++, make, etc.)


### Options

 - the `BOOST_ROOT` option forces CMake to search for Boost in a non-standard
   directory.
 - the `SMALLMATRIX` option allows two values:
    - `t3d`
    - `jrlMathTools`
   ...depending on what library will be used to handle small matrices.
 - `BLAS_LIBRARIES` is the path to the BLAS library.
 - `BOOSTNUMERICBINDINGS_DIR` is the path to the Boost numeric bindings
    library[1].

[1] Boost numeric bindings have been merged into Boost uBLAS in Boost
1.41. By consequence, if your Boost version is newer than 1.41, you
should ignore this option.


Testing
-------

To run the test suite, please type:

    ctest -E experimental


[jrl-mathtools]: http://github.com/jrl-umi3218/jrl-mathtools "jrl-mathtools"
