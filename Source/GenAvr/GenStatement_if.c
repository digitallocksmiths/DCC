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
// #  Function: GenIf
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
void GenIf(FILE *hOut, int iDepth, TPStatement pStat, LPSTR pszFunctionName, LPSTR pszExitLabel, LPSTR pszBreakLabel, LPSTR pszContinueLabel) {
    LPSTR       szIfThenLabel = NULL;
    LPSTR       szIfElseLabel = NULL;
    LPSTR       szIfDoneLabel = NULL;

    LPSTR       szStatementRef = GenLabel("_Statement_If_");

    GenStatementIntro(hOut, pStat, pszFunctionName, "If", szStatementRef);

    if (pStat->Use._if.pCond == NULL) {
        Error(WARNINGX, "GenIf(): no condition in If statement");
        GenAsm("", "; ***** IF condition was missing ! no code generated", "", "");
        return;
    }

    ASSERT(IsBoolean(pStat->Use._if.pCond->pType));

    if (pStat->Use._if.pNo == NULL) {
        szIfThenLabel = GenLabel("_IfThen_");
        //szIfElseLabel = GenLabel("_IfElse_");
        szIfDoneLabel = GenLabel("_IfDone_");

        // GenExpressionConditional(hOut, pStat->Use._if.pCond, szIfThenLabel, szIfDoneLabel);                              //
        GenExpressionConditional(pStat->Use._if.pCond, NULL, szIfDoneLabel);                                                //
        GenAsm(szIfThenLabel, ";      If Then ------------", "", szStatementRef);                                           //  Then
        GenStatements(hOut, iDepth+1, pStat->Use._if.pYes, pszFunctionName, pszExitLabel, pszBreakLabel, pszContinueLabel); //      Body
    }
    else {
        szIfThenLabel = GenLabel("_IfThen_");
        szIfElseLabel = GenLabel("_IfElse_");
        szIfDoneLabel = GenLabel("_IfDone_");

        // GenExpressionConditional(hOut, pStat->Use._if.pCond, szIfThenLabel, szIfElseLabel);                              //
        GenExpressionConditional(pStat->Use._if.pCond, NULL,          szIfElseLabel);                                       //
        GenAsm(szIfThenLabel, ";      If Then ------------", "", szStatementRef);                                           //  Then
        GenStatements(hOut, iDepth+1, pStat->Use._if.pYes, pszFunctionName, pszExitLabel, pszBreakLabel, pszContinueLabel); //      Body
        GenAsm("", "rjmp", szIfDoneLabel, "1/2:");                                                                          //      exit
        GenAsm(szIfElseLabel, ";      If Else ------------", "", szStatementRef);                                           //  Else
        GenStatements(hOut, iDepth+1, pStat->Use._if.pNo, pszFunctionName, pszExitLabel, pszBreakLabel, pszContinueLabel);  //      Body
    }
    GenAsm(szIfDoneLabel, ";      If End --------------", "", szStatementRef);

    if (szIfDoneLabel) Dispose(szIfDoneLabel);
    if (szIfElseLabel) Dispose(szIfElseLabel);
    if (szIfThenLabel) Dispose(szIfThenLabel);
    Dispose(szStatementRef);
}


/* eof */
