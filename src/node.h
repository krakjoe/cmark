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
#ifndef PHP_CMARK_NODE_H
#define PHP_CMARK_NODE_H

#include <cmark.h>

extern zend_class_entry *php_cmark_node_ce;
extern zend_object_handlers   php_cmark_node_handlers;

typedef struct _php_cmark_node_t {
	cmark_node* node;
	zend_bool used;
	struct {
		zend_refcounted_h gc;
		uint32_t handle;
		zend_class_entry *ce;
		const zend_object_handlers *handlers;
		HashTable *properties;
	} std;
	zval parent;
	zval previous;
	zval next;
	zval firstChild;
	zval lastChild;

	zval startLine;
	zval endLine;
	zval startColumn;
	zval endColumn;
} php_cmark_node_t;

#define php_cmark_node_from(o) \
	((php_cmark_node_t*) \
		((char*) o - XtOffsetOf(php_cmark_node_t, std)))
#define php_cmark_node_fetch(z) php_cmark_node_from(Z_OBJ_P(z))
#define php_cmark_node_zend(z) ((zend_object*) &(z)->std)

extern PHP_MINIT_FUNCTION(CommonMark_Node);
extern PHP_RINIT_FUNCTION(CommonMark_Node);

extern void php_cmark_node_new(zval *object, cmark_node_type type);
extern void php_cmark_node_list_new(zval *object, cmark_list_type type);
extern php_cmark_node_t* php_cmark_node_shadow(zval *return_value, cmark_node *node, zend_bool addref);
extern zend_class_entry* php_cmark_node_class(cmark_node* node);
#endif
