// # ---------------------------------------------------------------------------------------------
// #  $URL: https://eboracum-vss.digitallocksmiths.local/svn/Dls/Sean/RoyalHolloway/CC_Avr/Source/Utilities/Console.h $
// # ---------------------------------------------------------------------------------------------
// #  File:                  $Id: Console.h 310 2019-11-21 11:22:14Z sean $
// #  Last committed:  $Revision: 310 $
// # ---------------------------------------------------------------------------------------------

// Title: Console.h
// 
//  Implementation details.
//
//

#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#ifdef DEBUG_INCLUDE_FILES 
#pragma message("     including " __FILE__)
#endif // DEBUG_INCLUDE_FILES


#ifdef __cplusplus
extern "C" {
#endif


#define CON_BLACK       0
#define CON_BLUE        1
#define CON_GREEN       2
#define CON_CYAN        3
#define CON_RED         4
#define CON_MAGENTA     5
#define CON_YELLOW      6
#define CON_WHITE       7
#define CON_BRIGHT      8

#define CON_BLACK_BRIGHT       (CON_BLACK+CON_BRIGHT)
#define CON_BLUE_BRIGHT        (CON_BLUE+CON_BRIGHT)
#define CON_GREEN_BRIGHT       (CON_GREEN+CON_BRIGHT)
#define CON_CYAN_BRIGHT        (CON_CYAN+CON_BRIGHT)
#define CON_RED_BRIGHT         (CON_RED+CON_BRIGHT)
#define CON_MAGENTA_BRIGHT     (CON_MAGENTA+CON_BRIGHT)
#define CON_YELLOW_BRIGHT      (CON_YELLOW+CON_BRIGHT)
#define CON_WHITE_BRIGHT       (CON_WHITE+CON_BRIGHT)



    extern BOOL     ConsoleClearScreen(void);
    extern void     ConsoleSetColour(int a);
    extern int      ConsolePrintf( int iColour, const char *pbFormat, ...);
    extern void     ConsoleIndent(int iDepth);

#ifdef __cplusplus
}
#endif

#endif // __CONSOLE_H__

/* eof */




