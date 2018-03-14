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
