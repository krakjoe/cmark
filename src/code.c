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
#ifndef PHP_CMARK_NODE_CODE
#define PHP_CMARK_NODE_CODE

#include <php.h>

#include <src/common.h>
#include <src/node.h>
#include <src/text.h>
#include <src/handlers.h>

zend_class_entry *php_cmark_node_code_ce;

ZEND_BEGIN_ARG_INFO_EX(php_cmark_node_code_construct, 0, 0, 0)
	ZEND_ARG_INFO(0, literal)
ZEND_END_ARG_INFO()

PHP_METHOD(Code, __construct)
{
	php_cmark_node_text_t *n = php_cmark_node_text_fetch(getThis());
	zval *literal = NULL;

	if (php_cmark_parse_parameters("|z", &literal) != SUCCESS ||
	    (literal && Z_TYPE_P(literal) != IS_STRING)) {
		php_cmark_wrong_parameters("literal expected");
	}

	php_cmark_node_new(getThis(), CMARK_NODE_CODE);

	if (literal) {
		php_cmark_node_write_str(&n->h, 
			(cmark_node_write_str) cmark_node_set_literal, 
			literal, &n->literal);
	}
}

static zend_function_entry php_cmark_node_code_methods[] = {
	PHP_ME(Code, __construct, php_cmark_node_code_construct, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

PHP_MINIT_FUNCTION(CommonMark_Node_Code) 
{
	zend_class_entry ce;

	INIT_NS_CLASS_ENTRY(ce, "CommonMark\\Node", "Code", php_cmark_node_code_methods);

	php_cmark_node_code_ce = zend_register_internal_class_ex(&ce, php_cmark_node_text_ce);

	return SUCCESS;
}

PHP_RINIT_FUNCTION(CommonMark_Node_Code)
{
	php_cmark_node_code_ce->ce_flags |= ZEND_ACC_FINAL;

	return SUCCESS;
}
#endif
