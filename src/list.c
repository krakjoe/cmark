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
#ifndef PHP_CMARK_LIST
#define PHP_CMARK_LIST

#include <php.h>

#include <ext/spl/spl_exceptions.h>

#include <zend_exceptions.h>

#include <cmark.h>

#include <src/common.h>
#include <src/node.h>
#include <src/handlers.h>
#include <src/list.h>

zend_class_entry*      php_cmark_node_list_ordered_ce;
zend_class_entry*      php_cmark_node_list_bullet_ce;

zend_object_handlers php_cmark_node_list_handlers;
zend_object_handlers php_cmark_node_ordered_list_handlers;

typedef struct _php_cmark_node_list_t {
	php_cmark_node_t h;
	zval tight;
	zval delimiter;
} php_cmark_node_list_t;

#define php_cmark_node_list_from(o) \
	((php_cmark_node_list_t*) \
		((char*) o - XtOffsetOf(php_cmark_node_list_t, h.std)))
#define php_cmark_node_list_fetch(z) php_cmark_node_list_from(Z_OBJ_P(z))

zend_object* php_cmark_node_list_create(zend_class_entry *ce) {
	php_cmark_node_list_t *n = 
		(php_cmark_node_list_t*) 
			ecalloc(1, sizeof(php_cmark_node_list_t));

	zend_object_std_init(
		php_cmark_node_zend(&n->h), ce);

	n->h.std.handlers = &php_cmark_node_list_handlers;

	return php_cmark_node_zend(&n->h);
}

zval* php_cmark_node_list_read(zval *object, zval *member, int type, void **rtc, zval *rv) {
	php_cmark_node_list_t *n = php_cmark_node_list_fetch(object);

	if (Z_TYPE_P(member) != IS_STRING) {
		goto php_cmark_node_list_read_error;
	}

	if (EXPECTED(rtc)) {
		if (RTC(rtc, cmark_node_get_list_tight))
			return php_cmark_node_read_bool(&n->h, 
				(cmark_node_read_int) cmark_node_get_list_tight, &n->tight);
		if (RTC(rtc, cmark_node_get_list_delim))
			return php_cmark_node_read_int(&n->h, 
				(cmark_node_read_int) cmark_node_get_list_delim, &n->delimiter);
	}

	if (zend_string_equals_literal(Z_STR_P(member), "tight")) {
		return php_cmark_node_read_bool(&n->h, (cmark_node_read_int) 
			RTS(rtc, cmark_node_get_list_tight), &n->tight);
	} else if (zend_string_equals_literal(Z_STR_P(member), "delimiter")) {
		return php_cmark_node_read_int(&n->h, (cmark_node_read_int) 
			RTS(rtc, cmark_node_get_list_delim), &n->delimiter);
	}

php_cmark_node_list_read_error:
	return php_cmark_node_read(object, member, type, rtc, rv);
}

void php_cmark_node_list_write(zval *object, zval *member, zval *value, void **rtc) {
	php_cmark_node_list_t *n = php_cmark_node_list_fetch(object);

	if (EXPECTED(rtc)) {
		if (RTC(rtc, cmark_node_set_list_tight)) {
			php_cmark_assert_type(
				value, _IS_BOOL, 0, "tight expected to be bool");
			php_cmark_node_write_bool(&n->h, 
				(cmark_node_write_int) cmark_node_set_list_tight, value, &n->tight);
			return;
		} else if (RTC(rtc, cmark_node_set_list_delim)) {
			php_cmark_assert_type(
				value, IS_LONG, 0, "delimiter expected to be int");
			php_cmark_node_write_int(&n->h, 
				(cmark_node_write_int) cmark_node_set_list_delim, value, &n->delimiter);
			return;
		}
	}

	if (Z_TYPE_P(member) == IS_STRING) {
		if (zend_string_equals_literal(Z_STR_P(member), "tight")) {
			php_cmark_assert_type(
				value, _IS_BOOL, 0, "tight expected to be bool");
			php_cmark_node_write_bool(&n->h, 
				(cmark_node_write_int) RTS(rtc, cmark_node_set_list_tight), value, &n->tight);
			return;
		} else if (zend_string_equals_literal(Z_STR_P(member), "delimiter")) {
			php_cmark_assert_type(
				value, IS_LONG, 0, "delimiter expected to be int");
			php_cmark_node_write_int(&n->h, 
				(cmark_node_write_int) RTS(rtc, cmark_node_set_list_delim), value, &n->delimiter);
			return;
		}
	}

	php_cmark_node_write(object, member, value, rtc);
}

int php_cmark_node_list_isset(zval *object, zval *member, int has_set_exists, void **rtc) {
	php_cmark_node_list_t *n = php_cmark_node_list_fetch(object);
	zval *zv = &EG(uninitialized_zval);

	if (Z_TYPE_P(member) != IS_STRING) {
		return 0;
	}

	if (EXPECTED(rtc)) {
		if (RTC(rtc, cmark_node_get_list_tight)) {
			zv = php_cmark_node_read_bool(&n->h, 
				(cmark_node_read_int) cmark_node_get_list_tight, &n->tight);
			goto php_cmark_node_list_isset_result;
		} else if (RTC(rtc, cmark_node_get_list_delim)) {
			zv = php_cmark_node_read_int(&n->h, 
				(cmark_node_read_int) cmark_node_get_list_delim, &n->delimiter);
			goto php_cmark_node_list_isset_result;
		}
	}

	if (zend_string_equals_literal(Z_STR_P(member), "tight")) {
		zv = php_cmark_node_read_bool(&n->h, 
			(cmark_node_read_int) RTS(rtc, cmark_node_get_list_tight), &n->tight);
	} else if (zend_string_equals_literal(Z_STR_P(member), "delimiter")) {
		zv = php_cmark_node_read_int(&n->h, 
			(cmark_node_read_int) RTS(rtc, cmark_node_get_list_delim), &n->delimiter);
	}

php_cmark_node_list_isset_result:
	if (Z_TYPE_P(zv) == IS_TRUE || 
	    Z_TYPE_P(zv) == IS_FALSE ||
	    (Z_TYPE_P(zv) == IS_LONG && Z_LVAL_P(zv))) {
		return 1;
	}

	return php_cmark_node_isset(object, member, has_set_exists, rtc);
}

typedef struct _php_cmark_node_ordered_list_t {
	php_cmark_node_t h;
	zval tight;
	zval delimiter;
	zval start;
} php_cmark_node_ordered_list_t;

#define php_cmark_node_ordered_list_from(o) \
	((php_cmark_node_ordered_list_t*) \
		((char*) o - XtOffsetOf(php_cmark_node_ordered_list_t, h.std)))
#define php_cmark_node_ordered_list_fetch(z) php_cmark_node_ordered_list_from(Z_OBJ_P(z))

zend_object* php_cmark_node_ordered_list_create(zend_class_entry *ce) {
	php_cmark_node_ordered_list_t *n = 
		(php_cmark_node_ordered_list_t*) 
			ecalloc(1, sizeof(php_cmark_node_ordered_list_t));

	zend_object_std_init(
		php_cmark_node_zend(&n->h), ce);

	n->h.std.handlers = &php_cmark_node_ordered_list_handlers;

	return php_cmark_node_zend(&n->h);
}

zval* php_cmark_node_ordered_list_read(zval *object, zval *member, int type, void **rtc, zval *rv) {
	php_cmark_node_ordered_list_t *n = php_cmark_node_ordered_list_fetch(object);

	if (Z_TYPE_P(member) != IS_STRING) {
		goto php_cmark_node_ordered_list_read_error;
	}

	if (EXPECTED(rtc)) {
		if (RTC(rtc, cmark_node_get_list_start))
			return php_cmark_node_read_int(&n->h, 
				(cmark_node_read_int) cmark_node_get_list_start, &n->start);
	}

	if (zend_string_equals_literal(Z_STR_P(member), "start")) {
		return php_cmark_node_read_int(&n->h, 
			(cmark_node_read_int) RTS(rtc, cmark_node_get_list_start), &n->start);
	}

php_cmark_node_ordered_list_read_error:
	return php_cmark_node_list_read(object, member, type, rtc, rv);
}

void php_cmark_node_ordered_list_write(zval *object, zval *member, zval *value, void **rtc) {
	php_cmark_node_ordered_list_t *n = php_cmark_node_ordered_list_fetch(object);

	if (EXPECTED(rtc)) {
		if (RTC(rtc, cmark_node_set_list_start)) {
			php_cmark_assert_type(
				value, IS_LONG, 0, "start expected to be int");
			php_cmark_node_write_int(&n->h, 
				(cmark_node_write_int) cmark_node_set_list_start, value, &n->start);
			return;
		}
	}

	if (Z_TYPE_P(member) == IS_STRING) {
		if (zend_string_equals_literal(Z_STR_P(member), "start")) {
			php_cmark_assert_type(
				value, IS_LONG, 0, "start expected to be int");
			php_cmark_node_write_int(&n->h, 
				(cmark_node_write_int) RTS(rtc, cmark_node_set_list_start), value, &n->tight);
			return;
		}
	}

	php_cmark_node_list_write(object, member, value, rtc);
}

int php_cmark_node_ordered_list_isset(zval *object, zval *member, int has_set_exists, void **rtc) {
	php_cmark_node_ordered_list_t *n = php_cmark_node_ordered_list_fetch(object);
	zval *zv = &EG(uninitialized_zval);

	if (Z_TYPE_P(member) != IS_STRING) {
		return 0;
	}

	if (EXPECTED(rtc)) {
		if (RTC(rtc, cmark_node_get_list_start)) {
			zv = php_cmark_node_read_int(&n->h, 
				(cmark_node_read_int) cmark_node_get_list_start, &n->start);
			goto php_cmark_node_ordered_list_isset_result;
		}
	}

	if (zend_string_equals_literal(Z_STR_P(member), "start")) {
		zv = php_cmark_node_read_int(&n->h, (cmark_node_read_int) 
			RTS(rtc, cmark_node_get_list_start), &n->start);
	}

php_cmark_node_ordered_list_isset_result:
	if (Z_TYPE_P(zv) == IS_LONG && Z_LVAL_P(zv)) {
		return 1;
	}

	return php_cmark_node_list_isset(object, member, has_set_exists, rtc);
}

ZEND_BEGIN_ARG_INFO_EX(php_cmark_node_ordered_list_construct, 0, 0, 0)
	ZEND_ARG_INFO(0, tight)
	ZEND_ARG_INFO(0, delimiter)
	ZEND_ARG_INFO(0, start)
ZEND_END_ARG_INFO()

PHP_METHOD(OrderedList, __construct)
{
	php_cmark_node_ordered_list_t *n = php_cmark_node_ordered_list_fetch(getThis());
	zval *tight = NULL;
	zval *delimiter = NULL;
	zval *start = NULL;

	ZEND_BEGIN_PARAMS(0, 3)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL(tight)
		Z_PARAM_ZVAL(delimiter)
		Z_PARAM_ZVAL(start)
	ZEND_END_PARAMS();

	php_cmark_assert_type(tight, _IS_BOOL, 1, "tight expected to be bool");
	php_cmark_assert_type(delimiter, IS_LONG, 1, "delimiter expected to be int");
	php_cmark_assert_type(start, IS_LONG, 1, "start expected to be int");

	php_cmark_node_list_new(getThis(), CMARK_ORDERED_LIST);

	if (tight) {
		php_cmark_node_write_bool(&n->h, 
			(cmark_node_write_int) cmark_node_set_list_tight, 
			tight, &n->tight);
	}

	if (delimiter) {
		php_cmark_node_write_int(&n->h, 
			(cmark_node_write_int) cmark_node_set_list_delim, 
			delimiter, &n->delimiter);
	}

	if (start) {
		php_cmark_node_write_int(&n->h, 
			(cmark_node_write_int) cmark_node_set_list_start, 
			start, &n->start);
	}
}

static zend_function_entry php_cmark_node_list_ordered_methods[] = {
	PHP_ME(OrderedList, __construct, php_cmark_node_ordered_list_construct, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

ZEND_BEGIN_ARG_INFO_EX(php_cmark_node_bullet_list_construct, 0, 0, 0)
	ZEND_ARG_INFO(0, tight)
	ZEND_ARG_INFO(0, delimiter)
ZEND_END_ARG_INFO()

PHP_METHOD(BulletList, __construct)
{
	php_cmark_node_list_t *n = php_cmark_node_list_fetch(getThis());
	zval *tight = NULL;
	zval *delimiter = NULL;

	ZEND_BEGIN_PARAMS(0, 2)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL(tight)
		Z_PARAM_ZVAL(delimiter)
	ZEND_END_PARAMS();

	php_cmark_assert_type(tight, _IS_BOOL, 1, "tight expected to be bool");
	php_cmark_assert_type(delimiter, IS_LONG, 1, "delimiter expected to be int");

	php_cmark_node_list_new(getThis(), CMARK_BULLET_LIST);

	if (tight) {
		php_cmark_node_write_bool(&n->h, 
			(cmark_node_write_int) cmark_node_set_list_tight, 
			tight, &n->tight);
	}

	if (delimiter) {
		php_cmark_node_write_int(&n->h, 
			(cmark_node_write_int) cmark_node_set_list_delim, 
			delimiter, &n->delimiter);
	}
}

static zend_function_entry php_cmark_node_list_bullet_methods[] = {
	PHP_ME(BulletList, __construct, php_cmark_node_bullet_list_construct, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

PHP_MINIT_FUNCTION(CommonMark_Node_List) {
	zend_class_entry ce;

	REGISTER_NS_LONG_CONSTANT("CommonMark\\Node\\Lists\\Delimit", "Period", CMARK_PERIOD_DELIM, CONST_CS|CONST_PERSISTENT);
	REGISTER_NS_LONG_CONSTANT("CommonMark\\Node\\Lists\\Delimit", "Paren", CMARK_PAREN_DELIM, CONST_CS|CONST_PERSISTENT);

	INIT_NS_CLASS_ENTRY(ce, "CommonMark\\Node", "OrderedList", php_cmark_node_list_ordered_methods);
	
	php_cmark_node_list_ordered_ce = zend_register_internal_class_ex(&ce, php_cmark_node_ce);
	php_cmark_node_list_ordered_ce->create_object = php_cmark_node_ordered_list_create;

#define php_cmark_node_list_property(n) \
	zend_declare_property_null(php_cmark_node_list_ordered_ce, ZEND_STRL(n), ZEND_ACC_PUBLIC)

	php_cmark_node_list_property("tight");
	php_cmark_node_list_property("delimiter");
	php_cmark_node_list_property("start");
#undef php_cmark_node_list_property

	memcpy(&php_cmark_node_ordered_list_handlers, &php_cmark_node_handlers, sizeof(zend_object_handlers));

	php_cmark_node_ordered_list_handlers.read_property = php_cmark_node_ordered_list_read;
	php_cmark_node_ordered_list_handlers.write_property = php_cmark_node_ordered_list_write;
	php_cmark_node_ordered_list_handlers.has_property = php_cmark_node_ordered_list_isset;

	INIT_NS_CLASS_ENTRY(ce, "CommonMark\\Node", "BulletList", php_cmark_node_list_bullet_methods);

	php_cmark_node_list_bullet_ce = zend_register_internal_class_ex(&ce, php_cmark_node_ce);
	php_cmark_node_list_bullet_ce->create_object = php_cmark_node_list_create;

#define php_cmark_node_list_property(n) \
	zend_declare_property_null(php_cmark_node_list_bullet_ce, ZEND_STRL(n), ZEND_ACC_PUBLIC)

	php_cmark_node_list_property("tight");
	php_cmark_node_list_property("delimiter");
#undef php_cmark_node_list_property

	memcpy(&php_cmark_node_list_handlers, &php_cmark_node_handlers, sizeof(zend_object_handlers));

	php_cmark_node_list_handlers.read_property = php_cmark_node_list_read;
	php_cmark_node_list_handlers.write_property = php_cmark_node_list_write;
	php_cmark_node_list_handlers.has_property = php_cmark_node_list_isset;

	return SUCCESS;
}

PHP_RINIT_FUNCTION(CommonMark_Node_List)
{
	php_cmark_node_list_ordered_ce->ce_flags |= ZEND_ACC_FINAL;
	php_cmark_node_list_bullet_ce->ce_flags |= ZEND_ACC_FINAL;

	return SUCCESS;
}
#endif
