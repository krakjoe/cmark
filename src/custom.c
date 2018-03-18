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
#ifndef PHP_CMARK_NODE_CUSTOM
#define PHP_CMARK_NODE_CUSTOM

#include <php.h>

#include <cmark.h>

#include <src/common.h>
#include <src/node.h>

PHP_METHOD(Custom, setOnEnter) 
{
	php_cmark_node_t *n = php_cmark_node_fetch(getThis());
	zend_string *literal;

	if (php_cmark_parse_parameters("S", &literal) != SUCCESS) {
		php_cmark_wrong_parameters("literal expected");
		return;
	}

	cmark_node_set_on_enter(n->node, ZSTR_VAL(literal));

	php_cmark_chain();
}

PHP_METHOD(Custom, setOnLeave) 
{
	php_cmark_node_t *n = php_cmark_node_fetch(getThis());
	zend_string *literal;

	if (php_cmark_parse_parameters("S", &literal) != SUCCESS) {
		php_cmark_wrong_parameters("literal expected");
		return;
	}

	cmark_node_set_on_exit(n->node, ZSTR_VAL(literal));

	php_cmark_chain();
}

PHP_METHOD(Custom, getOnEnter) 
{
	php_cmark_node_t *n = php_cmark_node_fetch(getThis());
	const char *c;

	php_cmark_no_parameters();

	c = cmark_node_get_on_enter(n->node);

	if (!c || !c[0]) {
		return;
	}

	RETURN_STRING(c);
}

PHP_METHOD(Custom, getOnLeave) 
{
	php_cmark_node_t *n = php_cmark_node_fetch(getThis());
	const char *c;

	php_cmark_no_parameters();

	c = cmark_node_get_on_exit(n->node);

	if (!c || !c[0]) {
		return;
	}

	RETURN_STRING(c);
}
#endif
