/*
 * ============================================================================
 * MODULE      : tsop_rc5.h
 * PURPOSE     : TSOP receiver and RC5 protocol interface
 * PROJECT     : SmartLab Guardian - LPC214x embedded application
 * DESCRIPTION :
 *   - Defines the TSOP input pin, RC5 bit timing constants and the public receive API.
 *   - Declares the last-frame state used by the RC5 repeat/duplicate filter.
 *   - Timing constants are based on the nominal RC5 protocol and must be validated against the actual receiver module and clock.
 * MAINTENANCE : Update this module documentation whenever its public behaviour,
 *               hardware mapping, timing assumptions or dependencies change.
 * NOTE        : Documentation-only annotation; existing program logic is retained.
 * ============================================================================
 */
 /*================ RC5 SETTINGS ================*/
 int readrc5(u32 *,u32 *,u32 *);
void init_RC5(void);
u8 RC5_Receive(u32 *,u32 *,u32 *) ;


#define TSOP_PIN 16                     // TSOP output is connected to P0.20 (moved away from the LCD RS pin P0.16)


/* Read the TSOP output on P0.20: shift bit 20 down to bit 0, mask it, result is 0 or 1 */

#define READ_RC5PIN  ((IOPIN0 >> TSOP_PIN) & 1)
#define RC5_T   1778                    // Full RC5 bit time = 1778 us

#define RC5_H   889                     // Half bit time = 889 us (T/2)

#define RC5_Q   444                     // Quarter bit time = 444 us (T/4)

#define STEP_US 20         // Polling step in us while waiting for an edge


extern unsigned int last_address;          // Address of the last accepted frame

extern unsigned int last_command;          // Command of the last accepted frame

extern unsigned int last_toggle;          // Toggle bit of the last accepted frame

extern unsigned char previous_key_valid;
