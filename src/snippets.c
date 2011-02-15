/*
   +----------------------------------------------------------------------+
   | All rights reserved                                                  |
   |                                                                      |
   | Redistribution and use in source and binary forms, with or without   |
   | modification, are permitted provided that the following conditions   |
   | are met:                                                             |
   |                                                                      |
   | 1. Redistributions of source code must retain the above copyright    |
   |    notice, this list of conditions and the following disclaimer.     |
   | 2. Redistributions in binary form must reproduce the above copyright |
   |    notice, this list of conditions and the following disclaimer in   |
   |    the documentation and/or other materials provided with the        |
   |    distribution.                                                     |
   | 3. The names of the authors may not be used to endorse or promote    |
   |    products derived from this software without specific prior        |
   |    written permission.                                               |
   |                                                                      |
   | THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS  |
   | "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT    |
   | LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS    |
   | FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE       |
   | COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,  |
   | INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, |
   | BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;     |
   | LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER     |
   | CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT   |
   | LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN    | 
   | ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE      |
   | POSSIBILITY OF SUCH DAMAGE.                                          |
   +----------------------------------------------------------------------+
   | Authors: Ryusuke Sekiyama <rsky0711@gmail.com>                       |
   +----------------------------------------------------------------------+
*/

#include "php_snippets.h"

static PHP_MINIT_FUNCTION(snippets)
{
	if (intarray_setup(TSRMLS_C) == FAILURE) {
		return FAILURE;
	}
	return SUCCESS;
}

static PHP_MINFO_FUNCTION(snippets)
{
	php_info_print_table_start();
	php_info_print_table_row(2, "Version", SNIPPETS_VERSION);
	php_info_print_table_end();
}

static zend_function_entry snippets_functions[] = {
	PHP_FE(intarray_init, NULL)
	PHP_FE(intarray_add, NULL)
	PHP_FE(intarray_get, NULL)
	PHP_FE(intarray_set, NULL)
	PHP_FE(intarray_unset, NULL)
	PHP_FE(intarray_map, NULL)
	{ NULL, NULL, NULL }
};

static zend_module_entry snippets_module_entry = {
	STANDARD_MODULE_HEADER,
	"snippets",
	snippets_functions,
	PHP_MINIT(snippets),
	NULL,
	NULL,
	NULL,
	PHP_MINFO(snippets),
	SNIPPETS_VERSION,
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_CB
ZEND_GET_MODULE(snippets)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
