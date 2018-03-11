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
#ifndef PHP_CMARK_LIST
#define PHP_CMARK_LIST

#include <php.h>

#include <ext/spl/spl_exceptions.h>

#include <zend_exceptions.h>

#include <cmark.h>

#include <src/common.h>
#include <src/node.h>
#include <src/list.h>

zend_class_entry*      php_cmark_node_list_ce;
zend_class_entry*      php_cmark_node_list_ordered_ce;
zend_class_entry*      php_cmark_node_list_bullet_ce;

ZEND_BEGIN_ARG_INFO_EX(php_cmark_node_list_set_tight, 0, 0, 1)
	ZEND_ARG_INFO(0, tightness)
ZEND_END_ARG_INFO()

PHP_METHOD(List, setTight)
{
	php_cmark_node_t *n = php_cmark_node_fetch(getThis());
	zend_bool tight;

	if (php_cmark_parse_parameters("b", &tight) != SUCCESS) {
		php_cmark_wrong_parameters("tightness expected");
		return;
	}

	cmark_node_set_list_tight(n->node, tight);

	php_cmark_chain();
}

PHP_METHOD(List, isTight)
{
	php_cmark_node_t *n = php_cmark_node_fetch(getThis());

	php_cmark_no_parameters();

	RETURN_BOOL(cmark_node_get_list_tight(n->node));
}

PHP_METHOD(List, setDelimitPeriod)
{
	php_cmark_node_t *n = php_cmark_node_fetch(getThis());
	zend_long type;

	php_cmark_no_parameters();

	cmark_node_set_list_delim(n->node, CMARK_PERIOD_DELIM);

	php_cmark_chain();
}

PHP_METHOD(List, setDelimitParen)
{
	php_cmark_node_t *n = php_cmark_node_fetch(getThis());
	zend_long type;

	php_cmark_no_parameters();

	cmark_node_set_list_delim(n->node, CMARK_PAREN_DELIM);

	php_cmark_chain();
}

PHP_METHOD(List, hasPeriodDelim)
{
	php_cmark_node_t *n = php_cmark_node_fetch(getThis());

	php_cmark_no_parameters();

	RETURN_BOOL(cmark_node_get_list_delim(n->node) == CMARK_PERIOD_DELIM);	
}

PHP_METHOD(List, hasParenDelim)
{
	php_cmark_node_t *n = php_cmark_node_fetch(getThis());

	php_cmark_no_parameters();

	RETURN_BOOL(cmark_node_get_list_delim(n->node) == CMARK_PAREN_DELIM);	
}

static zend_function_entry php_cmark_node_list_methods[] = {
	PHP_ME(List, setTight, php_cmark_node_list_set_tight, ZEND_ACC_PUBLIC)
	PHP_ME(List, isTight, php_cmark_no_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(List, setDelimitPeriod, php_cmark_no_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(List, setDelimitParen, php_cmark_no_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(List, hasPeriodDelim, php_cmark_no_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(List, hasParenDelim, php_cmark_no_arginfo, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

PHP_METHOD(OrderedList, __construct)
{
	php_cmark_node_t *n = php_cmark_node_fetch(getThis());

	php_cmark_no_parameters();

	n->node = cmark_node_new_with_mem(
		CMARK_NODE_LIST, &php_cmark_node_mem);

	cmark_node_set_list_type(n->node, CMARK_ORDERED_LIST);
}

PHP_METHOD(OrderedList, getStart)
{
	php_cmark_node_t *n = php_cmark_node_fetch(getThis());

	php_cmark_no_parameters();

	RETURN_LONG(cmark_node_get_list_start(n->node));
}

ZEND_BEGIN_ARG_INFO_EX(php_cmark_node_list_ordered_set_start, 0, 0, 1)
	ZEND_ARG_INFO(0, start)
ZEND_END_ARG_INFO()

PHP_METHOD(OrderedList, setStart)
{
	php_cmark_node_t *n = php_cmark_node_fetch(getThis());
	zend_long start;

	if (php_cmark_parse_parameters("l", &start) != SUCCESS) {
		php_cmark_wrong_parameters("start expected");
		return;
	}

	if (start < 1) {
		php_cmark_wrong_parameters("start must be a positive integer");
		return;
	}

	cmark_node_set_list_start(n->node, start);

	php_cmark_chain();
}

static zend_function_entry php_cmark_node_list_ordered_methods[] = {
	PHP_ME(OrderedList, __construct, php_cmark_no_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(OrderedList, getStart, php_cmark_no_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(OrderedList, setStart, php_cmark_node_list_ordered_set_start, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

PHP_METHOD(BulletList, __construct)
{
	php_cmark_node_t *n = php_cmark_node_fetch(getThis());

	php_cmark_no_parameters();

	n->node = cmark_node_new_with_mem(
		CMARK_NODE_LIST, &php_cmark_node_mem);

	cmark_node_set_list_type(n->node, CMARK_BULLET_LIST);
}

static zend_function_entry php_cmark_node_list_bullet_methods[] = {
	PHP_ME(BulletList, __construct, php_cmark_no_arginfo, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

PHP_MINIT_FUNCTION(CommonMark_Node_List) {
	zend_class_entry ce;

	INIT_NS_CLASS_ENTRY(ce, "CommonMark\\Node", "List", php_cmark_node_list_methods);

	php_cmark_node_list_ce = zend_register_internal_class_ex(&ce, php_cmark_node_ce);

	INIT_NS_CLASS_ENTRY(ce, "CommonMark\\Node", "OrderedList", php_cmark_node_list_ordered_methods);
	
	php_cmark_node_list_ordered_ce = zend_register_internal_class_ex(&ce, php_cmark_node_list_ce);

	INIT_NS_CLASS_ENTRY(ce, "CommonMark\\Node", "BulletList", php_cmark_node_list_bullet_methods);

	php_cmark_node_list_bullet_ce = zend_register_internal_class_ex(&ce, php_cmark_node_list_ce);

	return SUCCESS;
}

PHP_RINIT_FUNCTION(CommonMark_Node_List)
{
	php_cmark_node_list_ce->ce_flags |= ZEND_ACC_FINAL|ZEND_ACC_EXPLICIT_ABSTRACT_CLASS;
	php_cmark_node_list_ordered_ce->ce_flags |= ZEND_ACC_FINAL;
	php_cmark_node_list_bullet_ce->ce_flags |= ZEND_ACC_FINAL;

	return SUCCESS;
}
#endif
