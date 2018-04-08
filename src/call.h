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
#ifndef PHP_CMARK_CALL_H
#define PHP_CMARK_CALL_H

typedef struct _php_cmark_call_t {
	cql_function_t   function;
	zend_object      std;
} php_cmark_call_t;

#define php_cmark_call_from(o) \
	((php_cmark_call_t*) \
		((char*) o - XtOffsetOf(php_cmark_call_t, std)))
#define php_cmark_call_fetch(z) php_cmark_call_from(Z_OBJ_P(z))

extern zend_class_entry *php_cmark_call_ce;

extern PHP_MINIT_FUNCTION(CommonMark_CQL);
extern PHP_RINIT_FUNCTION(CommonMark_CQL);
#endif
