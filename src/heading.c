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
#ifndef PHP_CMARK_NODE_HEADING
#define PHP_CMARK_NODE_HEADING

#include <php.h>

#include <src/common.h>
#include <src/node.h>
#include <src/handlers.h>

zend_class_entry *php_cmark_node_heading_ce;

zend_object_handlers php_cmark_node_heading_handlers;

typedef struct _php_cmark_node_heading_t {
	php_cmark_node_t h;
	zval level;
} php_cmark_node_heading_t;

#define php_cmark_node_heading_from(o) \
	((php_cmark_node_heading_t*) \
		((char*) o - XtOffsetOf(php_cmark_node_heading_t, h.std)))
#define php_cmark_node_heading_fetch(z) php_cmark_node_heading_from(Z_OBJ_P(z))

zend_object* php_cmark_node_heading_create(zend_class_entry *ce) {
	php_cmark_node_heading_t *n = 
		(php_cmark_node_heading_t*) 
			ecalloc(1, sizeof(php_cmark_node_heading_t));

	zend_object_std_init(
		php_cmark_node_zend(&n->h), ce);

	n->h.std.handlers = &php_cmark_node_heading_handlers;

	return php_cmark_node_zend(&n->h);
}

zval* php_cmark_node_heading_read(zval *object, zval *member, int type, void **rtc, zval *rv) {
	php_cmark_node_heading_t *n = php_cmark_node_heading_fetch(object);

	if (Z_TYPE_P(member) != IS_STRING) {
		goto php_cmark_node_heading_read_error;
	}

	if (EXPECTED(rtc)) {
		if (RTC(rtc, cmark_node_get_heading_level))
			return php_cmark_node_read_int(&n->h, 
				cmark_node_get_heading_level, &n->level);
	}

	if (zend_string_equals_literal(Z_STR_P(member), "level")) {
		return php_cmark_node_read_int(&n->h, 
			RTS(rtc, cmark_node_get_heading_level), &n->level);
	}

php_cmark_node_heading_read_error:
	return php_cmark_node_read(object, member, type, rtc, rv);
}

void php_cmark_node_heading_write(zval *object, zval *member, zval *value, void **rtc) {
	php_cmark_node_heading_t *n = php_cmark_node_heading_fetch(object);

	if (EXPECTED(rtc)) {
		if (RTC(rtc, cmark_node_set_heading_level)) {
			php_cmark_assert_type(
				value, IS_LONG, 0, "level expected to be int");
			php_cmark_node_write_int(&n->h, 
				cmark_node_set_heading_level, value, &n->level);
			return;
		}	
	}

	if (Z_TYPE_P(member) == IS_STRING) {
		if (zend_string_equals_literal(Z_STR_P(member), "level")) {
			php_cmark_assert_type(
				value, IS_LONG, 0, "level expected to be int");
			php_cmark_node_write_int(&n->h, 
				RTS(rtc, cmark_node_set_heading_level), value, &n->level);
			return;
		}
	}

	php_cmark_node_write(object, member, value, rtc);
}

int php_cmark_node_heading_isset(zval *object, zval *member, int has_set_exists, void **rtc) {
	php_cmark_node_heading_t *n = php_cmark_node_heading_fetch(object);
	zval *zv = &EG(uninitialized_zval);

	if (Z_TYPE_P(member) != IS_STRING) {
		return 0;
	}

	if (EXPECTED(rtc)) {
		if (RTC(rtc, cmark_node_get_heading_level)) {
			zv = php_cmark_node_read_int(&n->h, 
				cmark_node_get_heading_level, &n->level);
			goto php_cmark_node_heading_isset_result;
		}
	}

	if (zend_string_equals_literal(Z_STR_P(member), "level")) {
		zv = php_cmark_node_read_int(&n->h, 
			RTS(rtc, cmark_node_get_heading_level), &n->level);
	}

php_cmark_node_heading_isset_result:
	if (Z_TYPE_P(zv) == IS_LONG) {
		return 1;
	}

	return php_cmark_node_isset(object, member, has_set_exists, rtc);
}

ZEND_BEGIN_ARG_INFO_EX(php_cmark_node_heading_construct, 0, 0, 0)
	ZEND_ARG_INFO(0, level)
ZEND_END_ARG_INFO()

PHP_METHOD(Heading, __construct)
{
	php_cmark_node_heading_t *n = php_cmark_node_heading_fetch(getThis());
	zval *level = NULL;

	ZEND_BEGIN_PARAMS(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL(level)
	ZEND_END_PARAMS();

	php_cmark_assert_type(
		level, IS_LONG, 1, "level expected to be int");

	php_cmark_node_new(getThis(), CMARK_NODE_HEADING);

	if (level) {
		php_cmark_node_write_int(&n->h, 
			cmark_node_set_heading_level, level, &n->level);
	}
}

static zend_function_entry php_cmark_node_heading_methods[] = {
	PHP_ME(Heading, __construct, php_cmark_no_arginfo, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

PHP_MINIT_FUNCTION(CommonMark_Node_Heading) 
{
	zend_class_entry ce;

	INIT_NS_CLASS_ENTRY(ce, "CommonMark\\Node", "Heading", php_cmark_node_heading_methods);

	php_cmark_node_heading_ce = zend_register_internal_class_ex(&ce, php_cmark_node_ce);
	php_cmark_node_heading_ce->create_object = php_cmark_node_heading_create;

#define php_cmark_node_heading_property(n) \
	zend_declare_property_null(php_cmark_node_heading_ce, ZEND_STRL(n), ZEND_ACC_PUBLIC)

	php_cmark_node_heading_property("level");
#undef php_cmark_node_heading_property

	memcpy(&php_cmark_node_heading_handlers, &php_cmark_node_handlers, sizeof(zend_object_handlers));

	php_cmark_node_heading_handlers.read_property = php_cmark_node_heading_read;
	php_cmark_node_heading_handlers.write_property = php_cmark_node_heading_write;
	php_cmark_node_heading_handlers.has_property = php_cmark_node_heading_isset;

	return SUCCESS;
}

PHP_RINIT_FUNCTION(CommonMark_Node_Heading)
{
	php_cmark_node_heading_ce->ce_flags |= ZEND_ACC_FINAL;

	return SUCCESS;
}
#endif
