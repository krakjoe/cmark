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
#ifndef HAVE_CQL_H
#define HAVE_CQL_H

#include <cmark.h>

#ifdef HAVE_CONFIG_H
#	include "config.h"
#endif

#ifdef HAVE_CQL_JIT
#	include <jit/jit.h>
#	include <jit/jit-dump.h>
#endif

typedef signed long long cql_constraint_t;

typedef enum _cql_ast_type_t {
	CQL_PATH_FIRST_CHILD,
	CQL_PATH_LAST_CHILD,
	CQL_PATH_NEXT,
	CQL_PATH_PREVIOUS,
	CQL_PATH_PARENT,
	CQL_PATH_CHILDREN,
	CQL_PATH_SIBLINGS,
} cql_ast_type_t;

#define CQL_CONSTRAINT_NEGATE 1u << (CMARK_NODE_LAST_INLINE + 1)

typedef struct _cql_ast_t cql_ast_t;

struct _cql_ast_t {
	cql_ast_type_t type;
	cql_constraint_t constraint;
	union {
		cql_ast_t *ast;
		cql_ast_t *next;
	};
	cql_ast_t **last;
	cql_ast_t *children;
};

typedef struct _cql_op_t cql_op_t;

typedef struct _cql_function_t {
#ifdef HAVE_CQL_JIT
	struct {
		jit_context_t  context;
		jit_function_t function;
	} jit;
#endif
	cql_op_t  *ops;
	int        size;
	int        max;
	struct     {
		void **mem;
		size_t space;
	} stack;
} cql_function_t;

typedef int (cql_enter_function_t)(cmark_node*, void*);

typedef size_t (cql_print_function_t) (const char *format, ...);

#ifdef HAVE_CQL_JIT
#ifndef CQL_JIT_SMALLEST
#	define CQL_JIT_SMALLEST 10
#endif

extern void            cql_jit_init(void);
extern void	       cql_jit_cleanup(void);
#endif

extern cql_function_t* cql_compile(cql_function_t *function, unsigned char *text, size_t length, unsigned char **end);
extern int             cql_call(cql_function_t *function, cmark_node *node, cql_enter_function_t *cql_enter_function, void *arg);
extern void            cql_print(cql_function_t *function, cql_print_function_t *output);
extern int             cql_clone(cql_function_t *source, cql_function_t *destination);
extern void            cql_free(cql_function_t *function);
#endif
