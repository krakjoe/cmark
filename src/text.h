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
#ifndef PHP_CMARK_NODE_TEXT_H
#define PHP_CMARK_NODE_TEXT_H

extern zend_class_entry *php_cmark_node_text_ce;
extern zend_class_entry *php_cmark_node_text_emphasis_ce;
extern zend_class_entry *php_cmark_node_text_strong_ce;

extern PHP_MINIT_FUNCTION(CommonMark_Node_Text);
extern PHP_RINIT_FUNCTION(CommonMark_Node_Text);

extern zend_object_handlers php_cmark_node_text_handlers;

typedef struct _php_cmark_node_text_t {
	php_cmark_node_t h;
	zval literal;
} php_cmark_node_text_t;

#define php_cmark_node_text_from(o) \
	((php_cmark_node_text_t*) \
		((char*) o - XtOffsetOf(php_cmark_node_text_t, h.std)))
#define php_cmark_node_text_fetch(z) php_cmark_node_text_from(Z_OBJ_P(z))

#if PHP_VERSION_ID >= 80000
extern int php_cmark_node_text_isset(zend_object *object, zend_string *member, int has_set_exists, void **rtc);
extern zval* php_cmark_node_text_write(zend_object *object, zend_string *member, zval *value, void **rtc);
extern zval* php_cmark_node_text_read(zend_object *object, zend_string *member, int type, void **rtc, zval *rv);
extern void php_cmark_node_text_unset(zend_object *object, zend_string *member, void **rtc);
#else
extern int php_cmark_node_text_isset(zval *object, zval *member, int has_set_exists, void **rtc);
#	if PHP_VERSION_ID >= 70400
extern zval* php_cmark_node_text_write(zval *object, zval *member, zval *value, void **rtc);
#	else
extern void php_cmark_node_text_write(zval *object, zval *member, zval *value, void **rtc);
#	endif
extern zval* php_cmark_node_text_read(zval *object, zval *member, int type, void **rtc, zval *rv);
extern void php_cmark_node_text_unset(zval *object, zval *member, void **rtc);
#endif
#endif
