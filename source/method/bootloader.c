/*-----------------------------------------------------------------------------------------
 *    File Name   :bootloader.c
 *    Version     :V1.0.0
 *    Create Date :2020-10-13
 *    Modufy Date :2020-10-13
 *    Information :
 */
#include <stdint.h>
#include "LPC845.h"

/*-----------------------------------------------------------------------------------------
 *    Parameter
 */

/*-----------------------------------------------------------------------------------------
 *    Extern Function/Variable
 */
extern void delay(uint32_t us);
/*-----------------------------------------------------------------------------------------
 *    Local Type/Structure
 */

/*-----------------------------------------------------------------------------------------
 *    Local Variable
 */

/*-----------------------------------------------------------------------------------------
 *    Variable
 */

/*-----------------------------------------------------------------------------------------
 *    Inline Function
 */
 
/*-----------------------------------------------------------------------------------------
 *    Local Function
 */
__ASM __attribute__( ( noreturn ) ) void BootJumpASM( uint32_t SP, uint32_t RH )
{
  MSR      MSP,r0
  BX       r1
}
/*-----------------------------------------------------------------------------------------
 *    Public Function
 */
void BootJump( uint32_t *Address ){
	delay(200);
	NVIC->ICER[0] = 0xFFFFFFFF;
	NVIC->ICPR[0] = 0xFFFFFFFF;
	SysTick->CTRL = 0;
	SCB->ICSR |= SCB_ICSR_PENDSTCLR_Msk;
	if( CONTROL_SPSEL_Msk & __get_CONTROL( ) )
	{  /* MSP is not active */
		__set_MSP( __get_PSP( ) ) ;
		__set_CONTROL( __get_CONTROL( ) & ~CONTROL_SPSEL_Msk ) ;
	}
	SCB->VTOR = ( uint32_t )Address ;
	
	delay(200);
	BootJumpASM( Address[ 0 ], Address[ 1 ] ) ;
}


/*-----------------------------------------------------------------------------------------
 *    End of file
 */
