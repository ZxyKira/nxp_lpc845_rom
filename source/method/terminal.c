/*-----------------------------------------------------------------------------------------
 *    File Name   :terminal.c
 *    Version     :V1.0.0
 *    Create Date :2020-10-13
 *    Modufy Date :2020-10-13
 *    Information :
 */
#include <stdint.h>
#include <string.h>

#include "fw_chip.h"
/*-----------------------------------------------------------------------------------------
 *    Parameter
 */

/*-----------------------------------------------------------------------------------------
 *    Extern Function/Variable
 */

/*-----------------------------------------------------------------------------------------
 *    Local Type/Structure
 */

/*-----------------------------------------------------------------------------------------
 *    Local Variable
 */
static fw_usart_xfer_t xfer;
static volatile bool uart_idle = true;

/*-----------------------------------------------------------------------------------------
 *    Variable
 */
char terminal_cache[256];
/*-----------------------------------------------------------------------------------------
 *    Inline Function
 */
 
/*-----------------------------------------------------------------------------------------
 *    Local Function
 */
static void terminal_callback(fw_usart_entity_t entity, void* userData){
	uart_idle = true;
}

/*-----------------------------------------------------------------------------------------
 *    Public Function
 */

void terminal_write(const char* str, uint32_t len){
	xfer.callback.foo = terminal_callback;
	xfer.data = (void*)str;
	xfer.len = len;
	uart_idle = false;
	fw_usart_api.send(0, &xfer);
	while(1){
		if(uart_idle)
			break;
	}
} 
/*-----------------------------------------------------------------------------------------
 *    End of file
 */
