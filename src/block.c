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
#ifndef PHP_CMARK_NODE_BLOCK
#define PHP_CMARK_NODE_BLOCK

#include <php.h>

#include <src/common.h>
#include <src/node.h>
#include <src/custom.h>
#include <src/text.h>
#include <src/handlers.h>

zend_class_entry *php_cmark_node_code_block_ce;
zend_class_entry *php_cmark_node_html_block_ce;
zend_class_entry *php_cmark_node_custom_block_ce;

zend_object_handlers php_cmark_node_code_block_handlers;

typedef struct _php_cmark_node_code_block_t {
	php_cmark_node_text_t h;
	zval fence;
} php_cmark_node_code_block_t;

#define php_cmark_node_code_block_from(o) \
	((php_cmark_node_code_block_t*) \
		((char*) o - XtOffsetOf(php_cmark_node_code_block_t, h.h.std)))
#define php_cmark_node_code_block_fetch(z) php_cmark_node_code_block_from(Z_OBJ_P(z))

zend_object* php_cmark_node_code_block_create(zend_class_entry *ce) {
	php_cmark_node_code_block_t *n = 
		(php_cmark_node_code_block_t*) 
			ecalloc(1, sizeof(php_cmark_node_code_block_t));

	zend_object_std_init(
		php_cmark_node_zend(&n->h.h), ce);

	n->h.h.std.handlers = &php_cmark_node_code_block_handlers;

	return php_cmark_node_zend(&n->h.h);
}

#if PHP_VERSION_ID >= 80000
zval* php_cmark_node_code_block_read(zend_object *object, zend_string *member, int type, void **rtc, zval *rv) {
	php_cmark_node_code_block_t *n = php_cmark_node_code_block_from(object);
#else
zval* php_cmark_node_code_block_read(zval *object, zval *member, int type, void **rtc, zval *rv) {
	php_cmark_node_code_block_t *n = php_cmark_node_code_block_fetch(object);

	if (Z_TYPE_P(member) != IS_STRING) {
		goto php_cmark_node_code_block_read_error;
	}
#endif

	if (EXPECTED(rtc)) {
		if (RTC(rtc, cmark_node_get_fence_info))
			return php_cmark_node_read_str(&n->h.h, 
				cmark_node_get_fence_info, &n->fence, rv);
	}

#if PHP_VERSION_ID >= 80000
	if (zend_string_equals_literal(member, "fence")) {
#else
	if (zend_string_equals_literal(Z_STR_P(member), "fence")) {
#endif
		return php_cmark_node_read_str(&n->h.h, 
			RTS(rtc, cmark_node_get_fence_info), &n->fence, rv);
	}

php_cmark_node_code_block_read_error:
	return php_cmark_node_text_read(object, member, type, rtc, rv);
}

#if PHP_VERSION_ID >= 80000
zval* php_cmark_node_code_block_write(zend_object *object, zend_string *member, zval *value, void **rtc) {
	php_cmark_node_code_block_t *n = php_cmark_node_code_block_from(object);
#elif PHP_VERSION_ID >= 70400
zval* php_cmark_node_code_block_write(zval *object, zval *member, zval *value, void **rtc) {
	php_cmark_node_code_block_t *n = php_cmark_node_code_block_fetch(object);
#else
void php_cmark_node_code_block_write(zval *object, zval *member, zval *value, void **rtc) {
	php_cmark_node_code_block_t *n = php_cmark_node_code_block_fetch(object);
#endif

	if (EXPECTED(rtc)) {
		if (RTC(rtc, cmark_node_set_fence_info)) {
			php_cmark_assert_type(value, IS_STRING, 0, 
#if PHP_VERSION_ID >= 70400
                return &EG(uninitialized_zval),
#else
                return,
#endif
				"fence expected to be string");

			php_cmark_node_write_str(&n->h.h, 
				cmark_node_set_fence_info, value, &n->fence);
#if PHP_VERSION_ID >= 70400
			return value;
#else
			return;
#endif
		}	
	}

#if PHP_VERSION_ID < 80000
	if (Z_TYPE_P(member) == IS_STRING) {
#endif
#if PHP_VERSION_ID >= 80000
		if (zend_string_equals_literal(member, "fence")) {
#else
		if (zend_string_equals_literal(Z_STR_P(member), "fence")) {
#endif
			php_cmark_assert_type(value, IS_STRING, 0, 
#if PHP_VERSION_ID >= 70400
                return &EG(uninitialized_zval),
#else
                return,
#endif
				"fence expected to be string");

			php_cmark_node_write_str(&n->h.h, 
				RTS(rtc, cmark_node_set_fence_info), value, &n->fence);
#if PHP_VERSION_ID >= 70400
			return value;
#else
			return;
#endif
		}
#if PHP_VERSION_ID < 80000
	}
#endif

#if PHP_VERSION_ID >= 70400
    return php_cmark_node_text_write(object, member, value, rtc);
#else
	php_cmark_node_text_write(object, member, value, rtc);
#endif
}

#if PHP_VERSION_ID >= 80000
int php_cmark_node_code_block_isset(zend_object *object, zend_string *member, int has_set_exists, void **rtc) {
	php_cmark_node_code_block_t *n = php_cmark_node_code_block_from(object);
#else
int php_cmark_node_code_block_isset(zval *object, zval *member, int has_set_exists, void **rtc) {
	php_cmark_node_code_block_t *n = php_cmark_node_code_block_fetch(object);
#endif
	zval *zv = &EG(uninitialized_zval);

#if PHP_VERSION_ID < 80000
	if (Z_TYPE_P(member) != IS_STRING) {
		return 0;
	}
#endif

	if (EXPECTED(rtc)) {
		if (RTC(rtc, cmark_node_get_fence_info)) {
			zv = php_cmark_node_read_str(&n->h.h, 
				cmark_node_get_fence_info, &n->fence, NULL);
			goto php_cmark_node_code_block_isset_result;
		}
	}

#if PHP_VERSION_ID >= 80000
	if (zend_string_equals_literal(member, "fence")) {
#else
	if (zend_string_equals_literal(Z_STR_P(member), "fence")) {
#endif
		zv = php_cmark_node_read_str(&n->h.h, 
			RTS(rtc, cmark_node_get_fence_info), &n->fence, NULL);
	}

php_cmark_node_code_block_isset_result:
	if (Z_TYPE_P(zv) == IS_STRING) {
		return 1;
	}

	return php_cmark_node_text_isset(object, member, has_set_exists, rtc);
}

#if PHP_VERSION_ID >= 80000
void php_cmark_node_code_block_unset(zend_object *object, zend_string *member, void **rtc) {
	php_cmark_node_code_block_t *n = php_cmark_node_code_block_from(object);
#else
void php_cmark_node_code_block_unset(zval *object, zval *member, void **rtc) {
	php_cmark_node_code_block_t *n = php_cmark_node_code_block_fetch(object);

	if (Z_TYPE_P(member) != IS_STRING) {
		goto php_cmark_node_code_block_unset_error;
	}
#endif

	if (EXPECTED(rtc)) {
		if (RTC(rtc, cmark_node_set_fence_info)) {
			php_cmark_node_write_str(&n->h.h, 
				cmark_node_set_fence_info, NULL, &n->fence);
			return;
		}
	}

#if PHP_VERSION_ID >= 80000
	if (zend_string_equals_literal(member, "fence")) {
#else
	if (zend_string_equals_literal(Z_STR_P(member), "fence")) {
#endif
		php_cmark_node_write_str(&n->h.h, 
			RTS(rtc, cmark_node_set_fence_info), NULL, &n->fence);
		return;
	}

php_cmark_node_code_block_unset_error:
	return php_cmark_node_text_unset(object, member, rtc);
}

ZEND_BEGIN_ARG_INFO_EX(php_cmark_node_code_block_construct, 0, 0, 0)
	ZEND_ARG_INFO(0, fence)
	ZEND_ARG_INFO(0, literal)
ZEND_END_ARG_INFO()

PHP_METHOD(CodeBlock, __construct)
{
	php_cmark_node_code_block_t *n = php_cmark_node_code_block_fetch(getThis());
	zval *fence = NULL;
	zval *literal = NULL;

	if (ZEND_NUM_ARGS() == 1) {
		ZEND_BEGIN_PARAMS(1, 1)
			Z_PARAM_ZVAL(literal)
		ZEND_END_PARAMS();
	} else {
		ZEND_BEGIN_PARAMS(0, 2)
			Z_PARAM_OPTIONAL
			Z_PARAM_ZVAL(fence)
			Z_PARAM_ZVAL(literal)
		ZEND_END_PARAMS();
	}

	php_cmark_assert_type(fence, IS_STRING, 1, return, "fence expected to be string");
	php_cmark_assert_type(literal, IS_STRING, 1, return, "literal expected to be string");

	php_cmark_node_new(
		getThis(), CMARK_NODE_CODE_BLOCK);

	switch (ZEND_NUM_ARGS()) {
		case 2:
			php_cmark_node_write_str(&n->h.h, cmark_node_set_fence_info, fence, &n->fence);

		case 1:
			php_cmark_node_write_str(&n->h.h, cmark_node_set_literal, literal, &n->h.literal);
		break;
	}
}

static zend_function_entry php_cmark_node_code_block_methods[] = {
	PHP_ME(CodeBlock, __construct, php_cmark_node_code_block_construct, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

ZEND_BEGIN_ARG_INFO_EX(php_cmark_node_html_block_construct, 0, 0, 0)
	ZEND_ARG_INFO(0, literal)
ZEND_END_ARG_INFO()

PHP_METHOD(HTMLBlock, __construct)
{
	php_cmark_node_text_t *n = php_cmark_node_text_fetch(getThis());
	zval *literal = NULL;

	ZEND_BEGIN_PARAMS(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL(literal)
	ZEND_END_PARAMS();

	php_cmark_assert_type(
		literal, IS_STRING, 1, return, "literal expected to be string");

	php_cmark_node_new(getThis(), CMARK_NODE_HTML_BLOCK);

	if (literal) {
		php_cmark_node_write_str(&n->h, 
			(cmark_node_write_str) cmark_node_set_literal, 
			literal, &n->literal);
	}
}

static zend_function_entry php_cmark_node_html_block_methods[] = {
	PHP_ME(HTMLBlock, __construct, php_cmark_node_html_block_construct, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

PHP_METHOD(CustomBlock, __construct)
{
	php_cmark_no_parameters();

	php_cmark_node_new(getThis(), CMARK_NODE_CUSTOM_BLOCK);
}

static zend_function_entry php_cmark_node_custom_block_methods[] = {
	PHP_ME(CustomBlock, __construct, php_cmark_no_arginfo, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

PHP_MINIT_FUNCTION(CommonMark_Node_Block) 
{
	zend_class_entry ce;

	INIT_NS_CLASS_ENTRY(ce, "CommonMark\\Node", "CodeBlock", php_cmark_node_code_block_methods);

	php_cmark_node_code_block_ce = zend_register_internal_class_ex(&ce, php_cmark_node_text_ce);
	php_cmark_node_code_block_ce->create_object = php_cmark_node_code_block_create;

#define php_cmark_node_code_block_property(n) \
	zend_declare_property_null(php_cmark_node_code_block_ce, ZEND_STRL(n), ZEND_ACC_PUBLIC)

	php_cmark_node_code_block_property("fence");
#undef php_cmark_node_code_block_property

	memcpy(&php_cmark_node_code_block_handlers, &php_cmark_node_text_handlers, sizeof(zend_object_handlers));

	php_cmark_node_code_block_handlers.read_property = php_cmark_node_code_block_read;
	php_cmark_node_code_block_handlers.write_property = php_cmark_node_code_block_write;
	php_cmark_node_code_block_handlers.has_property = php_cmark_node_code_block_isset;
	php_cmark_node_code_block_handlers.unset_property = php_cmark_node_code_block_unset;

	INIT_NS_CLASS_ENTRY(ce, "CommonMark\\Node", "HTMLBlock", php_cmark_node_html_block_methods);

	php_cmark_node_html_block_ce = zend_register_internal_class_ex(&ce, php_cmark_node_text_ce);

	INIT_NS_CLASS_ENTRY(ce, "CommonMark\\Node", "CustomBlock", php_cmark_node_custom_block_methods);

	php_cmark_node_custom_block_ce = zend_register_internal_class_ex(&ce, php_cmark_node_ce);
	php_cmark_node_custom_block_ce->create_object = php_cmark_node_custom_create;

#define php_cmark_node_custom_block_property(n) \
	zend_declare_property_null(php_cmark_node_custom_block_ce, ZEND_STRL(n), ZEND_ACC_PUBLIC)

	php_cmark_node_custom_block_property("onEnter");
	php_cmark_node_custom_block_property("onLeave");
#undef php_cmark_node_custom_block_property

	return SUCCESS;
}

PHP_RINIT_FUNCTION(CommonMark_Node_Block)
{
	php_cmark_node_code_block_ce->ce_flags |= ZEND_ACC_FINAL;
	php_cmark_node_html_block_ce->ce_flags |= ZEND_ACC_FINAL;
	php_cmark_node_custom_block_ce->ce_flags |= ZEND_ACC_FINAL;

	return SUCCESS;
}
#endif
