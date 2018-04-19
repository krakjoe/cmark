/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_CQL_SRC_CQL_PARSER_H_INCLUDED
# define YY_CQL_SRC_CQL_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int cql_debug;
#endif
/* "%code requires" blocks.  */
#line 24 "/opt/src/php-cmark/src/cql_parser.y" /* yacc.c:1909  */

#include <stdlib.h>
#include <string.h>

#include <src/cql.h>
#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void* yyscan_t;
typedef struct _cql_lex_t cql_lex_t;
#endif

static inline cql_ast_t* cql_ast_create(cql_ast_type_t type, cmark_node_type constraint) {
	cql_ast_t *ast = (cql_ast_t*) calloc(1, sizeof(cql_ast_t));

	if (!ast) {
		return NULL;
	}

	ast->type = type;
	ast->constraint = constraint;
	ast->last = &ast->next;
	
	return ast;
}

static inline cql_ast_t* cql_ast_create_children(cql_ast_type_t type, cmark_node_type constraint, cql_ast_t *children) {
	cql_ast_t *ast = cql_ast_create(type, constraint);

	ast->children = children;

	return ast;
}

static inline cql_ast_t* cql_ast_next(cql_ast_t *stack, cql_ast_t *next) {

	*(stack->last) = next;
	stack->last = &next->next;

	return stack;
}


#line 87 "src/cql_parser.h" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    T_FIRST_CHILD = 258,
    T_LAST_CHILD = 259,
    T_PARENT = 260,
    T_PREVIOUS = 261,
    T_NEXT = 262,
    T_CHILDREN = 263,
    T_SIBLINGS = 264,
    T_SEPERATOR = 265,
    T_SUBQUERY_START = 266,
    T_SUBQUERY_END = 267,
    T_CONSTRAINT_START = 268,
    T_CONSTRAINT_NEGATE = 269,
    T_CONSTRAINT_END = 270,
    T_TYPE_SEPARATOR = 271,
    T_TYPE_BLOCK_QUOTE = 272,
    T_TYPE_LIST = 273,
    T_TYPE_ITEM = 274,
    T_TYPE_CODE_BLOCK = 275,
    T_TYPE_HTML_BLOCK = 276,
    T_TYPE_CUSTOM_BLOCK = 277,
    T_TYPE_PARAGRAPH = 278,
    T_TYPE_HEADING = 279,
    T_TYPE_THEMATIC_BREAK = 280,
    T_TYPE_TEXT = 281,
    T_TYPE_SOFT_BREAK = 282,
    T_TYPE_LINE_BREAK = 283,
    T_TYPE_CODE = 284,
    T_TYPE_HTML_INLINE = 285,
    T_TYPE_CUSTOM_INLINE = 286,
    T_TYPE_EMPHASIS = 287,
    T_TYPE_STRONG = 288,
    T_TYPE_LINK = 289,
    T_TYPE_IMAGE = 290
  };
#endif
/* Tokens.  */
#define T_FIRST_CHILD 258
#define T_LAST_CHILD 259
#define T_PARENT 260
#define T_PREVIOUS 261
#define T_NEXT 262
#define T_CHILDREN 263
#define T_SIBLINGS 264
#define T_SEPERATOR 265
#define T_SUBQUERY_START 266
#define T_SUBQUERY_END 267
#define T_CONSTRAINT_START 268
#define T_CONSTRAINT_NEGATE 269
#define T_CONSTRAINT_END 270
#define T_TYPE_SEPARATOR 271
#define T_TYPE_BLOCK_QUOTE 272
#define T_TYPE_LIST 273
#define T_TYPE_ITEM 274
#define T_TYPE_CODE_BLOCK 275
#define T_TYPE_HTML_BLOCK 276
#define T_TYPE_CUSTOM_BLOCK 277
#define T_TYPE_PARAGRAPH 278
#define T_TYPE_HEADING 279
#define T_TYPE_THEMATIC_BREAK 280
#define T_TYPE_TEXT 281
#define T_TYPE_SOFT_BREAK 282
#define T_TYPE_LINE_BREAK 283
#define T_TYPE_CODE 284
#define T_TYPE_HTML_INLINE 285
#define T_TYPE_CUSTOM_INLINE 286
#define T_TYPE_EMPHASIS 287
#define T_TYPE_STRONG 288
#define T_TYPE_LINK 289
#define T_TYPE_IMAGE 290

/* Value type.  */



int cql_parse (cql_lex_t *lex, cql_ast_t **stack);

#endif /* !YY_CQL_SRC_CQL_PARSER_H_INCLUDED  */
