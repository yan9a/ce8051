//#############################################################################
//File Name   : TmrConfig.h
//Programmer  : Yan Naing Aye
//Date        : 14 August 2009
//WebSite: http://cool-emerald.blogspot.sg/
//License: Creative Commons Attribution-ShareAlike 3.0
//         http://creativecommons.org/licenses/by-sa/3.0/
//#############################################################################
#ifndef	TMRCONFIG_H
	#define	TMRCONFIG_H
//-----------------------------------------------------------------------------
    //STEP 1: Define number of timers
    #define TMR_MAX 1
    //END of STEP 1
    //_________________________________________________________________________
    //STEP 2: Give timer names and use them instead of numbers
	#define SysSBYLEDTmr 0
    //END of STEP 2
    //_________________________________________________________________________
    #ifdef TMR_C
        #undef TMR_C
        //list of time out functions
		#ifdef SDCC//defined by the compiler
			void (*fp_tab []) (void) =
		#else
			code void (code *fp_tab []) (void) =
		#endif
					{
    //_________________________________________________________________________
    //STEP 3: Define functions to call on time out
							SysSBYLEDTmrTO //Time out function for timer 0
							//,func1
							//,func2
							//,func3
    //END of STEP 3
    //_________________________________________________________________________
					};
    #endif
    //_________________________________________________________________________
    //For 8051 : Define data type for timer data in its c file	
//-----------------------------------------------------------------------------
#endif
