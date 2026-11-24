/*
 * ============================================================================
 * MODULE      : menu.h
 * PURPOSE     : User menu interface and schedule state
 * PROJECT     : SmartLab Guardian - LPC214x embedded application
 * DESCRIPTION :
 *   - Exposes the interactive menu entry point and the configured lab opening/closing time variables.
 *   - The schedule variables are defined by the menu module and consumed by the RTC access-control logic.
 * MAINTENANCE : Update this module documentation whenever its public behaviour,
 *               hardware mapping, timing assumptions or dependencies change.
 * NOTE        : Documentation-only annotation; existing program logic is retained.
 * ============================================================================
 */
//menu.h

#include "types.h"

extern u32 ON_HOUR;
extern u32 ON_MIN;
extern u32 OFF_HOUR;
extern u32 OFF_MIN;

void Menu(void);


