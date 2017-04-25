//#############################################################################
//Hardware abstraction layer
//File Name   : System.c
//Programmer  : Yan Naing Aye
//Date: 14 August 2009
//WebSite: http://cool-emerald.blogspot.sg/
//License: Creative Commons Attribution-ShareAlike 3.0
//         http://creativecommons.org/licenses/by-sa/3.0/
//#############################################################################
#include "Headers.h"
//-----------------------------------------------------------------------------
#define TMR_RLCYCLES 40//number of machine cycle to reload timer value

ui08 mTH0Val;
ui08 mTL0Val;
ui08 ParityVal='N';
ui08 SysComSendActive=0;
//-----------------------------------------------------------------------------
void SysInit()
{
    #if USE_X2_CLK==YES
        CKCON0=0x01;
    #endif
    #if USE_ON_CHIP_XRAM==YES
        //Set XRAM size
        //AUXR=|DPU|--|M0|XRS2||XRS1|XRS0|EXTRAM|AO|
        //XRS2,XRS1,XRS0 = 010 (768 bytes -default)
        //now change to = 100 (1792 bytes)[Max for AT89C51ED2]
        //choose internal XRAM by clearing EXTRAM bit
        AUXR= (AUXR & 0xE1) | 0x10; //0xE3=111-0 00-0-1 B, 0x10=000-100-00 B
    #endif    
    EA=1;//Enable all interrupts
}
//-----------------------------------------------------------------------------
//(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
//Start of Soft-timers
//-----------------------------------------------------------------------------
//Uses timer 0
void SysTmrInit()
{
    ui32 T0Val;
    //TMOD: Timer/Counter Mode Control Register : Not bit addressable
    //TMOD= |GATE| C/_T | M1 | M0 | GATE | C/_T | M1 | M0 |
    //TMOD= |     TIMER 1         |        TIMER 0        |
    //Uses timer 0 in mode 1
    TMOD |= 0x01;

    T0Val=(ui32)0x10000-(((ui32)XTAL_FREQ*(fp32)TMR_TICK_INTVERVAL)/SYS_CLK_DIV)+(ui32)TMR_RLCYCLES;
    
    mTH0Val=(T0Val>>8) & 0xFF;
    mTL0Val=(T0Val & 0xFF);
    TH0=mTH0Val;
    TL0=mTL0Val;
    ET0= 1;//Enable timer 0 interrupt
    TR0= 1;//Run timer 0
}
//-----------------------------------------------------------------------------
//Timer tick ISR
void Timer0Int(void) interrupt 1
{	
    //For timer 0, to make interrupt every interval
    TR0 = 0;// Stop T0    
    TH0=mTH0Val;
    TL0=mTL0Val;
    TR0 = 1;// Start T0

    TmrSignalTmr();
}
//-----------------------------------------------------------------------------
//End of Soft-timers
//)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
//Start of Standby LED
//-----------------------------------------------------------------------------
//Blink at 0.5Hz
void SysSBYLEDTmrTO()
{
    SBLED^=1;
}
//-----------------------------------------------------------------------------
void SysSBYLEDInit()
{
    TmrSetInterval(SysSBYLEDTmr,100);//every 1 s
    TmrStart(SysSBYLEDTmr);
}
//-----------------------------------------------------------------------------
//End of Standby LED
//)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
//Start of Com
//-----------------------------------------------------------------------------
//Uses timer 1
void SysComInit()
{
    //PCON: Power Control Register : Not bit addressable
    //PCON= |SMOD| - | - | - | GF1 | GF0 | PD | IDL |
    //SMOD: double baud rate bit
    //      0: MCLK/32
    //      1: MCLK/16
    //Enable double baud rate bit
    PCON |= 0x80;

    //TMOD: Timer/Counter Mode Control Register : Not bit addressable
    //TMOD= |GATE| C/_T | M1 | M0 | GATE | C/_T | M1 | M0 |
    //TMOD= |     TIMER 1         |        TIMER 0        |
    //Uses timer 1- mode 2
    TMOD |= 0x20;
}
//-----------------------------------------------------------------------------
//Parameters
//BaudRate : Baud rate
//Parity   : 'N' for no parity, 'E' for even parity, 'O' for odd parity
//StopBit  : Number of stop bits
void SysComOpen(ui32 BaudRate,char Parity)
{
    ui32 T1Val;
    T1Val=(ui32)0x100-((((ui32)XTAL_FREQ/SYS_CLK_DIV)/BaudRate)>>4);

    TH1=T1Val & 0xFF;//store in global variables for later use

    ParityVal=Parity;
    //SCON: Serial Port Control Register : Bit addressable
    //SCON= |SM0| SM1 | SM2 | REN | TB8 | RB8 | TI | RI |
    //SM0 SM1: Serial mode specifier
    //         00 : shift register
    //         01 : 8 bit UART, variable baud
    //         10 : 9 bit UART, fixed baud
    //         11 : 9 bit UART, variable baud
    //SM2    : multiprocessor comm
    //REN    : Enable reception
    //TB8    : the 9 th bit that will be transmitted in modes 2 & 3
    //RB8    : received 9 th bit
    //TI     : transmit interrupt flag, must be cleared by software
    //RI     : receive interrupt flag, must be cleared by software
    //Enable double baud rate bit
    if(Parity=='N') SCON=0x50;//Mode 1 for 8 bit, enable receive
    else SCON=0xD0;//Mode 3 for 9 bit, enable receive

    ES=1;//Enable serial interrupt
    TR1=1;
}
//-----------------------------------------------------------------------------
void ComInterrupt(void) interrupt 4
{
    ui08 c;
    if(TI)
    {
        TI=0;
        if(SysComSendActive)
    	{
    		if(ComIsTxBufEmpty()==FALSE)
    		{
    			ACC=ComTxPop();
                TB8=P;
                c=ACC;
                if(ParityVal=='O') TB8^=1;
                SBUF=c;

    		}
    		else SysComSendActive=0;
    	}
    }
    if(RI)
    {
        ComRxPush(SBUF);
        RI=0;
    }
}
//-----------------------------------------------------------------------------
void SysComTxCheck()
{
	SysDI();//Enter critical section
	if(!SysComSendActive)
	{
		if(ComIsTxBufEmpty()==FALSE)
		{
			SysComSendActive=1;
			TI=1;
		}
	}
	SysEI();
}
//-----------------------------------------------------------------------------
//End of Com
//)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))
//-----------------------------------------------------------------------------
