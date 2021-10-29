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
// #  Function: GenWhile
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
void GenWhile(FILE *hOut, int iDepth, TPStatement pStat, LPSTR pszFunctionName, LPSTR pszExitLabel, LPSTR pszBreakLabel, LPSTR pszContinueLabel) {
    LPSTR       szStatementRef = GenLabel("_Statement_While_");

    GenStatementIntro(hOut, pStat, pszFunctionName, "While", szStatementRef);

    if (pStat->Use._while.pCond == NULL) {
        Error(WARNINGX, "GenWhile(): no condition in while statement");
        GenAsm("", "; ***** WHILE condition was missing ! no code generated", "", "");
        return;
    }

    LPSTR       szNewWhileTestLabel = GenLabel("_WhileTest_");
    GenAsm(szNewWhileTestLabel, ";      While Condition ----", "", szStatementRef);
    if (pStat->Use._while.pAction == NULL) {                                                    // ? no body so 
        GenExpressionConditional(pStat->Use._while.pCond, szNewWhileTestLabel, NULL);           //      true->repeat, false->fall out. 
        GenAsm("", ";      While end -----------", "", szStatementRef);                         //
    }                                                                                           //
    else {                                                                                      // ? body
        LPSTR       szNewWhileBreakLabel = GenLabel("_WhileBreak_");
        GenExpressionConditional(pStat->Use._while.pCond, NULL, szNewWhileBreakLabel);          //      true->fall into body, false->exit 
        GenStatements(hOut, iDepth+1, pStat->Use._while.pAction, pszFunctionName, pszExitLabel, szNewWhileBreakLabel, szNewWhileTestLabel);
        GenAsm("", "rjmp", szNewWhileTestLabel, "1/2:");                                        // Jmp break

        GenAsm(szNewWhileBreakLabel, ";      While end -----------", "", szStatementRef);
        Dispose(szNewWhileBreakLabel);
    }

    Dispose(szNewWhileTestLabel);
    Dispose(szStatementRef);
}

/* eof */
