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
#ifndef PHP_CMARK_NODE_BREAK
#define PHP_CMARK_NODE_BREAK

#include <php.h>

#include <src/common.h>
#include <src/node.h>

zend_class_entry *php_cmark_node_thematic_break_ce;
zend_class_entry *php_cmark_node_soft_break_ce;
zend_class_entry *php_cmark_node_line_break_ce;

PHP_METHOD(ThematicBreak, __construct)
{
	php_cmark_no_parameters();

	php_cmark_node_new(getThis(), CMARK_NODE_THEMATIC_BREAK);
}

static zend_function_entry php_cmark_node_thematic_break_methods[] = {
	PHP_ME(ThematicBreak, __construct, php_cmark_no_arginfo, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

PHP_METHOD(SoftBreak, __construct)
{
	php_cmark_no_parameters();

	php_cmark_node_new(getThis(), CMARK_NODE_SOFTBREAK);
}

static zend_function_entry php_cmark_node_soft_break_methods[] = {
	PHP_ME(SoftBreak, __construct, php_cmark_no_arginfo, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

PHP_METHOD(LineBreak, __construct)
{
	php_cmark_no_parameters();

	php_cmark_node_new(getThis(), CMARK_NODE_LINEBREAK);
}

static zend_function_entry php_cmark_node_line_break_methods[] = {
	PHP_ME(LineBreak, __construct, php_cmark_no_arginfo, ZEND_ACC_PUBLIC)
	PHP_FE_END
};


PHP_MINIT_FUNCTION(CommonMark_Node_Break) 
{
	zend_class_entry ce;

	INIT_NS_CLASS_ENTRY(ce, "CommonMark\\Node", "ThematicBreak", php_cmark_node_thematic_break_methods);

	php_cmark_node_thematic_break_ce = zend_register_internal_class_ex(&ce, php_cmark_node_ce);

	INIT_NS_CLASS_ENTRY(ce, "CommonMark\\Node", "SoftBreak", php_cmark_node_soft_break_methods);

	php_cmark_node_soft_break_ce = zend_register_internal_class_ex(&ce, php_cmark_node_ce);

	INIT_NS_CLASS_ENTRY(ce, "CommonMark\\Node", "LineBreak", php_cmark_node_line_break_methods);

	php_cmark_node_line_break_ce = zend_register_internal_class_ex(&ce, php_cmark_node_ce);

	return SUCCESS;
}

PHP_RINIT_FUNCTION(CommonMark_Node_Break)
{
	php_cmark_node_thematic_break_ce->ce_flags |= ZEND_ACC_FINAL;
	php_cmark_node_soft_break_ce->ce_flags |= ZEND_ACC_FINAL;
	php_cmark_node_line_break_ce->ce_flags |= ZEND_ACC_FINAL;

	return SUCCESS;
}
#endif
