/*
 * ============================================================================
 * MODULE      : LCD_defines.h
 * PURPOSE     : LCD hardware and command definitions
 * PROJECT     : SmartLab Guardian - LPC214x embedded application
 * DESCRIPTION :
 *   - Centralises HD44780-compatible LCD instruction codes and the LPC214x GPIO pin mapping.
 *   - LCD_DATA is the starting bit position for the data bus; LCD_RS, LCD_RW and LCD_EN identify control pins.
 *   - Keep these definitions consistent with the physical wiring and the LCD driver implementation.
 * MAINTENANCE : Update this module documentation whenever its public behaviour,
 *               hardware mapping, timing assumptions or dependencies change.
 * NOTE        : Documentation-only annotation; existing program logic is retained.
 * ============================================================================
 */
//lcd_defines.h
//HD44780 commands

#define CLEAR_LCD 0x01
#define RET_CUR_HOME 0x02
#define SHIFT_CUR_RIGHT 0x06
#define SHIFT_CUR_LEFT 0x07
#define DSP_OFF 0x08
#define DSP_ON_CUR_OFF 0x0C
#define DSP_ON_CUR_ON 0x0E
#define DSP_ON_CUR_BLK 0x0F
#define SHIFT_DSP_LEFT 0x10
#define SHIFT_DSP_RIGHT 0x14
#define MODE_8BIT_1LINE 0x30
#define MODE_4BIT_1LINE 0x20
#define MODE_8BIT_2LINE 0x38
#define MODE_4BIT_2LINE 0x28
#define GOTO_LINE1_POS0 0x80
#define GOTO_LINE2_POS0 0xC0
#define GOTO_LINE3_POS0 0x94
#define GOTO_LINE4_POS0 0xD4
#define GOTO_CGRAM_START 0x40

//lcd pin connection to LPC21xx defines

#define LCD_DATA 8
#define LCD_RS 17
#define LCD_RW 19
#define LCD_EN 18

//lcd interface selection

#define LCD_MODE 4

