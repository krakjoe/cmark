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
#ifndef PHP_CMARK_NODE_INLINE
#define PHP_CMARK_NODE_INLINE

#include <php.h>

#include <src/common.h>
#include <src/node.h>
#include <src/custom.h>
#include <src/text.h>
#include <src/handlers.h>

zend_class_entry *php_cmark_node_html_inline_ce;
zend_class_entry *php_cmark_node_custom_inline_ce;

ZEND_BEGIN_ARG_INFO_EX(php_cmark_node_html_inline_construct, 0, 0, 0)
	ZEND_ARG_INFO(0, literal)
ZEND_END_ARG_INFO()

PHP_METHOD(HTMLInline, __construct)
{
	php_cmark_node_text_t *n = php_cmark_node_text_fetch(getThis());
	zval *literal = NULL;

	if (php_cmark_parse_parameters("|z", &literal) != SUCCESS ||
	    (literal && Z_TYPE_P(literal) != IS_STRING)) {
		php_cmark_wrong_parameters("literal expected");
	}

	php_cmark_node_new(getThis(), CMARK_NODE_HTML_INLINE);

	if (literal) {
		php_cmark_node_write_str(&n->h, 
			(cmark_node_write_str) cmark_node_set_literal, 
			literal, &n->literal);
	}
}

static zend_function_entry php_cmark_node_html_inline_methods[] = {
	PHP_ME(HTMLInline, __construct, php_cmark_node_html_inline_construct, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

PHP_METHOD(CustomInline, __construct)
{
	php_cmark_no_parameters();

	php_cmark_node_new(getThis(), CMARK_NODE_CUSTOM_INLINE);
}

static zend_function_entry php_cmark_node_custom_inline_methods[] = {
	PHP_ME(CustomInline, __construct, php_cmark_no_arginfo, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

PHP_MINIT_FUNCTION(CommonMark_Node_Inline) 
{
	zend_class_entry ce;

	INIT_NS_CLASS_ENTRY(ce, "CommonMark\\Node", "HTMLInline", php_cmark_node_html_inline_methods);

	php_cmark_node_html_inline_ce = zend_register_internal_class_ex(&ce, php_cmark_node_text_ce);

	INIT_NS_CLASS_ENTRY(ce, "CommonMark\\Node", "CustomInline", php_cmark_node_custom_inline_methods);

	php_cmark_node_custom_inline_ce = zend_register_internal_class_ex(&ce, php_cmark_node_ce);
	php_cmark_node_custom_inline_ce->create_object = php_cmark_node_custom_create;

#define php_cmark_node_custom_inline_property(n) \
	zend_declare_property_null(php_cmark_node_custom_inline_ce, ZEND_STRL(n), ZEND_ACC_PUBLIC)

	php_cmark_node_custom_inline_property("onEnter");
	php_cmark_node_custom_inline_property("onLeave");
#undef php_cmark_node_custom_inline_property

	return SUCCESS;
}

PHP_RINIT_FUNCTION(CommonMark_Node_Inline)
{
	php_cmark_node_html_inline_ce->ce_flags |= ZEND_ACC_FINAL;
	php_cmark_node_custom_inline_ce->ce_flags |= ZEND_ACC_FINAL;

	return SUCCESS;
}
#endif
