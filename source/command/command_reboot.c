/*-----------------------------------------------------------------------------------------
 *    File Name   :command_reboot.c
 *    Version     :V1.0.0
 *    Create Date :2020-10-15
 *    Modufy Date :2020-10-15
 *    rebootrmation :
 */
#include "terminal_entity.h"
#include <string.h>

/*-----------------------------------------------------------------------------------------
 *    Parameter
 */

/*-----------------------------------------------------------------------------------------
 *    Extern Function/Variable
 */
extern void BootJump(uint32_t *Address);
/*-----------------------------------------------------------------------------------------
 *    Local Type/Structure
 */

/*-----------------------------------------------------------------------------------------
 *    Local Variable
 */
const char command_reboot_text_cmd[] = "reboot";
/*-----------------------------------------------------------------------------------------
 *    Variable
 */

/*-----------------------------------------------------------------------------------------
 *    Inline Function
 */
 
/*-----------------------------------------------------------------------------------------
 *    Local Function
 */
static void command_reboot_bootloader(terminal_xfer_api_t *pApi){
	pApi->sendString("reboot to bootloader");
	pApi->putCh('\n');
	BootJump((uint32_t*)0x00000000);
} 

static void command_reboot_rom(terminal_xfer_api_t *pApi){
	pApi->sendString("reboot to rom");
	pApi->putCh('\n');
	BootJump((uint32_t*)0x00008000);
} 

static bool command_reboot_handle(terminal_xfer_api_t *pApi, void* userData, int argc, char **argv){
	if(argc == 1)
		command_reboot_bootloader(pApi);
	
	else{
		if(strcmp(argv[1], "bootloader") == 0)
			command_reboot_bootloader(pApi);
		else if(strcmp(argv[1], "rom") == 0)
			command_reboot_rom(pApi);
		else{
			pApi->sendString("unknown param :");
			pApi->sendString(argv[1]);
		}
			
	}
		
	return true;
}

/*-----------------------------------------------------------------------------------------
 *    Public Function
 */
terminal_command_t command_reboot_getCommand(){
	terminal_command_t command = {
		.command = command_reboot_text_cmd,
		.userData = (void*)0x00000000,
		.handle = command_reboot_handle,
	};	
	return command;
}

/*-----------------------------------------------------------------------------------------
 *    End of file
 */

