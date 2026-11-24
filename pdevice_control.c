/*
 * ============================================================================
 * MODULE      : pdevice_control.c
 * PURPOSE     : Output-device control implementation
 * PROJECT     : SmartLab Guardian - LPC214x embedded application
 * DESCRIPTION :
 *   - Initialises the LED and buzzer GPIO outputs and applies decoded commands to the output devices.
 *   - Maintains software status values for the two LEDs and updates the LCD with the current device state.
 *   - The command values are part of the current RC5/application command mapping; keep the transmitter mapping and receiver mapping aligned.
 * MAINTENANCE : Update this module documentation whenever its public behaviour,
 *               hardware mapping, timing assumptions or dependencies change.
 * NOTE        : Documentation-only annotation; existing program logic is retained.
 * ============================================================================
 */
//device_control.c
#include "headerfiles.h"
#include "device_control.h"

//u32 temp=0,temp1=0;

void initLED(void)
{
    //PINSEL0&=~(3<<10);//p0.5 as GPIO
    //PINSEL0&=~(3<<12);//p0.6 as GPIO

    IODIR1 |= LED_MASK|BUZZER;
	IOCLR1=BUZZER;
    IOCLR1=LED_MASK;
}
void AllLEDsOFF(void)
{
	IOCLR1=LED_MASK;
}
void AllLEDsON(void)
{
	IOSET1=LED_MASK;
}
void DeviceCntrl(u32 command,u32 *temp,u32 *temp1)
{	 
          switch(command)
			{
			  case 1:IOSET1=LED1;
					*temp=1;
				   break;
			  case 2:IOCLR1=LED1;
			        *temp=0;
					break;
			case 3:IOSET1=LED2;
			       *temp1=1;
		           break;				
				case 4:IOCLR1=LED2;
					*temp1=0;
					break;
			case 5:AllLEDsON();
			       *temp=1,*temp1=1;
				    break;
			case 6:AllLEDsOFF();
			       *temp=0,*temp1=0;
	            	break;
			 case 47:Cmdlcd(CLEAR_LCD);
			         showtime();
			         delay_ms(1000);
					 break;
}
}
void devicestatus(u32 temp,u32 temp1)
{		 			 
	                if(temp==1)
					{ Cmdlcd(GOTO_LINE1_POS0);
					Strlcd("L1 ON  ");
					}
					else
					 {
					 Cmdlcd(GOTO_LINE1_POS0);
					Strlcd("L1 OFF  ");
					}
					if(temp1==1)
					 {
					 Cmdlcd(GOTO_LINE1_POS0+8);
					Strlcd("L2 ON   ");
					}
					else
					 {
					 Cmdlcd(GOTO_LINE1_POS0+8);
					Strlcd("L2 OFF  ");
            		 }
                 Cmdlcd(GOTO_LINE2_POS0);
	             Strlcd("lab is opened   ");
}

