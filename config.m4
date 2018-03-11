dnl $Id$
dnl config.m4 for extension cmark

PHP_ARG_WITH(cmark, whether to enable cmark support,
dnl Make sure that the comment is aligned:
[  --with-cmark          Enable cmark support], no)

if test "$PHP_CMARK" != "no"; then
  SEARCH_PATH="/usr/local /usr"
  SEARCH_FOR="/include/cmark.h"
  if test -r $PHP_CMARK/$SEARCH_FOR; then
    CMARK_DIR=$PHP_CMARK
  else
    AC_MSG_CHECKING([for cmark files in default path])
    for i in $SEARCH_PATH ; do
      if test -r $i/$SEARCH_FOR; then
        CMARK_DIR=$i
        AC_MSG_RESULT(found in $i)
      fi
    done
  fi

  if test -z "$CMARK_DIR"; then
    AC_MSG_RESULT([not found])
    AC_MSG_ERROR([Please reinstall the cmark distribution])
  fi

  PHP_ADD_INCLUDE($CMARK_DIR/include)

  # --with-cmark -> check for lib and symbol presence
  LIBNAME=cmark
  LIBSYMBOL=cmark_markdown_to_html

  PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  [
    PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $CMARK_DIR/$PHP_LIBDIR, CMARK_SHARED_LIBADD)
    AC_DEFINE(HAVE_CMARKLIB,1,[ ])
  ],[
    AC_MSG_ERROR([wrong cmark lib version or lib not found])
  ],[
    -L$CMARK_DIR/$PHP_LIBDIR -lm
  ])
  dnl
  PHP_SUBST(CMARK_SHARED_LIBADD)

  PHP_ADD_BUILD_DIR($ext_builddir/src)
  PHP_ADD_INCLUDE($ext_builddir)

  AC_DEFINE(HAVE_CMARK, 1, [ Have cmark support ])

  PHP_NEW_EXTENSION(cmark, cmark.c src/node.c src/document.c src/quote.c src/list.c src/item.c src/block.c src/paragraph.c src/heading.c src/break.c src/text.c src/code.c src/inline.c src/media.c src/render.c src/parse.c, $ext_shared)
fi
