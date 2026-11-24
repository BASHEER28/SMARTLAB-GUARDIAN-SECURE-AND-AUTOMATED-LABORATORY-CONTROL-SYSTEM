/*
 * ============================================================================
 * MODULE      : lcd.h
 * PURPOSE     : LCD driver public interface
 * PROJECT     : SmartLab Guardian - LPC214x embedded application
 * DESCRIPTION :
 *   - Declares low-level LCD operations and formatted output helpers.
 *   - Call the LCD initialisation routine before sending commands, characters or strings.
 * MAINTENANCE : Update this module documentation whenever its public behaviour,
 *               hardware mapping, timing assumptions or dependencies change.
 * NOTE        : Documentation-only annotation; existing program logic is retained.
 * ============================================================================
 */
//LCD.h

#include "types.h"
void initlcd(void);
void Writelcd(u8 dat);
void Cmdlcd(u8 cmd);
void Charlcd(u8 asciival);
void Initlcd(void);
void Strlcd(s8 *);
void u32lcd(u32);
void s32lcd(s32);
void f32lcd(f32,u8);
void BuildCGRAM(u8*,u8);
