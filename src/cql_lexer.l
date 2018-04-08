/*
 * cql_lexer.l
 */

#include <src/cql.h>
#include <src/cql_parser.h>

/*!types:re2c*/
struct _cql_lex_t {
        unsigned int len;
        unsigned char *text;
        unsigned char *cursor;
        unsigned char *marker;
        unsigned char *ctxmarker;
        int state;
};

cql_lex_t* cql_lex_init (unsigned char *text, size_t length) {
	cql_lex_t *lex;

	if (!length || !text || !*text) {
		return NULL;
	}

	lex = (cql_lex_t*) calloc(1, sizeof(cql_lex_t));

	if (!lex) {
		return NULL;
	}

	lex->state = ST_LOOKING_FOR_SEPARATOR;
	lex->text  = lex->cursor = text;
	lex->len   = length;

	return lex;
}

unsigned char* cql_lex_cursor(cql_lex_t *lex, int offset) {
	return lex->cursor + offset;
}

void cql_lex_free(cql_lex_t *lex) {
	if (!lex) {
		return;
	}

	free(lex);
}

int cql_lex (cql_ast_t *yylval, cql_lex_t *lex) {

restart:
	lex->text = lex->cursor;

/*!re2c
re2c:yyfill:check = 0;
re2c:define:YYFILL = '';
re2c:define:YYSETCONDITION:naked = 1;
re2c:define:YYSETCONDITION = 'lex->state = @@';
re2c:define:YYGETCONDITION:naked = 1;
re2c:define:YYGETCONDITION = 'lex->state';
re2c:define:YYCURSOR = 'lex->cursor';
re2c:define:YYMARKER = 'lex->marker';
re2c:define:YYCTXMARKER = 'lex->ctxmarker';
re2c:define:YYCTYPE = 'unsigned char';
re2c:define:YYCONDTYPE = 'cql_lex_state_t';
re2c:condenumprefix = '';

T_FIRST_CHILD    'firstChild'
T_LAST_CHILD     'lastChild'
T_PREVIOUS       'previous'
T_NEXT           'next'
T_PARENT         'parent'
T_CHILDREN       'children'
T_SIBLINGS       'siblings'

T_BLOCK_QUOTE    'BlockQuote'
T_LIST           'List'
T_ITEM           'Item'
T_CODE_BLOCK     'CodeBlock'
T_HTML_BLOCK     'HtmlBlock'
T_CUSTOM_BLOCK   'CustomBlock'
T_PARAGRAPH      'Paragraph'
T_HEADING        'Heading'
T_THEMATIC_BREAK 'ThematicBreak'
T_TEXT           'Text'
T_SOFT_BREAK     'SoftBreak'
T_LINE_BREAK     'LineBreak'
T_CODE           'Code'
T_HTML_INLINE    'HtmlInline'
T_CUSTOM_INLINE  'CustomInline'
T_EMPHASIS       'Emphasis'
T_STRONG         'Strong'
T_LINK           'Link'
T_IMAGE          'Image'

SEPARATOR	 [\\/]
WS               [ \r\t\n]+

<!*> := lex->len = (size_t) lex->cursor - (size_t) lex->text;

<*>[\000] {
	return 0;
}

<*>{WS} {
	goto restart;
}

<*>[#][^\n]+ {
	goto restart;
}

<ST_LOOKING_FOR_SEPARATOR>({SEPARATOR}) {
	lex->state = ST_LOOKING_FOR_NODE;

	return T_SEPERATOR;
}

<ST_LOOKING_FOR_NODE>({T_FIRST_CHILD}) {
	lex->state = ST_LOOKING_FOR_SEPARATOR;

	return T_FIRST_CHILD;
}

<ST_LOOKING_FOR_NODE>({T_LAST_CHILD}) {
	lex->state = ST_LOOKING_FOR_SEPARATOR;

	return T_LAST_CHILD;
}

<ST_LOOKING_FOR_NODE>({T_PARENT}) {
	lex->state = ST_LOOKING_FOR_SEPARATOR;

	return T_PARENT;
}

<ST_LOOKING_FOR_NODE>({T_NEXT}) {
	lex->state = ST_LOOKING_FOR_SEPARATOR;

	return T_NEXT;
}

<ST_LOOKING_FOR_NODE>({T_PREVIOUS}) {
	lex->state = ST_LOOKING_FOR_SEPARATOR;

	return T_PREVIOUS;
}

<ST_LOOKING_FOR_NODE>({T_CHILDREN}) {
	lex->state = ST_LOOKING_FOR_SUBQUERY;

	return T_CHILDREN;
}

<ST_LOOKING_FOR_NODE>({T_SIBLINGS}) {
	lex->state = ST_LOOKING_FOR_SUBQUERY;

	return T_SIBLINGS;
}

<ST_LOOKING_FOR_SEPARATOR,ST_LOOKING_FOR_SUBQUERY>"[" {
	lex->state = ST_LOOKING_FOR_SEPARATOR;

	return T_SUBQUERY_START;
}

<ST_LOOKING_FOR_SEPARATOR,ST_LOOKING_FOR_SUBQUERY>"]" {
	return T_SUBQUERY_END;
}

<ST_LOOKING_FOR_SEPARATOR,ST_LOOKING_FOR_SUBQUERY>"(" {
	lex->state = ST_LOOKING_FOR_TYPE;

	return T_CONSTRAINT_START;
}

<ST_LOOKING_FOR_TYPE>"^" {
	return T_CONSTRAINT_NEGATE;
}

<ST_LOOKING_FOR_TYPE,ST_LOOKING_FOR_TYPE_SEPARATOR>")" {
	lex->state = ST_LOOKING_FOR_SUBQUERY;

	return T_CONSTRAINT_END;
}

<ST_LOOKING_FOR_TYPE_SEPARATOR>"|" {
	lex->state = ST_LOOKING_FOR_TYPE;

	return T_TYPE_SEPARATOR;
}

<ST_LOOKING_FOR_TYPE>({T_BLOCK_QUOTE}) {
	lex->state = ST_LOOKING_FOR_TYPE_SEPARATOR;

	return T_TYPE_BLOCK_QUOTE;
}

<ST_LOOKING_FOR_TYPE>({T_LIST}) {
	lex->state = ST_LOOKING_FOR_TYPE_SEPARATOR;

	return T_TYPE_LIST;
}

<ST_LOOKING_FOR_TYPE>({T_ITEM}) {
	lex->state = ST_LOOKING_FOR_TYPE_SEPARATOR;

	return T_TYPE_ITEM;
}

<ST_LOOKING_FOR_TYPE>({T_CODE_BLOCK}) {
	lex->state = ST_LOOKING_FOR_TYPE_SEPARATOR;

	return T_TYPE_CODE_BLOCK;
}

<ST_LOOKING_FOR_TYPE>({T_HTML_BLOCK}) {
	lex->state = ST_LOOKING_FOR_TYPE_SEPARATOR;

	return T_TYPE_HTML_BLOCK;
}

<ST_LOOKING_FOR_TYPE>({T_CUSTOM_BLOCK}) {
	lex->state = ST_LOOKING_FOR_TYPE_SEPARATOR;

	return T_TYPE_CUSTOM_BLOCK;
}

<ST_LOOKING_FOR_TYPE>({T_PARAGRAPH}) {
	lex->state = ST_LOOKING_FOR_TYPE_SEPARATOR;

	return T_TYPE_PARAGRAPH;
}

<ST_LOOKING_FOR_TYPE>({T_HEADING}) {
	lex->state = ST_LOOKING_FOR_TYPE_SEPARATOR;

	return T_TYPE_HEADING;
}

<ST_LOOKING_FOR_TYPE>({T_THEMATIC_BREAK}) {
	lex->state = ST_LOOKING_FOR_TYPE_SEPARATOR;

	return T_TYPE_THEMATIC_BREAK;
}

<ST_LOOKING_FOR_TYPE>({T_TEXT}) {
	lex->state = ST_LOOKING_FOR_TYPE_SEPARATOR;

	return T_TYPE_TEXT;
}

<ST_LOOKING_FOR_TYPE>({T_SOFT_BREAK}) {
	lex->state = ST_LOOKING_FOR_TYPE_SEPARATOR;

	return T_TYPE_SOFT_BREAK;
}

<ST_LOOKING_FOR_TYPE>({T_LINE_BREAK}) {
	lex->state = ST_LOOKING_FOR_TYPE_SEPARATOR;

	return T_TYPE_LINE_BREAK;
}

<ST_LOOKING_FOR_TYPE>({T_CODE}) {
	lex->state = ST_LOOKING_FOR_TYPE_SEPARATOR;

	return T_TYPE_CODE;
}

<ST_LOOKING_FOR_TYPE>({T_HTML_INLINE}) {
	lex->state = ST_LOOKING_FOR_TYPE_SEPARATOR;

	return T_TYPE_HTML_INLINE;
}

<ST_LOOKING_FOR_TYPE>({T_CUSTOM_INLINE}) {
	lex->state = ST_LOOKING_FOR_TYPE_SEPARATOR;

	return T_TYPE_CUSTOM_INLINE;
}

<ST_LOOKING_FOR_TYPE>({T_EMPHASIS}) {
	lex->state = ST_LOOKING_FOR_TYPE_SEPARATOR;

	return T_TYPE_EMPHASIS;
}

<ST_LOOKING_FOR_TYPE>({T_STRONG}) {
	lex->state = ST_LOOKING_FOR_TYPE_SEPARATOR;

	return T_TYPE_STRONG;
}

<ST_LOOKING_FOR_TYPE>({T_LINK}) {
	lex->state = ST_LOOKING_FOR_TYPE_SEPARATOR;

	return T_TYPE_LINK;
}

<ST_LOOKING_FOR_TYPE>({T_IMAGE}) {
	lex->state = ST_LOOKING_FOR_TYPE_SEPARATOR;

	return T_TYPE_IMAGE;
}

*/
}
