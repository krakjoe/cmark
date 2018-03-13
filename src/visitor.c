#ifndef PHP_CMARK_NODE_VISITOR
#define PHP_CMARK_NODE_VISITOR

#include <php.h>

#include <src/common.h>
#include <src/node.h>

zend_class_entry *php_cmark_node_visitor_ce;
zend_class_entry *php_cmark_node_visitable_ce;

ZEND_BEGIN_ARG_INFO_EX(php_cmark_node_visitor_arginfo, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, node, CommonMark\\Node, 0)
ZEND_END_ARG_INFO()

static zend_function_entry php_cmark_node_visitor_methods[] = {
	PHP_ABSTRACT_ME(Visitor, enter, php_cmark_node_visitor_arginfo)
	PHP_ABSTRACT_ME(Visitor, leave, php_cmark_node_visitor_arginfo)
	PHP_FE_END
};

ZEND_BEGIN_ARG_INFO_EX(php_cmark_node_visitable_arginfo, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, visitor, CommonMark\\Node\\Visitor, 0)
ZEND_END_ARG_INFO()

static zend_function_entry php_cmark_node_visitable_methods[] = {
	PHP_ABSTRACT_ME(Visitable, accept, php_cmark_node_visitable_arginfo)
	PHP_FE_END
};

PHP_MINIT_FUNCTION(CommonMark_Node_Visitor) 
{
	zend_class_entry ce;

	INIT_NS_CLASS_ENTRY(ce, "CommonMark\\Node", "Visitor", php_cmark_node_visitor_methods);

	php_cmark_node_visitor_ce = zend_register_internal_interface(&ce);

	REGISTER_NS_LONG_CONSTANT("CommonMark\\Node\\Visitor", "Done",  CMARK_EVENT_DONE,  CONST_PERSISTENT);
	REGISTER_NS_LONG_CONSTANT("CommonMark\\Node\\Visitor", "Enter", CMARK_EVENT_ENTER, CONST_PERSISTENT);
	REGISTER_NS_LONG_CONSTANT("CommonMark\\Node\\Visitor", "Leave", CMARK_EVENT_EXIT,  CONST_PERSISTENT);

	INIT_NS_CLASS_ENTRY(ce, "CommonMark\\Node", "Visitable", php_cmark_node_visitable_methods);

	php_cmark_node_visitable_ce = zend_register_internal_interface(&ce);

	return SUCCESS;
}

PHP_RINIT_FUNCTION(CommonMark_Node_Visitor)
{
	php_cmark_node_visitor_ce->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS;
	php_cmark_node_visitable_ce->ce_flags |= ZEND_ACC_FINAL;

	return SUCCESS;
}
#endif
