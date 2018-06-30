dnl config.m4 for extension cmark

PHP_ARG_WITH(cmark, whether to enable cmark support,
dnl Make sure that the comment is aligned:
[  --with-cmark            Enable cmark support], no)

LIBCMARK_MIN_MAJOR=0
LIBCMARK_MIN_MINOR=28

if test "$PHP_CMARK" != "no"; then
  AC_PROG_YACC
  PHP_SUBST(YACC)

  LIBCMARK_VERSON=""
  LIBNAME=cmark
  LIBSYMBOL=cmark_markdown_to_html

  dnl try pkgconfig if no path provided
  if test "$PHP_CMARK" = "yes"; then
    AC_PATH_PROG(PKG_CONFIG, pkg-config, no)
    AC_MSG_CHECKING(for libcmark)
    if test -x "$PKG_CONFIG" && $PKG_CONFIG --exists libcmark; then
      if $PKG_CONFIG libcmark --atleast-version $LIBCMARK_MIN_MAJOR.$LIBCMARK_MIN_MINOR; then
        LIBCMARK_CFLAGS=`$PKG_CONFIG libcmark --cflags`
        LIBCMARK_LIBDIR=`$PKG_CONFIG libcmark --libs`
        LIBCMARK_VERSON=`$PKG_CONFIG libcmark --modversion`
        AC_MSG_RESULT(from pkgconfig: version $LIBCMARK_VERSON)
      else
        AC_MSG_ERROR(system libcmark is too old: version $LIBCMARK_MIN_MAJOR.$LIBCMARK_MIN_MINOR required)
      fi
    fi
    PHP_EVAL_LIBLINE($LIBCMARK_LIBDIR, CMARK_SHARED_LIBADD)
    PHP_EVAL_INCLINE($LIBCMARK_CFLAGS)

    dnl check symbol, can probably be removed, if minimal version is properly set
    PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
    [
      AC_DEFINE(HAVE_CMARKLIB,1,[ ])
    ],[
      AC_MSG_ERROR([wrong cmark lib version or lib not found])
    ],[
      $CMARK_SHARED_LIBADD
    ])
  fi

  dnl fallback on patch search
  if test -z "$LIBCMARK_VERSON"; then
    AC_MSG_CHECKING(for libcmark headers)
    SEARCH_PATH="/usr/local /usr"
    SEARCH_FOR="/include/cmark.h"
    if test -r $PHP_CMARK/$SEARCH_FOR; then
      CMARK_DIR=$PHP_CMARK
    else
      AC_MSG_CHECKING([for cmark files in default path])
      for i in $SEARCH_PATH ; do
        if test -r $i/$SEARCH_FOR; then
          CMARK_DIR=$i
        fi
      done
    fi

    if test -n "$CMARK_DIR"; then
      AC_MSG_RESULT(found in $CMARK_DIR/include)
    else
      AC_MSG_RESULT([not found $CMARK_DIR])
      AC_MSG_ERROR([Please reinstall the cmark distribution])
    fi
    PHP_ADD_INCLUDE($CMARK_DIR/include)

    PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
    [
      PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $CMARK_DIR/$PHP_LIBDIR, CMARK_SHARED_LIBADD)
      AC_DEFINE(HAVE_CMARKLIB,1,[ ])
    ],[
      AC_MSG_ERROR([wrong cmark lib version or lib not found])
    ],[
      -L$CMARK_DIR/$PHP_LIBDIR -lm
    ])

    AC_MSG_CHECKING([for cmark minimal version])
    old_CFLAGS=$CFLAGS
    CFLAGS="-I$CMARK_DIR/include"
    AC_TRY_RUN([
#include <cmark.h>
int main() {
  return (CMARK_VERSION < (($LIBCMARK_MIN_MAJOR << 16) | ($LIBCMARK_MIN_MINOR << 8)) ? 1 : 0);
}
    ], [
      AC_MSG_RESULT([ok])
    ], [
      AC_MSG_ERROR(system libcmark is too old: version 0.28 required)
    ])
    CFLAGS=$old_CFLAGS
  fi

  PHP_SUBST(CMARK_SHARED_LIBADD)

  PHP_ADD_BUILD_DIR($abs_builddir/src)
  PHP_ADD_INCLUDE($ext_srcdir)

  AC_DEFINE(HAVE_CMARK, 1, [ Have cmark support ])

  PHP_NEW_EXTENSION(cmark, cmark.c src/node.c src/handlers.c src/custom.c src/visitor.c src/document.c src/quote.c src/list.c src/item.c src/block.c src/paragraph.c src/heading.c src/break.c src/text.c src/code.c src/inline.c src/media.c src/render.c src/parse.c src/iterator.c src/cql_lexer.c src/cql_parser.c src/call.c src/cql.c, $ext_shared)

  PHP_ADD_MAKEFILE_FRAGMENT
fi
