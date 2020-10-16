/*-----------------------------------------------------------------------------------------
 *    File Name   :command_led.c
 *    Version     :V1.0.0
 *    Create Date :2020-10-15
 *    Modufy Date :2020-10-15
 *    ledrmation :
 */
#include "terminal_entity.h"
#include <string.h>
#include <stdlib.h>

#include "fw_chip.h"
/*-----------------------------------------------------------------------------------------
 *    Parameter
 */

/*-----------------------------------------------------------------------------------------
 *    Extern Function/Variable
 */
extern void BootJump(uint32_t *Address);
extern fw_io_entity_t LED[8];
/*-----------------------------------------------------------------------------------------
 *    Local Type/Structure
 */

/*-----------------------------------------------------------------------------------------
 *    Local Variable
 */
const char command_led_text_cmd[] = "led";
/*-----------------------------------------------------------------------------------------
 *    Variable
 */

/*-----------------------------------------------------------------------------------------
 *    Inline Function
 */
 
/*-----------------------------------------------------------------------------------------
 *    Local Function
 */


static bool command_led_handle(terminal_xfer_api_t *pApi, void* userData, int argc, char **argv){
	if(argc >= 3){
		int i = atoi(argv[1]);
		if(i>=8){
			pApi->sendString("out of led pin range <0~7>");
		}else{
			if(strcmp(argv[2], "high") == 0){
				fw_io_entity_api.setHigh(LED[i]);
				pApi->sendString("set led high : ");
				pApi->sendString(argv[1]);
			}
			else if(strcmp(argv[2], "low") == 0){
				fw_io_entity_api.setLow(LED[i]);
				pApi->sendString("set led low : ");
				pApi->sendString(argv[1]);
			}
			else{
				pApi->sendString("unknown param: ");
				pApi->sendString(argv[2]);
			}
			
		}
	}else{
		pApi->sendString("unknown param");
	}
		
	return true;
}

/*-----------------------------------------------------------------------------------------
 *    Public Function
 */
terminal_command_t command_led_getCommand(){
	terminal_command_t command = {
		.command = command_led_text_cmd,
		.userData = (void*)0x00000000,
		.handle = command_led_handle,
	};	
	return command;
}

/*-----------------------------------------------------------------------------------------
 *    End of file
 */

