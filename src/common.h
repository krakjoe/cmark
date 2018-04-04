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

#if PHP_VERSION_ID < 70200
#define ZEND_BEGIN_PARAMS(min, max) \
	if (ZEND_NUM_ARGS() < min || ZEND_NUM_ARGS() > max) { \
		zend_throw_exception_ex(zend_ce_type_error, 0, "wrong argument count"); \
		return; \
	} \
	\
	ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, min, max)
#else
#define ZEND_BEGIN_PARAMS(min, max) \
	ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, min, max)
#endif
#define ZEND_END_PARAMS ZEND_PARSE_PARAMETERS_END

#define PHP_OBJ_SAFE_RELEASE(zz) do { \
	if (IS_OBJ_VALID(EG(objects_store).object_buckets[(zz)->handle])) \
		OBJ_RELEASE((zend_object*) (zz)); \
} while(0)

#define php_cmark_throw_ex(e, s, ...) \
	zend_throw_exception_ex(spl_ce_##e, 0, s, ##__VA_ARGS__)
#define php_cmark_throw(s, ...) \
	php_cmark_throw_ex(RuntimeException, s, ##__VA_ARGS__)
#define php_cmark_wrong_parameters(s, ...) \
	zend_throw_exception_ex(zend_ce_type_error, 0, s, ##__VA_ARGS__)
#define php_cmark_no_parameters() do { \
	if (ZEND_NUM_ARGS()) { \
		php_cmark_wrong_parameters("no parameters expected"); \
		return; \
	} \
} while(0)

#define php_cmark_assert_type(v, e, n, s, ...) do { \
	if ((!(v) && (n)) || ((v) && ZEND_SAME_FAKE_TYPE((e), Z_TYPE_P(v)))) \
		break; \
	\
	zend_throw_exception_ex(zend_ce_type_error, 0, (s), ##__VA_ARGS__); \
	return; \
} while(0)

#define php_cmark_assert_class(v, e, n, s, ...) do { \
	if ((!(v) && (n)) || ((v) && Z_TYPE_P((v)) == IS_OBJECT && instanceof_function(Z_OBJCE_P(v), (e)))) \
		break; \
	\
	zend_throw_exception_ex(zend_ce_type_error, 0, (s), ##__VA_ARGS__); \
	return; \
} while(0)

#define php_cmark_assert_range(v, min, max, n, s, ...) do { \
	if ((!(v) && (n)) || ((v) && Z_TYPE_P((v)) == IS_LONG && Z_LVAL_P((v)) >= (min) && Z_LVAL_P((v)) <= (max))) \
		break; \
	\
	zend_throw_exception_ex(zend_ce_type_error, 0, (s), ##__VA_ARGS__); \
	return; \
} while(0)

#define php_cmark_assert_range_ex(v, min, max, n, s, ...) do { \
	if ((!(v) && (n)) || ((v) && (v) >= (min) && (v) <= (max))) \
		break; \
	\
	zend_throw_exception_ex(zend_ce_type_error, 0, (s), ##__VA_ARGS__); \
	return; \
} while(0)

#define php_cmark_assert_count(v, e, n, s, ...) do { \
	if ((!(v) && (n)) || ((v) && Z_TYPE_P((v)) == IS_ARRAY && zend_hash_num_elements(Z_ARRVAL_P((v))) == (e))) \
		break; \
	\
	zend_throw_exception_ex(zend_ce_type_error, 0, (s), ##__VA_ARGS__); \
	return; \
} while(0)

#define php_cmark_chain_ex(t) ZVAL_ZVAL(return_value, t, 1, 0)
#define php_cmark_chain()     php_cmark_chain_ex(getThis())

ZEND_BEGIN_ARG_INFO_EX(php_cmark_no_arginfo, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(php_cmark_set_string_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, string)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(php_cmark_node_custom_set, 0, 0, 1)
	ZEND_ARG_INFO(0, literal)
ZEND_END_ARG_INFO()

extern cmark_mem php_cmark_mem;

#endif
