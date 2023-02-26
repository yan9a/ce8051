//#############################################################################
//Main program
//File Name   : Main.c
//Programmer  : Yan Naing Aye
//Date        : 14 August 2009
//WebSite: http://cool-emerald.blogspot.sg/
//License: Creative Commons Attribution-ShareAlike 3.0
//         http://creativecommons.org/licenses/by-sa/3.0/ 
//#############################################################################
#include "Headers.h"
//-----------------------------------------------------------------------------
void main()
{
    SysInit();
    TmrInit();//Must be the first
	SysTmrInit();
    SysComInit();
    SysSBYLEDInit();
	SysComOpen(9600,'N');//Baud=9600, Parity='N', Always 1 stop bit
	ComPrint("\nCom template V1.");
	while(1)
    {
    //-------------------------------------------------------------------------
        //Timer task
        TmrTask();
    //-------------------------------------------------------------------------
        //Com task
        ComChkRx();
    //-------------------------------------------------------------------------
    }
}
//-----------------------------------------------------------------------------
