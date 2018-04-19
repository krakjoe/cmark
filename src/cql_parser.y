%{
#include <src/cql.h>

#define YYSTYPE cql_ast_t

#include <src/cql_parser.h>
#include <src/cql_lexer.h>

#undef yyerror
static int yyerror(cql_lex_t *lex, cql_ast_t **stack, const char *msg);

#ifdef _MSC_VER
#define YYMALLOC malloc
#define YYFREE free
#endif

%}

%pure-parser
%error-verbose
%lex-param {lex}
%parse-param {cql_lex_t *lex} {cql_ast_t **stack}

%code requires {
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

}

%output  "src/cql_parser.c"
%defines "src/cql_parser.h"

%token T_FIRST_CHILD "firstChild"
%token T_LAST_CHILD "lastChild"
%token T_PARENT "parent"
%token T_PREVIOUS "previous"
%token T_NEXT "next"
%token T_CHILDREN "children"
%token T_SIBLINGS "siblings"
%token T_SEPERATOR "separator"
%token T_SUBQUERY_START "["
%token T_SUBQUERY_END "]"

%token T_CONSTRAINT_START "("
%token T_CONSTRAINT_NEGATE "^"
%token T_CONSTRAINT_END ")"
%token T_TYPE_SEPARATOR "|"
%token T_TYPE_BLOCK_QUOTE "BlockQuote"
%token T_TYPE_LIST "List"
%token T_TYPE_ITEM "Item"
%token T_TYPE_CODE_BLOCK     "CodeBlock"
%token T_TYPE_HTML_BLOCK     "HtmlBlock"
%token T_TYPE_CUSTOM_BLOCK   "CustomBlock"
%token T_TYPE_PARAGRAPH      "Paragraph"
%token T_TYPE_HEADING        "Heading"
%token T_TYPE_THEMATIC_BREAK "ThematicBreak"
%token T_TYPE_TEXT           "Text"
%token T_TYPE_SOFT_BREAK     "SoftBreak"
%token T_TYPE_LINE_BREAK     "LineBreak"
%token T_TYPE_CODE           "Code"
%token T_TYPE_HTML_INLINE    "HtmlInline"
%token T_TYPE_CUSTOM_INLINE  "CustomInline"
%token T_TYPE_EMPHASIS       "Emphasis"
%token T_TYPE_STRONG         "Strong"
%token T_TYPE_LINK           "Link"
%token T_TYPE_IMAGE          "Image"

%type <ast> cql selector selectors subquery
%type <constraint> types type constraint negate
%type <type> path

%%

cql
	: T_SEPERATOR selectors {
		*stack = $2; 
	}
	;

selectors
	: selectors T_SEPERATOR selector { 
		$$ = cql_ast_next($1, $3);
	}
	| selector  { $$ = $1; }
	;

subquery
	: T_SUBQUERY_START T_SEPERATOR selectors T_SUBQUERY_END { $$ = $3; }
	| /* nothing */	{ $$ = NULL; }
	;

type
	: T_TYPE_BLOCK_QUOTE        { $$ = CMARK_NODE_BLOCK_QUOTE; }
	| T_TYPE_LIST               { $$ = CMARK_NODE_LIST; }
	| T_TYPE_ITEM               { $$ = CMARK_NODE_ITEM; }
	| T_TYPE_CODE_BLOCK         { $$ = CMARK_NODE_CODE_BLOCK; }
	| T_TYPE_HTML_BLOCK         { $$ = CMARK_NODE_HTML_BLOCK; }
	| T_TYPE_CUSTOM_BLOCK       { $$ = CMARK_NODE_CUSTOM_BLOCK; }
	| T_TYPE_PARAGRAPH          { $$ = CMARK_NODE_PARAGRAPH; }
	| T_TYPE_HEADING            { $$ = CMARK_NODE_HEADING; }
	| T_TYPE_THEMATIC_BREAK     { $$ = CMARK_NODE_THEMATIC_BREAK; }
	| T_TYPE_TEXT               { $$ = CMARK_NODE_TEXT; }
	| T_TYPE_SOFT_BREAK         { $$ = CMARK_NODE_SOFTBREAK; }
	| T_TYPE_LINE_BREAK         { $$ = CMARK_NODE_LINEBREAK; }
	| T_TYPE_CODE               { $$ = CMARK_NODE_CODE; }
	| T_TYPE_HTML_INLINE        { $$ = CMARK_NODE_HTML_INLINE; }
	| T_TYPE_CUSTOM_INLINE      { $$ = CMARK_NODE_CUSTOM_INLINE; }
	| T_TYPE_EMPHASIS           { $$ = CMARK_NODE_EMPH; }
	| T_TYPE_STRONG             { $$ = CMARK_NODE_STRONG; }
	| T_TYPE_LINK               { $$ = CMARK_NODE_LINK; }
	| T_TYPE_IMAGE              { $$ = CMARK_NODE_IMAGE; }
	;

types
	: types T_TYPE_SEPARATOR type { $$ = $1 | 1u << $3; }
	| type { $$ = 1u << $1; }
	;

negate
	: T_CONSTRAINT_NEGATE { $$ = CQL_CONSTRAINT_NEGATE; }
	| /* nothing */ { $$ = 0; }
	;

constraint
	: T_CONSTRAINT_START negate types T_CONSTRAINT_END { $$ = $2 | $3; }
	| /* nothing */ { $$ = 0; }
	;

path
	: T_FIRST_CHILD { $$ = CQL_PATH_FIRST_CHILD; }
	| T_LAST_CHILD  { $$ = CQL_PATH_LAST_CHILD; }
	| T_PARENT      { $$ = CQL_PATH_PARENT; }
	| T_NEXT        { $$ = CQL_PATH_NEXT; }
	| T_PREVIOUS    { $$ = CQL_PATH_PREVIOUS; }
	| T_CHILDREN    { $$ = CQL_PATH_CHILDREN; }
	| T_SIBLINGS    { $$ = CQL_PATH_SIBLINGS; }
	;

selector
	: path constraint subquery { 
		if ($3) {
			$$ = cql_ast_create_children($1, $2, $3);
		} else  $$ = cql_ast_create($1, $2);
		
	}
	;
%%

static int yyerror(cql_lex_t *lex, cql_ast_t **stack, const char *msg) {
	return 0;
}
