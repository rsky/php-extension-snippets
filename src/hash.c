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

static int _hash_element_dump(zval **entry TSRMLS_DC);

int hash_setup(TSRMLS_D)
{
	return SUCCESS;
}

PHP_FUNCTION(hash_foreach_print)
{
	HashTable *arr;
	HashPosition pos;
	zval **entry;
	zend_hash_key key;
	int type;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "h", &arr) == FAILURE) {
		return;
	}

	zend_hash_internal_pointer_reset_ex(arr, &pos);
	while (zend_hash_get_current_data_ex(arr, (void **)&entry, &pos) == SUCCESS) {
		type = zend_hash_get_current_key_ex(arr, &key.arKey, &key.nKeyLength, &key.h, 0, &pos);

		switch (type) {
			case HASH_KEY_IS_STRING:
				PHPWRITE(key.arKey, key.nKeyLength - 1);
				break;
			case HASH_KEY_IS_LONG:
				php_printf("%ld", (long)key.h);
				break;
			case HASH_KEY_NON_EXISTANT:
			default:
				return;
		}

		PHPWRITE(": ", 2);
		php_var_export(entry, 0 TSRMLS_CC);
		PHPWRITE(PHP_EOL, strlen(PHP_EOL));

		zend_hash_move_forward_ex(arr, &pos);
	}
}

PHP_FUNCTION(hash_apply_dump)
{
	HashTable *arr;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "h", &arr) == FAILURE) {
		return;
	}

	zend_hash_apply(arr, (apply_func_t)_hash_element_dump TSRMLS_CC);
}

static int _hash_element_dump(zval **entry TSRMLS_DC)
{
	php_var_dump(entry, 0 TSRMLS_CC);
	return ZEND_HASH_APPLY_KEEP;
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
