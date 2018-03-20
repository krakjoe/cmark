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
#ifndef PHP_CMARK_NODE_HANDLERS
#define PHP_CMARK_NODE_HANDLERS

#include <php.h>

#include <cmark.h>

#include <src/common.h>
#include <src/node.h>

static inline zval* php_cmark_node_read_cached(php_cmark_node_t *n, cmark_node* (*cmark_node_read) (cmark_node*), zval *cache) {
	cmark_node *verified = cmark_node_read(n->node);

	if (Z_TYPE_P(cache) == IS_OBJECT) {
		if (verified == php_cmark_node_fetch(cache)->node) {
			return cache;
		}

		zval_ptr_dtor(cache);
		ZVAL_UNDEF(cache);
	}

	if (!php_cmark_node_shadow(cache, verified, 0)) {
		return &EG(uninitialized_zval);
	}

	return cache;
}

zval* php_cmark_node_read(zval *object, zval *member, int type, void **rtc, zval *rv) {
	php_cmark_node_t *n = php_cmark_node_fetch(object);

	if (Z_TYPE_P(member) != IS_STRING) {
		goto php_cmark_node_read_error;
	}

	if (EXPECTED(rtc)) {
		if (*rtc == cmark_node_parent)
			return php_cmark_node_read_cached(n, cmark_node_parent, &n->parent);
		if (*rtc == cmark_node_previous)
			return php_cmark_node_read_cached(n, cmark_node_previous, &n->previous);
		if (*rtc == cmark_node_next)
			return php_cmark_node_read_cached(n, cmark_node_next, &n->next);
		if (*rtc == cmark_node_first_child)
			return php_cmark_node_read_cached(n, cmark_node_first_child, &n->firstChild);
		if (*rtc == cmark_node_last_child)
			return php_cmark_node_read_cached(n, cmark_node_last_child, &n->lastChild);
	}

	if (zend_string_equals_literal(Z_STR_P(member), "parent")) {
		if (rtc) 
			*rtc = cmark_node_parent;
		return php_cmark_node_read_cached(n, cmark_node_parent, &n->parent);
	} else if (zend_string_equals_literal(Z_STR_P(member), "previous")) {
		if (rtc) 
			*rtc = cmark_node_previous;
		return php_cmark_node_read_cached(n, cmark_node_previous, &n->previous);
	} else if (zend_string_equals_literal(Z_STR_P(member), "next")) {
		if (rtc) 
			*rtc = cmark_node_next;
		return php_cmark_node_read_cached(n, cmark_node_next, &n->next);
	} else if (zend_string_equals_literal(Z_STR_P(member), "firstChild")) {
		if (rtc) 
			*rtc = cmark_node_first_child;
		return php_cmark_node_read_cached(n, cmark_node_first_child, &n->firstChild);
	}  else if (zend_string_equals_literal(Z_STR_P(member), "lastChild")) {
		if (rtc) 
			*rtc = cmark_node_last_child;
		return php_cmark_node_read_cached(n, cmark_node_last_child, &n->lastChild);
	} else {
php_cmark_node_read_error:
		php_cmark_throw(
			"invalid read of %s", 
			Z_TYPE_P(member) == IS_STRING ? 
				Z_STRVAL_P(member) : "invalid property");
	}

	return &EG(uninitialized_zval);	
}

void php_cmark_node_write(zval *object, zval *member, zval *value, void **rtc) {
	php_cmark_throw(
		"invalid write of %s", 
		Z_TYPE_P(member) == IS_STRING ? 
			Z_STRVAL_P(member) : "invalid property");
}

int php_cmark_node_isset(zval *object, zval *member, int has_set_exists, void **rtc) {
	php_cmark_node_t *n = php_cmark_node_fetch(object);
	zval *zv = &EG(uninitialized_zval);

	if (Z_TYPE_P(member) != IS_STRING) {
		return 0;
	}

	if (has_set_exists == 2) {
		if (zend_string_equals_literal(Z_STR_P(member), "parent") ||
		    zend_string_equals_literal(Z_STR_P(member), "previous") ||
		    zend_string_equals_literal(Z_STR_P(member), "next") ||
		    zend_string_equals_literal(Z_STR_P(member), "lastChild") || 
		    zend_string_equals_literal(Z_STR_P(member), "firstChild")) {
			return 1;
		}
	}

	if (zend_string_equals_literal(Z_STR_P(member), "parent")) {
		zv = php_cmark_node_read_cached(n, cmark_node_parent, &n->parent);
	} else if (zend_string_equals_literal(Z_STR_P(member), "previous")) {
		zv = php_cmark_node_read_cached(n, cmark_node_previous, &n->previous);
	} else if (zend_string_equals_literal(Z_STR_P(member), "next")) {
		zv = php_cmark_node_read_cached(n, cmark_node_next, &n->next);
	} else if (zend_string_equals_literal(Z_STR_P(member), "firstChild")) {
		zv = php_cmark_node_read_cached(n, cmark_node_first_child, &n->firstChild);
	}  else if (zend_string_equals_literal(Z_STR_P(member), "lastChild")) {
		zv = php_cmark_node_read_cached(n, cmark_node_last_child, &n->lastChild);
	}

	return Z_TYPE_P(zv) == IS_OBJECT;
}

void php_cmark_node_unset(zval *object, zval *member, void **rtc) {
	php_cmark_throw(
		"invalid write of %s", 
		Z_TYPE_P(member) == IS_STRING ? 
			Z_STRVAL_P(member) : "invalid property");
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

	target->node = cmark_node_new_with_mem(type, &php_cmark_mem);

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

		case CMARK_NODE_CUSTOM_BLOCK:
		case CMARK_NODE_CUSTOM_INLINE:
			cmark_node_set_on_enter(target->node,
				cmark_node_get_on_enter(source));
			cmark_node_set_on_exit(target->node,
				cmark_node_get_on_exit(source));
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

		case CMARK_NODE_CUSTOM_BLOCK:
		case CMARK_NODE_CUSTOM_INLINE: {
			zval enter;
			zval leave;

			ZVAL_STRING(&enter,
				cmark_node_get_on_enter(parent->node));
			ZVAL_STRING(&leave,	
				cmark_node_get_on_exit(parent->node));

			zend_hash_str_update(debug, "enter", sizeof("enter")-1, &enter);
			zend_hash_str_update(debug, "leave", sizeof("leave")-1, &leave);
		} break;
	}

	child = cmark_node_first_child(parent->node);

	if (!child) {
		return;
	}

	array_init(&children);

	do {
		zval zv;

		if (!php_cmark_node_shadow(&zv, child, 1)) {
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

	zend_object_std_init(
		php_cmark_node_zend(co), zo->std.ce);

	php_cmark_node_clone_impl(co, zo->node);
	
	co->std.handlers = &php_cmark_node_handlers;
	
	return php_cmark_node_zend(co);
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

		PHP_OBJ_SAFE_RELEASE(php_cmark_node_zend(u));
	}

	if ((u = cmark_node_get_user_data(n->node))) {
		cmark_node_set_user_data(u->node, NULL);
		cmark_node_unlink(u->node);

		PHP_OBJ_SAFE_RELEASE(php_cmark_node_zend(u));
	}

	cmark_node_free(n->node);
}

void php_cmark_node_free(zend_object *zo) {
	php_cmark_node_t *n = php_cmark_node_from(zo);

	if (n->node) {
		php_cmark_nodes_free(n);
	}
}

#endif
