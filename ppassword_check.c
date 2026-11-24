/*
 * ============================================================================
 * MODULE      : ppassword_check.c
 * PURPOSE     : Password authentication workflow
 * PROJECT     : SmartLab Guardian - LPC214x embedded application
 * DESCRIPTION :
 *   - Collects the configured number of keypad digits, compares the result with the application credential and controls retry behaviour.
 *   - The LCD displays a masked password entry and a welcome or rejection message.
 *   - This is a basic embedded demonstration mechanism; it does not provide secure credential storage or rate limiting.
 * MAINTENANCE : Update this module documentation whenever its public behaviour,
 *               hardware mapping, timing assumptions or dependencies change.
 * NOTE        : Documentation-only annotation; existing program logic is retained.
 * ============================================================================
 */
//passwordcheck.c
#include"headerfiles.h"
#include<LPC214x.h>
int passwordcheck(void)
{
    u32 pass;
          Cmdlcd(CLEAR_LCD);
			    Cmdlcd(GOTO_LINE1_POS0);
          Strlcd("Enter Password");
			   pass=password(PASSWORD_LEN);
         Cmdlcd(CLEAR_LCD);
        if (pass== PASSWORD)
				{
					return 1;
				}
        else
        { 
					return 0;
				}
    }
void passwordchecking(void)
{
	while(1)
	{
	       if(passwordcheck())
            {
                Cmdlcd(CLEAR_LCD);
				Cmdlcd(GOTO_LINE1_POS0);
                Strlcd("WELCM TO SMART");
				Cmdlcd(GOTO_LINE2_POS0);
				Strlcd("GUARDIAN");
                delay_ms(500);
							break;
            }
          else
            {
                Cmdlcd(CLEAR_LCD);
                Strlcd("Wrong Password");
                delay_ms(500);
            }
	}
}


