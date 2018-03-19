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
#ifndef PHP_CMARK_RENDER_H
#define PHP_CMARK_RENDER_H

ZEND_BEGIN_ARG_INFO_EX(php_cmark_render_without_width, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, node, CommonMark\\Node, 0)
	ZEND_ARG_INFO(0, options)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(php_cmark_render_with_width, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, node, CommonMark\\Node, 0)
	ZEND_ARG_INFO(0, options)
	ZEND_ARG_INFO(0, width)
ZEND_END_ARG_INFO()

extern PHP_FUNCTION(CommonMark_Render);
extern PHP_FUNCTION(CommonMark_Render_XML);
extern PHP_FUNCTION(CommonMark_Render_HTML);
extern PHP_FUNCTION(CommonMark_Render_Man);
extern PHP_FUNCTION(CommonMark_Render_Latex);
extern PHP_FUNCTION(CommonMark_Render_Visitor);

extern PHP_MINIT_FUNCTION(CommonMark_Render);
extern PHP_RINIT_FUNCTION(CommonMark_Render);
#endif
