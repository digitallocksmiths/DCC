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
// #  Function: GenBreak
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
void GenBreak(FILE *hOut, int iDepth, TPStatement pStat, LPSTR pszFunctionName, LPSTR pszExitLabel, LPSTR pszBreakLabel, LPSTR pszContinueLabel) {
    GenStatementIntro(hOut, pStat, pszFunctionName, "Break", "");
    if ((pszBreakLabel == NULL) || (*pszBreakLabel == '\0')) {
        Error(WARNINGX, "GenBreak(): Function '%s' break ignored. It has no enclosing compound statement.", pszFunctionName);
        GenAsm("", "; ***** Unexpected break statement found here ***", "", NULL);
        return;
    }
    GenAsm("", "rjmp", pszBreakLabel, "  2: break");                                    // Jmp break
}

/* eof */
