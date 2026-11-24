/*
 * ============================================================================
 * MODULE      : keypad.h
 * PURPOSE     : Matrix keypad driver interface
 * PROJECT     : SmartLab Guardian - LPC214x embedded application
 * DESCRIPTION :
 *   - Declares keypad initialisation, row/column scanning, key decoding and numeric/password input APIs.
 *   - The returned key values are ASCII characters as defined by the lookup table in the keypad implementation.
 * MAINTENANCE : Update this module documentation whenever its public behaviour,
 *               hardware mapping, timing assumptions or dependencies change.
 * NOTE        : Documentation-only annotation; existing program logic is retained.
 * ============================================================================
 */
//keypad.h
#include "types.h"
void initkpm(void);
int colscan(void);
u8 rowcheck(void);
u8 colcheck(void);
u8 keyscan(void);
u32 ReadNum(void);
void Readnum2(u32 *,u8 *);
u32 password(u32 );
