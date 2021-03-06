// # ---------------------------------------------------------------------------------------------
// #  $URL: https://eboracum-vss.digitallocksmiths.local/svn/Dls/Sean/RoyalHolloway/CC_Avr/Source/Utilities/Console.c $
// # ---------------------------------------------------------------------------------------------
// #  File:                  $Id: Console.c 320 2019-11-27 17:21:34Z sean $
// #  Last committed:  $Revision: 320 $
// # ---------------------------------------------------------------------------------------------

// Title: Console.c
// This file provides platform specific debugging routines.
//

//#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>  
//#include <winsock2.h>
#include <windows.h>

#include "Console.h"

char szOutString[1024];



// ##########################################################################
// #  Function: ConsoleClearScreen
// #        *public*, Wibble.
// #
// #
// #  Parameters:
// #        wibble - wibble.
// #
// #  Returns:
// #        wibble.
// #
// #  See Also:
// #        <wibble>
// #
// ######################################################################### 
BOOL    ConsoleClearScreen(void) {
    int                         hWrittenChars = 0;
    CONSOLE_SCREEN_BUFFER_INFO  strConsoleInfo;
    COORD                       Home;

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); // Make a handle

    Home.X = 0;
    Home.Y = 0;

    GetConsoleScreenBufferInfo(handle, &strConsoleInfo);
    FillConsoleOutputCharacter(handle, ' ', strConsoleInfo.dwSize.X - 2 * strConsoleInfo.dwSize.Y, Home, &hWrittenChars);
    SetConsoleCursorPosition(handle, Home);
    return FALSE;

}


// ##########################################################################
// #  Function: DebugSetColour
// #        Change the printing colour.
// #
// #
// #  Parameters:
// #        s16 a  - Colour to use in printf.
// #
// #  Returns:
// #        nothing.
// #
// #  See Also:
// #        <ConsolePrintf>
// #
// #  Available colours are ...
// #        * 0 - BLACK
// #        * 1 - BLUE
// #        * 2 - GREEN
// #        * 3 - CYAN
// #        * 4 - RED
// #        * 5 - MAGENTA
// #        * 6 - YELLOW
// #        * 7 - WHITE
// #        * 8 - BRIGHT
// #
// ######################################################################### 
void ConsoleSetColour(int a) {
     HANDLE handle = GetStdHandle( STD_OUTPUT_HANDLE ); // Make a handle
     SetConsoleTextAttribute( handle, a );              // Set the color of the text
}

// ##########################################################################
// #  Function: ConsolePrintf
// #        Function just like the <stdio.h> printf.
// #        Used to permit debug printing from the <ITSO Library>
// #        without generating a dependency on a host function from 
// #        within the library.
// #
// #        This function can be replaced on a host by host basis
// #
// #  Parameters:
// #
// #        const char *format - printf format string
// #        ...                - and number of parameters 
// #
// #  Returns:
// #        The number of characters printed.
// #
// #  See Also:
// #        <ConsolePrintf>
// #
// ######################################################################### 

int ConsolePrintf( int nColour, const char *pbFormat, ...) {
    va_list ArgList;
    int n;

    ConsoleSetColour(nColour);
    
    va_start(ArgList, pbFormat);
    _vsnprintf_s(szOutString, sizeof(szOutString), _TRUNCATE, pbFormat, ArgList);
    szOutString[sizeof(szOutString)-1] = 0;

    n = printf(szOutString);
    ConsoleSetColour(CON_WHITE);
    return n;
}


// ##########################################################################
// #  Function: ConsoleIndent
// #        Indent a given number of four character byte blocks
// #
// #  Parameters:
// #
// #        int iDepth - Indent size
// #
// #  Returns:
// #        nothing.
// #
// #  See Also:
// #        <ConsolePrintf>
// #
// ######################################################################### 
void    ConsoleIndent(int iDepth) {
    while (iDepth--) {
        printf("    ");
    }
}

/* eof */
