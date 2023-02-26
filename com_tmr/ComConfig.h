//#############################################################################
//File Name   : ComConfig.h
//Programmer  : Yan Naing Aye
//Date        : 17 August 2009
//WebSite: http://cool-emerald.blogspot.sg/
//License: Creative Commons Attribution-ShareAlike 3.0
//         http://creativecommons.org/licenses/by-sa/3.0/ 
//#############################################################################
#ifndef	COMCONFIG_H
	#define	COMCONFIG_H	
//-----------------------------------------------------------------------------
	//Step 1: Define buffer sizes in 2 power n
    #define RX_BUF_SIZE 8//receive buffer length
    #define TX_BUF_SIZE 8//transmit buffer length
//-----------------------------------------------------------------------------
	//Step 2: Define a function to call on receive event
	//Signature of receive char event function
	//void Com_Rx(ui08 ch);
	#define Com_Rx IfsProcessChar
//-----------------------------------------------------------------------------
	//For 8051 : Define data type for com buffers in its c file
//-----------------------------------------------------------------------------

#endif
