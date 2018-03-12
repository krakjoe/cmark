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
#ifndef PHP_CMARK_NODE
#define PHP_CMARK_NODE

#include <php.h>

#include <ext/spl/spl_exceptions.h>

#include <zend_exceptions.h>

#include <src/common.h>
#include <src/node.h>
#include <src/document.h>
#include <src/quote.h>
#include <src/list.h>
#include <src/item.h>
#include <src/block.h>
#include <src/paragraph.h>
#include <src/heading.h>
#include <src/break.h>
#include <src/text.h>
#include <src/code.h>
#include <src/inline.h>
#include <src/media.h>

zend_class_entry*      php_cmark_node_ce;
zend_object_handlers   php_cmark_node_handlers;
cmark_mem              php_cmark_node_mem;

zend_class_entry* php_cmark_node_class(cmark_node* node) {
	switch (cmark_node_get_type(node)) {
		case CMARK_NODE_DOCUMENT:
			return php_cmark_node_document_ce;
		case CMARK_NODE_BLOCK_QUOTE:
			return php_cmark_node_quote_ce;
		case CMARK_NODE_LIST:
			return php_cmark_node_list_ce;
		case CMARK_NODE_ITEM:
			return php_cmark_node_item_ce;
		case CMARK_NODE_CODE_BLOCK:
			return php_cmark_node_code_block_ce;
		case CMARK_NODE_HTML_BLOCK:
			return php_cmark_node_html_block_ce;
		case CMARK_NODE_CUSTOM_BLOCK:
			return php_cmark_node_custom_block_ce;
		case CMARK_NODE_PARAGRAPH:
			return php_cmark_node_paragraph_ce;
		case CMARK_NODE_HEADING:
			return php_cmark_node_heading_ce;
		case CMARK_NODE_THEMATIC_BREAK:
			return php_cmark_node_thematic_break_ce;
		case CMARK_NODE_TEXT:
			return php_cmark_node_text_ce;
		case CMARK_NODE_CODE:
			return php_cmark_node_code_ce;
		case CMARK_NODE_HTML_INLINE:
			return php_cmark_node_html_inline_ce;
		case CMARK_NODE_CUSTOM_INLINE:
			return php_cmark_node_custom_inline_ce;
		case CMARK_NODE_IMAGE:
			return php_cmark_node_image_ce;
		case CMARK_NODE_LINK:
			return php_cmark_node_link_ce;
	}

	return php_cmark_node_ce;
}

zend_object* php_cmark_node_create(zend_class_entry *ce) {
	php_cmark_node_t *n = 
		(php_cmark_node_t*) 
			ecalloc(1, sizeof(php_cmark_node_t));

	zend_object_std_init(&n->std, ce);

	n->std.handlers = &php_cmark_node_handlers;	
	n->shadow = 0;

	return &n->std;
}

void php_cmark_node_shadow(zval *return_value, cmark_node *node) {
	php_cmark_node_t *n;

	if (!node) {
		return;
	}

	object_init_ex(return_value, php_cmark_node_class(node));

	n = php_cmark_node_fetch(return_value);
	n->node = node;
	n->shadow = 1;
}

void php_cmark_node_free(zend_object *zo) {
	php_cmark_node_t *n = php_cmark_node_from(zo);

	if (n->node) {
		if (!n->shadow && cmark_node_parent(n->node) == NULL) {
			cmark_node_free(n->node);
		}
	}

	zend_object_std_dtor(&n->std);
}

PHP_METHOD(Node, getNext)
{
	php_cmark_node_t *n = php_cmark_node_fetch(getThis());

	php_cmark_no_parameters();

	php_cmark_node_shadow(return_value, cmark_node_next(n->node));
}

PHP_METHOD(Node, getPrevious)
{
	php_cmark_node_t *n = php_cmark_node_fetch(getThis());

	php_cmark_no_parameters();

	php_cmark_node_shadow(return_value, cmark_node_previous(n->node));
}

PHP_METHOD(Node, getParent)
{
	php_cmark_node_t *n = php_cmark_node_fetch(getThis());

	php_cmark_no_parameters();

	php_cmark_node_shadow(return_value, cmark_node_parent(n->node));
}

PHP_METHOD(Node, getFirstChild)
{
	php_cmark_node_t *n = php_cmark_node_fetch(getThis());

	php_cmark_no_parameters();

	php_cmark_node_shadow(return_value, cmark_node_first_child(n->node));
}

PHP_METHOD(Node, getLastChild)
{
	php_cmark_node_t *n = php_cmark_node_fetch(getThis());

	php_cmark_no_parameters();

	php_cmark_node_shadow(return_value, cmark_node_last_child(n->node));
}

ZEND_BEGIN_ARG_INFO_EX(php_cmark_node_add, 0, 0, 1)
	ZEND_ARG_INFO(0, child)
ZEND_END_ARG_INFO()

PHP_METHOD(Node, appendChild)
{
	php_cmark_node_t *n = php_cmark_node_fetch(getThis());
	zval *child;

	if (php_cmark_parse_parameters("O", &child, php_cmark_node_ce) != SUCCESS) {
		php_cmark_wrong_parameters("node expected");
		return;
	}

	if (!cmark_node_append_child(n->node, php_cmark_node_fetch(child)->node)) {
		php_cmark_throw(
			"%s may not have %s children",
			ZSTR_VAL(n->std.ce->name),
			ZSTR_VAL(Z_OBJCE_P(child)->name));
		return;
	}

	php_cmark_chain();
}

PHP_METHOD(Node, prependChild)
{
	php_cmark_node_t *n = php_cmark_node_fetch(getThis());
	zval *child;

	if (php_cmark_parse_parameters("O", &child, php_cmark_node_ce) != SUCCESS) {
		php_cmark_wrong_parameters("node expected");
		return;
	}

	if (!cmark_node_prepend_child(n->node, php_cmark_node_fetch(child)->node)) {
		php_cmark_throw(
			"%s may not have %s children",
			ZSTR_VAL(n->std.ce->name),
			ZSTR_VAL(Z_OBJCE_P(child)->name));
		return;
	}

	php_cmark_chain();
}

ZEND_BEGIN_ARG_INFO_EX(php_cmark_node_insert, 0, 0, 1)
	ZEND_ARG_INFO(0, sibling)
ZEND_END_ARG_INFO()

PHP_METHOD(Node, insertBefore)
{
	php_cmark_node_t *n = php_cmark_node_fetch(getThis());
	zval *sibling;

	if (php_cmark_parse_parameters("O", &sibling, php_cmark_node_ce) != SUCCESS) {
		php_cmark_wrong_parameters("node expected");
		return;
	}

	if (!cmark_node_insert_before(n->node, php_cmark_node_fetch(sibling)->node)) {
		php_cmark_throw(
			"%s may not have %s siblings",
			ZSTR_VAL(n->std.ce->name),
			ZSTR_VAL(Z_OBJCE_P(sibling)->name));
		return;
	}

	php_cmark_chain();
}

PHP_METHOD(Node, insertAfter)
{
	php_cmark_node_t *n = php_cmark_node_fetch(getThis());
	zval *sibling;

	if (php_cmark_parse_parameters("O", &sibling, php_cmark_node_ce) != SUCCESS) {
		php_cmark_wrong_parameters("node expected");
		return;
	}

	if (!cmark_node_insert_after(n->node, php_cmark_node_fetch(sibling)->node)) {
		php_cmark_throw(
			"%s may not have %s siblings",
			ZSTR_VAL(n->std.ce->name),
			ZSTR_VAL(Z_OBJCE_P(sibling)->name));
		return;
	}
	
	php_cmark_chain();
}

static zend_function_entry php_cmark_node_type_methods[] = {
	PHP_ME(Node, getNext, php_cmark_no_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(Node, getPrevious, php_cmark_no_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(Node, getParent, php_cmark_no_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(Node, getFirstChild, php_cmark_no_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(Node, getLastChild, php_cmark_no_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(Node, appendChild, php_cmark_node_add, ZEND_ACC_PUBLIC)
	PHP_ME(Node, prependChild, php_cmark_node_add, ZEND_ACC_PUBLIC)
	PHP_ME(Node, insertBefore, php_cmark_node_insert, ZEND_ACC_PUBLIC)
	PHP_ME(Node, insertAfter, php_cmark_node_insert, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

void* php_cmark_node_calloc_func(size_t n, size_t s) { return ecalloc(n, s); }
void* php_cmark_node_realloc_func(void *p, size_t s) { return erealloc(p ,s); }
void  php_cmark_node_free_func(void *p)              { efree(p); }

PHP_MINIT_FUNCTION(CommonMark_Node) {
	zend_class_entry ce;

	INIT_NS_CLASS_ENTRY(ce, "CommonMark", "Node", php_cmark_node_type_methods);

	php_cmark_node_ce = zend_register_internal_class(&ce);
	php_cmark_node_ce->create_object = php_cmark_node_create;

	memcpy(&php_cmark_node_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

	php_cmark_node_handlers.free_obj = php_cmark_node_free;
	php_cmark_node_handlers.offset = XtOffsetOf(php_cmark_node_t, std);

	php_cmark_node_mem.calloc = php_cmark_node_calloc_func;
	php_cmark_node_mem.realloc = php_cmark_node_realloc_func;
	php_cmark_node_mem.free = php_cmark_node_free_func;

	return SUCCESS;
}

PHP_RINIT_FUNCTION(CommonMark_Node)
{
	php_cmark_node_ce->ce_flags |= ZEND_ACC_FINAL|ZEND_ACC_EXPLICIT_ABSTRACT_CLASS;

	return SUCCESS;
}
#endif
