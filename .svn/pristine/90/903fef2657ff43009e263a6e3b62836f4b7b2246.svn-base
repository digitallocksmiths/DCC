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
// #  Function: GenSwitch
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
void GenSwitch(FILE *hOut, int iDepth, TPStatement pStat, LPSTR pszFunctionName, LPSTR pszExitLabel, LPSTR pszBreakLabel, LPSTR pszContinueLabel) {
    LPSTR       pszNewBreakLabel = GenLabel("_Break_");
    LPSTR       pszCaseTestLabel = GenLabel("_Case_");
    LPSTR       pszCaseBodyLabel = GenLabel("_Body_");
    LPSTR       szStatementRef = GenLabel("_Statement_Switch_");

    char        szOperand[32];
    char        szComment[32];
    char        szTestLabel[32];
    char        szBodyLabel[32];
    int         iTestCount;
    int         iBodyCount;

    TPStatement pCase;
    GenStatementIntro(hOut, pStat, pszFunctionName, "Switch", szStatementRef);
    GenExpression(pStat->Use._switch.pExpr);

    int nExprTypeSize = CalcSizeOf(pStat->Use._switch.pExpr->pType);

    iTestCount = 1;
    iBodyCount = 1;
    sprintf(szTestLabel, "%s_%d", pszCaseTestLabel, iTestCount++);
    sprintf(szBodyLabel, "%s_%d", pszCaseBodyLabel, iBodyCount++);

    sprintf(szTestLabel, "%s_%d", pszCaseTestLabel, iTestCount++);
    for (pCase = pStat->Use._switch.pBody; pCase != NULL; pCase = pCase->pNext) {
        ASSERT(pCase->Usage == StatementCASE);
        
        if (pCase->Use._case.pExpr != NULL) {                                                   // case
            long lVal;
            ASSERT(pCase->Use._case.pExpr->Usage == uConst);
            switch (nExprTypeSize) {
            case 1: lVal = (pCase->Use._case.pExpr->Use.Const.lInteger & 0xFF);
                    sprintf(szOperand, "r%d, 0x%02x", REG_ACC0, lVal);
                    sprintf(szComment, "  1: -> Case %d", lVal);
                    GenAsm("", "cpi", szOperand, szComment);
                    GenAsm("", "breq", szBodyLabel, "1/2:");
                    break;
            case 2: lVal = (pCase->Use._case.pExpr->Use.Const.lInteger & 0xFFFF);
                    sprintf(szOperand, "r%d, 0x%02x", REG_ACC0, (lVal&0xFF));
                    sprintf(szComment, "  1: -> Case %d", lVal);
                    GenAsm(szTestLabel, "cpi", szOperand, szComment);
                    sprintf(szTestLabel, "%s_%d", pszCaseTestLabel, iTestCount++);
                    GenAsm("", "brne", szTestLabel, "1/2:");
                    sprintf(szOperand, "r%d, 0x%02x", REG_ACC1, ((lVal>>8) & 0xFF));
                    GenAsm("", "cpi", szOperand, "  1:");
                    GenAsm("", "breq", szBodyLabel, "1/2:");
                    break;
            case 4: lVal = pCase->Use._case.pExpr->Use.Const.lInteger;
                    sprintf(szOperand, "r%d, 0x%02x", REG_ACC0, (lVal & 0xFF));
                    sprintf(szComment, "  1: -> Case %ld", lVal);
                    GenAsm(szTestLabel, "cpi", szOperand, szComment);
                    sprintf(szTestLabel, "%s_%d", pszCaseTestLabel, iTestCount++);
                    GenAsm("", "brne", szTestLabel, "1/2:");
                    
                    sprintf(szOperand, "r%d, 0x%02x", REG_ACC1, ((lVal >> 8) & 0xFF));
                    GenAsm("", "cpi", szOperand, "  1:");
                    GenAsm("", "brne", szTestLabel, "1/2:");
                    
                    sprintf(szOperand, "r%d, 0x%02x", REG_ACC2, ((lVal >> 16) & 0xFF));
                    GenAsm("", "cpi", szOperand, "  1:");
                    GenAsm("", "brne", szTestLabel, "1/2:");

                    sprintf(szOperand, "r%d, 0x%02x", REG_ACC3, ((lVal >> 24) & 0xFF));
                    GenAsm("", "cpi", szOperand, "  1:");
                    GenAsm("", "breq", szBodyLabel, "1/2:");
                    break;
            default: Error(FATAL, "GenSwitch(): wierd size");
            }
            if (pCase->Use._case.pBody != NULL) {
                sprintf(szBodyLabel, "%s_%d", pszCaseBodyLabel, iBodyCount++);
            }
        }
        else {                                                                                  // default
            if (nExprTypeSize == 1) {
                GenAsm("", "rjmp", szBodyLabel, "  2: -> Default");
            }
            else {
                GenAsm(szTestLabel, "rjmp", szBodyLabel, "  2: -> Default");
            }
        }
    }

    iBodyCount = 1;
    sprintf(szBodyLabel, "%s_%d", pszCaseBodyLabel, iBodyCount++);

    for (pCase = pStat->Use._switch.pBody; pCase != NULL; pCase = pCase->pNext) {

        if (pCase->Use._case.pExpr != NULL) {                                                   // case
            if (pCase->Use._case.pBody != NULL) {
                GenAsm(szBodyLabel, ";      Case ----------------", "", szStatementRef);
                GenStatements(hOut, iDepth+1, pCase->Use._case.pBody, pszFunctionName, pszExitLabel, pszNewBreakLabel, pszContinueLabel);
                sprintf(szBodyLabel, "%s_%d", pszCaseBodyLabel, iBodyCount++);
            }
        }
        else {                                                                                  // default
            GenAsm(szBodyLabel, ";      Default -------------", "", szStatementRef);
            GenStatements(hOut, iDepth+1, pCase->Use._case.pBody, pszFunctionName, pszExitLabel, pszNewBreakLabel, pszContinueLabel);
        }
    }
    GenAsm(pszNewBreakLabel, ";      Switch end ----------", "", szStatementRef);

}

/* eof */
