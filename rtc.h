/*
 * ============================================================================
 * MODULE      : rtc.h
 * PURPOSE     : RTC module interface and clock configuration
 * PROJECT     : SmartLab Guardian - LPC214x embedded application
 * DESCRIPTION :
 *   - Declares RTC initialisation, time/date display/editing and lab-schedule functions.
 *   - Defines oscillator, CPU/peripheral clock and RTC prescaler calculations used by the RTC configuration.
 *   - Clock constants must reflect the actual oscillator and PLL settings used by the board.
 * MAINTENANCE : Update this module documentation whenever its public behaviour,
 *               hardware mapping, timing assumptions or dependencies change.
 * NOTE        : Documentation-only annotation; existing program logic is retained.
 * ============================================================================
 */
//rtc.h
#include "types.h"
void initRTC(void);
u32 Islabtime(void);
void labtimecheck(void);
void showtime(void);
void displaydate(void);
void rtcedit(void);
void date1(void);
void labtimeedit(void);
void RTC_SetDate(u32,u32,u32,u32);
void RTC_SetTime(u32,u32,u32);
#define FOSC          12000000         //frequency os system
#define CCLK          FOSC*5           //CPU opearating clock freq
#define PCLK          CCLK/4           //pheripharals opearating clock freq
#define PRE_INT_FREQ  (PCLK/32768)-1      //prescale register convet pclk to rtc clk freq(32.768KHZ).it gives approx value 
#define PRE_FRAC_FREQ \
PCLK-((PRE_INT_FREQ+1)*32768)  //prescale register convet pclk to rtc clk freq.it gives exact value with fraction also





