//#############################################################################
//File Name   : Com.h
//Programmer  : Yan Naing Aye
//Date        : 17 August 2009
//WebSite: http://cool-emerald.blogspot.sg/
//License: Creative Commons Attribution-ShareAlike 3.0
//         http://creativecommons.org/licenses/by-sa/3.0/ 
//#############################################################################
#ifndef	COM_H
	#define	COM_H	
//-----------------------------------------------------------------------------
    void ComChkRx(void);
    ui08 ComPutch(ui08 c);
    void ComPrint(char *s);
    void ComPrintHex(ui08 ch);
    bool ComIsTxBufFull();
    bool ComIsTxBufEmpty();
    ui08 ComTxPop();
    void ComTxPush(ui08 c);
    bool ComIsRxBufFull();
    bool ComIsRxBufEmpty();
    ui08 ComRxPop();
    void ComRxPush(ui08 c);
//-----------------------------------------------------------------------------
#endif