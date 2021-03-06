// # $URL: https://eboracum-vss.digitallocksmiths.local/svn/Dls/Sean/RoyalHolloway/CC_Avr/Source/Lex.h $
// # $Revision: 317 $

#ifndef __SKC_LEX_H__
#define __SKC_LEX_H__

#ifdef DEBUG_INCLUDE_FILES 
#pragma message("     including " __FILE__)
#endif // DEBUG_INCLUDE_FILES

#define LINESIZE 256			// max text line size.

LPVOID	New(INT n);
void	Dispose(LPVOID n);

BOOL	StartInput(LPSTR Name);
BOOL	EndInput(void);
int     yylex(void);

extern  DWORD   LineNo;
extern  DWORD   LinePos;
extern  CHAR    CurrentLine[LINESIZE];
extern  CHAR    PreviousLine[LINESIZE];



#endif // __SKC_LEX_H__

/* eof */

