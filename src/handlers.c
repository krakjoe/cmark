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
#include <src/handlers.h>

typedef cmark_node* (*cmark_node_read_object) (cmark_node*);

zval* php_cmark_node_read_bool(php_cmark_node_t *n, cmark_node_read_int cmark_node_read, zval *cache) {
	if (cmark_node_read(n->node)) {
		ZVAL_TRUE(cache);
	} else ZVAL_FALSE(cache);
	
	return cache;
}

zval* php_cmark_node_read_int(php_cmark_node_t *n, cmark_node_read_int cmark_node_read, zval *cache) {
	ZVAL_LONG(cache, 
		cmark_node_read(n->node));
	
	return cache;
}

zval* php_cmark_node_read_str(php_cmark_node_t *n, cmark_node_read_str cmark_node_read, zval *cache, zval *rv) {
	const char *verified = cmark_node_read(n->node);

	if (Z_TYPE_P(cache) == IS_STRING) {
		if (verified && *verified) {
			if (!rv) {
				return cache;
			}

			ZVAL_COPY(rv, cache);
			return rv;
		}

		zval_ptr_dtor(cache);

		return &EG(uninitialized_zval);
	} else {
		if (!verified || !*verified) {
			return &EG(uninitialized_zval);
		}

		ZVAL_STRING(cache, verified);

		if (!rv) {
			return cache;
		}

		ZVAL_COPY(rv, cache);
		return rv;
	}
}

void php_cmark_node_write_int(php_cmark_node_t *n, cmark_node_write_int cmark_node_write, zval *value, zval *cache) {
	if (!cmark_node_write(n->node, Z_LVAL_P(value))) {
		php_cmark_throw("write operation failed");
		return;
	}

	ZVAL_COPY(cache, value);
}

void php_cmark_node_write_bool(php_cmark_node_t *n, cmark_node_write_int cmark_node_write, zval *value, zval *cache) {
	if (!cmark_node_write(n->node, zend_is_true(value))) {
		php_cmark_throw("write operation failed");
		return;
	}

	ZVAL_COPY(cache, value);
}

void php_cmark_node_write_str(php_cmark_node_t *n, cmark_node_write_str cmark_node_write, zval *content, zval *cache) {
	if (!content) {
		if (!Z_ISUNDEF_P(cache)) {
			zval_ptr_dtor(cache);
		}
		ZVAL_UNDEF(cache);
	}

	if (!cmark_node_write(n->node, content ? Z_STRVAL_P(content) : NULL)) {
		php_cmark_throw("write operation failed");
		return;
	}

	if (content) {
		ZVAL_COPY(cache, content);
	}
}

static inline zval* php_cmark_node_read_object(php_cmark_node_t *n, cmark_node_read_object cmark_node_read, zval *cache, zval *rv) {
	cmark_node *verified = cmark_node_read(n->node);

	if (cache && Z_TYPE_P(cache) == IS_OBJECT) {
		if (verified == php_cmark_node_fetch(cache)->node) {
			if (!rv) {
				return cache;
			}

			ZVAL_COPY(rv, cache);
			return rv;
		}

		zval_ptr_dtor(cache);
	}

	if (!php_cmark_node_shadow(cache, verified)) {
		return &EG(uninitialized_zval);
	}

	if (!rv) {
		return cache;
	}
	
	ZVAL_COPY(rv, cache);
	return rv;
}

zval* php_cmark_node_read(zval *object, zval *member, int type, void **rtc, zval *rv) {
	php_cmark_node_t *n = php_cmark_node_fetch(object);

	if (Z_TYPE_P(member) != IS_STRING) {
		goto php_cmark_node_read_error;
	}

	if (EXPECTED(rtc)) {
		if (RTC(rtc, cmark_node_parent))
			return php_cmark_node_read_object(n, 
				cmark_node_parent, &n->parent, rv);
		if (RTC(rtc, cmark_node_previous))
			return php_cmark_node_read_object(n, 
				cmark_node_previous, &n->previous, rv);
		if (RTC(rtc, cmark_node_next))
			return php_cmark_node_read_object(n, 
				cmark_node_next, &n->next, rv);
		if (RTC(rtc, cmark_node_first_child))
			return php_cmark_node_read_object(n, 
				cmark_node_first_child, &n->firstChild, rv);
		if (RTC(rtc, cmark_node_last_child))
			return php_cmark_node_read_object(n, 
				cmark_node_last_child, &n->lastChild, rv);
		if (RTC(rtc, cmark_node_get_start_line))
			return php_cmark_node_read_int(n, 
				cmark_node_get_start_line, &n->startLine);
		if (RTC(rtc, cmark_node_get_end_line))
			return php_cmark_node_read_int(n, 
				cmark_node_get_end_line, &n->endLine);
		if (RTC(rtc, cmark_node_get_start_column))
			return php_cmark_node_read_int(n, 
				cmark_node_get_start_column, &n->startColumn);
		if (RTC(rtc, cmark_node_get_end_column))
			return php_cmark_node_read_int(n, 
				cmark_node_get_end_column, &n->endColumn);
	}

	if (zend_string_equals_literal(Z_STR_P(member), "parent")) {
		return php_cmark_node_read_object(n, 
			RTS(rtc, cmark_node_parent), &n->parent, rv);
	} else if (zend_string_equals_literal(Z_STR_P(member), "previous")) {
		return php_cmark_node_read_object(n, 
			RTS(rtc, cmark_node_previous), &n->previous, rv);
	} else if (zend_string_equals_literal(Z_STR_P(member), "next")) {
		return php_cmark_node_read_object(n, 
			RTS(rtc, cmark_node_next), &n->next, rv);
	} else if (zend_string_equals_literal(Z_STR_P(member), "firstChild")) {
		return php_cmark_node_read_object(n, 
			RTS(rtc, cmark_node_first_child), &n->firstChild, rv);
	}  else if (zend_string_equals_literal(Z_STR_P(member), "lastChild")) {
		return php_cmark_node_read_object(n, 
			RTS(rtc, cmark_node_last_child), &n->lastChild, rv);
	} else if (zend_string_equals_literal(Z_STR_P(member), "startLine")) {
		return php_cmark_node_read_int(n, 
			RTS(rtc, cmark_node_get_start_line), &n->startLine);
	} else if (zend_string_equals_literal(Z_STR_P(member), "endLine")) {
		return php_cmark_node_read_int(n, 
			RTS(rtc, cmark_node_get_end_line), &n->endLine);
	} else if (zend_string_equals_literal(Z_STR_P(member), "startColumn")) {
		return php_cmark_node_read_int(n, 
			RTS(rtc, cmark_node_get_start_column), &n->startColumn);
	} else if (zend_string_equals_literal(Z_STR_P(member), "endColumn")) {
		return php_cmark_node_read_int(n, 
			RTS(rtc, cmark_node_get_end_column), &n->endColumn);
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

	if (EXPECTED(rtc)) {
		if (RTC(rtc, cmark_node_parent)) {
			zv = php_cmark_node_read_object(n, 
				cmark_node_parent, &n->parent, NULL);
			goto php_cmark_node_handlers_isset_result;
		} else if (RTC(rtc, cmark_node_previous)) {
			zv = php_cmark_node_read_object(n, 
				cmark_node_previous, &n->previous, NULL);
			goto php_cmark_node_handlers_isset_result;
		}  else if (RTC(rtc, cmark_node_next)) {
			zv = php_cmark_node_read_object(n, 
				cmark_node_next, &n->next, NULL);
			goto php_cmark_node_handlers_isset_result;
		} else if (RTC(rtc, cmark_node_first_child)) {
			zv = php_cmark_node_read_object(n, 
				cmark_node_first_child, &n->firstChild, NULL);
			goto php_cmark_node_handlers_isset_result;
		} else if (RTC(rtc, cmark_node_last_child)) {
			zv = php_cmark_node_read_object(n, 
				cmark_node_last_child, &n->lastChild, NULL);
			goto php_cmark_node_handlers_isset_result;
		} else if (RTC(rtc, cmark_node_get_start_line)) {
			zv = php_cmark_node_read_int(n, 
				cmark_node_get_start_line, &n->startLine);
			goto php_cmark_node_handlers_isset_result;
		} else if (RTC(rtc, cmark_node_get_end_line)) {
			zv = php_cmark_node_read_int(n, 
				cmark_node_get_end_line, &n->endLine);
			goto php_cmark_node_handlers_isset_result;
		} else if (RTC(rtc, cmark_node_get_start_column)) {
			zv = php_cmark_node_read_int(n, 
				cmark_node_get_start_column, &n->startColumn);
			goto php_cmark_node_handlers_isset_result;
		} else if (RTC(rtc, cmark_node_get_end_column)) {
			zv = php_cmark_node_read_int(n, 
				cmark_node_get_end_column, &n->endColumn);
			goto php_cmark_node_handlers_isset_result;
		}
	}

	if (zend_string_equals_literal(Z_STR_P(member), "parent")) {
		zv = php_cmark_node_read_object(n, 
			RTS(rtc, cmark_node_parent), &n->parent, NULL);
	} else if (zend_string_equals_literal(Z_STR_P(member), "previous")) {
		zv = php_cmark_node_read_object(n, 
			RTS(rtc, cmark_node_previous), &n->previous, NULL);
	} else if (zend_string_equals_literal(Z_STR_P(member), "next")) {
		zv = php_cmark_node_read_object(n, 
			RTS(rtc, cmark_node_next), &n->next, NULL);
	} else if (zend_string_equals_literal(Z_STR_P(member), "firstChild")) {
		zv = php_cmark_node_read_object(n, 
			RTS(rtc, cmark_node_first_child), &n->firstChild, NULL);
	}  else if (zend_string_equals_literal(Z_STR_P(member), "lastChild")) {
		zv = php_cmark_node_read_object(n, 
			RTS(rtc, cmark_node_last_child), &n->lastChild, NULL);
	} else if (zend_string_equals_literal(Z_STR_P(member), "startLine")) {
		zv = php_cmark_node_read_int(n, 
			RTS(rtc, cmark_node_get_start_line), &n->startLine);
	}  else if (zend_string_equals_literal(Z_STR_P(member), "endLine")) {
		zv = php_cmark_node_read_int(n, 
			RTS(rtc, cmark_node_get_end_line), &n->endLine);
	}  else if (zend_string_equals_literal(Z_STR_P(member), "startColumn")) {
		zv = php_cmark_node_read_int(n, 
			RTS(rtc, cmark_node_get_start_column), &n->startColumn);
	}   else if (zend_string_equals_literal(Z_STR_P(member), "endColumn")) {
		zv = php_cmark_node_read_int(n, 
			RTS(rtc, cmark_node_get_end_column), &n->endColumn);
	}
php_cmark_node_handlers_isset_result:
	return Z_TYPE_P(zv) == IS_OBJECT || Z_TYPE_P(zv) == IS_LONG;
}

void php_cmark_node_unset(zval *object, zval *member, void **rtc) {
	php_cmark_throw(
		"invalid write of %s", 
		Z_TYPE_P(member) == IS_STRING ? 
			Z_STRVAL_P(member) : "invalid property");
}

static inline cmark_node* php_cmark_node_clone_impl(cmark_node *source);

static inline void php_cmark_node_clone_children_impl(cmark_node *target, cmark_node *source) {
	cmark_node *current = cmark_node_first_child(source);

	if (!current) {
		return;
	}

	do {
		cmark_node_append_child(target, 
			php_cmark_node_clone_impl(current));

		current = cmark_node_next(current);
	} while (current);
}

static inline cmark_node* php_cmark_node_clone_impl(cmark_node *source) {
	cmark_node_type type = cmark_node_get_type(source);

	cmark_node *node = cmark_node_new_with_mem(type, &php_cmark_mem);

	switch (type) {
		case CMARK_NODE_LIST:
			cmark_node_set_list_type(
				node, 
				cmark_node_get_list_type(source));
			cmark_node_set_list_tight(
				node, 
				cmark_node_get_list_tight(source));
			cmark_node_set_list_delim(
				node, 
				cmark_node_get_list_delim(source));
			if (cmark_node_get_list_type(source) == CMARK_ORDERED_LIST) {
				cmark_node_set_list_start(node,
					cmark_node_get_list_start(source));
			}
		break;

		case CMARK_NODE_HEADING:
			cmark_node_set_heading_level(node,
				cmark_node_get_heading_level(source));
		break;

		case CMARK_NODE_CODE_BLOCK:
			cmark_node_set_fence_info(node,
				cmark_node_get_fence_info(source));

		case CMARK_NODE_TEXT:
		case CMARK_NODE_HTML_INLINE:
		case CMARK_NODE_CODE:
		case CMARK_NODE_HTML_BLOCK:
			cmark_node_set_literal(
				node, 
				cmark_node_get_literal(source));
		break;

		case CMARK_NODE_LINK:
		case CMARK_NODE_IMAGE:
			cmark_node_set_url(
				node, 
				cmark_node_get_url(source));
			cmark_node_set_title(
				node,
				cmark_node_get_title(source));
		break;

		case CMARK_NODE_CUSTOM_BLOCK:
		case CMARK_NODE_CUSTOM_INLINE:
			cmark_node_set_on_enter(node,
				cmark_node_get_on_enter(source));
			cmark_node_set_on_exit(node,
				cmark_node_get_on_exit(source));
		break;
	}

	if (cmark_node_first_child(source)) {
		php_cmark_node_clone_children_impl(node, source);
	}

	return node;
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

		if (!php_cmark_node_shadow(&zv, child)) {
			break;
		}

		if (add_next_index_zval(&children, &zv) != SUCCESS) {
			zval_ptr_dtor(&zv);
		}

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

	co->node = php_cmark_node_clone_impl(zo->node);
	co->owned = 1;

	co->std.handlers = &php_cmark_node_handlers;
	
	return php_cmark_node_zend(co);
}

void php_cmark_node_free(zend_object *zo) {
	php_cmark_node_t *n = php_cmark_node_from(zo);

	if (n->node) {
		if (n->owned) {
			cmark_node_free(n->node);
		}
	}

	zend_object_std_dtor(zo);

}

#endif
