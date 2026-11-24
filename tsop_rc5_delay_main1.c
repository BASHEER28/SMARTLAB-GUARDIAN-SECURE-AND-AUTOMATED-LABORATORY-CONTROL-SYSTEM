/*
 * ============================================================================
 * MODULE      : tsop_rc5_delay_main1.c
 * PURPOSE     : TSOP infrared receiver and RC5 decoder
 * PROJECT     : SmartLab Guardian - LPC214x embedded application
 * DESCRIPTION :
 *   - Implements polling-based edge detection, RC5 frame sampling, field extraction and repeat-frame filtering.
 *   - The receiver assumes the TSOP module's active-low demodulated output and uses software delays for bit timing.
 *   - Polling and software-delay timing are sensitive to compiler optimisation and interrupt latency; validate with a logic analyser or oscilloscope.
 * MAINTENANCE : Update this module documentation whenever its public behaviour,
 *               hardware mapping, timing assumptions or dependencies change.
 * NOTE        : Documentation-only annotation; existing program logic is retained.
 * ============================================================================
 */
		#include <LPC214x.h>                    // Include LPC2148 register definitions (IO0PIN, IODIR0, IOSET0, IOCLR0, PINSEL1, etc.)
		#include "LCD_defines.h"
		#include "delay.h"
/*================ LCD COMMANDS (HD44780) ================*/
/*#define CLEAR_LCD            0x01       // Clear the display and move the cursor home
#define RET_CUR_HOME         0x02       // Return the cursor to home position
#define SHIFT_CUR_RIGHT      0x06       // Entry mode: cursor moves right after each character
#define SHIFT_CUR_LEFT       0x07       // Entry mode: cursor moves left after each character
#define DSP_OFF              0x08       // Display off
#define DSP_ON_CUR_OFF       0x0c       // Display on, cursor hidden
#define DSP_ON_CUR_ON        0x0E       // Display on, cursor shown
#define DSP_ON_CUR_BLINK     0x0F       // Display on, cursor blinking
#define SHIFT_DISP_LEFT      0x10       // Shift the whole display left
#define SHIFT_DISP_RIGHT     0x14       // Shift the whole display right
#define MODE_8BIT_1LINE      0x30       // 8-bit interface, 1 line
#define MODE_4BIT_1LINE      0x20       // 4-bit interface, 1 line
#define MODE_8BIT_2LINE      0x38       // 8-bit interface, 2 lines
#define MODE_4BIT_2LINE      0x28       // 4-bit interface, 2 lines
#define GOTO_LINE1_POS0      0x80       // Move cursor to line 1, position 0
#define GOTO_LINE2_POS0      0xC0       // Move cursor to line 2, position 0
#define GOTO_LINE3_POS0      0x94       // Move cursor to line 3, position 0 (20x4 LCD)
#define GOTO_LINE4_POS0      0xD4       // Move cursor to line 4, position 0 (20x4 LCD)
#define GOTO_CGRAM_START     0x40       // Set the address to the start of CGRAM (custom characters) */

/*================ LCD CONNECTION PINS ================*/
/*#define LCD_DATA 8                      // LCD data pins D0-D7 on P0.8 to P0.15 (start bit = 8)
#define LCD_RS   5                     // LCD register select on P0.16
#define LCD_RW   17                     // LCD read/write on P0.17
#define LCD_EN   6                     // LCD enable on P0.18*/

/*================ TYPE SHORTCUTS ================*/
typedef unsigned int u32;               // 32-bit unsigned integer
typedef const char   cs8;               // Constant character
typedef char s8;                        // Signed 8-bit character
typedef unsigned char u8;               // Unsigned 8-bit integer
typedef int s32;                        // 32-bit signed integer
typedef float f32;                      // 32-bit floating point*/

/*================ HELPER MACROS ================*/
/* Write a byte into a register at a given start bit: first clear the 8 bits, then OR the new byte in */
#define WRITEBYTE(WORD,STARTBIT,BYTE) \
        WORD=((WORD&~(0xFF<<STARTBIT))| \
              (BYTE<<STARTBIT))

#define READBIT(WORD,BIT) ((WORD>>BIT)&1)   // Read one bit: shift it down to bit 0 and mask it

/*================ RC5 SETTINGS ================*/
#define TSOP_PIN 16                     // TSOP output is connected to P0.20 (moved away from the LCD RS pin P0.16)

/* Read the TSOP output on P0.20: shift bit 20 down to bit 0, mask it, result is 0 or 1 */
#define RC5_PIN  ((IO0PIN >> TSOP_PIN) & 1)

#define RC5_T   1778                    // Full RC5 bit time = 1778 us
#define RC5_H   889                     // Half bit time = 889 us (T/2)
#define RC5_Q   444                     // Quarter bit time = 444 us (T/4)
#define STEP_US 20                      // Polling step in us while waiting for an edge

/*================ SOFTWARE DELAYS ================*/

/*void delay_us(u32 dlyUS)                // Microsecond delay
{
    for(dlyUS*=12; dlyUS>0; dlyUS--);   // Convert us to loop count (12 loops per us at CCLK = 60 MHz), count down to 0
}

void delay_ms(u32 dlyMS)                // Millisecond delay
{
    for(dlyMS*=12000; dlyMS>0; dlyMS--);   // Convert ms to loop count (12000 loops per ms), count down to 0
}

void delay_s(u32 dlyS)                  // Second delay (not used in this program)
{
    for(dlyS*=12000000; dlyS>0; dlyS--);   // Convert s to loop count (12,000,000 loops per s), count down to 0
}
  */
/*================ LCD DRIVER ================*/

/*void WriteLCD(u8 byte)                  // Send one byte to the LCD (command or data, depending on RS)
{
    IOCLR0 = 1<<LCD_RW;                 // RW = 0: select write operation
    WRITEBYTE(IOPIN0, LCD_DATA, byte);  // Place the byte on data pins P0.8 to P0.15
    IOSET0 = 1<<LCD_EN;                 // EN = 1: start the latching pulse
    delay_us(1);                        // Keep EN high for about 1 us
    IOCLR0 = 1<<LCD_EN;                 // EN = 0: falling edge latches the byte into the LCD
    delay_ms(2);                        // Wait 2 ms for the LCD to finish processing
}

void CmdLCD(u8 cmd)                     // Send a command byte to the LCD
{
    IOCLR0 = 1<<LCD_RS;                 // RS = 0: select the command register
    WriteLCD(cmd);                      // Write the command byte
}

void InitLCD(void)                      // Initialise the LCD in 8-bit, 2-line mode
{
    IODIR0 |= (0xFF<<LCD_DATA)|(1<<LCD_RS)|     // Make data pins and RS pin outputs
              (1<<LCD_RW)|(1<<LCD_EN);          // Make RW and EN pins outputs too
    delay_ms(15);                       // Power-on delay: wait 15 ms for the LCD to start
    CmdLCD(0x30);                       // Wake-up command, first time
    delay_ms(4);                        // Wait more than 4.1 ms
    delay_us(100);                      // Wait an extra 100 us
    CmdLCD(0x30);                       // Wake-up command, second time
    delay_us(100);                      // Wait 100 us
    CmdLCD(0x30);                       // Wake-up command, third time
    CmdLCD(MODE_8BIT_2LINE);            // Set 8-bit interface, 2 display lines
    CmdLCD(DSP_ON_CUR_OFF);             // Turn the display on, hide the cursor
    CmdLCD(CLEAR_LCD);                  // Clear the display
    CmdLCD(SHIFT_CUR_RIGHT);            // Cursor moves right after each character
}

void CharLCD(u8 asciiVal)               // Display one character
{
    IOSET0 = 1<<LCD_RS;                 // RS = 1: select the data register
    WriteLCD(asciiVal);                 // Write the ASCII value to the display memory
}

void Strlcd(s8 *s)                      // Display a null-terminated string
{
    while(*s)                           // Repeat until the null terminator is reached
        CharLCD(*s++);                  // Show the current character, then advance the pointer
}

void U32LCD(u32 n)                      // Display an unsigned number in decimal
{
    s32 i=0;  u8 a[10];                 // i = digit count, a[] = buffer for digits (stored in reverse)
    if(n==0)                            // Is the number zero?
    {
        CharLCD('0');                   // Yes: just show '0'
    }
    else                                // Number is not zero
    {
        while(n>0)                      // Extract digits until the number becomes 0
        {
            a[i++] = (n%10)+48;         // Take the last digit, convert it to ASCII, store it
            n /= 10;                    // Remove the last digit
        }
        for(--i; i>=0; i--)             // Go back through the digits from last stored to first
        {
            CharLCD(a[i]);              // Show each digit in the correct order
        }
    }
}

void S32LCD(s32 n)                      // Display a signed number (not used in this program)
{
    if(n<0)                             // Is the number negative?
    {
        CharLCD('-');                   // Yes: show the minus sign
        n = -n;                         // Make the number positive
    }
    U32LCD(n);                          // Show the magnitude
}

void F32LCD(f32 fn, u8 nDP)             // Display a float with nDP decimal places (not used in this program)
{
    u32 n, i;                           // n = current digit/integer part, i = loop counter
    if(fn<0.0)                          // Is the value negative?
    {
        CharLCD('-');                   // Yes: show the minus sign
        fn = -fn;                       // Make the value positive
    }
    n = fn;                             // Take the integer part
    U32LCD(n);                          // Show the integer part
    CharLCD('.');                       // Show the decimal point
    for(i=0; i<nDP; i++)                // Repeat for each decimal place
    {
        fn = (fn-n) * 10;               // Remove the shown part, shift the next decimal digit up
        n = fn;                         // Take that digit
        CharLCD(n+48);                  // Show it as an ASCII character
    }
}					   */

/*================ EDGE / IDLE HELPERS ================*/

/* Wait until the line changes from 'lvl'. Returns 1 if the edge came within max_us, else 0 */
static unsigned char WaitEdge(unsigned int lvl, unsigned int max_us)
{
    unsigned int t = 0;                 // Elapsed time in us, starts at 0

    while(t < max_us)                   // Keep checking until the time limit is reached
    {
        if(RC5_PIN != lvl)              // Has the pin level changed from the starting level?
            return 1;                   // Yes: edge found, report success
        delay_us(STEP_US);              // No: wait one polling step (20 us)
        t += STEP_US;                   // Add the step to the elapsed time
    }
    return 0;                           // Time ran out with no edge: report failure
}

/* Wait until the line has stayed HIGH for 4 ms (frame is over) */
static void WaitIdle(void)
{
    unsigned int t = 0;                 // Time the line has been continuously HIGH

    while(t < 4000)                     // Loop until HIGH has lasted 4000 us
    {
        if(RC5_PIN == 0)                // Is the line LOW (IR burst still present)?
            t = 0;                      // Yes: restart the idle timer
        else                            // Line is HIGH
            t += STEP_US;               // Add one step to the idle time
        delay_us(STEP_US);              // Wait one polling step before checking again
    }
}

/*================ DUPLICATE FILTER =================*/

unsigned int last_address = 0;          // Address of the last accepted frame
unsigned int last_command = 0;          // Command of the last accepted frame
unsigned int last_toggle  = 0;          // Toggle bit of the last accepted frame
unsigned char previous_key_valid = 0;   // Flag: 1 once a frame has been stored

/*================ RC5 RECEIVE ================*/

/* Call right after the first falling edge (middle of start bit S1) */
unsigned char RC5_Receive(unsigned int *address,   // Output: 5-bit address
                          unsigned int *command,   // Output: 6-bit command
                          unsigned int *toggle)    // Output: toggle bit
{
    unsigned int data = 1;              // Frame data, starts with the start bit S1 = 1
    unsigned int i, lvl;                // i = bit counter, lvl = pin level before an edge

    delay_us(RC5_T - RC5_Q);            // Move from mid S1 to 0.75T, inside the first half of the next bit

    for(i = 0; i < 13; i++)             // Receive the remaining 13 bits (S2, toggle, 5 address, 6 command)
    {
        lvl = RC5_PIN;                  // Remember the current pin level

        if(!WaitEdge(lvl, RC5_T))       // Wait for the mid-bit transition (resync point)
            return 0;                   // No edge within one bit time: bad frame, give up

        delay_us(RC5_Q);                // Wait a quarter bit after the edge, into the stable second half

        if(RC5_PIN == 0)                // Sample the pin: LOW means 1 (TSOP output is inverted)
            data = (data << 1) | 1;     // Shift data left and add a 1
        else                            // Pin is HIGH, so the bit is 0
            data = (data << 1);         // Shift data left and add a 0

        delay_us(RC5_H);                // Wait half a bit to reach 0.75T of the next bit
    }

    if(((data >> 12) & 1) != 1)         // Check the second start bit S2 (bit 12), must be 1
        return 0;                       // Invalid start bit: reject the frame

    *toggle  = (data >> 11) & 1;        // Extract the toggle bit (bit 11)
    *address = (data >> 6)  & 0x1F;     // Extract the 5 address bits (bits 10-6)
    *command =  data        & 0x3F;     // Extract the 6 command bits (bits 5-0)
    return 1;                           // Report that a valid frame was received
}

/*================ MAIN ================*/

int readrc5(u32 *address,u32 *command,u32 *toggle)                          // Program entry point
{
    //unsigned int address, command, toggle;   // Variables to hold the decoded values

    PINSEL1 &= ~(3 << 8);               // Set P0.20 to GPIO function (its function bits are 9:8 of PINSEL1)
    IO0DIR  &= ~(1 << TSOP_PIN);        // Make P0.20 an input (TSOP output)               
        if(RC5_PIN == 0)
		{           // Wait here while the line is idle HIGH, exit on the first falling edge

        if(RC5_Receive(address, command, toggle))   // Decode one frame; true if it was valid
        {
            if(!(previous_key_valid &&          // Was there a previous key AND...
                 *address == last_address &&     // ...same address AND...
                 *command == last_command &&     // ...same command AND...
                 *toggle  == last_toggle))       // ...same toggle? If so it is a repeat, so skip it
            {
                last_address = *address;         // Save this address for the next comparison
                last_command = *command;         // Save this command for the next comparison
                last_toggle  = *toggle;          // Save this toggle bit for the next comparison
                previous_key_valid = 1;         // Mark that a stored key now exists
				    
				   }
				   WaitIdle();
				   return 1;
		//return 0;
	   }
	   return 1;                   // Wait until the line is HIGH for 4 ms so the same frame is not decoded twice
    }
		return 0;
}
