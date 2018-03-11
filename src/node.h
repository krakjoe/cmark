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
extern cmark_mem         php_cmark_node_mem;

typedef struct _php_cmark_node_t {
	cmark_node* node;
	zend_bool   shadow;
	zend_object std;
} php_cmark_node_t;

#define php_cmark_node_from(o) \
	((php_cmark_node_t*) \
		((char*) o - XtOffsetOf(php_cmark_node_t, std)))
#define php_cmark_node_fetch(z) php_cmark_node_from(Z_OBJ_P(z))

extern PHP_MINIT_FUNCTION(CommonMark_Node);
extern PHP_RINIT_FUNCTION(CommonMark_Node);

extern zend_class_entry* php_cmark_node_class(cmark_node* node);
#endif
