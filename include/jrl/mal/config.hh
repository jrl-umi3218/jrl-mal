// Copyright (C) 2010 Florent Lamiraux, Thomas Moulard, JRL, CNRS/AIST.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef JRL_MAL_CONFIG_HH
# define JRL_MAL_CONFIG_HH

// Package version (header).
# define JRL_MAL_VERSION "1.19.3-6-gd1db"

// Handle portable symbol export.
// Defining manually which symbol should be exported is required
// under Windows whether MinGW or MSVC is used.
//
// The headers then have to be able to work in two different modes:
// - dllexport when one is building the library,
// - dllimport for clients using the library.
//
// On Linux, set the visibility accordingly. If C++ symbol visibility
// is handled by the compiler, see: http://gcc.gnu.org/wiki/Visibility
# if defined _WIN32 || defined __CYGWIN__
// On Microsoft Windows, use dllimport and dllexport to tag symbols.
#  define JRL_MAL_DLLIMPORT __declspec(dllimport)
#  define JRL_MAL_DLLEXPORT __declspec(dllexport)
#  define JRL_MAL_DLLLOCAL
# else
// On Linux, for GCC >= 4, tag symbols using GCC extension.
#  if __GNUC__ >= 4
#   define JRL_MAL_DLLIMPORT __attribute__ ((visibility("default")))
#   define JRL_MAL_DLLEXPORT __attribute__ ((visibility("default")))
#   define JRL_MAL_DLLLOCAL  __attribute__ ((visibility("hidden")))
#  else
// Otherwise (GCC < 4 or another compiler is used), export everything.
#   define JRL_MAL_DLLIMPORT
#   define JRL_MAL_DLLEXPORT
#   define JRL_MAL_DLLLOCAL
#  endif // __GNUC__ >= 4
# endif // defined _WIN32 || defined __CYGWIN__

# ifdef JRL_MAL_STATIC
// If one is using the library statically, get rid of
// extra information.
#  define JRL_MAL_DLLAPI
#  define JRL_MAL_LOCAL
# else
// Depending on whether one is building or using the
// library define DLLAPI to import or export.
#  ifdef jrl_mal_EXPORTS
#   define JRL_MAL_DLLAPI JRL_MAL_DLLEXPORT
#  else
#   define JRL_MAL_DLLAPI JRL_MAL_DLLIMPORT
#  endif // JRL_MAL_EXPORTS
#  define JRL_MAL_LOCAL JRL_MAL_DLLLOCAL
# endif // JRL_MAL_STATIC
#endif //! JRL_MAL_CONFIG_HH
