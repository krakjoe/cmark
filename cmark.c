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

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <php.h>
#include <ext/standard/info.h>

#include "php_cmark.h"

#include <src/node.h>
#include <src/text.h>
#include <src/document.h>
#include <src/quote.h>
#include <src/list.h>
#include <src/item.h>
#include <src/block.h>
#include <src/paragraph.h>
#include <src/heading.h>
#include <src/break.h>
#include <src/code.h>
#include <src/inline.h>
#include <src/media.h>

#include <src/render.h>
#include <src/parse.h>

/* {{{ */
PHP_MINIT_FUNCTION(cmark)
{
	PHP_MINIT(CommonMark_Node)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_MINIT(CommonMark_Node_Text)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_MINIT(CommonMark_Node_Document)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_MINIT(CommonMark_Node_BlockQuote)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_MINIT(CommonMark_Node_List)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_MINIT(CommonMark_Node_Item)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_MINIT(CommonMark_Node_Block)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_MINIT(CommonMark_Node_Paragraph)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_MINIT(CommonMark_Node_Heading)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_MINIT(CommonMark_Node_Break)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_MINIT(CommonMark_Node_Code)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_MINIT(CommonMark_Node_Inline)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_MINIT(CommonMark_Node_Media)(INIT_FUNC_ARGS_PASSTHRU);

	PHP_MINIT(CommonMark_Render)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_MINIT(CommonMark_Parser)(INIT_FUNC_ARGS_PASSTHRU);

	REGISTER_NS_LONG_CONSTANT("CommonMark", "Version", cmark_version(), CONST_CS|CONST_PERSISTENT);
	REGISTER_NS_STRING_CONSTANT("CommonMark", "VersionString", (char*) cmark_version_string(), CONST_CS|CONST_PERSISTENT);

	return SUCCESS;
} /* }}} */

/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(cmark)
{
#if defined(ZTS) && defined(COMPILE_DL_CMARK)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	PHP_RINIT(CommonMark_Node)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_RINIT(CommonMark_Node_Text)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_RINIT(CommonMark_Node_Document)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_RINIT(CommonMark_Node_BlockQuote)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_RINIT(CommonMark_Node_List)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_RINIT(CommonMark_Node_Item)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_RINIT(CommonMark_Node_Block)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_RINIT(CommonMark_Node_Paragraph)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_RINIT(CommonMark_Node_Heading)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_RINIT(CommonMark_Node_Break)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_RINIT(CommonMark_Node_Code)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_RINIT(CommonMark_Node_Inline)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_RINIT(CommonMark_Node_Media)(INIT_FUNC_ARGS_PASSTHRU);

	PHP_RINIT(CommonMark_Render)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_RINIT(CommonMark_Parser)(INIT_FUNC_ARGS_PASSTHRU);

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(cmark)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "cmark support", "enabled");
	php_info_print_table_end();
}
/* }}} */

/* {{{ cmark_functions[]
 */
static const zend_function_entry cmark_functions[] = {
	ZEND_NS_NAMED_FE("CommonMark\\Render", XML,        zif_Render_XML,         php_cmark_render_without_width)
	ZEND_NS_NAMED_FE("CommonMark\\Render", HTML,       zif_Render_HTML,        php_cmark_render_without_width)
	ZEND_NS_NAMED_FE("CommonMark\\Render", Man,        zif_Render_Man,         php_cmark_render_with_width)
	ZEND_NS_NAMED_FE("CommonMark\\Render", CommonMark, zif_Render_CommonMark,  php_cmark_render_with_width)
	ZEND_NS_NAMED_FE("CommonMark\\Render", Latex,      zif_Render_Latex,       php_cmark_render_with_width)
	PHP_FE_END
};
/* }}} */

/* {{{ cmark_module_entry
 */
zend_module_entry cmark_module_entry = {
	STANDARD_MODULE_HEADER,
	"cmark",					/* Extension name */
	cmark_functions,			/* zend_function_entry */
	PHP_MINIT(cmark),							/* PHP_MINIT - Module initialization */
	NULL,							/* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(cmark),			/* PHP_RINIT - Request initialization */
	NULL,							/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(cmark),			/* PHP_MINFO - Module info */
	PHP_CMARK_VERSION,		/* Version */
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_CMARK
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(cmark)
#endif
