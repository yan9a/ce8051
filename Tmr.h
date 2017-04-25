//#############################################################################
//File Name   : Tmr.h
//Programmer  : Yan Naing Aye
//Date        : 14 August 2009
//WebSite: http://cool-emerald.blogspot.sg/
//License: Creative Commons Attribution-ShareAlike 3.0
//         http://creativecommons.org/licenses/by-sa/3.0/
//#############################################################################
#ifndef	TMR_H
	#define	TMR_H
//-----------------------------------------------------------------------------
    void TmrInit();
    void TmrTask();
    void TmrSetInterval(ui08 TmrNo,ui16 Interval);
    void TmrReset(ui08 TmrNo);
    void TmrStart(ui08 TmrNo);
    void TmrStop(ui08 TmrNo);
    ui16 TmrChk(ui08 TmrNo);
    void TmrSignalTmr();
//-----------------------------------------------------------------------------
#endif
