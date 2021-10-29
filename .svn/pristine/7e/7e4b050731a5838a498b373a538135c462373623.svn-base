// # $URL: https://eboracum-vss.digitallocksmiths.local/svn/Dls/Sean/RoyalHolloway/CC_Avr/Source/GenExpression.h $
// # $Revision: 387 $


#ifndef __SKC_GEN_ASSEMBLER_STATEMENTS_H__
#define __SKC_GEN_ASSEMBLER_STATEMENTS_H__

#ifdef DEBUG_INCLUDE_FILES 
#pragma message("     including " __FILE__)
#endif // DEBUG_INCLUDE_FILES

LPSTR OperandImmediateImmediate(unsigned char bV1, unsigned char bV2);
LPSTR OperandRegImmediate(int iR1, unsigned char bVal);
LPSTR OperandImmediateReg(unsigned char bVal, int iR1);
LPSTR OperandRegProgVar(int iR1, LPSTR pszVar);
LPSTR OperandRegVar(int iR1, LPSTR pszVar);
LPSTR OperandRegStr(int iR1, LPSTR pszStr);
LPSTR OperandRegStrDisp(int iR1, LPSTR pszStr, int iDisp);
LPSTR OperandStrReg(LPSTR pszStr, int iR1);
LPSTR OperandStrDispReg(LPSTR pszStr, int iDisp, int iR1);
LPSTR OperandRegDisp(int iR1, LPSTR pszStr, int iDisp);
LPSTR OperandDispReg(LPSTR pszStr, int iDisp, int iR1);
LPSTR OperandReg(int iR);
LPSTR OperandRegReg(int iR1, int iR2);
LPSTR OperandFreeform(LPSTR pszF, ...);

LPSTR CommentNumber(int iCycles, LPSTR pszT, long lValue);
LPSTR CommentString(int iCycles, LPSTR pszT, LPSTR pszM);
void  GenAsm(LPSTR pszLabel, LPSTR pszOpcode, LPSTR pszOperand, LPSTR pszComment);


#endif // __SKC_GEN_ASSEMBLER_STATEMENTS_H__

/* eof */


