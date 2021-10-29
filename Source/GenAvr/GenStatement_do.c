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
// #  Function: GenDo
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
void GenDo(FILE *hOut, int iDepth, TPStatement pStat, LPSTR pszFunctionName, LPSTR pszExitLabel, LPSTR pszBreakLabel, LPSTR pszContinueLabel) {
    LPSTR       szNewDoAgainLabel = GenLabel("_DoAgain_");
    LPSTR       szNewDoTestLabel  = GenLabel("_DoTest_");
    LPSTR       szNewDoBreakLabel = GenLabel("_DoBreak_");
    LPSTR       szStatementRef    = GenLabel("_Statement_Do_");

    GenStatementIntro(hOut, pStat, pszFunctionName, "Do", szStatementRef);
    GenAsm(szNewDoAgainLabel, ";      Do Body ------------", "", szStatementRef);
    GenStatements(hOut, iDepth+1, pStat->Use._do.pAction, pszFunctionName, pszExitLabel, szNewDoBreakLabel, szNewDoTestLabel);

    if (pStat->Use._do.pCond != NULL) {
        GenAsm(szNewDoTestLabel, ";      Do test -------------", "", szStatementRef);
        GenExpressionConditional(pStat->Use._do.pCond, szNewDoAgainLabel, NULL);
    }
    else {
        Error(WARNINGX, "GenDo(): no condition in do statement");
        GenAsm(szNewDoTestLabel, "; ***** DO condition was missing !", "", "");
    }

    GenAsm(szNewDoBreakLabel, ";      Do end --------------", "", szStatementRef);

    Dispose(szStatementRef);
    Dispose(szNewDoBreakLabel);
    Dispose(szNewDoTestLabel);
    Dispose(szNewDoAgainLabel);
}

/* eof */
