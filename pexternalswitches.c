/*
 * ============================================================================
 * MODULE      : pexternalswitches.c
 * PURPOSE     : External interrupt and emergency handling
 * PROJECT     : SmartLab Guardian - LPC214x embedded application
 * DESCRIPTION :
 *   - Configures EINT0/EINT3 routing through PINSEL and the Vectored Interrupt Controller.
 *   - The interrupt service routines acknowledge the corresponding external interrupt and set application event flags.
 *   - The emergency handler performs the visible alert and output shutdown sequence in foreground context.
 * MAINTENANCE : Update this module documentation whenever its public behaviour,
 *               hardware mapping, timing assumptions or dependencies change.
 * NOTE        : Documentation-only annotation; existing program logic is retained.
 * ============================================================================
 */
//INT.c

#include <LPC214x.h>
#include "headerfiles.h"
#include "types.h"
#include "externalswitches.h"
#include "LCD_defines.h"
extern volatile int flag;
extern volatile int flag1;
void EINT0_ISR(void)__irq
{  flag=1;
	//Menu();
	EXTINT =1<<0;
	VICVectAddr = 0;
}

void Init_Interrupt(void)
{ //for rtc
	PINSEL0 &= ~(3 << 2);
	PINSEL0 |= 0x0000000C;
	//for emergency
	PINSEL1&=~(3<<28);
	PINSEL1|=(2<<28);
	
	//VICIntSelect|=1<<EINT3_VIC_CHNO;//set fiq
	VICIntEnable |= (1 << 14)|(1<<17);//enable ent0 and ent3
	
	VICVectCntl0 = (1 << 5) | 14;
	VICVectAddr0 = (unsigned)EINT0_ISR;
	VICVectCntl1 = (1 << 5) | 17;
	VICVectAddr1 = (unsigned)EINT3_ISR;
	

//	IODIR0 &= ~(1 << 1);

	EXTMODE |= (1<<0)|(1<<3);//set edge trigger
	//EXTPOLAR=0;default is falling edge
}
void EINT3_ISR(void)__irq
	{
	flag1=1;
	EXTINT=1<<3;
		VICVectAddr=0;
}
void extinterrupt(void)
{	Cmdlcd(CLEAR_LCD);
	Strlcd("EMERGENCY ALERT");
	Cmdlcd(GOTO_LINE2_POS0);
	Strlcd("TURN OFF ALL");
	/*IOCLR1=LED1;
	IOCLR1=LED2;*/
	IOSET1=BUZZER;
	IOCLR1=LED1;
	IOCLR1=LED2;
	delay_ms(3000);
	if(!(Islabtime()))
	{
	Cmdlcd(GOTO_LINE1_POS0);
	Strlcd("lab closed      ");
	}
	else
	 {
	Cmdlcd(GOTO_LINE2_POS0);
	Strlcd("Lab is opened   ");
	}
	IOCLR1=BUZZER;
}

