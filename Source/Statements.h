// # $URL: https://eboracum-vss.digitallocksmiths.local/svn/Dls/Sean/RoyalHolloway/CC_Avr/Source/Statements.h $
// # $Revision: 338 $


#ifndef __SKC_STATEMENTS_H__
#define __SKC_STATEMENTS_H__

#ifdef DEBUG_INCLUDE_FILES 
#pragma message("     including " __FILE__)
#endif // DEBUG_INCLUDE_FILES


typedef enum {
    StatementCOMPOUND,
    StatementRETURN,
    StatementIF,                // Use identifiers for statement nodes
    StatementWHILE,
    StatementDO,
    StatementFOR,
    StatementEXPR,
    StatementBREAK,
    StatementCONTINUE,
    StatementGOTO,
    StatementSWITCH,
    StatementCASE,
} TStatementTypes;

typedef struct TagStatement TStatement;     // Statement node
typedef TStatement * TPStatement;      
struct TagStatement {
    TPStatement         pNext;
    TStatementTypes     Usage;
    LPSTR               pszLabel;
    union {
        struct {
            TPDeclSpec      pDeclList;                                  // Declaration List
            TPStatement     pStatement;                                 // Statement List
        }_compound;
        struct {
            TPExprNode pExpr;
        } _return;
        struct {
            TPExprNode  pCond;
            TPStatement pYes;
            TPStatement pNo;
        } _if;
        struct {
            TPExprNode  pCond;
            TPStatement pAction;
        } _while;
        struct {
            TPStatement pAction;
            TPExprNode  pCond;
        } _do;
        struct {
            TPExprNode  pInit;
            TPExprNode  pCond;
            TPExprNode  pRepeat;
            TPStatement pAction;
        } _for;
        struct {
            TPExprNode  pExpr;
        } _expr;
        struct {
            LPSTR       pszLabel;
        } _goto;
        struct {
            TPExprNode  pExpr;
            TPStatement pBody;
        } _switch;
        struct {
            TPExprNode  pExpr;
            TPStatement pBody;
        } _case;

    } Use;
};


TPStatement StatementAppend(TPStatement pList, TPStatement pStat);

TPStatement StatementMakeCompound(TPDeclSpec pDeclList, TPStatement pStat);
TPStatement StatementMakeReturn(TPExprNode pRetVal);
TPStatement StatementMakeIf(TPExprNode pCond, TPStatement pYes, TPStatement pNo);
TPStatement StatementMakeWhile(TPExprNode pCond, TPStatement pAction);
TPStatement StatementMakeDo(TPStatement pAction, TPExprNode pCond);
TPStatement StatementMakeFor(TPExprNode  pInit, TPExprNode pCond, TPExprNode pRepeat, TPStatement pAction);
TPStatement StatementMakeExpression(TPExprNode  pExpr);
TPStatement StatementMakeBreak(void);
TPStatement StatementMakeContinue(void);
TPStatement StatementMakeGoto(LPSTR pszLabel);
TPStatement StatementMakeSwitch(TPExprNode  pConst, TPStatement pBody);
TPStatement StatementMakeCase(TPExprNode  pConst, TPStatement pStat);

TPStatement StatementAddLabel(LPSTR pszLabel, TPStatement pStat);


#endif // __SKC_STATEMENTS_H__

/* eof */


