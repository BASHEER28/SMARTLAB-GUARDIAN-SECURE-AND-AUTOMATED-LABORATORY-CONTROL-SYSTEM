/*
 * ============================================================================
 * MODULE      : pdelay.c
 * PURPOSE     : Blocking software delay implementation
 * PROJECT     : SmartLab Guardian - LPC214x embedded application
 * DESCRIPTION :
 *   - Implements microsecond, millisecond and second delays using calibrated busy-wait loops.
 *   - These routines occupy the CPU while waiting and are not suitable as precise timing sources for production scheduling or safety-critical timing.
 * MAINTENANCE : Update this module documentation whenever its public behaviour,
 *               hardware mapping, timing assumptions or dependencies change.
 * NOTE        : Documentation-only annotation; existing program logic is retained.
 * ============================================================================
 */
//delay.c
#include "types.h"
void delay_us(u32 dlyus)
{
 for(dlyus*=12;dlyus>0;dlyus--);
}
void delay_ms(u32 dlyms)
{
for(;dlyms>0;dlyms--)
	delay_us(1000);
}
void delay_s(u32 dlys)
{
for(;dlys>0;dlys--)
	delay_ms(1000);
}



