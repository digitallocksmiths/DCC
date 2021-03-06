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

#include "GenMemAccess.h"
#include "GenStatement_break.h"
#include "GenStatement_continue.h"
#include "GenStatement_do.h"
#include "GenStatement_for.h"
#include "GenStatement_goto.h"
#include "GenStatement_if.h"
#include "GenStatement_return.h"
#include "GenStatement_switch.h"
#include "GenStatement_while.h"


//static void GenStatements(FILE *hOut, int iDepth, TPStatement pStat, LPSTR pszFunctionName, LPSTR pszExitLabel, LPSTR pszBreakLabel, LPSTR pszContinueLabel); // forward


void    GenStatementPrettyPrint(int iDepth, TPStatement pStat, BOOL fNext) {
    
    if (pStat == NULL) {
        return;
    }
    do {
        ConsoleIndent(iDepth);
        if (pStat->pszLabel) {
            printf("%s: ", pStat->pszLabel);
        }
        switch (pStat->Usage) {
        case    StatementCOMPOUND:
            printf("COMPOUND {\n");
            GenStatementPrettyPrint(iDepth + 1, pStat->Use._compound.pStatement, TRUE);
            ConsoleIndent(iDepth); printf("COMPOUND_END }\n");
            break;

        case    StatementRETURN:
            printf("RETURN %s\n", (pStat->Use._return.pExpr) ? "something" : "void");
            break;

        case    StatementIF:
            printf("IF (%s) THEN\n", (pStat->Use._if.pCond) ? "something" : "void");
            GenStatementPrettyPrint(iDepth + 1, pStat->Use._if.pYes, TRUE);
            if (pStat->Use._if.pNo) {
                ConsoleIndent(iDepth); printf("ELSE\n");
                GenStatementPrettyPrint(iDepth + 1, pStat->Use._if.pNo, TRUE);
            }
            ConsoleIndent(iDepth); printf("IF_END\n");
            break;

        case    StatementWHILE:
            printf("WHILE (%s) DO\n", (pStat->Use._while.pCond) ? "something" : "void");
            if (pStat->Use._while.pAction) {
                GenStatementPrettyPrint(iDepth + 1, pStat->Use._while.pAction, TRUE);
            }
            ConsoleIndent(iDepth); printf("WHILE_END\n");
            break;

        case    StatementDO:
            printf("DO\n");
            if (pStat->Use._do.pAction) {
                GenStatementPrettyPrint(iDepth + 1, pStat->Use._do.pAction, TRUE);
            }
            ConsoleIndent(iDepth+1); printf("while condition (%s)\n", (pStat->Use._do.pCond) ? "something" : "void");
            ConsoleIndent(iDepth); printf("DO_END\n");
            break;

        case    StatementFOR:
            printf("FOR\n");
            ConsoleIndent(iDepth + 1); printf("Init      (%s)\n", (pStat->Use._for.pInit)   ? "something" : "void");
            ConsoleIndent(iDepth + 1); printf("Condition (%s)\n", (pStat->Use._for.pCond)   ? "something" : "void");
            if (pStat->Use._for.pAction) {
                GenStatementPrettyPrint(iDepth + 2, pStat->Use._for.pAction, TRUE);
            }
            ConsoleIndent(iDepth + 1); printf("Repeat    (%s)\n", (pStat->Use._for.pRepeat) ? "something" : "void");

            ConsoleIndent(iDepth); printf("FOR_END\n");
            break;

        case    StatementEXPR:
            printf("EXPRESSION (%s)\n", (pStat->Use._expr.pExpr) ? "something" : "void");
            //GenExpressionPrettyPrint(iDepth + 1, pStat->Use._expr.pExpr);
//            pStat->Use._expr.pExpr  = ExprOptimize(pStat->Use._expr.pExpr);
#pragma message("GenStatementPrettyPrint: ExprOptimize commented out")

            break;

        case    StatementBREAK:
            printf("BREAK\n");
            break;

        case    StatementCONTINUE:
            printf("CONTINUE\n");
            break;

        case    StatementGOTO:
            printf("GOTO '%s'\n", pStat->Use._goto.pszLabel);
            break;

        case    StatementSWITCH:
            printf("SWITCH (%s)\n", (pStat->Use._switch.pExpr) ? "something" : "WTF?");
            if (pStat->Use._switch.pBody) {
                GenStatementPrettyPrint(iDepth + 1, pStat->Use._switch.pBody, TRUE);
            }
            ConsoleIndent(iDepth); printf("SWITCH_END\n");
            break;

        case    StatementCASE:
            printf("CASE '%s'\n", (pStat->Use._case.pExpr) ? "something" : "default");
            if (pStat->Use._case.pBody) {
                GenStatementPrettyPrint(iDepth + 1, pStat->Use._case.pBody, TRUE);
            }
            break;

        default: Error(FATAL, "StatementPrint(): unknown statement usage");
        }
        pStat = pStat->pNext;
    } while (fNext && pStat);
}


// ##########################################################################
// #  Function: GenStatementLabel
// #        Generate an statement lable for the current 'c' statement.. 
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
LPSTR GenStatementLabel(LPSTR pszFn, LPSTR pszLab) {
    static char szLab[256];

    if (pszLab != NULL) {
        sprintf_s(szLab, sizeof(szLab), "Label_%s_%s", pszFn, pszLab);
    }
    else {
        szLab[0] = '\0';
    }
    return szLab;
}

// ##########################################################################
// #  Function: GenStatementIntro
// #        Generate an assembler line for the Statement Start. 
// #        If the statement is labeled the label will be genterated here.
// #
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
void GenStatementIntro(FILE *hOut, TPStatement pStat, LPSTR pszFn, LPSTR pszAction, LPSTR pszExtraComment) {
    static char szComment[100];
    LPSTR pszLab = GenStatementLabel(pszFn, pStat->pszLabel);

    sprintf_s(szComment, sizeof(szComment), "; ==== %s Statement =======================================", pszAction);
    szComment[OPCODE_WIDTH + OPERAND_WIDTH - 2] = ' ';
    szComment[OPCODE_WIDTH + OPERAND_WIDTH - 1] = '\0';
    GenAsm(pszLab, szComment, "", pszExtraComment);
}

// ##########################################################################
// #  Function: GenExpr
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
static void GenExpr(FILE *hOut, TPStatement pStat, LPSTR pszFunctionName, LPSTR pszExitLabel, LPSTR pszBreakLabel, LPSTR pszContinueLabel) {
    LPSTR       szStatementRef = GenLabel("_Statement_Expression_");
    GenStatementIntro(hOut, pStat, pszFunctionName, "Expr", szStatementRef);
    GenExpression(pStat->Use._expr.pExpr);
    GenAsm("", ";      Expr end ------------", "", szStatementRef);
    Dispose(szStatementRef);
}



void GenLocalInitializers(FILE* hOut, int iDepth, TPDeclSpec pVars) {
    while (pVars != NULL) {
        ASSERT(pVars->Usage == DecId);
        if (pVars->Use.DecId.pInitializer != 0) {                               // this var needs initializing
            ASSERT(pVars->Use.DecId.pInitializer->Usage == uInit);
            int iSizeVar = CalcSizeOf(pVars->Use.DecId.pTarget);
            //printf("Initialize %s (Y+%d[%d])\n", pVars->Use.DecId.pszName, pVars->Use.DecId.iOffset, iSizeVar);
            ASSERT(pVars->Use.DecId.pInitializer->Use.Init.pAssignment != NULL);
            GenExpression(pVars->Use.DecId.pInitializer->Use.Init.pAssignment);
            TMemAccess Z;
            Z.Method = ACCESS_FRAME;
            Z.bVarSize = iSizeVar;
            Z.lN = pVars->Use.DecId.iOffset;
            Z.pszS = pVars->Use.DecId.pszName;
            FetchStore(&Z, REG_ACC);

        }
        pVars = pVars->Use.DecId.pBrother;
    }
}


// ##########################################################################
// #  Function: GenCompound
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
void GenCompound(FILE *hOut, int iDepth, TPStatement pStat, LPSTR pszFunctionName, LPSTR pszExitLabel, LPSTR pszBreakLabel, LPSTR pszContinueLabel) {
    LPSTR       szStatementRef = GenLabel("_Statement_compound_");
    GenStatementIntro(hOut, pStat, pszFunctionName, "Compound", szStatementRef);
    GenLocalInitializers(hOut, iDepth+1, pStat->Use._compound.pDeclList);
    GenAsm("", ";      Compound Body -------", "", szStatementRef);
    GenStatements(hOut, iDepth+1, pStat->Use._compound.pStatement, pszFunctionName, pszExitLabel, pszBreakLabel, pszContinueLabel);
    GenAsm("", ";      Compound End --------", "", szStatementRef);
    Dispose(szStatementRef);
}


// ##########################################################################
// #  Function: GenStatements
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
void GenStatements(FILE *hOut, int iDepth, TPStatement pStat, LPSTR pszFunctionName, LPSTR pszExitLabel, LPSTR pszBreakLabel, LPSTR pszContinueLabel) {

    while (pStat != NULL) {

        switch (pStat->Usage) {
        case    StatementCOMPOUND:  GenCompound(hOut, iDepth, pStat, pszFunctionName, pszExitLabel, pszBreakLabel, pszContinueLabel); break;
        case    StatementRETURN:    GenReturn(hOut, iDepth, pStat, pszFunctionName, pszExitLabel, pszBreakLabel, pszContinueLabel); break;
        case    StatementIF:        GenIf(hOut, iDepth, pStat, pszFunctionName, pszExitLabel, pszBreakLabel, pszContinueLabel); break;
        case    StatementWHILE:     GenWhile(hOut, iDepth, pStat, pszFunctionName, pszExitLabel, pszBreakLabel, pszContinueLabel); break;
        case    StatementDO:        GenDo(hOut, iDepth, pStat, pszFunctionName, pszExitLabel, pszBreakLabel, pszContinueLabel); break;
        case    StatementFOR:       GenFor(hOut, iDepth, pStat, pszFunctionName, pszExitLabel, pszBreakLabel, pszContinueLabel); break;
        case    StatementEXPR:      GenExpr(hOut, pStat, pszFunctionName, pszExitLabel, pszBreakLabel, pszContinueLabel); break;
        case    StatementBREAK:     GenBreak(hOut, iDepth, pStat, pszFunctionName, pszExitLabel, pszBreakLabel, pszContinueLabel); break;
        case    StatementCONTINUE:  GenContinue(hOut, iDepth, pStat, pszFunctionName, pszExitLabel, pszBreakLabel, pszContinueLabel); break;
        case    StatementGOTO:      GenGoto(hOut, iDepth, pStat, pszFunctionName, pszExitLabel, pszBreakLabel, pszContinueLabel); break;
        case    StatementSWITCH:    GenSwitch(hOut, iDepth, pStat, pszFunctionName, pszExitLabel, pszBreakLabel, pszContinueLabel); break;
        default: Error(FATAL, "GenStatements(): unknown statement usage");
        }
        pStat = pStat->pNext;
    }
}


// ##########################################################################
// #  Function: GenParamVars
// #        <todo: task brief description>
// #
// #        <todo: task detailed description>
// #
// #  Parameters:
// #            FILE* hOut              -
// #            TPDec lSpec  pParams    -
// #            int   iLocalsSize       -
// #            BOOL  fFrameNeeded      -
// #            int  nRegSize           - size of first parameter (may be put  in register)
// #
// #  Returns:
// #        <todo: return Value>
// #
// #  See Also:
// #
// ##########################################################################
int GenParamVars(FILE *hOut, TPDeclSpec  pParams, int  iLocalsSize, BOOL fFrameNeeded, int nRegSize) {
    char        caString[256];

    ASSERT(pParams->Usage == DecId);
    ASSERT((pParams->Use.DecId.pTarget == NULL) || (pParams->Use.DecId.pTarget->Usage == DecSpec) || (pParams->Use.DecId.pTarget->Usage == DecPtr) || (pParams->Use.DecId.pTarget->Usage == DecArray));

    if (pParams->Use.DecId.pTarget && (pParams->Use.DecId.pTarget->Usage == DecSpec) && ((pParams->Use.DecId.pTarget->Use.DecSpec.Type & TypeVOID) == TypeVOID)) {
        GenAsm("", "; #   Params: <none>", "", NULL);
        return 0;
    }

    LPSTR       pszIntro = "   Param: ";                                                                //
    TPDeclSpec  pP;                                                                                     // pointer to the current parameter
    int         iOffset = FRAME_OVERHEAD + iLocalsSize;                                                 // offset of first parameter
    int         iParamCounts = 0;                                                                       // count of parameters
    int         iTotalParamSize = 0;

    for (pP = pParams, iParamCounts = 0; pP != NULL; pP = pP->Use.DecId.pBrother, iParamCounts++) {     // For all params.
        pP->Use.DecId.iOffset = CalcSizeOf(pP->Use.DecId.pTarget);                                      // Find its own size
        iTotalParamSize += pP->Use.DecId.iOffset;                                                       //      the accumulated size of all parameters..
    }                                                                                                   //      and the number of parameters.
    
    int iDisplacement = iTotalParamSize + iLocalsSize - nRegSize;
    int iThisParamsSize;

    for (pP = pParams; pP != NULL; pP = pP->Use.DecId.pBrother) {                                       // For all params .
        
        if (pP->Use.DecId.pBrother == NULL) {                                                           // just before the last param.

            if (fFrameNeeded) {
                iDisplacement -= ASM_CALL_RET_ADDR_SIZE;
                sprintf_s(caString, sizeof(caString), "; #   CPU   : <return address> @Y+%-3d size=%d", FRAME_OVERHEAD + iDisplacement, ASM_CALL_RET_ADDR_SIZE);
                GenAsm("", caString, "", NULL);
                iDisplacement -= SIZE_PTR_DEFAULT;
                sprintf_s(caString, sizeof(caString), "; #         : <saved fptr>     @Y+%-3d size=%d", FRAME_OVERHEAD + iDisplacement, SIZE_PTR_DEFAULT);
                GenAsm("", caString, "", NULL);
                pszIntro = "   Param: ";
            }

            if (nRegSize != 0) {
                iThisParamsSize = pP->Use.DecId.iOffset;
                pP->Use.DecId.iOffset = -2;
                sprintf_s(caString, sizeof(caString), "; # %s%-16s r2%s  size=%d %s",
                    pszIntro,
                    pP->Use.DecId.pszName,
                    (nRegSize == 1) ? "   " : ((nRegSize == 1) ? ",r3" : "-r5"),
                    iThisParamsSize,
                    DescFullTypeString(0, pP->Use.DecId.pTarget));
                GenAsm("", caString, "", NULL);
                return iTotalParamSize - nRegSize;
            }
        }

        iThisParamsSize = pP->Use.DecId.iOffset;                                                        //      retrieve our own size.     
        iDisplacement -= pP->Use.DecId.iOffset;                                                         //      frame displacement 
        pP->Use.DecId.iOffset = FRAME_OVERHEAD + iDisplacement;                                         //      offset by the frame overhead and locals.

        if (iThisParamsSize == 0) {                               // size of this == 0
            sprintf_s(caString, sizeof(caString), "; # %s%-16s @Y+%-3d",
                pszIntro,
                pP->Use.DecId.pszName,
                pP->Use.DecId.iOffset);
        }
        else {
            sprintf_s(caString, sizeof(caString), "; # %s%-16s @Y+%-3d size=%d %s",
                pszIntro,
                pP->Use.DecId.pszName,
                pP->Use.DecId.iOffset,
                iThisParamsSize,
                DescFullTypeString(0, pP->Use.DecId.pTarget));
        }
        GenAsm("", caString, "", NULL);
        pszIntro = "        : ";

    }
    return iTotalParamSize - nRegSize;
}

// ##########################################################################
// #  Function: CalcLocalSize
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
int GenCalcLocalSize(TPStatement pStatment) {
    int         iReturnValue = 0;
    int         iMax1 = 0;
    int         iMax2 = 0;
    TPStatement pS;
    TPDeclSpec  pParams;


    if (pStatment == NULL) {            // statement was empty (eg "while(x--) ;")
        return 0;
    }

    switch (pStatment->Usage) {
    case    StatementCOMPOUND:
        iReturnValue = 0;           // size of locals here

        pParams = pStatment->Use._compound.pDeclList;
        if (pParams == NULL) {
            ;
        }
        else {
            while (pParams) {
                int iVarSize = CalcSizeOf(pParams->Use.DecId.pTarget);
                iReturnValue += iVarSize;
                pParams = pParams->Use.DecId.pBrother;
            }
        }

        for (pS = pStatment->Use._compound.pStatement; pS != NULL; pS = pS->pNext) {
            iMax1 = GenCalcLocalSize(pS);
            iMax2 = max(iMax1, iMax2);
        }
        return iReturnValue + iMax2;

    case    StatementIF:
        iMax1 = GenCalcLocalSize(pStatment->Use._if.pYes);
        iMax2 = GenCalcLocalSize(pStatment->Use._if.pNo);
        return max(iMax1, iMax2);

    case    StatementWHILE:
        return GenCalcLocalSize(pStatment->Use._while.pAction);

    case    StatementDO:
        return GenCalcLocalSize(pStatment->Use._do.pAction);

    case    StatementFOR:
        return GenCalcLocalSize(pStatment->Use._for.pAction);

    case    StatementRETURN:
    case    StatementEXPR:
    case    StatementBREAK:
    case    StatementCONTINUE:
    case    StatementGOTO:
    case    StatementSWITCH:
    case    StatementCASE:
        return 0;

    default: Error(FATAL, "CalcLocalSize(): unknown statement usage");
    }

    return 0;
}

// ##########################################################################
// #  Function: GenCalcLocalSize
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
int GenLocalVars(FILE *hOut, int iDepth, TPStatement pStatment, int  iLocalsSize) {
    char        caString[256];

    int         iReturnValue = 0;
    int         iMax1 = 0;
    int         iMax2 = 0;
    TPStatement pS;
    TPDeclSpec  pParams;

    if (pStatment == NULL) {            // statement was empty (eg "while(x--) ;")
        return 0;
    }

    switch (pStatment->Usage) {
    case    StatementCOMPOUND:
        iReturnValue = 0;           // size of locals here

        if (iDepth == 0) {
            LPSTR pszIntro = "  Locals: ";
        }
        pParams = pStatment->Use._compound.pDeclList;
        if (pParams == NULL) {
            if (iDepth == 0) {
                LPSTR pszIntro = "  Locals: ";
                sprintf_s(caString, sizeof(caString), "; # %s<none>", pszIntro);
                GenAsm("", caString, "", NULL);
            }
        }
        else {
            LPSTR pszIntro = "  Locals: ";
            while (pParams) {
                int iVarSize = CalcSizeOf(pParams->Use.DecId.pTarget);
                iReturnValue += iVarSize;
                iLocalsSize  -= iVarSize;
                pParams->Use.DecId.iOffset = iLocalsSize+1;

                LPSTR pszT = DescFullTypeString(0, pParams->Use.DecId.pTarget);
                sprintf_s(caString, sizeof(caString), "; # %s%-16s @Y+%-3d size=%d %s",
                        pszIntro,
                        pParams->Use.DecId.pszName,
                        pParams->Use.DecId.iOffset,
                        iVarSize,
                        pszT);
                
                GenAsm("", caString, "", NULL);
                pszIntro = "        : ";
                pParams = pParams->Use.DecId.pBrother;
            }
        }

        for (pS = pStatment->Use._compound.pStatement; pS != NULL; pS = pS->pNext) {
            iMax1 = GenLocalVars(hOut, iDepth++, pS, iLocalsSize);
            iMax2 = max(iMax1, iMax2);
        }
        return iReturnValue + iMax2;

    case    StatementIF:
        iMax1 = GenLocalVars(hOut, iDepth++, pStatment->Use._if.pYes, iLocalsSize);
        iMax2 = GenLocalVars(hOut, iDepth++, pStatment->Use._if.pNo, iLocalsSize);
        return max(iMax1, iMax2);

    case    StatementWHILE:
        return GenLocalVars(hOut, iDepth++, pStatment->Use._while.pAction, iLocalsSize);

    case    StatementDO:
        return GenLocalVars(hOut, iDepth++, pStatment->Use._do.pAction, iLocalsSize);

    case    StatementFOR:
        return GenLocalVars(hOut, iDepth++, pStatment->Use._for.pAction, iLocalsSize);

    case    StatementRETURN:
    case    StatementEXPR:
    case    StatementBREAK:
    case    StatementCONTINUE:
    case    StatementGOTO:
    case    StatementSWITCH:
    case    StatementCASE:
        return 0;

    default: Error(FATAL, "GenCalcLocalSize(): unknown statement usage");
    }

    return 0;
}



LPSTR DescReturnTypeString(TPDeclSpec pType) {
    static char szReturnTypedescriptor[256];                      // gets rewrirtten each call! Beware
    int n = 0;
    while (pType->Usage == DecPtr) {
        n += sprintf_s(&szReturnTypedescriptor[n], sizeof(szReturnTypedescriptor)-n, "ptr to ");
        pType = pType->Use.DecPtr.pTarget;
    }
    n += sprintf_s(&szReturnTypedescriptor[n], sizeof(szReturnTypedescriptor)-n, DescTypeString(pType->Use.DecSpec.Type));
    return szReturnTypedescriptor;
}


// ##########################################################################
// #  Function: GenFunction
// #        *public* <todo: task brief description>
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

void GenFunction(FILE *hOut, LPSTR pszName, TPDeclSpec pFunc) {
    char        caString[256];
    int         iReturnSize;
    int         iParamCount;
    int         iParamsSize;
    int         iLocalsSize;
    //int         iLocalCount;
    //int         iCorruptParamCount;
    BOOL        fContainsNestedCall;
    BOOL    fFrameNeeded;
    BOOL    fRegifyP1;
    LPSTR       pszExitLabel = GenLabel("_Exit_");
    LPSTR       pszVerifiedEntry = ""; 

    ASSERT(pFunc->Usage == DecFunc);

    TPDeclSpec pP = pFunc->Use.DecFunc.pPList;
    if (pP->Use.DecId.pTarget && (pP->Use.DecId.pTarget->Usage == DecSpec) && ((pP->Use.DecId.pTarget->Use.DecSpec.Type & TypeVOID) == TypeVOID)) {
        iParamCount = 0;
    }
    else {
        for (iParamCount = 0; pP != NULL; pP = pP->Use.DecId.pBrother, iParamCount++);
    }

    iLocalsSize = GenCalcLocalSize(pFunc->Use.DecFunc.pBody);
    //iCorruptParamCount  = _GenParameterCostStatement(0, pFunc->Use.DecFunc.pBody);                                                // find the most expensive function call in this function body.
    fContainsNestedCall = _GenDetectNestedCall(pFunc->Use.DecFunc.pBody);                                                           // find the most expensive function call in this function body.

    fFrameNeeded = FALSE;                                                                                                           // Do we need a Frame ?
    if (iParamCount > 1)        fFrameNeeded |= TRUE;                                                                               //
    if (iLocalsSize > 0)        fFrameNeeded |= TRUE;                                                                               //
    if (fContainsNestedCall)    fFrameNeeded |= TRUE;                                                                               //

    fRegifyP1 = FALSE;                                                                                                              // Can we put P1 in a Register
    if ((iParamCount != 0) && !fContainsNestedCall) fRegifyP1 = TRUE;                                                               // 

    //ConsolePrintf(CON_MAGENTA_BRIGHT, "%-10s: Frame %s  : RegP1 %s\n", pszName, (fFrameNeeded) ? "Yes" : " No", (fRegifyP1) ? "Yes" : " No");

    sprintf_s(caString, sizeof(caString), "; # Function: %s", pszName);
    GenAsm("", "; ###############################################################", "", NULL);
    GenAsm("", caString, "", NULL);
    GenAsm("", "; ###############################################################", "", NULL);

    DWORD nFirstParamSize = 0;                                                                                                      // Size of the first parameter
    if (iParamCount > 0) {                                                                                                          //
        for (pP = pFunc->Use.DecFunc.pPList; pP->Use.DecId.pBrother; pP = pP->Use.DecId.pBrother);                                  //      find the first parameter (it's the last in the chain)!
        nFirstParamSize = CalcSizeOf(pP->Use.DecId.pTarget);                                                                        //      Get its size
    }                                                                                                                               //

    iParamsSize = GenParamVars(hOut, pFunc->Use.DecFunc.pPList, iLocalsSize, fFrameNeeded, (fRegifyP1) ? nFirstParamSize : 0);

    if (fFrameNeeded && (iParamsSize == 0)) {                                                                                       // no params and no locals makes for no frame 
        sprintf_s(caString, sizeof(caString), "; #   CPU   : <return addr>    @Y+%-3d size=2", iLocalsSize + 3);                    // Otherwize ...
        GenAsm("", caString, "", NULL);                                                                                             //      here it is.
        sprintf_s(caString, sizeof(caString), "; #   CPU   : <saved fptr>     @Y+%-3d size=2", iLocalsSize + 1);                    //
        GenAsm("", caString, "", NULL);                                                                                             //
    }                                                                                                                               //

    iLocalsSize = GenLocalVars(hOut, 0, pFunc->Use.DecFunc.pBody, iLocalsSize) + ((fRegifyP1) ? 0:nFirstParamSize);
    if (iLocalsSize != 0) {
        sprintf_s(caString, sizeof(caString), "; #         : sizeof(locals) = %d", iLocalsSize);
        GenAsm("", caString, "", NULL);
    }

    ASSERT((pFunc->Use.DecFunc.pReturnType->Usage == DecSpec) || (pFunc->Use.DecFunc.pReturnType->Usage == DecPtr));
    iReturnSize = CalcSizeOf(pFunc->Use.DecFunc.pReturnType);
    switch (iReturnSize) {
    case 0: sprintf_s(caString, sizeof(caString), "; #   Return: %-16s", DescReturnTypeString(pFunc->Use.DecFunc.pReturnType)); break;
    case 1: sprintf_s(caString, sizeof(caString), "; #   Return: %-16s r%d", DescReturnTypeString(pFunc->Use.DecFunc.pReturnType), REG_ACC0); break;
    case 2: sprintf_s(caString, sizeof(caString), "; #   Return: %-16s r%d,r%d", DescReturnTypeString(pFunc->Use.DecFunc.pReturnType), REG_ACC0, REG_ACC1); break;
    case 4: sprintf_s(caString, sizeof(caString), "; #   Return: %-16s r%d-r%d", DescReturnTypeString(pFunc->Use.DecFunc.pReturnType), REG_ACC0, REG_ACC3); break;
    default:
        Error(ERRORX, "Function %s. returning more than 4 bytes is not supported", pszName);
        sprintf_s(caString, sizeof(caString), "; # Return: %s - size=%d NOT SUPPORTED", DescTypeString(pFunc->Use.DecFunc.pReturnType->Use.DecSpec.Type), iReturnSize);
    }
    GenAsm("", caString, "", NULL);
    GenAsm("", "; ###############################################################", "", NULL);

    TPDeclSpec pD = pFunc->Use.DecFunc.pReturnType;
    while (pD->Usage == DecPtr) {
        pD = pD->Use.DecPtr.pTarget;
    }
    ASSERT(pD->Usage == DecSpec);

    WORD nClass = pD->Use.DecSpec.Class;
    WORD nQual = pD->Use.DecSpec.wQual;
    BOOL fGlobal = ((nClass & ClassSTATIC) != ClassSTATIC);

    if (((nClass & ClassEXTERN) == ClassEXTERN) ||                                                                      // declared extern or
        (pFunc->Use.DecFunc.pBody == NULL)) {                                                                           // declared without a body.
        GenAsm("", ".extern", pszName, NULL);                                                                           //
        fprintf(hOut, "\n\n");                                                                                          //
        return;                                                                                                         //
    } 
     

    if (!fFrameNeeded) {                                                                                                // Local Frame setup (if needed.
        GenAsmOut(pszName, "; #### no frame needed ###############", "", "no parameters or locals", TRUE, fGlobal);     //
    }                                                                                                                   //
    else {                                                                                                              //
        GenAsmOut(pszName, "; #### frame setup ###################", "", "", TRUE, fGlobal);                            // @SP = [<ret addr>]
        GenAsm("",      "push",   "r29",                    "  2: (YH) preserve Frame");                                // 
        GenAsm("",      "push",   "r28",                    "  2: (YL)");                                               // @SP = [<old FP> <ret addr>]
        GenAsm("",      "in",     "r29, _IO_SPH",           "  1: FP <- SP");                                           // Fp+SP. 
        GenAsm("",      "in",     "r28, _IO_SPL",           "  1:");                                                    //
        if (iLocalsSize != 0) {                                                                                         // @SP = [<locals> <old FP> <ret addr>]
            sprintf_s(caString, sizeof(caString), "r28, %d", iLocalsSize);                                              //
            GenAsm("",  "sbiw",   caString,                 "  2: FP -= sizeof(locals))");                              //
            GenAsm("",  "out",    "_IO_SPH, r29",           "  1: SP <- FP");                                           //
            GenAsm("",  "out",    "_IO_SPL, r28",           "  1:");                                                    //
        }                                                                                                               //
    }                                                                                                                   //

    if (nFirstParamSize > 0) {                                                                                          // Do the right thing with the orphan parameter left in REG_ACC0
        if (fRegifyP1) {                                                                                                //
            switch (nFirstParamSize) {                                                                                  //
            case 1:                                                                                                     //
                GenAsm("", "mov",  OperandRegReg(2 + REG_ORDER0, REG_ACC0), "  1: First parameter is regified");        //
                break;                                                                                                  //
            case 2:                                                                                                     //
                GenAsm("", "movw", OperandRegReg(2 + REG_ORDER0, REG_ACC0), "  1: First parameter is regified");        //
                break;                                                                                                  //
            case 4:                                                                                                     //
                GenAsm("", "movw", OperandRegReg(2 + REG_ORDER0, REG_ACC0), "  1: First parameter is regified");        //
                GenAsm("", "movw", OperandRegReg(2 + REG_ORDER2, REG_ACC2), "  1:");                                    //
                break;                                                                                                  //
            }                                                                                                           //
        }                                                                                                               //
        else {                                                                                                          //
            switch (nFirstParamSize) {                                                                                  //
            case 1:                                                                                                     //
                GenAsm("", "std", OperandStrDispReg("Y", iLocalsSize - 0, REG_ACC0), "  2: First parameter is in the frame");   //
                break;                                                                                                          //
            case 2:                                                                                                             //
                GenAsm("", "std", OperandStrDispReg("Y", iLocalsSize - 1, REG_ACC0), "  2: First parameter is in the frame");   //
                GenAsm("", "std", OperandStrDispReg("Y", iLocalsSize - 0, REG_ACC1), "  2: ");                          //
                break;                                                                                                  //
            case 4:                                                                                                     //
                GenAsm("", "std", OperandStrDispReg("Y", iLocalsSize - 3, REG_ACC0), "  2: First parameter is in the frame");   //
                GenAsm("", "std", OperandStrDispReg("Y", iLocalsSize - 2, REG_ACC1), "  2: ");                          //
                GenAsm("", "std", OperandStrDispReg("Y", iLocalsSize - 1, REG_ACC2), "  2: ");                          //
                GenAsm("", "std", OperandStrDispReg("Y", iLocalsSize - 0, REG_ACC3), "  2: ");                          //
                break;                                                                                                  //
            }                                                                                                           //
        }                                                                                                               //
    }                                                                                                                   //

    //TPDeclSpec pT = pFunc->Use.DecFunc.pReturnType;
    //ASSERT(pT && (pT->Usage == DecSpec));
    //WORD wQualifier = pT->Use.DecSpec.Qual;

    if (!FnIsUndefended(nQual) && ((CmdLine.iDefendCallRet & 1) == 1)) {                                                                        // Defended call type 1.
        pszVerifiedEntry = GenLabel("_OK_");                                                                                                     //
        GenAsm("", "; #### intended call check ###########", "", "");                                                                           // 
        if ((CmdLine.iDefendCallRet & 2) == 2) {
            GenAsm("", "clz", "", CommentString(1, "   Preset to fail if subi is skipped.", ""));                                               // additional defence 2
        }                                                                                                                                       //
        GenAsm("", "subi",  OperandFreeform("r%d, lo8(%s-1)", REG_DEFENDER, pszName), CommentString(1, "   Check the call was deliberate", ""));//
        GenAsm("", "BREQ", pszVerifiedEntry,                                           CommentString(2, "   Clean setup, or ", ""));             //          // capitals to stop recognition of "breq" generating -d3=1 defence.
        GenAsm("", ASM_TRAP_OPCODE, ASM_TRAP_OPERAND,                                CommentString(2, "   Accidental arrival?", ""));          //
        if ((CmdLine.iDefendCallRet & 4) == 4) {                                                                                                // additional defence 4
            GenAsm("", ASM_TRAP_OPCODE, ASM_TRAP_OPERAND, CommentString(2, "   Repeated in case the the earlier one was skipped.", ""));        //
        }                                                                                                                                       //
    }                                                                                                                                           //

    GenAsm(pszVerifiedEntry, "; #### body text #####################", "", "");                                                          // Function body
    GenStatements(hOut, 0, pFunc->Use.DecFunc.pBody, pszName, pszExitLabel, NULL, NULL);                                                 //

    GenAsm("", "; #### exit ##########################", "", "");                                                                       // Exit Code.
    if ((nQual & QualNORETURN) == QualNORETURN) {                                                                                       //
        GenAsm("", ASM_TRAP_OPCODE, ASM_TRAP_OPERAND, "  2: 'noreturn' function wanting to return.");                                   //      No return function
    }
    else {
        if (!FnIsUndefended(nQual) && ((CmdLine.iDefendCallRet & 1) == 1)) {                                                                    //      Defended call type 1.
            GenAsm(pszExitLabel, "ldi", OperandFreeform("r%d, lo8(%s+1)", REG_DEFENDER, pszName), CommentString(1, "Returner's identity", ""));  //
            pszExitLabel = NULL;                                                                                                                 //
        }                                                                                                                                       //

        if (!fFrameNeeded) {                                                                                                            //      No frame to strip out
            GenAsm(pszExitLabel, "ret", "", "  4: ");                                                                                    //
        }                                                                                                                               //
        else {                                                                                                                          //
            if (iLocalsSize != 0) {                                                                                                     //      Strip local storage
                sprintf_s(caString, sizeof(caString), "r28, %d", iLocalsSize);                                                          //          only if we have locals!
                GenAsm(pszExitLabel, "adiw", caString, "  2: Y += sizeof(locals)");                                                      //
                pszExitLabel = NULL;                                                                                                     //
            }                                                                                                                           //
            GenAsm(pszExitLabel, "out", "_IO_SPH, r29", "  1: SP <- Y");                                                                 //      reset SP to end of frame
            GenAsm("", "out", "_IO_SPL, r28", "  1:");                                                                                  //
            GenAsm("", "pop", "r28", "  2: FP <- preserved Frame");                                                                     //      recover the preserved frame
            GenAsm("", "pop", "r29", "  2: ");                                                                                          //


            GenAsm("", "ret", "", "  4: ");                                                                                             //      back to caller.
        }
    }
    GenAsm("", "\n", "\n", NULL);
}

/*
void GenFunction(FILE *hOut, LPSTR pszName, TPDeclSpec pFunc) {
    char        caString[256];
    int         iParamsSize;
    int         iLocalsSize;
    int         iReturnSize;
    LPSTR       szExitLabel = GenLabel("_Exit_");

    ASSERT(pFunc->Usage == DecFunc);

    sprintf_s(caString, sizeof(caString), "; # Function: %s", pszName);
    GenAsmOut("", "; ###########################################", "", NULL, TRUE, FALSE);
    GenAsmOut("", caString,                                        "", NULL, TRUE, FALSE);

    ASSERT((pFunc->Use.DecFunc.pReturnType->Usage == DecSpec) || (pFunc->Use.DecFunc.pReturnType->Usage == DecPtr));
    iReturnSize = CalcSizeOf(pFunc->Use.DecFunc.pReturnType);
    switch (iReturnSize) {
    case 0: sprintf_s(caString, sizeof(caString), "; #   Return: %s", DescReturnTypeString(pFunc->Use.DecFunc.pReturnType)); break;
    case 1: sprintf_s(caString, sizeof(caString), "; #   Return: %s (r%d)", DescReturnTypeString(pFunc->Use.DecFunc.pReturnType), REG_ACC0); break;
    case 2: sprintf_s(caString, sizeof(caString), "; #   Return: %s (r%d,r%d)", DescReturnTypeString(pFunc->Use.DecFunc.pReturnType), REG_ACC0, REG_ACC1); break;
    case 4: sprintf_s(caString, sizeof(caString), "; #   Return: %s (r%d,r%d,r%d,r%d)", DescReturnTypeString(pFunc->Use.DecFunc.pReturnType), REG_ACC0, REG_ACC1, REG_ACC2, REG_ACC3); break;
    default:
        Error(ERRORX, "Function %s. returning more than 4 bytes is not supported", pszName);
        sprintf_s(caString, sizeof(caString), "; # Return: %s - size=%d NOT SUPPORTED", DescTypeString(pFunc->Use.DecFunc.pReturnType->Use.DecSpec.Type), iReturnSize);
    }
    GenAsmOut("", caString, "", NULL, TRUE, FALSE);

    iLocalsSize = GenCalcLocalSize(pFunc->Use.DecFunc.pBody);
    iParamsSize = GenParamVars(hOut, pFunc->Use.DecFunc.pPList, iLocalsSize);
    sprintf_s(caString, sizeof(caString), "; #   CPU   : <return addr>    @Y+%-3d size=2", iLocalsSize+3); GenAsmOut("", caString, "", NULL, TRUE, FALSE);
    sprintf_s(caString, sizeof(caString), "; #         : <saved fptr>     @Y+%-3d size=2", iLocalsSize+1); GenAsmOut("", caString, "", NULL, TRUE, FALSE);
    iLocalsSize = GenLocalVars(hOut, 0, pFunc->Use.DecFunc.pBody, iLocalsSize);
    sprintf_s(caString, sizeof(caString), "; #         : sizeof(locals) = %d", iLocalsSize);
    GenAsmOut("", caString, "", NULL, TRUE, FALSE);
    GenAsmOut("", "; ###########################################", "", NULL, TRUE, FALSE);

    ASSERT(pFunc->Use.DecFunc.pReturnType->Usage == DecSpec);
    WORD bClass = pFunc->Use.DecFunc.pReturnType->Use.DecSpec.Class;
    BOOL fGlobal = ((bClass & ClassSTATIC) != ClassSTATIC);

    if (((bClass & ClassEXTERN) == ClassEXTERN) ||                                          // declared extern or
        (pFunc->Use.DecFunc.pBody == NULL)) {                                               // declared without a body.
        GenAsmOut("", ".extern", pszName, NULL, TRUE, FALSE);                               //
        fprintf(hOut, "\n\n");                                                              //
        return;                                                                             //
    }                                                                                       //

//    int iCorruptParamCount = _GenParameterCostStatement(0, pFunc->Use.DecFunc.pBody);       // find the most expensive function call in this function body.

    if (iParamsSize + iLocalsSize == 0) {
        GenAsmOut(pszName, "; #### no frame needed #####", "", "   : no parameters or locals", TRUE, fGlobal);
    }
    else {
        GenAsmOut(pszName, "; #### frame setup #########", "", "", TRUE, fGlobal);              // @SP = [<ret addr>]
        GenAsmOut("", "push", "r29", "  2: (YH) preserve Frame", TRUE, FALSE);                  // 
        GenAsmOut("", "push", "r28", "  2: (YL)", TRUE, FALSE);                                 // @SP = [<old FP> <ret addr>]
        GenAsmOut("", "in", "r29, _IO_SPH", "  1: FP <- SP", TRUE, FALSE);                      // Fp+SP. 
        GenAsmOut("", "in", "r28, _IO_SPL", "  1:", TRUE, FALSE);
        if (iLocalsSize != 0) {                                                                 // @SP = [<locals> <old FP> <ret addr>]
             sprintf_s(caString, sizeof(caString), "r28, %d", iLocalsSize);
             GenAsmOut("", "sbiw", caString,       "  2: FP -= sizeof(locals))", TRUE, FALSE);
             GenAsmOut("", "out", "_IO_SPH, r29",  "  1: SP <- FP", TRUE, FALSE);
             GenAsmOut("", "out", "_IO_SPL, r28",  "  1:", TRUE, FALSE);
        }
    }
    GenAsmOut("", "; #### body text ###########", "", "", TRUE, FALSE);

    GenStatements(hOut, 0, pFunc->Use.DecFunc.pBody, pszName, szExitLabel, NULL, NULL);

    GenAsmOut("", "; #### exit ################", "", "", TRUE, FALSE);
    if (iParamsSize + iLocalsSize == 0) {
        GenAsmOut(szExitLabel, "ret", "", " 4: ", TRUE, FALSE);
    }
    else {
        if (iLocalsSize != 0) {                                                                                 // Strip local storage
            sprintf_s(caString, sizeof(caString), "r28, %d", iLocalsSize);                                      // only if we have locals!
            GenAsmOut(szExitLabel, "adiw", caString, "  2: Y += sizeof(locals)", TRUE, FALSE);            //
            szExitLabel[0] = 0;                                                                                 //
        }                                                                                                       //
        GenAsmOut(szExitLabel, "out",  "_IO_SPH, r29", "  1: SP <- Y", TRUE, FALSE);                      // reset SP to end of frame
        GenAsmOut("",          "out",  "_IO_SPL, r28", "  1:",         TRUE, FALSE);                      //
        GenAsmOut("",          "pop",  "r28",          "  2: FP <- preserved Frame", TRUE, FALSE);        // recover the preserved frame
        GenAsmOut("",          "pop",  "r29",          "  2: ",        TRUE, FALSE);                      //
        GenAsmOut("",          "ret",  "",             "  4: ",        TRUE, FALSE);                      // bact to caller.
    }
    GenAsmOut("", "\n", "\n", NULL, TRUE, FALSE);
}
*/

// ##########################################################################
// #  Function: GenText
// #        *public* <todo: task brief description>
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
void GenText(TPDeclSpec pDeclList) {
    //char szOperand[32];
    TPDeclSpec pDecl;

    GenAsm(NULL, NULL, NULL, "#########################");
    GenAsm(NULL, ASM_DIRECTIVE_SEGMENT_BEGIN_TEXT, "", "# Start of TEXT segment #");
    GenAsm(NULL, "", "", "#########################");

    GenAsm("", "", "", "Here starts the executable code\n\n");
    
    for (pDecl = pDeclList; pDecl; pDecl = pDecl->pChain) {
        if ((pDecl->Usage == DecId) &&
            GenIsFunction(pDecl->Use.DecId.pTarget->Usage)) {

            TPDeclSpec pF = pDecl->Use.DecId.pTarget;
            ASSERT(pF->Usage == DecFunc);
            GenFunction(hGlbOut, pDecl->Use.DecId.pszName, pDecl->Use.DecId.pTarget);

        }
    }
    GenAsm(NULL, ASM_DIRECTIVE_SEGMENT_END, NULL, "=== End of TEXT segment ===\n\n");

}




// ##################################################################################################################

/*
// ##########################################################################
// #  Function: _GenExprParameterCost
// #        Look at all the function calls made within a function to determine 
// #        how many registers wil be corrupted by function calls.
// #
// #        Registers are counted in pairs. all parameters need to be 16-bit aligned.
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
int    _GenParameterCostStatement(int iMax, TPStatement pStat) {
    while (pStat != NULL) {
        switch (pStat->Usage) {
        case    StatementCOMPOUND:  
                iMax = _GenParameterCostStatement(iMax, pStat->Use._compound.pStatement); 
                break;
        case    StatementRETURN:    
                iMax = _GenParameterCostExpression(iMax, pStat->Use._return.pExpr); 
                break;
        case    StatementIF:        
                iMax = _GenParameterCostExpression(iMax, pStat->Use._if.pCond);
                iMax = _GenParameterCostStatement(iMax, pStat->Use._if.pYes);
                iMax = _GenParameterCostStatement(iMax, pStat->Use._if.pNo);
                break;
        case    StatementWHILE:     
                iMax = _GenParameterCostExpression(iMax, pStat->Use._while.pCond);
                iMax = _GenParameterCostStatement(iMax, pStat->Use._while.pAction);
                break;
        case    StatementDO:        
                iMax = _GenParameterCostExpression(iMax, pStat->Use._do.pCond);
                iMax = _GenParameterCostStatement(iMax, pStat->Use._do.pAction);
                break;
        case    StatementFOR:       
                iMax = _GenParameterCostExpression(iMax, pStat->Use._for.pInit);
                iMax = _GenParameterCostExpression(iMax, pStat->Use._for.pCond);
                iMax = _GenParameterCostExpression(iMax, pStat->Use._for.pRepeat);
                iMax = _GenParameterCostStatement(iMax, pStat->Use._for.pAction);
                break;

        case    StatementEXPR:     
                iMax = _GenParameterCostExpression(iMax, pStat->Use._expr.pExpr);
                break;
        case    StatementBREAK:     
        case    StatementCONTINUE:  
        case    StatementGOTO:
                break;
        case    StatementSWITCH: 
                iMax = _GenParameterCostExpression(iMax, pStat->Use._switch.pExpr);
                iMax = _GenParameterCostStatement(iMax, pStat->Use._switch.pBody);
                break;
        case    StatementCASE:
                iMax = _GenParameterCostExpression(iMax, pStat->Use._case.pExpr);
                iMax = _GenParameterCostStatement(iMax, pStat->Use._case.pBody);
                break;

        default: Error(FATAL, "GenStatements(): unknown statement usage");
        }
        pStat = pStat->pNext;
    }
    return iMax;
}
*/


// ##########################################################################
// #  Function: _GenDetectNestedCall
// #        Look to find any function calls made within a this function.
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
BOOL  _GenDetectNestedCall(TPStatement pStat) {
    BOOL fFound = FALSE;
    while (pStat != NULL  && !fFound) {
        switch (pStat->Usage) {
        case    StatementCOMPOUND:
            fFound |= _GenDetectNestedCall(pStat->Use._compound.pStatement);
            break;
        case    StatementRETURN:
            fFound |= _GenExprNestedCall(pStat->Use._return.pExpr);
            break;
        case    StatementIF:
            fFound |= _GenExprNestedCall(pStat->Use._if.pCond);
            fFound |= _GenDetectNestedCall(pStat->Use._if.pYes);
            fFound |= _GenDetectNestedCall(pStat->Use._if.pNo);
            break;
        case    StatementWHILE:
            fFound |= _GenExprNestedCall(pStat->Use._while.pCond);
            fFound |= _GenDetectNestedCall(pStat->Use._while.pAction);
            break;
        case    StatementDO:
            fFound |= _GenExprNestedCall(pStat->Use._do.pCond);
            fFound |= _GenDetectNestedCall(pStat->Use._do.pAction);
            break;
        case    StatementFOR:
            fFound |= _GenExprNestedCall(pStat->Use._for.pInit);
            fFound |= _GenExprNestedCall(pStat->Use._for.pCond);
            fFound |= _GenExprNestedCall(pStat->Use._for.pRepeat);
            fFound |= _GenDetectNestedCall(pStat->Use._for.pAction);
            break;

        case    StatementEXPR:
            fFound |= _GenExprNestedCall(pStat->Use._expr.pExpr);
            break;
        case    StatementBREAK:
        case    StatementCONTINUE:
        case    StatementGOTO:
            break;
        case    StatementSWITCH:
            fFound |= _GenExprNestedCall(pStat->Use._switch.pExpr);
            fFound |= _GenDetectNestedCall(pStat->Use._switch.pBody);
            break;
        case    StatementCASE:
            fFound |= _GenExprNestedCall(pStat->Use._case.pExpr);
            fFound |= _GenDetectNestedCall(pStat->Use._case.pBody);
            break;

        default: Error(FATAL, "GenStatements(): unknown statement usage");
        }
        pStat = pStat->pNext;
    }
    return fFound;
}


/* eof */
