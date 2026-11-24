/*
 * ============================================================================
 * MODULE      : rtc_time_date1.c
 * PURPOSE     : RTC time, date and schedule configuration UI
 * PROJECT     : SmartLab Guardian - LPC214x embedded application
 * DESCRIPTION :
 *   - Implements keypad-driven editing of RTC time, calendar date and lab opening/closing schedule.
 *   - Uses ReadNum() for numeric entry and writes accepted values to the LPC214x RTC registers or schedule variables.
 *   - Input range checks in this module are application-level checks; calendar validity and boundary values should be verified before deployment.
 * MAINTENANCE : Update this module documentation whenever its public behaviour,
 *               hardware mapping, timing assumptions or dependencies change.
 * NOTE        : Documentation-only annotation; existing program logic is retained.
 * ============================================================================
 */
#include "types.h"
#include "headerfiles.h"
void rtcedit(void)
{ u32 choice;
        u32 hour, minute, second;
        while(1)
        {
                Cmdlcd(CLEAR_LCD);
        Strlcd("1.HOUR  2.MIN");
        Cmdlcd(GOTO_LINE2_POS0);
        Strlcd("3.SEC  4.EXT");

                choice =keyscan()-48;
        if(choice==1)
        {
Hour:
                        Cmdlcd(CLEAR_LCD);
                        Strlcd("ENTER HOUR");
                        hour = ReadNum();
                        if(hour > 24)
                        {
                                Cmdlcd(CLEAR_LCD);
                                Strlcd("INVALID HOUR");
                                delay_ms(500);
                                goto Hour;
                        }
                        HOUR=hour;
                }
        else if(choice==2)
        {
                        Minute:
                        Cmdlcd(CLEAR_LCD);
                        Strlcd("ENTER MINUTE");
                        minute = ReadNum();
                        if(minute > 60)
                        {
                                Cmdlcd(CLEAR_LCD);
                                Strlcd("INVALID MINUTE");
                                delay_ms(500);
                                goto Minute;
                        }
                        MIN=minute;
                }
  else if(choice==3)
        {
                        Second:
                        Cmdlcd(CLEAR_LCD);
                        Strlcd("ENTER SECOND");
                         second=ReadNum();
                        if(second > 60)
                        {
                                Cmdlcd(CLEAR_LCD);
                                Strlcd("INVALID SECOND");
                                delay_ms(500);
                                goto Second;
                        }
                        SEC=second;
                }
        else if(choice==4)
                return;
        else
        {
                Cmdlcd(CLEAR_LCD);
                                Strlcd("invalid option");
                delay_ms(100);
        }
}
}
void date1(void)
{ u32 date,month,year,choice;
        while(1)
        {
                Cmdlcd(CLEAR_LCD);
        Strlcd("1.DATE 2.MONTH");
        Cmdlcd(GOTO_LINE2_POS0);
        Strlcd("3.YEAR  4.EXT");
                choice=keyscan()-48;
                if(choice==1)
                {
        Date:
                        Cmdlcd(CLEAR_LCD);
                        Strlcd("ENTER DATE");
                        date = ReadNum();
                        if(date > 31)
                        {
                                Cmdlcd(CLEAR_LCD);
                                Strlcd("INVALID DATE");
                                delay_ms(500);
                                goto Date;
                        }
                        DOM=date;
                }
                else if(choice==2)
                {
                        Month:
                        Cmdlcd(CLEAR_LCD);
                        Strlcd("ENTER MONTH");
                        month = ReadNum();
                        if(month > 12)
                        {
                                Cmdlcd(CLEAR_LCD);
                                Strlcd("INVALID MONTH");
                                delay_ms(500);
                                goto Month;
                        }
                        MONTH=month;
                }
                else if(choice==3)
                {

                        Year:
                        Cmdlcd(CLEAR_LCD);
                        Strlcd("ENTER YEAR");
                        year = ReadNum();
                        if(year > 4096)
                        {
                                Cmdlcd(CLEAR_LCD);
                                Strlcd("INVALID YEAR");
                                delay_ms(500);
                                goto Year;
                        }
                        YEAR=year;
                }
                else if(choice==4)
                {
                        return;
                }
                else
                {
                        Cmdlcd(CLEAR_LCD);
                                Strlcd("invalid option");
                delay_ms(100);
                }
        }
}

   /////
   void labtimeedit(void)
   {
     u32 choice; 
		 u32 second;
     while(1)
         {
        Cmdlcd(CLEAR_LCD);
        Strlcd("1.ON TIME       ");
        Cmdlcd(GOTO_LINE2_POS0);
        Strlcd("2.OFF TIME 3.EXT");
                choice=keyscan()-48;
					  delay_ms(100);
 if(choice==1)
        { 
					while(1)
        {
                Cmdlcd(CLEAR_LCD);
        Strlcd("1.HOUR 2.MIN");
        Cmdlcd(GOTO_LINE2_POS0);
        Strlcd("3.SEC  4.EXT");

                choice =keyscan()-48;
					     delay_ms(100);
        if(choice==1)
        {
                 Hour:
                        Cmdlcd(CLEAR_LCD);
                        Strlcd("ENTER HOUR");
                        ON_HOUR = ReadNum();
                        if(ON_HOUR > 24)
                        {
                                Cmdlcd(CLEAR_LCD);
                                Strlcd("INVALID HOUR");
                                delay_ms(500);
                                goto Hour;
                        }
                }
        else if(choice==2)
        {
                        Minute:
                        Cmdlcd(CLEAR_LCD);
                        Strlcd("ENTER MINUTE");
                        ON_MIN= ReadNum();
                        if(ON_MIN > 60)
                        {
                                Cmdlcd(CLEAR_LCD);
                                Strlcd("INVALID MINUTE");
                                delay_ms(500);
                                goto Minute;
                        }
                }
  else if(choice==3)
        {
                        Second:
                        Cmdlcd(CLEAR_LCD);
                        Strlcd("ENTER SECOND");
                         second=ReadNum();
                        if(second > 60)
                        {
                                Cmdlcd(CLEAR_LCD);
                                Strlcd("INVALID SECOND");
                                delay_ms(500);
                                goto Second;
                        }
                       // SEC=second;
                }
        else if(choice==4)
                break;
        else
        {
                Cmdlcd(CLEAR_LCD);
                                Strlcd("invalid option");
                delay_ms(100);
        }
}
				}
else if(choice==2)
                {
                        while(1)
        {
                Cmdlcd(CLEAR_LCD);
        Strlcd("1.HOUR  2.MIN");
        Cmdlcd(GOTO_LINE2_POS0);
        Strlcd("3.SEC  4.EXT");

                choice =keyscan()-48;
					     delay_ms(100);
        if(choice==1)
        {
                 Hour1:
                        Cmdlcd(CLEAR_LCD);
                        Strlcd("ENTER HOUR");
                        OFF_HOUR= ReadNum();
                        if(OFF_HOUR> 24)
                        {
                                Cmdlcd(CLEAR_LCD);
                                Strlcd("INVALID HOUR");
                                delay_ms(500);
                                goto Hour1;
                        }
                }
        else if(choice==2)
        {
                        Minute1:
                        Cmdlcd(CLEAR_LCD);
                        Strlcd("ENTER MINUTE");
                        OFF_MIN= ReadNum();
                        if(OFF_MIN > 60)
                        {
                                Cmdlcd(CLEAR_LCD);
                                Strlcd("INVALID MINUTE");
                                delay_ms(500);
                                goto Minute1;
                        }
                }
  else if(choice==3)
        {
                        Second1:
                        Cmdlcd(CLEAR_LCD);
                        Strlcd("ENTER SECOND");
                         second=ReadNum();
                        if(second > 60)
                        {
                                Cmdlcd(CLEAR_LCD);
                                Strlcd("INVALID SECOND");
                                delay_ms(500);
                                goto Second1;
                        }
                       // SEC=second;
                }
        else if(choice==4)
                break;
        else
        {
                Cmdlcd(CLEAR_LCD);
                                Strlcd("invalid option");
                delay_ms(100);
        }
    }
 }
else if(choice==3)
                {
                        break;
                }
     else
                {
                        Cmdlcd(CLEAR_LCD);
                                Strlcd("invalid option");
                delay_ms(100);
                }
        }
}
