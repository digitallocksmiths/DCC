// # $URL: https://eboracum-vss.digitallocksmiths.local/svn/Dls/Sean/RoyalHolloway/CC_Avr/Source/GenExpression.c $
// # $Revision: 406 $

//#pragma message(" Logical operations generate values. Change this to branch targets.")
// Skipping code is better.


#pragma message(" Pre/Post Inc/Dec does not check for const variables.")


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <ctype.h>
#include <signal.h>
#include <setjmp.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <limits.h>
#include <float.h>
#include <Windows.h>

//#include <ext\types.h>
#include "..\Utilities\Console.h"

#include "..\lex.h"
#include "..\typectrl.h"
#include "..\expr.h"
#include "..\ExprOptimize.h"
#include "gen.h"
#include "..\main.h"
//#include "C_Yacced.tab.h"
#include "GenAsm.h"
//#include "GenStatements.h"
#include "GenMemAccess.h"


static FILE *hGlbOut;

//static int     GenCostOfCalculation(TPExprNode pExpr);                                          // forward
//static void    GenExpr(int iReg, TPExprNode pExpr);                                             // forward
static void    GenExprConditional(int iReg, TPExprNode pExpr, LPSTR pzsTrue, LPSTR pszFalse);   // forward



char *Uops[] = { "-u",  "+u",  "~u",    "u++",  "++u", "u--", "--u", "sizeof","addr", "ptr", "!u" };

char *Bops[] = { "", "+b",  "-b",  "*b",    "/b",   "%b", "&b",  "|b",  "^b",    "==b",  "!=b", "<b",  "<=b", ">b",    ">=b",  "&&b", "||b", ">>b", "<<b" };


void PrintNode(TPExprNode pN) {
    switch (pN->Usage) {
        case uConst:    printf("%lx ",  pN->Use.Const.lInteger);
                        break;
        case uVar:      printf("<%s> ",  pN->Use.Var.pszIdentifier);
                        break;
        case uUnary:    printf("(op ");
                        PrintNode(pN->Use.Unary.pOperand);
                        printf(")");
                        break;
        default:    Error(WARNING0, "Other ");
                    break;
    }
}

void ExprPrintInit(TPExprNode n) {
    while (n) {
        if (n->Usage != uInit) {
            Error(FATAL, "PrintInit: What !\n");
        }
        if (n->Use.Init.pAssignment) {
            PrintNode(n->Use.Init.pAssignment);
        }
        if (n->Use.Init.pChildren) {
            printf("{ ");
            ExprPrintInit(n->Use.Init.pChildren);
            printf("} ");
        }
        n=n->pSibling;
    }
}


void PrintType(int iDepth, TPExprNode n) {
    ASSERT(n->pType && ((n->pType->Usage == DecSpec) || (n->pType->Usage == DecPtr) || (n->pType->Usage == DecArray) || (n->pType->Usage == DecFunc)));
    ParseDeclSpec(0, n->pType, FALSE);
 }

char *pszCasts[] = {
    "s8 to s16",
    "s8 to s32",
    "s16 to s32",
    "u8 to u16",
    "u8 to u32",
    "u16 to u32",
    "32 to 16",
    "32 to 8",
    "32 to BOOL",
    "16 to 8",
    "16 to BOOL",
    "8 to BOOL"
};

char *pszaAssignOps[] = {
        ":=",       //  binNop
        "+=",       //  binAdd,    
        "-=",       //  binSub,    
        "*=",       //  binMul,
        "\\=",       //  binDiv,
        "%=",       //  binMod,
        "&=",       //  binAnd,    
        "|=",       //  binOr,     
        "^=",       //  binXor,    
        "?=1",      //  binCEQ,    
        "?=2",      //  binCNE,
        "?=3",      //  binCLT,    
        "?=4",      //  binCLE,    
        "?=5",      //  binCGT,    
        "?=6",      //  binCGE,    
        "?=7",      //  binLAnd,
        "?=8",      //  binLOr,    
        "?=9",      //  binShr,    
        "?=A",      //  binShl,    
};

void GenExpressionPrettyPrint(int iDepth, TPExprNode pExpr) {
    if (!pExpr) {
        printf("..Null\n");
        return;
    }
    
    for (; pExpr; pExpr = pExpr->pSibling) {        // expressions can be comma separated lists. The resulting value is the final entry.
        switch (pExpr->Usage) {
        case    uConst:
            ConsoleIndent(iDepth);
            ConsolePrintf(CON_MAGENTA_BRIGHT, "0x%x ", pExpr->Use.Const.lInteger);
            PrintType(iDepth, pExpr);
            break;
        case    uIoreg:
            ConsoleIndent(iDepth);
            ConsolePrintf(CON_MAGENTA_BRIGHT, "IO(0x%x,%s) ", pExpr->Use.Ioreg.nReg, pExpr->Use.Ioreg.pszName);
            PrintType(iDepth, pExpr);
            break;
        case    uVar:
            ConsoleIndent(iDepth);
            ConsolePrintf(CON_YELLOW_BRIGHT, "[%s", pExpr->Use.Var.pszIdentifier);
            if (pExpr->Use.Var.pDecId != NULL) ConsolePrintf(CON_YELLOW_BRIGHT, ":%d] ", pExpr->Use.Var.pDecId->Use.DecId.iOffset);     // variable offset
            else                               ConsolePrintf(CON_YELLOW_BRIGHT, "] ");                                                  // variable is global
            PrintType(iDepth, pExpr);
            break;
        case    uUnary:     
            ConsoleIndent(iDepth);
            printf("%s ", Uops[pExpr->Use.Unary.Op]);
            PrintType(iDepth, pExpr);
            GenExpressionPrettyPrint(iDepth + 1, pExpr->Use.Unary.pOperand);
            break;
        case    uBinary:    
            GenExpressionPrettyPrint(iDepth + 1, pExpr->Use.Binary.pLeft);
            ConsoleIndent(iDepth);
            printf("%s ", Bops[pExpr->Use.Unary.Op]);
            PrintType(iDepth, pExpr);
            GenExpressionPrettyPrint(iDepth + 1, pExpr->Use.Binary.pRight);
            break;
        case    uTernary:   
            ConsoleIndent(iDepth);
            printf("Tern ");
            PrintType(iDepth, pExpr);
            GenExpressionPrettyPrint(iDepth + 1, pExpr->Use.Ternary.pFirst);
            ConsoleIndent(iDepth);
            printf("Then\n");
            GenExpressionPrettyPrint(iDepth + 1, pExpr->Use.Ternary.pSecond);
            ConsoleIndent(iDepth);
            printf("Else\n");
            GenExpressionPrettyPrint(iDepth + 1, pExpr->Use.Ternary.pThird);
            break;
        case    uDot:       
            GenExpressionPrettyPrint(iDepth + 1, pExpr->Use.Dot.pRecord);
            ConsoleIndent(iDepth);
            printf("Dot ");
            PrintType(iDepth, pExpr);
            ConsoleIndent(iDepth);
            printf("[%s:%d]\n", pExpr->Use.Dot.pszField, pExpr->Use.Dot.iOffset);
            break;
        case    uArrow:     
            GenExpressionPrettyPrint(iDepth + 1, pExpr->Use.Arrow.pRecord);
            ConsoleIndent(iDepth);
            printf("Arrow ");
            PrintType(iDepth, pExpr);
            ConsoleIndent(iDepth);
            printf("[%s:%d]\n", pExpr->Use.Arrow.pszField, pExpr->Use.Arrow.iOffset);
            break;
        case    uArray:     
            GenExpressionPrettyPrint(iDepth + 1, pExpr->Use.Array.pVector);
            ConsoleIndent(iDepth);
            printf("Array ");
            PrintType(iDepth, pExpr);
            GenExpressionPrettyPrint(iDepth + 1, pExpr->Use.Array.pIndex);
            break;
        case    uFunc:      
            GenExpressionPrettyPrint(iDepth + 1, pExpr->Use.Func.pFunc);
            ConsoleIndent(iDepth);
            printf("Function ");
            PrintType(iDepth, pExpr);
            GenExpressionPrettyPrint(iDepth + 1, pExpr->Use.Func.pParams);
            break;
        case    uCast:      
            ConsoleIndent(iDepth);
            printf("Cast %s", pszCasts[pExpr->Use.Cast.Op]);
            PrintType(iDepth, pExpr);
            GenExpressionPrettyPrint(iDepth + 1, pExpr->Use.Cast.pTarget);
            break;
        case    uAssign:    
            ConsoleIndent(iDepth);
            printf("Assign ");
            PrintType(iDepth, pExpr);
            GenExpressionPrettyPrint(iDepth + 1, pExpr->Use.Assign.pLval);
            ConsoleIndent(iDepth);
            printf("%s\n", pszaAssignOps[pExpr->Use.Assign.Op]);
            GenExpressionPrettyPrint(iDepth + 1, pExpr->Use.Assign.pRval);
            break;
        default:            
            Error(FATAL, "ParseExpr: What [%d]\n", pExpr->Usage);
            break;
        }
    }
}



// #################################################################################################
static BOOL IsAllZeros(int iTargetSize, LONG lValue) {
    static const LONG laInv[5] = { 0, 0xFF, 0xFFFF, 0, 0xFFFFFFFF };    // -1 for differnet iTargetSizes
    return ((laInv[iTargetSize] & lValue) == 0);
}

static BOOL IsAllOnes(int iTargetSize, LONG lValue) {
    static const LONG laInv[5] = { 0, 0xFF, 0xFFFF, 0, 0xFFFFFFFF };    // -1 for differnet iTargetSizes
    return ((laInv[iTargetSize] & lValue) == laInv[iTargetSize]);
}


// ##########################################################################
// #  Function: AVR_Move
// #        Move the register contents to another register. 
// #        Works for 8, 16 & 32 bits.
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
void AVR_Move(int iDest, int iSrce, int iTargetSize) {
    ASSERT((iDest & 3) == 0);
    ASSERT((iSrce & 3) == 0);
    switch (iTargetSize) {
    case 1:
        GenAsm("", "mov",  OperandRegReg(iDest + REG_ORDER0, iSrce + REG_ORDER0), "  1:");
        break;
    case 2:
        GenAsm("", "movw", OperandRegReg(iDest + REG_ORDER0, iSrce + REG_ORDER0), "  1:");
        break;
    case 4:
        GenAsm("", "movw", OperandRegReg(iDest + REG_ORDER0, iSrce + REG_ORDER0), "  1:");
        GenAsm("", "movw", OperandRegReg(iDest + REG_ORDER2, iSrce + REG_ORDER2), "  1:");
        break;
    default:
        Error(FATAL, "AVR_Move to unknown sized object");
        return;
    }
}

// ##########################################################################
// #  Function: AVR_Push
// #        Push a register to the stack. 
// #        Works for 8, 16 & 32 bits.
// #        Data in memory will be little endian.
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
int AVR_Push(int iReg, int iTargetSize, LPSTR pszComment) {


    ASSERT((iReg & 3) == 0);

    LPSTR pszC = (pszComment && *pszComment) ? CommentString(2, "push parameter ", pszComment) : "  2:";

    switch (iTargetSize) {
    case 1:
        GenAsm("", "push", OperandReg(iReg + REG_ORDER0), pszC);
        return 1;
    case 2:
        GenAsm("", "push", OperandReg(iReg + REG_ORDER1), pszC);            // stack is push decrementing -> msbyte first to maitain endienness
        GenAsm("", "push", OperandReg(iReg + REG_ORDER0), "  2:");
        return 2;
    case 4:
        GenAsm("", "push", OperandReg(iReg + REG_ORDER3), pszC);
        GenAsm("", "push", OperandReg(iReg + REG_ORDER2), "  2:");
        GenAsm("", "push", OperandReg(iReg + REG_ORDER1), "  2:");
        GenAsm("", "push", OperandReg(iReg + REG_ORDER0), "  2:");
        return 4;
    default:
        Error(FATAL, "AVR_Push to unknown sized object");
        return 0;
    }
}

// ##########################################################################
// #  Function: AVR_Pop
// #        Pop a register from the stack. 
// #        Works for 8, 16 & 32 bits.
// #        Data in memory expected to be little endian.
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
void AVR_Pop(int iReg, int iTargetSize) {
    ASSERT((iReg & 3) == 0);
    switch (iTargetSize) {
    case 1:
        GenAsm("", "pop", OperandReg(iReg+ REG_ORDER0),  "  2:");
        break;
    case 2:
        GenAsm("", "pop", OperandReg(iReg+ REG_ORDER0),  "  2:");            // stack is pop incrementing -> lsbyte first to maitain endienness
        GenAsm("", "pop", OperandReg(iReg+ REG_ORDER1),  "  2:");
        break;
    case 4:
        GenAsm("", "pop", OperandReg(iReg+ REG_ORDER0),  "  2:");
        GenAsm("", "pop", OperandReg(iReg+ REG_ORDER1),  "  2:");
        GenAsm("", "pop", OperandReg(iReg+ REG_ORDER2),  "  2:");
        GenAsm("", "pop", OperandReg(iReg+ REG_ORDER3),  "  2:");
        break;
    default:
        Error(FATAL, "AVR_Pop to unknown sized object");
        return;
    }
}

/*
// ##########################################################################
// #  Function: AVR_LoadImmediate8
// #        Set a register to a constant value.
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
void AVR_LoadImmediate8(int iReg, unsigned char bValue) {
    ASSERT((iReg & 3) == 0);
    ASSERT(iReg >= 16);
    GenAsm("", "ldi",  OperandRegImmediate(iReg + REG_ORDER0, bValue), CommentNumber(1, "Immediate byte ", bValue));
}

// ##########################################################################
// #  Function: AVR_LoadImmediate16
// #        Set a register to a constant value.
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
void AVR_LoadImmediate16(int iReg, unsigned short nValue) {
    ASSERT((iReg & 3) == 0);
    ASSERT(iReg >= 16);
    GenAsm("", "ldi",  OperandRegImmediate(iReg + REG_ORDER0,   (nValue & 0xFF)),      CommentNumber(1, "Immediate short ", nValue));
    GenAsm("", "ldi",  OperandRegImmediate(iReg + REG_ORDER1, ((nValue >> 8) & 0xFF)), "  1:");
}

// ##########################################################################
// #  Function: AVR_LoadImmediate32
// #        Set a register to a constant value.
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
void AVR_LoadImmediate32(int iReg, unsigned long lValue) {
    ASSERT((iReg & 3) == 0);
    ASSERT(iReg >= 16);
    GenAsm("", "ldi", OperandRegImmediate(iReg + REG_ORDER0,   (lValue & 0xFF)),       CommentNumber(1, "Immediate long ", lValue));
    GenAsm("", "ldi", OperandRegImmediate(iReg + REG_ORDER1, ((lValue >> 8) & 0xFF)),  "  1:");
    GenAsm("", "ldi", OperandRegImmediate(iReg + REG_ORDER2, ((lValue >> 16) & 0xFF)), "  1:");
    GenAsm("", "ldi", OperandRegImmediate(iReg + REG_ORDER3, ((lValue >> 24) & 0xFF)), "  1:");
}
*/

/*
// ##########################################################################
// #  Function: AVR_LoadRom8
// #        Read contents of a ROM 'variable'.
// #        reg8 = *Var*
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
void AVR_LoadRom8(int iReg, LPSTR pszVar) {
    ASSERT((iReg & 3) == 0);
    GenAsm("", "ldi", OperandRegVar(30, pszVar),              CommentString(1, "Z = &", pszVar));
    GenAsm("", "ldi", OperandRegVar(31, pszVar),              "  1:");
    GenAsm("", "lpm", OperandRegStr(iReg + REG_ORDER0, "Z"),  CommentString(3, "byte <== ROM @", pszVar));
}

// ##########################################################################
// #  Function: AVR_LoadRom16
// #        Read contents of a ROM 'variable'.
// #        reg16 = *Var*
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
void  AVR_LoadRom16(int iReg, LPSTR pszVar) {
    ASSERT((iReg & 3) == 0);
    GenAsm("", "ldi", OperandRegVar(30, pszVar),              CommentString(1, "Z = &", pszVar));
    GenAsm("", "ldi", OperandRegVar(31, pszVar),              "  1:");
    GenAsm("", "lpm", OperandRegStr(iReg + REG_ORDER0, "Z+"), CommentString(3, "short <== ROM @", pszVar));
    GenAsm("", "lpm", OperandRegStr(iReg + REG_ORDER1, "Z"),  "  3:");
}

// ##########################################################################
// #  Function: AVR_LoadRom32
// #        Read contents of a ROM 'variable'.
// #        reg32 = *Var*
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
void  AVR_LoadRom32(int iReg, LPSTR pszVar) {
    ASSERT((iReg & 3) == 0);
    GenAsm("", "ldi", OperandRegVar(30, pszVar),              CommentString(1, "Z = &", pszVar));
    GenAsm("", "ldi", OperandRegVar(31, pszVar),              "  1:");
    GenAsm("", "lpm", OperandRegStr(iReg + REG_ORDER0, "Z+"), CommentString(3, "long <== ROM @", pszVar));
    GenAsm("", "lpm", OperandRegStr(iReg + REG_ORDER1, "Z+"), "  3:");
    GenAsm("", "lpm", OperandRegStr(iReg + REG_ORDER2, "Z+"), "  3:");
    GenAsm("", "lpm", OperandRegStr(iReg + REG_ORDER3, "Z"),  "  3:");
}
*/

/*
// ##########################################################################
// #  Function: AVR_LoadRam8
// #        Read contents of a RAM 'variable'.
// #        reg8 = *Var*
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
void AVR_LoadRam8(int iReg, LPSTR pszVar) {
//    ASSERT((iReg & 3) == 0);
//    GenAsm("", "ldi", OperandRegVar(30, pszVar),              CommentString(1, "Z = &", pszVar));
//    GenAsm("", "ldi", OperandRegVar(31, pszVar),              "  1:");
//    GenAsm("", "ld",  OperandRegStr(iReg + REG_ORDER0, "Z"),  CommentString(1, "byte <==  RAM @", pszVar)); 

    GenAsm("", "lds", OperandRegStr(iReg, pszVar), CommentString(2, "reg8 <== ", pszVar));
}

// ##########################################################################
// #  Function: AVR_LoadRam16
// #        Read contents of a RAM variable.
// #        reg16 = *Var*
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
void  AVR_LoadRam16(int iReg, LPSTR pszVar) {
    ASSERT((iReg & 1) == 0);
//    GenAsm("", "ldi", OperandRegVar(30, pszVar),                 CommentString(1, "Z = &", pszVar));
//    GenAsm("", "ldi", OperandRegVar(31, pszVar),                 "  1:");
//    GenAsm("", "ld",  OperandRegStr(iReg + REG_ORDER0, "Z"),     CommentString(1, "short <==  RAM @", pszVar));
//    GenAsm("", "ldd", OperandRegDisp(iReg + REG_ORDER1, "Z", 1), "  2:");
    
    GenAsm("", "lds", OperandRegStr(iReg,   pszVar),            CommentString(2, "reg16 <== ", pszVar));
    GenAsm("", "lds", OperandRegStrDisp(iReg+1, pszVar, 1),     "  2:" );

}

// ##########################################################################
// #  Function: AVR_LoadRam32
// #        Read contents of a RAM variable.
// #        reg32 = *Var*
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
void  AVR_LoadRam32(int iReg, LPSTR pszVar) {
    ASSERT((iReg & 3) == 0);
//    GenAsm("", "ldi", OperandRegVar(30, pszVar),                 CommentString(1, "Z = &", pszVar));
//    GenAsm("", "ldi", OperandRegVar(31, pszVar),                 "  1:");
//    GenAsm("", "ld",  OperandRegStr(iReg + REG_ORDER0, "Z"),     CommentString(1, "long <==  RAM @", pszVar));
//    GenAsm("", "ldd", OperandRegDisp(iReg + REG_ORDER1, "Z", 1), "  2:");
//    GenAsm("", "ldd", OperandRegDisp(iReg + REG_ORDER2, "Z", 2), "  2:");
//    GenAsm("", "ldd", OperandRegDisp(iReg + REG_ORDER3, "Z", 3), "  2:");

    GenAsm("", "lds", OperandRegStr(iReg, pszVar), CommentString(2, "reg32 <== ", pszVar));
    GenAsm("", "lds", OperandRegStrDisp(iReg + 1, pszVar, 1), "  2:");
    GenAsm("", "lds", OperandRegStrDisp(iReg + 2, pszVar, 2), "  2:");
    GenAsm("", "lds", OperandRegStrDisp(iReg + 3, pszVar, 3), "  2:");

}
*/

/*
// ##########################################################################
// #  Function: AVR_StoreRam8
// #        Save register to a RAM variable.
// #        *Var = reg8*
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
void AVR_StoreRam8(LPSTR pszVar, int iReg) {
    //ASSERT((iReg & 3) == 0);
//  GenAsm("", "ldi", OperandRegVar(30, pszVar),                 CommentString(1, "Z = &", pszVar));
//  GenAsm("", "ldi", OperandRegVar(31, pszVar),                 "  1:");
//  GenAsm("", "st",  OperandStrReg("Z", iReg + REG_ORDER0),     CommentString(1, "byte ==> RAM @", pszVar));

    GenAsm("", "sts", OperandStrReg(pszVar, iReg), CommentString(2, "reg8 ==> ", pszVar));
}

// ##########################################################################
// #  Function: AVR_StoreRam16
// #        Save register to a RAM variable.
// #        *Var = reg16*
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
void  AVR_StoreRam16(LPSTR pszVar, int iReg) {
    ASSERT((iReg & 1) == 0);
//  GenAsm("", "ldi", OperandRegVar(30, pszVar),                 CommentString(1, "Z = &", pszVar));
//  GenAsm("", "ldi", OperandRegVar(31, pszVar),                 "  1:");
//  GenAsm("", "st",  OperandStrReg("Z", iReg + REG_ORDER0),     CommentString(1, "short ==> RAM @", pszVar));
//  GenAsm("", "std", OperandDispReg("Z", 1, iReg + REG_ORDER1), "  2:");

    GenAsm("", "sts", OperandStrReg(pszVar, iReg),             CommentString(2, "reg16 ==> ", pszVar));
    GenAsm("", "sts", OperandStrDispReg(pszVar, 1, iReg + 1),  "  2:");
}

// ##########################################################################
// #  Function: AVR_StoreRam32
// #        Save register to a RAM variable.
// #        *Var = reg32*
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
void  AVR_StoreRam32(LPSTR pszVar, int iReg) {
    ASSERT((iReg & 3) == 0);
//  GenAsm("", "ldi", OperandRegVar(30, pszVar),                 CommentString(1, "Z = &", pszVar));
//  GenAsm("", "ldi", OperandRegVar(31, pszVar),                 "  1:");
//  GenAsm("", "st",  OperandStrReg("Z", iReg + REG_ORDER0),     CommentString(1, "long ==> RAM @", pszVar));
//  GenAsm("", "std", OperandDispReg("Z", 1, iReg + REG_ORDER1), "  2:");
//  GenAsm("", "std", OperandDispReg("Z", 2, iReg + REG_ORDER2), "  2:");
//  GenAsm("", "std", OperandDispReg("Z", 3, iReg + REG_ORDER3), "  2:");

    GenAsm("", "sts", OperandStrReg(pszVar, iReg),            CommentString(2, "reg32 ==> ", pszVar));
    GenAsm("", "sts", OperandStrDispReg(pszVar, 1, iReg + 1), "  2:");
    GenAsm("", "sts", OperandStrDispReg(pszVar, 2, iReg + 2), "  2:");
    GenAsm("", "sts", OperandStrDispReg(pszVar, 3, iReg + 3), "  2:");


}
*/

/*
// ##########################################################################
// #  Function: AVR_LoadFrame8
// #        Read contents of a variable within the call frame.
// #        *reg8 = Var*
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
void AVR_LoadFrame8(int iReg, int iOffset, LPSTR pszVar) {
    ASSERT((iReg & 3) == 0);
    GenAsm("", "ldd", OperandRegDisp(iReg + REG_ORDER0, "Y", iOffset), CommentString(2, "reg8 <== ", pszVar));
}

// ##########################################################################
// #  Function: AVR_LoadFrame16
// #        Read contents of a variable within the call frame.
// #        *reg8 = Var*
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
void  AVR_LoadFrame16(int iReg, int iOffset, LPSTR pszVar) {
    ASSERT((iReg & 1) == 0);
    ASSERT(((iReg & 1) == 0) && (iReg > 15) && (iOffset < 64));
    GenAsm("", "ldd", OperandRegDisp(iReg + REG_ORDER0,  "Y", iOffset),     CommentString(2, "reg16 <== ", pszVar));
    GenAsm("", "ldd", OperandRegDisp(iReg + REG_ORDER1 , "Y", iOffset+1),   "  2:");
}

// ##########################################################################
// #  Function: AVR_LoadFrame32
// #        Read contents of a variable within the call frame.
// #        *reg8 = Var*
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
void  AVR_LoadFrame32(int iReg, int iOffset, LPSTR pszVar) {
    ASSERT((iReg & 3) == 0);
    GenAsm("", "ldd", OperandRegDisp(iReg + REG_ORDER0, "Y", iOffset),     CommentString(2, "reg32 <== ", pszVar));
    GenAsm("", "ldd", OperandRegDisp(iReg + REG_ORDER1, "Y", iOffset + 1), "  2:");
    GenAsm("", "ldd", OperandRegDisp(iReg + REG_ORDER2, "Y", iOffset + 2), "  2:");
    GenAsm("", "ldd", OperandRegDisp(iReg + REG_ORDER3, "Y", iOffset + 3), "  2:");
}
*/

/*
// ##########################################################################
// #  Function: AVR_StoreFrame8
// #        Store a value in the call frame.
// #        *var = reg8*
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
void AVR_StoreFrame8(int iOffset, int iReg, LPSTR pszVar) {
    ASSERT((iReg & 3) == 0);
    GenAsm("", "std", OperandDispReg("Y", iOffset,   iReg + REG_ORDER0),   CommentString(2, "reg8 ==> ", pszVar));
}

// ##########################################################################
// #  Function: AVR_StoreFrame16
// #        Store a value in the call frame.
// #        *var = reg16*
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
void  AVR_StoreFrame16(int iOffset, int iReg, LPSTR pszVar) {
    ASSERT((iReg & 3) == 0);
    GenAsm("", "std", OperandDispReg("Y", iOffset,   iReg + REG_ORDER0), CommentString(2, "reg16 ==> ", pszVar));
    GenAsm("", "std", OperandDispReg("Y", iOffset+1, iReg + REG_ORDER1), "  2:");
}

// ##########################################################################
// #  Function: AVR_StoreFrame32
// #        Store a value in the call frame.
// #        *var = reg32*
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
void  AVR_StoreFrame32(int iOffset, int iReg, LPSTR pszVar) {
    ASSERT((iReg & 3) == 0);
    GenAsm("", "std", OperandDispReg("Y", iOffset,   iReg + REG_ORDER0), CommentString(2, "reg32 ==> ", pszVar));
    GenAsm("", "std", OperandDispReg("Y", iOffset+1, iReg + REG_ORDER1), "  2:");
    GenAsm("", "std", OperandDispReg("Y", iOffset+2, iReg + REG_ORDER2), "  2:");
    GenAsm("", "std", OperandDispReg("Y", iOffset+3, iReg + REG_ORDER3), "  2:");
}

*/

// ############################################################################################


// ##########################################################################
// #  Function: GenAdd
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
void GenAdd(int iReg, TPExprNode pExpr) {

    TPExprNode pLeft = pExpr->Use.Binary.pLeft;                                 // Left
    TPExprNode pRight = pExpr->Use.Binary.pRight;                               // Right
    int iLeftSize = CalcSizeOf(pLeft->pType);                                   //
    int iRightSize = CalcSizeOf(pRight->pType);                                 //
    ASSERT(iLeftSize == iRightSize);                                            // Confirm sizes match. This should be correct because of the initial parsing phase.

     
    // Calculate Left & Right (Order irelevant)
    _GenExpr(iReg, pLeft);                                                      // Generate Left.
   
    if (pRight->Usage == uConst) {                                                                                                  // easy optimization if RVal is constant.
        LONG lV = -pRight->Use.Const.lInteger;                                                                                      //
        if (lV == 0) {                                                                                                              //
            return;                                                                                                                 //
        }                                                                                                                           //
        switch (iLeftSize) {                                                                                                        //
        case 1:                                                                                                                     //
            GenAsm("", "subi", OperandRegImmediate(iReg + REG_ORDER0, (UCHAR)(lV)),       CommentNumber(1, "Add8 #", -lV));         //
            break;                                                                                                                  //
        case 2:                                                                                                                     //
            GenAsm("", "subi", OperandRegImmediate(iReg + REG_ORDER0, (UCHAR)(lV)),       CommentNumber(1, "Add16 #", -lV));        //
            GenAsm("", "sbci", OperandRegImmediate(iReg + REG_ORDER1, (UCHAR)(lV >> 8)),  "  1:");                                  //
            break;                                                                                                                  //
        case 4:                                                                                                                     //
            GenAsm("", "subi", OperandRegImmediate(iReg + REG_ORDER0, (UCHAR)(lV)),       CommentNumber(1, "Add32 #", -lV));        //
            GenAsm("", "sbci", OperandRegImmediate(iReg + REG_ORDER1, (UCHAR)(lV >> 8)),  "  1:");                                  //
            GenAsm("", "sbci", OperandRegImmediate(iReg + REG_ORDER2, (UCHAR)(lV >> 16)), "  1:");                                  //
            GenAsm("", "sbci", OperandRegImmediate(iReg + REG_ORDER3, (UCHAR)(lV >> 18)), "  1:");                                  //
            break;                                                                                                                  //
        default:                                                                                                                    //
            Error(FATAL, "GenAdd: size not supported (%d)\n", iLeftSize);                                                           //
        }
        return;
    }

    ASSERT(iReg == REG_ACC);
//    if (iReg != REG_ACC) {
//#pragma message("    **** TEMP: Nasty fix to get code volume results")                              // Dirty hack to ensure we get output fit for code volume comparisons.
//        GenAsm("", "nop", "", "  1:   ****** Expression too complex for available resisters.");     // It is exceedingly rare but it blocked code generation and hence size metrics.
//        return;                                                                                     // 
//    }


    if (_GenCostOfCalculation(pRight) == 1) {                                   //
        _GenExpr(REG_TMP, pRight);                                              // Generate Right direct to tmp reg.
    }                                                                           //  
    else {                                                                      //
        AVR_Push(REG_ACC, iLeftSize, "");                                       //    
        _GenExpr(iReg, pRight);                                                 // Generate Right. (reg preservation required)
        AVR_Pop(REG_TMP, iLeftSize);                                            //
    }

    switch (iLeftSize) {
    case 1: 
        GenAsm("", "add", OperandRegReg(REG_ACC0, REG_TMP0), "  1: Add_8");
        break;
    case 2:
        GenAsm("", "add", OperandRegReg(REG_ACC0, REG_TMP0),  "  1: Add_16");
        GenAsm("", "adc", OperandRegReg(REG_ACC1, REG_TMP1),  "  1:");
        break;
    case 4:
        GenAsm("", "add", OperandRegReg(REG_ACC0, REG_TMP0),  "  1:: Add_32");
        GenAsm("", "adc", OperandRegReg(REG_ACC1, REG_TMP1),  "  1:");
        GenAsm("", "adc", OperandRegReg(REG_ACC2, REG_TMP2),  "  1:");
        GenAsm("", "adc", OperandRegReg(REG_ACC3, REG_TMP3),  "  1:");
        break;
    default:
        Error(FATAL, "GenAdd: size not supported (%d)\n", iLeftSize);
    }
}

// ##########################################################################
// #  Function: GenSub
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
void GenSub(int iReg, TPExprNode pExpr) {

    int iLeftSize;                                                                                      //
    int iRightSize;                                                                                     //
    TPExprNode pLeft = pExpr->Use.Binary.pLeft;                                                         // Left
    TPExprNode pRight = pExpr->Use.Binary.pRight;                                                       // Right

    iLeftSize  = (pLeft->pType->Usage == DecArray)  ? SIZE_PTR_DEFAULT : CalcSizeOf(pLeft->pType);      //
    iRightSize = (pRight->pType->Usage == DecArray) ? SIZE_PTR_DEFAULT : CalcSizeOf(pRight->pType);     //

    ASSERT(iLeftSize == iRightSize);                                                                    // Confirm sizes match. This should be correct because of the initial parsing phase.

                                                                                // Calculate Left & Right (Order preserved)
    _GenExpr(iReg, pLeft);                                                      // Generate Left.

    if (pRight->Usage == uConst) {                                                                                                  // easy optimization if RVal is constant.
        LONG lV = pRight->Use.Const.lInteger;                                                                                       //
        if (lV == 0) {                                                                                                              //
            return;                                                                                                                 //
        }                                                                                                                           //
        switch (iLeftSize) {                                                                                                        //
        case 1:                                                                                                                     //
            GenAsm("", "subi", OperandRegImmediate(iReg + REG_ORDER0, (UCHAR)(lV)),       CommentNumber(1, "Sub8 #", lV));          //
            break;                                                                                                                  //
        case 2:                                                                                                                     //
            GenAsm("", "subi", OperandRegImmediate(iReg + REG_ORDER0, (UCHAR)(lV)),       CommentNumber(1, "Sub16 #", lV));         //
            GenAsm("", "sbci", OperandRegImmediate(iReg + REG_ORDER1, (UCHAR)(lV >> 8)),  "  1:");                                  //
            break;                                                                                                                  //
        case 4:                                                                                                                     //
            GenAsm("", "subi", OperandRegImmediate(iReg + REG_ORDER0, (UCHAR)(lV)),       CommentNumber(1, "Sub32 #", lV));         //
            GenAsm("", "sbci", OperandRegImmediate(iReg + REG_ORDER1, (UCHAR)(lV >> 8)),  "  1:");                                  //
            GenAsm("", "sbci", OperandRegImmediate(iReg + REG_ORDER2, (UCHAR)(lV >> 16)), "  1:");                                  //
            GenAsm("", "sbci", OperandRegImmediate(iReg + REG_ORDER3, (UCHAR)(lV >> 18)), "  1:");                                  //
            break;                                                                                                                  //
        default:                                                                                                                    //
            Error(FATAL, "GenSub: size not supported (%d)\n", iLeftSize);                                                           //
        }
        return;
    }

    ASSERT(iReg == REG_ACC);
//#pragma message("    **** DEBUG GenSub(): Reg overload forgiven to enable test compile. Faulty code generated.")
    if (_GenCostOfCalculation(pRight) == 1) {                                   //
        _GenExpr(REG_TMP, pRight);                                              // Generate Right direct to tmp reg.
    }                                                                           //
    else {                                                                      //
        AVR_Push(REG_ACC, iLeftSize, "");                                       //
        _GenExpr(iReg, pRight);                                                 // Generate Right. (reg preservation required)
        AVR_Move(REG_TMP, REG_ACC, iLeftSize);                                  //
        AVR_Pop(REG_ACC, iLeftSize);                                            //
    }                                                                           //

    switch (iLeftSize) {
    case 1:
        GenAsm("", "sub", OperandRegReg(REG_ACC0, REG_TMP0),  "  1: Sub 8");
        break;
    case 2:
        GenAsm("", "sub", OperandRegReg(REG_ACC0, REG_TMP0), "  1: Sub 16");
        GenAsm("", "sbc", OperandRegReg(REG_ACC1, REG_TMP1), "  1:");
        break;
    case 4:
        GenAsm("", "sub", OperandRegReg(REG_ACC0, REG_TMP0), "  1: Sub 32");
        GenAsm("", "sbc", OperandRegReg(REG_ACC1, REG_TMP1), "  1:");
        GenAsm("", "sbc", OperandRegReg(REG_ACC2, REG_TMP2), "  1:");
        GenAsm("", "sbc", OperandRegReg(REG_ACC3, REG_TMP3), "  1:");
        break;
    default:
        Error(FATAL, "GenSub: size not supported (%d)\n", iLeftSize);
    }
}

// ##########################################################################
// #  Function: GenMul
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
void GenMul(int iReg, TPExprNode pExpr) {

    TPExprNode pLeft = pExpr->Use.Binary.pLeft;                                 // Left
    TPExprNode pRight = pExpr->Use.Binary.pRight;                               // Right
    int iLeftSize = CalcSizeOf(pLeft->pType);                                   //
    int iRightSize = CalcSizeOf(pRight->pType);                                 //
    ASSERT(iLeftSize == iRightSize);                                            // Confirm sizes match. This should be correct because of the initial parsing phase.

    if (pRight->Usage == uConst) {                                              // ? * const
        _GenExpr(iReg, pLeft);                                                  // Generate Right. (reg preservation required)
        switch (pRight->Use.Const.lInteger) {
        case 1: 
            GenAsm("", "", "", "  0: Multiply by 1"); 
            return;
        case 2: 
            GenAsm("", "add", OperandRegReg(iReg, iReg), "  1: Multiply by 2");
            if (iLeftSize == 1) return;
            GenAsm("", "adc", OperandRegReg(iReg+1, iReg+1), "  1: ");
            if (iLeftSize == 2) return;
            GenAsm("", "adc", OperandRegReg(iReg + 2, iReg + 2), "  1: ");
            GenAsm("", "adc", OperandRegReg(iReg + 3, iReg + 3), "  1: ");
            return;
        default:
            GenAsm("", "", "", "  x: DEBUGG Multiply by const needed.");
            return;
        }
    }

    ASSERT(iReg == REG_ACC);

                                                                                // Calculate Left & Right (Order reversed)
    _GenExpr(iReg, pLeft);                                                      // Generate Left.
    if (_GenCostOfCalculation(pRight) == 1) {                                   //
        _GenExpr(REG_TMP, pRight);                                              // Generate Right direct to tmp reg.
    }                                                                           //  
    else {                                                                      //
        AVR_Push(REG_ACC, iLeftSize, "");                                       //    
        _GenExpr(iReg, pRight);                                                 // Generate Right. (reg preservation required)
        AVR_Pop(REG_TMP, iLeftSize);                                            //
    }
#pragma message("    GenMul: right var = const is a common special case.")

    LPSTR   szMulLoop = GenLabel("_MulMult_");
    LPSTR   szMulDone = GenLabel("_MulDone_");

    switch (iLeftSize) {
    case 1:
        GenAsm("",        "clr",  OperandReg(0),                    "  1: Mul 8");
        GenAsm(szMulLoop, "sbrc", OperandRegImmediate(REG_ACC0, 0), "1/3:");
        GenAsm("",        "add",  OperandRegReg(0, REG_TMP0),       "  1:");
        GenAsm("",        "lsl",  OperandReg(REG_TMP0),             "  1:");
        GenAsm("",        "breq", szMulDone,                        "1/2:");
        GenAsm("",        "lsr",  OperandReg(REG_ACC0),             "  1:");
        GenAsm("",        "brne", szMulLoop,                        "1/2:");
        GenAsm(szMulDone, "mov",  OperandRegReg(REG_ACC0, 0),       "  1:");
        break;
    case 2:
        GenAsm("", ASM_CALL_OPCODE,"SysMul16",                              " +3: Mul 16");     // REG_ACC0,1 *= REG_TMP0,1
        break;
    case 4:
        GenAsm("", ASM_CALL_OPCODE,"SysMul32",                              " +3: Mul 32");     // REG_ACC0-3 *= REG_TMP0-3
        break;
    default:
        Error(FATAL, "GenMul: size not supported (%d)\n", iLeftSize);
    }
}


// ##########################################################################
// #  Function: GenDiv
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
void GenDiv(int iReg, TPExprNode pExpr) {

    TPExprNode pLeft = pExpr->Use.Binary.pLeft;                                 // Left
    TPExprNode pRight = pExpr->Use.Binary.pRight;                               // Right
    int iLeftSize = CalcSizeOf(pLeft->pType);                                   //
    int iRightSize = CalcSizeOf(pRight->pType);                                 //
    ASSERT(iLeftSize == iRightSize);                                            // Confirm sizes match. This should be correct because of the initial parsing phase.
    ASSERT(iReg == REG_ACC);

    _GenExpr(iReg, pLeft);                                                      // Generate Left.

    if (pRight->Usage == uConst) {                                              // div by some constants is easy to optimize.
        switch (pRight->Use.Const.lInteger) {                                   //
        case 0:                                                                 //
            Error(ERROR0, "GenDiv: Division by Cobstan Zero.\n");               // div zero is not healthy
            return;                                                             //
        case 1:                                                                 // div one  is do nop
            return;
#pragma message("    GenDiv: right var = const is a common special case.")
            // diferent sizes need for shift  also sign propogate top bit!

        }
    }
                                                                                // Calculate Left & Right (Order preserved)
    if (_GenCostOfCalculation(pRight) == 1) {                                   //
        _GenExpr(REG_TMP, pRight);                                              // Generate Right direct to tmp reg.
    }                                                                           //
    else {                                                                      //
        AVR_Push(REG_ACC, iLeftSize, "");                                       //
        _GenExpr(iReg, pRight);                                                 // Generate Right. (reg preservation required)
        AVR_Move(REG_TMP, REG_ACC, iLeftSize);                                  //
        AVR_Pop(REG_ACC, iLeftSize);                                            //
    }                                                                           //

    LPSTR   szDivLoop = GenLabel("_DivLoop_");
    LPSTR   szDivEntr = GenLabel("_DivEntr_");

    switch (iLeftSize) {
    case 1:
        GenAsm("",        "clr",  OperandReg(REG_TMP1),              "  1: Div 8");   // unsigned
        GenAsm("",        "ldi",  OperandRegImmediate(REG_ACC3,9),   "  1:");
        GenAsm("",        "rjmp", szDivEntr,                         "  2:");
        GenAsm(szDivLoop, "rol",  OperandReg(REG_TMP1),              "  1:");
        GenAsm("",        "cp",   OperandRegReg(REG_TMP1, REG_TMP0), "  1:");
        GenAsm("",        "brcs", szDivEntr,                         "1/3:");
        GenAsm("",        "sub",  OperandRegReg(REG_TMP1, REG_TMP0), "  1:");
        GenAsm(szDivEntr, "rol",  OperandReg(REG_ACC0),              "  1:");
        GenAsm("",        "dec",  OperandReg(REG_ACC3),              "  1:");
        GenAsm("",        "brne", szDivLoop,                         "  1:");
        GenAsm("",        "com",  OperandReg(REG_ACC0),              "  1:");
        break;
    case 2:
        GenAsm("", ASM_CALL_OPCODE,"SysDiv16",                          " +3: Div 1");                   // REG_ACC0,1 *= REG_TMP0,1, r0 = remainder
        break;
    case 4:
        GenAsm("", ASM_CALL_OPCODE,"SysDiv32",                          " +3: Div 32");                  // REG_ACC0,1 *= REG_TMP0,1, r0 = remainder
        break;
    default:
        Error(FATAL, "GenDiv: size not supported (%d)\n", iLeftSize);
    }
}

// ##########################################################################
// #  Function: GenMod
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
void GenMod(int iReg, TPExprNode pExpr) {

    TPExprNode pLeft = pExpr->Use.Binary.pLeft;                                 // Left
    TPExprNode pRight = pExpr->Use.Binary.pRight;                               // Right
    int iLeftSize = CalcSizeOf(pLeft->pType);                                   //
    int iRightSize = CalcSizeOf(pRight->pType);                                 //
    ASSERT(iLeftSize == iRightSize);                                            // Confirm sizes match. This should be correct because of the initial parsing phase.
    ASSERT(iReg == REG_ACC);

    // Calculate Left & Right (Order preserved)
    _GenExpr(iReg, pLeft);                                                      // Generate Left.
    if (_GenCostOfCalculation(pRight) == 1) {                                   //
        _GenExpr(REG_TMP, pRight);                                              // Generate Right direct to tmp reg.
    }                                                                           //
    else {                                                                      //
        AVR_Push(REG_ACC, iLeftSize, "");                                       //
        _GenExpr(iReg, pRight);                                                 // Generate Right. (reg preservation required)
        AVR_Move(REG_TMP, REG_ACC, iLeftSize);                                  //
        AVR_Pop(REG_ACC, iLeftSize);                                            //
    }                                                                           //
#pragma message("    GenMod: right var = const is a common special case.")

    LPSTR   szModLoop = GenLabel("_ModLoop_");
    LPSTR   szModEntr = GenLabel("_ModEntr_");

    switch (iLeftSize) {
    case 1:
        GenAsm("",        "clr",  OperandReg(REG_TMP1),             "  1: Mod 8");
        GenAsm("",        "ldi",  OperandRegImmediate(REG_ACC3, 9), "  1:");
        GenAsm("",        "rjmp", szModEntr,                        "  2:");
        GenAsm(szModLoop, "rol",  OperandReg(REG_TMP1),             "  1:");
        GenAsm("",        "cp",   OperandRegReg(REG_TMP1, REG_TMP0),"  1:");
        GenAsm("",        "brcs", szModEntr,                        "1/3:");
        GenAsm("",        "sub",  OperandRegReg(REG_TMP1, REG_TMP0),"  1:");
        GenAsm(szModEntr, "rol",  OperandReg(REG_ACC0),             "  1:");
        GenAsm("",        "dec",  OperandReg(REG_ACC3),             "  1:");
        GenAsm("",        "brne", szModLoop,                        "  1:");
        GenAsm("",        "mov",  OperandRegReg(REG_ACC0, 0),       "  1:");
        break;
    case 2:
        GenAsm("", ASM_CALL_OPCODE,"SysDiv16",                  " +3: Mod 16");                   // REG_ACC0,1 *= REG_TMP0,1, r0 = remainder
        GenAsm("",        "movw", OperandRegReg(REG_ACC0, 0),  "  1:");
        break;            
    case 4:               
        GenAsm("", ASM_CALL_OPCODE,"SysDiv32",                  " +3: Mod 32");                   // REG_ACC0,1 *= REG_TMP0,1, r0 = remainder
        GenAsm("",        "movw", OperandRegReg(REG_ACC0, 0),  "  1:");
        GenAsm("",        "movw", OperandRegReg(REG_ACC2, 2),  "  1:");
    default:
        Error(FATAL, "GenMod: size not supported (%d)\n", iLeftSize);
    }
}

// ##########################################################################
// #  Function: GenAnd
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
void GenAnd(int iReg, TPExprNode pExpr) {

    TPExprNode pLeft = pExpr->Use.Binary.pLeft;                                 // Left
    TPExprNode pRight = pExpr->Use.Binary.pRight;                               // Right
    int iLeftSize = CalcSizeOf(pLeft->pType);                                   //
    int iRightSize = CalcSizeOf(pRight->pType);                                 //
    ASSERT(iLeftSize == iRightSize);                                            // Confirm sizes match. This should be correct because of the initial parsing phase.
    ASSERT(iReg == REG_ACC);
//#pragma message("    **** DEBUG GenAnd(): Reg overload forgiven to enable test compile. Faulty code generated.")


    if (pRight->Usage == uConst) {                                                                                                  // easy optimization if RVal is constant.
        _GenExpr(iReg, pLeft);                                                      // Generate Left.

        LONG lV = pRight->Use.Const.lInteger;                                                                                       //
        switch (iLeftSize) {                                                                                                        //
        case 1:                                                                                                                     //
            GenAsm("", "andi", OperandRegImmediate(iReg + REG_ORDER0, (UCHAR)(lV)),       CommentNumber(1, "Add8 #", lV));          //
            break;                                                                                                                  //
        case 2:                                                                                                                     //
            GenAsm("", "andi", OperandRegImmediate(iReg + REG_ORDER0, (UCHAR)(lV)),       CommentNumber(1, "Add16 #", lV));         //
            GenAsm("", "andi", OperandRegImmediate(iReg + REG_ORDER1, (UCHAR)(lV >> 8)),  "  1:");                                  //
            break;                                                                                                                  //
        case 4:                                                                                                                     //
            GenAsm("", "andi", OperandRegImmediate(iReg + REG_ORDER0, (UCHAR)(lV)),       CommentNumber(1, "Add32 #", lV));         //
            GenAsm("", "andi", OperandRegImmediate(iReg + REG_ORDER1, (UCHAR)(lV >> 8)),  "  1:");                                  //
            GenAsm("", "andi", OperandRegImmediate(iReg + REG_ORDER2, (UCHAR)(lV >> 16)), "  1:");                                  //
            GenAsm("", "andi", OperandRegImmediate(iReg + REG_ORDER3, (UCHAR)(lV >> 18)), "  1:");                                  //
            break;                                                                                                                  //
        default:                                                                                                                    //
            Error(FATAL, "GenAnd: size not supported (%d)\n", iLeftSize);                                                           //
        }
        return;
    }

    _GenExpr(iReg, pLeft);                                                      // Generate Left.
    if (_GenCostOfCalculation(pRight) == 1) {                                   //
        _GenExpr(REG_TMP, pRight);                                              // Generate Right direct to tmp reg.
    }                                                                           //  
    else {                                                                      //
        AVR_Push(REG_ACC, iLeftSize, "");                                       //    
        _GenExpr(iReg, pRight);                                                 // Generate Right. (reg preservation required)
        AVR_Pop(REG_TMP, iLeftSize);                                            //
    }

    switch (iLeftSize) {
    case 1: 
        GenAsm("", "and", OperandRegReg(REG_ACC0, REG_TMP0), "  1: And 8");
        break;
    case 2:
        GenAsm("", "and", OperandRegReg(REG_ACC0, REG_TMP0),  "  1: And 16");
        GenAsm("", "and", OperandRegReg(REG_ACC1, REG_TMP1),  "  1:");
        break;
    case 4:
        GenAsm("", "and", OperandRegReg(REG_ACC0, REG_TMP0),  "  1: And 32");
        GenAsm("", "and", OperandRegReg(REG_ACC1, REG_TMP1),  "  1:");
        GenAsm("", "and", OperandRegReg(REG_ACC2, REG_TMP2),  "  1:");
        GenAsm("", "and", OperandRegReg(REG_ACC3, REG_TMP3),  "  1:");
        break;
    default:
        Error(FATAL, "GenAnd: size not supported (%d)\n", iLeftSize);
    }
}

// ##########################################################################
// #  Function: GenXor
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
void GenXor(int iReg, TPExprNode pExpr) {

    TPExprNode pLeft = pExpr->Use.Binary.pLeft;                                 // Left
    TPExprNode pRight = pExpr->Use.Binary.pRight;                               // Right
    int iLeftSize = CalcSizeOf(pLeft->pType);                                   //
    int iRightSize = CalcSizeOf(pRight->pType);                                 //
    ASSERT(iLeftSize == iRightSize);                                            // Confirm sizes match. This should be correct because of the initial parsing phase.

    ASSERT(iReg == REG_ACC);
//#pragma message(" **** DEBUG iREG test remomved to get code sample")
    if (iReg != REG_ACC) {
        GenAsm("", "; DEBUG faulty iReg", "","");
    }

                                                                                // Calculate Left & Right (Order reversed)
    _GenExpr(iReg, pLeft);                                                      // Generate Left.
    if (_GenCostOfCalculation(pRight) == 1) {                                   //
        _GenExpr(REG_TMP, pRight);                                              // Generate Right direct to tmp reg.
    }                                                                           //  
    else {                                                                      //
        AVR_Push(REG_ACC, iLeftSize, "");                                       //    
        _GenExpr(iReg, pRight);                                                 // Generate Right. (reg preservation required)
        AVR_Pop(REG_TMP, iLeftSize);                                            //
    }
#pragma message("    GenXor: right var = const is a common special case.")

    switch (iLeftSize) {
    case 1:
        GenAsm("", "eor", OperandRegReg(REG_ACC0, REG_TMP0), "  1: Xor 8");
        break;
    case 2:
        GenAsm("", "eor", OperandRegReg(REG_ACC0, REG_TMP0), "  1: Xor 16");
        GenAsm("", "eor", OperandRegReg(REG_ACC1, REG_TMP1), "  1:");
        break;
    case 4:
        GenAsm("", "eor", OperandRegReg(REG_ACC0, REG_TMP0), "  1: Xor 32");
        GenAsm("", "eor", OperandRegReg(REG_ACC1, REG_TMP1), "  1:");
        GenAsm("", "eor", OperandRegReg(REG_ACC2, REG_TMP2), "  1:");
        GenAsm("", "eor", OperandRegReg(REG_ACC2, REG_TMP3), "  1:");
        break;
    default:
        Error(FATAL, "GenXor: size not supported (%d)\n", iLeftSize);
    }
}

// ##########################################################################
// #  Function: GenOr
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
void GenOr(int iReg, TPExprNode pExpr) {

    TPExprNode pLeft = pExpr->Use.Binary.pLeft;                                 // Left
    TPExprNode pRight = pExpr->Use.Binary.pRight;                               // Right
    int iLeftSize = CalcSizeOf(pLeft->pType);                                   //
    int iRightSize = CalcSizeOf(pRight->pType);                                 //
    ASSERT(iLeftSize == iRightSize);                                            // Confirm sizes match. This should be correct because of the initial parsing phase.
    ASSERT(iReg == REG_ACC);

                                                                                // Calculate Left & Right 
    _GenExpr(iReg, pLeft);                                                      // Generate Left.

    if (pRight->Usage == uConst) {                                                                                                  // easy optimization if RVal is constant.
        LONG lV = pRight->Use.Const.lInteger;                                                                                       //
        if (lV == 0) {                                                                                                              //
            return;                                                                                                                 //
        }                                                                                                                           //
        switch (iLeftSize) {                                                                                                        //
        case 1:                                                                                                                     //
            GenAsm("", "ori", OperandRegImmediate(iReg + REG_ORDER0, (UCHAR)(lV)),       CommentNumber(1, "Or8 #", lV));            //
            break;                                                                                                                  //
        case 2:                                                                                                                     //
            GenAsm("", "ori", OperandRegImmediate(iReg + REG_ORDER0, (UCHAR)(lV)),       CommentNumber(1, "Or16 #", lV));           //
            GenAsm("", "ori", OperandRegImmediate(iReg + REG_ORDER1, (UCHAR)(lV >> 8)),  "  1:");                                   //
            break;                                                                                                                  //
        case 4:                                                                                                                     //
            GenAsm("", "ori", OperandRegImmediate(iReg + REG_ORDER0, (UCHAR)(lV)),       CommentNumber(1, "Or32 #", lV));           //
            GenAsm("", "ori", OperandRegImmediate(iReg + REG_ORDER1, (UCHAR)(lV >> 8)),  "  1:");                                   //
            GenAsm("", "ori", OperandRegImmediate(iReg + REG_ORDER2, (UCHAR)(lV >> 16)), "  1:");                                   //
            GenAsm("", "ori", OperandRegImmediate(iReg + REG_ORDER3, (UCHAR)(lV >> 18)), "  1:");                                   //
            break;                                                                                                                  //
        default:                                                                                                                    //
            Error(FATAL, "GenOr: size not supported (%d)\n", iLeftSize);                                                            //
        }
        return;
    }

    if (_GenCostOfCalculation(pRight) == 1) {                                   //
        _GenExpr(REG_TMP, pRight);                                              // Generate Right direct to tmp reg.
    }                                                                           //  
    else {                                                                      //
        AVR_Push(REG_ACC, iLeftSize, "");                                       //    
        _GenExpr(iReg, pRight);                                                 // Generate Right. (reg preservation required)
        AVR_Pop(REG_TMP, iLeftSize);                                            //
    }

#pragma message("    GenOr: right var = const is a common special case.")

    switch (iLeftSize) {
    case 1:
        GenAsm("", "or",  OperandRegReg(REG_ACC0, REG_TMP0), "  1: Or 8");
        break;
    case 2:
        GenAsm("", "or",  OperandRegReg(REG_ACC0, REG_TMP0), "  1: Or 16");
        GenAsm("", "or",  OperandRegReg(REG_ACC1, REG_TMP1), "  1:");
        break;
    case 4:
        GenAsm("", "or",  OperandRegReg(REG_ACC0, REG_TMP0), "  1: Or 32");
        GenAsm("", "or",  OperandRegReg(REG_ACC1, REG_TMP1), "  1:");
        GenAsm("", "or",  OperandRegReg(REG_ACC2, REG_TMP2), "  1:");
        GenAsm("", "or",  OperandRegReg(REG_ACC3, REG_TMP3), "  1:");
        break;
    default:
        Error(FATAL, "GenOr: size not supported (%d)\n", iLeftSize);
    }
}

// ##########################################################################
// #  Function: GenShiftR
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
void GenShiftR(int iReg, TPExprNode pExpr) {

    TPExprNode pLeft = pExpr->Use.Binary.pLeft;                                 // Left
    TPExprNode pRight = pExpr->Use.Binary.pRight;                               // Right
    int iLeftSize = CalcSizeOf(pLeft->pType);                                   //
    int iRightSize = CalcSizeOf(pRight->pType);                                 //
    //ASSERT(iRightSize == 1);                                                    // Confirm sizes match. This should be correct because of the initial parsing phase.
    ASSERT(iReg == REG_ACC);

    _GenExpr(iReg, pRight);                                                     // Generate Right. (deliberate reverse order)
    AVR_Push(REG_ACC, iRightSize, "");
    _GenExpr(iReg, pLeft);                                                      // Generate Left.
    AVR_Pop(REG_TMP, iRightSize);
#pragma message("    GenShiftR: right var = const is a common special case.")

    BOOL fSigned = TypeIsSigned(pLeft->pType);
    LPSTR   szRotDone = GenLabel("_RSLdone_");
    LPSTR   szRepeat = GenLabel("_RSLagain_");

    GenAsm("",                         "Tst",  OperandReg(REG_TMP0), "  1: Shift Right");
    GenAsm("",                         "breq", szRotDone,             "2/3:");

    switch (iLeftSize) {
    case 1:
        if (fSigned) GenAsm(szRepeat, "asr", OperandReg(REG_ACC0),   "  1: >> 8 (signed)");
        else         GenAsm(szRepeat, "lsr", OperandReg(REG_ACC0),   "  1: >> 8 (unsigned)");
        break;                                                 
    case 2:                                                    
        if (fSigned) GenAsm(szRepeat, "asr", OperandReg(REG_ACC1),   "  1: >> 16 (signed)");
        else         GenAsm(szRepeat, "lsr", OperandReg(REG_ACC1),   "  1: >> 16 (unsigned)");
        GenAsm("",                    "ror", OperandReg(REG_ACC0),   "  1:");
        break;                                                 
    case 4:                                                    
        if (fSigned) GenAsm(szRepeat, "asr", OperandReg(REG_ACC3),   "  1: >> 32 (signed)");
        else         GenAsm(szRepeat, "lsr", OperandReg(REG_ACC3),   "  1: >> 32 (unsigned)");
        GenAsm("",                    "ror", OperandReg(REG_ACC2),   "  1:");
        GenAsm("",                    "ror", OperandReg(REG_ACC1),   "  1:");
        GenAsm("",                    "ror", OperandReg(REG_ACC0),   "  1:");
        break;
    default:
        Error(FATAL, "GenShiftR: size not supported (%d)\n", iLeftSize);
    }
    GenAsm("",                        "dec", OperandReg(REG_TMP0), "  1:");
    GenAsm("",                        "brne", szRepeat,            "2/3:");
    GenAsm(szRotDone,                 "",     "",                  "---: Shift Right done.");
}

// ##########################################################################
// #  Function: GenShiftL
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
void GenShiftL(int iReg, TPExprNode pExpr) {

    TPExprNode pLeft = pExpr->Use.Binary.pLeft;                                 // Left
    TPExprNode pRight = pExpr->Use.Binary.pRight;                               // Right
    int iLeftSize = CalcSizeOf(pLeft->pType);                                   //
    int iRightSize = CalcSizeOf(pRight->pType);                                 //
    ASSERT(iRightSize == 1);                                                    // Confirm sizes match. This should be correct because of the initial parsing phase.
    ASSERT(iReg == REG_ACC || iReg == REG_TMP);

    LPSTR   szRotDone = NULL;
    LPSTR   szRepeat = NULL;

    if (pRight->Usage == uConst) {                                                                         // shift by constant.
        _GenExpr(iReg, pLeft);
        int iShift = pRight->Use.Const.lInteger;
        if (iShift > 32) iShift = 32;

        if (pRight->Use.Const.lInteger == 0) {
            GenAsm("", "", "", "   : Shift Left zero places");
            return;
        }
        else if (pRight->Use.Const.lInteger == 8) {                                                         // shift by 8
            switch (iLeftSize) {
            case 1:
                GenAsm("", "clr", OperandReg(iReg + REG_ORDER0),                       "  1: 8 << 8");
                return;
            case 2:
                GenAsm("", "mov", OperandRegReg(iReg + REG_ORDER1, iReg + REG_ORDER0), "  1: 16 << 8");
                GenAsm("", "clr", OperandReg(iReg + REG_ORDER0),                       "  1:");
                return;;
            case 4:
                GenAsm("", "mov", OperandRegReg(iReg + REG_ORDER3, iReg + REG_ORDER2), "  1: 32 << 8");
                GenAsm("", "mov", OperandRegReg(iReg + REG_ORDER2, iReg + REG_ORDER1), "  1: ");
                GenAsm("", "mov", OperandRegReg(iReg + REG_ORDER1, iReg + REG_ORDER0), "  1: ");
                GenAsm("", "clr", OperandReg(iReg + REG_ORDER0),                       "  1:");
                return;
            default:
                Error(FATAL, "GenShiftL: size not supported (%d)\n", iLeftSize);
            }

        }
        else if (pRight->Use.Const.lInteger == 16) {                                                         // shift by 18
            switch (iLeftSize) {
            case 1:
                GenAsm("", "clr", OperandReg(iReg + REG_ORDER0), "  1: 8 << 16");
                return;
            case 2:
                GenAsm("", "clr", OperandReg(iReg + REG_ORDER1), "  1: 16 << 16");
                GenAsm("", "clr", OperandReg(iReg + REG_ORDER0), "  1:");
                return;;
            case 4:
                GenAsm("", "movw", OperandRegReg(iReg + REG_ORDER2, iReg + REG_ORDER0), "  1: 32 << 16");
                GenAsm("", "clr", OperandReg(iReg + REG_ORDER1), "  1:");
                GenAsm("", "clr", OperandReg(iReg + REG_ORDER0), "  1:");
                return;
            default:
                Error(FATAL, "GenShiftL: size not supported (%d)\n", iLeftSize);
            }
        }
        else if (pRight->Use.Const.lInteger == 24) {                                                         // shift by 24
            switch (iLeftSize) {
            case 1:
                GenAsm("", "clr", OperandReg(iReg + REG_ORDER0), "  1: 8 << 24");
                return;
            case 2:
                GenAsm("", "clr", OperandReg(iReg + REG_ORDER1), "  1: 16 << 24");
                GenAsm("", "clr", OperandReg(iReg + REG_ORDER0), "  1:");
                return;;
            case 4:
                GenAsm("", "mov", OperandRegReg(iReg + REG_ORDER3, iReg + REG_ORDER0), "  1: 32 << 24");
                GenAsm("", "clr", OperandReg(iReg + REG_ORDER2), "  1:");
                GenAsm("", "clr", OperandReg(iReg + REG_ORDER1), "  1:");
                GenAsm("", "clr", OperandReg(iReg + REG_ORDER0), "  1:");
                return;
            default:
                Error(FATAL, "GenShiftL: size not supported (%d)\n", iLeftSize);
            }
        }
        else if (pRight->Use.Const.lInteger == 32) {                                                         // shify by 32 or more
            switch (iLeftSize) {
            case 1:
                GenAsm("", "clr", OperandReg(iReg + REG_ORDER0), "  1: 8 << 32");
                return;
            case 2:
                GenAsm("", "clr", OperandReg(iReg + REG_ORDER1), "  1: 16 << 32");
                GenAsm("", "clr", OperandReg(iReg + REG_ORDER0), "  1:");
                return;;
            case 4:
                GenAsm("", "clr", OperandReg(iReg + REG_ORDER3), "  1: 32 << 32");
                GenAsm("", "clr", OperandReg(iReg + REG_ORDER2), "  1:");
                GenAsm("", "clr", OperandReg(iReg + REG_ORDER1), "  1:");
                GenAsm("", "clr", OperandReg(iReg + REG_ORDER0), "  1:");
                return;
            default:
                Error(FATAL, "GenShiftL: size not supported (%d)\n", iLeftSize);
            }
        }
        else {
            _GenExpr(iReg, pLeft);                                                      // Generate Left.
            GenAsm("", "ldi", OperandRegImmediate(30, iShift), "  1: Shift Left, constant, awkward and non-zero number of bits.");
            GenAsm("", "mov", OperandRegReg(0,30),             "  1: ");
            szRepeat = GenLabel("_LSLagain_");                                          // loop will be needed.
        }
    }
    else {
        _GenExpr(iReg, pRight);                                                     // Generate Right. (deliberate reverse order)
        AVR_Push(iReg, iRightSize, "");
        _GenExpr(iReg, pLeft);                                                      // Generate Left.
        AVR_Pop(0, iRightSize);
        
        szRotDone = GenLabel("_LSLdone_");                                          // loop and exit will be needed.
        szRepeat = GenLabel("_LSLagain_");

        GenAsm("", "Tst", OperandReg(0), "  1: Shift Left");
        GenAsm("", "breq", szRotDone, "2/3:");
    }

    switch (iLeftSize) {
    case 1:
        GenAsm(szRepeat, "lsl", OperandReg(iReg + REG_ORDER0), "  1: << 8");
        break;
    case 2:
        GenAsm(szRepeat, "lsl", OperandReg(iReg + REG_ORDER0), "  1: << 16");
        GenAsm("",       "rol", OperandReg(iReg + REG_ORDER1), "  1:");
        break;
    case 4:
        GenAsm(szRepeat, "lsl", OperandReg(iReg + REG_ORDER0), "  1: << 32");
        GenAsm("",       "rol", OperandReg(iReg + REG_ORDER1), "  1:");
        GenAsm("",       "rol", OperandReg(iReg + REG_ORDER2), "  1:");
        GenAsm("",       "rol", OperandReg(iReg + REG_ORDER3), "  1:");
        break;
    default:
        Error(FATAL, "GenShiftL: size not supported (%d)\n", iLeftSize);
    }
    GenAsm("",           "dec", OperandReg(0),        "  1:");
    GenAsm("",           "brne", szRepeat,            "2/3:");
    if (szRotDone != NULL) {
        GenAsm(szRotDone, "", "", "---: Shift left done.");
    }
}

// ##########################################################################
// #  Function: GenCompEQ
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
void  GenCompEQ(int iReg, TPExprNode pExpr) {

    TPExprNode pLeft = pExpr->Use.Binary.pLeft;                                 // Left
    TPExprNode pRight = pExpr->Use.Binary.pRight;                               // Right
    int iLeftSize = CalcSizeOf(pLeft->pType);                                   //
    int iRightSize = CalcSizeOf(pRight->pType);                                 //
    ASSERT(iLeftSize == iRightSize);                                            // Confirm sizes match. This should be correct because of the initial parsing phase.
    ASSERT(iReg == REG_ACC);

                                                                                // Calculate Left & Right (Order reversed)
    _GenExpr(iReg, pLeft);                                                      // Generate Left.
    if (_GenCostOfCalculation(pRight) == 1) {                                   //
        _GenExpr(REG_TMP, pRight);                                              // Generate Right direct to tmp reg.
    }                                                                           //  
    else {                                                                      //
        AVR_Push(REG_ACC, iLeftSize, "");                                       //    
        _GenExpr(iReg, pRight);                                                 // Generate Right. (reg preservation required)
        AVR_Pop(REG_TMP, iLeftSize);                                            //
    }



    switch (iLeftSize) {
    case 1:
        GenAsm("", "sub", OperandRegReg(REG_ACC0, REG_TMP0),  "  1: Compare EQ 8");
        break;
    case 2: 
        GenAsm("", "sub", OperandRegReg(REG_ACC0, REG_TMP0), "  1: Compare EQ 16");
        GenAsm("", "sbc", OperandRegReg(REG_ACC1, REG_TMP1), "  1:");
        break;
    case 4:
        GenAsm("", "sub", OperandRegReg(REG_ACC0, REG_TMP0), "  1: Compare EQ 32");
        GenAsm("", "sbc", OperandRegReg(REG_ACC1, REG_TMP1), "  1:");
        GenAsm("", "sbc", OperandRegReg(REG_ACC2, REG_TMP2), "  1:");
        GenAsm("", "sbc", OperandRegReg(REG_ACC3, REG_TMP3), "  1:");
        break;
    default:
        Error(FATAL, "GenCompEQ: size not supported (%d)\n", iLeftSize);
    }

    LPSTR   szEqOut = GenLabel("_EqT_");
    GenAsm("",     "breq", szEqOut,                "  1:");
    GenAsm("",     "ser",  OperandReg(REG_ACC0),   "  1:");
    GenAsm(szEqOut,"inc",  OperandReg(REG_ACC0),   "  1:");
    Dispose(szEqOut);
}

// ##########################################################################
// #  Function: GenCompEQConditional
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
void  GenCompEQConditional(int iReg, TPExprNode pExpr, LPSTR pszTrue, LPSTR pszFalse) {

    TPExprNode pLeft = pExpr->Use.Binary.pLeft;                                 // Left
    TPExprNode pRight = pExpr->Use.Binary.pRight;                               // Right
    int iLeftSize = CalcSizeOf(pLeft->pType);                                   //
    int iRightSize = CalcSizeOf(pRight->pType);                                 //
    ASSERT(iLeftSize == iRightSize);                                            // Confirm sizes match. This should be correct because of the initial parsing phase.
    ASSERT(iReg == REG_ACC);

                                                                                // Calculate Left & Right (Order reversed)
    _GenExpr(iReg, pLeft);                                                      // Generate Left.
    if (_GenCostOfCalculation(pRight) == 1) {                                   //
        _GenExpr(REG_TMP, pRight);                                              // Generate Right direct to tmp reg.
    }                                                                           //  
    else {                                                                      //
        AVR_Push(REG_ACC, iLeftSize, "");                                       //    
        _GenExpr(iReg, pRight);                                                 // Generate Right. (reg preservation required)
        AVR_Pop(REG_TMP, iLeftSize);                                            //
    }


    LPSTR   szEqOut = GenLabel("_EqDone_");

    switch (iLeftSize) {
    case 1:
        GenAsm("", "sub", OperandRegReg(REG_ACC0, REG_TMP0),  "  1: Compare EQ 8");
        break;
    case 2: 
        GenAsm("", "sub", OperandRegReg(REG_ACC0, REG_TMP0), "  1: Compare EQ 16");
        GenAsm("", "sbc", OperandRegReg(REG_ACC1, REG_TMP1), "  1:");
        break;
    case 4:
        GenAsm("", "sub", OperandRegReg(REG_ACC0, REG_TMP0), "  1: Compare EQ 32");
        GenAsm("", "sbc", OperandRegReg(REG_ACC1, REG_TMP1), "  1:");
        GenAsm("", "sbc", OperandRegReg(REG_ACC2, REG_TMP2), "  1:");
        GenAsm("", "sbc", OperandRegReg(REG_ACC3, REG_TMP3), "  1:");
        break;
    default:
        Error(FATAL, "GenCompEQConditional: size not supported (%d)\n", iLeftSize);
    }

    if (pszTrue != NULL)  { GenAsm("", "breq", pszTrue,  "1/2:  branch if EQ TRUE"); }
    if (pszFalse != NULL) { GenAsm("", "brne", pszFalse, "1/2:  branch if EQ FALSE"); }
    if (pszTrue == NULL)  { GenAsm("", "",     "",       "   :  fall through on EQ TRUE"); }
    if (pszFalse == NULL) { GenAsm("", "",     "",       "   :  fall through on EQ FALSE"); }
}


// ##########################################################################
// #  Function: GenCompNE
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
void GenCompNE(int iReg, TPExprNode pExpr) {

    TPExprNode pLeft = pExpr->Use.Binary.pLeft;                                 // Left
    TPExprNode pRight = pExpr->Use.Binary.pRight;                               // Right
    int iLeftSize = CalcSizeOf(pLeft->pType);                                   //
    int iRightSize = CalcSizeOf(pRight->pType);                                 //
    ASSERT(iLeftSize == iRightSize);                                            // Confirm sizes match. This should be correct because of the initial parsing phase.
    ASSERT(iReg == REG_ACC);

                                                                                // Calculate Left & Right (Order reversed)
    _GenExpr(iReg, pLeft);                                                      // Generate Left.
    if (_GenCostOfCalculation(pRight) == 1) {                                   //
        _GenExpr(REG_TMP, pRight);                                              // Generate Right direct to tmp reg.
    }                                                                           //  
    else {                                                                      //
        AVR_Push(REG_ACC, iLeftSize, "");                                       //    
        _GenExpr(iReg, pRight);                                                 // Generate Right. (reg preservation required)
        AVR_Pop(REG_TMP, iLeftSize);                                            //
    }


    switch (iLeftSize) {
    case 1:
        GenAsm("", "sub", OperandRegReg(REG_ACC0, REG_TMP0),  "  1: Compare NE 8");
        break;
    case 2: 
        GenAsm("", "sub", OperandRegReg(REG_ACC0, REG_TMP0), "  1: Compare NE 16");
        GenAsm("", "sbc", OperandRegReg(REG_ACC1, REG_TMP1), "  1:");
        break;
    case 4:
        GenAsm("", "sub", OperandRegReg(REG_ACC0, REG_TMP0), "  1: Compare NE 32");
        GenAsm("", "sbc", OperandRegReg(REG_ACC1, REG_TMP1), "  1:");
        GenAsm("", "sbc", OperandRegReg(REG_ACC2, REG_TMP2), "  1:");
        GenAsm("", "sbc", OperandRegReg(REG_ACC3, REG_TMP3), "  1:");
        break;
    default:
        Error(FATAL, "GenCompNe: size not supported (%d)\n", iLeftSize);
    }

    LPSTR   szNeT = GenLabel("_NeT_");  
    GenAsm("",      "breq", szNeT,                  "  1:");
    GenAsm("",      "clr",  OperandReg(REG_ACC0),   "  1:");
    GenAsm("",      "inc",  OperandReg(REG_ACC0),   "  1:");
    GenAsm(szNeT,   "",     "",                       "   :");
    Dispose(szNeT);
}

// ##########################################################################
// #  Function: GenCompNEConditional
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
void GenCompNEConditional(int iReg, TPExprNode pExpr, LPSTR pszTrue, LPSTR pszFalse) {

    TPExprNode pLeft = pExpr->Use.Binary.pLeft;                                 // Left
    TPExprNode pRight = pExpr->Use.Binary.pRight;                               // Right
    int iLeftSize = CalcSizeOf(pLeft->pType);                                   //
    int iRightSize = CalcSizeOf(pRight->pType);                                 //
    ASSERT(iLeftSize == iRightSize);                                            // Confirm sizes match. This should be correct because of the initial parsing phase.
    ASSERT(iReg == REG_ACC);

                                                                                // Calculate Left & Right (Order reversed)
    _GenExpr(iReg, pLeft);                                                      // Generate Left.
    if (_GenCostOfCalculation(pRight) == 1) {                                   //
        _GenExpr(REG_TMP, pRight);                                              // Generate Right direct to tmp reg.
    }                                                                           //  
    else {                                                                      //
        AVR_Push(REG_ACC, iLeftSize, "");                                       //    
        _GenExpr(iReg, pRight);                                                 // Generate Right. (reg preservation required)
        AVR_Pop(REG_TMP, iLeftSize);                                            //
    }

    LPSTR   szNeOut = GenLabel("_NeDone_");

    switch (iLeftSize) {
    case 1:
        GenAsm("", "sub", OperandRegReg(REG_ACC0, REG_TMP0),  "  1: Compare NE 8");
        break;
    case 2: 
        GenAsm("", "sub", OperandRegReg(REG_ACC0, REG_TMP0), "  1: Compare NE 16");
        GenAsm("", "sbc", OperandRegReg(REG_ACC1, REG_TMP1), "  1:");
        break;
    case 4:
        GenAsm("", "sub", OperandRegReg(REG_ACC0, REG_TMP0), "  1: Compare NE 32");
        GenAsm("", "sbc", OperandRegReg(REG_ACC1, REG_TMP1), "  1:");
        GenAsm("", "sbc", OperandRegReg(REG_ACC2, REG_TMP2), "  1:");
        GenAsm("", "sbc", OperandRegReg(REG_ACC3, REG_TMP3), "  1:");
        break;
    default:
        Error(FATAL, "GenCompNEConditional: size not supported (%d)\n", iLeftSize);
    }

    if (pszTrue != NULL)  { GenAsm("", "brne", pszTrue,  "1/2:  branch if NE TRUE"); }
    if (pszFalse != NULL) { GenAsm("", "breq", pszFalse, "1/2:  branch if NE FALSE"); }
    if (pszTrue == NULL)  { GenAsm("", "",     "",       "   :  fall through on NE TRUE"); }
    if (pszFalse == NULL) { GenAsm("", "",     "",       "   :  fall through on NE FALSE"); }
}


// ##########################################################################
// #  Function: GenCompLT
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
void GenCompLT(int iReg, TPExprNode pExpr) {

    TPExprNode pLeft = pExpr->Use.Binary.pLeft;                                 // Left
    TPExprNode pRight = pExpr->Use.Binary.pRight;                               // Right
    int iLeftSize = CalcSizeOf(pLeft->pType);                                   //
    int iRightSize = CalcSizeOf(pRight->pType);                                 //
    ASSERT(iLeftSize == iRightSize);                                            // Confirm sizes match. This should be correct because of the initial parsing phase.
    ASSERT(iReg == REG_ACC);

                                                                                // Calculate Left & Right (Order preserved)
    _GenExpr(iReg, pLeft);                                                      // Generate Left.
    if (_GenCostOfCalculation(pRight) == 1) {                                   //
        _GenExpr(REG_TMP, pRight);                                              // Generate Right direct to tmp reg.
    }                                                                           //
    else {                                                                      //
        AVR_Push(REG_ACC, iLeftSize, "");                                       //
        _GenExpr(iReg, pRight);                                                 // Generate Right. (reg preservation required)
        AVR_Move(REG_TMP, REG_ACC, iLeftSize);                                  //
        AVR_Pop(REG_ACC, iLeftSize);                                            //
    }                                                                           //

    BOOL fSigned = TypeIsSigned(pLeft->pType);
    LPSTR   szTrue  = GenLabel("_LtT_");
    LPSTR   szFalse = GenLabel("_LtF_");
    LPSTR   szOut   = GenLabel("_LtOut_");
    switch (iLeftSize) {
    case 1:
        GenAsm("", "sub", OperandRegReg(REG_ACC0, REG_TMP0), "  1: Compare LT 8");
        break;
    case 2:
        GenAsm("", "sub", OperandRegReg(REG_ACC0, REG_TMP0), "  1: Compare LT 16");
        GenAsm("", "sbc", OperandRegReg(REG_ACC1, REG_TMP1), "  1:");
        break;
    case 4:
        GenAsm("", "sub", OperandRegReg(REG_ACC0, REG_TMP0), "  1: Compare LT 32");
        GenAsm("", "sbc", OperandRegReg(REG_ACC1, REG_TMP1), "  1:");
        GenAsm("", "sbc", OperandRegReg(REG_ACC2, REG_TMP2), "  1:");
        GenAsm("", "sbc", OperandRegReg(REG_ACC3, REG_TMP3), "  1:");
        break;
    default:
        Error(FATAL, "GenCompLT: size not supported (%d)\n", iLeftSize);
    }




    if (fSigned) {
        GenAsm("", "brlt", szTrue, "1/2:  signed");
    }
    else {
        GenAsm("", "brlo", szTrue, "1/2:  unsigned");
    }

    GenAsm(szFalse,     "clr",  OperandReg(REG_ACC0), "  1: False");
    GenAsm("",          "rjmp", szOut,                "  1:");
    GenAsm(szTrue,      "clr",  OperandReg(REG_ACC0), "  1: True");
    GenAsm("",          "inc",  OperandReg(REG_ACC0), "  1:");
    GenAsm(szOut,       "",     "",                   "   :");
    Dispose(szOut);
    Dispose(szFalse);
    Dispose(szTrue);
}


// ##########################################################################
// #  Function: GenCompLTConditional
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
void GenCompLTConditional(int iReg, TPExprNode pExpr, LPSTR pszTrue, LPSTR pszFalse) {

    TPExprNode pLeft = pExpr->Use.Binary.pLeft;                                 // Left
    TPExprNode pRight = pExpr->Use.Binary.pRight;                               // Right
    int iLeftSize = CalcSizeOf(pLeft->pType);                                   //
    int iRightSize = CalcSizeOf(pRight->pType);                                 //
    ASSERT(iLeftSize == iRightSize);                                            // Confirm sizes match. This should be correct because of the initial parsing phase.
    ASSERT(iReg == REG_ACC);

                                                                                // Calculate Left & Right (Order preserved)
    _GenExpr(iReg, pLeft);                                                      // Generate Left.
    if (_GenCostOfCalculation(pRight) == 1) {                                   //
        _GenExpr(REG_TMP, pRight);                                              // Generate Right direct to tmp reg.
    }                                                                           //
    else {                                                                      //
        AVR_Push(REG_ACC, iLeftSize, "");                                       //
        _GenExpr(iReg, pRight);                                                 // Generate Right. (reg preservation required)
        AVR_Move(REG_TMP, REG_ACC, iLeftSize);                                  //
        AVR_Pop(REG_ACC, iLeftSize);                                            //
    }                                                                           //

    BOOL fSigned = TypeIsSigned(pLeft->pType);

    switch (iLeftSize) {
    case 1:
        GenAsm("", "sub", OperandRegReg(REG_ACC0, REG_TMP0), "  1: Compare LT 8");
        break;
    case 2:
        GenAsm("", "sub", OperandRegReg(REG_ACC0, REG_TMP0), "  1: Compare LT 16");
        GenAsm("", "sbc", OperandRegReg(REG_ACC1, REG_TMP1), "  1:");
        break;
    case 4:
        GenAsm("", "sub", OperandRegReg(REG_ACC0, REG_TMP0), "  1: Compare LT 32");
        GenAsm("", "sbc", OperandRegReg(REG_ACC1, REG_TMP1), "  1:");
        GenAsm("", "sbc", OperandRegReg(REG_ACC2, REG_TMP2), "  1:");
        GenAsm("", "sbc", OperandRegReg(REG_ACC3, REG_TMP3), "  1:");
        break;
    default:
        Error(FATAL, "GenCompLTConditional: size not supported (%d)\n", iLeftSize);
    }

    if (pszTrue != NULL) {
        if (fSigned) { GenAsm("", "brlt", pszTrue, "1/2:  branch if (signed) LT TRUE"); }
        else         { GenAsm("", "brlo", pszTrue, "1/2:  branch if (unsigned) LT TRUE"); }
    }
    if (pszFalse != NULL) {
        if (fSigned) { GenAsm("", "brge", pszFalse, "1/2:  branch if (signed) LT FALSE"); }
        else         { GenAsm("", "brsh", pszFalse, "1/2:  branch if (unsigned) LT FALSE"); }
    }
    if (pszTrue == NULL) {
        if (fSigned) { GenAsm("", "", "", "   :  fall through on (signed) LT TRUE"); }
        else         { GenAsm("", "", "", "   :  fall through on (unsigned) LT TRUE"); }
    }
    if (pszFalse == NULL) {
        if (fSigned) { GenAsm("", "", "", "   :  fall through on (signed) LT FALSE"); }
        else         { GenAsm("", "", "", "   :  fall through on (unsigned) LT FALSE"); }
    }

}


// ##########################################################################
// #  Function: GenCompLE
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
void GenCompLE(int iReg, TPExprNode pExpr) {

    TPExprNode pLeft = pExpr->Use.Binary.pLeft;                                 // Left
    TPExprNode pRight = pExpr->Use.Binary.pRight;                               // Right
    int iLeftSize = CalcSizeOf(pLeft->pType);                                   //
    int iRightSize = CalcSizeOf(pRight->pType);                                 //
    ASSERT(iLeftSize == iRightSize);                                            // Confirm sizes match. This should be correct because of the initial parsing phase.
    ASSERT(iReg == REG_ACC);

    // Calculate Left & Right (Order preserved)
    _GenExpr(iReg, pLeft);                                                      // Generate Left.
    if (_GenCostOfCalculation(pRight) == 1) {                                   //
        _GenExpr(REG_TMP, pRight);                                              // Generate Right direct to tmp reg.
    }                                                                           //
    else {                                                                      //
        AVR_Push(REG_ACC, iLeftSize, "");                                       //
        _GenExpr(iReg, pRight);                                                 // Generate Right. (reg preservation required)
        AVR_Move(REG_TMP, REG_ACC, iLeftSize);                                  //
        AVR_Pop(REG_ACC, iLeftSize);                                            //
    }                                                                           //

    BOOL fSigned = TypeIsSigned(pLeft->pType);
    LPSTR   szTrue = GenLabel("_LeT_");
    LPSTR   szFalse = GenLabel("_LeF_");
    LPSTR   szOut = GenLabel("_LeOut_");
    switch (iLeftSize) {
    case 1:
        GenAsm("", "sub", OperandRegReg(REG_TMP0, REG_ACC0), "  1: Compare LE 8");
        break;
    case 2:
        GenAsm("", "sub", OperandRegReg(REG_TMP0, REG_ACC0), "  1: Compare LE 16");
        GenAsm("", "sbc", OperandRegReg(REG_TMP1, REG_ACC1), "  1:");
        break;
    case 4:
        GenAsm("", "sub", OperandRegReg(REG_TMP0, REG_ACC0), "  1: Compare LE 32");
        GenAsm("", "sbc", OperandRegReg(REG_TMP1, REG_ACC1), "  1:");
        GenAsm("", "sbc", OperandRegReg(REG_TMP2, REG_ACC2), "  1:");
        GenAsm("", "sbc", OperandRegReg(REG_TMP3, REG_ACC3), "  1:");
        break;
    default:
        Error(FATAL, "GenCompLE: size not supported (%d)\n", iLeftSize);
    }
    
    if (fSigned) {
        GenAsm("", "brge", szTrue, "1/2:  signed");
    }
    else {
        GenAsm("", "brsh", szTrue, "1/2:  unsigned");
    }

    GenAsm(szFalse,     "clr",  OperandReg(REG_ACC0), "  1:");
    GenAsm("",          "rjmp", szOut,                "  2:");
    GenAsm(szTrue,      "clr",  OperandReg(REG_ACC0), "  1:");
    GenAsm("",          "inc",  OperandReg(REG_ACC0), "  1:");
    GenAsm(szOut,       "",     "",                   "   :");

    Dispose(szOut);
    Dispose(szFalse);
    Dispose(szTrue);

}

// ##########################################################################
// #  Function: GenCompLEConditional
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
void GenCompLEConditional(int iReg, TPExprNode pExpr, LPSTR pszTrue, LPSTR pszFalse) {

    TPExprNode pLeft = pExpr->Use.Binary.pLeft;                                 // Left
    TPExprNode pRight = pExpr->Use.Binary.pRight;                               // Right
    int iLeftSize = CalcSizeOf(pLeft->pType);                                   //
    int iRightSize = CalcSizeOf(pRight->pType);                                 //
    ASSERT(iLeftSize == iRightSize);                                            // Confirm sizes match. This should be correct because of the initial parsing phase.
    ASSERT(iReg == REG_ACC);

    // Calculate Left & Right (Order preserved)
    _GenExpr(iReg, pLeft);                                                      // Generate Left.
    if (_GenCostOfCalculation(pRight) == 1) {                                   //
        _GenExpr(REG_TMP, pRight);                                              // Generate Right direct to tmp reg.
    }                                                                           //
    else {                                                                      //
        AVR_Push(REG_ACC, iLeftSize, "");                                       //
        _GenExpr(iReg, pRight);                                                 // Generate Right. (reg preservation required)
        AVR_Move(REG_TMP, REG_ACC, iLeftSize);                                  //
        AVR_Pop(REG_ACC, iLeftSize);                                            //
    }                                                                           //

    BOOL fSigned = TypeIsSigned(pLeft->pType);
    LPSTR   szTrue = GenLabel("_LeTrue_");
    LPSTR   szOut = GenLabel("_LeOut_");
    switch (iLeftSize) {
    case 1:
        GenAsm("", "sub", OperandRegReg(REG_TMP0, REG_ACC0), "  1: Compare LE 8");
        break;
    case 2:
        GenAsm("", "sub", OperandRegReg(REG_TMP0, REG_ACC0), "  1: Compare LE 16");
        GenAsm("", "sbc", OperandRegReg(REG_TMP1, REG_ACC1), "  1:");
        break;
    case 4:
        GenAsm("", "sub", OperandRegReg(REG_TMP0, REG_ACC0), "  1: Compare LE 32");
        GenAsm("", "sbc", OperandRegReg(REG_TMP1, REG_ACC1), "  1:");
        GenAsm("", "sbc", OperandRegReg(REG_TMP2, REG_ACC2), "  1:");
        GenAsm("", "sbc", OperandRegReg(REG_TMP3, REG_ACC3), "  1:");
        break;
    default:
        Error(FATAL, "GenCompLEConditional: size not supported (%d)\n", iLeftSize);
    }
    
    if (pszTrue != NULL) {
        if (fSigned) { GenAsm("", "brge", pszTrue, "1/2:  branch if (signed) LE TRUE"); }
        else         { GenAsm("", "brsh", pszTrue, "1/2:  branch if (unsigned) LE TRUE"); }
    }
    if (pszFalse != NULL) {
        if (fSigned) { GenAsm("", "brlt", pszFalse, "1/2:  branch if (signed) LE FALSE"); }
        else         { GenAsm("", "brlo", pszFalse, "1/2:  branch if (unsigned) LE FALSE"); }
    }
    if (pszTrue == NULL) {
        if (fSigned) { GenAsm("", "", "", "   :  fall through on (signed) LE TRUE"); }
        else         { GenAsm("", "", "", "   :  fall through on (unsigned) LE TRUE"); }
    }
    if (pszFalse == NULL) {
        if (fSigned) { GenAsm("", "", "", "   :  fall through on (signed) LE FALSE"); }
        else         { GenAsm("", "", "", "   :  fall through on (unsigned) LE FALSE"); }
    }
}

// ##########################################################################
// #  Function: GenCompGT
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
void GenCompGT(int iReg, TPExprNode pExpr) {

    TPExprNode pLeft = pExpr->Use.Binary.pLeft;                                 // Left
    TPExprNode pRight = pExpr->Use.Binary.pRight;                               // Right
    int iLeftSize = CalcSizeOf(pLeft->pType);                                   //
    int iRightSize = CalcSizeOf(pRight->pType);                                 //
    ASSERT(iLeftSize == iRightSize);                                            // Confirm sizes match. This should be correct because of the initial parsing phase.
    ASSERT(iReg == REG_ACC);

    // Calculate Left & Right (Order preserved)
    _GenExpr(iReg, pLeft);                                                      // Generate Left.
    if (_GenCostOfCalculation(pRight) == 1) {                                   //
        _GenExpr(REG_TMP, pRight);                                              // Generate Right direct to tmp reg.
    }                                                                           //
    else {                                                                      //
        AVR_Push(REG_ACC, iLeftSize, "");                                       //
        _GenExpr(iReg, pRight);                                                 // Generate Right. (reg preservation required)
        AVR_Move(REG_TMP, REG_ACC, iLeftSize);                                  //
        AVR_Pop(REG_ACC, iLeftSize);                                            //
    }                                                                           //

    BOOL fSigned = TypeIsSigned(pLeft->pType);
    LPSTR   szTrue = GenLabel("_GtT_");
    LPSTR   szFalse = GenLabel("_GtT_");
    LPSTR   szOut = GenLabel("_GtOut_");
    switch (iLeftSize) {
    case 1:
        GenAsm("", "sub", OperandRegReg(REG_TMP0, REG_ACC0), "  1: Compare GT 8");
        break;
    case 2:
        GenAsm("", "sub", OperandRegReg(REG_TMP0, REG_ACC0), "  1: Compare GT 16");
        GenAsm("", "sbc", OperandRegReg(REG_TMP1, REG_ACC1), "  1:");
        break;
    case 4:
        GenAsm("", "sub", OperandRegReg(REG_TMP0, REG_ACC0), "  1: Compare GT 32");
        GenAsm("", "sbc", OperandRegReg(REG_TMP1, REG_ACC1), "  1:");
        GenAsm("", "sbc", OperandRegReg(REG_TMP2, REG_ACC2), "  1:");
        GenAsm("", "sbc", OperandRegReg(REG_TMP3, REG_ACC3), "  1:");
        break;
    default:
        Error(FATAL, "GenCompGT: size not supported (%d)\n", iLeftSize);
    }
    
    if (fSigned) {
        GenAsm("", "brlt", szTrue, "1/2:  signed");
    }
    else {
        GenAsm("", "brlo", szTrue, "1/2:  unsigned");
    }

    GenAsm(szFalse, "clr",  OperandReg(REG_ACC0),   "  1:");
    GenAsm("",      "rjmp", szOut,                  "  2:");
    GenAsm(szTrue,  "clr",  OperandReg(REG_ACC0),   "  1:");
    GenAsm("",      "inc",  OperandReg(REG_ACC0),   "  1:");
    GenAsm(szOut,   "",     "",                     "   :");

    Dispose(szOut);
    Dispose(szFalse);
    Dispose(szTrue);
}


// ##########################################################################
// #  Function: GenCompGTConditional
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
void GenCompGTConditional(int iReg, TPExprNode pExpr, LPSTR pszTrue, LPSTR pszFalse) {

    TPExprNode pLeft = pExpr->Use.Binary.pLeft;                                 // Left
    TPExprNode pRight = pExpr->Use.Binary.pRight;                               // Right
    int iLeftSize = CalcSizeOf(pLeft->pType);                                   //
    int iRightSize = CalcSizeOf(pRight->pType);                                 //
    ASSERT(iLeftSize == iRightSize);                                            // Confirm sizes match. This should be correct because of the initial parsing phase.
    ASSERT(iReg == REG_ACC);

    // Calculate Left & Right (Order preserved)
    _GenExpr(iReg, pLeft);                                                      // Generate Left.
    if (_GenCostOfCalculation(pRight) == 1) {                                   //
        _GenExpr(REG_TMP, pRight);                                              // Generate Right direct to tmp reg.
    }                                                                           //
    else {                                                                      //
        AVR_Push(REG_ACC, iLeftSize, "");                                       //
        _GenExpr(iReg, pRight);                                                 // Generate Right. (reg preservation required)
        AVR_Move(REG_TMP, REG_ACC, iLeftSize);                                  //
        AVR_Pop(REG_ACC, iLeftSize);                                            //
    }                                                                           //

    BOOL fSigned = TypeIsSigned(pLeft->pType);
    LPSTR   szTrue = GenLabel("_GtTrue_");
    LPSTR   szOut = GenLabel("_GtOut_");
    switch (iLeftSize) {
    case 1:
        GenAsm("", "sub", OperandRegReg(REG_TMP0, REG_ACC0), "  1: Compare GT 8");
        break;
    case 2:
        GenAsm("", "sub", OperandRegReg(REG_TMP0, REG_ACC0), "  1: Compare GT 16");
        GenAsm("", "sbc", OperandRegReg(REG_TMP1, REG_ACC1), "  1:");
        break;
    case 4:
        GenAsm("", "sub", OperandRegReg(REG_TMP0, REG_ACC0), "  1: Compare GT 32");
        GenAsm("", "sbc", OperandRegReg(REG_TMP1, REG_ACC1), "  1:");
        GenAsm("", "sbc", OperandRegReg(REG_TMP2, REG_ACC2), "  1:");
        GenAsm("", "sbc", OperandRegReg(REG_TMP3, REG_ACC3), "  1:");
        break;
    default:
        Error(FATAL, "GenCompGTConditional: size not supported (%d)\n", iLeftSize);
    }
    
    if (pszTrue != NULL) {
        if (fSigned) { GenAsm("", "brlt", pszTrue, "1/2:  branch if (signed) GT TRUE"); }
        else         { GenAsm("", "brlo", pszTrue, "1/2:  branch if (unsigned) GT TRUE"); }
    }
    if (pszFalse != NULL) {
        if (fSigned) { GenAsm("", "brge", pszFalse, "1/2:  branch if (signed) GT FALSE"); }
        else         { GenAsm("", "brsh", pszFalse, "1/2:  branch if (unsigned) GT FALSE"); }
    }
    if (pszTrue == NULL) {
        if (fSigned) { GenAsm("", "", "", "   :  fall through on (signed) GT TRUE"); }
        else         { GenAsm("", "", "", "   :  fall through on (unsigned) GT TRUE"); }
    }
    if (pszFalse == NULL) {
        if (fSigned) { GenAsm("", "", "", "   :  fall through on (signed) GT FALSE"); }
        else         { GenAsm("", "", "", "   :  fall through on (unsigned) GT FALSE"); }
    }
}

// ##########################################################################
// #  Function: GenCompGE
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
void GenCompGE(int iReg, TPExprNode pExpr) {

    TPExprNode pLeft = pExpr->Use.Binary.pLeft;                                 // Left
    TPExprNode pRight = pExpr->Use.Binary.pRight;                               // Right
    int iLeftSize = CalcSizeOf(pLeft->pType);                                   //
    int iRightSize = CalcSizeOf(pRight->pType);                                 //
    ASSERT(iLeftSize == iRightSize);                                            // Confirm sizes match. This should be correct because of the initial parsing phase.
    ASSERT(iReg == REG_ACC);

    // Calculate Left & Right (Order preserved)
    _GenExpr(iReg, pLeft);                                                      // Generate Left.
    if (_GenCostOfCalculation(pRight) == 1) {                                   //
        _GenExpr(REG_TMP, pRight);                                              // Generate Right direct to tmp reg.
    }                                                                           //
    else {                                                                      //
        AVR_Push(REG_ACC, iLeftSize, "");                                       //
        _GenExpr(iReg, pRight);                                                 // Generate Right. (reg preservation required)
        AVR_Move(REG_TMP, REG_ACC, iLeftSize);                                  //
        AVR_Pop(REG_ACC, iLeftSize);                                            //
    }                                                                           //

    BOOL    fSigned = TypeIsSigned(pLeft->pType);
    LPSTR   szTrue = GenLabel("_GeT_");
    LPSTR   szFalse = GenLabel("_GeF_");
    LPSTR   szOut = GenLabel("_GeOut_");
    switch (iLeftSize) {
    case 1:
        GenAsm("", "sub", OperandRegReg(REG_ACC0, REG_TMP0), "  1: Compare GE 8");
        break;
    case 2:
        GenAsm("", "sub", OperandRegReg(REG_ACC0, REG_TMP0), "  1: Compare GE 16");
        GenAsm("", "sbc", OperandRegReg(REG_ACC1, REG_TMP1), "  1:");
        break;
    case 4:
        GenAsm("", "sub", OperandRegReg(REG_ACC0, REG_TMP0), "  1: Compare GE 32");
        GenAsm("", "sbc", OperandRegReg(REG_ACC1, REG_TMP1), "  1:");
        GenAsm("", "sbc", OperandRegReg(REG_ACC2, REG_TMP2), "  1:");
        GenAsm("", "sbc", OperandRegReg(REG_ACC3, REG_TMP3), "  1:");
        break;
    default:
        Error(FATAL, "GenCompGE: size not supported (%d)\n", iLeftSize);
    }

    if (fSigned) {
        GenAsm("", "brge", szTrue, "1/2:  signed");
    }
    else {
        GenAsm("", "brsh", szTrue, "1/2:  unsigned");
    }

    GenAsm(szFalse, "clr",  OperandReg(REG_ACC0), "  1:");
    GenAsm("",      "rjmp", szOut,                "  2:");
    GenAsm(szTrue,  "clr",  OperandReg(REG_ACC0), "  1:");
    GenAsm("",      "inc",  OperandReg(REG_ACC0), "  1:");
    GenAsm(szOut,   "",     "",                   "   :");

    Dispose(szOut);
    Dispose(szFalse);
    Dispose(szTrue);
}

// ##########################################################################
// #  Function: GenCompGEConditional
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
void GenCompGEConditional(int iReg, TPExprNode pExpr, LPSTR pszTrue, LPSTR pszFalse) {

    TPExprNode pLeft = pExpr->Use.Binary.pLeft;                                 // Left
    TPExprNode pRight = pExpr->Use.Binary.pRight;                               // Right
    int iLeftSize = CalcSizeOf(pLeft->pType);                                   //
    int iRightSize = CalcSizeOf(pRight->pType);                                 //
    ASSERT(iLeftSize == iRightSize);                                            // Confirm sizes match. This should be correct because of the initial parsing phase.
    ASSERT(iReg == REG_ACC);

    // Calculate Left & Right (Order preserved)
    _GenExpr(iReg, pLeft);                                                      // Generate Left.
    if (_GenCostOfCalculation(pRight) == 1) {                                   //
        _GenExpr(REG_TMP, pRight);                                              // Generate Right direct to tmp reg.
    }                                                                           //
    else {                                                                      //
        AVR_Push(REG_ACC, iLeftSize, "");                                       //
        _GenExpr(iReg, pRight);                                                 // Generate Right. (reg preservation required)
        AVR_Move(REG_TMP, REG_ACC, iLeftSize);                                  //
        AVR_Pop(REG_ACC, iLeftSize);                                            //
    }                                                                           //

    BOOL    fSigned = TypeIsSigned(pLeft->pType);
    LPSTR   szTrue = GenLabel("_GeTrue_");
    LPSTR   szOut = GenLabel("_GeOut_");
    switch (iLeftSize) {
    case 1:
        GenAsm("", "sub", OperandRegReg(REG_ACC0, REG_TMP0), "  1: Compare GE 8");
        break;
    case 2:
        GenAsm("", "sub", OperandRegReg(REG_ACC0, REG_TMP0), "  1: Compare GE 16");
        GenAsm("", "sbc", OperandRegReg(REG_ACC1, REG_TMP1), "  1:");
        break;
    case 4:
        GenAsm("", "sub", OperandRegReg(REG_ACC0, REG_TMP0), "  1: Compare GE 32");
        GenAsm("", "sbc", OperandRegReg(REG_ACC1, REG_TMP1), "  1:");
        GenAsm("", "sbc", OperandRegReg(REG_ACC2, REG_TMP2), "  1:");
        GenAsm("", "sbc", OperandRegReg(REG_ACC3, REG_TMP3), "  1:");
        break;
    default:
        Error(FATAL, "GenCompGEConditional: size not supported (%d)\n", iLeftSize);
    }

    if (pszTrue != NULL) {
        if (fSigned) { GenAsm("", "brge", pszTrue, "1/2:  branch if (signed) GE TRUE"); }
        else         { GenAsm("", "brsh", pszTrue, "1/2:  branch if (unsigned) GE TRUE"); }
    }
    if (pszFalse != NULL) {
        if (fSigned) { GenAsm("", "brlt", pszFalse, "1/2:  branch if (signed) GE FALSE"); }
        else         { GenAsm("", "brlo", pszFalse, "1/2:  branch if (unsigned) GE FALSE"); }
    }
    if (pszTrue == NULL) {
        if (fSigned) { GenAsm("", "", "", "   :  fall through on (signed) GE TRUE"); }
        else         { GenAsm("", "", "", "   :  fall through on (unsigned) GE TRUE"); }
    }
    if (pszFalse == NULL) {
        if (fSigned) { GenAsm("", "", "", "   :  fall through on (signed) GE FALSE"); }
        else         { GenAsm("", "", "", "   :  fall through on (unsigned) GE FALSE"); }
    }
}

// ##########################################################################
// #  Function: GenCompLogicalAnd
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
void GenCompLogicalAnd(int iReg, TPExprNode pExpr) {

    TPExprNode pLeft = pExpr->Use.Binary.pLeft;
    TPExprNode pRight = pExpr->Use.Binary.pRight;
    int iLeftSize = CalcSizeOf(pLeft->pType);
    int iRightSize = CalcSizeOf(pRight->pType);
    ASSERT(iReg == REG_ACC);

    ASSERT(iLeftSize == iRightSize);                    // Confirm sizes match. 
    ASSERT(iLeftSize == SIZE_BOOL);

    LPSTR   szFalse = GenLabel("_LAndOut_");
    _GenExpr(iReg, pLeft);                                         // Left
    GenAsm("", "tst",  OperandReg(REG_ACC0), "  1: Logical And");  // was it FALSE
    GenAsm("", "breq", szFalse,              "1/2:");
    _GenExpr(iReg, pRight);                                        // Right.
    GenAsm(szFalse,    "", "",               "   :");              // exit
}

// ##########################################################################
// #  Function: GenCompLogicalAndConditional
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
void GenCompLogicalAndConditional(int iReg, TPExprNode pExpr, LPSTR pszTrue, LPSTR pszFalse) {

    TPExprNode pLeft = pExpr->Use.Binary.pLeft;
    TPExprNode pRight = pExpr->Use.Binary.pRight;

    ASSERT(IsBoolean(pLeft->pType));
    ASSERT(IsBoolean(pRight->pType));

    LPSTR   szAnd = GenLabel("_LAndRef_");                                                              //
    GenAsm("", "", "", CommentString(0, "Logical AND start. ", szAnd));                                 // 

    if (pszTrue != NULL && pszFalse != NULL) {                                                          // Both outcome destinations are defined.
        GenExprConditional(iReg, pLeft,  NULL,    pszFalse);                                                  // Left
        GenExprConditional(iReg, pRight, pszTrue, pszFalse);                                                  // Right
        GenAsm("", "", "", CommentString(0, "Logical AND end", szAnd));                                 // exit
    }
    else if (pszFalse != NULL) {                                                                        // fall through to TRUE, jump to FALSE 
        GenExprConditional(iReg, pLeft,  NULL, pszFalse);                                                     // Left
        GenExprConditional(iReg, pRight, NULL, pszFalse);                                                     // Right
        GenAsm("", "", "", CommentString(0, "Logical AND end (fall through to TRUE) ", szAnd));         // exit
    }
    else if (pszTrue != NULL) {                                                                         // jump to TRUE, fall through to FALSE
        LPSTR szFalse = GenLabel("_LAndFalse_");                                                        //
        GenExprConditional(iReg, pLeft, NULL, szFalse);                                                       // Left
        GenExprConditional(iReg, pRight, pszTrue, NULL);                                                      // Right
        GenAsm(szFalse, "", "", CommentString(0, "Logical AND end (fall through to FALSE) ", szAnd));   // exit
        Dispose(szFalse);
    }
    else {
        ASSERT(FALSE);
    }

    Dispose(szAnd);
}


// ##########################################################################
// #  Function: GenCompLogicalOr
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
void GenCompLogicalOr(int iReg, TPExprNode pExpr) {

    TPExprNode pLeft = pExpr->Use.Binary.pLeft;
    TPExprNode pRight = pExpr->Use.Binary.pRight;
    int iLeftSize = CalcSizeOf(pLeft->pType);
    int iRightSize = CalcSizeOf(pRight->pType);
    ASSERT(iReg == REG_ACC);

    ASSERT(iLeftSize == iRightSize);                              // Confirm sizes match. 
    ASSERT(iLeftSize == SIZE_BOOL);

    LPSTR   szTrue = GenLabel("_LOrOut_");
    _GenExpr(iReg, pLeft);                                        // Left
    GenAsm("", "tst",  OperandReg(REG_ACC0), "  1: Logical Or");  // was it TRUE
    GenAsm("", "brne", szTrue,               "1/2:");
    _GenExpr(iReg, pRight);                                       // Right.
    GenAsm(szTrue, "", "",                   "   :");             // exit
}

// ##########################################################################
// #  Function: GenCompLogicalOrConditional
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
void GenCompLogicalOrConditional(int iReg, TPExprNode pExpr, LPSTR pszTrue, LPSTR pszFalse) {

    TPExprNode pLeft = pExpr->Use.Binary.pLeft;
    TPExprNode pRight = pExpr->Use.Binary.pRight;

    ASSERT(IsBoolean(pLeft->pType));
    ASSERT(IsBoolean(pRight->pType));

    LPSTR   szOr = GenLabel("_LOrRef_");                                                            //
    GenAsm("", "", "", CommentString(0, "Logical OR start. ", szOr));                               // 

    if (pszTrue != NULL && pszFalse != NULL) {                                                      // Both outcome destinations are defined.
        GenExprConditional(iReg, pLeft, pszTrue, NULL);                                                   // Left
        GenExprConditional(iReg, pRight, pszTrue, pszFalse);                                              // Right
        GenAsm("", "", "", CommentString(0, "Logical OR end", szOr));                               // exit
    }
    else if (pszFalse != NULL) {                                                                    // fall through to TRUE, jump to FALSE 
        LPSTR szTrue = GenLabel("_LOrTrue_");                                                       //
        GenExprConditional(iReg, pLeft, szTrue, NULL);                                                    // Left
        GenExprConditional(iReg, pRight, NULL, pszFalse);                                                 // Right
        GenAsm(szTrue, "", "", CommentString(0, "Logical OR end (fall through to TRUE) ", szOr));   // exit
        Dispose(szTrue);
    }
    else if (pszTrue != NULL) {                                                                     // jump to TRUE, fall through to FALSE
        GenAsm("", "", "", "   : Logical AND start");                                               // exit
        GenExprConditional(iReg, pLeft, pszTrue, NULL);                                                   // Left
        GenExprConditional(iReg, pRight, pszTrue, NULL);                                                  // Right
        GenAsm("", "", "", CommentString(0, "Logical OR end (fall through to FALSE) ", szOr));      // exit
    }
    else {
        ASSERT(FALSE);
    }

    Dispose(szOr);
}


// ##########################################################################
// #  Function: GenExprConst
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
void GenExprConst(int iReg, TPExprNode pExpr) {
    TMemAccess Z;
    FetchOptions(iReg, pExpr, &Z);
    FetchLoad(&Z, iReg);

}


// ##########################################################################
// #  Function: GenExprIoreg
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
void GenExprIoreg(int iReg, TPExprNode pExpr) {
    TMemAccess Z;
    FetchOptions(iReg, pExpr, &Z);
    FetchLoad(&Z, iReg);
}

// ##########################################################################
// #  Function: GenExprConstConditional
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
void GenExprConstConditional(int iReg, TPExprNode pExpr, LPSTR pszTrue, LPSTR pszFalse) {
    if ((pExpr->Use.Const.lInteger != 0) && (pszTrue != NULL)) {
        GenAsm("", "rjmp", pszTrue, "  2: if <const> jump.  (always TRUE)");
    }
    if ((pExpr->Use.Const.lInteger == 0) && (pszFalse != NULL)) {
        GenAsm("", "rjmp", pszFalse, "  2: if <const> jump.  (always FALSE)");
    }
}

// ##########################################################################
// #  Function: GenExprVar
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
void GenExprVar(int iReg, TPExprNode pExpr) {

    TMemAccess Z;
    FetchOptions(iReg, pExpr, &Z);
    FetchLoad(&Z, iReg);

}


// ##########################################################################
// #  Function: SignExtend
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
void SignExtend(int iReg, int iExtra) {
    char szComment[36];
    switch (iExtra) {
    case 1: sprintf_s(szComment, sizeof(szComment), "  1: Signed extend 8 to 16 bits");              // 8->16
            GenAsm("", "mov", OperandRegReg(iReg + REG_ORDER1, iReg+ REG_ORDER0),  szComment);
            GenAsm("", "lsl", OperandReg(iReg + REG_ORDER1),                       "  1:");
            GenAsm("", "clr", OperandReg(iReg + REG_ORDER1),                       "  1: ");
            GenAsm("", "sbc", OperandRegReg(iReg + REG_ORDER1, iReg + REG_ORDER1), "  1:");
            break;
    case 2: sprintf_s(szComment, sizeof(szComment), "  1: Signed extend 16 to 32 bits");            // 16->32
            GenAsm("", "mov", OperandRegReg(iReg + REG_ORDER2, iReg+ REG_ORDER1),  szComment);
            GenAsm("", "lsl", OperandReg(iReg + REG_ORDER2),                       "  1:");
            GenAsm("", "clr", OperandReg(iReg + REG_ORDER2),                       "  1: ");
            GenAsm("", "sbc", OperandRegReg(iReg + REG_ORDER2, iReg + REG_ORDER2), "  1:");
            GenAsm("", "mov", OperandRegReg(iReg + REG_ORDER3, iReg + REG_ORDER2), "  1:");
            break;
    case 3: sprintf_s(szComment, sizeof(szComment), "  1: Signed extend 8 to 32 bits");            // 8->32
            GenAsm("", "mov", OperandRegReg(iReg + REG_ORDER1, iReg + REG_ORDER0), szComment);
            GenAsm("", "lsl", OperandReg(iReg + REG_ORDER1),                       "  1:");
            GenAsm("", "clr", OperandReg(iReg + REG_ORDER1),                       "  1: ");
            GenAsm("", "sbc", OperandRegReg(iReg + REG_ORDER1, iReg + REG_ORDER1), "  1:");
            GenAsm("", "mov", OperandRegReg(iReg + REG_ORDER2, iReg + REG_ORDER1), "  1:");
            GenAsm("", "mov", OperandRegReg(iReg + REG_ORDER3, iReg + REG_ORDER2), "  1:");
            break;
    default: Error(FATAL, "SignExtend: size problem");
    }
}

void UnsignExtend(int iReg, int iExtra) {
    char szComment[36];
    switch (iExtra) {
    case 1: sprintf_s(szComment, sizeof(szComment), "  1: unsigned extend 8 to 16 bits");       // 8->16
            GenAsm("", "clr", OperandReg(iReg + REG_ORDER1), szComment);
            break;
    case 2: sprintf_s(szComment, sizeof(szComment), "  1: unsigned extend 16 to 32 bits");      // 16->32
            GenAsm("", "clr", OperandReg(iReg + REG_ORDER2), szComment);
            GenAsm("", "clr", OperandReg(iReg + REG_ORDER3), szComment);
            break;
    case 3: sprintf_s(szComment, sizeof(szComment), "  1: unsigned extend 8 to 32 bits");       // 8->32
            GenAsm("", "clr", OperandReg(iReg + REG_ORDER1), szComment);
            GenAsm("", "clr", OperandReg(iReg + REG_ORDER2), szComment);
            GenAsm("", "clr", OperandReg(iReg + REG_ORDER3), szComment);
            break;
    default: Error(FATAL, "UnsignExtend: size problem");
    }
}

// ##########################################################################
// #  Function: LongToFlag
// #  Function: ShortToFlag
// #  Function: LongToFlag
// #        Arithmetic value to flag value.
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

static void LongToFlag(int iReg) {
    GenAsm("", "or", OperandRegReg(iReg + REG_ORDER0, iReg + REG_ORDER1),  "  1: Cast Long to Flag");
    GenAsm("", "or", OperandRegReg(iReg + REG_ORDER0, iReg + REG_ORDER2),  "  1:");
    GenAsm("", "or", OperandRegReg(iReg + REG_ORDER0, iReg + REG_ORDER3),  "  1:");
    GenAsm("", "subi", OperandRegImmediate(iReg + REG_ORDER0, 1),          "  1:");
    GenAsm("", "sbc", OperandRegReg(iReg + REG_ORDER0, iReg + REG_ORDER0), "  1:");
    GenAsm("", "andi", OperandRegImmediate(iReg + REG_ORDER0, 1),          "  1:");
}

static void ShortToFlag(int iReg) {
    GenAsm("", "or", OperandRegReg(iReg + REG_ORDER0, iReg + REG_ORDER1),  "  1: Cast Short to Flag");
    GenAsm("", "subi", OperandRegImmediate(iReg + REG_ORDER0, 1),          "  1:");
    GenAsm("", "sbc", OperandRegReg(iReg + REG_ORDER0, iReg + REG_ORDER0), "  1:");
    GenAsm("", "andi", OperandRegImmediate(iReg + REG_ORDER0, 1),          "  1:");
}

static void ByteToFlag(int iReg) {
    GenAsm("", "or", OperandRegReg(iReg + REG_ORDER0, iReg + REG_ORDER0),  "  1: Cast Byte to Flag");
    GenAsm("", "subi", OperandRegImmediate(iReg + REG_ORDER0, 1),          "  1:");
    GenAsm("", "sbc", OperandRegReg(iReg + REG_ORDER0, iReg + REG_ORDER0), "  1:");
    GenAsm("", "andi", OperandRegImmediate(iReg + REG_ORDER0, 1),          "  1:");
}

// ##########################################################################
// #  Function: ByteToFlagConditional
// #  Function: ShortToFlagConditional
// #  Function: LongToFlagConditional
// #        Arithmetic value to appropriate jump statements.
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

static void FlagConditionalCommonExit(LPSTR pzsTrue, LPSTR pszFalse);  // forward

static void LongToFlagConditional(int iReg, LPSTR pzsTrue, LPSTR pszFalse) {
    GenAsm("", "or", OperandRegReg(iReg + REG_ORDER2, iReg + REG_ORDER3), "  1: Cast Long to Flag");
    GenAsm("", "or", OperandRegReg(iReg + REG_ORDER1, iReg + REG_ORDER2), "  1:");
    GenAsm("", "or", OperandRegReg(iReg + REG_ORDER0, iReg + REG_ORDER1), "  1:");
    FlagConditionalCommonExit(pzsTrue, pszFalse);
}

static void ShortToFlagConditional(int iReg, LPSTR pzsTrue, LPSTR pszFalse) {
    GenAsm("", "or", OperandRegReg(iReg + REG_ORDER0, iReg + REG_ORDER1), "  1: Cast Short to Flag");
    FlagConditionalCommonExit(pzsTrue, pszFalse);
}

static void ByteToFlagConditional(int iReg, LPSTR pzsTrue, LPSTR pszFalse) {
    GenAsm("", "tst", OperandReg(iReg + REG_ORDER0), "  1: Cast Byte to Flag");
    FlagConditionalCommonExit(pzsTrue, pszFalse);
}

static void FlagConditionalCommonExit(LPSTR pzsTrue, LPSTR pszFalse) {
    ASSERT((pzsTrue != NULL) || (pszFalse != NULL));                                                // at least one label must be valid!

    if (CmdLine.iDefendConditionals == 0) {                                                         // No defensive code so we use the fall through to null lables.
        if (pzsTrue != NULL) { GenAsm("", "brne", pzsTrue, "1/2: branch if TRUE"); }
        if (pszFalse != NULL) { GenAsm("", "breq", pszFalse, "1/2: branch if FALSE"); }
        if (pzsTrue == NULL) { GenAsm("", "", "", "   : fall through on TRUE"); }
        if (pszFalse == NULL) { GenAsm("", "", "", "   : fall through on FALSE"); }
        return;
    }

    LPSTR pszTmpLabel = NULL;                                                                       // Defended alternative.
    if  (pzsTrue != NULL) { 
        GenAsm("", "brne", pzsTrue, "1/2: branch if TRUE"); 
    }
//    else { 
//        pszTmpLabel = GenLabel("_IfTrue_");
//        GenAsm("", "brne", pszTmpLabel, "1/2: branch if TRUE (defended fall through)");
//    }
    if (pszFalse != NULL) { 
        GenAsm("", "breq", pszFalse, "1/2: branch if FALSE"); 
    }
//    else {
//        pszTmpLabel = GenLabel("_IfFalse_");
//        GenAsm("", "breq", pszTmpLabel, "1/2: branch if FALSE (defended fall through)");
//    }
    
//    if (pszTmpLabel != NULL) {
//        GenAsm(pszTmpLabel, "", "", "   : Defended fall through");
//        Dispose(pszTmpLabel);
//    }

    return;
}



// ##########################################################################
// #  Function: GenExprCast
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
void GenExprCast(int iReg, TPExprNode pExpr) {
    ASSERT(pExpr->Usage == uCast);

    _GenExpr(iReg, pExpr->Use.Cast.pTarget);                       // Calculate whatever it is we are casting.
    switch (pExpr->Use.Cast.Op) {
    case Cast_c2s: SignExtend(iReg,   (SIZE_SHORT - SIZE_CHAR)); return;  //   signed  8 to 16
    case Cast_c2l: SignExtend(iReg,   (SIZE_LONG - SIZE_CHAR));  return;  //   signed  8 to 32
    case Cast_s2l: SignExtend(iReg,   (SIZE_LONG - SIZE_SHORT)); return;  //   signed 16 to 32
    case Cast_b2s: UnsignExtend(iReg, (SIZE_SHORT - SIZE_CHAR)); return;  // unsigned  8 to 16
    case Cast_b2l: UnsignExtend(iReg, (SIZE_LONG - SIZE_CHAR));  return;  // unsigned  8 to 32
    case Cast_u2l: UnsignExtend(iReg, (SIZE_LONG - SIZE_SHORT)); return;  // unsigned 16 to 32
    case Cast_l2s: /* nop */                                     return;  //          32 to 16
    case Cast_l2b: /* nop */                                     return;  //          32 to  8
    case Cast_l2f: LongToFlag(iReg);                             return;  //          32 to size of flag
    case Cast_s2b: /* nop */                                     return;  //          16 to  8
    case Cast_s2f: ShortToFlag(iReg);                            return;  //          16 to size of flag
    case Cast_b2f: ByteToFlag(iReg);                             return;  //           8 to size of flag
    default:
        Error(FATAL, "GenExprCast: Unknown cast (%d)\n", pExpr->Use.Cast.Op);
    }
}

static void GenExprCastConditional(int iReg, TPExprNode pExpr, LPSTR pzsTrue, LPSTR pszFalse) {
    ASSERT(pExpr->Usage == uCast);
    ASSERT(IsBoolean(pExpr->pType));

    _GenExpr(iReg, pExpr->Use.Cast.pTarget);                                    // Calculate whatever it is we are casting. 
                                                                                // It can't be conditional or we wouldn't be here casting it!

    switch (pExpr->Use.Cast.Op) {
    case Cast_l2f: LongToFlagConditional(iReg, pzsTrue, pszFalse);  return;  // 32 to size of flag
    case Cast_s2f: ShortToFlagConditional(iReg, pzsTrue, pszFalse); return;  // 16 to size of flag
    case Cast_b2f: ByteToFlagConditional(iReg, pzsTrue, pszFalse);  return;  //  8 to size of flag
    default:
        Error(FATAL, "GenExprCastConditional: Unknown cast (%d)\n", pExpr->Use.Cast.Op);
    }
}

// ##########################################################################
// #  Function: UnaryMinus
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
static void UnaryMinus(int iReg, TPExprNode pExpr) {
    ASSERT(iReg == REG_ACC); // no need but hard coded below...

    int iSize = CalcSizeOf(pExpr->pType);
    _GenExpr(iReg, pExpr);                                           // Calc decendant.
    switch (iSize) {
    case 1:
        GenAsm("", "neg", OperandReg(REG_ACC0),               "  1: Negate8    r = -r");
        break;
    case 2:
        GenAsm("", "movw", OperandRegReg(REG_TMP0, REG_ACC0), "  1: Negate16    r = -r");
        GenAsm("", "clr",  OperandReg(REG_ACC0),              "  1:");
        GenAsm("", "clr",  OperandReg(REG_ACC1),              "  1:");
        GenAsm("", "sub",  OperandRegReg(REG_ACC0, REG_TMP0), "  1:");
        GenAsm("", "sbc",  OperandRegReg(REG_ACC1, REG_TMP1), "  1:");
        break;
    case 4:                 
        GenAsm("", "movw", OperandRegReg(REG_TMP0, REG_ACC0), "  1: Negate32    r = -r");
        GenAsm("", "movw", OperandRegReg(REG_TMP2, REG_ACC2), "  1:");
        GenAsm("", "clr",  OperandReg(REG_ACC0),              "  1:");
        GenAsm("", "clr",  OperandReg(REG_ACC1),              "  1:");
        GenAsm("", "movw", OperandRegReg(REG_ACC2, REG_ACC0), "  1:");
        GenAsm("", "sub",  OperandRegReg(REG_ACC0, REG_TMP0), "  1:");
        GenAsm("", "sbc",  OperandRegReg(REG_ACC1, REG_TMP1), "  1:");
        GenAsm("", "sbc",  OperandRegReg(REG_ACC2, REG_TMP2), "  1:");
        GenAsm("", "sbc",  OperandRegReg(REG_ACC3, REG_TMP3), "  1:");
        break;
    default:
        Error(FATAL, "UnaryMinus: size not supported (%d)\n", iSize);
    }
}

// ##########################################################################
// #  Function: UnaryPlus
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
static void UnaryPlus(int iReg, TPExprNode pExpr) {
    _GenExpr(iReg, pExpr);                                           // Calc decendant.
}

// ##########################################################################
// #  Function: UnaryNeg
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
static void UnaryNeg(int iReg, TPExprNode pExpr) {
    int iSize = CalcSizeOf(pExpr->pType);
    _GenExpr(iReg, pExpr);                                           // Calc decendant.
    switch (iSize) {
    case 1:
        GenAsm("", "com", OperandReg(iReg), "  1: Compliment8    r = ~r");
        break;
    case 2:
        GenAsm("", "com", OperandReg(iReg), "  1: Compliment16   r = ~r");
        GenAsm("", "com", OperandReg(iReg), "  1:");
        break;
    case 4:
        GenAsm("", "com", OperandReg(iReg), "  1: Compliment32   r = ~r");
        GenAsm("", "com", OperandReg(iReg), "  1:");
        GenAsm("", "com", OperandReg(iReg), "  1:");
        GenAsm("", "com", OperandReg(iReg), "  1:");
        break;
    default:
        Error(FATAL, "UnaryNeg: size not supported (%d)\n", iSize);
    }
}

// ##########################################################################
// #  Function: UnaryNot
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
static void UnaryNot(int iReg, TPExprNode pExpr) {

    int iSize = CalcSizeOf(pExpr->pType);
    ASSERT(iSize == SIZE_BOOL);
    _GenExpr(iReg, pExpr);                                   // Calc decendant.
    GenAsm("",       "sub",  OperandRegImmediate(iReg, 1),  "  1: Invert Flag (0==>1, 1-255==>0)");
    GenAsm("",       "clr",  OperandReg(iReg),              "  1: ");
    GenAsm("",       "rol",  OperandReg(iReg),              "  1: ");
}


// ##########################################################################
// #  Function: UnaryNotConditional
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
static void UnaryNotConditional(int iReg, TPExprNode pExpr, LPSTR pszTrue, LPSTR pszFalse) {
    ASSERT(IsBoolean(pExpr->pType));

    GenExprConditional(iReg, pExpr, pszFalse, pszTrue);   // Calc decendant.
}


// ##########################################################################
// #  Function: UnaryPtr
// #        Fetch what's at the pointer experession
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
static void UnaryPtr(int iReg, TPExprNode pExpr) {
   // ASSERT(iReg == REG_ACC);

    TMemAccess Z;
    FetchOptions(iReg, pExpr, &Z);                                            // how to get it.
    FetchLoad(&Z, iReg);                                                      // get it.
   
}

// ##########################################################################
// #  Function: UnaryPostInc
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

//#include "GenMemAccess.c"

static void UnaryPostInc(int iReg, TPExprNode pExpr) {
    ASSERT((iReg == REG_ACC) || (iReg == 30));
//#pragma message("    **** DEBUG  reg test removed for testing")
    BOOL fFrame = FALSE;

    UCHAR bVarSize = (UCHAR)CalcSizeOf(pExpr->pType);                                                   // Size of this variable

    UCHAR bIncrement = 1;                                                                               // default when incrementing numeric base types.
    if (IsPointer(pExpr->pType)) {                                                                      // None numeric? 
        ASSERT(bVarSize == SIZE_PTR_DEFAULT);                                                           //
        ASSERT(pExpr->pType->Usage == DecPtr);                                                           //
        bIncrement = (UCHAR)CalcSizeOf(pExpr->pType->Use.DecPtr.pTarget);                               // Size of what's pointed to.
        ASSERT(bIncrement < 64);                                                                        //
    }                                                                                                   //

    TMemAccess Z;
    FetchOptions(iReg, pExpr, &Z);
    FetchLoad(&Z, iReg);                                                                                // Collect it

    switch (bVarSize) {                                                                                 // Post Increment
        case 1: GenAsm("", "mov", OperandRegReg(REG_TMP0, iReg + REG_ORDER0),   "  1: post inc 8");     //     
                GenAsm("", "inc", OperandReg(REG_TMP0),                         "  1:");                //
                break;                                                                                  //
        case 2: GenAsm("", "movw", OperandRegReg(REG_TMP0, iReg + REG_ORDER0),  "  1: post inc 16");    //
                GenAsm("", "adiw", OperandRegImmediate(REG_TMP0, bIncrement),   "  2:");                //
                break;                                                                                  //
        case 4: GenAsm("", "movw", OperandRegReg(REG_TMP0, iReg + REG_ORDER0),  "  1: post inc 32");    //
                GenAsm("", "movw", OperandRegReg(REG_TMP2, iReg + REG_ORDER2),  "  1:");                //
                GenAsm("", "subi", OperandRegImmediate(REG_TMP0, (-bIncrement)),"  1:");                //
                GenAsm("", "sbci", OperandRegImmediate(REG_TMP1, 0xff),         "  1:");                //
                GenAsm("", "sbci", OperandRegImmediate(REG_TMP2, 0xff),         "  1:");                //
                GenAsm("", "sbci", OperandRegImmediate(REG_TMP3, 0xff),         "  1:");                //
                break;                                                                                  //
        default: Error(FATAL, "UnaryPostInc Ram: Size?\n");                                             //
    }                                                                                                   //

    FetchStore(&Z, REG_TMP0);                                                                           // Put it back
}


// ##########################################################################
// #  Function: UnaryPreInc
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
static void UnaryPreInc(int iReg, TPExprNode pExpr) {
    ASSERT((iReg == REG_ACC) || (iReg == 30));
    BOOL fFrame = FALSE;

    UCHAR bVarSize = (UCHAR)CalcSizeOf(pExpr->pType);                                                       // Size of this variable

    UCHAR bIncrement = 1;                                                                                   // default when incrementing numeric base types.
    if (IsPointer(pExpr->pType)) {                                                                          // None numeric? 
        ASSERT(bVarSize == SIZE_PTR_DEFAULT);                                                               //
        ASSERT(pExpr->pType->Usage == DecPtr);                                                              //
        bIncrement = (UCHAR)CalcSizeOf(pExpr->pType->Use.DecPtr.pTarget);                                   // Size of what's pointed to.
        ASSERT(bIncrement < 64);                                                                            //
    }                                                                                                       //

    TMemAccess Z;
    FetchOptions(iReg, pExpr, &Z);
    FetchLoad(&Z, iReg);                                                                                    // Collect it

    switch (bVarSize) {                                                                                     // Pre Increment
    case 1: GenAsm("", "inc",  OperandReg(iReg + REG_ORDER0),                         "  1: pre inc 8");    //     
            break;                                                                                          //
    case 2: //GenAsm("", "adiw", OperandRegImmediate(iReg + REG_ORDER0, bIncrement),    "  1: pre inc 16"); //
            GenAsm("", "subi", OperandRegImmediate(iReg + REG_ORDER0, (-bIncrement)),   "  1: pre inc 16"); //
            GenAsm("", "sbci", OperandRegImmediate(iReg + REG_ORDER1, 0xff), "  1:");                       //
            break;                                                                                          //
    case 4: GenAsm("", "subi", OperandRegImmediate(iReg + REG_ORDER0, (-bIncrement)), "  1: pre inc 32");   //
            GenAsm("", "sbci", OperandRegImmediate(iReg + REG_ORDER1, 0xff),          "  1:");              //
            GenAsm("", "sbci", OperandRegImmediate(iReg + REG_ORDER2, 0xff),          "  1:");              //
            GenAsm("", "sbci", OperandRegImmediate(iReg + REG_ORDER3, 0xff),          "  1:");              //
            break;                                                                                          //
    default: Error(FATAL, "UnaryPreInc Ram: Size?\n");                                                      //
    }                                                                                                       //

    FetchStore(&Z, iReg);                                                                                   // Put it back

}


// ##########################################################################
// #  Function: UnaryPostDec
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
static void UnaryPostDec(int iReg, TPExprNode pExpr) {
    ASSERT((iReg == REG_ACC) || (iReg == 30));
    BOOL fFrame = FALSE;

    UCHAR bVarSize = (UCHAR)CalcSizeOf(pExpr->pType);                                           // Size of this variable

    UCHAR bIncrement = 1;                                                                       // default when incrementing numeric base types.
    if (IsPointer(pExpr->pType)) {                                                              // None numeric? 
        ASSERT(bVarSize == SIZE_PTR_DEFAULT);                                                   //
        ASSERT(pExpr->pType->Usage == DecPtr);                                                  //
        bIncrement = (UCHAR)CalcSizeOf(pExpr->pType->Use.DecPtr.pTarget);                       // Size of what's pointed to.
        ASSERT(bIncrement < 64);                                                                //
    }                                                                                           //

    TMemAccess Z;
    FetchOptions(iReg, pExpr, &Z);
    FetchLoad(&Z, iReg);                                                                        // Collect it

    switch (bVarSize) {                                                                         // Post Decrement 8
    case 1: GenAsm("", "mov", OperandRegReg(REG_TMP0, iReg + REG_ORDER0),  "  1: post dec 8");  //     
            GenAsm("", "dec", OperandReg(REG_TMP0), "  1:");                                    //
            break;                                                                              //
    case 2: GenAsm("", "movw", OperandRegReg(REG_TMP0, iReg + REG_ORDER0), "  1: post dec 16"); //
            GenAsm("", "sbiw", OperandRegImmediate(REG_TMP0, bIncrement),  "  2:");             //
            break;                                                                              //
    case 4: GenAsm("", "movw", OperandRegReg(REG_TMP0, iReg + REG_ORDER0), "  1: post dec 32"); //
            GenAsm("", "movw", OperandRegReg(REG_TMP2, iReg + REG_ORDER2), "  1:");             //
            GenAsm("", "subi", OperandRegImmediate(REG_TMP0, bIncrement),  "  1:");             //
            GenAsm("", "sbci", OperandRegImmediate(REG_TMP1, 0),           "  1:");             //
            GenAsm("", "sbci", OperandRegImmediate(REG_TMP2, 0),           "  1:");             //
            GenAsm("", "sbci", OperandRegImmediate(REG_TMP3, 0),           "  1:");             //
            break;                                                                              //
    default: Error(FATAL, "UnaryPostDec Ram: Size?\n");                                         //
    }                                                                                           //

    FetchStore(&Z, REG_TMP0);                                                                   // Put it back

}

// ##########################################################################
// #  Function: UnaryPreDec
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
static void UnaryPreDec(int iReg, TPExprNode pExpr) {
    ASSERT((iReg == REG_ACC) || (iReg == 30));
    BOOL fFrame = FALSE;

    UCHAR bVarSize = (UCHAR)CalcSizeOf(pExpr->pType);                                                       // Size of this variable

    UCHAR bIncrement = 1;                                                                                   // default when incrementing numeric base types.
    if (IsPointer(pExpr->pType)) {                                                                          // None numeric? 
        ASSERT(bVarSize == SIZE_PTR_DEFAULT);                                                               //
        ASSERT(pExpr->pType->Usage == DecPtr);                                                               //
        bIncrement = (UCHAR)CalcSizeOf(pExpr->pType->Use.DecPtr.pTarget);                                   // Size of what's pointed to.
        ASSERT(bIncrement < 64);                                                                            //
    }                                                                                                       //

    TMemAccess Z;
    FetchOptions(iReg, pExpr, &Z);
    FetchLoad(&Z, iReg);                                                                                    // Collect it

    switch (bVarSize) {                                                                                     // Pre Decrement 8
    case 1: GenAsm("", "dec",  OperandReg(iReg + REG_ORDER0),                         "  1: pre dec 8");    //     
            break;                                                                                          //
    case 2: //GenAsm("", "sbiw", OperandRegImmediate(iReg + REG_ORDER0, bIncrement),    "  1: pre dec 16");   //
            GenAsm("", "subi", OperandRegImmediate(iReg + REG_ORDER0, bIncrement),    "  1: pre dec 16");   //
            GenAsm("", "sbci", OperandRegImmediate(iReg + REG_ORDER1, 0),             "  1:");              //
            break;                                                                                          //
    case 4: GenAsm("", "subi", OperandRegImmediate(iReg + REG_ORDER0, bIncrement),    "  1: pre dec 32");   //
            GenAsm("", "sbci", OperandRegImmediate(iReg + REG_ORDER1, 0),             "  1:");              //
            GenAsm("", "sbci", OperandRegImmediate(iReg + REG_ORDER2, 0),             "  1:");              //
            GenAsm("", "sbci", OperandRegImmediate(iReg + REG_ORDER3, 0),             "  1:");              //
            break;                                                                                          //
    default: Error(FATAL, "UnaryPreDec Ram: Size?\n");                                                      //
    }                                                                                                       //

    FetchStore(&Z, iReg);                                                                                   // Put it back

}



// ##########################################################################
// #  Function: UnaryAddr
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
static void UnaryAddr(int iReg, TPExprNode pExpr) {
    //ASSERT((iReg == REG_ACC) || (iReg == 30));
    if (pExpr->Usage == uVar) {                                                                                                                 // Simple case is addr of a variable name.
        if (pExpr->Use.Var.pDecId == NULL) {                                                                                                    //      Global.
            if (pExpr->pType->Usage == DecFunc) {
                GenAsm("", "ldi", OperandRegProgVar(iReg, pExpr->Use.Var.pszIdentifier), CommentString(1, "Z = ", pExpr->Use.Var.pszIdentifier));
                GenAsm("", "ldi", OperandRegProgVar(iReg + REG_ORDER1, pExpr->Use.Var.pszIdentifier), "  1:");
            }
            else {
                GenAsm("", "ldi", OperandRegVar(iReg, pExpr->Use.Var.pszIdentifier), CommentString(1, "Z = ", pExpr->Use.Var.pszIdentifier));
                GenAsm("", "ldi", OperandRegVar(iReg + REG_ORDER1, pExpr->Use.Var.pszIdentifier), "  1:");
            }
        }
        else {                                                                                                                                  //      Frame var.
            GenAsm("", "movw", OperandRegReg(iReg, 28),                                             CommentString(1, "Z = ", pExpr->Use.Var.pszIdentifier));
            if (24 <= iReg) {
                GenAsm("", "adiw", OperandRegImmediate(iReg, pExpr->Use.Var.pDecId->Use.DecId.iOffset), "  2:");
            }
            else {
                GenAsm("", "subi", OperandRegImmediate(iReg,   (unsigned char)(-pExpr->Use.Var.pDecId->Use.DecId.iOffset)), "  1: add frame offset (subtract -offset)");
                GenAsm("", "sbci", OperandRegImmediate(iReg+1, (unsigned char)0xFF), "  1:");
            }
        }
        return;
    }
                                                                                                            // Address of something at the end of a pointer
    if (pExpr->Usage == uUnary && pExpr->Use.Unary.Op == unPtr) {                                           // address => pointer => <eppr>  = <expr>
        _GenExpr(iReg, pExpr->Use.Unary.pOperand);
        return;
    }

    //GenExpressionPrettyPrint(0, pExpr);
    Error(FATAL, "UnaryAddr complicated use not implemented");
}


// ##########################################################################
// #  Function: GenExprUnary
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
void GenExprUnary(int iReg, TPExprNode pExpr) {
    ASSERT(pExpr->Usage == uUnary);
    TPExprNode pN = pExpr->Use.Unary.pOperand;

    switch (pExpr->Use.Unary.Op) {                                                                      // Do the arithmetic. 
    case unMinus:   UnaryMinus(iReg, pN);   return;
    case unPlus:    UnaryPlus(iReg, pN);    return;
    case unNeg:     UnaryNeg(iReg, pN);     return;
    case unPostInc: UnaryPostInc(iReg, pN); return;
    case unPreInc:  UnaryPreInc(iReg, pN);  return;
    case unPostDec: UnaryPostDec(iReg, pN); return;
    case unPreDec:  UnaryPreDec(iReg, pN);  return;
  //case unSizeOf:  UnarySizeOf(iReg, pN);  return; // not used. optimized away into a constant.
    case unAddr:    UnaryAddr(iReg, pN);    return;
    case unPtr:     UnaryPtr(iReg, pExpr);     return;
    case unNot:     UnaryNot(iReg, pN);     return;

    default:                                                                                            //
        Error(FATAL, "GenExprUnary: Unrecognized Op Unary %d\n", pExpr->Use.Unary.Op);                  //
        return;                                                                                         //
    }                                                                                                   //
}

// ##########################################################################
// #  Function: GenExprUnaryConditional
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
void GenExprUnaryConditional(int iReg, TPExprNode pExpr, LPSTR pszTrue, LPSTR pszFalse) {
    ASSERT(pExpr->Usage == uUnary);
    ASSERT(IsBoolean(pExpr->pType));

    TPExprNode pN = pExpr->Use.Unary.pOperand;

    if (pExpr->Use.Unary.Op == unNot) {     // Do the arithmetic. 
        UnaryNotConditional(iReg, pN, pszTrue, pszFalse);
    }
    else {
        Error(FATAL, "GenExprUnaryConditional: Unrecognized Op Unary %d\n", pExpr->Use.Unary.Op);   //
    }
}



// ##########################################################################
// #  Function: GenExprBinary
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
void GenExprBinary(int iReg, TPExprNode pExpr) {
    ASSERT(pExpr->Usage == uBinary);
   // ASSERT(iReg == REG_ACC);

    switch (pExpr->Use.Binary.Op) {                                                           // Do the arithmetic. 
    case binAdd:  GenAdd(iReg, pExpr);            return;                                     //  
    case binSub:  GenSub(iReg, pExpr);            return;                                     //
    case binMul:  GenMul(iReg, pExpr);            return;                                     //
    case binDiv:  GenDiv(iReg, pExpr);            return;                                     //
    case binMod:  GenMod(iReg, pExpr);            return;                                     //
    case binAnd:  GenAnd(iReg, pExpr);            return;                                     //
    case binOr:   GenOr(iReg, pExpr);             return;                                     //
    case binXor:  GenXor(iReg, pExpr);            return;                                     //
    case binCEQ:  GenCompEQ(iReg, pExpr);         return;                                     //
    case binCNE:  GenCompNE(iReg, pExpr);         return;                                     //
    case binCLT:  GenCompLT(iReg, pExpr);         return;                                     //
    case binCLE:  GenCompLE(iReg, pExpr);         return;                                     //
    case binCGT:  GenCompGT(iReg, pExpr);         return;                                     //
    case binCGE:  GenCompGE(iReg, pExpr);         return;                                     //
    case binLAnd: GenCompLogicalAnd(iReg, pExpr); return;                                     //
    case binLOr:  GenCompLogicalOr(iReg, pExpr);  return;                                     //
    case binShr:  GenShiftR(iReg, pExpr);         return;                                     //
    case binShl:  GenShiftL(iReg, pExpr);         return;                                     //
    default:                                                                                  //
        Error(FATAL, "GenExprBinary: Un recognized Op Binary %d\n", pExpr->Use.Binary.Op);    //
    }
}



// ##########################################################################
// #  Function: GenExprBinaryConditional
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
void GenExprBinaryConditional(int iReg, TPExprNode pExpr, LPSTR pszTrue, LPSTR pszFalse) {
    ASSERT(pExpr->Usage == uBinary);
    ASSERT(IsBoolean(pExpr->pType));

    switch (pExpr->Use.Binary.Op) {                                                 // Do the arithmetic. 
      case binAdd:  
      case binSub:
      case binMul:
      case binDiv:
      case binMod:
      case binAnd:
      case binOr: 
      case binXor:
           Error(FATAL, "GenExprBinaryConditional: Unrecognized Op Binary %d\n", pExpr->Use.Binary.Op);
           return;

      case binCEQ:  GenCompEQConditional(iReg, pExpr, pszTrue, pszFalse);         return; //
      case binCNE:  GenCompNEConditional(iReg, pExpr, pszTrue, pszFalse);         return; //
      case binCLT:  GenCompLTConditional(iReg, pExpr, pszTrue, pszFalse);         return; //
      case binCLE:  GenCompLEConditional(iReg, pExpr, pszTrue, pszFalse);         return; //
      case binCGT:  GenCompGTConditional(iReg, pExpr, pszTrue, pszFalse);         return; //
      case binCGE:  GenCompGEConditional(iReg, pExpr, pszTrue, pszFalse);         return; //
      case binLAnd: GenCompLogicalAndConditional(iReg, pExpr, pszTrue, pszFalse); return; //
      case binLOr:  GenCompLogicalOrConditional(iReg, pExpr, pszTrue, pszFalse);  return; //

      case binShr:
      case binShl:
      default:
           Error(FATAL, "GenExprBinaryConditional: Unrecognized Op Binary %d\n", pExpr->Use.Binary.Op);
    }
}



// ##########################################################################
// #  Function: GenExprTernary
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
void GenExprTernary(int iReg, TPExprNode pExpr) {
    ASSERT(pExpr->Usage == uTernary);
    LPSTR       szTernaryFalse = GenLabel("_TernaryFalse_");
    LPSTR       szTernaryExit  = GenLabel("_TernaryExit_");

    ASSERT(IsBoolean(pExpr->Use.Ternary.pFirst->pType));
    GenAsm("",             "",     "",            "   : Ternary start");
    GenExprConditional(iReg, pExpr->Use.Ternary.pFirst, NULL, szTernaryFalse);
    _GenExpr(iReg, pExpr->Use.Ternary.pSecond);
    GenAsm("",             "rjmp", szTernaryExit, "  2:");
    GenAsm(szTernaryFalse, "",     "",            "   :");
    _GenExpr(iReg, pExpr->Use.Ternary.pThird);
    GenAsm(szTernaryExit,  "",     "",            "   : Ternary end");
}



// #######################################################################################################################################

int IsSingleBit(LONG i) {
    switch (i & 0xFF) {
    case   1: return 1;
    case   2: return 2;
    case   4: return 3;
    case   8: return 4;
    case  16: return 5;
    case  32: return 6;
    case  64: return 7;
    case 128: return 8;
    default:  return 0;
    }
}
// ##########################################################################
// #  Function: GenExprAssignNop
// #        <todo: task brief description>
// #
// #        <todo: task detailed description>
// #
// #  Parameters:
// #       int iReg         - Working reg. used for building the result
// #       int iTargetSize  - size of the operation in bytes
// #       TPExprNode pLval - expr for Lval
// #       TPExprNode pRval - expr for Rval
// #
// #  Returns:
// #        nothing
// #
// #  See Also:
// #
// ##########################################################################
static void GenExprAssignNop(int iReg, int iTargetSize, TPExprNode pLval, TPExprNode pRval) {
    TMemAccess Z;
    ASSERT(iReg == REG_ACC);
    
    _GenExpr(iReg, pRval);                                                              // First Calculate the RVAL. 
    FetchOptions(REG_TMP, pLval, &Z);
    FetchStore(&Z, iReg);
}


// ##########################################################################
// #  Function: GenExprAssignOr
// #        <todo: task brief description>
// #
// #        <todo: task detailed description>
// #
// #  Parameters:
// #       int iReg         - Working reg. used for building the result
// #       int iTargetSize  - size of the operation in bytes
// #       TPExprNode pLval - expr for Lval
// #       TPExprNode pRval - expr for Rval
// #
// #  Returns:
// #        nothing
// #
// #  See Also:
// #
// ##########################################################################
static void GenExprAssignOr(int iReg, int iTargetSize, TPExprNode pLval, TPExprNode pRval) {
    TMemAccess Z;
    ASSERT(iReg == REG_ACC);

    if (pRval->Usage == uConst) {                                                                                                   // easy optimization if RVal is constant.
        FetchOptions(REG_TMP, pLval, &Z);                                                                                           //
        if (Z.Method == ACCESS_IO && Z.lN < 32 && IsSingleBit(pRval->Use.Const.lInteger)) {                                         //      better still if it set a single bit in a register?
            GenAsm("", "sbi", OperandImmediateImmediate((UCHAR)Z.lN, (UCHAR)IsSingleBit(pRval->Use.Const.lInteger)-1), CommentString(1, Z.pszS, " |= to set a single-bit"));
        }                                                                                                                           //
        else {                                                                                                                      //      second best use immediate opcodes.
            FetchLoad(&Z, iReg);                                                                                                    //
            switch (iTargetSize) {                                                                                                  //
            case 1:                                                                                                                 //
                GenAsm("", "ori", OperandRegImmediate(iReg + REG_ORDER0, (UCHAR)(pRval->Use.Const.lInteger)),        "  1: Or8");   //
                break;                                                                                                              //
            case 2:                                                                                                                 //
                GenAsm("", "ori", OperandRegImmediate(iReg + REG_ORDER0, (UCHAR)(pRval->Use.Const.lInteger)),       "  1: Or16");   //
                GenAsm("", "ori", OperandRegImmediate(iReg + REG_ORDER1, (UCHAR)(pRval->Use.Const.lInteger >> 8)),  "  1:");        //
                break;                                                                                                              //
            case 4:                                                                                                                 //
                GenAsm("", "ori", OperandRegImmediate(iReg + REG_ORDER0, (UCHAR)(pRval->Use.Const.lInteger)),       "  1: Or32");   //
                GenAsm("", "ori", OperandRegImmediate(iReg + REG_ORDER1, (UCHAR)(pRval->Use.Const.lInteger >> 8)),  "  1:");        //
                GenAsm("", "ori", OperandRegImmediate(iReg + REG_ORDER2, (UCHAR)(pRval->Use.Const.lInteger >> 16)), "  1:");        //
                GenAsm("", "ori", OperandRegImmediate(iReg + REG_ORDER3, (UCHAR)(pRval->Use.Const.lInteger >> 18)), "  1:");        //
                break;                                                                                                              //
            default:                                                                                                                //
                Error(FATAL, "GenExprAssignOr: size not supported (%d)\n", iTargetSize);                                            //
            }                                                                                                                       //
            FetchStore(&Z, iReg);                                                                                                   //
        }                                                                                                                           //
    }                                                                                                                               
    else {                                                                                                                          // long hand..
        _GenExpr(iReg, pRval);                                                                                                      //      First Calculate the RVAL. 
        FetchOptions(REG_TMP, pLval, &Z);                                                                                           //      Fetch Lval
        FetchLoad(&Z, REG_TMP);                                                                                                     //
        switch (iTargetSize) {                                                                                                      //      do the maths.
        case 1:                                                                                                                     //
            GenAsm("", "or", OperandRegReg(iReg + REG_ORDER0, REG_TMP0), "  1: Or 8");                                              //
            break;                                                                                                                  //
        case 2:                                                                                                                     //
            GenAsm("", "or", OperandRegReg(iReg + REG_ORDER0, REG_TMP0), "  1: Or 16");                                             //
            GenAsm("", "or", OperandRegReg(iReg + REG_ORDER1, REG_TMP1), "  1:");                                                   //
            break;                                                                                                                  //
        case 4:                                                                                                                     //
            GenAsm("", "or", OperandRegReg(iReg + REG_ORDER0, REG_TMP0), "  1: Or 32");                                             //
            GenAsm("", "or", OperandRegReg(iReg + REG_ORDER1, REG_TMP1), "  1:");                                                   //
            GenAsm("", "or", OperandRegReg(iReg + REG_ORDER2, REG_TMP2), "  1:");                                                   //
            GenAsm("", "or", OperandRegReg(iReg + REG_ORDER3, REG_TMP3), "  1:");                                                   //
            break;                                                                                                                  //
        default:                                                                                                                    //
            Error(FATAL, "GenExprAssignOr: size not supported (%d)\n", iTargetSize);                                                //
        }                                                                                                                           //
        FetchStore(&Z, iReg);                                                                                                       //
    }
}

// ##########################################################################
// #  Function: GenExprAssignAnd
// #        <todo: task brief description>
// #
// #        <todo: task detailed description>
// #
// #  Parameters:
// #       int iReg         - Working reg. used for building the result
// #       int iTargetSize  - size of the operation in bytes
// #       TPExprNode pLval - expr for Lval
// #       TPExprNode pRval - expr for Rval
// #
// #  Returns:
// #        nothing
// #
// #  See Also:
// #
// ##########################################################################
static void GenExprAssignAnd(int iReg, int iTargetSize, TPExprNode pLval, TPExprNode pRval) {
    TMemAccess Z;
    ASSERT(iReg == REG_ACC);

    if (pRval->Usage == uConst) {                                                                                                   // easy optimization if RVal is constant.
        FetchOptions(REG_TMP, pLval, &Z);                                                                                           //
        if (Z.Method == ACCESS_IO && Z.lN < 32 && IsSingleBit(~pRval->Use.Const.lInteger)) {                                        //      better still if it set a single bit in a register?
            GenAsm("", "cbi", OperandImmediateImmediate((UCHAR)Z.lN, (UCHAR)IsSingleBit(~pRval->Use.Const.lInteger) - 1), CommentString(1, Z.pszS, " &= to clear a single-bit"));
        }                                                                                                                           //
        else {                                                                                                                      //      second best use immediate opcodes.
            if (IsAllZeros(iTargetSize, pRval->Use.Const.lInteger)) {                                                               //
                switch (iTargetSize) {                                                                                              //
                case 1:                                                                                                             //
                    GenAsm("", "clr", OperandReg(iReg + REG_ORDER0), "  1: And8 #0");                                               //
                    break;                                                                                                          //
                case 2:                                                                                                             //
                    GenAsm("", "clr", OperandReg(iReg + REG_ORDER0), "  1: And16 #0");                                              //
                    GenAsm("", "clr", OperandReg(iReg + REG_ORDER1), "  1:");                                                       //
                    break;                                                                                                          //
                case 4:                                                                                                             //
                    GenAsm("", "clr", OperandReg(iReg + REG_ORDER0), "  1: And32 #0");                                              //
                    GenAsm("", "clr", OperandReg(iReg + REG_ORDER1), "  1:");                                                       //
                    GenAsm("", "clr", OperandReg(iReg + REG_ORDER2), "  1:");                                                       //
                    GenAsm("", "clr", OperandReg(iReg + REG_ORDER3), "  1:");                                                       //
                    break;                                                                                                          //
                default:                                                                                                            //
                    Error(FATAL, "GenExprAssignAnd: size not supported (%d)\n", iTargetSize);                                       //
                }                                                                                                                   //
                FetchStore(&Z, iReg);                                                                                               //
                return;
            }

            FetchLoad(&Z, iReg);                                                                                                    //
            if (IsAllOnes(iTargetSize, pRval->Use.Const.lInteger)) {
                return;
            }
            switch (iTargetSize) {                                                                                              //
            case 1:                                                                                                             //
                GenAsm("", "andi", OperandRegImmediate(iReg + REG_ORDER0, (UCHAR)(pRval->Use.Const.lInteger)), "  1: And8");    //
                break;                                                                                                          //
            case 2:                                                                                                             //
                GenAsm("", "andi", OperandRegImmediate(iReg + REG_ORDER0, (UCHAR)(pRval->Use.Const.lInteger)), "  1: And16");   //
                GenAsm("", "andi", OperandRegImmediate(iReg + REG_ORDER1, (UCHAR)(pRval->Use.Const.lInteger >> 8)), "  1:");    //
                break;                                                                                                          //
            case 4:                                                                                                             //
                GenAsm("", "andi", OperandRegImmediate(iReg + REG_ORDER0, (UCHAR)(pRval->Use.Const.lInteger)), "  1: And32");   //
                GenAsm("", "andi", OperandRegImmediate(iReg + REG_ORDER1, (UCHAR)(pRval->Use.Const.lInteger >> 8)), "  1:");    //
                GenAsm("", "andi", OperandRegImmediate(iReg + REG_ORDER2, (UCHAR)(pRval->Use.Const.lInteger >> 16)), "  1:");   //
                GenAsm("", "andi", OperandRegImmediate(iReg + REG_ORDER3, (UCHAR)(pRval->Use.Const.lInteger >> 18)), "  1:");   //
                break;                                                                                                          //
            default:                                                                                                            //
                Error(FATAL, "GenExprAssignAnd: size not supported (%d)\n", iTargetSize);                                       //
            }                                                                                                                   //
            FetchStore(&Z, iReg);                                                                                               //
        }
    }
    else {                                                                                                                          // long hand..
        _GenExpr(iReg, pRval);                                                                                                      //      First Calculate the RVAL. 
        FetchOptions(REG_TMP, pLval, &Z);                                                                                           //      Fetch Lval
        FetchLoad(&Z, REG_TMP);                                                                                                     //
        switch (iTargetSize) {                                                                                                      //      do the maths.
        case 1:                                                                                                                     //
            GenAsm("", "and", OperandRegReg(iReg + REG_ORDER0, REG_TMP0), "  1: And 8");                                            //
            break;                                                                                                                  //
        case 2:                                                                                                                     //
            GenAsm("", "and", OperandRegReg(iReg + REG_ORDER0, REG_TMP0), "  1: And 16");                                           //
            GenAsm("", "and", OperandRegReg(iReg + REG_ORDER1, REG_TMP1), "  1:");                                                  //
            break;                                                                                                                  //
        case 4:                                                                                                                     //
            GenAsm("", "and", OperandRegReg(iReg + REG_ORDER0, REG_TMP0), "  1: And 32");                                           //
            GenAsm("", "and", OperandRegReg(iReg + REG_ORDER1, REG_TMP1), "  1:");                                                  //
            GenAsm("", "and", OperandRegReg(iReg + REG_ORDER2, REG_TMP2), "  1:");                                                  //
            GenAsm("", "and", OperandRegReg(iReg + REG_ORDER3, REG_TMP3), "  1:");                                                  //
            break;                                                                                                                  //
        default:                                                                                                                    //
            Error(FATAL, "GenExprAssignAnd: size not supported (%d)\n", iTargetSize);                                               //
        }                                                                                                                           //
        FetchStore(&Z, iReg);                                                                                                       //
    }
}

// ##########################################################################
// #  Function: GenExprAssignAdd
// #        <todo: task brief description>
// #
// #        <todo: task detailed description>
// #
// #  Parameters:
// #       int iReg         - Working reg. used for building the result
// #       int iTargetSize  - size of the operation in bytes
// #       TPExprNode pLval - expr for Lval
// #       TPExprNode pRval - expr for Rval
// #
// #  Returns:
// #        nothing
// #
// #  See Also:
// #
// ##########################################################################
static void GenExprAssignAdd(int iReg, int iTargetSize, TPExprNode pLval, TPExprNode pRval) {
    TMemAccess Z;
    ASSERT(iReg == REG_ACC);

    if (pRval->Usage == uConst) {                                                                                                   // easy optimization if RVal is constant.
        FetchOptions(REG_TMP, pLval, &Z);                                                                                           //
        FetchLoad(&Z, iReg);                                                                                                        //
        LONG lV = -pRval->Use.Const.lInteger;                                                                                       //
        switch (iTargetSize) {                                                                                                      //
        case 1:                                                                                                                     //
            GenAsm("", "subi", OperandRegImmediate(iReg + REG_ORDER0, (UCHAR)(lV)),       CommentNumber(1, "Add8 #", -lV));         //
            break;                                                                                                                  //
        case 2:                                                                                                                     //
            GenAsm("", "subi", OperandRegImmediate(iReg + REG_ORDER0, (UCHAR)(lV)),       CommentNumber(1, "Add16 #", -lV));        //
            GenAsm("", "sbci", OperandRegImmediate(iReg + REG_ORDER1, (UCHAR)(lV >> 8)),  "  1:");                                  //
            break;                                                                                                                  //
        case 4:                                                                                                                     //
            GenAsm("", "subi", OperandRegImmediate(iReg + REG_ORDER0, (UCHAR)(lV)),       CommentNumber(1, "Add32 #", -lV));        //
            GenAsm("", "sbci", OperandRegImmediate(iReg + REG_ORDER1, (UCHAR)(lV >> 8)),  "  1:");                                  //
            GenAsm("", "sbci", OperandRegImmediate(iReg + REG_ORDER2, (UCHAR)(lV >> 16)), "  1:");                                  //
            GenAsm("", "sbci", OperandRegImmediate(iReg + REG_ORDER3, (UCHAR)(lV >> 18)), "  1:");                                  //
            break;                                                                                                                  //
        default:                                                                                                                    //
            Error(FATAL, "GenExprAssignAdd: size not supported (%d)\n", iTargetSize);                                               //
        }                                                                                                                           //
        FetchStore(&Z, iReg);                                                                                                       //
    }
    else {                                                                                                                          // long hand..
        _GenExpr(iReg, pRval);                                                                                                      //      First Calculate the RVAL. 
        FetchOptions(REG_TMP, pLval, &Z);                                                                                           //      Fetch Lval
        FetchLoad(&Z, REG_TMP);                                                                                                     //
        switch (iTargetSize) {                                                                                                      //      do the maths.
        case 1:                                                                                                                     //
            GenAsm("", "add", OperandRegReg(iReg + REG_ORDER0, REG_TMP0), "  1: Add 8");                                            //
            break;                                                                                                                  //
        case 2:                                                                                                                     //
            GenAsm("", "add", OperandRegReg(iReg + REG_ORDER0, REG_TMP0), "  1: Add 16");                                           //
            GenAsm("", "adc", OperandRegReg(iReg + REG_ORDER1, REG_TMP1), "  1:");                                                  //
            break;                                                                                                                  //
        case 4:                                                                                                                     //
            GenAsm("", "add", OperandRegReg(iReg + REG_ORDER0, REG_TMP0), "  1: Add 32");                                           //
            GenAsm("", "adc", OperandRegReg(iReg + REG_ORDER1, REG_TMP1), "  1:");                                                  //
            GenAsm("", "adc", OperandRegReg(iReg + REG_ORDER2, REG_TMP2), "  1:");                                                  //
            GenAsm("", "adc", OperandRegReg(iReg + REG_ORDER3, REG_TMP3), "  1:");                                                  //
            break;                                                                                                                  //
        default:                                                                                                                    //
            Error(FATAL, "GenExprAssignAdd: size not supported (%d)\n", iTargetSize);                                               //
        }                                                                                                                           //
        FetchStore(&Z, iReg);                                                                                                       //
    }
}


// ##########################################################################
// #  Function: GenExprAssignSub
// #        <todo: task brief description>
// #
// #        <todo: task detailed description>
// #
// #  Parameters:
// #       int iReg         - Working reg. used for building the result
// #       int iTargetSize  - size of the operation in bytes
// #       TPExprNode pLval - expr for Lval
// #       TPExprNode pRval - expr for Rval
// #
// #  Returns:
// #        nothing
// #
// #  See Also:
// #
// ##########################################################################
static void GenExprAssignSub(int iReg, int iTargetSize, TPExprNode pLval, TPExprNode pRval) {
    TMemAccess Z;
    ASSERT(iReg == REG_ACC);

    if (pRval->Usage == uConst) {                                                                                                   // easy optimization if RVal is constant.
        FetchOptions(REG_TMP, pLval, &Z);                                                                                           //
        FetchLoad(&Z, iReg);                                                                                                        //
        LONG lV = pRval->Use.Const.lInteger;                                                                                        //
        switch (iTargetSize) {                                                                                                      //
        case 1:                                                                                                                     //
            GenAsm("", "subi", OperandRegImmediate(iReg + REG_ORDER0, (UCHAR)(lV)),       CommentNumber(1, "Sub8 #", lV));          //
            break;                                                                                                                  //
        case 2:                                                                                                                     //
            GenAsm("", "subi", OperandRegImmediate(iReg + REG_ORDER0, (UCHAR)(lV)),       CommentNumber(1, "Sub16 #", lV));         //
            GenAsm("", "sbci", OperandRegImmediate(iReg + REG_ORDER1, (UCHAR)(lV >> 8)),  "  1:");                                  //
            break;                                                                                                                  //
        case 4:                                                                                                                     //
            GenAsm("", "subi", OperandRegImmediate(iReg + REG_ORDER0, (UCHAR)(lV)),       CommentNumber(1, "Sub32 #", lV));         //
            GenAsm("", "sbci", OperandRegImmediate(iReg + REG_ORDER1, (UCHAR)(lV >> 8)),  "  1:");                                  //
            GenAsm("", "sbci", OperandRegImmediate(iReg + REG_ORDER2, (UCHAR)(lV >> 16)), "  1:");                                  //
            GenAsm("", "sbci", OperandRegImmediate(iReg + REG_ORDER3, (UCHAR)(lV >> 18)), "  1:");                                  //
            break;                                                                                                                  //
        default:                                                                                                                    //
            Error(FATAL, "GenExprAssignSub: size not supported (%d)\n", iTargetSize);                                               //
        }                                                                                                                           //
        FetchStore(&Z, iReg);                                                                                                       //
    }
    else {                                                                                                                          // long hand..
        _GenExpr(iReg, pRval);                                                                                                      //      First Calculate the RVAL. 
        FetchOptions(REG_TMP, pLval, &Z);                                                                                           //      Fetch Lval
        FetchLoad(&Z, REG_TMP);                                                                                                     //
        switch (iTargetSize) {                                                                                                      //      do the maths.
        case 1:                                                                                                                     //
            GenAsm("", "sub", OperandRegReg(REG_TMP0, iReg + REG_ORDER0), "  1: Sub 8");                                            //
            GenAsm("", "mov", OperandRegReg(iReg + REG_ORDER0, REG_TMP0), "  1:");                                                  //
            break;                                                                                                                  //
        case 2:                                                                                                                     //
            GenAsm("", "sub",  OperandRegReg(REG_TMP0, iReg + REG_ORDER0), "  1: Sub 16");                                          //
            GenAsm("", "sbc",  OperandRegReg(REG_TMP1, iReg + REG_ORDER1), "  1:");                                                 //
            GenAsm("", "movw", OperandRegReg(iReg + REG_ORDER0, REG_TMP0), "  1:");                                                 //
            break;                                                                                                                  //
        case 4:                                                                                                                     //
            GenAsm("", "sub",  OperandRegReg(REG_TMP0, iReg + REG_ORDER0), "  1: Sub 32");                                          //
            GenAsm("", "sbc",  OperandRegReg(REG_TMP1, iReg + REG_ORDER1), "  1:");                                                 //
            GenAsm("", "sbc",  OperandRegReg(REG_TMP2, iReg + REG_ORDER2), "  1:");                                                 //
            GenAsm("", "sbc",  OperandRegReg(REG_TMP3, iReg + REG_ORDER3), "  1:");                                                 //
            GenAsm("", "movw", OperandRegReg(iReg + REG_ORDER0, REG_TMP0), "  1:");                                                 //
            GenAsm("", "movw", OperandRegReg(iReg + REG_ORDER2, REG_TMP2), "  1:");                                                 //
            break;                                                                                                                  //
        default:                                                                                                                    //
            Error(FATAL, "GenExprAssignSub: size not supported (%d)\n", iTargetSize);                                               //
        }                                                                                                                           //
        FetchStore(&Z, iReg);                                                                                                       //
    }
}


// ##########################################################################
// #  Function: GenExprAssignXor
// #        <todo: task brief description>
// #
// #        <todo: task detailed description>
// #
// #  Parameters:
// #       int iReg         - Working reg. used for building the result
// #       int iTargetSize  - size of the operation in bytes
// #       TPExprNode pLval - expr for Lval
// #       TPExprNode pRval - expr for Rval
// #
// #  Returns:
// #        nothing
// #
// #  See Also:
// #
// ##########################################################################
static void GenExprAssignXor(int iReg, int iTargetSize, TPExprNode pLval, TPExprNode pRval) {
    TMemAccess Z;
    ASSERT(iReg == REG_ACC);

    if ((pRval->Usage == uConst) && (pRval->Use.Const.lInteger == 0)) {                                                             // easy optimization if RVal is constant 0.
        ;                                                                                                                           //
    }
    else if ((pRval->Usage == uConst) && IsAllOnes(iTargetSize, pRval->Use.Const.lInteger)) {                                       // easy optimization if RVal is constant -1.
        FetchOptions(REG_TMP, pLval, &Z);                                                                                           //
        FetchLoad(&Z, iReg);                                                                                                        //
        switch (iTargetSize) {                                                                                                      //
        case 1:                                                                                                                     //
            GenAsm("", "com", OperandReg(iReg + REG_ORDER0),  "  1: Xor8 #0xFF");                                                   //
            break;                                                                                                                  //
        case 2:                                                                                                                     //
            GenAsm("", "com", OperandReg(iReg + REG_ORDER0), "  1: Xor16 #0xFFFF");                                                 //
            GenAsm("", "com", OperandReg(iReg + REG_ORDER1), "  1:");                                                               //
            break;                                                                                                                  //
        case 4:                                                                                                                     //
            GenAsm("", "com", OperandReg(iReg + REG_ORDER0), "  1: Xor32 #0xFFFFFFFF");                                             //
            GenAsm("", "com", OperandReg(iReg + REG_ORDER1), "  1:");                                                               //
            GenAsm("", "com", OperandReg(iReg + REG_ORDER2), "  1:");                                                               //
            GenAsm("", "com", OperandReg(iReg + REG_ORDER3), "  1:");                                                               //
            break;                                                                                                                  //
        default:                                                                                                                    //
            Error(FATAL, "GenExprAssignXor: size not supported (%d)\n", iTargetSize);                                               //
        }                                                                                                                           //
        FetchStore(&Z, iReg);                                                                                                       //
    }
    else {                                                                                                                          // long hand..
        _GenExpr(iReg, pRval);                                                                                                      //      First Calculate the RVAL. 
        FetchOptions(REG_TMP, pLval, &Z);                                                                                           //      Fetch Lval
        FetchLoad(&Z, REG_TMP);                                                                                                     //
        switch (iTargetSize) {                                                                                                      //      do the maths.
        case 1:                                                                                                                     //
            GenAsm("", "eor", OperandRegReg(iReg + REG_ORDER0, REG_TMP0), "  1: Xor 8");                                            //
            break;                                                                                                                  //
        case 2:                                                                                                                     //
            GenAsm("", "eor", OperandRegReg(iReg + REG_ORDER0, REG_TMP0), "  1: Xor 16");                                           //
            GenAsm("", "eor", OperandRegReg(iReg + REG_ORDER1, REG_TMP1), "  1:");                                                  //
            break;                                                                                                                  //
        case 4:                                                                                                                     //
            GenAsm("", "eor", OperandRegReg(iReg + REG_ORDER0, REG_TMP0), "  1: Xor 32");                                           //
            GenAsm("", "eor", OperandRegReg(iReg + REG_ORDER1, REG_TMP1), "  1:");                                                  //
            GenAsm("", "eor", OperandRegReg(iReg + REG_ORDER2, REG_TMP2), "  1:");                                                  //
            GenAsm("", "eor", OperandRegReg(iReg + REG_ORDER3, REG_TMP3), "  1:");                                                  //
            break;                                                                                                                  //
        default:                                                                                                                    //
            Error(FATAL, "GenExprAssignXor: size not supported (%d)\n", iTargetSize);                                               //
        }                                                                                                                           //
        FetchStore(&Z, iReg);                                                                                                       //
    }
}


// ##########################################################################
// #  Function: GenExprAssign
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
void GenExprAssign(int iReg, TPExprNode pExpr) {
    TPExprNode pLval = pExpr->Use.Assign.pLval;
    TPExprNode pRval = pExpr->Use.Assign.pRval;
    int iTargetSize = CalcSizeOf(pLval->pType);
    int iSourceSize = CalcSizeOf(pRval->pType);
    ASSERT(iReg == REG_ACC);

    ASSERT(iTargetSize == iSourceSize);                                                                          // Confirm sizes match. 

    // TOS = the new value to store
    if (IsTypeQualifierConst(pExpr->pType)) {                                                                    // Trouble if we want to assign to a constant!
        GenAsm(";", "!!!", "write to ROM", "   : Code omitted here. The prescription is silly");                 //
        return;                                                                                                  //
    }                                                                                                            //
    ASSERT(iReg == REG_ACC);
    switch (pExpr->Use.Assign.Op) {
    case binNop: GenExprAssignNop(iReg, iTargetSize, pLval, pRval); return;
    case binAdd: GenExprAssignAdd(iReg, iTargetSize, pLval, pRval); return;
    case binSub: GenExprAssignSub(iReg, iTargetSize, pLval, pRval); return;
#pragma message("    GenExprAssignMul(): Needs implementing.")   // dont forget coresponding the yacc changes.
    case binMul:
#pragma message("    GenExprAssignDiv(): Needs implementing.")   // dont forget coresponding the yacc changes.
    case binDiv:
#pragma message("    GenExprAssignMod(): Needs implementing.")   // dont forget coresponding the yacc changes.
    case binMod:
    case binOr:  GenExprAssignOr(iReg, iTargetSize, pLval, pRval);  return;
    case binAnd: GenExprAssignAnd(iReg, iTargetSize, pLval, pRval); return;
    case binXor: GenExprAssignXor(iReg, iTargetSize, pLval, pRval); return;
    //case binCEQ:
    //case binCNE:
    //case binCLT:
    //case binCLE:
    //case binCGT:
    //case binCGE:
    //case binLAnd:
    //case binLOr:
#pragma message("    GenExprAssignShr(): Needs implementing.")   // dont forget coresponding the yacc changes.
    //case binShr:
#pragma message("    GenExprAssignShl(): Needs implementing.")   // dont forget coresponding the yacc changes.
    //case binShl:
    default:
        Error(FATAL, "GenExprAssign() - Unimplemented assignment operator\n"); break;

    }

}



int     _GenCostOfCalculation(TPExprNode pExpr) {
    int iCost    = 0;
    int iBiggest = 0;
    for (; pExpr; pExpr = pExpr->pSibling) {
        switch (pExpr->Usage) {
        case    uConst:   iCost = 1; break;                                                 // Const lookup uses the target register only.
        case    uVar:     if (IsTypeQualifierConst(pExpr->pType) &&                         // lookup of const global needs to use Z as well.
                              (pExpr->Use.Var.pDecId == NULL)) { 
                            iCost = 2;
                          }
                          else {
                            iCost = 1;
                          }
                          break;
        case    uUnary:   iCost = _GenCostOfCalculation(pExpr->Use.Unary.pOperand); break;  // In-situ on top of cost of decendant.
        case    uBinary:  if (pExpr->Use.Binary.pLeft->Usage == uConst)       iCost = _GenCostOfCalculation(pExpr->Use.Binary.pRight);
                          else if (pExpr->Use.Binary.pRight->Usage == uConst) iCost = _GenCostOfCalculation(pExpr->Use.Binary.pLeft); 
                          else {
                            int iL = _GenCostOfCalculation(pExpr->Use.Binary.pLeft); 
                            int iR = _GenCostOfCalculation(pExpr->Use.Binary.pRight);
                            iCost = 1 + max(iL - 1, iR);                                    // lazy assumption but may be bigger than 1.
                           }
                          break;
        case    uTernary: iCost = 2; break;                                                 // lazy assumption but may be bigger than 1.
        case    uDot:     Error(FATAL, "GenExpr() - uDot needs implementing\n"); break;
        case    uArrow:   Error(FATAL, "GenExpr() - uArrow needs implementing\n"); break;
        case    uArray:                                                                     // not expecting to be here. Array access was re-parsed to make it a collection of & and * operators.
            Error(FATAL, "GenExpr() - uArray needs implementing\n"); break;
        case    uFunc:    iCost = 2; break; 
        case    uCast:    iCost = _GenCostOfCalculation(pExpr->Use.Cast.pTarget);    break;
        case    uAssign:  iCost = 2; break;                                                 // lazy assumption but may be bigger than 1.
        default:          Error(FATAL, "GenExpr() - [%d]\n", pExpr->Usage); break;
        }
        iBiggest = max(iBiggest, iCost);
    }
    return iBiggest;
}



// ##########################################################################
// #  Function: GenFunction
// #        Generate code for a call to a function.
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
static void GenFunctionCall(int iReg, TPExprNode pExpr) {
    BOOL    fDirect;
    BOOL    fElipsis = FALSE;
    LPSTR   szVerifiedReturn = "";


    ASSERT(pExpr->Usage == uFunc);
    TPExprNode pInvokationParameterList = pExpr->Use.Func.pParams;
    int iCallParamaters;
    for (iCallParamaters = 0; pInvokationParameterList != NULL; iCallParamaters++, pInvokationParameterList = pInvokationParameterList->pPreviousArg);

    //ASSERT(pExpr->Use.Func.pFunc->Usage == uVar);
    //printf("name=%s", pExpr->Use.Func.pFunc->Use.Var.pszIdentifier);
    
    TPDeclSpec pDefnParameterList;
    TPDeclSpec pReturnType;
    WORD wFnQualifier;

    if (IsFunc(pExpr->Use.Func.pFunc->pType)) {
        fDirect = TRUE;                                                                                                         // direct function call.
        pDefnParameterList = pExpr->Use.Func.pFunc->pType->Use.DecFunc.pPList;
        pReturnType = pExpr->Use.Func.pFunc->pType->Use.DecFunc.pReturnType;
    }
    else if (IsPointer(pExpr->Use.Func.pFunc->pType) && IsFunc(pExpr->Use.Func.pFunc->pType->Use.DecPtr.pTarget)) {
        fDirect = FALSE;                                                                                                        // indirect call
        pDefnParameterList = pExpr->Use.Func.pFunc->pType->Use.DecPtr.pTarget->Use.DecFunc.pPList;
        pReturnType = pExpr->Use.Func.pFunc->pType->Use.DecPtr.pTarget->Use.DecFunc.pReturnType;
    }
    else {
        ASSERT(FALSE);
        return;
    }

    ASSERT(pReturnType != NULL);
    if (pReturnType->Usage == DecSpec) { wFnQualifier = pReturnType->Use.DecSpec.wQual; }
    else if (pReturnType->Usage == DecPtr) { wFnQualifier = pReturnType->Use.DecPtr.wQual; }
    else ASSERT(FALSE);

    int        iDefnParamaters;
    TPDeclSpec pPl = pDefnParameterList;
    for (iDefnParamaters = 0; pPl != NULL; iDefnParamaters++, pPl = pPl->Use.DecId.pBrother) {
        if ((pPl->Use.DecId.pTarget->Usage == DecSpec) &&                                                                               //
            (pPl->Use.DecId.pTarget->Use.DecSpec.Type == TypeVOID)) {                                                                   // void is special case 1 param expecting zero!
            if (!(iDefnParamaters == 0 && pPl->Use.DecId.pBrother == NULL)) {                                                           // void  should be the only parameter if the grammar works OK
                Error(ERROR0, "Compiler internal logic is screwed.");                                                                                  //
            }                                                                                                                                          //
            break;                                                                                                                                     //
        }                                                                                                                                              //

        if (strcmp(pPl->Use.DecId.pszName, "...") == 0) {
            fElipsis |= (strcmp(pPl->Use.DecId.pszName, "...") == 0);
            iDefnParamaters--;
        }
    }

    if (iDefnParamaters > iCallParamaters) {
        ASSERT(FALSE);
        // this was trapped when parsing the call.
        Error(ERRORX, "Function '%s' expects %d parameters. This invocation has %d.", pExpr->Use.Func.pFunc->Use.Var.pszIdentifier, iDefnParamaters, iCallParamaters);
        return;
    }

    int nTotalPushes = 0;
    pInvokationParameterList = pExpr->Use.Func.pParams;

    pPl = pDefnParameterList;
    if ((iCallParamaters == iDefnParamaters) && fElipsis) {                                                                             // formal defn parameters. used to ensure type compliance of each parameter.                                        // elipise needs clipping if no XS parameters were provided.
        pPl = pPl = pPl->Use.DecId.pBrother;                                                                                            //      so cut it off here if we have it..
    }                                                                                                                                   //

    while (iCallParamaters > 0) {                                                                                                       // Parameters   
        ASSERT(pPl->Usage == DecId);                                                                                                    //
                                                                                                                                        //
        GenAsm("", "", "", CommentNumber(0, "Calculate parameter #", iCallParamaters));                                                 //
        _GenExpr(iReg, pInvokationParameterList);                                                                                       //      Calculate it.
                                                                                                                                        //
        if (iCallParamaters > 1) {                                                                                                      //      Push it to the call stack
            nTotalPushes += AVR_Push(iReg, CalcSizeOf(pInvokationParameterList->pType), pPl->Use.DecId.pszName);                        //
        }                                                                                                                               //
        else {                                                                                                                          //      Unless it's the first parameter
            GenAsm("", "", "", CommentString(0, "First parameter is passed in register.  ", pPl->Use.DecId.pszName));                   //      It stays in the Accumulator 
        }                                                                                                                               //
                                                                                                                                        //
        pInvokationParameterList = pInvokationParameterList->pPreviousArg;                                                              //
        iCallParamaters--;                                                                                                              //
        if (iCallParamaters <= iDefnParamaters) {                                                                                       //      == clips the elipsis; < traverses the list.
            pPl = pPl->Use.DecId.pBrother;                                                                                              //
        }                                                                                                                               //
    }

    if (!fDirect) {                                                                                                                     //  Indirect call needs to setup Z.
        int i = _GenCostOfCalculation(pExpr->Use.Func.pFunc);
        if (i <2) _GenExpr(30, pExpr->Use.Func.pFunc);
        else {
            ASSERT(FALSE);
            //GenAsm("", "nop", "", "  1: Fake Code used to complete testing");                                                    //
            //#pragma message("    **** DEBUG Fake code here.")
        }
    }


    if (!FnIsUndefended(wFnQualifier) && ((CmdLine.iDefendCallRet & 1) == 1)) {                                                                                                 // Defended call type 1.
        if (fDirect) {                                                                                                                                                          //  Direct call     
            GenAsm("", "ldi", OperandFreeform("r%d, lo8(%s-1)", REG_DEFENDER, pExpr->Use.Func.pFunc->Use.Var.pszIdentifier), CommentString(1, "Defended call", ""));            //
        }
        else {
            GenAsm("", "mov", OperandFreeform("r%d, r30", REG_DEFENDER), CommentString(1, "Defended call", ""));                                                                //
            GenAsm("", "lsl", OperandFreeform("r%d", REG_DEFENDER), "  1:");                                                                                                   //
            GenAsm("", "dec", OperandFreeform("r%d", REG_DEFENDER), "  1:");                                                                                                   //
        }
    }                                                                                                                                                                           //
                                                                                                                                                                                
    if ((wFnQualifier & QualNORETURN) == QualNORETURN) {                                                                                                                        // Invoke noreturn function
        if (fDirect) {                                                                                                                                                          //  Direct call     
            GenAsm("", "rjmp", pExpr->Use.Func.pFunc->Use.Var.pszIdentifier, "  2: Invoke the function (No return)");                                                           //
        }                                                                                                                                                                       //
        else {                                                                                                                                                                  //      indirect call
            GenAsm("", "ijmp", "",                                           "  2: Invoke indirect @Z (No return)");                                                            //
        }                                                                                                                                                                       //
    }                                                                                                                                                                           //
    else {                                                                                                                                                                      // Invoke returning function
        if (fDirect) {                                                                                                                                                          //  Direct call     
            GenAsm("", ASM_CALL_OPCODE, pExpr->Use.Func.pFunc->Use.Var.pszIdentifier, "  3: Invoke the function");                                                              //      returning function
        }                                                                                                                                                                       //
        else {                                                                                                                                                                  //      indirect call
            GenAsm("", "icall", "",                                           "  3: Invoke indirect @Z");                                                                       //
        }                                                                                                                                                                       //

        if (!FnIsUndefended(wFnQualifier) && ((CmdLine.iDefendCallRet & 1) == 1)) {                                                                                             // Defended call type 1.
            szVerifiedReturn = GenLabel("_OK_");                                                                                                                                //
            if ((CmdLine.iDefendCallRet & 2) == 2) {
                GenAsm("", "clz", "",                                                                          CommentString(1, "   Preset to fail if subi is skipped.", ""));  // additional defence 2
            }
            if (fDirect) {                                                                                                                                                          //  Direct call     
                GenAsm("", "subi", OperandFreeform("r%d, lo8(%s+1)", REG_DEFENDER, pExpr->Use.Func.pFunc->Use.Var.pszIdentifier), CommentString(1, "   Check who returned", ""));   //
                GenAsm("", "BREQ", szVerifiedReturn, CommentString(2, "   Expected returner?", ""));                                                                                // capitals to stop auto generation of brne_>trap
                GenAsm("", ASM_TRAP_OPCODE, ASM_TRAP_OPERAND, CommentString(2, "   Accept no substitutes.", ""));              //
                if ((CmdLine.iDefendCallRet & 4) == 4) {                                                                                                                            // additional defence 4
                    GenAsm("", ASM_TRAP_OPCODE, ASM_TRAP_OPERAND, CommentString(2, "   Repeated in case the the earlier one was skipped.", ""));                                                    //
                }
            }
            else {
                ; // what about the Z that's now corrupted!!!!
            }
        }                                                                                                                                                                       //

        if (nTotalPushes > 3) {                                                                                                     // 3 pop = same cycles but smaller code.
            GenAsm(szVerifiedReturn, "in", OperandRegStr(REG_TMP0, "_IO_SPL"), "  1: Strip parameters from the stack");
            GenAsm("", "in", OperandRegStr(REG_TMP1, "_IO_SPH"), "  1:");
            GenAsm("", "adiw", OperandRegImmediate(REG_TMP, nTotalPushes), "  2:");
            GenAsm("", "out", OperandStrReg("_IO_SPH", REG_TMP1), "  1:");
            GenAsm("", "out", OperandStrReg("_IO_SPL", REG_TMP0), "  1:");
        }
        else if (nTotalPushes > 0) {
            GenAsm(szVerifiedReturn, "pop", OperandReg(REG_TMP0), "  2: Strip parameters from the stack");
            while (--nTotalPushes) {
                GenAsm("", "pop", OperandReg(REG_TMP0), "  2:");
            }
        }
        else {
            GenAsm(szVerifiedReturn, "", "", "   :");
            // nothing to clean up
        }
    }

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
void _GenExpr(int iReg, TPExprNode pExpr) {
    ASSERT(pExpr != NULL);
    ASSERT(iReg == REG_ACC || iReg == REG_TMP || iReg == 30);

    for (; pExpr ; pExpr = pExpr->pSibling) {
        switch (pExpr->Usage) {
        case    uConst:   GenExprConst(iReg, pExpr); break;
        case    uIoreg:   GenExprIoreg(iReg, pExpr); break;
        case    uVar:     GenExprVar(iReg, pExpr); break;
        case    uUnary:   GenExprUnary(iReg, pExpr);  break;
        case    uBinary:  GenExprBinary(iReg, pExpr); break;
        case    uTernary: GenExprTernary(iReg, pExpr); break;
        case    uArrow:   Error(FATAL, "GenExpr() - uArrow needs implementing\n"); break;
        case    uDot:     // not expecting to be here. Dot access was re-parsed to make it a collection of & and * operators.
        case    uArray:   // not expecting to be here. Array access was re-parsed to make it a collection of & and * operators.
            Error(FATAL, "GenExpr() - uArray needs implementing\n"); break;
        case    uFunc:    GenFunctionCall(iReg, pExpr);   break;
        case    uCast:    GenExprCast(iReg, pExpr);   break;
        case    uAssign:  GenExprAssign(iReg, pExpr); break;
        default:          Error(FATAL, "GenExpr() - [%d]\n", pExpr->Usage); break;
        } 
    }

    return;

}

// ##########################################################################
// #  Function: GenExpression
// #        Evaluate an expression leaving the result in the Accumulator register.
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
void    GenExpression(TPExprNode pExpr) {

    if (CmdLine.fExpr) {
    ConsolePrintf(CON_YELLOW_BRIGHT, "Expression generation.\n");
    GenExpressionPrettyPrint(0, pExpr);
    ConsolePrintf(CON_YELLOW_BRIGHT, "\n");
    }

    pExpr = ExprOptimize(pExpr);
    _GenExpr(REG_ACC, pExpr);

}



// ##########################################################################
// #  Function: GenExprConditional
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
static void GenExprConditional(int iReg, TPExprNode pExpr, LPSTR pszTrue, LPSTR pszFalse) {
    ASSERT(pExpr != NULL);
    ASSERT(IsBoolean(pExpr->pType));

    switch (pExpr->Usage) {
    case    uConst:   GenExprConstConditional(REG_ACC, pExpr, pszTrue, pszFalse); return;
    case    uVar:     //GenExprVar(REG_ACC, pExpr); return;
    case    uUnary:   GenExprUnaryConditional(iReg, pExpr, pszTrue, pszFalse); return;
    case    uBinary:  GenExprBinaryConditional(iReg, pExpr, pszTrue, pszFalse); return;
    case    uTernary: //Error(FATAL, "GenExprCond() - uTernary needs implementing\n"); return;
    case    uDot:     //Error(FATAL, "GenExprCond() - uDot needs implementing\n"); return;
    case    uArrow:   //Error(FATAL, "GenExprCond() - uArrow needs implementing\n"); return;
    case    uArray:   // not expecting to be here. Array access was re-parsed to make it a collection of & and * operators.
                      //Error(FATAL, "GenExprCond() - uArray needs implementing\n"); return;
    case    uFunc:    //Error(FATAL, "GenExprCond() - uFunc needs implementing\n"); return;
                      Error(FATAL, "GenExprCond() - [%d]\n", pExpr->Usage); return;
    case    uCast:    GenExprCastConditional(iReg, pExpr, pszTrue, pszFalse);   return;
    case    uAssign:  //GenExprAssign(pExpr); return;
    default:          Error(FATAL, "GenExprCond() - [%d]\n", pExpr->Usage); return;
    }
    return;

}

// ##########################################################################
// #  Function: GenExpressionConditional
// #        As per <GenExpression> except the result is a jump to one or two labels depending on the result being <TRU> or <FALSE>.
// #        The input expression must be of type BOOL.
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

void    GenExpressionConditional(TPExprNode pExpr, LPSTR pzsTrue, LPSTR pszFalse) {

    //ConsolePrintf(CON_YELLOW_BRIGHT, "Conditional Expression generation.\n");
    //GenExpressionPrettyPrint(0, pExpr);
    //ConsolePrintf(CON_YELLOW_BRIGHT, "\n");

    GenExprConditional(REG_ACC, pExpr, pzsTrue, pszFalse);
}



/*
// ##############################################################################################################################################
int     _GenParameterCostExpression(int iMax, TPExprNode pExpr);

int ParamListCost(TPExprNode pParams) {
    int iUsed = 0;
    int iDeeper = 0;
    while (pParams != NULL) {
        iUsed += 1;
        iDeeper = _GenParameterCostExpression(iDeeper, pParams);
        pParams = pParams->pPreviousArg;
    }
    return max(iUsed, iDeeper);
}



// ##########################################################################
// #  Function: _GenParameterCostExpression
// #        Calculate the maximum number of parameters passeed during function 
// #        calls while evaluating this expression.
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
int     _GenParameterCostExpression(int iMax, TPExprNode pExpr) {
    int iThis;

    while (pExpr != NULL) {
        switch (pExpr->Usage) {
        case    uConst:
        case    uVar:     break;
        case    uUnary:   iMax = _GenParameterCostExpression(iMax, pExpr->Use.Unary.pOperand);
                          break;
        case    uBinary:  iMax = _GenParameterCostExpression(iMax, pExpr->Use.Binary.pLeft); 
                          iMax = _GenParameterCostExpression(iMax, pExpr->Use.Binary.pRight);
                          break;
        case    uTernary: iMax = _GenParameterCostExpression(iMax, pExpr->Use.Ternary.pFirst);
                          iMax = _GenParameterCostExpression(iMax, pExpr->Use.Ternary.pSecond);
                          iMax = _GenParameterCostExpression(iMax, pExpr->Use.Ternary.pThird);
                          break;
        case    uFunc:    iThis = ParamListCost(pExpr->Use.Func.pParams);
                          iMax = max(iThis, iMax);
                          break;
        case    uCast:    iMax = _GenParameterCostExpression(iMax, pExpr->Use.Cast.pTarget); 
                          break;
        case    uAssign:  iMax = _GenParameterCostExpression(iMax, pExpr->Use.Assign.pLval);
                          iMax = _GenParameterCostExpression(iMax, pExpr->Use.Assign.pRval);
                          break;
        case    uDot:     
        case    uArrow:   
        case    uArray:   
        default:          Error(FATAL, "_GenParameterCostExpression() - [%d]\n", pExpr->Usage); 
        }
        pExpr = pExpr->pSibling;
    }
    return iMax;
}
*/


// ##########################################################################
// #  Function: _GenParameterCostExpression
// #        Calculate the maximum number of parameters passeed during function 
// #        calls while evaluating this expression.
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
BOOL    _GenExprNestedCall(TPExprNode pExpr) {
    BOOL fFound = FALSE;

    while (pExpr != NULL && !fFound) {
        switch (pExpr->Usage) {
        case    uConst:
        case    uVar: 
        case    uIoreg:   break;
        case    uUnary:   fFound |= _GenExprNestedCall(pExpr->Use.Unary.pOperand);
                          break;
        case    uBinary:  fFound |= _GenExprNestedCall(pExpr->Use.Binary.pLeft);
                          fFound |= _GenExprNestedCall(pExpr->Use.Binary.pRight);
                          break;
        case    uTernary: fFound |= _GenExprNestedCall(pExpr->Use.Ternary.pFirst);
                          fFound |= _GenExprNestedCall(pExpr->Use.Ternary.pSecond);
                          fFound |= _GenExprNestedCall(pExpr->Use.Ternary.pThird);
                          break;
        case    uFunc:    {
                            TPExprNode  pFunc;
                            TPDeclSpec  pReturnType;
                            WORD wQualifier;
                         
                            pFunc = pExpr->Use.Func.pFunc;
                            ASSERT((pFunc != NULL) && (pFunc->pType))                                           
                            if (IsFunc(pFunc->pType)) {                                                             // normal function call
                                pReturnType = pFunc->pType->Use.DecFunc.pReturnType;
                            }
                            else if (IsPointer(pFunc->pType) && IsFunc(pFunc->pType->Use.DecPtr.pTarget)) {         // indirect function call
                                pReturnType = pFunc->pType->Use.DecPtr.pTarget->Use.DecFunc.pReturnType;
                            }
                            else {
                                pReturnType = NULL;
                                ASSERT(FALSE);
                            }
                            ASSERT(pReturnType != NULL);

                            if (pReturnType->Usage == DecSpec) { wQualifier = pReturnType->Use.DecSpec.wQual; }          //  get the return type qualifier
                            else if (pReturnType->Usage == DecPtr) { wQualifier = pReturnType->Use.DecPtr.wQual; }
                            else ASSERT(FALSE);
                            fFound |= ((wQualifier & QualNORETURN) != QualNORETURN);                                    // does it return?
                          }
                          break;
        case    uCast:    fFound |= _GenExprNestedCall(pExpr->Use.Cast.pTarget);
                          break;
        case    uAssign:  fFound |= _GenExprNestedCall(pExpr->Use.Assign.pLval);
                          fFound |= _GenExprNestedCall(pExpr->Use.Assign.pRval);
                          break;
        case    uDot:     
        case    uArrow:   
        case    uArray:   
        default:          Error(FATAL, "_GenExprNestedCall() - [%d]\n", pExpr->Usage); 
        }
        pExpr = pExpr->pSibling;
    }
    return fFound;
}

/* eof */

