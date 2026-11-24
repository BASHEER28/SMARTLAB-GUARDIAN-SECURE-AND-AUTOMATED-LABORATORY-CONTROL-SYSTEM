/*
 * ============================================================================
 * MODULE      : externalswitches.h
 * PURPOSE     : External interrupt interface and configuration
 * PROJECT     : SmartLab Guardian - LPC214x embedded application
 * DESCRIPTION :
 *   - Declares the external interrupt initialisation routine and interrupt service routines.
 *   - The EINT pin-function values and VIC channel numbers must match the LPC214x pin multiplexing and vector configuration.
 * MAINTENANCE : Update this module documentation whenever its public behaviour,
 *               hardware mapping, timing assumptions or dependencies change.
 * NOTE        : Documentation-only annotation; existing program logic is retained.
 * ============================================================================
 */
//externalswitches.h
void Init_Interrupt(void);
void EINT3_ISR(void)__irq;
void EINT0_ISR(void)__irq;

#define EINT0_PIN_0_1 0
#define EINT0_PIN_FUNC 0x0000000C
#define EINT0_VIC_CHNO 14

#define EINT3_PIN_0_9 0
#define EINT3_PIN_FUNC 0x25400000
#define EINT3_VIC_CHNO 17

/*definitions for input devics such as switche's
#define EMERG_SW		1
#define RTC_SW      6*/

