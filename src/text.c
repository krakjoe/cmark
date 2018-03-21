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
#ifndef PHP_CMARK_NODE_TEXT
#define PHP_CMARK_NODE_TEXT

#include <php.h>

#include <src/common.h>
#include <src/node.h>
#include <src/handlers.h>

zend_class_entry *php_cmark_node_text_ce;
zend_class_entry *php_cmark_node_text_emphasis_ce;
zend_class_entry *php_cmark_node_text_strong_ce;

zend_object_handlers php_cmark_node_text_handlers;

typedef struct _php_cmark_node_text_t {
	php_cmark_node_t h;
	zval literal;
} php_cmark_node_text_t;

#define php_cmark_node_text_from(o) \
	((php_cmark_node_text_t*) \
		((char*) o - XtOffsetOf(php_cmark_node_text_t, h.std)))
#define php_cmark_node_text_fetch(z) php_cmark_node_text_from(Z_OBJ_P(z))

zend_object* php_cmark_node_text_create(zend_class_entry *ce) {
	php_cmark_node_text_t *n = 
		(php_cmark_node_text_t*) 
			ecalloc(1, sizeof(php_cmark_node_text_t));

	zend_object_std_init(
		php_cmark_node_zend(&n->h), ce);

	n->h.std.handlers = &php_cmark_node_text_handlers;

	return php_cmark_node_zend(&n->h);
}

zval* php_cmark_node_text_read(zval *object, zval *member, int type, void **rtc, zval *rv) {
	php_cmark_node_text_t *n = php_cmark_node_text_fetch(object);

	if (Z_TYPE_P(member) != IS_STRING) {
		goto php_cmark_node_text_read_error;
	}

	if (EXPECTED(rtc)) {
		if (RTC(rtc, cmark_node_get_literal))
			return php_cmark_node_read_str(&n->h, cmark_node_get_literal, &n->literal);
	}

	if (zend_string_equals_literal(Z_STR_P(member), "literal")) {
		return php_cmark_node_read_str(&n->h, 
			RTS(rtc, cmark_node_get_literal), &n->literal);
	}

php_cmark_node_text_read_error:
	return php_cmark_node_read(object, member, type, rtc, rv);
}

void php_cmark_node_text_write(zval *object, zval *member, zval *value, void **rtc) {
	php_cmark_node_text_t *n = php_cmark_node_text_fetch(object);

	if (EXPECTED(rtc)) {
		if (RTC(rtc, cmark_node_set_literal)) {
			php_cmark_assert_type(value, IS_STRING, 0, 
				"literal expected to be string");

			php_cmark_node_write_str(&n->h, cmark_node_set_literal, value, &n->literal);
			return;
		}	
	}

	if (Z_TYPE_P(member) == IS_STRING) {
		if (zend_string_equals_literal(Z_STR_P(member), "literal")) {
			php_cmark_assert_type(value, IS_STRING, 0, 
				"literal expected to be string");

			php_cmark_node_write_str(&n->h, 
				RTS(rtc, cmark_node_set_literal), value, &n->literal);
			return;
		}
	}

	php_cmark_node_write(object, member, value, rtc);
}

int php_cmark_node_text_isset(zval *object, zval *member, int has_set_exists, void **rtc) {
	php_cmark_node_text_t *n = php_cmark_node_text_fetch(object);
	zval *zv = &EG(uninitialized_zval);

	if (Z_TYPE_P(member) != IS_STRING) {
		return 0;
	}

	if (has_set_exists == 2) {
		if (EXPECTED(rtc)) {
			if (RTC(rtc, cmark_node_get_literal))
				return 1;
		}

		if (zend_string_equals_literal(Z_STR_P(member), "literal")) {
			return RTS(rtc, cmark_node_get_literal) != NULL;
		}
	}

	if (EXPECTED(rtc)) {
		if (RTC(rtc, cmark_node_get_literal)) {
			zv = php_cmark_node_read_str(&n->h, 
				RTS(rtc, cmark_node_get_literal), &n->literal);
			goto php_cmark_node_text_isset_result;
		}
	}

	if (zend_string_equals_literal(Z_STR_P(member), "literal")) {
		zv = php_cmark_node_read_str(&n->h, 
			RTS(rtc, cmark_node_get_literal), &n->literal);
	}

php_cmark_node_text_isset_result:
	if (Z_TYPE_P(zv) == IS_STRING) {
		return 1;
	}

	return php_cmark_node_isset(object, member, has_set_exists, rtc);
}

void php_cmark_node_text_unset(zval *object, zval *member, void **rtc) {
	php_cmark_node_text_t *n = php_cmark_node_text_fetch(object);

	if (Z_TYPE_P(member) != IS_STRING) {
		goto php_cmark_node_text_unset_error;
	}

	if (EXPECTED(rtc)) {
		if (RTC(rtc, cmark_node_set_literal)) {
			php_cmark_node_write_str(&n->h, cmark_node_set_literal, NULL, &n->literal);
			return;
		}
	}

	if (zend_string_equals_literal(Z_STR_P(member), "literal")) {
		php_cmark_node_write_str(&n->h, 
			RTS(rtc, cmark_node_set_literal), NULL, &n->literal);
		return;
	}

php_cmark_node_text_unset_error:
	return php_cmark_node_unset(object, member, rtc);
}

void php_cmark_node_text_free(zend_object *zo) {
	php_cmark_node_text_t *n = 
		php_cmark_node_text_from(zo);

	if (!Z_ISUNDEF(n->literal)) {
		zval_ptr_dtor(&n->literal);
	}

	php_cmark_node_free(zo);
}

ZEND_BEGIN_ARG_INFO_EX(php_cmark_node_text_construct, 0, 0, 0)
	ZEND_ARG_INFO(0, literal)
ZEND_END_ARG_INFO()

PHP_METHOD(Text, __construct)
{
	php_cmark_node_text_t *n = php_cmark_node_text_fetch(getThis());
	zval *literal = NULL;

	ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL(literal)
	ZEND_PARSE_PARAMETERS_END();

	php_cmark_assert_type(literal, IS_STRING, 1, "literal expected to be string");

	php_cmark_node_new(getThis(), CMARK_NODE_TEXT);

	if (literal) {
		php_cmark_node_write_str(&n->h, 
			(cmark_node_write_str) cmark_node_set_literal, 
			literal, &n->literal);
	}
}

static zend_function_entry php_cmark_node_text_methods[] = {
	PHP_ME(Text, __construct, php_cmark_node_text_construct, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

PHP_METHOD(Emphasis, __construct)
{
	php_cmark_no_parameters();

	php_cmark_node_new(getThis(), CMARK_NODE_EMPH);
}

static zend_function_entry php_cmark_node_text_emphasis_methods[] = {
	PHP_ME(Emphasis, __construct, php_cmark_no_arginfo, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

PHP_METHOD(Strong, __construct)
{
	php_cmark_no_parameters();

	php_cmark_node_new(getThis(), CMARK_NODE_STRONG);
}

static zend_function_entry php_cmark_node_text_strong_methods[] = {
	PHP_ME(Strong, __construct, php_cmark_no_arginfo, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

PHP_MINIT_FUNCTION(CommonMark_Node_Text) 
{
	zend_class_entry ce;

	INIT_NS_CLASS_ENTRY(ce, "CommonMark\\Node", "Text", php_cmark_node_text_methods);

	php_cmark_node_text_ce = zend_register_internal_class_ex(&ce, php_cmark_node_ce);
	php_cmark_node_text_ce->create_object = php_cmark_node_text_create;

#define php_cmark_node_text_property(n) \
	zend_declare_property_null(php_cmark_node_text_ce, ZEND_STRL(n), ZEND_ACC_PUBLIC)

	php_cmark_node_text_property("literal");
#undef php_cmark_node_text_property

	memcpy(&php_cmark_node_text_handlers, &php_cmark_node_handlers, sizeof(zend_object_handlers));

	php_cmark_node_text_handlers.free_obj = php_cmark_node_text_free;
	php_cmark_node_text_handlers.read_property = php_cmark_node_text_read;
	php_cmark_node_text_handlers.write_property = php_cmark_node_text_write;
	php_cmark_node_text_handlers.has_property = php_cmark_node_text_isset;
	php_cmark_node_text_handlers.unset_property = php_cmark_node_text_unset;

	INIT_NS_CLASS_ENTRY(ce, "CommonMark\\Node\\Text", "Emphasis", php_cmark_node_text_emphasis_methods);

	php_cmark_node_text_emphasis_ce = zend_register_internal_class_ex(&ce, php_cmark_node_ce);

	INIT_NS_CLASS_ENTRY(ce, "CommonMark\\Node\\Text", "Strong", php_cmark_node_text_strong_methods);

	php_cmark_node_text_strong_ce = zend_register_internal_class_ex(&ce, php_cmark_node_ce);

	return SUCCESS;
}

PHP_RINIT_FUNCTION(CommonMark_Node_Text)
{
	php_cmark_node_text_ce->ce_flags |= ZEND_ACC_FINAL;
	php_cmark_node_text_emphasis_ce->ce_flags |= ZEND_ACC_FINAL;
	php_cmark_node_text_strong_ce->ce_flags |= ZEND_ACC_FINAL;

	return SUCCESS;
}
#endif
