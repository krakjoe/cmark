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

zend_class_entry *php_cmark_node_media_ce;
zend_class_entry *php_cmark_node_link_ce;
zend_class_entry *php_cmark_node_image_ce;

ZEND_BEGIN_ARG_INFO_EX(php_cmark_node_media_set_url, 0, 0, 1)
	ZEND_ARG_INFO(0, url)
ZEND_END_ARG_INFO()

PHP_METHOD(Media, setURL)
{
	php_cmark_node_t *n = php_cmark_node_fetch(getThis());
	zend_string *url;

	if (php_cmark_parse_parameters("S", &url) != SUCCESS) {
		php_cmark_wrong_parameters("url expected");
		return;
	}

	cmark_node_set_url(n->node, ZSTR_VAL(url));

	php_cmark_chain();
}

PHP_METHOD(Media, getURL)
{
	php_cmark_node_t *n = php_cmark_node_fetch(getThis());
	const char *c;

	php_cmark_no_parameters();

	c = cmark_node_get_url(n->node);

	if (!c || !c[0]) {
		return;
	}

	RETURN_STRING(c);
}

ZEND_BEGIN_ARG_INFO_EX(php_cmark_node_media_set_title, 0, 0, 1)
	ZEND_ARG_INFO(0, title)
ZEND_END_ARG_INFO()

PHP_METHOD(Media, setTitle)
{
	php_cmark_node_t *n = php_cmark_node_fetch(getThis());
	zend_string *url;

	if (php_cmark_parse_parameters("S", &url) != SUCCESS) {
		php_cmark_wrong_parameters("url expected");
		return;
	}

	cmark_node_set_title(n->node, ZSTR_VAL(url));

	php_cmark_chain();
}

PHP_METHOD(Media, getTitle)
{
	php_cmark_node_t *n = php_cmark_node_fetch(getThis());
	const char *c;

	php_cmark_no_parameters();

	c = cmark_node_get_title(n->node);

	if (!c || !c[0]) {
		return;
	}

	RETURN_STRING(c);
}

static zend_function_entry php_cmark_node_media_methods[] = {
	PHP_ME(Media, setURL, php_cmark_node_media_set_url, ZEND_ACC_PUBLIC)
	PHP_ME(Media, getURL, php_cmark_no_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(Media, setTitle, php_cmark_node_media_set_title, ZEND_ACC_PUBLIC)
	PHP_ME(Media, getTitle, php_cmark_no_arginfo, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

ZEND_BEGIN_ARG_INFO_EX(php_cmark_media_construct, 0, 0, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(Link, __construct)
{
	php_cmark_no_parameters();

	php_cmark_node_new(getThis(), CMARK_NODE_LINK);
}

static zend_function_entry php_cmark_node_link_methods[] = {
	PHP_ME(Link, __construct, php_cmark_media_construct, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

PHP_METHOD(Image, __construct)
{
	php_cmark_no_parameters();

	php_cmark_node_new(getThis(), CMARK_NODE_IMAGE);
}

static zend_function_entry php_cmark_node_image_methods[] = {
	PHP_ME(Image, __construct, php_cmark_media_construct, ZEND_ACC_PUBLIC)
	PHP_FE_END
};


PHP_MINIT_FUNCTION(CommonMark_Node_Media) 
{
	zend_class_entry ce;

	INIT_NS_CLASS_ENTRY(ce, "CommonMark\\Node", "Media", php_cmark_node_media_methods);

	php_cmark_node_media_ce = zend_register_internal_class_ex(&ce, php_cmark_node_ce);

	INIT_NS_CLASS_ENTRY(ce, "CommonMark\\Node\\Media", "Link", php_cmark_node_link_methods);

	php_cmark_node_link_ce = zend_register_internal_class_ex(&ce, php_cmark_node_media_ce);

	INIT_NS_CLASS_ENTRY(ce, "CommonMark\\Node\\Media", "Image", php_cmark_node_image_methods);

	php_cmark_node_image_ce = zend_register_internal_class_ex(&ce, php_cmark_node_media_ce);

	return SUCCESS;
}

PHP_RINIT_FUNCTION(CommonMark_Node_Media)
{
	php_cmark_node_media_ce->ce_flags |= ZEND_ACC_FINAL|ZEND_ACC_EXPLICIT_ABSTRACT_CLASS;
	php_cmark_node_link_ce->ce_flags |= ZEND_ACC_FINAL;
	php_cmark_node_image_ce->ce_flags |= ZEND_ACC_FINAL;

	return SUCCESS;
}
#endif
