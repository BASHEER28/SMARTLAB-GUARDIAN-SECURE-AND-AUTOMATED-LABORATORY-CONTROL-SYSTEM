/*
 * ============================================================================
 * MODULE      : password.h
 * PURPOSE     : Password module interface
 * PROJECT     : SmartLab Guardian - LPC214x embedded application
 * DESCRIPTION :
 *   - Declares the password validation function and the retry-until-success user interaction routine.
 *   - The credential policy and input length are configured in the common project header.
 * MAINTENANCE : Update this module documentation whenever its public behaviour,
 *               hardware mapping, timing assumptions or dependencies change.
 * NOTE        : Documentation-only annotation; existing program logic is retained.
 * ============================================================================
 */
//password.h
void passwordchecking(void);
int passwordcheck(void);
