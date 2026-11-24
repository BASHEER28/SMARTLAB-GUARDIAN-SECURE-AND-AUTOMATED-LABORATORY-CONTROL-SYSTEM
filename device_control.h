/*
 * ============================================================================
 * MODULE      : device_control.h
 * PURPOSE     : Device-control module interface
 * PROJECT     : SmartLab Guardian - LPC214x embedded application
 * DESCRIPTION :
 *   - Declares the LED initialisation, bulk LED operations, command dispatcher and status-display routines.
 *   - The implementation uses the board-level LED and buzzer pin assignments defined in the project configuration.
 * MAINTENANCE : Update this module documentation whenever its public behaviour,
 *               hardware mapping, timing assumptions or dependencies change.
 * NOTE        : Documentation-only annotation; existing program logic is retained.
 * ============================================================================
 */
//device_control.h
#include"types.h"
void initLED(void);
void AllLEDsOFF(void);
void AllLEDsON(void);
int LEDControl(u8 );
void DeviceCntrl(u32 ,u32 *,u32 *);
void devicestatus(u32 ,u32 );
