AC_INIT([kleuren], [0.0.1], [cole@colelyman.com])
m4_ifdef([AM_PROG_AR], [AM_PROG_AR])
LT_INIT
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
INC_CPPFLAGS="-I./inc -I./thirdparty/dbgfm -I./thirdparty/cxxopts/include"
AC_SUBST(INC_CPPFLAGS)
AC_CONFIG_SRCDIR([src])
AC_CONFIG_MACRO_DIR([m4])
CXXFLAGS="$CXXFLAGS -std=c++11"
AC_PROG_CXX
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
