/*
 * ============================================================================
 * MODULE      : keypaddefines.h
 * PURPOSE     : Matrix keypad GPIO mapping
 * PROJECT     : SmartLab Guardian - LPC214x embedded application
 * DESCRIPTION :
 *   - Maps the four keypad row lines and four column lines to LPC214x Port 1 bit positions.
 *   - These bit positions must match the PCB or breadboard wiring and the scan implementation.
 * MAINTENANCE : Update this module documentation whenever its public behaviour,
 *               hardware mapping, timing assumptions or dependencies change.
 * NOTE        : Documentation-only annotation; existing program logic is retained.
 * ============================================================================
 */
//KeypadDEFINES.H
#define ROW0 16
#define ROW1 17
#define ROW2 18
#define ROW3 19
#define COL0 20
#define COL1 21
#define COL2 22
#define COL3 23
