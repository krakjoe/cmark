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
#ifndef PHP_CMARK_NODE_HANDLERS_H
#define PHP_CMARK_NODE_HANDLERS_H

extern HashTable* php_cmark_node_debug(zval *zv, int *tmp);
extern zend_object* php_cmark_node_clone(zval *zv);
extern void php_cmark_node_free(zend_object *zo);

typedef int (*cmark_node_read_int) (cmark_node*);
typedef const char* (*cmark_node_read_str) (cmark_node*);

typedef int (*cmark_node_write_str) (cmark_node*, const char *content);
typedef int (*cmark_node_write_int) (cmark_node*, int value);

zval* php_cmark_node_read_bool(php_cmark_node_t *n, cmark_node_read_int cmark_node_read, zval *cache);
zval* php_cmark_node_read_int(php_cmark_node_t *n, cmark_node_read_int cmark_node_read, zval *cache);
zval* php_cmark_node_read_str(php_cmark_node_t *n, cmark_node_read_str cmark_node_read, zval *cache, zval *rv);
void php_cmark_node_write_str(php_cmark_node_t *n, cmark_node_write_str cmark_node_write, zval *content, zval *cache);
void php_cmark_node_write_int(php_cmark_node_t *n, cmark_node_write_int cmark_node_write, zval *value, zval *cache);
void php_cmark_node_write_bool(php_cmark_node_t *n, cmark_node_write_int cmark_node_write, zval *value, zval *cache);

extern zval* php_cmark_node_read(zval *object, zval *member, int type, void **rtc, zval *rv);
extern void php_cmark_node_write(zval *object, zval *member, zval *value, void **rtc);
extern int php_cmark_node_isset(zval *object, zval *member, int has_set_exists, void **rtc);
extern void php_cmark_node_unset(zval *object, zval *member, void **rtc);

#define RTS(c, f) ((c) ? (*c) = (f) : (f))
#define RTC(c, f) ((*c) == (f))

#endif
