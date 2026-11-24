/*
 * ============================================================================
 * MODULE      : macros.h
 * PURPOSE     : Register bit-manipulation macros
 * PROJECT     : SmartLab Guardian - LPC214x embedded application
 * DESCRIPTION :
 *   - Provides macros for replacing an eight-bit field and reading a single bit.
 *   - Macro arguments should be simple register/constant expressions; parenthesise expressions at call sites where needed.
 * MAINTENANCE : Update this module documentation whenever its public behaviour,
 *               hardware mapping, timing assumptions or dependencies change.
 * NOTE        : Documentation-only annotation; existing program logic is retained.
 * ============================================================================
 */
//macros.h
#define WRITEBYTE(WORD,STBIT,BYTE) \
WORD=((WORD&~(0xFF<<STBIT))|((BYTE)<<STBIT))
#define READBIT(WORD,BIT) ((WORD>>BIT)&1)
