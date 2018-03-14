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

#define php_cmark_render_arg_null {0, 0}

typedef char* (*php_cmark_render_func) (cmark_node *, zend_long, zend_long);

static inline void php_cmark_render(
		zval *return_value,
		php_cmark_render_func func,
		php_cmark_node_t *node, 
		php_cmark_render_arg_t *arg) {
	char *buffer = func(node->node, arg->options, arg->width);

	ZEND_ASSERT(buffer);

	ZVAL_STRING(return_value, buffer);
	
	efree(buffer);
}

PHP_FUNCTION(CommonMark_Render)
{
	zval *z;
	php_cmark_render_arg_t arg = php_cmark_render_arg_null;

	ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 3)
		Z_PARAM_OBJECT_OF_CLASS(z, php_cmark_node_ce)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(arg.options)
		Z_PARAM_LONG(arg.width)
	ZEND_PARSE_PARAMETERS_END();

	php_cmark_render(return_value, 
		(php_cmark_render_func) cmark_render_commonmark, 
		php_cmark_node_fetch(z), &arg);
}


PHP_FUNCTION(CommonMark_Render_XML)
{
	zval *z;
	php_cmark_render_arg_t arg = php_cmark_render_arg_null;

	ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 2)
		Z_PARAM_OBJECT_OF_CLASS(z, php_cmark_node_ce)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(arg.options)
	ZEND_PARSE_PARAMETERS_END();

	php_cmark_render(return_value, 
		(php_cmark_render_func) cmark_render_xml, 
		php_cmark_node_fetch(z), &arg);
}

PHP_FUNCTION(CommonMark_Render_HTML)
{
	zval *z;
	php_cmark_render_arg_t arg = php_cmark_render_arg_null;

	ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 2)
		Z_PARAM_OBJECT_OF_CLASS(z, php_cmark_node_ce)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(arg.options)
	ZEND_PARSE_PARAMETERS_END();

	php_cmark_render(return_value, 
		(php_cmark_render_func) cmark_render_html, 
		php_cmark_node_fetch(z), &arg);
}

PHP_FUNCTION(CommonMark_Render_Man)
{
	zval *z;
	php_cmark_render_arg_t arg = php_cmark_render_arg_null;

	ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 3)
		Z_PARAM_OBJECT_OF_CLASS(z, php_cmark_node_ce)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(arg.options)
		Z_PARAM_LONG(arg.width)
	ZEND_PARSE_PARAMETERS_END();

	php_cmark_render(return_value, 
		(php_cmark_render_func) cmark_render_man, 
		php_cmark_node_fetch(z), &arg);
}

PHP_FUNCTION(CommonMark_Render_Latex)
{
	zval *z;
	php_cmark_render_arg_t arg = php_cmark_render_arg_null;

	ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 3)
		Z_PARAM_OBJECT_OF_CLASS(z, php_cmark_node_ce)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(arg.options)
		Z_PARAM_LONG(arg.width)
	ZEND_PARSE_PARAMETERS_END();

	php_cmark_render(return_value, 
		(php_cmark_render_func) cmark_render_latex, 
		php_cmark_node_fetch(z), &arg);
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
