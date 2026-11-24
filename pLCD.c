/*
 * ============================================================================
 * MODULE      : pLCD.c
 * PURPOSE     : LCD peripheral driver implementation
 * PROJECT     : SmartLab Guardian - LPC214x embedded application
 * DESCRIPTION :
 *   - Implements GPIO-based communication with the character LCD, including command/data writes and numeric formatting.
 *   - The driver is configured for an eight-bit data bus using the pin positions in LCD_defines.h.
 *   - Timing is implemented with blocking software delays; verify timing against the LCD datasheet and actual peripheral clock.
 * MAINTENANCE : Update this module documentation whenever its public behaviour,
 *               hardware mapping, timing assumptions or dependencies change.
 * NOTE        : Documentation-only annotation; existing program logic is retained.
 * ============================================================================
 */
//LCD.c

#include "types.h"
#include <LPC214x.h>
#include "macros.h"
#include "LCD_defines.h"
#include "delay.h"
#include "lcd.h"

void Writelcd(u8 dat)
{
	WRITEBYTE(IOPIN0,LCD_DATA,dat);//IOPIN0=IOPINO&~(oxff<<LCD_DATA))|dat<<LCD_DATA;
	IOCLR0=1<<LCD_RW;
	IOSET0=1<<LCD_EN;
	delay_us(1); 
	IOCLR0=1<<LCD_EN;
	delay_ms(2);
}
void Cmdlcd(u8 cmd)
{
	IOCLR0=1<<LCD_RS;
	Writelcd(cmd);
}
void Charlcd(u8 asciival)
{
	IOSET0=1<<LCD_RS;
	Writelcd(asciival);
}
void initlcd(void)
{
	IODIR0|=((0xff<<LCD_DATA)|(1<<LCD_RS)|(1<<LCD_RW)|(1<<LCD_EN));
	delay_ms(15);
	Cmdlcd(0x30);
	delay_ms(4);
	delay_us(100);
	Cmdlcd(0x30);
	delay_us(100);
	Cmdlcd(0x30);
	Cmdlcd(MODE_8BIT_2LINE);
	Cmdlcd(DSP_ON_CUR_OFF);
	Cmdlcd(CLEAR_LCD);
	Cmdlcd(SHIFT_CUR_RIGHT);
}
void Strlcd(s8 *s)
{
	while(*s)
	{
		Charlcd(*s);
		s++;}
}
void u32lcd(u32 n)
{
	u8 a[10];
	s32 i=0;
	if(n==0)
		{
			Charlcd('0');
		}
		else
			{
				while(n>0)
					{
						a[i]=(n%10)+48;
						n/=10;
						i++;
					}
					for(--i;i>=0;i--)
					{
						Charlcd(a[i]);
					}
			}
}
void s32lcd(s32 sn)
{
	if(sn<0)
		{
			Charlcd('-');
			sn=-sn;
		}
		u32lcd(sn);
}
void f32lcd(f32 FN,u8 nDP)
{
	u32 n,i;
	if(FN<0.0)
		{
			Charlcd('-');
			FN=-FN;
		}
		n=FN;
		u32lcd(n);
		Charlcd('.');
		for(i=0;i<nDP;i++)
		{
			FN=(FN-n)*10;
			n=FN;
			Charlcd(n+48);
		}
}
void BuildCGRAM(u8 *p,u8 nBytes)
{
	u32 i;
	Cmdlcd(GOTO_CGRAM_START);
	IOCLR0=1<<LCD_RW;
	for(i=0;i<nBytes;i++)
	{
		Writelcd(p[i]);
	}
	Cmdlcd(GOTO_LINE1_POS0);
}





