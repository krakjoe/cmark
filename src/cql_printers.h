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
#ifndef HAVE_CQL_PRINTERS_H
#define HAVE_CQL_PRINTERS_H
static inline char* cql_op_name(cql_op_t *op) {
	switch (op->in) {
		case CQLI_NOP: return "NOP";
		case CQLI_FCN: return "FCN";
		case CQLI_LCN: return "LCN";
		case CQLI_PAN: return "PAN";
		case CQLI_PRN: return "PRN";
		case CQLI_NEN: return "NEN";
		case CQLI_ENT: return "ENT";
		case CQLI_JMP: return "JMP";
		case CQLI_CON: return "CON";
		case CQLI_SET: return "SET";
		case CQLI_RET: return "RET";
		case CQLI_BRK: return "BRK";
	}

	return "INV";
}

#define cql_constraint_print_reduce(from, type, name) do { \
	if ((from) & 1u << ((type))) { \
		(from) &= ~1u << (type); \
		output(#name); \
		if ((from) && (from) != CQL_CONSTRAINT_NEGATE) { \
			output("|"); \
		} \
	} \
} while(0)

void cql_constraint_print(cql_constraint_t constraint, cql_print_function_t *output) {
	cql_constraint_t type = constraint;

	if (!constraint) {
		return;
	}

	output("(");
	if (type & CQL_CONSTRAINT_NEGATE) {
		output("~");
	}
	while (type && type != CQL_CONSTRAINT_NEGATE) {
		cql_constraint_print_reduce(type, CMARK_NODE_BLOCK_QUOTE,     BlockQuote);
		cql_constraint_print_reduce(type, CMARK_NODE_LIST,            List);
		cql_constraint_print_reduce(type, CMARK_NODE_ITEM,            Item);
		cql_constraint_print_reduce(type, CMARK_NODE_CODE_BLOCK,      CodeBlock);
		cql_constraint_print_reduce(type, CMARK_NODE_HTML_BLOCK,      HtmlBlock);
		cql_constraint_print_reduce(type, CMARK_NODE_CUSTOM_BLOCK,    CustomBlock);
		cql_constraint_print_reduce(type, CMARK_NODE_PARAGRAPH,       Paragraph);
		cql_constraint_print_reduce(type, CMARK_NODE_HEADING,         Heading);
		cql_constraint_print_reduce(type, CMARK_NODE_THEMATIC_BREAK,  ThematicBreak);
		cql_constraint_print_reduce(type, CMARK_NODE_TEXT,            Text);
		cql_constraint_print_reduce(type, CMARK_NODE_SOFTBREAK,       SoftBreak);
		cql_constraint_print_reduce(type, CMARK_NODE_LINEBREAK,       LineBreak);
		cql_constraint_print_reduce(type, CMARK_NODE_CODE,            Code);
		cql_constraint_print_reduce(type, CMARK_NODE_HTML_INLINE,     HtmlInline);
		cql_constraint_print_reduce(type, CMARK_NODE_CUSTOM_INLINE,   CustomInline);
		cql_constraint_print_reduce(type, CMARK_NODE_EMPH,            Emphasis);
		cql_constraint_print_reduce(type, CMARK_NODE_STRONG,          Strong);
		cql_constraint_print_reduce(type, CMARK_NODE_LINK,            Link);
		cql_constraint_print_reduce(type, CMARK_NODE_IMAGE,           Image);
	}
	output(")");
}

static inline void cql_op_print(cql_function_t *function, cql_op_t *op, cql_print_function_t *output) {
	output(" #%ld\t %s\t", op - function->ops, cql_op_name(op));

	switch (op->in) {
		case CQLI_CON:
			output(" %ld\t #%ld\t|", 
				op->ip - function->stack.mem,
				op->op - function->ops);
			cql_constraint_print(op->constraint, output);
		break;

		case CQLI_RET:
			output(" -\t -\t|-");
		break;

		case CQLI_ENT:
			output(" %ld\t -\t|-", op->ip - function->stack.mem);
		break;

		case CQLI_BRK:
			output(" -\t #%ld\t|-",
				op->op - function->ops);
		break;

		case CQLI_JMP:
			output(" %ld\t #%ld\t|-",
				op->ip - function->stack.mem,
				op->op - function->ops);
		break;

		default:
			if (op->ip) {
				output(" %ld\t", op->ip - function->stack.mem);
			} else {
				output(" -\t");
			}

			if (op->rp) {
				output(" %ld\t", op->rp - function->stack.mem);
			} else {
				output(" -\t");
			}

			if (op->constraint == 1) {
				output("|loop");
			} else  if (op->constraint > -1) {
				output("|");
				cql_constraint_print(op->constraint, output);
			} else output("|-");
	}
	
	output("\n");
}

void cql_print(cql_function_t *function, cql_print_function_t *output) {
	cql_op_t *op, *end;

	if (!function) {
		return;
	}

	output("---------------------------------------\n");
	output("Function Size:  %d\n",        function->size);
	output("Function Space: %ld bytes\n", function->size * sizeof(cql_op_t));
	output("Stack Size:     %ld\n",       function->stack.space);
	output("Stack Space:    %ld bytes\n", function->stack.space * sizeof(void*));
        output("Total Space:    %ld bytes\n",
		sizeof(cql_function_t) +
		(sizeof(cql_op_t) * function->size) +
		(sizeof(void*) * function->stack.space));

	op = function->ops;
	end = op + function->size;

	output("---------------------------------------\n");
	output("|OL\t|INSTR\t|IV\t|RV/#T\t|\n");
	output("---------------------------------------\n");
	while (op < end) {
		cql_op_print(function, op, output);
		op++;
	}
	output("---------------------------------------\n");
}
#endif
