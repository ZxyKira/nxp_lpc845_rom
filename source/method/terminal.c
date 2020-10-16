/*-----------------------------------------------------------------------------------------
 *    File Name   :terminal.c
 *    Version     :V1.0.0
 *    Create Date :2020-10-13
 *    Modufy Date :2020-10-13
 *    Information :
 */
#include <stdint.h>
#include <string.h>

#include "terminal.h"
#include "fw_chip.h"
/*-----------------------------------------------------------------------------------------
 *    Parameter
 */
#define TERMINAL_DEFINE_MAX_OF_COMMAND 16
#define TERMINAL_DEFINE_INPUT_BUFFER_SIZE 256

void terminal_writeCh(char ch);
void terminal_write(const char* str, uint32_t len);
char terminal_readCh(void);
/*-----------------------------------------------------------------------------------------
 *    Extern Function/Variable
 */
extern terminal_command_t command_info_getCommand(void);
extern terminal_command_t command_reboot_getCommand(void);
extern terminal_command_t command_led_getCommand(void);
/*-----------------------------------------------------------------------------------------
 *    Local Type/Structure
 */

/*-----------------------------------------------------------------------------------------
 *    Local Variable
 */
static char terminal_text_unknownCommand[] = "unknown command: ";
static char terminal_text_outOfMemory[] = "Out of memory.\n";

static terminal_command_t terminal_command[TERMINAL_DEFINE_MAX_OF_COMMAND];
static char terminal_input_buffer[TERMINAL_DEFINE_INPUT_BUFFER_SIZE];
 
static fw_usart_xfer_t xferSend, xferRecv;
static volatile bool uart_send_idle = true;
static volatile bool uart_recv_idle = true;
/*-----------------------------------------------------------------------------------------
 *    Variable
 */
terminal_handle_t terminal_terminal_handle;
char terminal_cache[256];
/*-----------------------------------------------------------------------------------------
 *    Inline Function
 */
 
/*-----------------------------------------------------------------------------------------
 *    Local Function
 */
static void terminal_send_callback(fw_usart_entity_t entity, void* userData){
	uart_send_idle = true;
}

static void terminal_recv_callback(fw_usart_entity_t entity, void* userData){
	uart_recv_idle = true;
}

static char terminal_abstract_xfer_getCh(void){
	char result = terminal_readCh();
	return result;
}

static void terminal_abstract_xfer_putCh(char ch){
	terminal_writeCh(ch);
}

static void terminal_abstract_xfer_read(void* buffer, int len){
	int i;
	char* pbuf = (char*)buffer;
	for(i=0; i<len; i++){
		pbuf[i] = terminal_readCh();
	}
}

static void terminal_abstract_xfer_send(const void* data, int len){
	terminal_write(data, len);
}

static void terminal_abstract_xfer_sendString(const char* string){
	terminal_abstract_xfer_send(string, strlen(string));
}

static terminal_command_t* terminal_abstract_getCommands(void){
	return &terminal_command[0];
}

static uint32_t terminal_abstract_getCommandsSize(void){
	return TERMINAL_DEFINE_MAX_OF_COMMAND;
}

static const char* terminal_abstract_getPrefix(void){
	return "LPC845-ROM\0";
}

static void terminal_abstract_event_onUnknownCommand(terminal_xfer_api_t *pApi, int argc, char *argv[]){
	pApi->send(terminal_text_unknownCommand, strlen(terminal_text_unknownCommand));
	pApi->sendString(argv[0]);
}

static void terminal_abstract_event_onOutOfBuffer(terminal_xfer_api_t *pApi){
	pApi->send(terminal_text_outOfMemory, strlen(terminal_text_outOfMemory));
}

/*-----------------------------------------------------------------------------------------
 *    Public Function
 */

void terminal_writeCh(char ch){
	xferSend.callback.foo = terminal_send_callback;
	xferSend.data = &ch;
	xferSend.len = 1;
	uart_send_idle = false;
	fw_usart_api.send(0, &xferSend);
	while(1){
		if(uart_send_idle)
			break;
	}
} 

void terminal_write(const char* str, uint32_t len){
	xferSend.callback.foo = terminal_send_callback;
	xferSend.data = (void*)str;
	xferSend.len = len;
	uart_send_idle = false;
	fw_usart_api.send(0, &xferSend);
	while(1){
		if(uart_send_idle)
			break;
	}
}

char terminal_readCh(void){
	char result[2];
	xferRecv.callback.foo = terminal_recv_callback;
	xferRecv.data = (void*)&result;
	xferRecv.len = 1;
	uart_recv_idle = false;
	fw_usart_api.reciver(0, &xferRecv);
	while(1){
		if(uart_recv_idle)
			break;
	}
	return result[0];
}

void terminal_init0(void){
	const terminal_abstract_t abstract = {
		.Xfer = {
			.getCh = terminal_abstract_xfer_getCh,
			.putCh = terminal_abstract_xfer_putCh,
			.read = terminal_abstract_xfer_read,
			.send = terminal_abstract_xfer_send,
			.sendString = terminal_abstract_xfer_sendString
		},
		.getCommands = terminal_abstract_getCommands,
		.getCommandsSize = terminal_abstract_getCommandsSize,
		.getPrefix = terminal_abstract_getPrefix,
		.Event = {
			.onUnknownCommand = terminal_abstract_event_onUnknownCommand,
			.onOutOfBuffer = terminal_abstract_event_onOutOfBuffer
		}
	};
	
	terminal_api.init(&terminal_terminal_handle, &abstract);
	terminal_api.setBuffer(&terminal_terminal_handle, &terminal_input_buffer[0], TERMINAL_DEFINE_INPUT_BUFFER_SIZE);
	
	terminal_api.addCommand(&terminal_terminal_handle, command_info_getCommand());
	terminal_api.addCommand(&terminal_terminal_handle, command_reboot_getCommand());
	terminal_api.addCommand(&terminal_terminal_handle, command_led_getCommand());
}

void terminal_start0(void){
	terminal_api.start(&terminal_terminal_handle);
}

/*-----------------------------------------------------------------------------------------
 *    End of file
 */
