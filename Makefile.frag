%.c: %.y
%.c: %.l

$(builddir)/src/cql_lexer.lo: $(srcdir)/src/cql_parser.h

$(srcdir)/src/cql_lexer.c: $(srcdir)/src/cql_lexer.l
	@(cd $(top_srcdir); $(RE2C) $(RE2C_FLAGS) --no-generation-date -cbFo $(srcdir)/src/cql_lexer.c $(srcdir)/src/cql_lexer.l)

$(srcdir)/src/cql_parser.h: $(srcdir)/src/cql_parser.c
$(srcdir)/src/cql_parser.c: $(srcdir)/src/cql_parser.y
	$(YACC) -p cql_ -v -d $(srcdir)/src/cql_parser.y -o $@

cmark-test-coverage:
	CCACHE_DISABLE=1 EXTRA_CFLAGS="-fprofile-arcs -ftest-coverage" TEST_PHP_ARGS="-q" $(MAKE) clean test

cmark-test-coverage-lcov: cmark-test-coverage
	lcov -c --directory $(top_srcdir)/src/.libs --output-file $(top_srcdir)/coverage.info

cmark-test-coverage-html: cmark-test-coverage-lcov
	genhtml $(top_srcdir)/coverage.info --output-directory=$(top_srcdir)/html

cmark-test-coverage-travis:
	CCACHE_DISABLE=1 EXTRA_CFLAGS="-fprofile-arcs -ftest-coverage" $(MAKE)
