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
#ifndef PHP_CMARK_CALL
#define PHP_CMARK_CALL

#include <php.h>

#include <src/common.h>
#include <src/node.h>
#include <src/cql.h>
#include <src/call.h>

typedef struct _php_cmark_call_info_t {
	zval root;
	zend_fcall_info fci;
	zend_fcall_info_cache fcc;
} php_cmark_call_info_t;

zend_class_entry *php_cmark_call_ce;
zend_object_handlers php_cmark_call_handlers;

static inline zend_object *php_cmark_call_create(zend_class_entry *type) {
	php_cmark_call_t *c = 
		(php_cmark_call_t*) ecalloc(1, 
			sizeof(php_cmark_call_t) + zend_object_properties_size(type));

	zend_object_std_init(&c->std, type);

	object_properties_init(&c->std, type);

	c->std.handlers = &php_cmark_call_handlers;

	return &c->std;
}

static inline void php_cmark_call_free(zend_object *zo) {
	php_cmark_call_t *c = php_cmark_call_from(zo);

	cql_free(&c->function);

	zend_object_std_dtor(zo);
}

static inline zend_object* php_cmark_call_clone(zval *zv) {
	zend_class_entry *type = Z_OBJCE_P(zv);
	php_cmark_call_t *src = php_cmark_call_fetch(zv);
	php_cmark_call_t *dst = (php_cmark_call_t*) 
		ecalloc(1, sizeof(php_cmark_call_t) + 
			zend_object_properties_size(type));

	zend_object_std_init(&dst->std, type);
	
	object_properties_init(&dst->std, type);

	dst->std.handlers = &php_cmark_call_handlers;

	zend_objects_clone_members(&dst->std, &src->std);

	if (!cql_clone(&src->function, &dst->function)) {
		/* do something */
		memset(&dst->function, 0, sizeof(cql_function_t));
	}

	return &dst->std;
}

PHP_METHOD(CQL, __construct)
{
	php_cmark_call_t *call = php_cmark_call_fetch(getThis());
	zval *cql = NULL;
	unsigned char *cursor = NULL;

	ZEND_BEGIN_PARAMS(1, 1)
		Z_PARAM_ZVAL(cql)
	ZEND_END_PARAMS();

	php_cmark_assert_type(cql, IS_STRING, 0, "cql expected to be string");

	if (!cql_compile(&call->function, Z_STRVAL_P(cql), Z_STRLEN_P(cql), &cursor)) {
		php_cmark_throw("failed to compile call near character %ld \"%s\"", 
				(cursor - (unsigned char*) Z_STRVAL_P(cql)) + 1, cursor);
	}
}

static inline int php_cmark_cql_enter_function(cmark_node *node, php_cmark_call_info_t *call) {
	php_cmark_node_t *n;	
	zval arg;
	zval rv;
	int retval = 1;

	object_init_ex(&arg, php_cmark_node_class(node));

	n = php_cmark_node_fetch(&arg);
	n->node = node;
	n->owned = 0;

	ZVAL_NULL(&rv);

	call->fci.retval = &rv;

	zend_fcall_info_argn(&call->fci, 2, &call->root, &arg);

	if (zend_call_function(&call->fci, &call->fcc) != SUCCESS) {
		return -1;
	}

	if (Z_TYPE(rv) != IS_NULL) {
		retval = zend_is_true(&rv);

		if (Z_REFCOUNTED(rv)) {
			zval_ptr_dtor(&rv);
		}
	}

	zend_fcall_info_args_clear(&call->fci, 1);

	zval_ptr_dtor(&arg);

	return retval;
}

ZEND_BEGIN_ARG_INFO_EX(php_cmark_call_invoke, 0, 0, 2)
	ZEND_ARG_OBJ_INFO(0, node, CommonMark\\Node, 0)
	ZEND_ARG_CALLABLE_INFO(0, enter, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(CQL, __invoke)
{
	php_cmark_call_t *c = php_cmark_call_fetch(getThis());
	zval *root = NULL;
	php_cmark_call_info_t info;

	ZEND_BEGIN_PARAMS(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(root, php_cmark_node_ce)
		Z_PARAM_FUNC(info.fci, info.fcc)
	ZEND_END_PARAMS();

	ZVAL_COPY_VALUE(&info.root, root);

	RETURN_BOOL(cql_call(&c->function, 
		php_cmark_node_fetch(root)->node, 
		(cql_enter_function_t*) 
			php_cmark_cql_enter_function, &info) == SUCCESS);
}

PHP_METHOD(CQL, print)
{
	php_cmark_call_t *c = php_cmark_call_fetch(getThis());

	ZEND_BEGIN_PARAMS(0, 0)
	ZEND_END_PARAMS();

	cql_print(&c->function, php_printf);
}

static zend_function_entry php_cmark_call_methods[] = {
	PHP_ME(CQL, __construct, php_cmark_no_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(CQL, __invoke,    php_cmark_call_invoke, ZEND_ACC_PUBLIC)
	PHP_ME(CQL, print,       php_cmark_no_arginfo, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

PHP_MINIT_FUNCTION(CommonMark_CQL) 
{
	zend_class_entry ce;

	INIT_NS_CLASS_ENTRY(ce, "CommonMark", "CQL", php_cmark_call_methods);

	php_cmark_call_ce = zend_register_internal_class(&ce);
	php_cmark_call_ce->create_object = php_cmark_call_create;

	memcpy(&php_cmark_call_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

	php_cmark_call_handlers.offset = XtOffsetOf(php_cmark_call_t, std);
	php_cmark_call_handlers.free_obj = php_cmark_call_free;
	php_cmark_call_handlers.clone_obj = php_cmark_call_clone;

	return SUCCESS;
}

PHP_RINIT_FUNCTION(CommonMark_CQL)
{
	return SUCCESS;
}
#endif
