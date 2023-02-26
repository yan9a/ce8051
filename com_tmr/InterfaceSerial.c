//#############################################################################
//Interface to serial com
//File Name   : InterfaceSerial.c
//Programmer  : Yan Naing Aye
//Date        : 20 August 2009
//WebSite: http://cool-emerald.blogspot.sg/
//License: Creative Commons Attribution-ShareAlike 3.0
//         http://creativecommons.org/licenses/by-sa/3.0/
//#############################################################################
#include "Headers.h"
//*****************************************************************************
void IfsProcessChar(ui08 ch)
{
	ComPutch(ch);//echo char back
}
//-----------------------------------------------------------------------------
