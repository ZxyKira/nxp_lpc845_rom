/*-----------------------------------------------------------------------------------------
 *    File Name   :command_info.c
 *    Version     :V1.0.0
 *    Create Date :2020-10-15
 *    Modufy Date :2020-10-15
 *    Information :
 */
#include "terminal_entity.h"

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
const char command_info_text_cmd[] = "info";
/*-----------------------------------------------------------------------------------------
 *    Variable
 */

/*-----------------------------------------------------------------------------------------
 *    Inline Function
 */
 
/*-----------------------------------------------------------------------------------------
 *    Local Function
 */
static bool command_info_handle(terminal_xfer_api_t *pApi, void* userData, int argc, char **argv){
	pApi->sendString("rom type = ROM 1 test\n");
	pApi->sendString("build version = 1.0.0\n");
	pApi->sendString("build date = 2020/10/16 11:26");
	return true;
}

/*-----------------------------------------------------------------------------------------
 *    Public Function
 */
terminal_command_t command_info_getCommand(){
	terminal_command_t command = {
		.command = command_info_text_cmd,
		.userData = (void*)0x00000000,
		.handle = command_info_handle,
	};	
	return command;
}

/*-----------------------------------------------------------------------------------------
 *    End of file
 */

