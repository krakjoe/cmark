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
#ifndef PHP_CMARK_NODE_VISITOR_H
#define PHP_CMARK_NODE_VISITOR_H

extern zend_class_entry *php_cmark_node_visitor_ce;
extern zend_class_entry *php_cmark_node_visitable_ce;

extern PHP_MINIT_FUNCTION(CommonMark_Node_Visitor);
extern PHP_RINIT_FUNCTION(CommonMark_Node_Visitor);

extern void php_cmark_node_accept_impl(php_cmark_node_t *root, zval *visitor);
#endif
