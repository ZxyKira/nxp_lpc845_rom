/*-----------------------------------------------------------------------------------------
 *    File Name   :loop.c
 *    Version     :V1.0.0
 *    Create Date :2020-10-12
 *    Modufy Date :2020-10-13
 *    Information :
 */
#include "fsl_power.h"
#include "fsl_clock.h"
#include "fsl_syscon.h"
#include "LPC845.h"
#include "stdio.h"

#include "fw_chip.h"


/*-----------------------------------------------------------------------------------------
 *    Parameter
 */
#define LOGOUT(fmt, ...) terminal_write(&terminal_cache[0], sprintf(&terminal_cache[0],fmt, ##__VA_ARGS__))

/*-----------------------------------------------------------------------------------------
 *    Extern Function/Variable
 */
extern fw_io_entity_t LED[8];
extern fw_spim_base_t FW_SPI0;
extern fw_spim_xfer_t FW_SPI0_XFER;
extern void terminal_write(void* str, uint32_t len);
extern char terminal_cache[256];
/*-----------------------------------------------------------------------------------------
 *    Local Type/Structure
 */

/*-----------------------------------------------------------------------------------------
 *    Local Variable
 */


/*-----------------------------------------------------------------------------------------
 *    inline Function
 */
 
/*-----------------------------------------------------------------------------------------
 *    Public Function
 */
void delay(uint32_t us){
	uint32_t i;
	for(i=0; i<=us; i++){
		__NOP();
		__NOP();
		__NOP();
		__NOP();
	}
}

void loop(){
	int i;
	LOGOUT("Start ROM\n");
	while(1){
		for(i=0; i<8; i++){
			fw_io_entity_api.setHigh(LED[i]);
			delay(1000000);
			fw_io_entity_api.setLow(LED[i]);
			delay(1000000);
		}
	}
}
/*-----------------------------------------------------------------------------------------
 *    End of file
 */
