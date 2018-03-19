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
#ifndef PHP_CMARK_RENDER
#define PHP_CMARK_RENDER

#include <php.h>

#include <src/common.h>
#include <src/node.h>
#include <src/visitor.h>

typedef struct _php_cmark_render_arg_t {
	zend_long options;
	zend_long width;
} php_cmark_render_arg_t;

#define php_cmark_render_arg_empty {0, 0}

typedef char* (*php_cmark_render_func)(cmark_node *n, int options, int width);
typedef char* (*php_cmark_render_func_no_width)(cmark_node *n, int options);

static inline void php_cmark_render(zval *retval, php_cmark_node_t *n, php_cmark_render_func func, php_cmark_render_arg_t *arg, zend_bool width) {
	char *result = 
		width ? 
			((php_cmark_render_func)func)
				(n->node, arg->options, arg->width) :
			((php_cmark_render_func_no_width)func)
				(n->node, arg->options);

	ZVAL_STRING(retval, result);
	
	efree(result);	
}

PHP_FUNCTION(CommonMark_Render)
{
	zval *node;
	php_cmark_render_arg_t arg = php_cmark_render_arg_empty;

	ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 3)
		Z_PARAM_OBJECT_OF_CLASS(node, php_cmark_node_ce)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(arg.options)
		Z_PARAM_LONG(arg.width)
	ZEND_PARSE_PARAMETERS_END();

	php_cmark_render(
		return_value,
		php_cmark_node_fetch(node), 
		(php_cmark_render_func) cmark_render_commonmark,
		&arg, 1);
}

PHP_FUNCTION(CommonMark_Render_XML)
{
	zval *node;
	php_cmark_render_arg_t arg = php_cmark_render_arg_empty;

	ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 2)
		Z_PARAM_OBJECT_OF_CLASS(node, php_cmark_node_ce)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(arg.options)
	ZEND_PARSE_PARAMETERS_END();

	php_cmark_render(
		return_value,
		php_cmark_node_fetch(node), 
		(php_cmark_render_func) cmark_render_xml,
		&arg, 0);
}

PHP_FUNCTION(CommonMark_Render_HTML)
{
	zval *node;
	php_cmark_render_arg_t arg = php_cmark_render_arg_empty;

	ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 2)
		Z_PARAM_OBJECT_OF_CLASS(node, php_cmark_node_ce)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(arg.options)
	ZEND_PARSE_PARAMETERS_END();

	php_cmark_render(
		return_value,
		php_cmark_node_fetch(node), 
		(php_cmark_render_func) cmark_render_html,
		&arg, 0);
}

PHP_FUNCTION(CommonMark_Render_Man)
{
	zval *node;
	php_cmark_render_arg_t arg = php_cmark_render_arg_empty;

	ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 3)
		Z_PARAM_OBJECT_OF_CLASS(node, php_cmark_node_ce)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(arg.options)
		Z_PARAM_LONG(arg.width)
	ZEND_PARSE_PARAMETERS_END();

	php_cmark_render(
		return_value,
		php_cmark_node_fetch(node), 
		(php_cmark_render_func) cmark_render_man,
		&arg, 1);
}

PHP_FUNCTION(CommonMark_Render_Latex)
{
	zval *node;
	php_cmark_render_arg_t arg = php_cmark_render_arg_empty;

	ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 3)
		Z_PARAM_OBJECT_OF_CLASS(node, php_cmark_node_ce)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(arg.options)
		Z_PARAM_LONG(arg.width)
	ZEND_PARSE_PARAMETERS_END();

	php_cmark_render(
		return_value,
		php_cmark_node_fetch(node), 
		(php_cmark_render_func) cmark_render_latex,
		&arg, 1);
}

PHP_MINIT_FUNCTION(CommonMark_Render) 
{
	zend_class_entry ce;

	REGISTER_NS_LONG_CONSTANT("CommonMark\\Render", "Normal", CMARK_OPT_DEFAULT, CONST_CS|CONST_PERSISTENT);
	REGISTER_NS_LONG_CONSTANT("CommonMark\\Render", "SourcePos", CMARK_OPT_SOURCEPOS, CONST_CS|CONST_PERSISTENT);
	REGISTER_NS_LONG_CONSTANT("CommonMark\\Render", "HardBreaks", CMARK_OPT_HARDBREAKS, CONST_CS|CONST_PERSISTENT);
	REGISTER_NS_LONG_CONSTANT("CommonMark\\Render", "Safe", CMARK_OPT_SAFE, CONST_CS|CONST_PERSISTENT);
	REGISTER_NS_LONG_CONSTANT("CommonMark\\Render", "NoBreaks", CMARK_OPT_NOBREAKS, CONST_CS|CONST_PERSISTENT);

	return SUCCESS;
}

PHP_RINIT_FUNCTION(CommonMark_Render)
{
	return SUCCESS;
}
#endif
