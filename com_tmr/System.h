//#############################################################################
//File Name   : System.h
//Programmer  : Yan Naing Aye
//Date        : 14 August 2009
//WebSite: http://cool-emerald.blogspot.sg/
//License: Creative Commons Attribution-ShareAlike 3.0
//         http://creativecommons.org/licenses/by-sa/3.0/
//#############################################################################
//-----------------------------------------------------------------------------
#ifndef	SYSTEM_H
	#define	SYSTEM_H
//-----------------------------------------------------------------------------
	#ifdef SDCC//defined by the compiler
		void Timer0Int(void) interrupt 1;
		void ComInterrupt(void) interrupt 4;
		#include <at89c51ed2.h>
	#else
		//#include <REG52.H>
		#include <at89c51xd2.h>
	#endif
//-----------------------------------------------------------------------------
    typedef unsigned char bool;
    typedef unsigned char ui08;
    typedef signed char   si08;
    typedef unsigned int  ui16;
    typedef signed int    si16;
    typedef unsigned long ui32;
    typedef signed long   si32;
    typedef float         fp32;
    //typedef double        fp64;
//-----------------------------------------------------------------------------
	#define SysDI() (EA=0)//disable all interrupts
    #define SysEI() (EA=1)//enable all interrupts

    #define FALSE 0
    #define TRUE 1//(!FALSE)

    #define YES 1
    #define NO 0

    #define ENABLE 1
    #define DISABLE 0
//-----------------------------------------------------------------------------
	void SysInit();
    void SysTmrInit();
    void SysSBYLEDTmrTO();
    void SysSBYLEDInit();
    void SysComInit();
    void SysComOpen(ui32 BaudRate,char Parity);
    void SysComTxCheck();
//-----------------------------------------------------------------------------
#endif
