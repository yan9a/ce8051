//#############################################################################
//File Name   : SystemConfig.h
//Programmer  : Yan Naing Aye
//Date        : 14 August 2009
//WebSite: http://cool-emerald.blogspot.sg/
//License: Creative Commons Attribution-ShareAlike 3.0
//         http://creativecommons.org/licenses/by-sa/3.0/
//#############################################################################
//-----------------------------------------------------------------------------
#ifndef	SYSTEMCONFIG_H
	#define	SYSTEMCONFIG_H
//-----------------------------------------------------------------------------
	#define XTAL_FREQ 12000000//in Hz   (12 MHz)

	#define TMR_TICK_INTVERVAL 0.01//in second (10 ms)
    
	#ifdef SDCC//defined by the compiler
		#define SBLED P3_4
	#else
		sbit SBLED=P3^4; //Pin definition for Standby LED
	#endif

//-----------------------------------------------------------------------------
    //Extended features
    #define USE_X2_CLK YES//to use X2 clock in supported MCU
    #if USE_X2_CLK==YES
        #define SYS_CLK_DIV 6//system clock divider
    #else
        #define SYS_CLK_DIV 12//system clock divider
    #endif
    #define USE_ON_CHIP_XRAM NO//to use on chip XRAM
//-----------------------------------------------------------------------------
#endif
