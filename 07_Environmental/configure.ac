#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([rhasher], [1.0], [...])
AC_CONFIG_SRCDIR([src/rhasher.c])
AM_INIT_AUTOMAKE([foreign subdir-objects])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([rhash], [rhash_library_init], [], [AC_MSG_ERROR([rhash is needed])])
AC_CHECK_LIB([readline], [using_history])

# Checks for header files.
AC_CHECK_HEADERS([RHash/rhash.h])
AC_CHECK_HEADERS([ctype.h])

# Optional clues
AC_ARG_WITH([readline], [AS_HELP_STRING([--enable-readline], [Enable readline library])], [readline_flag="$withval"], [readline_flag="no"])

if test "x$readline_flag" = "xyes"; then
    AC_DEFINE([READLINE], [1], [Check readline access])
    AC_MSG_NOTICE([Use readline lib])
    AC_SUBST([READLINE_LIBS], [-lreadline])
else
    AC_MSG_NOTICE([Without readline library])
fi

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([calloc])
AC_CHECK_FUNCS([strerror])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
