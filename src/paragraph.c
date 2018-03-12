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
#ifndef PHP_CMARK_NODE_PARAGRAPH
#define PHP_CMARK_NODE_PARAGRAPH

#include <php.h>

#include <src/common.h>
#include <src/node.h>

zend_class_entry *php_cmark_node_paragraph_ce;

PHP_METHOD(Paragraph, __construct)
{
	php_cmark_no_parameters();

	php_cmark_node_new(getThis(), CMARK_NODE_PARAGRAPH);
}

static zend_function_entry php_cmark_node_paragraph_methods[] = {
	PHP_ME(Paragraph, __construct, php_cmark_no_arginfo, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

PHP_MINIT_FUNCTION(CommonMark_Node_Paragraph) 
{
	zend_class_entry ce;

	INIT_NS_CLASS_ENTRY(ce, "CommonMark\\Node", "Paragraph", php_cmark_node_paragraph_methods);

	php_cmark_node_paragraph_ce = zend_register_internal_class_ex(&ce, php_cmark_node_ce);

	return SUCCESS;
}

PHP_RINIT_FUNCTION(CommonMark_Node_Paragraph)
{
	php_cmark_node_paragraph_ce->ce_flags |= ZEND_ACC_FINAL;

	return SUCCESS;
}
#endif
