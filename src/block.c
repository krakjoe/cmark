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
#ifndef PHP_CMARK_NODE_BLOCK
#define PHP_CMARK_NODE_BLOCK

#include <php.h>

#include <src/common.h>
#include <src/node.h>

zend_class_entry *php_cmark_node_code_block_ce;
zend_class_entry *php_cmark_node_html_block_ce;
zend_class_entry *php_cmark_node_custom_block_ce;

zend_class_entry *php_cmark_node_first_block_ce;
zend_class_entry *php_cmark_node_last_block_ce;

PHP_METHOD(CodeBlock, __construct)
{
	php_cmark_node_t *n = php_cmark_node_fetch(getThis());

	php_cmark_no_parameters();

	n->node = cmark_node_new_with_mem(CMARK_NODE_CODE_BLOCK, &php_cmark_node_mem);
}

static zend_function_entry php_cmark_node_code_block_methods[] = {
	PHP_ME(CodeBlock, __construct, php_cmark_no_arginfo, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

PHP_METHOD(HTMLBlock, __construct)
{
	php_cmark_node_t *n = php_cmark_node_fetch(getThis());

	php_cmark_no_parameters();

	n->node = cmark_node_new_with_mem(CMARK_NODE_HTML_BLOCK, &php_cmark_node_mem);
}

static zend_function_entry php_cmark_node_html_block_methods[] = {
	PHP_ME(HTMLBlock, __construct, php_cmark_no_arginfo, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

PHP_METHOD(CustomBlock, __construct)
{
	php_cmark_node_t *n = php_cmark_node_fetch(getThis());

	php_cmark_no_parameters();

	n->node = cmark_node_new_with_mem(CMARK_NODE_CUSTOM_BLOCK, &php_cmark_node_mem);
}

static zend_function_entry php_cmark_node_custom_block_methods[] = {
	PHP_ME(CustomBlock, __construct, php_cmark_no_arginfo, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

PHP_METHOD(FirstBlock, __construct)
{
	php_cmark_node_t *n = php_cmark_node_fetch(getThis());

	php_cmark_no_parameters();

	n->node = cmark_node_new_with_mem(CMARK_NODE_FIRST_BLOCK, &php_cmark_node_mem);
}

static zend_function_entry php_cmark_node_first_block_methods[] = {
	PHP_ME(FirstBlock, __construct, php_cmark_no_arginfo, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

PHP_METHOD(LastBlock, __construct)
{
	php_cmark_node_t *n = php_cmark_node_fetch(getThis());

	php_cmark_no_parameters();

	n->node = cmark_node_new_with_mem(CMARK_NODE_LAST_BLOCK, &php_cmark_node_mem);
}

static zend_function_entry php_cmark_node_last_block_methods[] = {
	PHP_ME(LastBlock, __construct, php_cmark_no_arginfo, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

PHP_MINIT_FUNCTION(CommonMark_Node_Block) 
{
	zend_class_entry ce;

	INIT_NS_CLASS_ENTRY(ce, "CommonMark\\Node", "CodeBlock", php_cmark_node_code_block_methods);

	php_cmark_node_code_block_ce = zend_register_internal_class_ex(&ce, php_cmark_node_ce);

	INIT_NS_CLASS_ENTRY(ce, "CommonMark\\Node", "HTMLBlock", php_cmark_node_html_block_methods);

	php_cmark_node_html_block_ce = zend_register_internal_class_ex(&ce, php_cmark_node_ce);

	INIT_NS_CLASS_ENTRY(ce, "CommonMark\\Node", "CustomBlock", php_cmark_node_custom_block_methods);

	php_cmark_node_custom_block_ce = zend_register_internal_class_ex(&ce, php_cmark_node_ce);

	INIT_NS_CLASS_ENTRY(ce, "CommonMark\\Node", "FirstBlock", php_cmark_node_first_block_methods);

	php_cmark_node_first_block_ce = zend_register_internal_class_ex(&ce, php_cmark_node_ce);

	INIT_NS_CLASS_ENTRY(ce, "CommonMark\\Node", "LastBlock", php_cmark_node_last_block_methods);

	php_cmark_node_last_block_ce = zend_register_internal_class_ex(&ce, php_cmark_node_ce);

	return SUCCESS;
}

PHP_RINIT_FUNCTION(CommonMark_Node_Block)
{
	php_cmark_node_code_block_ce->ce_flags |= ZEND_ACC_FINAL;
	php_cmark_node_html_block_ce->ce_flags |= ZEND_ACC_FINAL;
	php_cmark_node_custom_block_ce->ce_flags |= ZEND_ACC_FINAL;
	php_cmark_node_first_block_ce->ce_flags |= ZEND_ACC_FINAL;
	php_cmark_node_last_block_ce->ce_flags |= ZEND_ACC_FINAL;

	return SUCCESS;
}
#endif
