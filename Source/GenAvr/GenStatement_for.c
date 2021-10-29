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
// #  Function: GenFor
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
void GenFor(FILE *hOut, int iDepth, TPStatement pStat, LPSTR pszFunctionName, LPSTR pszExitLabel, LPSTR pszBreakLabel, LPSTR pszContinueLabel) {
    LPSTR       szTestLabel        = GenLabel("_ForTest_");
    LPSTR       szForBodyLabel     = GenLabel("_ForBody_");
    LPSTR       szNewContinueLabel = GenLabel("_ForCont_");
    LPSTR       szNewBreakLabel    = GenLabel("_ForBreak_");
    LPSTR       szStatementRef     = GenLabel("_Statement_For_");

    GenStatementIntro(hOut, pStat, pszFunctionName, "For", szStatementRef);
    if (pStat->Use._for.pInit != NULL) {
        GenExpression(pStat->Use._for.pInit);
    }

    GenAsm(szTestLabel, ";      For Test ------------", "", szStatementRef);
    if (pStat->Use._for.pCond != NULL) {
        GenExpressionConditional(pStat->Use._for.pCond, NULL, szNewBreakLabel);
    }

    GenAsm(szForBodyLabel, ";      For Body ------------", "", szStatementRef);
    GenStatements(hOut, iDepth+1, pStat->Use._for.pAction, pszFunctionName, pszExitLabel, szNewBreakLabel, szNewContinueLabel);

    GenAsm(szNewContinueLabel,";      For Body end --------", "", szStatementRef);
    if (pStat->Use._for.pRepeat != NULL) {
        GenExpression(pStat->Use._for.pRepeat);
    }

    GenAsm("", "rjmp", szTestLabel, "  2:");                    // Jmp again

    GenAsm(szNewBreakLabel,   ";      For End -------------", "", szStatementRef);

    Dispose(szTestLabel);
    Dispose(szForBodyLabel);
    Dispose(szNewContinueLabel);
    Dispose(szNewBreakLabel);
    Dispose(szStatementRef);
}

/* eof */
