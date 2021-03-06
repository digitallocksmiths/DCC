// # $URL: https://eboracum-vss.digitallocksmiths.local/svn/Dls/Sean/RoyalHolloway/CC_Avr/Source/Statements.c $
// # $Revision: 390 $


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>

#include "Utilities\Console.h"

#include "lex.h"
#include "typectrl.h"
#include "expr.h"
#include "Statements.h"
#include "main.h"


static TPStatement
NewStatement(TStatementTypes Use) {
    TPStatement NewStatment;
    NewStatment = New(sizeof(TStatement));
    NewStatment->Usage = Use;
    NewStatment->pNext = NULL;
    return NewStatment;
}

TPStatement StatementAppend(TPStatement pList, TPStatement pStat) {                     // add new statement to the end of the list
    TPStatement pL = pList;
    if (pList == NULL) {
        return pStat;
    }
    while (pList->pNext != NULL) {
        pList = pList->pNext;
    }
    pList->pNext = pStat;
    return pL;
}


TPStatement StatementMakeCompound(TPDeclSpec pDeclList, TPStatement pStat) {
    TPStatement pS = NewStatement(StatementCOMPOUND);
    pS->Use._compound.pDeclList = pDeclList;
    pS->Use._compound.pStatement = pStat;
    return pS;
}

TPStatement StatementMakeReturn(TPExprNode pExpr) {
    TPStatement pS = NewStatement(StatementRETURN);
    ASSERT(Glb_pCurrenFunction &&  Glb_pCurrenFunction->Usage == DecId && Glb_pCurrenFunction->Use.DecId.pTarget->Usage == DecFunc);
    TPDeclSpec pT = Glb_pCurrenFunction->Use.DecId.pTarget->Use.DecFunc.pReturnType;
    ASSERT(pT);
    if ((pT->Usage == DecSpec) && ((pT->Use.DecSpec.Type & TypeVOID) == TypeVOID) && (pExpr != NULL)) {
        Error(ERROR0, "Attempt to return value from void function '%s'.", Glb_pCurrenFunction->Use.DecId.pszName);
        return pS;
    }
    if ((pT->Usage == DecSpec) && ((pT->Use.DecSpec.Type & TypeVOID) != TypeVOID) && (pExpr == NULL)) {
        Error(ERROR0, "Expecting a value to be returned from function '%s'.", Glb_pCurrenFunction->Use.DecId.pszName);
        return pS;
    }

    if ((pT->Usage == DecSpec) && ((pT->Use.DecSpec.Type & TypeVOID) != TypeVOID) && (pExpr != NULL)) {                     // if result is returned then cast it 
        pExpr = ExprMakeCastNode(pT, pExpr);                                                                //
    }                                                                                                                       //

    pS->Use._return.pExpr = pExpr;

    return pS;
}

TPStatement StatementMakeIf(TPExprNode pCond, TPStatement pYes, TPStatement pNo) {
    ASSERT(pCond != NULL);
    TPDeclSpec NewType = NewSpecType(TypeBOOL, NULL);
    TPStatement pS = NewStatement(StatementIF);
    pS->Use._if.pCond = ExprMakeCastNode(NewType, pCond);                               // Force the condition to be BOOL
    pS->Use._if.pYes = pYes;
    pS->Use._if.pNo = pNo;
    return pS;
}

TPStatement StatementMakeWhile(TPExprNode pCond, TPStatement pAction) {
    ASSERT(pCond != NULL);
    TPDeclSpec NewType = NewSpecType(TypeBOOL, NULL);
    TPStatement pS = NewStatement(StatementWHILE);
    pS->Use._while.pCond = ExprMakeCastNode(NewType, pCond);                            // Force the condition to be BOOL
    pS->Use._while.pAction = pAction;
    return pS;
}

TPStatement StatementMakeDo(TPStatement pAction, TPExprNode pCond) {
    ASSERT(pCond != NULL);
    TPDeclSpec NewType = NewSpecType(TypeBOOL, NULL);
    TPStatement pS = NewStatement(StatementDO);
    pS->Use._do.pAction = pAction;
    pS->Use._do.pCond = ExprMakeCastNode(NewType, pCond);                               // Force the condition to be BOOL
    return pS;
}
TPStatement StatementMakeFor(TPExprNode  pInit, TPExprNode pCond, TPExprNode pRepeat, TPStatement pAction) {
    TPDeclSpec NewType = NewSpecType(TypeBOOL, NULL);
    TPStatement pS = NewStatement(StatementFOR);
    pS->Use._for.pInit = pInit;
    pS->Use._for.pCond = (pCond != NULL) ? ExprMakeCastNode(NewType, pCond) : NULL;     // Force the condition to be BOOL
    pS->Use._for.pRepeat = pRepeat;
    pS->Use._for.pAction = pAction;
    return pS;
}

TPStatement StatementMakeExpression(TPExprNode  pExpr) {
    TPStatement pS = NewStatement(StatementEXPR);
    pS->Use._expr.pExpr = pExpr;
    return pS;

}

TPStatement StatementMakeBreak(void) {
    return NewStatement(StatementBREAK);
}

TPStatement StatementMakeContinue(void) {
    return NewStatement(StatementCONTINUE);
}

TPStatement StatementMakeGoto(LPSTR pszLabel) {
    TPStatement pS = NewStatement(StatementGOTO);
    pS->Use._goto.pszLabel = pszLabel;
    return pS;
}

TPStatement StatementMakeSwitch(TPExprNode  pExpr, TPStatement pBody) {
    TPStatement pS = NewStatement(StatementSWITCH);
    pS->Use._switch.pExpr = pExpr;
    pS->Use._switch.pBody = pBody;
    return pS;
}

TPStatement StatementMakeCase(TPExprNode  pConst, TPStatement pStat) {
    TPStatement pS = NewStatement(StatementCASE);
    pS->Use._case.pExpr = pConst;
    pS->Use._case.pBody = pStat;
    return pS;
}


TPStatement StatementAddLabel(LPSTR pszLabel, TPStatement pStat) {
    if (pStat == NULL) {
        Error(WARNING1, "Label '%s' needs a statement", pszLabel);
    }
    else {
        pStat->pszLabel = pszLabel;
    }
    return pStat;
}


/* eof */
