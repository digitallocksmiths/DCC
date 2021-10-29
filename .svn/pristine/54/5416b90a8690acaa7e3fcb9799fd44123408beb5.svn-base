// # $URL: https://eboracum-vss.digitallocksmiths.local/svn/Dls/Sean/RoyalHolloway/CC_Avr/Source/GenExpression.h $
// # $Revision: 401 $


#ifndef __SKC_GEN_EXPRESSIONS_H__
#define __SKC_GEN_EXPRESSIONS_H__

#ifdef DEBUG_INCLUDE_FILES 
#pragma message("     including " __FILE__)
#endif // DEBUG_INCLUDE_FILES


//============================================================================================
// Public functions

void    GenExpressionPrettyPrint(int iDepth, TPExprNode n);


// protected
void    _GenExpr(int iReg, TPExprNode pExpr);
int     _GenCostOfCalculation(TPExprNode pExpr);
//int     _GenParameterCostExpression(int iMax, TPExprNode pExpr);
BOOL    _GenExprNestedCall(TPExprNode pExpr);


//public
void    GenExpression(TPExprNode pExpr);                                                    //
void    GenExpressionConditional(TPExprNode pExpr, LPSTR pzsTrue, LPSTR pszFalse);          //


#endif // __SKC_GEN_EXPRESSIONS_H__

/* eof */

