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
#ifndef HAVE_CQL
#define HAVE_CQL

#include <stdlib.h>
#include <string.h>

#include <src/cql.h>
#include <src/cql_lexer.h>
#include <src/cql_parser.h>

/****************************************************************************************/
/* CQL OP FORWARD DECLS                                                                 */
/****************************************************************************************/
typedef enum cql_in_t {
	CQLI_NOP,
	CQLI_FCN,    /* firstChild */
	CQLI_LCN,    /* lastChild  */
	CQLI_PAN,    /* parent */
	CQLI_PRN,    /* previous */
	CQLI_NEN,    /* next */
	CQLI_JMP,    /* jmp */
	CQLI_BRK,    /* break */
	CQLI_ENT,    /* enter */
	CQLI_SET,    /* set */
	CQLI_CON,    /* constrain */
	CQLI_RET,    /* return */
} cql_in_t;

struct _cql_op_t {
	cql_in_t in;
	cql_constraint_t constraint;

	union {
		int iv;
		void **ip;
	};
	union {
		int rv;
		void **rp;
		cql_op_t *op;
	};

	cmark_node* (*handler) (cmark_node*);
};

typedef enum _cql_op_ir_type_t {
	CQLI_OP_IR_NONE = 0,
	CQLI_OP_IR_NUM,
	CQLI_OP_IR_ALLOC,
	CQLI_OP_IR_IV_LAST,
	CQLI_OP_IR_RV_LAST,
	CQLI_OP_IR_IV,
	CQLI_OP_IR_RV,
} cql_op_ir_type_t;

static inline int cql_op_alloc(cql_function_t *function);
static inline int cql_op_lastloop(cql_function_t *function, int last);
static inline int cql_op_firstloop(cql_function_t *function, int pos);
static inline int cql_op_firstof(cql_function_t *function, cql_in_t in);
static inline int cql_op_emit(cql_function_t *function, cql_in_t in, cql_op_ir_type_t it, int iv, cql_op_ir_type_t rt, int rv, cql_constraint_t constraint);
static inline int cql_op_update_ir(cql_function_t *function, int op, cql_op_ir_type_t it, int ir);
static inline int cql_op_emit_simple(cql_function_t *function, cql_in_t in);

/****************************************************************************************/
/* CQL AST                                                                              */
/****************************************************************************************/
static inline cql_in_t cql_ast_loop_begin_in(cql_ast_type_t type) {
	switch (type) {
		case CQL_PATH_CHILDREN: return CQLI_FCN;
		case CQL_PATH_SIBLINGS: return CQLI_NEN;
		case CQL_PATH_FIRST_CHILD: return CQLI_FCN;
		case CQL_PATH_LAST_CHILD: return CQLI_LCN;
		case CQL_PATH_PREVIOUS: return CQLI_PRN;
		case CQL_PATH_PARENT: return CQLI_PAN;
		case CQL_PATH_NEXT: return CQLI_NEN;
	}
	return CQLI_NOP;
}

static inline cql_in_t cql_ast_loop_next_in(cql_ast_type_t type) {
	switch (type) {
		case CQL_PATH_CHILDREN: return CQLI_NEN;
		case CQL_PATH_SIBLINGS: return CQLI_NEN;
		case CQL_PATH_FIRST_CHILD: return CQLI_NEN;
		case CQL_PATH_LAST_CHILD: return CQLI_PRN;
		case CQL_PATH_PREVIOUS: return CQLI_PRN;
		case CQL_PATH_PARENT: return CQLI_PAN;
		case CQL_PATH_NEXT: return CQLI_NEN; 
	}
	return CQLI_NOP;
}

static inline int cql_ast_process(cql_ast_t *stack, cql_function_t *function, int depth) {
	cql_ast_t *ast = stack;

	while (ast) {

		if (ast->type == CQL_PATH_CHILDREN || 
		    ast->type == CQL_PATH_SIBLINGS || 
		    ast->constraint > 1) {

			int begin = cql_op_emit(function, 
					cql_ast_loop_begin_in(ast->type), 
						CQLI_OP_IR_RV_LAST, 0, CQLI_OP_IR_ALLOC, 0, 1),
			    go = -1,
			    next = -1,
			    enter = -1,
			    target = begin,
			    constraint = -1;

			if (ast->constraint) {
				constraint = cql_op_emit(function, CQLI_CON,
					CQLI_OP_IR_RV_LAST, 0, CQLI_OP_IR_NONE, 0, ast->constraint);
			}

			if (ast->children) {
				cql_ast_process(ast->children, function, depth + 1);

				if (cql_op_lastloop(function, function->size - 1) > begin) {
					target = cql_op_firstloop(function, begin + 1);
				}  else target = begin + 2;
			}

			if ((enter = cql_op_firstof(function, CQLI_ENT)) < 0) {
				enter = cql_op_emit(function, CQLI_ENT,
						CQLI_OP_IR_RV_LAST, 0, CQLI_OP_IR_NONE, 0, 0);

				if (!ast->children) {
					target = enter;
				}
			}

			if (ast->type != CQL_PATH_CHILDREN && CQL_PATH_SIBLINGS != ast->type) {
				go = cql_op_emit(function, CQLI_BRK,
					CQLI_OP_IR_NONE, 0, CQLI_OP_IR_NONE, 0, 0);
			}

			next = cql_op_emit(function, cql_ast_loop_next_in(ast->type),
					CQLI_OP_IR_RV, begin, CQLI_OP_IR_ALLOC, 0, 0);

			if (function->ops[target].constraint >= 1) {
				cql_op_emit(function, CQLI_SET,
					CQLI_OP_IR_NUM, function->ops[target].iv, CQLI_OP_IR_RV, next, -1);
			} else {
				cql_op_emit(function, CQLI_SET,
					CQLI_OP_IR_IV, next, CQLI_OP_IR_RV, next, -1);
			}

			if (constraint > -1) {
				cql_op_update_ir(function, constraint, CQLI_OP_IR_RV, next);

				cql_op_emit(function, CQLI_CON,
					CQLI_OP_IR_RV_LAST, 0, CQLI_OP_IR_NUM, next, ast->constraint);
			}

			cql_op_emit(function, CQLI_JMP, CQLI_OP_IR_RV, next, CQLI_OP_IR_NUM, target, -1);

			if (go > -1) {
				cql_op_update_ir(function, go, CQLI_OP_IR_RV, function->size);
			}

		} else switch (ast->type) {
			case CQL_PATH_FIRST_CHILD:  cql_op_emit_simple(function, CQLI_FCN); break;
			case CQL_PATH_LAST_CHILD:   cql_op_emit_simple(function, CQLI_LCN); break;
			case CQL_PATH_PARENT:       cql_op_emit_simple(function, CQLI_PAN); break;
			case CQL_PATH_PREVIOUS:     cql_op_emit_simple(function, CQLI_PRN); break;
			case CQL_PATH_NEXT:         cql_op_emit_simple(function, CQLI_NEN); break;

			default:
				/* nothing */
				break;
		}

		ast = ast->next;
	}

	if (depth == 0) {
		if (cql_op_firstof(function, CQLI_ENT) < 0) {
			cql_op_emit(function, CQLI_ENT, CQLI_OP_IR_RV_LAST, 0, CQLI_OP_IR_NONE, 0, 0);
		}

		cql_op_emit(function, CQLI_RET, CQLI_OP_IR_NONE, 0, CQLI_OP_IR_NONE, 0, -1);
	}

	return function->size;
}

static inline void cql_ast_free(cql_ast_t *ast) {
	while (ast) {
		cql_ast_t *garbage = ast;

		if (ast->children) {
			cql_ast_free(ast->children);
		}

		ast = garbage->next;

		free(garbage);
	}
}
/****************************************************************************************/
/* CQL OPS                                                                              */
/****************************************************************************************/
static inline int cql_op_alloc(cql_function_t *function) {
	return function->stack.space++;
}

static inline int cql_constrain(cql_constraint_t type, cmark_node *node) {
	return (type & 1u << cmark_node_get_type(node)) ?
		!(type & CQL_CONSTRAINT_NEGATE) :
		(type & CQL_CONSTRAINT_NEGATE) ;
}

static inline int cql_op_lastloop(cql_function_t *function, int last) {
	int end = 0,
            pos = last;

	while (pos > end) {
		switch (function->ops[pos].in) {
			case CQLI_FCN:
			case CQLI_NEN:
			case CQLI_LCN:
			case CQLI_PAN:
			case CQLI_PRN:
				if (function->ops[pos].constraint == 1) {
					return pos;
				}
			break;

			default:
				/* nothing */
				break;
		}
		
		pos--;
	}

	return -1;
}

static inline int cql_op_firstof(cql_function_t *function, cql_in_t in) {
	int pos = 0,
	    end = function->size;

	while (pos < end) {
		if (function->ops[pos].in == in) {
			return pos;
		}
		pos++;
	}

	return -1;
}

static inline int cql_op_firstloop(cql_function_t *function, int pos) {
	int end = function->size;

	while (pos < end) {
		switch (function->ops[pos].in) {
			case CQLI_FCN:
			case CQLI_NEN:
			case CQLI_LCN:
			case CQLI_PAN:
			case CQLI_PRN:
				if (function->ops[pos].constraint == 1) {
					return pos;
				}
			break;

			default:
				/* nothing */
				break;
		}
		pos++;
	}

	return -1;
}

static inline int cql_op_update_ir(cql_function_t *function, int op, cql_op_ir_type_t it, int ir) {
	switch (it) {
		case CQLI_OP_IR_RV:
			return function->ops[op].rv = ir;

		case CQLI_OP_IR_IV:
			return function->ops[op].iv = ir;

		default:
			/* nothing */
			break;
	}

	return -1;
}

static inline int cql_op_ir(cql_function_t *function, cql_op_ir_type_t type, int ir) {
	int last = function->size - 1;

	switch (type) {
		case CQLI_OP_IR_IV:
			return function->ops[ir].iv;

		case CQLI_OP_IR_RV:
			return function->ops[ir].rv;

		case CQLI_OP_IR_NUM:
			return ir;

		case CQLI_OP_IR_IV_LAST:
			if (last > -1) {
				while (function->ops[last].iv < 0 && last > 0) {
					last--;
				}
	
				if (last > -1)
					return function->ops[last].iv;
			}
			return cql_op_alloc(function);

		case CQLI_OP_IR_RV_LAST:
			if (last > -1) {
				while (function->ops[last].rv < 0 && last > 0) {
					last--;
				}
	
				if (last > -1)
					return function->ops[last].rv;
			}
			return cql_op_alloc(function);

		case CQLI_OP_IR_ALLOC:
			return cql_op_alloc(function);

		default:
			/* nothing */
			break;
	}

	return -1;
}

static inline int cql_op_emit(cql_function_t *function, cql_in_t in, cql_op_ir_type_t it, int iv, cql_op_ir_type_t rt, int rv, cql_constraint_t constraint) {
	cql_op_t *op;

	if (!function->ops) {
		function->ops = (cql_op_t*) malloc(sizeof(cql_op_t) * 8);
		function->size = 0;
		function->max = 8;
	} else {
		if (function->size + 1 > function->max) {
			function->ops = (cql_op_t*) realloc(
				function->ops, sizeof(cql_op_t) * (function->size * 2));
			function->max = function->size * 2;
		}
	}

	if (!function->ops) {
		return -1;
	}

	op = function->ops + function->size;

	op->in = in;
	op->constraint = constraint;

	op->iv = cql_op_ir(function, it, iv);
	op->rv = cql_op_ir(function, rt, rv);

	switch (op->in) {
		case CQLI_FCN: op->handler = cmark_node_first_child; break;
		case CQLI_LCN: op->handler = cmark_node_last_child; break;
		case CQLI_NEN: op->handler = cmark_node_next; break;
		case CQLI_PRN: op->handler = cmark_node_previous; break;
		case CQLI_PAN: op->handler = cmark_node_parent; break;
		
		default:
			op->handler = NULL;
	}

	return function->size++;
}

static inline int cql_op_emit_simple(cql_function_t *function, cql_in_t in) {
	return cql_op_emit(function, in, CQLI_OP_IR_RV_LAST, 0, CQLI_OP_IR_ALLOC, 0, -1);
}

static inline int cql_op_stack(cql_function_t *function) {
	if (!function->size) {
		return -1;
	}

	function->stack.mem = (void**) calloc(function->stack.space, sizeof(void*));

	if (!function->stack.mem) {
		return -1;
	}

	{
		cql_op_t *op = function->ops, *end = op + function->size;

		while (op < end) {
			switch (op->in) {
				case CQLI_BRK:
				case CQLI_JMP:
				case CQLI_CON: {
					op->ip = &function->stack.mem[op->iv];
					op->op = (cql_op_t*) function->ops + op->rv;
				} break;

				case CQLI_ENT:
					op->ip = &function->stack.mem[op->iv];
				break;

				case CQLI_RET:
				break;

				default:
					if (op->iv > -1)
						op->ip = &function->stack.mem[op->iv];
					if (op->rv > -1)
						op->rp = &function->stack.mem[op->rv];		
			}

			op++;
		}
	}

	return function->size;
}

/****************************************************************************************/
/* CQL VM                                                                               */
/****************************************************************************************/
#define OP(o)   ((o)->op)
#define IN(o)   ((o)->in)
#define IV(o)   ((o)->ip)
#define RV(o)   ((o)->rp)
#define CON(o)  ((o)->constraint)
#define FN(o)   ((o)->handler)

#define VMLOOP(o, e) while(o < e) __CQL_VM_ENTER:
#define VMNEXT(o) ((o)++); continue;
#define VMJMP(o ,t) (o) = (cql_op_t*) (t); goto __CQL_VM_ENTER;
#define VMRET(v) return v;

static inline int cql_vm(cql_function_t *function, 
			 cmark_node *node, 
			 cql_enter_function_t *cql_enter_function, void *arg) {

	cql_op_t       *op     = function->ops,
		       *end    = op + function->size;

	*IV(op) = (void*) node;

	VMLOOP(op, end) {
		if (FN(op)) {
			*RV(op) = FN(op)(*IV(op));

			VMNEXT(op);
		}

		switch (IN(op)) {
			case CQLI_SET: *IV(op) = *RV(op); break;

			case CQLI_BRK: VMJMP(op, OP(op)); break;

			case CQLI_JMP:
				if (*IV(op)) {
					VMJMP(op, OP(op));
				}
			break;

			case CQLI_CON:
				if (*IV(op) && !cql_constrain(CON(op), *IV(op))) {
					VMJMP(op, OP(op));
				}
			break;

			case CQLI_ENT:
				if (*IV(op)) {
					if (!cql_enter_function(*IV(op), arg)) {
						VMRET(0);
					}
				}
			break;

			case CQLI_RET: VMRET(0);

			default:
				/* nothing */
				break;
		}

		VMNEXT(op);
	}

	VMRET(-1);
}

#undef VMRET
#undef VMJMP
#undef VMNEXT
#undef VMLOOP
#undef EXT
#undef RV
#undef IV
#undef IN
#undef OP

/****************************************************************************************/
/* CQL PUBLIC                                                                           */
/****************************************************************************************/
#include <src/cql_printers.h>

cql_function_t* cql_compile(cql_function_t *function, unsigned char *text, size_t length, unsigned char **end) {
	cql_lex_t *lex = cql_lex_init(text, length);
	cql_ast_t *ast = NULL;

	if (!lex) {
		return NULL;
	}

	memset(function, 0, sizeof(cql_function_t));

	if (cql_parse(lex, &ast) != 0) {
		goto cql_compile_error;
	}

	if (cql_lex_cursor(lex, -1) == (unsigned char*) (text + length)) {
		int size = cql_ast_process(ast, function, 0);

		if (size < 0) {
			goto cql_compile_error;
		}

		cql_lex_free(lex);
		cql_ast_free(ast);

		if (!cql_op_stack(function)) {
			cql_free(function);

			return NULL;
		}

		return function;		
	}

cql_compile_error:
	(*end) = cql_lex_cursor(lex, -1);

	cql_lex_free(lex);
	cql_ast_free(ast);
	cql_free(function);

	return NULL;
}

int cql_clone(cql_function_t *source, cql_function_t *destination) {
	cql_op_t *op, *end;

	if (!source || !source->size) {
		return -1;
	}

	memcpy(destination, source, sizeof(cql_function_t));

	destination->ops = (cql_op_t*) calloc(source->size, sizeof(cql_op_t));

	if (!destination->ops) {
		return -1;
	}

	memcpy(destination->ops, source->ops, sizeof(cql_op_t) * source->size);

	op = destination->ops;
	end = op + destination->size;

	while (op < end) {
		switch (op->in) {
			case CQLI_BRK:
			case CQLI_JMP:
			case CQLI_CON:
				op->iv = op->ip - source->stack.mem;
				op->rv = op->op - source->ops;
			break;

			case CQLI_ENT:
				op->iv = op->ip - source->stack.mem;
			break;

			case CQLI_RET:
			break;

			default:
				if (op->ip)
					op->iv = op->ip - source->stack.mem;
				if (op->rp)
					op->rv = op->rp - source->stack.mem;
		}
		op++;
	}

	if (!cql_op_stack(destination)) {
		free(destination->ops);

		return -1;
	}

	return destination->size;
}

int cql_call(cql_function_t *function, cmark_node *node, cql_enter_function_t *cql_enter_function, void *arg) {
	if (!function->size || !node || !cql_enter_function) {
		return -1;
	}

	return cql_vm(function, node, cql_enter_function, arg);
}

void cql_free(cql_function_t *function) {
	if (function->stack.mem) {
		free(function->stack.mem);
	}
	
	if (function->ops) {
		free(function->ops);
	}
}
#endif
