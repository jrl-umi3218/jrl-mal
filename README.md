jrl-mal
=======

[![Build Status](https://travis-ci.org/jrl-umi3218/jrl-mal.png)](https://travis-ci.org/jrl-umi3218/jrl-mal)
[![Coverage Status](https://coveralls.io/repos/jrl-umi3218/jrl-mal/badge.png?branch=master)](https://coveralls.io/r/jrl-umi3218/jrl-mal?branch=master)

![LGPL-3](https://www.gnu.org/graphics/lgplv3-88x31.png)


This library has been designed to allow algorithms to communicate with
different frameworks using different matrix types without the cost of
a copy to convert from one type to another one.

Please note that *the direct use of Boost.uBLAS is prefered* to the
use of this compatibility layer when possible. Boost.uBLAS is the
reference matrix library at JRL and in the GEPETTO group at LAAS-CNRS.


It is released under the [LGPL-3](COPYING.LESSER) license.


**Warning:** this repository contains [Git
submodules][git-submodules]. Please clone this repository using the
`git clone --recursive` command. If you already have cloned the
repository, you can run `git submodule init && git submodule update`
to retrieve the submodules.


Documentation
-------------

To get started with this library, please read the [online Doxygen
documentation][doxygen-documentation].

It can also be generated locally by running the `make doc`
command. After the package is installed, the documentation will be
located in the `$prefix/share/doc/jrl-mal` directoy where
`$prefix` is your installation prefix (`/usr/local` by default).


Getting Help
------------

Support is provided through:
 * the HPP mailing-list: hpp@laas.fr
 * the following HipChat room: http://www.hipchat.com/gh4wQrZeV


How can I install jrl-mal?
--------------------------

### Installing dependencies

The matrix abstract layer depends on several packages which
have to be available on your machine.

 - Libraries:
   - [Boost][] (>= 1.40)
     Its detection is controled by the `BOOST_ROOT` variable, see next section
     for more information.
   - [Eigen][]
     Eigen can be used instead of uBlas but is currently an experimental feature.
   - [Lapack][] library
     Use the generic purpose `CMAKE_CXX_FLAGS` and `CMAKE_EXE_LINKER_FLAGS`
     to insert the flags required for the compiler to find your Lapack library
     if it is installed in a non-standard directory.
   - [jrl-mathtools][] or [t3d][] are two small-matrices libraries which can be
     used by jrl-mal. You *will* have to install either one of these two libraries.
	 We recommend you to use [jrl-mathtools][].
 - System tools:
   - [CMake][] (>=2.6)
   - [pkg-config][]
   - usual compilation tools (GCC/G++, make, etc.)
     If you are using Ubuntu, these tools are gathered in the `build-essential` package.


### Compiling and installing the package

The manual compilation requires two steps:

 1. configuration of the build and generation of the build files
 2. compilation of the sources and installation of the package

jrl-mal uses [CMake][] to generate build files. It is
recommended to create a separate build directory:

```sh
mkdir _build         # (1) Create a build directory
cd _build            # (2) Go to the newly created build directory
cmake [options] ..   # (3) Generate the build files
```

Options which can be passed to CMake are detailed in the next section.

```sh
make                 # (4) Compile the package
make test            # (5) Execute the package tests
make install         # (6) Install the package into the prefix (see step 3)
```


### Options

Additional options can be set on the command line through the
following command: `-D<option>=<value>`.

For instance: `cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo ..` will set
the `CMAKE_BUILD_TYPE` option to the value `RelWithDebInfo`.


Available options are:

- `CMAKE_BUILD_TYPE` set the build profile that should be used (debug,
  release, etc.). We recommend `RelWithDebInfo` as it will provide
  performances while keeping debugging symbols enabled.
- `CMAKE_INSTALL_PREFIX` set the installation prefix (the directory
  where the software will be copied to after it has been compiled).
- `SMALLMATRIX` defines which small matrix library will be used.
  Values can either be `jrl-mathtools` or `t3d`.
- `LINEAR_ALGEBRA_LIB` defines which linear algebra library will be
  used. Values can either be `boost` or `eigen`. `eigen` version is
  currently in development and is not recommended currently. It will,
  however, replace the Boost version using uBals eventually.

### Running the test suite

The test suite can be run from your build directory by running:

```sh
   make test
```

Please open a ticket if some tests are failing on your computer, it
should not be the case.


Contributing
------------

If you want to contribute, please refer to the
[CONTRIBUTING.md](CONTRIBUTING.md) file

Credits
-------

This package authors are credited in the [AUTHORS](AUTHORS) file.


[doxygen-documentation]: http://jrl-umi3218.github.io/jrl-mal/doxygen/HEAD/

[jrl-mathtools]: https://github.com/jrl-umi3218/jrl-mathtools

[git-submodules]: http://git-scm.com/book/en/Git-Tools-Submodules

[Boost]: http://www.boost.org/
[CMake]: htttp://www.cmake.org/
[Doxygen]: http://www.stack.nl/~dimitri/doxygen/
[Eigen]: http://eigen.tuxfamily.org/
[Git]: http://git-scm.com/
[Lapack]: http://www.netlib.org/lapack/
[Libtool]: https://www.gnu.org/software/libtool/
[RobotPkg]: http://robotpkg.openrobots.org/
[log4cxx]: https://logging.apache.org/log4cxx/
[pkg-config]: http://www.freedesktop.org/wiki/Software/pkg-config/
