// # $URL: https://eboracum-vss.digitallocksmiths.local/svn/Dls/Sean/RoyalHolloway/CC_Avr/Source/Main.h $
// # $Revision: 425 $


#ifndef __SKC_MAIN_H__
#define __SKC_MAIN_H__

#ifdef DEBUG_INCLUDE_FILES 
#pragma message("     including " __FILE__)
#endif // DEBUG_INCLUDE_FILES



typedef struct TagArgs {                                // settings extracted from the command line.
    BOOL    fVerbose;
    BOOL    fEcho;
    BOOL    fExpr;
    BOOL    fObjects;
    int     iDefendCallRet;
    int     iDefendBranches;
    int     iDefendConditionals;
} TArgs;
extern  TArgs CmdLine;

extern  FILE *hGlbOut;                                  // target file for generated code.


typedef enum { WARNING0, WARNING1, WARNINGX, ERROR0, ERROR1, ERRORX, FATAL } TErrorType;
void Error(TErrorType e, const char *pbFormat, ...);

#define ASSERT(expression) if (!(expression)) { Error(FATAL, "\n    Source:    %s\n    Line:      %d.\n    Function:  %s\n    Condition: (%s)", __FILE__, __LINE__, __FUNCTION__, #expression ); }


#endif // __SKC_MAIN_H__

/* eof */

