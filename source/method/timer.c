/*-----------------------------------------------------------------------------------------
 *    File Name   :timer.c
 *    Version     :V1.0.0
 *    Create Date :2020-10-15
 *    Modufy Date :2020-10-15
 *    Information :
 */
#include <stdint.h>
#include "fsl_mrt.h"

#include "fw_chip.h"

/*-----------------------------------------------------------------------------------------
 *    Parameter
 */
 
/*-----------------------------------------------------------------------------------------
 *    Extern Function/Variable
 */
extern fw_io_entity_t LED[8];
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
void timer_init(void){
	uint32_t mrt_clock = CLOCK_GetFreq(kCLOCK_CoreSysClk);
	mrt_config_t mrtConfig;
	MRT_GetDefaultConfig(&mrtConfig);
	MRT_Init(MRT0, &mrtConfig);
	MRT_SetupChannelMode(MRT0, kMRT_Channel_0, kMRT_RepeatMode);
	MRT_EnableInterrupts(MRT0, kMRT_Channel_0, kMRT_TimerInterruptEnable);
	EnableIRQ(MRT0_IRQn);
	MRT_StartTimer(MRT0, kMRT_Channel_0, USEC_TO_COUNT(250000U, mrt_clock));
} 


void MRT0_IRQHandler(void){
	MRT_ClearStatusFlags(MRT0, kMRT_Channel_0, kMRT_TimerInterruptFlag);
	int i;
	for(i=0; i<8; i++){
		fw_io_entity_api.setToggle(LED[i]);
	}
}

/*-----------------------------------------------------------------------------------------
 *    End of file
 */
