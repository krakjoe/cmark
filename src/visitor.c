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
#ifndef PHP_CMARK_NODE_VISITOR
#define PHP_CMARK_NODE_VISITOR

#include <php.h>

#include <src/common.h>
#include <src/node.h>

zend_class_entry *php_cmark_node_visitor_ce;
zend_class_entry *php_cmark_node_visitable_ce;

void php_cmark_node_accept_impl(php_cmark_node_t *root, zval *visitor) {
	cmark_event_type event;	
	cmark_iter *iterator = cmark_iter_new(root->node);

	while ((event = cmark_iter_next(iterator)) != CMARK_EVENT_DONE) {
		zval visiting;
		zval result;
		zend_fcall_info fci = empty_fcall_info;
		zend_fcall_info_cache fcc = empty_fcall_info_cache;

		php_cmark_node_t *node = 
			php_cmark_node_shadow(
				&visiting, cmark_iter_get_node(iterator), 0);

		ZVAL_NULL(&result);

		fci.size = sizeof(zend_fcall_info);
		fci.retval = &result;
		fci.object = Z_OBJ_P(visitor);

#if PHP_VERSION_ID < 70300
		fcc.initialized = 1;
#endif
		fcc.object = fci.object;

		zend_fcall_info_argn(&fci, 1, &visiting);

		switch (event) {
			case CMARK_EVENT_ENTER:
				fcc.function_handler = zend_hash_str_find_ptr(
					&Z_OBJCE_P(visitor)->function_table, ZEND_STRL("enter"));
			break;

			case CMARK_EVENT_EXIT:
				fcc.function_handler = zend_hash_str_find_ptr(
					&Z_OBJCE_P(visitor)->function_table, ZEND_STRL("leave"));
			break;
		}

		zend_call_function(&fci, &fcc);

		if (Z_TYPE(result) == IS_LONG && Z_LVAL(result) > CMARK_EVENT_NONE) {
			cmark_iter_reset(iterator, 
				node->node, (cmark_event_type) Z_LVAL(result));
		}

		if (Z_TYPE(result) == IS_OBJECT && instanceof_function(Z_OBJCE(result), php_cmark_node_visitable_ce)) {
			cmark_iter_reset(iterator,
				php_cmark_node_fetch(&result)->node, event);
		}

		if (Z_REFCOUNTED(result)) {
			zval_ptr_dtor(&result);
		}

		zend_fcall_info_args_clear(&fci, 1);
	}

	cmark_iter_free(iterator);
}

ZEND_BEGIN_ARG_INFO_EX(php_cmark_node_visitor_arginfo, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, node, CommonMark\\Interfaces\\IVisitable, 0)
ZEND_END_ARG_INFO()

static zend_function_entry php_cmark_node_visitor_methods[] = {
	PHP_ABSTRACT_ME(Visitor, enter, php_cmark_node_visitor_arginfo)
	PHP_ABSTRACT_ME(Visitor, leave, php_cmark_node_visitor_arginfo)
	PHP_FE_END
};

ZEND_BEGIN_ARG_INFO_EX(php_cmark_node_visitable_arginfo, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, visitor, CommonMark\\Interfaces\\IVisitor, 0)
ZEND_END_ARG_INFO()

static zend_function_entry php_cmark_node_visitable_methods[] = {
	PHP_ABSTRACT_ME(Visitable, accept, php_cmark_node_visitable_arginfo)
	PHP_FE_END
};

PHP_MINIT_FUNCTION(CommonMark_Node_Visitor) 
{
	zend_class_entry ce;

	INIT_NS_CLASS_ENTRY(ce, "CommonMark\\Interfaces", "IVisitor", php_cmark_node_visitor_methods);

	php_cmark_node_visitor_ce = zend_register_internal_interface(&ce);

	zend_declare_class_constant_long(php_cmark_node_visitor_ce, ZEND_STRL("Done"), CMARK_EVENT_DONE);
	zend_declare_class_constant_long(php_cmark_node_visitor_ce, ZEND_STRL("Enter"), CMARK_EVENT_ENTER);
	zend_declare_class_constant_long(php_cmark_node_visitor_ce, ZEND_STRL("Leave"), CMARK_EVENT_EXIT);

	INIT_NS_CLASS_ENTRY(ce, "CommonMark\\Interfaces", "IVisitable", php_cmark_node_visitable_methods);

	php_cmark_node_visitable_ce = zend_register_internal_interface(&ce);

	return SUCCESS;
}

PHP_RINIT_FUNCTION(CommonMark_Node_Visitor)
{
	php_cmark_node_visitor_ce->ce_flags |= ZEND_ACC_FINAL;
	php_cmark_node_visitable_ce->ce_flags |= ZEND_ACC_FINAL;

	return SUCCESS;
}
#endif
