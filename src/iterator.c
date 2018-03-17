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
#ifndef HAVE_PHP_CMARK_ITERATOR
#define HAVE_PHP_CMARK_ITERATOR

#include <php.h>

#include <cmark.h>

#include <src/common.h>
#include <src/node.h>

typedef struct _php_cmark_iterator_t {
	zend_object_iterator zit;
	zval                 zo;
	cmark_event_type     ev;
	cmark_iter          *it;
	cmark_node          *ro;
} php_cmark_iterator_t;

static inline void php_cmark_iterator_dtor(php_cmark_iterator_t* iterator) {
	cmark_iter_free(iterator->it);

	zval_ptr_dtor(&iterator->zo);
}

static inline int php_cmark_iterator_validate(php_cmark_iterator_t* iterator) {
	return iterator->ev == CMARK_EVENT_DONE ? FAILURE : SUCCESS;
}

static inline zval* php_cmark_iterator_current_data(php_cmark_iterator_t* iterator) {
	if (Z_TYPE(iterator->zit.data) == IS_OBJECT) {
		PHP_OBJ_SAFE_RELEASE(Z_OBJ(iterator->zit.data));
	}

	php_cmark_node_shadow(
		&iterator->zit.data, 
			cmark_iter_get_node(iterator->it));

	return &iterator->zit.data;
}

static inline void php_cmark_iterator_current_key(php_cmark_iterator_t* iterator, zval* result) {
	ZVAL_LONG(result, iterator->ev);
}

static inline void php_cmark_iterator_move_forward(php_cmark_iterator_t* iterator) {
	iterator->ev = cmark_iter_next(iterator->it);
}

static inline void php_cmark_iterator_rewind(php_cmark_iterator_t* iterator) {
	cmark_iter_reset(
		iterator->it, 
		iterator->ro, 
		iterator->ev = CMARK_EVENT_ENTER);
}

static zend_object_iterator_funcs php_cmark_iterator_funcs = {
	(void (*) (zend_object_iterator*))		php_cmark_iterator_dtor,
	(int (*)(zend_object_iterator *))		php_cmark_iterator_validate,
	(zval* (*)(zend_object_iterator *))		php_cmark_iterator_current_data,
	(void (*)(zend_object_iterator *, zval *))	php_cmark_iterator_current_key,
	(void (*)(zend_object_iterator *))		php_cmark_iterator_move_forward,
	(void (*)(zend_object_iterator *))		php_cmark_iterator_rewind
};

zend_object_iterator* php_cmark_iterator_create(zend_class_entry *ce, zval *object, int by_ref) {
	php_cmark_iterator_t *iterator;
	php_cmark_node_t *n = php_cmark_node_fetch(object);

	if (by_ref) {
		php_cmark_throw("iteration by reference unsupported");
		return NULL;
	}

	iterator = 
		(php_cmark_iterator_t*) 
			ecalloc(1, sizeof(php_cmark_iterator_t));

	zend_iterator_init((zend_object_iterator*)iterator);

	ZVAL_COPY(&iterator->zo, object);
	ZVAL_UNDEF(&iterator->zit.data);

	iterator->ro = n->node;
	iterator->it = cmark_iter_new(iterator->ro);
	iterator->zit.funcs = &php_cmark_iterator_funcs;

	return (zend_object_iterator*) iterator;
}
#endif
