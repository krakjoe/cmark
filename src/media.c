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
#ifndef PHP_CMARK_NODE_MEDIA
#define PHP_CMARK_NODE_MEDIA

#include <php.h>

#include <src/common.h>
#include <src/node.h>
#include <src/handlers.h>

zend_class_entry *php_cmark_node_link_ce;
zend_class_entry *php_cmark_node_image_ce;

zend_object_handlers php_cmark_node_media_handlers;

typedef struct _php_cmark_node_media_t {
	php_cmark_node_t h;
	zval url;
	zval title;
} php_cmark_node_media_t;

#define php_cmark_node_media_from(o) \
	((php_cmark_node_media_t*) \
		((char*) o - XtOffsetOf(php_cmark_node_media_t, h.std)))
#define php_cmark_node_media_fetch(z) php_cmark_node_media_from(Z_OBJ_P(z))

zend_object* php_cmark_node_media_create(zend_class_entry *ce) {
	php_cmark_node_media_t *n = 
		(php_cmark_node_media_t*) 
			ecalloc(1, sizeof(php_cmark_node_media_t));

	zend_object_std_init(
		php_cmark_node_zend(&n->h), ce);

	n->h.std.handlers = &php_cmark_node_media_handlers;

	return php_cmark_node_zend(&n->h);
}

zval* php_cmark_node_media_read(zval *object, zval *member, int type, void **rtc, zval *rv) {
	php_cmark_node_media_t *n = php_cmark_node_media_fetch(object);

	if (Z_TYPE_P(member) != IS_STRING) {
		goto php_cmark_node_media_read_error;
	}

	if (EXPECTED(rtc)) {
		if (*rtc == cmark_node_get_url)
			return php_cmark_node_read_str(&n->h, cmark_node_get_url, &n->url);
		if (*rtc == cmark_node_get_title)
			return php_cmark_node_read_str(&n->h, cmark_node_get_title, &n->title);
	}

	if (zend_string_equals_literal(Z_STR_P(member), "url")) {
		if (rtc) 
			*rtc = cmark_node_get_url;
		return php_cmark_node_read_str(&n->h, cmark_node_get_url, &n->url);
	} else if (zend_string_equals_literal(Z_STR_P(member), "title")) {
		if (rtc) 
			*rtc = cmark_node_get_title;
		return php_cmark_node_read_str(&n->h, cmark_node_get_title, &n->title);
	}

php_cmark_node_media_read_error:
	return php_cmark_node_read(object, member, type, rtc, rv);
}

void php_cmark_node_media_write(zval *object, zval *member, zval *value, void **rtc) {
	php_cmark_node_media_t *n = php_cmark_node_media_fetch(object);

	if (EXPECTED(rtc)) {
		if (*rtc == cmark_node_set_url) {
			php_cmark_node_write_str(&n->h, cmark_node_set_url, value, &n->url);
			return;
		} else if (*rtc == cmark_node_set_title) {
			php_cmark_node_write_str(&n->h, cmark_node_set_title, value, &n->title);
			return;
		}	
	}

	if (Z_TYPE_P(member) == IS_STRING) {
		if (zend_string_equals_literal(Z_STR_P(member), "url")) {
			if (rtc)
				*rtc = cmark_node_set_url;
			php_cmark_node_write_str(&n->h, cmark_node_set_url, value, &n->url);
			return;
		} else if (zend_string_equals_literal(Z_STR_P(member), "title")) {
			if (rtc)
				*rtc = cmark_node_set_title;
			php_cmark_node_write_str(&n->h, cmark_node_set_title, value, &n->title);
			return;
		}
	}

	php_cmark_node_write(object, member, value, rtc);
}

int php_cmark_node_media_isset(zval *object, zval *member, int has_set_exists, void **rtc) {
	php_cmark_node_media_t *n = php_cmark_node_media_fetch(object);
	zval *zv = &EG(uninitialized_zval);

	if (Z_TYPE_P(member) != IS_STRING) {
		return 0;
	}

	if (has_set_exists == 2) {
		if (zend_string_equals_literal(Z_STR_P(member), "url")) {
			return 1;
		} else if (zend_string_equals_literal(Z_STR_P(member), "title")) {
			return 1;
		}
	}

	if (zend_string_equals_literal(Z_STR_P(member), "url")) {
		zv = php_cmark_node_read_str(&n->h, cmark_node_get_url, &n->url);
	} else if (zend_string_equals_literal(Z_STR_P(member), "title")) {
		zv = php_cmark_node_read_str(&n->h, cmark_node_get_title, &n->title);
	}

	if (Z_TYPE_P(zv) == IS_STRING) {
		return 1;
	}

	return php_cmark_node_isset(object, member, has_set_exists, rtc);
}

void php_cmark_node_media_unset(zval *object, zval *member, void **rtc) {
	php_cmark_node_media_t *n = php_cmark_node_media_fetch(object);

	if (Z_TYPE_P(member) != IS_STRING) {
		goto php_cmark_node_media_unset_error;
	}

	if (EXPECTED(rtc)) {
		if (*rtc == cmark_node_set_title) {
			php_cmark_node_write_str(&n->h, cmark_node_set_title, NULL, &n->title);
			return;
		} else if (*rtc == cmark_node_set_url) {
			php_cmark_node_write_str(&n->h, cmark_node_set_url, NULL, &n->url);
			return;
		}
	}

	if (zend_string_equals_literal(Z_STR_P(member), "title")) {
		if (rtc)	
			*rtc = cmark_node_set_title;
		php_cmark_node_write_str(&n->h, cmark_node_set_title, NULL, &n->title);
		return;
	} else if (zend_string_equals_literal(Z_STR_P(member), "url")) {
		if (rtc)	
			*rtc = cmark_node_set_url;
		php_cmark_node_write_str(&n->h, cmark_node_set_url, NULL, &n->url);
		return;
	}

php_cmark_node_media_unset_error:
	return php_cmark_node_unset(object, member, rtc);
}

void php_cmark_node_media_free(zend_object *zo) {
	php_cmark_node_media_t *n = 
		php_cmark_node_media_from(zo);

	if (!Z_ISUNDEF(n->url)) {
		zval_ptr_dtor(&n->url);
	}
	
	if (!Z_ISUNDEF(n->title)) {
		zval_ptr_dtor(&n->title);
	}

	php_cmark_node_free(zo);
}

static inline void php_cmark_node_media_construct_impl(zval *object, cmark_node_type type, zval *url, zval *title) {
	php_cmark_node_media_t *n = php_cmark_node_media_fetch(object);

	php_cmark_node_new(object, type);

	if (url) {
		php_cmark_node_write_str(&n->h, 
			(cmark_node_write_str) cmark_node_set_url, 
				url, &n->url);
	}

	if (title) {
		php_cmark_node_write_str(&n->h, 
			(cmark_node_write_str) cmark_node_set_title, 
				title, &n->title);
	}
}

static zend_function_entry php_cmark_node_media_methods[] = {
	PHP_FE_END
};

ZEND_BEGIN_ARG_INFO_EX(php_cmark_media_construct, 0, 0, 0)
	ZEND_ARG_INFO(0, url)
	ZEND_ARG_INFO(0, title)
ZEND_END_ARG_INFO()

PHP_METHOD(Link, __construct)
{
	zval *url = NULL;
	zval *title = NULL;

	if (php_cmark_parse_parameters("|zz", &url, &title) != SUCCESS ||
	    (url && Z_TYPE_P(url) != IS_STRING) ||
	    (title && Z_TYPE_P(title) != IS_STRING)) {
		php_cmark_wrong_parameters("url and or title expected");
		return;
	}

	php_cmark_node_media_construct_impl(getThis(), CMARK_NODE_LINK, url, title);
}

static zend_function_entry php_cmark_node_link_methods[] = {
	PHP_ME(Link, __construct, php_cmark_media_construct, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

PHP_METHOD(Image, __construct)
{
	zval *url = NULL;
	zval *title = NULL;

	if (php_cmark_parse_parameters("|zz", &url, &title) != SUCCESS ||
	    (url && Z_TYPE_P(url) != IS_STRING) ||
	    (title && Z_TYPE_P(title) != IS_STRING)) {
		php_cmark_wrong_parameters("url and or title expected");
		return;
	}

	php_cmark_node_media_construct_impl(getThis(), CMARK_NODE_IMAGE, url, title);
}

static zend_function_entry php_cmark_node_image_methods[] = {
	PHP_ME(Image, __construct, php_cmark_media_construct, ZEND_ACC_PUBLIC)
	PHP_FE_END
};


PHP_MINIT_FUNCTION(CommonMark_Node_Media) 
{
	zend_class_entry ce;

	INIT_NS_CLASS_ENTRY(ce, "CommonMark\\Node", "Link", php_cmark_node_link_methods);

	php_cmark_node_link_ce = zend_register_internal_class_ex(&ce, php_cmark_node_ce);
	php_cmark_node_link_ce->create_object = php_cmark_node_media_create;

#define php_cmark_node_link_property(n) \
	zend_declare_property_null(php_cmark_node_link_ce, ZEND_STRL(n), ZEND_ACC_PUBLIC)

	php_cmark_node_link_property("url");
	php_cmark_node_link_property("title");
#undef php_cmark_node_link_property

	INIT_NS_CLASS_ENTRY(ce, "CommonMark\\Node", "Image", php_cmark_node_image_methods);

	php_cmark_node_image_ce = zend_register_internal_class_ex(&ce, php_cmark_node_ce);
	php_cmark_node_image_ce->create_object = php_cmark_node_media_create;

#define php_cmark_node_image_property(n) \
	zend_declare_property_null(php_cmark_node_image_ce, ZEND_STRL(n), ZEND_ACC_PUBLIC)

	php_cmark_node_image_property("url");
	php_cmark_node_image_property("title");
#undef php_cmark_node_image_property

	memcpy(&php_cmark_node_media_handlers, &php_cmark_node_handlers, sizeof(zend_object_handlers));

	php_cmark_node_media_handlers.free_obj = php_cmark_node_media_free;
	php_cmark_node_media_handlers.read_property = php_cmark_node_media_read;
	php_cmark_node_media_handlers.write_property = php_cmark_node_media_write;
	php_cmark_node_media_handlers.has_property = php_cmark_node_media_isset;
	php_cmark_node_media_handlers.unset_property = php_cmark_node_media_unset;

	return SUCCESS;
}

PHP_RINIT_FUNCTION(CommonMark_Node_Media)
{
	php_cmark_node_link_ce->ce_flags |= ZEND_ACC_FINAL;
	php_cmark_node_image_ce->ce_flags |= ZEND_ACC_FINAL;

	return SUCCESS;
}
#endif
