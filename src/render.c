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

PHP_FUNCTION(CommonMark_Render)
{
	zval *z;
	php_cmark_node_t *n;
	zend_long options = 0;
	zend_long width = 0;
	char *c;

	if (php_cmark_parse_parameters("O|ll", &z, php_cmark_node_ce, &options, &width) != SUCCESS) {
		php_cmark_wrong_parameters(
			"node, with optional options and width expected");
		return;
	}

	n = php_cmark_node_fetch(z);
	
	ZVAL_STRING(return_value, 
		(c = cmark_render_commonmark(n->node, options, width)));

	efree(c);
}


PHP_FUNCTION(CommonMark_Render_XML)
{
	zval *z;
	php_cmark_node_t *n;
	zend_long options = 0;
	char *c;

	if (php_cmark_parse_parameters("O|l", &z, php_cmark_node_ce, &options) != SUCCESS) {
		php_cmark_wrong_parameters(
			"node, with optional options");
		return;
	}

	n = php_cmark_node_fetch(z);

	ZVAL_STRING(return_value, 
		(c = cmark_render_xml(n->node, options)));

	efree(c);
}

PHP_FUNCTION(CommonMark_Render_HTML)
{
	zval *z;
	php_cmark_node_t *n;
	zend_long options = 0;
	char *c;

	if (php_cmark_parse_parameters("O|l", &z, php_cmark_node_ce, &options) != SUCCESS) {
		php_cmark_wrong_parameters(
			"node, with optional options");
		return;
	}

	n = php_cmark_node_fetch(z);
	
	ZVAL_STRING(return_value, 
		(c = cmark_render_html(n->node, options)));

	efree(c);
}

PHP_FUNCTION(CommonMark_Render_Man)
{
	zval *z;
	php_cmark_node_t *n;
	zend_long options = 0;
	zend_long width = 0;
	char *c;

	if (php_cmark_parse_parameters("O|ll", &z, php_cmark_node_ce, &options, &width) != SUCCESS) {
		php_cmark_wrong_parameters(
			"node, with optional options and width expected");
		return;
	}

	n = php_cmark_node_fetch(z);
	
	ZVAL_STRING(return_value, 
		(c = cmark_render_man(n->node, options, width)));

	efree(c);
}

PHP_FUNCTION(CommonMark_Render_Latex)
{
	zval *z;
	php_cmark_node_t *n;
	zend_long options = 0;
	zend_long width = 0;
	char *c;

	if (php_cmark_parse_parameters("O|ll", &z, php_cmark_node_ce, &options, &width) != SUCCESS) {
		php_cmark_wrong_parameters(
			"node, with optional options and width expected");
		return;
	}

	n = php_cmark_node_fetch(z);
	
	ZVAL_STRING(return_value, 
		(c = cmark_render_latex(n->node, options, width)));

	efree(c);
}

PHP_MINIT_FUNCTION(CommonMark_Render) 
{
	zend_class_entry ce;

	REGISTER_NS_LONG_CONSTANT("CommonMark\\Render", "Default", CMARK_OPT_DEFAULT, CONST_CS|CONST_PERSISTENT);
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
