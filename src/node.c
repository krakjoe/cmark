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
#include <zend_interfaces.h>

#include <src/common.h>
#include <src/node.h>
#include <src/handlers.h>
#include <src/iterator.h>
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
#include <src/visitor.h>

#include <src/cql.h>

zend_class_entry*      php_cmark_node_ce;
zend_object_handlers   php_cmark_node_handlers;

typedef enum _php_cmark_node_edit_result {
	PHP_CMARK_NODE_EDIT_MISSING,
	PHP_CMARK_NODE_EDIT_USED,
	PHP_CMARK_NODE_EDIT_HANDLER,
	PHP_CMARK_NODE_EDIT_OK
} php_cmark_node_edit_result;

typedef int (*php_cmark_node_edit_f) (cmark_node*, cmark_node*);

static inline php_cmark_node_edit_result php_cmark_node_edit(php_cmark_node_edit_f handler, php_cmark_node_t *object, php_cmark_node_t *arg) {

	if (!arg->owned) {
		return PHP_CMARK_NODE_EDIT_USED;
	}

	if (!handler(object->node, arg->node)) {
		return PHP_CMARK_NODE_EDIT_HANDLER;
	}

	arg->owned = 0;



	return PHP_CMARK_NODE_EDIT_OK;
}

void php_cmark_node_new(zval *object, cmark_node_type type) {
	php_cmark_node_t *n = php_cmark_node_fetch(object);

	n->node = cmark_node_new_with_mem(
		type, &php_cmark_mem);

	n->owned = 1;
}

void php_cmark_node_list_new(zval *object, cmark_list_type type) {
	php_cmark_node_t *n = php_cmark_node_fetch(object);

	n->node = cmark_node_new_with_mem(
		CMARK_NODE_LIST, &php_cmark_mem);

	cmark_node_set_list_type(n->node, type);

	n->owned = 1;
}

zend_class_entry* php_cmark_node_class(cmark_node* node) {
	switch (cmark_node_get_type(node)) {
		case CMARK_NODE_DOCUMENT:
			return php_cmark_node_document_ce;
		case CMARK_NODE_BLOCK_QUOTE:
			return php_cmark_node_quote_ce;
		case CMARK_NODE_LIST: switch (cmark_node_get_list_type(node)) {
			case CMARK_ORDERED_LIST:
				return php_cmark_node_list_ordered_ce;
			case CMARK_BULLET_LIST:
				return php_cmark_node_list_bullet_ce;

			EMPTY_SWITCH_DEFAULT_CASE();
		} break;
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
		case CMARK_NODE_SOFTBREAK:
			return php_cmark_node_soft_break_ce;
		case CMARK_NODE_LINEBREAK:
			return php_cmark_node_line_break_ce;
		case CMARK_NODE_TEXT:
			return php_cmark_node_text_ce;
		case CMARK_NODE_STRONG:
			return php_cmark_node_text_strong_ce;
		case CMARK_NODE_EMPH:
			return php_cmark_node_text_emphasis_ce;
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

		EMPTY_SWITCH_DEFAULT_CASE();
	}

	return php_cmark_node_ce;
}

zend_object* php_cmark_node_create(zend_class_entry *ce) {
	php_cmark_node_t *n = 
		(php_cmark_node_t*) 
			ecalloc(1, sizeof(php_cmark_node_t));

	zend_object_std_init
		(php_cmark_node_zend(n), ce);

	n->std.handlers = &php_cmark_node_handlers;

	return php_cmark_node_zend(n);
}

php_cmark_node_t* php_cmark_node_shadow(zval *return_value, cmark_node *node) {
	php_cmark_node_t *n;
	
	if (!node) {
		return NULL;
	}

	object_init_ex(return_value, php_cmark_node_class(node));

	n = php_cmark_node_fetch(return_value);
	n->node = node;
	n->owned = 0;

	return n;
}

ZEND_BEGIN_ARG_INFO_WITH_RETURN_CLASS(php_cmark_node_add, 0, 1, CommonMark\\Node, 0)
	ZEND_ARG_OBJ_INFO(0, child, CommonMark\\Node, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(Node, appendChild)
{
	zval *child;

	ZEND_BEGIN_PARAMS(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(child, php_cmark_node_ce)
	ZEND_END_PARAMS();

	switch (php_cmark_node_edit(
			cmark_node_append_child,
				php_cmark_node_fetch(getThis()), 
				php_cmark_node_fetch(child))) {
		case PHP_CMARK_NODE_EDIT_MISSING:
		case PHP_CMARK_NODE_EDIT_HANDLER:
			php_cmark_throw(
				"failed to set %s as child of %s",
				ZSTR_VAL(Z_OBJCE_P(child)->name),
				ZSTR_VAL(Z_OBJCE_P(getThis())->name));
			return;

		case PHP_CMARK_NODE_EDIT_USED:
			php_cmark_throw(
				"%s is already in use",
				ZSTR_VAL(Z_OBJCE_P(child)->name));
			return;

		case PHP_CMARK_NODE_EDIT_OK:
			break;
	}

	php_cmark_chain();
}

PHP_METHOD(Node, prependChild)
{
	zval *child;

	ZEND_BEGIN_PARAMS(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(child, php_cmark_node_ce)
	ZEND_END_PARAMS();

	switch (php_cmark_node_edit(
			cmark_node_prepend_child, 
				php_cmark_node_fetch(getThis()), 
				php_cmark_node_fetch(child))) {
		case PHP_CMARK_NODE_EDIT_MISSING:
		case PHP_CMARK_NODE_EDIT_HANDLER:
			php_cmark_throw(
				"failed to set %s as child of %s",
				ZSTR_VAL(Z_OBJCE_P(child)->name),
				ZSTR_VAL(Z_OBJCE_P(getThis())->name));
			return;

		case PHP_CMARK_NODE_EDIT_USED:
			php_cmark_throw(
				"%s is already in use",
				ZSTR_VAL(Z_OBJCE_P(child)->name));
			return;

		case PHP_CMARK_NODE_EDIT_OK:
			break;
	}

	php_cmark_chain();
}

ZEND_BEGIN_ARG_INFO_WITH_RETURN_CLASS(php_cmark_node_insert, 0, 1, CommonMark\\Node, 0)
	ZEND_ARG_OBJ_INFO(0, sibling, CommonMark\\Node, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(Node, insertBefore)
{
	zval *sibling;

	ZEND_BEGIN_PARAMS(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(sibling, php_cmark_node_ce)
	ZEND_END_PARAMS();

	switch (php_cmark_node_edit(
			cmark_node_insert_before, 
				php_cmark_node_fetch(getThis()), 
				php_cmark_node_fetch(sibling))) {
		case PHP_CMARK_NODE_EDIT_MISSING:
		case PHP_CMARK_NODE_EDIT_HANDLER:
			php_cmark_throw(
				"failed to set %s as sibling of %s",
				ZSTR_VAL(Z_OBJCE_P(sibling)->name),
				ZSTR_VAL(Z_OBJCE_P(getThis())->name));
			return;

		case PHP_CMARK_NODE_EDIT_USED:
			php_cmark_throw(
				"%s is already in use",
				ZSTR_VAL(Z_OBJCE_P(sibling)->name));
			return;

		case PHP_CMARK_NODE_EDIT_OK:
			break;
	}

	php_cmark_chain();
}

PHP_METHOD(Node, insertAfter)
{
	zval *sibling;

	ZEND_BEGIN_PARAMS(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(sibling, php_cmark_node_ce)
	ZEND_END_PARAMS();

	switch (php_cmark_node_edit(
			cmark_node_insert_after, 
				php_cmark_node_fetch(getThis()), 
				php_cmark_node_fetch(sibling))) {
		case PHP_CMARK_NODE_EDIT_MISSING:
		case PHP_CMARK_NODE_EDIT_HANDLER:
			php_cmark_throw(
				"failed to set %s as sibling of %s",
				ZSTR_VAL(Z_OBJCE_P(sibling)->name),
				ZSTR_VAL(Z_OBJCE_P(getThis())->name));
			return;

		case PHP_CMARK_NODE_EDIT_USED:
			php_cmark_throw(
				"%s is already in use",
				ZSTR_VAL(Z_OBJCE_P(sibling)->name));
			return;

		case PHP_CMARK_NODE_EDIT_OK:
			break;
	}
	
	php_cmark_chain();
}

ZEND_BEGIN_ARG_INFO_WITH_RETURN_CLASS(php_cmark_node_replace, 0, 1, CommonMark\\Node, 0)
	ZEND_ARG_OBJ_INFO(0, target, CommonMark\\Node, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(Node, replace)
{
	zval *target;

	ZEND_BEGIN_PARAMS(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(target, php_cmark_node_ce)
	ZEND_END_PARAMS();

	switch (php_cmark_node_edit(
			cmark_node_replace, 
				php_cmark_node_fetch(getThis()), 
				php_cmark_node_fetch(target))) {
		case PHP_CMARK_NODE_EDIT_MISSING:
		case PHP_CMARK_NODE_EDIT_HANDLER:
			php_cmark_throw(
				"failed to replace %s with %s",
				ZSTR_VAL(Z_OBJCE_P(getThis())->name),
				ZSTR_VAL(Z_OBJCE_P(target)->name));
			return;

		case PHP_CMARK_NODE_EDIT_USED:
			php_cmark_throw(
				"%s is already in use",
				ZSTR_VAL(Z_OBJCE_P(target)->name));
			return;

		case PHP_CMARK_NODE_EDIT_OK:
			break;
	}

	php_cmark_node_fetch(getThis())->owned = 1;
	php_cmark_node_fetch(target)->owned = 0;

	php_cmark_chain_ex(target);
}

PHP_METHOD(Node, unlink)
{
	php_cmark_node_t *n = php_cmark_node_fetch(getThis());

	php_cmark_no_parameters();

	cmark_node_unlink(n->node);

	n->owned = 1;
}

ZEND_BEGIN_ARG_INFO_EX(php_cmark_node_accept, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, visitor, CommonMark\\Interfaces\\IVisitor, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(Node, accept)
{
	zval *visitor = NULL;

	ZEND_BEGIN_PARAMS(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(visitor, php_cmark_node_visitor_ce)
	ZEND_END_PARAMS();

	php_cmark_node_accept_impl(php_cmark_node_fetch(getThis()), visitor);
}

#if PHP_VERSION_ID >= 80000
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(php_cmark_node_getIterator, 0, 0, Iterator, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(Node, getIterator)
{
	ZEND_PARSE_PARAMETERS_NONE();

	zend_create_internal_iterator_zval(return_value, ZEND_THIS);
}
#endif

static zend_function_entry php_cmark_node_type_methods[] = {
	PHP_ME(Node, appendChild, php_cmark_node_add, ZEND_ACC_PUBLIC)
	PHP_ME(Node, prependChild, php_cmark_node_add, ZEND_ACC_PUBLIC)
	PHP_ME(Node, insertBefore, php_cmark_node_insert, ZEND_ACC_PUBLIC)
	PHP_ME(Node, insertAfter, php_cmark_node_insert, ZEND_ACC_PUBLIC)
	PHP_ME(Node, replace, php_cmark_node_replace, ZEND_ACC_PUBLIC)
	PHP_ME(Node, unlink, php_cmark_no_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(Node, accept, php_cmark_node_accept, ZEND_ACC_PUBLIC)
#if PHP_VERSION_ID >= 80000
	PHP_ME(Node, getIterator, php_cmark_node_getIterator, ZEND_ACC_PUBLIC)
#endif
	PHP_FE_END
};

PHP_MINIT_FUNCTION(CommonMark_Node) {
	zend_class_entry ce;

	INIT_NS_CLASS_ENTRY(ce, "CommonMark", "Node", php_cmark_node_type_methods);

	php_cmark_node_ce = zend_register_internal_class(&ce);
	php_cmark_node_ce->create_object = php_cmark_node_create;
	php_cmark_node_ce->get_iterator = php_cmark_iterator_create;

#define php_cmark_node_property(n) \
	zend_declare_property_null(php_cmark_node_ce, ZEND_STRL(n), ZEND_ACC_PUBLIC)

	php_cmark_node_property("parent");
	php_cmark_node_property("previous");
	php_cmark_node_property("next");
	php_cmark_node_property("lastChild");
	php_cmark_node_property("firstChild");

	php_cmark_node_property("startLine");
	php_cmark_node_property("endLine");
	php_cmark_node_property("startColumn");
	php_cmark_node_property("endColumn");
#undef php_cmark_node_property

#if PHP_VERSION_ID >= 80000
	zend_class_implements(php_cmark_node_ce, 2, php_cmark_node_visitable_ce, zend_ce_aggregate);
#else
	zend_class_implements(php_cmark_node_ce, 2, php_cmark_node_visitable_ce, zend_ce_traversable);
#endif

	memcpy(&php_cmark_node_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

	php_cmark_node_handlers.get_debug_info = php_cmark_node_debug;
	php_cmark_node_handlers.clone_obj = php_cmark_node_clone;
	php_cmark_node_handlers.free_obj = php_cmark_node_free;
	php_cmark_node_handlers.read_property = php_cmark_node_read;
	php_cmark_node_handlers.write_property = php_cmark_node_write;
	php_cmark_node_handlers.has_property = php_cmark_node_isset;
	php_cmark_node_handlers.unset_property = php_cmark_node_unset;
	php_cmark_node_handlers.get_property_ptr_ptr = NULL;

	php_cmark_node_handlers.offset = XtOffsetOf(php_cmark_node_t, std);

	return SUCCESS;
}

PHP_RINIT_FUNCTION(CommonMark_Node)
{
	php_cmark_node_ce->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS;

	return SUCCESS;
}
#endif
