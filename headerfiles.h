/*
 * ============================================================================
 * MODULE      : headerfiles.h
 * PURPOSE     : Application-wide project configuration
 * PROJECT     : SmartLab Guardian - LPC214x embedded application
 * DESCRIPTION :
 *   - Collects common peripheral interfaces and project-wide hardware/application constants.
 *   - PASSWORD and PASSWORD_LEN define the current demonstration access credential and expected digit count.
 *   - Extern declarations are defined in their owning source modules; this header only makes them visible to other modules.
 * MAINTENANCE : Update this module documentation whenever its public behaviour,
 *               hardware mapping, timing assumptions or dependencies change.
 * NOTE        : Documentation-only annotation; existing program logic is retained.
 * ============================================================================
 */
//header file inclusion
#include<LPC214x.h>
#include "LCD_defines.h"
#include "lcd.h"
#include "delay.h"
#include "types.h"
#include "rtc.h"
#include "keypad.h"
#include "keypaddefines.h"
#include "menu.h"
#include "password.h"
#include "tsop_rc5.h"
#include "externalswitches.h"
#define LED1 (1<<24)
#define LED2 (1<<25)
#define LED_MASK (LED1|LED2)
#define BUZZER (1<<26)

#define PASSWORD       4444
#define PASSWORD_LEN   4

//extern u32 temp;
//extern u32 temp1;

extern u32 addr;
extern u32 command;
extern u32 toggle; 

