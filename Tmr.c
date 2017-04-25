//#############################################################################
//Soft timers
//File Name   : Tmr.c
//Programmer  : Yan Naing Aye
//Date        : 14 August 2009
//WebSite: http://cool-emerald.blogspot.sg/
//License: Creative Commons Attribution-ShareAlike 3.0
//         http://creativecommons.org/licenses/by-sa/3.0/
//#############################################################################
//TmrSignalTmr() is to be called every tick interval by an interrupt
//TmrTask() is to be polled regularly e.g., by main()
//*****************************************************************************
#define TMR_C
#include "Headers.h"
//-----------------------------------------------------------------------------
volatile ui08 TmrTickCtr=0;
//-----------------------------------------------------------------------------
typedef struct {
                    bool TmrEN;
                    ui16 TmrTick;//to keep track elasped time
                    ui16 TmrTimeOutInterval;//time out interval
                } TMRSOFT;
TMRSOFT T[TMR_MAX];//declare timers array
//-----------------------------------------------------------------------------
//Call TmrSignalTmr() every tick interval by an interrupt
void TmrSignalTmr()
{
    TmrTickCtr++;
}
//-----------------------------------------------------------------------------
//TmrTask() is to be polled regularly e.g., by main()
void TmrTask()
{
    ui08 i;
    bool f=FALSE;
    TMRSOFT *ptmr;
    ptmr=&T[0];

    SysDI();
    if(TmrTickCtr)
    {
        TmrTickCtr--;//TmrTickCtr increases every interval, decrease it to 0 again
        f=TRUE;
    }
    SysEI();

    if(f)//if there was increase in TmrTickCtr
    {
        for(i=0;i<TMR_MAX;i++,ptmr++)
        {
            if(ptmr->TmrEN)//if it is enabled
            {
                if(--(ptmr->TmrTick)==0)//accuracy <= one TmrTick interval
                {
                    ptmr->TmrTick=ptmr->TmrTimeOutInterval;//restart
                    (*fp_tab[i])();   //call time out function
                }
            }
        }
    }
}
//-----------------------------------------------------------------------------
//Initializes all timers
void TmrInit()
{
    ui08 i;
    TMRSOFT *ptmr;
    ptmr=&T[0];
    for(i=0;i<TMR_MAX;i++,ptmr++)//init every timer in the timer array
    {
        ptmr->TmrEN=FALSE;
        ptmr->TmrTimeOutInterval=100;
        ptmr->TmrTick=ptmr->TmrTimeOutInterval;
    }
    TmrTickCtr=0;
}
//-----------------------------------------------------------------------------
//Sets timer interval
void TmrSetInterval(ui08 TmrNo,ui16 Interval)
{
    TMRSOFT *ptmr;
    if(TmrNo<TMR_MAX)
    {
        ptmr=&T[TmrNo];
        ptmr->TmrTimeOutInterval=Interval;
        ptmr->TmrTick=ptmr->TmrTimeOutInterval;
    }
}
//-----------------------------------------------------------------------------
//Starts a timer
void TmrStart(ui08 TmrNo)
{
    TMRSOFT *ptmr;
    if(TmrNo<TMR_MAX)
    {
        ptmr=&T[TmrNo];
        ptmr->TmrEN=TRUE;
    }
}
//-----------------------------------------------------------------------------
/*
//Stops a timer
void TmrStop(ui08 TmrNo)
{
    TMRSOFT *ptmr;
    if(TmrNo<TMR_MAX)
    {
        ptmr=&T[TmrNo];
        ptmr->TmrEN=FALSE;
    }
}
//-----------------------------------------------------------------------------
//Reloads a timer with its initial value
void TmrReset(ui08 TmrNo)
{
    TMRSOFT *ptmr;
    if(TmrNo<TMR_MAX)
    {
        ptmr=&T[TmrNo];
        ptmr->TmrTick=ptmr->TmrTimeOutInterval;
    }
}
//-----------------------------------------------------------------------------
//Get current tick count
ui16 TmrChk(ui08 TmrNo)
{
    ui16 cTick;
    TMRSOFT *ptmr;
    if(TmrNo<TMR_MAX)
    {
        ptmr=&T[TmrNo];
        cTick=ptmr->TmrTick;
    }
    return cTick;
}
*/
//-----------------------------------------------------------------------------
