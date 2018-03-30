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

typedef struct _php_cmark_node_visitor_t {
	zend_fcall_info        fci;
	zend_fcall_info_cache  fcc;
	zval                   result;
	zval                   visiting;

	zend_function          *enter;
	zend_function          *leave;
} php_cmark_node_visitor_t;

static zend_always_inline zend_bool php_cmark_node_visitor_shortcircuit(zend_function *fbc) {
	return	fbc->type == ZEND_USER_FUNCTION &&
		fbc->op_array.last == 2 &&
		fbc->op_array.opcodes[1].opcode == ZEND_RETURN &&
		fbc->op_array.opcodes[1].extended_value == -1;
}

static zend_always_inline void php_cmark_node_visitor_init(php_cmark_node_visitor_t *v, zval *visitor) 
{
	v->enter = (zend_function*)
			zend_hash_str_find_ptr(
				&Z_OBJCE_P(visitor)->function_table, ZEND_STRL("enter"));
	if (php_cmark_node_visitor_shortcircuit(v->enter)) {
		v->enter = NULL;
	}

	v->leave = (zend_function*)
			zend_hash_str_find_ptr(
				&Z_OBJCE_P(visitor)->function_table, ZEND_STRL("leave"));
	if (php_cmark_node_visitor_shortcircuit(v->leave)) {
		v->leave = NULL;
	}

	v->fci = empty_fcall_info;
	v->fci.size = sizeof(zend_fcall_info);
	v->fci.object = Z_OBJ_P(visitor);
	v->fci.param_count = 1;
	v->fci.params = &v->visiting;
	v->fci.retval = &v->result;

	v->fcc = empty_fcall_info_cache;
#if PHP_VERSION_ID < 70300
	v->fcc.initialized = 1;
#endif
	v->fcc.object = v->fci.object;

	ZVAL_UNDEF(&v->result);
}

static zend_always_inline void php_cmark_node_visitor_call(
		php_cmark_node_visitor_t *interface, cmark_event_type event, cmark_iter *iterator) {

	php_cmark_node_t *node = php_cmark_node_shadow(
		&interface->visiting, cmark_iter_get_node(iterator), 0);

	zend_call_function(&interface->fci, &interface->fcc);

	switch (Z_TYPE(interface->result)) {
		case IS_LONG:
			if (Z_LVAL(interface->result) > CMARK_EVENT_NONE) {
				cmark_iter_reset(iterator, 
					node->node, 
					(cmark_event_type) Z_LVAL(interface->result));			
			}
		break;

		case IS_OBJECT:
			if (instanceof_function(Z_OBJCE(interface->result), php_cmark_node_visitable_ce)) {
				cmark_iter_reset(iterator,
					php_cmark_node_fetch(
						&interface->result)->node, 
					event == CMARK_EVENT_ENTER ? 
						CMARK_EVENT_EXIT : CMARK_EVENT_ENTER);
			}

		default:
			if (Z_REFCOUNTED(interface->result)) {
				zval_ptr_dtor(&interface->result);
			}
	}

	ZVAL_UNDEF(&interface->result);
}

void php_cmark_node_accept_impl(php_cmark_node_t *root, zval *visitor) {
	php_cmark_node_visitor_t interface;
	cmark_event_type event;
	cmark_iter *iterator = cmark_iter_new(root->node);

	php_cmark_node_visitor_init(&interface, visitor);

	while ((event = cmark_iter_next(iterator)) != CMARK_EVENT_DONE) {
		interface.fcc.function_handler = 
			(event == CMARK_EVENT_ENTER) ?
				interface.enter :
				interface.leave;

		if (!interface.fcc.function_handler) {
			continue;
		}

		php_cmark_node_visitor_call(&interface, event, iterator);
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
