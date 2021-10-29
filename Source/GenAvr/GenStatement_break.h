// # $URL: https://eboracum-vss.digitallocksmiths.local/svn/Dls/Sean/RoyalHolloway/CC_Avr/Source/GenStatements.h $
// # $Revision: 401 $


#ifndef __SKC_GEN_STATEMENTS_BREAK_H__
#define __SKC_GEN_STATEMENTS_BREAK_H__

#ifdef DEBUG_INCLUDE_FILES 
#pragma message("     including " __FILE__)
#endif // DEBUG_INCLUDE_FILES


void GenBreak(FILE *hOut, int iDepth, TPStatement pStat, LPSTR pszFunctionName, LPSTR pszExitLabel, LPSTR pszBreakLabel, LPSTR pszContinueLabel);


#endif // __SKC_GEN_STATEMENTS_BREAK_H__

/* eof */
