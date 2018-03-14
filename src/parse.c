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
#ifndef PHP_CMARK_PARSER
#define PHP_CMARK_PARSER

#include <php.h>

#include <src/common.h>
#include <src/parse.h>
#include <src/node.h>

zend_class_entry *php_cmark_parser_ce;
zend_object_handlers php_cmark_parser_handlers;

typedef struct _php_cmark_parser_t {
	cmark_parser *parser;
	zval root;
	zend_object std;
} php_cmark_parser_t;

#define php_cmark_parser_from(o) \
	((php_cmark_parser_t*) \
		((char*) o - XtOffsetOf(php_cmark_parser_t, std)))
#define php_cmark_parser_fetch(z) php_cmark_parser_from(Z_OBJ_P(z))

static inline void php_cmark_parser_free(zend_object *zo) {
	php_cmark_parser_t *p = php_cmark_parser_from(zo);
	zend_bool finished = 0;

	if (!Z_ISUNDEF(p->root)) {
		zval_ptr_dtor(&p->root);
		finished = 1;
	}

	if (p->parser) {
		if (!finished) {
			cmark_node_free(
				cmark_parser_finish(p->parser));
		}
		cmark_parser_free(p->parser);
	}

	zend_object_std_dtor(zo);
}

zend_object* php_cmark_parser_create(zend_class_entry *ce) {
	php_cmark_parser_t *p = (php_cmark_parser_t*) ecalloc(1, sizeof(php_cmark_parser_t));

	zend_object_std_init(&p->std, ce);

	p->std.handlers = &php_cmark_parser_handlers;

	ZVAL_UNDEF(&p->root);

	return &p->std;
}

ZEND_BEGIN_ARG_INFO_EX(php_cmark_parser_construct, 0, 0, 0)
	ZEND_ARG_INFO(0, options)
ZEND_END_ARG_INFO()

PHP_METHOD(Parser, __construct)
{
	php_cmark_parser_t *p = php_cmark_parser_fetch(getThis());
	zend_long options;

	ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_STRICT_LONG(options)
	ZEND_PARSE_PARAMETERS_END();

	p->parser = cmark_parser_new_with_mem(options, &php_cmark_node_mem);
}

ZEND_BEGIN_ARG_INFO_EX(php_cmark_parser_parse, 0, 0, 1)
	ZEND_ARG_INFO(0, buffer)
ZEND_END_ARG_INFO()

PHP_METHOD(Parser, parse)
{
	php_cmark_parser_t *p = php_cmark_parser_fetch(getThis());
	zend_string *buffer;

	ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
		Z_PARAM_STR(buffer)
	ZEND_PARSE_PARAMETERS_END();

	cmark_parser_feed(p->parser, ZSTR_VAL(buffer), ZSTR_LEN(buffer));
}

PHP_METHOD(Parser, finish)
{
	php_cmark_parser_t *p = php_cmark_parser_fetch(getThis());
	php_cmark_node_t *n;

	php_cmark_no_parameters();

	if (!Z_ISUNDEF(p->root)) {
		php_cmark_throw("already finished");
		return;
	}

	n = php_cmark_node_shadow(
		return_value, cmark_parser_finish(p->parser));

	ZVAL_COPY(&n->parser, getThis());
	ZVAL_COPY(&p->root,   return_value);
}

static zend_function_entry php_cmark_parser_methods[] = {
	PHP_ME(Parser, __construct, php_cmark_parser_construct, ZEND_ACC_PUBLIC)
	PHP_ME(Parser, parse, php_cmark_parser_parse, ZEND_ACC_PUBLIC)
	PHP_ME(Parser, finish, php_cmark_no_arginfo, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

PHP_FUNCTION(CommonMark_Parse) 
{
	zend_string *content;
	zend_long options;
	cmark_parser *parser;

	ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 2)
		Z_PARAM_STR(content)
		Z_PARAM_OPTIONAL
		Z_PARAM_STRICT_LONG(options)
	ZEND_PARSE_PARAMETERS_END();

	parser = cmark_parser_new_with_mem(options, &php_cmark_node_mem);

	cmark_parser_feed(parser, ZSTR_VAL(content), ZSTR_LEN(content));

	php_cmark_node_shadow(
		return_value, cmark_parser_finish(parser));

	cmark_parser_free(parser);
}

PHP_MINIT_FUNCTION(CommonMark_Parser) 
{
	zend_class_entry ce;

	INIT_NS_CLASS_ENTRY(ce, "CommonMark", "Parser", php_cmark_parser_methods);

	php_cmark_parser_ce = zend_register_internal_class(&ce);
	php_cmark_parser_ce->create_object = php_cmark_parser_create;

	memcpy(&php_cmark_parser_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

	php_cmark_parser_handlers.free_obj = php_cmark_parser_free;
	php_cmark_parser_handlers.offset = XtOffsetOf(php_cmark_parser_t, std);

	REGISTER_NS_LONG_CONSTANT("CommonMark\\Parser", "Normalize", CMARK_OPT_NORMALIZE, CONST_CS|CONST_PERSISTENT);
	REGISTER_NS_LONG_CONSTANT("CommonMark\\Parser", "ValidateUTF8", CMARK_OPT_VALIDATE_UTF8, CONST_CS|CONST_PERSISTENT);
	REGISTER_NS_LONG_CONSTANT("CommonMark\\Parser", "Smart", CMARK_OPT_SMART, CONST_CS|CONST_PERSISTENT);

	return SUCCESS;
}

PHP_RINIT_FUNCTION(CommonMark_Parser)
{
	php_cmark_parser_ce->ce_flags |= ZEND_ACC_FINAL;

	return SUCCESS;
}
#endif
