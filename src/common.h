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
#ifndef HAVE_PHP_CMARK_COMMON_H
#define HAVE_PHP_CMARK_COMMON_H

#include <ext/spl/spl_exceptions.h>
#include <zend_exceptions.h>

#include <cmark.h>

#ifndef GC_ADDREF
#	define GC_ADDREF(g) ++GC_REFCOUNT(g)
#endif

#ifndef GC_DELREF
#	define GC_DELREF(g) --GC_REFCOUNT(g)
#endif

#if PHP_VERSION_ID >= 70200
#	define ZEND_BEGIN_ARG_INFO_WITH_RETURN_CLASS(name, ref, req, type, nullable) \
		ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(name, ref, req, type, nullable)
#else
#	define ZEND_BEGIN_ARG_INFO_WITH_RETURN_CLASS(name, ref, req, type, nullable) \
		ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(name, ref, req, IS_OBJECT, #type, nullable)
#endif

#define php_cmark_parse_parameters(s, ...) \
	zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS(), s, ##__VA_ARGS__)
#define php_cmark_throw_ex(e, s, ...) \
	zend_throw_exception_ex(spl_ce_##e, 0, s, ##__VA_ARGS__)
#define php_cmark_throw(s, ...) \
	php_cmark_throw_ex(RuntimeException, s, ##__VA_ARGS__)
#define php_cmark_wrong_parameters(s, ...) \
	zend_throw_exception_ex(zend_ce_type_error, 0, s, ##__VA_ARGS__)
#define php_cmark_no_parameters() do { \
	if (php_cmark_parse_parameters("") != SUCCESS) { \
		php_cmark_wrong_parameters("no parameters expected"); \
		return; \
	} \
} while(0)

#define php_cmark_chain_ex(t) ZVAL_ZVAL(return_value, t, 1, 0)
#define php_cmark_chain()     php_cmark_chain_ex(getThis())

ZEND_BEGIN_ARG_INFO_EX(php_cmark_no_arginfo, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(php_cmark_set_string_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, string)
ZEND_END_ARG_INFO()

#endif
