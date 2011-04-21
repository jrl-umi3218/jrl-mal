// Copyright 2010 Thomas Moulard.
//
// This file is part of jrl-mathtools.
// jrl-mathtools is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// jrl-mathtools is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// You should have received a copy of the GNU Lesser General Public License
// along with jrl-mathtools.  If not, see <http://www.gnu.org/licenses/>.

#include <jrl/mal/matrixabstractlayer.hh>

#if _BOOST_MATRIX_ == 1
  #define BOOST_TEST_MODULE simple
  #include <boost/test/unit_test.hpp>

  BOOST_AUTO_TEST_CASE (simple)
  {
    //FIXME: add test here.
  }
#elif _EIGEN_MATRIX_ == 1
  int main(){}
  //TODO: add test here too.
#endif
