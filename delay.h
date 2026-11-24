/*
 * ============================================================================
 * MODULE      : delay.h
 * PURPOSE     : Software delay API
 * PROJECT     : SmartLab Guardian - LPC214x embedded application
 * DESCRIPTION :
 *   - Declares blocking delay routines used by peripheral drivers and application modules.
 *   - The actual delay accuracy depends on the configured CPU clock, compiler optimisation and instruction timing.
 * MAINTENANCE : Update this module documentation whenever its public behaviour,
 *               hardware mapping, timing assumptions or dependencies change.
 * NOTE        : Documentation-only annotation; existing program logic is retained.
 * ============================================================================
 */
//delay.h
#include "types.h"
void delay_us(u32 dlyus);
void delay_ms(u32 dlyms);
void delay_s(u32 dlys);


