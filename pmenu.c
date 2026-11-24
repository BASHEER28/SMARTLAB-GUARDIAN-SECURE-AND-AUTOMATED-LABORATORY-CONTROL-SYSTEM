/*
 * ============================================================================
 * MODULE      : pmenu.c
 * PURPOSE     : Interactive configuration menu
 * PROJECT     : SmartLab Guardian - LPC214x embedded application
 * DESCRIPTION :
 *   - Provides the keypad-driven menu for RTC time/date editing and lab schedule configuration.
 *   - Defines the opening and closing schedule values shared with the RTC module.
 *   - Menu choices are interpreted as ASCII digit keys returned by the keypad driver.
 * MAINTENANCE : Update this module documentation whenever its public behaviour,
 *               hardware mapping, timing assumptions or dependencies change.
 * NOTE        : Documentation-only annotation; existing program logic is retained.
 * ============================================================================
 */
//MENU.c

#include <LPC214x.h>
#include "headerfiles.h"
#include "keypad.h"
#include "keypaddefines.h"
#include "types.h"
#include "lcd.h"
#include "LCD_defines.h"
#include "rtc.h"
#include "menu.h"
#include "delay.h"

u32 ON_HOUR = 6;
u32 ON_MIN = 0;

u32 OFF_HOUR = 9;
u32 OFF_MIN = 59;

void Menu(void)
{	
	while(1)
	{ u32 choice;
		Cmdlcd(CLEAR_LCD);
	Strlcd("1.TIME  2.DATE");
	Cmdlcd(GOTO_LINE2_POS0);
	Strlcd("3.LABTIME 4.EXT");
		
		choice =keyscan()-48;
		if(choice == 1)
		{
			rtcedit();
			Cmdlcd(CLEAR_LCD);
				Strlcd("TIME UPDATED");
				showtime();
			delay_ms(1000);
    }
		else if(choice == 2)
    {
			date1();
			Cmdlcd(CLEAR_LCD);
				Strlcd("DATE UPDATED");
				displaydate();
				delay_ms(1000);
		}
		
		else if(choice == 3)
		{
		  labtimeedit();
				Cmdlcd(CLEAR_LCD);
				Strlcd("SCHEDULE UPDATED");
				delay_ms(500);
		}
		else if(choice==4)
		{ 
			Cmdlcd(CLEAR_LCD);
			break;
		}
		else
		{
			Cmdlcd(CLEAR_LCD);
			Strlcd("INVALID OPTION");
			delay_ms(500);
		}
	}
}
