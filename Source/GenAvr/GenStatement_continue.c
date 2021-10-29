// # $URL: https://eboracum-vss.digitallocksmiths.local/svn/Dls/Sean/RoyalHolloway/CC_Avr/Source/GenStatements.c $
// # $Revision: 402 $


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>

#include "..\Utilities\Console.h"

#include "..\lex.h"
#include "..\typectrl.h"
#include "..\expr.h"
#include "Gen.h"
#include "GenAsm.h"
#include "..\Statements.h"
#include "..\main.h"
#include "..\ExprOptimize.h"



// ##########################################################################
// #  Function: GenContinue
// #        <todo: task brief description>
// #
// #        <todo: task detailed description>
// #
// #  Parameters:
// #        <todo: params >
// #
// #  Returns:
// #        <todo: return Value>
// #
// #  See Also:
// #
// ##########################################################################
void GenContinue(FILE *hOut, int iDepth, TPStatement pStat, LPSTR pszFunctionName, LPSTR pszExitLabel, LPSTR pszBreakLabel, LPSTR pszContinueLabel) {
    GenStatementIntro(hOut, pStat, pszFunctionName, "Continue", "");
    if ((pszContinueLabel == NULL) || (*pszContinueLabel == '\0')) {
        Error(WARNINGX, "GenContinue(): Function '%s' continue ignored. It has no enclosing loop.", pszFunctionName);
        GenAsm("", "; ***** Unexpected continue statement found here ***", "", NULL);
        return;
    }
    GenAsm("", "rjmp", pszContinueLabel, "  2: continue");                              // Jmp cont
}


/* eof */
