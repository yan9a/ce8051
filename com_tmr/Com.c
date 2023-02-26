//#############################################################################
//Transmits and receives serial data
//File Name   : Com.c
//Programmer  : Yan Naing Aye
//Date        : 17 August 2009
//WebSite: http://cool-emerald.blogspot.sg/
//License: Creative Commons Attribution-ShareAlike 3.0
//         http://creativecommons.org/licenses/by-sa/3.0/ 
//#############################################################################
//#define COM_C
#include "Headers.h"
//*****************************************************************************
volatile ui08 rbin=0,rbout=0;
ui08 rbuf[RX_BUF_SIZE];
volatile ui08 tbin=0,tbout=0;
ui08 tbuf[TX_BUF_SIZE];
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//used in non-critical section
bool ComIsTxBufFull()
{
	bool f;
	SysDI();//Enter critical section
	f= (((tbin+1)& (TX_BUF_SIZE-1))==tbout);
	SysEI();//Exit critical section
	return f;
}
//-----------------------------------------------------------------------------
//used in critical section
bool ComIsTxBufEmpty()
{
	return (tbin==tbout);
}
//-----------------------------------------------------------------------------
//used in critical section
ui08 ComTxPop()
{
	ui08 ch;
	ch=tbuf[tbout];
	tbout=(++tbout) & (TX_BUF_SIZE-1);
	return ch;
}
//-----------------------------------------------------------------------------
//used in non-critical section
void ComTxPush(ui08 ch)
{
	//-------------------------------------------------------------------------
	SysDI();//Enter critical section
	tbuf[tbin]=ch;
    tbin=(++tbin) & (TX_BUF_SIZE-1);
    SysEI();//Exit critical section
    //-------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------
/*
bool ComIsRxBufFull()
{
	SysDI();//Enter critical section
	f=  (((rbin+1)& (RX_BUF_SIZE-1))==rbout);
	SysEI();//Exit critical section
	return f;
}
*/
//-----------------------------------------------------------------------------
//used in non-critical section
bool ComIsRxBufEmpty()
{
	bool f;
	SysDI();//Enter critical section
	f= (rbout==rbin);
	SysEI();//Exit critical section
	return f;
}
//-----------------------------------------------------------------------------
//used in non-critical section
ui08 ComRxPop()
{
	ui08 ch;
	SysDI();//Enter critical section
	ch=rbuf[rbout];
	rbout=(++rbout) & (RX_BUF_SIZE-1);
	SysEI();//Exit critical section
	return ch;
}
//-----------------------------------------------------------------------------
//used in critical section
void ComRxPush(ui08 ch)
{
	//while(ComIsRxBufFull()) //never check RxBuf
	//i.e., Discard Policy=> discard old data
	rbuf[rbin]=ch;//put received character into the buffer
    rbin=(++rbin) & (RX_BUF_SIZE-1);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//Polled regularly by main(), check the serial input buffer if 
//there is any input char and then pass these chars to ComRxEvent()
void ComChkRx(void)
{
	//while rx buf is not empty
    while(ComIsRxBufEmpty()==FALSE) Com_Rx(ComRxPop());
}
//-----------------------------------------------------------------------------
//put the char into the transmit buffer and start transmission
ui08 ComPutch(ui08 ch)
{
    while(ComIsTxBufFull());//wait when the buffer is full
    ComTxPush(ch);	     
    SysComTxCheck();    
    return ch;
}
//-----------------------------------------------------------------------------
void ComPrint(char *s)
{
    for(;*s;s++) ComPutch(*s);
}
//-----------------------------------------------------------------------------
/*
void ComPrintHex(ui08 ch)
{
    ui08 a;

    a=(ch >> 4) | 0x30;
    if(a>0x39) a+=7;
    ComPutch(a);

    a=(ch & 0x0F) | 0x30;
    if(a>0x39) a+=7;
    ComPutch(a);
}
*/
//-----------------------------------------------------------------------------
