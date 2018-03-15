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
#ifndef PHP_CMARK_PARSER_H
#define PHP_CMARK_PARSER_H

extern zend_class_entry *php_cmark_parser_ce;

ZEND_BEGIN_ARG_INFO_EX(php_cmark_parse_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, content)
	ZEND_ARG_INFO(0, options)
ZEND_END_ARG_INFO()

extern PHP_FUNCTION(CommonMark_Parse);

extern PHP_MINIT_FUNCTION(CommonMark_Parser);
extern PHP_RINIT_FUNCTION(CommonMark_Parser);
#endif
