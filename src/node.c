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

zend_class_entry*      php_cmark_node_ce;
zend_object_handlers   php_cmark_node_handlers;
cmark_mem              php_cmark_node_mem;

typedef enum _php_cmark_node_edit_result {
	PHP_CMARK_NODE_EDIT_MISSING,
	PHP_CMARK_NODE_EDIT_USED,
	PHP_CMARK_NODE_EDIT_HANDLER,
	PHP_CMARK_NODE_EDIT_OK
} php_cmark_node_edit_result;

typedef int (*php_cmark_node_edit_f) (cmark_node*, cmark_node*);

static inline php_cmark_node_edit_result php_cmark_node_edit(php_cmark_node_edit_f handler, php_cmark_node_t *object, php_cmark_node_t *arg) {
	php_cmark_node_t *n = 
		(php_cmark_node_t*) cmark_node_get_user_data(arg->node);

	if (!n) {
		return PHP_CMARK_NODE_EDIT_MISSING;
	}

	if (arg->used) {
		return PHP_CMARK_NODE_EDIT_USED;
	}

	if (!handler(object->node, arg->node)) {
		return PHP_CMARK_NODE_EDIT_HANDLER;
	}

	GC_ADDREF(&n->std);

	arg->used = 1;

	return PHP_CMARK_NODE_EDIT_OK;
}

void php_cmark_node_new(zval *object, cmark_node_type type) {
	php_cmark_node_t *n = php_cmark_node_fetch(object);

	n->node = cmark_node_new_with_mem(
		type, &php_cmark_node_mem);

	cmark_node_set_user_data(n->node, n);
}

void php_cmark_node_list_new(zval *object, cmark_list_type type) {
	php_cmark_node_t *n = php_cmark_node_fetch(object);

	n->node = cmark_node_new_with_mem(
		CMARK_NODE_LIST, &php_cmark_node_mem);

	cmark_node_set_list_type(n->node, type);
	cmark_node_set_user_data(n->node, n);
}

void php_cmark_node_text_new(zval *object, cmark_node_type type, zend_string *literal) {
	php_cmark_node_new(object, type);

	if (literal) {
		cmark_node_set_literal(
			php_cmark_node_fetch(object)->node, ZSTR_VAL(literal));
	}
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
			default:
				return php_cmark_node_list_ce;
		}
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
	}

	return php_cmark_node_ce;
}

zend_object* php_cmark_node_create(zend_class_entry *ce) {
	php_cmark_node_t *n = 
		(php_cmark_node_t*) 
			ecalloc(1, sizeof(php_cmark_node_t));

	zend_object_std_init(&n->std, ce);

	n->std.handlers = &php_cmark_node_handlers;

	return &n->std;
}

static inline void php_cmark_node_clone_impl(php_cmark_node_t *target, cmark_node *source);

static inline void php_cmark_node_clone_children_impl(php_cmark_node_t *target, cmark_node *source) {
	cmark_node *current = cmark_node_first_child(source);

	if (!current) {
		return;
	}

	do {
		zval zv;

		object_init_ex(&zv, 
			php_cmark_node_class(current));

		php_cmark_node_clone_impl(
			php_cmark_node_fetch(&zv), current);

		cmark_node_append_child(target->node, 
			php_cmark_node_fetch(&zv)->node);

		current = cmark_node_next(current);
	} while (current);
}

static inline void php_cmark_node_clone_impl(php_cmark_node_t *target, cmark_node *source) {
	cmark_node_type type = cmark_node_get_type(source);

	target->node = cmark_node_new_with_mem(type, &php_cmark_node_mem);

	switch (type) {
		case CMARK_NODE_LIST:
			cmark_node_set_list_type(
				target->node, 
				cmark_node_get_list_type(source));
			cmark_node_set_list_tight(
				target->node, 
				cmark_node_get_list_tight(source));
			cmark_node_set_list_delim(
				target->node, 
				cmark_node_get_list_delim(source));
		break;

		case CMARK_NODE_CODE_BLOCK:
			cmark_node_set_fence_info(target->node,
				cmark_node_get_fence_info(source));

		case CMARK_NODE_TEXT:
		case CMARK_NODE_HTML_INLINE:
		case CMARK_NODE_CODE:
		case CMARK_NODE_HTML_BLOCK:
			cmark_node_set_literal(
				target->node, 
				cmark_node_get_literal(source));
		break;

		case CMARK_NODE_LINK:
		case CMARK_NODE_IMAGE:
			cmark_node_set_url(
				target->node, 
				cmark_node_get_url(source));
			cmark_node_set_title(
				target->node,
				cmark_node_get_title(source));
		break;
	}

	if (cmark_node_first_child(source)) {
		php_cmark_node_clone_children_impl(target, source);
	}

	cmark_node_set_user_data(target->node, target);
}

static inline void php_cmark_node_debug_impl(HashTable* debug, php_cmark_node_t *parent) {
	zval children;
	cmark_node *child;

	switch (cmark_node_get_type(parent->node)) {
		case CMARK_NODE_CODE_BLOCK: {
			zval fence;

			ZVAL_STRING(&fence,
				cmark_node_get_fence_info(parent->node));
			zend_hash_str_update(debug, "fence", sizeof("fence")-1, &fence);
		}

		case CMARK_NODE_TEXT:
		case CMARK_NODE_HTML_INLINE:
		case CMARK_NODE_HTML_BLOCK:
		case CMARK_NODE_CODE: {
			zval literal;
			ZVAL_STRING(&literal,
				cmark_node_get_literal(parent->node));
			zend_hash_str_update(debug, "literal", sizeof("literal")-1, &literal);
		} break;

		case CMARK_NODE_IMAGE:
		case CMARK_NODE_LINK: {
			zval url;
			zval title;

			ZVAL_STRING(&url,
				cmark_node_get_url(parent->node));
			ZVAL_STRING(&title,	
				cmark_node_get_title(parent->node));

			zend_hash_str_update(debug, "url", sizeof("url")-1, &url);
			zend_hash_str_update(debug, "title", sizeof("title")-1, &title);
		} break;
	}

	child = cmark_node_first_child(parent->node);

	if (!child) {
		return;
	}

	array_init(&children);

	do {
		zval zv;

		if (!php_cmark_node_shadow(&zv, child)) {
			break;
		}

		add_next_index_zval(&children, &zv);

		child = cmark_node_next(child);
	} while(child);

	zend_hash_str_update(debug, "children", sizeof("children")-1, &children);
}

HashTable* php_cmark_node_debug(zval *zv, int *tmp) {
	HashTable *debug;

	ALLOC_HASHTABLE(debug);
	zend_hash_init(debug, 8, NULL, ZVAL_PTR_DTOR, 0);

	php_cmark_node_debug_impl(debug, php_cmark_node_fetch(zv));

	*tmp = 1;

	return debug;
}

zend_object* php_cmark_node_clone(zval *zv) {
	php_cmark_node_t *zo = php_cmark_node_fetch(zv);
	php_cmark_node_t *co = 
		(php_cmark_node_t*) 
			ecalloc(1, sizeof(php_cmark_node_t));

	zend_object_std_init(&co->std, zo->std.ce);

	php_cmark_node_clone_impl(co, zo->node);
	
	co->std.handlers = &php_cmark_node_handlers;
	
	return &co->std;
}

php_cmark_node_t* php_cmark_node_shadow(zval *return_value, cmark_node *node) {
	php_cmark_node_t *n;

	if (!node) {
		return NULL;
	}

	if (!(n = cmark_node_get_user_data(node))) {
		object_init_ex(return_value, php_cmark_node_class(node));

		n = php_cmark_node_fetch(return_value);
		n->node = node;

		cmark_node_set_user_data(n->node, n);
	} else {
		ZVAL_OBJ(return_value, &n->std);
	}

	Z_ADDREF_P(return_value);
	return n;
}

static inline void php_cmark_nodes_free(const php_cmark_node_t *n) {
	php_cmark_node_t *u;
	cmark_node *last = cmark_node_last_child(n->node);

	while (last) {
		cmark_node *g = last;

		last = cmark_node_previous(last);

		if (!(u = (php_cmark_node_t*) cmark_node_get_user_data(g))) {
			continue;
		}

		cmark_node_set_user_data(u->node, NULL);
		cmark_node_unlink(u->node);

		PHP_OBJ_SAFE_RELEASE(&u->std);
	}

	if ((u = cmark_node_get_user_data(n->node))) {
		cmark_node_set_user_data(u->node, NULL);
		cmark_node_unlink(u->node);

		PHP_OBJ_SAFE_RELEASE(&u->std);
	}

	cmark_node_free(n->node);
}

void php_cmark_node_free(zend_object *zo) {
	php_cmark_node_t *n = php_cmark_node_from(zo);

	if (n->node) {
		php_cmark_nodes_free(n);
	}

	zend_object_std_dtor(&n->std);
}

ZEND_BEGIN_ARG_INFO_WITH_RETURN_CLASS(php_cmark_node_or_null_return, 0, 0, CommonMark\\Node, 1)
ZEND_END_ARG_INFO()

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

ZEND_BEGIN_ARG_INFO_WITH_RETURN_CLASS(php_cmark_node_add, 0, 1, CommonMark\\Node, 0)
	ZEND_ARG_OBJ_INFO(0, child, CommonMark\\Node, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(Node, appendChild)
{
	zval *child;

	if (php_cmark_parse_parameters("O", &child, php_cmark_node_ce) != SUCCESS) {
		php_cmark_wrong_parameters("node expected");
		return;
	}

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
	}

	php_cmark_chain();
}

PHP_METHOD(Node, prependChild)
{
	zval *child;

	if (php_cmark_parse_parameters("O", &child, php_cmark_node_ce) != SUCCESS) {
		php_cmark_wrong_parameters("node expected");
		return;
	}

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
	}

	php_cmark_chain();
}

ZEND_BEGIN_ARG_INFO_WITH_RETURN_CLASS(php_cmark_node_insert, 0, 1, CommonMark\\Node, 0)
	ZEND_ARG_OBJ_INFO(0, sibling, CommonMark\\Node, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(Node, insertBefore)
{
	zval *sibling;

	if (php_cmark_parse_parameters("O", &sibling, php_cmark_node_ce) != SUCCESS) {
		php_cmark_wrong_parameters("node expected");
		return;
	}

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
	}

	php_cmark_chain();
}

PHP_METHOD(Node, insertAfter)
{
	zval *sibling;

	if (php_cmark_parse_parameters("O", &sibling, php_cmark_node_ce) != SUCCESS) {
		php_cmark_wrong_parameters("node expected");
		return;
	}

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
	}
	
	php_cmark_chain();
}

ZEND_BEGIN_ARG_INFO_WITH_RETURN_CLASS(php_cmark_node_replace, 0, 1, CommonMark\\Node, 0)
	ZEND_ARG_OBJ_INFO(0, target, CommonMark\\Node, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(Node, replace)
{
	zval *target;

	if (php_cmark_parse_parameters("O", &target, php_cmark_node_ce) != SUCCESS) {
		php_cmark_wrong_parameters("node expected");
		return;
	}

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

		default: 
			zval_ptr_dtor(getThis());
	}

	php_cmark_chain_ex(target);
}

PHP_METHOD(Node, unlink)
{	
	php_cmark_node_t *n = php_cmark_node_fetch(getThis());

	php_cmark_no_parameters();

	cmark_node_unlink(n->node);

	n->used = 0;

	zval_ptr_dtor(getThis());
}

static inline void php_cmark_node_accept_impl(php_cmark_node_t *root, zval *visitor) {
	cmark_event_type event;	
	cmark_iter *iterator = cmark_iter_new(root->node);

	while ((event = cmark_iter_next(iterator)) != CMARK_EVENT_DONE) {
		zval visiting;
		zval arg;
		zval result;
		zend_fcall_info fci = empty_fcall_info;
		zend_fcall_info_cache fcc = empty_fcall_info_cache;

		php_cmark_node_t *node = 
			php_cmark_node_shadow(
				&visiting, cmark_iter_get_node(iterator));

		ZVAL_NULL(&result);

		fci.size = sizeof(zend_fcall_info);
		fci.retval = &result;
		fci.object = Z_OBJ_P(visitor);

#if PHP_VERSION_ID < 70300
		fcc.initialized = 1;
#endif
		fcc.object = fci.object;

		zend_fcall_info_argn(&fci, 1, &visiting);

		switch (event) {
			case CMARK_EVENT_ENTER:
				fcc.function_handler = zend_hash_str_find_ptr(
					&Z_OBJCE_P(visitor)->function_table, ZEND_STRL("enter"));
			break;

			case CMARK_EVENT_EXIT:
				fcc.function_handler = zend_hash_str_find_ptr(
					&Z_OBJCE_P(visitor)->function_table, ZEND_STRL("leave"));
			break;
		}

		zend_call_function(&fci, &fcc);

		if (Z_TYPE(result) == IS_LONG && Z_LVAL(result) > CMARK_EVENT_NONE) {
			cmark_iter_reset(iterator, 
				node->node, (cmark_event_type) Z_LVAL(result));
		}

		if (Z_REFCOUNTED(result)) {
			zval_ptr_dtor(&result);
		}

		zend_fcall_info_args_clear(&fci, 1);

		zval_ptr_dtor(&visiting);
	}

	cmark_iter_free(iterator);
}

ZEND_BEGIN_ARG_INFO_EX(php_cmark_node_accept, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, visitor, CommonMark\\Interfaces\\IVisitor, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(Node, accept)
{
	zval *visitor = NULL;

	if (php_cmark_parse_parameters("O", &visitor, php_cmark_node_visitor_ce) != SUCCESS) {
		php_cmark_wrong_parameters(
			"node, with optional options and width expected");
		return;
	}

	php_cmark_node_accept_impl(php_cmark_node_fetch(getThis()), visitor);
}

static zend_function_entry php_cmark_node_type_methods[] = {
	PHP_ME(Node, getNext, php_cmark_node_or_null_return, ZEND_ACC_PUBLIC)
	PHP_ME(Node, getPrevious, php_cmark_node_or_null_return, ZEND_ACC_PUBLIC)
	PHP_ME(Node, getParent, php_cmark_node_or_null_return, ZEND_ACC_PUBLIC)
	PHP_ME(Node, getFirstChild, php_cmark_node_or_null_return, ZEND_ACC_PUBLIC)
	PHP_ME(Node, getLastChild, php_cmark_node_or_null_return, ZEND_ACC_PUBLIC)
	PHP_ME(Node, appendChild, php_cmark_node_add, ZEND_ACC_PUBLIC)
	PHP_ME(Node, prependChild, php_cmark_node_add, ZEND_ACC_PUBLIC)
	PHP_ME(Node, insertBefore, php_cmark_node_insert, ZEND_ACC_PUBLIC)
	PHP_ME(Node, insertAfter, php_cmark_node_insert, ZEND_ACC_PUBLIC)
	PHP_ME(Node, replace, php_cmark_node_replace, ZEND_ACC_PUBLIC)
	PHP_ME(Node, unlink, php_cmark_no_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(Node, accept, php_cmark_node_accept, ZEND_ACC_PUBLIC)
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

	php_cmark_node_handlers.get_debug_info = php_cmark_node_debug;
	php_cmark_node_handlers.clone_obj = php_cmark_node_clone;
	php_cmark_node_handlers.free_obj = php_cmark_node_free;
	php_cmark_node_handlers.offset = XtOffsetOf(php_cmark_node_t, std);

	php_cmark_node_mem.calloc = php_cmark_node_calloc_func;
	php_cmark_node_mem.realloc = php_cmark_node_realloc_func;
	php_cmark_node_mem.free = php_cmark_node_free_func;

	return SUCCESS;
}

PHP_RINIT_FUNCTION(CommonMark_Node)
{
	zend_class_implements(php_cmark_node_ce, 1, php_cmark_node_visitable_ce);

	php_cmark_node_ce->ce_flags |= ZEND_ACC_FINAL|ZEND_ACC_EXPLICIT_ABSTRACT_CLASS;

	return SUCCESS;
}
#endif
