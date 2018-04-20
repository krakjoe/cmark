/*
  +----------------------------------------------------------------------+
  | cmark                                                                |
  +----------------------------------------------------------------------+
  | Copyright (c) Joe Watkins 2018                                       |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: krakjoe <krakjoe@php.net>                                    |
  +----------------------------------------------------------------------+
 */
#ifndef PHP_CMARK_CQL_LEXER_H
#define PHP_CMARK_CQL_LEXER_H

#include <src/cql.h>

typedef struct _cql_lex_t cql_lex_t;

cql_lex_t* cql_lex_init (unsigned char *text, size_t length);
int cql_lex (cql_ast_t *yylval, cql_lex_t *lex);
unsigned char* cql_lex_cursor(cql_lex_t *lex, int offset);
void cql_lex_free(cql_lex_t *lex);

#endif
