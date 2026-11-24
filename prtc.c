/*
 * ============================================================================
 * MODULE      : prtc.c
 * PURPOSE     : Real-time clock and lab access policy
 * PROJECT     : SmartLab Guardian - LPC214x embedded application
 * DESCRIPTION :
 *   - Initialises the LPC214x RTC, evaluates whether the current time falls within the configured lab schedule and formats time/date for the LCD.
 *   - Provides validated setter functions for time and date values.
 *   - The RTC clock source, prescaler and backup-power behaviour must be configured and validated for the target hardware.
 * MAINTENANCE : Update this module documentation whenever its public behaviour,
 *               hardware mapping, timing assumptions or dependencies change.
 * NOTE        : Documentation-only annotation; existing program logic is retained.
 * ============================================================================
 */
//REAL TIME CLOCK.c program
/********************************************************************************************/
//header file inclusion
#include"headerfiles.h"
#include "rtc.h"
u8 day[][4]={"SUN","MON","TUE","WED","THU","FRI","SAT"}; //day of week register
void initRTC(void)
{
/*-----------------------------------------------------------------------------------------
 to set require RTC parameters
-----------------------------------------------------------------------------------------*/
if((CCR&0X01)==0)
{
//to enable the RTC by 0th bit set  and give external frequency by set 4th bit
//CCR=1<<1;
CCR=(1<<0|1<<4);
HOUR=10;
MIN=59;
SEC=30;
DOM=31;
DOW=4;
MONTH=11;
YEAR=2026;
}
else
CCR|=1<<4;
}

u32 Islabtime(void)
{ 
	if(((ON_HOUR)*60+ON_MIN)<((OFF_HOUR)*60)+OFF_MIN)
	{
		if((((HOUR*60)+MIN)>=((ON_HOUR*60)+ON_MIN))&&(((HOUR*60)+MIN)<((OFF_HOUR*60)+OFF_MIN)))
		return 1;
	}
 else if(((ON_HOUR)*60+ON_MIN)> ((OFF_HOUR)*60)+OFF_MIN)
{
	if((((HOUR*60)+MIN)>=((ON_HOUR*60)+ON_MIN))||(((HOUR*60)+MIN)<((OFF_HOUR*60)+OFF_MIN)))
	return 1;
}
  return 0;
}
void showtime(void)
{  		 
		Cmdlcd(GOTO_LINE1_POS0);   //current cur in line1 pos1 in LCD
Charlcd((HOUR/10)+48);
Charlcd((HOUR%10)+48);
Charlcd(':');
Charlcd((MIN/10)+48);
Charlcd((MIN%10)+48);
Charlcd(':');
Charlcd((SEC/10)+48);
Charlcd((SEC%10)+48);
Strlcd("        ");
}
void RTC_SetTime(u32 hour, u32 minute, u32 second)
{
    if(hour < 24 && minute < 60 && second < 60)
    {
        SEC = second;
        MIN = minute;
        HOUR = hour;
    }
}

void RTC_SetDate(u32 date, u32 month, u32 year, u32 day)
{
	if(date >= 1 && date <= 31 &&
		 month >= 1 && month <= 12 &&
		 year >= 2000 && year <= 2099 &&
		 day <= 6)
	{
			DOM = date;
			MONTH = month;
			YEAR = year;
			DOW = day;
	}
}
void displaydate(void)
{
	Charlcd((DOM / 10) + 48);
	Charlcd((DOM % 10) + 48);
	Charlcd('-');

	Charlcd((MONTH / 10) + 48);
	Charlcd((MONTH % 10) + 48);
	Charlcd('-');

	Charlcd((YEAR / 1000) + 48);
	Charlcd(((YEAR / 100) % 10) + 48);
	Charlcd(((YEAR / 10) % 10) + 48);
	Charlcd((YEAR % 10) + 48);
}


void labtimecheck(void)
{
  if((Islabtime()))
        {  
					
					Cmdlcd(CLEAR_LCD);
					Cmdlcd(0x80);
					Strlcd("lab open");
				  delay_ms(1000);
				Cmdlcd(CLEAR_LCD);
            
        }
}

	

