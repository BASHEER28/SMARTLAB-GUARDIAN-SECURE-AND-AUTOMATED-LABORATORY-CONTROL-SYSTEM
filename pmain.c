/*
 * ============================================================================
 * MODULE      : pmain.c
 * PURPOSE     : SmartLab Guardian application entry point
 * PROJECT     : SmartLab Guardian - LPC214x embedded application
 * DESCRIPTION :
 *   - Initialises the LCD, keypad, output devices, RTC and external interrupts before starting the application loop.
 *   - Coordinates password-gated access, lab-hour enforcement, remote-control commands, menu access and emergency events.
 *   - Interrupt handlers only publish event flags; the main loop performs the longer user-interface and device actions.
 * MAINTENANCE : Update this module documentation whenever its public behaviour,
 *               hardware mapping, timing assumptions or dependencies change.
 * NOTE        : Documentation-only annotation; existing program logic is retained.
 * ============================================================================
 */
#include<LPC214x.h>
#include "headerfiles.h"
#include "device_control.h"
#include "rtc.h"
volatile int flag=0;
volatile int flag1=0;
main()
{  u32 addr,command,toggle,temp=0,temp1=0,rtc_flag=0;
    initlcd();
    initkpm();
    initLED();
    initRTC();
	Init_Interrupt();
	passwordchecking();
	Cmdlcd(CLEAR_LCD);
    while(1)
    { 	
      if((Islabtime()))
        {   
			devicestatus(temp,temp1);
				while((readrc5(&addr,&command,&toggle)==0))
				{  
					  if(rtc_flag==0)
					    {showtime();
						 	Cmdlcd(GOTO_LINE2_POS0);
	                        Strlcd("lab is opened  ");
						}
					if(flag)
					{
						flag=0;
						Menu();
						flag1=0;
						if(Islabtime())
						devicestatus(temp,temp1);
						else
						break;
					}
					if(flag1)
					{	   flag1=0;
					 extinterrupt();
					    temp=0,temp1=0;
						if(Islabtime())
						devicestatus(temp,temp1);
						else
						break;
					}  
				}
		     DeviceCntrl(command,&temp,&temp1);
			 command=0;
			 if(rtc_flag==0)
			 {
			 Cmdlcd(GOTO_LINE1_POS0);
			 Strlcd("              ");
			 rtc_flag=1;
			 }
			 rtc_flag=1;
			 	devicestatus(temp,temp1);
			 }								
       else
        {
            AllLEDsOFF();
	
            E :Cmdlcd(0xC0);
            Strlcd("Lab Closed      ");
					while(Islabtime()==0)
					{  showtime();
						if(flag)
						{
							flag=0;
							Menu();
							flag1=0;
							if(Islabtime())
						devicestatus(temp,temp1);
						else
						   goto E;
						}
                      }
					  Cmdlcd(CLEAR_LCD);
					  Cmdlcd(0x80);
                   Strlcd("Lab is now open");
			         delay_ms(100);
    }	 
}	
}

