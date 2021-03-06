// # $URL: https://eboracum-vss.digitallocksmiths.local/svn/Dls/Sean/RoyalHolloway/CC_Avr/Source/GenExpression.c $
// # $Revision: 391 $



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

#include "..\Utilities\dl_type.h"
#include "..\Utilities\Console.h"

//#include "lex.h"
#include "..\typectrl.h"
#include "..\expr.h"
//#include "ExprOptimize.h"
#include "gen.h"
#include "..\main.h"
//#include "C_Yacced.tab.h"
#include "GenAsm.h"
//#include "GenStatements.h"
#include "GenMemAccess.h"


// ##########################################################################
// #  Function: FetchOptions
// #        Fetch what's at the pointer experession
// #
// #
// #  Parameters:
// #    int         iReg          -  workspace
// #    TPExprNode  pExpr         - 
// #    TPMemAccess pZ            - 
// #
// #  Returns:
// #        <todo: return Value>
// #
// #  See Also:
// #
// ##########################################################################
void       FetchOptions(int iReg, TPExprNode pExpr, TPMemAccess pZ) {
    //ConsolePrintf(CON_YELLOW_BRIGHT, "FetchOptions.\n");
    //GenExpressionPrettyPrint(2, pExpr);

    pZ->bVarSize = (UCHAR)CalcSizeOf(pExpr->pType);                                                         // Size of this variable
    if ((pExpr->pType->Usage == DecArray) || (pExpr->pType->Usage == DecFunc)) {                            // Except, Arrays and pointers are addresses not their physical sizes).
        pZ->bVarSize = SIZE_PTR_DEFAULT;                                                                    //      set the pointer size
    }                                                                                                       //

    if (pExpr->Usage == uConst) {                                                                           // **** Constant indicated.
        ASSERT(pZ->bVarSize <= 4);                                                                          //
        pZ->lN = pExpr->Use.Const.lInteger;                                                                 //
        pZ->Method = ACCESS_CONST;                                                                          //
        return;                                                                                             //
    }                                                                                                       //

    if (pExpr->Usage == uIoreg) {                                                                           // **** I/O register indicated.
        ASSERT(pZ->bVarSize <= 4);                                                                          //
        pZ->lN   = pExpr->Use.Ioreg.nReg;                                                                   //
        pZ->pszS = pExpr->Use.Ioreg.pszName;                                                                //
        pZ->Method = ACCESS_IO;                                                                             //
        return;                                                                                             //
    }                                                                                                       //

    if (pExpr->Usage == uVar) {                                                                             // **** Variable
                                                                                                            //
        if ((pExpr->pType->Usage == DecArray) || (pExpr->pType->Usage == DecFunc)) {                        // named global array or function 
            pZ->bVarSize = SIZE_PTR_DEFAULT;                                                                //      set the pointer size
            pZ->pszS = pExpr->Use.Var.pszIdentifier;                                                        //      we want its address.

            if (ExprIsVarGlobal(pExpr)) {                                                                   //      &Var (global)
                pZ->lN = 0;                                                                                 //
                pZ->Method = ACCESS_GLOBAL_ADDRESS;                                                         //
                return;                                                                                     //
            }                                                                                               //
            else {                                                                                          //
                pZ->lN = pExpr->Use.Var.pDecId->Use.DecId.iOffset;                                          //      offset in Frame (local)
                pZ->Method = ACCESS_FRAME_ADDRESS;                                                          //
                return;                                                                                     //
            }                                                                                               //
        }                                                                                                   //
                                                                                                            //
        ASSERT(pZ->bVarSize <= 4);                                                                          //
        if (ExprIsVarGlobal(pExpr)) {                                                                       // Z := &Var (global)
            pZ->pszS = pExpr->Use.Var.pszIdentifier;                                                        //
            pZ->lN   = 0;                                                                                   //
            if (IsTypeQualifierConst(pExpr->pType)) {                                                       //      ROM
                pZ->Method = ACCESS_GLOBAL_ROM;                                                             //
            }                                                                                               //
            else {                                                                                          //
                pZ->Method = ACCESS_GLOBAL;                                                                 //      RAM
            }                                                                                               //
            return;                                                                                         //
        }                                                                                                   //
        else {                                                                                              // Frame variables Y + disp = Frame var
            if (pExpr->Use.Var.pDecId->Use.DecId.iOffset >= 0) {                                            //      +ve displacement = RAM @(Y+disp)
                pZ->pszS = pExpr->Use.Var.pszIdentifier;                                                    //
                pZ->lN = pExpr->Use.Var.pDecId->Use.DecId.iOffset;                                          //
                pZ->Method = ACCESS_FRAME;                                                                  //
            }                                                                                               //
            else {                                                                                          //      -ve displacement = Register (-displacment)
                pZ->pszS = pExpr->Use.Var.pszIdentifier;                                                    //
                pZ->lN = -pExpr->Use.Var.pDecId->Use.DecId.iOffset;                                         //
                pZ->Method = ACCESS_REG;                                                                    //
            }                                                                                               //
            return;                                                                                         //
        }                                                                                                   //
    }                                                                                                       //

    ASSERT(pZ->bVarSize <= 4);                                                                              //
    if ((pExpr->Usage == uUnary) && (pExpr->Use.Unary.Op == unPtr)) {                                       // *** Pointer (*, Arrays, dots & arrows)
        TPExprNode pN = pExpr->Use.Unary.pOperand;                                                          //
                                                                                                            //
        if (pN->pType->Usage == DecArray) {                                                                 // Arrays
            if (pN->Usage == uVar) {                                                                        //
                pZ->pszS = pN->Use.Var.pszIdentifier;                                                       //
                if (ExprIsVarGlobal(pN)) {                                                                  //  Global
                    pZ->lN = 0;                                                                             //
                    if (IsTypeQualifierConst(pExpr->pType)) {                                               // 
                        pZ->Method = ACCESS_GLOBAL_ROM;                                                     //
                    }                                                                                       //
                    else {                                                                                  //
                        pZ->Method = ACCESS_GLOBAL;                                                         //
                    }                                                                                       //
                    return;                                                                                 //
                }                                                                                           //
                else {                                                                                      // Local
                    pZ->lN = pN->Use.Var.pDecId->Use.DecId.iOffset;                                         //
                    pZ->Method = ACCESS_FRAME;                                                              //
                    return;                                                                                 //
                }                                                                                           //
                return;
            }
        }
   
        else if (pN->pType->Usage == DecPtr) {                                                              //  Pointer
            TPDeclSpec pTarget = pN->pType->Use.DecPtr.pTarget;                                             // type of target.

            // common to see *(+(a,const));
            if ((pN->Usage == uBinary) && (pN->Use.Binary.Op == binAdd)) {                                  // very common structure for array lookup is Add(addr,offset)
                TPExprNode pAddLeft = pN->Use.Binary.pLeft;                                                 //
                TPExprNode pAddRight = pN->Use.Binary.pRight;                                               //

                if (pAddRight->Usage == uConst) {                                                           // if the right is constant we can use displaced index 
                    int iOff = (int)pAddRight->Use.Const.lInteger;                                          //
                    if ((pAddLeft->Usage == uUnary) &&                                                      // if Left is the address of a global variable
                        (pAddLeft->Use.Unary.Op == unAddr) &&                                               //
                        (pAddLeft->Use.Unary.pOperand->Usage == uVar)) {                                    // 
                        pZ->pszS = pAddLeft->Use.Unary.pOperand->Use.Var.pszIdentifier;                     //      use its name with the provided offset.
                        if (ExprIsVarGlobal(pAddLeft->Use.Unary.pOperand)) {                                //       Global
                            pZ->lN = iOff;                                                                  //
                            if (IsTypeQualifierConst(pExpr->pType)) {                                       // 
                                pZ->Method = ACCESS_GLOBAL_ROM;                                             //
                            }                                                                               //
                            else {                                                                          //
                                pZ->Method = ACCESS_GLOBAL;                                                 //
                            }                                                                               //
                            return;                                                                         //
                        }                                                                                   //
                        else {                                                                              //       Local
                            pZ->lN = pAddLeft->Use.Unary.pOperand->Use.Var.pDecId->Use.DecId.iOffset + iOff;//
                            pZ->Method = ACCESS_FRAME;                                                      //
                            return;                                                                         //
                        }                                                                                   //
                    }

                    if (_GenCostOfCalculation(pAddLeft) < 2) {                                              // Calc the address.
                        _GenExpr(30, pAddLeft);                                                             //      if it's simple we load directly to Z
                    }                                                                                       //
                    else {                                                                                  // 
                        _GenExpr(iReg, pAddLeft);                                                           //      requires arithmetic so do it  
                        GenAsm("", "movw", OperandRegReg(30, REG_ACC0), "  1: pointer base");               //       and move it to Z
                    }                                                                                       //

                    if ((iOff < 0) || ((64 - pZ->bVarSize) < iOff) || IsTypeQualifierConst(pTarget)) {      // if the displacement will be illegal 
                        ///GenAsm("", "adiw", OperandRegImmediate(30, iOff), "  2: displaced");             //      add it to Z and 
                        GenAsm("", "subi", OperandRegImmediate(30, (u8)(-iOff)), "  1: displaced");         //      add it to Z and 
                        GenAsm("", "subi", OperandRegImmediate(31, (u8)((-iOff)>>8)), "  1:");              //
                        iOff = 0;                                                                           //      make it zero.
                    }

                    pZ->lN = iOff;                                                                          // Tell the caller what the displacement is
                    if (IsTypeQualifierConst(pExpr->pType)) {
                        pZ->Method = ACCESS_POINTER_ROM;                                                    // Also that it's a Z indexed access.
                    }
                    else {
                        pZ->Method = ACCESS_POINTER;                                                        // Also that it's a Z indexed access.
                    }
                    return;
                }
            }

            // un-optimized general case
            if (_GenCostOfCalculation(pN) < 2) {
                _GenExpr(30, pN);                                                                           // Calc descendant. gives address in ACC
            }
            else {
                _GenExpr(iReg, pN);                                                                         // Calc descendant. gives address in ACC
                GenAsm("", "movw", OperandRegReg(30, iReg), "  1: de-ref pointer");                         //
            }
            pZ->lN = 0;                                                                                     // Tell the caller what the displacement is
            if (IsTypeQualifierConst(pExpr->pType)) {                                                       //      ROM
                pZ->Method = ACCESS_POINTER_ROM;                                                            // Also that it's a Z indexed access.
            }                                                                                               //
            else {                                                                                          //
                pZ->Method = ACCESS_POINTER;                                                                // Also that it's a Z indexed access.
            }                                                                                               //
            return;                                                                                         //
        }
        
        else {
            ASSERT(0);                                                                                      //
        }
    }

    ASSERT(0); // not a const, var or pointer in need of deref.
                                                                                                            // un-optimized general case
}


LPSTR _CommentString(int iCycles, const char *pbFormat, ...);

LPSTR _CommentString(int iCycles, const char *pbFormat, ...) {
    va_list ArgList;
    int n;

    static char caMsg[1024];

    va_start(ArgList, pbFormat);
    n = _snprintf_s(caMsg,      sizeof(caMsg),   _TRUNCATE, "%3d: ", iCycles);
    n = _vsnprintf_s(&caMsg[n], sizeof(caMsg)-n, _TRUNCATE, pbFormat, ArgList);
    caMsg[sizeof(caMsg) - 1] = 0;

    return caMsg;
}


// ##########################################################################
// #  Function: FetchLoad
// #        Fetch according to the recipie from <FetchOptions>()
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
void       FetchLoad(TPMemAccess pZ, int iReg) {

    int iVarSize = (int)pZ->bVarSize;
    ASSERT(iVarSize <= 4)

    switch (pZ->Method) {
    long l;
    unsigned char b;
    LPSTR pszComment;
    case ACCESS_CONST:                                                                                                          // Constant value
        pszComment = _CommentString(1, "reg%d <== immediate #%d", (iVarSize == 1) ? 8 : (iVarSize == 2) ? 16 : 32, pZ->lN);     //
        if (pZ->lN == 0) {                                                                                                      //     #0 common special case   
            GenAsm("", "clr",  OperandReg(iReg + REG_ORDER0),                       pszComment);                                //
            if (iVarSize < 2)  return;                                                                                          //
            GenAsm("", "mov",  OperandRegReg(iReg + REG_ORDER1, iReg + REG_ORDER0), "  1:");                                    //
            if (iVarSize < 4)  return;                                                                                          //
            GenAsm("", "movw", OperandRegReg(iReg + REG_ORDER2, iReg + REG_ORDER0), "  1:");                                    //
            return;                                                                                                             //
        }                                                                                                                       //
        if (pZ->lN == -1) {                                                                                                     //     #-1 common special case   
            GenAsm("", "ldi", OperandRegImmediate(iReg + REG_ORDER0, 0xFF),         pszComment);                                //
            if (iVarSize < 2)  return;                                                                                          //
            GenAsm("", "mov", OperandRegReg(iReg + REG_ORDER1, iReg + REG_ORDER0), "  1:");                                     //
            if (iVarSize < 4)  return;                                                                                          //
            GenAsm("", "movw", OperandRegReg(iReg + REG_ORDER2, iReg + REG_ORDER0), "  1:");                                    //
            return;                                                                                                             //
        }                                                                                                                       //
                                                                                                                                //
        l = pZ->lN;                                                                                                             //      # funny/irregular number
        b = (l & 0xFF);                                                                                                         //
        GenAsm("", "ldi", OperandRegImmediate(iReg + REG_ORDER0, b),                pszComment);                                //
        if (iVarSize < 2)  return;                                                                                              //
                                                                                                                                //
        l >>= 8;                                                                                                                //
        b = (l & 0xFF);                                                                                                         //
        GenAsm("", "ldi", OperandRegImmediate(iReg + REG_ORDER1, b), "  1:");                                                   //
        if (iVarSize < 4)  return;                                                                                              //
                                                                                                                                //
        l >>= 8;                                                                                                                //
        b = (l & 0xFF);                                                                                                         //
        GenAsm("", "ldi", OperandRegImmediate(iReg + REG_ORDER2, b), "  1:");                                                   //
                                                                                                                                //
        l >>= 8;                                                                                                                //
        b = (l & 0xFF);                                                                                                         //
        GenAsm("", "ldi", OperandRegImmediate(iReg + REG_ORDER3, b), "  1:");                                                   //
        return;                                                                                                                 //

    case ACCESS_IO:
        pszComment = _CommentString(1, "I/O fetch %s", pZ->pszS);                                                               //
        GenAsm("", "in", OperandRegImmediate(iReg + REG_ORDER0, (UCHAR)pZ->lN), pszComment);                                    //
        return;                                                                                                                 //

    case ACCESS_GLOBAL:                                                                                                         // Global symbol normal (RAM/Data access)
        pszComment = _CommentString(1, "reg%d <== Global %s[%d]", (iVarSize == 1) ? 8 : (iVarSize == 2) ? 16 : 32, pZ->pszS, pZ->lN);//
        if (pZ->lN == 0) {                                                                                                      //
            GenAsm("", "lds", OperandRegStr(iReg + REG_ORDER0, pZ->pszS), pszComment);                                          //
        }                                                                                                                       //
        else {                                                                                                                  //
            GenAsm("", "lds", OperandRegStrDisp(iReg + REG_ORDER0, pZ->pszS, pZ->lN), pszComment);                              //
        }                                                                                                                       //
        if (iVarSize < 2) return;                                                                                               //
        GenAsm("", "lds", OperandRegStrDisp(iReg + REG_ORDER1, pZ->pszS, pZ->lN + 1), "  1:");                                  //
        if (iVarSize < 4) return;                                                                                               //
        GenAsm("", "lds", OperandRegStrDisp(iReg + REG_ORDER2, pZ->pszS, pZ->lN + 2), "  1:");                                  //
        GenAsm("", "lds", OperandRegStrDisp(iReg + REG_ORDER3, pZ->pszS, pZ->lN + 3), "  1:");                                  //
        return;                                                                                                                 //

    case ACCESS_GLOBAL_ROM:                                                                                                     //  global symbol but in ROM memory
        pszComment = _CommentString(1, "reg%d <== ROM Global %s[%d]", (iVarSize == 1) ? 8 : (iVarSize == 2) ? 16 : 32, pZ->pszS, pZ->lN);//
        GenAsm("", "ldi", OperandRegVar(30, pZ->pszS),            pszComment);                                                  // 
        GenAsm("", "ldi", OperandRegVar(31, pZ->pszS),            "  1:");                                                      //
        if (pZ->lN != 0) {                                                                                                      //
            GenAsm("", "adiw", OperandRegImmediate(30, (UCHAR)pZ->lN), "  2:");                                                 //
        }                                                                                                                       //
        GenAsm("", "lpm", OperandRegStr(iReg + REG_ORDER0, "Z+"), "  3:");                                                      //
        if (iVarSize < 2) return;                                                                                               //
        GenAsm("", "lpm", OperandRegStr(iReg + REG_ORDER1, "Z+"), "  3:");                                                      //
        if (iVarSize < 4) return;                                                                                               //
        GenAsm("", "lpm", OperandRegStr(iReg + REG_ORDER2, "Z+"), "  3:");                                                      //
        GenAsm("", "lpm", OperandRegStr(iReg + REG_ORDER3, "Z"),  "  3:");                                                      //
        return;                                                                                                                 //

    case ACCESS_GLOBAL_ADDRESS:                                                                                                 // Address of a global symbol.
        ASSERT(iVarSize == 2);                                                                                                  //
        pszComment = _CommentString(1, "reg16 <== Address of Global %s", pZ->pszS);                                             //
        GenAsm("", "ldi", OperandRegVar(iReg + REG_ORDER0, pZ->pszS), pszComment);                                              // 
        GenAsm("", "ldi", OperandRegVar(iReg + REG_ORDER1, pZ->pszS), "  1:");                                                  //
        return;                                                                                                                 //

    case ACCESS_FRAME:                                                                                                          // local or parameter variable. (offset y)
        pszComment = _CommentString(1, "reg%d <== Local %s @Frame:%d", (iVarSize == 1) ? 8 : (iVarSize == 2) ? 16 : 32, pZ->pszS, pZ->lN);//
        if (pZ->lN == 0) {                                                                                                      //
            GenAsm("", "ld", OperandRegStr(iReg + REG_ORDER0, "Y"), pszComment);                                                //
        }                                                                                                                       //
        else {                                                                                                                  //
            GenAsm("", "ldd", OperandRegDisp(iReg + REG_ORDER0, "Y", pZ->lN), pszComment);                                      //
        }                                                                                                                       //
        if (iVarSize < 2) return;                                                                                               //
        GenAsm("", "ldd", OperandRegDisp(iReg + REG_ORDER1, "Y", pZ->lN + 1), "  2:");                                          //
        if (iVarSize < 4) return;                                                                                               //
        GenAsm("", "ldd", OperandRegDisp(iReg + REG_ORDER2, "Y", pZ->lN + 2), "  2:");                                          //
        GenAsm("", "ldd", OperandRegDisp(iReg + REG_ORDER3, "Y", pZ->lN + 3), "  2:");                                          //
        return;
    
    case ACCESS_FRAME_ADDRESS:                                                                                                  // Address of a local symbol.
        ASSERT(iVarSize == 2);                                                                                                  //
        pszComment = _CommentString(1, "reg16 <== Address of Local %s", pZ->pszS);                                              //
        GenAsm("", "movw", OperandRegReg(iReg + REG_ORDER0, 28), pszComment);                                                   // 
        GenAsm("", "adiw", OperandRegImmediate(iReg + REG_ORDER0, (UCHAR)pZ->lN), "  2:");                                      //
        return;

    case ACCESS_POINTER:                                                                                                        // A pointer has been collected into Z ready to be de-referenced. (offset Z)
        if (pZ->lN == 0) {                                                                                                      //
            pszComment = _CommentString(1, "reg%d <== Indirect from RAM", (iVarSize == 1) ? 8 : (iVarSize == 2) ? 16 : 32);     //
            GenAsm("", "ld", OperandRegStr(iReg + REG_ORDER0, "Z"), pszComment);                                                //
        }                                                                                                                       //
        else {                                                                                                                  //
            pszComment = _CommentString(2, "reg%d <== Indirect from RAM", (iVarSize == 1) ? 8 : (iVarSize == 2) ? 16 : 32);     //
            GenAsm("", "ldd", OperandRegDisp(iReg + REG_ORDER0, "Z", pZ->lN), pszComment);                                      //
        }                                                                                                                       //
        if (iVarSize < 2) return;                                                                                               //
        GenAsm("", "ldd", OperandRegDisp(iReg + REG_ORDER1, "Z", pZ->lN + 1), "  2:");                                          //
        if (iVarSize < 4) return;                                                                                               //
        GenAsm("", "ldd", OperandRegDisp(iReg + REG_ORDER2, "Z", pZ->lN + 2), "  2:");                                          //
        GenAsm("", "ldd", OperandRegDisp(iReg + REG_ORDER3, "Z", pZ->lN + 3), "  2:");                                          //
        return;

    case ACCESS_POINTER_ROM:                                                                                                    //   A pointer has been collected into Z ready to be de-referenced but it's in ROM memory.
        ASSERT(pZ->lN == 0);                                                                                                    //
        pszComment = _CommentString(3, "reg%d <== Indirect from ROM", (iVarSize == 1) ? 8 : (iVarSize == 2) ? 16 : 32);         //
        GenAsm("", "lpm", OperandRegStr(iReg + REG_ORDER0, "Z+"), pszComment);                                                  //
        if (iVarSize < 2) return;                                                                                               //
        GenAsm("", "lpm", OperandRegStr(iReg + REG_ORDER1, "Z+"), "  3:");                                                      //
        if (iVarSize < 4) return;                                                                                               //
        GenAsm("", "lpm", OperandRegStr(iReg + REG_ORDER1, "Z+"), "  3:");                                                      //
        GenAsm("", "lpm", OperandRegStr(iReg + REG_ORDER1, "Z+"), "  3:");                                                      //
        return;
    
    case ACCESS_REG:                                                                                                            //  Register   
        ASSERT(iVarSize <= 4);                                                                                                  //
        pszComment = _CommentString(1, "reg%d <== register variable %s", (iVarSize == 1)?8:(iVarSize == 2)?16:32, pZ->pszS);    //
        switch (iVarSize) {                                                                                                     //
        case 1:                                                                                                                 //
            GenAsm("", "mov",  OperandRegReg(iReg + REG_ORDER0, pZ->lN), pszComment);                                           //
            return;                                                                                                             //
        case 2:                                                                                                                 //
            GenAsm("", "movw", OperandRegReg(iReg + REG_ORDER0, pZ->lN), pszComment);                                           //
            return;                                                                                                             //
        case 4:                                                                                                                 //
            GenAsm("", "movw", OperandRegReg(iReg + REG_ORDER0, pZ->lN),   pszComment);                                         //
            GenAsm("", "movw", OperandRegReg(iReg + REG_ORDER2, pZ->lN+2), "");                                                 //
            return;                                                                                                             //
        }

    default:
        ASSERT(0);
    }
}

// ##########################################################################
// #  Function: FetchStore
// #        Fetch according to the recipie from <FetchOptions>()
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
void       FetchStore(TPMemAccess pZ, int iReg) {

    int iVarSize = (int)pZ->bVarSize;
    LPSTR pszComment;
    
    ASSERT(iVarSize <= 4)

    switch (pZ->Method) {                                                                                                       // Write back

    case ACCESS_GLOBAL:                                                                                                         // Global symbol normal (RAM/Data access)
        if (pZ->lN == 0) {                                                                                                      //
            GenAsm("", "sts", OperandStrReg(pZ->pszS, iReg + REG_ORDER0), CommentString(1, pZ->pszS, " <== reg "));             //
        }                                                                                                                       //
        else {                                                                                                                  //
            GenAsm("", "sts", OperandStrDispReg(pZ->pszS, pZ->lN, iReg + REG_ORDER0), CommentString(1, pZ->pszS, " <== reg ")); //
        }                                                                                                                       //
        if (iVarSize < 2) break;                                                                                                //
        GenAsm("", "sts", OperandStrDispReg(pZ->pszS, pZ->lN + 1, iReg + REG_ORDER1), "  1:");                                  //
        if (iVarSize < 4) break;                                                                                                //
        GenAsm("", "sts", OperandStrDispReg(pZ->pszS, pZ->lN + 2, iReg + REG_ORDER2), "  1:");                                  //
        GenAsm("", "sts", OperandStrDispReg(pZ->pszS, pZ->lN + 3, iReg + REG_ORDER3), "  1:");                                  //
        break;

    case ACCESS_FRAME:                                                                                                          // local or parameter variable. (offset y)
        if (pZ->lN == 0) {                                                                                                      //
            GenAsm("", "st", OperandStrReg("Y", iReg + REG_ORDER0), CommentString(1, "local <== reg ", pZ->pszS));             //
        }                                                                                                                       //
        else {                                                                                                                  //
            GenAsm("", "std", OperandDispReg("Y", pZ->lN, iReg + REG_ORDER0), CommentString(2, "local <== reg ", pZ->pszS));   //
        }                                                                                                                       //
        if (iVarSize < 2) break;                                                                                                //
        GenAsm("", "std", OperandDispReg("Y", pZ->lN + 1, iReg + REG_ORDER1), "  2:");                                          //
        if (iVarSize < 4) break;                                                                                                //
        GenAsm("", "std", OperandDispReg("Y", pZ->lN + 2, iReg + REG_ORDER2), "  2:");                                          //
        GenAsm("", "std", OperandDispReg("Y", pZ->lN + 3, iReg + REG_ORDER3), "  2:");                                          //
        break;

    case ACCESS_POINTER:                                                                                                        // A pointer has been collected into Z ready to be de-referenced. (offset Z)
        if (pZ->lN == 0) {                                                                                                      //
            GenAsm("", "st", OperandStrReg("Z", iReg + REG_ORDER0), "  1: @Z <== reg");                                         //
        }                                                                                                                       //
        else {                                                                                                                  //
            GenAsm("", "std", OperandDispReg("Z", pZ->lN, iReg + REG_ORDER0), "  2: @Z <== reg");                               //
        }                                                                                                                       //
        if (iVarSize < 2) break;                                                                                                //
        GenAsm("", "std", OperandDispReg("Z", pZ->lN + 1, iReg + REG_ORDER1), "  2:");                                          //
        if (iVarSize < 4) break;                                                                                                //
        GenAsm("", "std", OperandDispReg("Z", pZ->lN + 2, iReg + REG_ORDER2), "  2:");                                          //
        GenAsm("", "std", OperandDispReg("Z", pZ->lN + 3, iReg + REG_ORDER3), "  2:");                                          //
        break;

    case ACCESS_REG:                                                                                                            //  Register   
        ASSERT(iVarSize <= 4);                                                                                                  //
        pszComment = _CommentString(1, "register variable %s <== reg%d", pZ->pszS, (iVarSize == 1)?8:(iVarSize == 2)?16:32);    //
        switch (iVarSize) {                                                                                                     //
        case 1:                                                                                                                 //
            GenAsm("", "mov", OperandRegReg(pZ->lN, iReg + REG_ORDER0), pszComment);                                            //
            return;                                                                                                             //
        case 2:                                                                                                                 //
            GenAsm("", "movw", OperandRegReg(pZ->lN, iReg + REG_ORDER0), pszComment);                                           //
            return;                                                                                                             //
        case 4:                                                                                                                 //
            GenAsm("", "movw", OperandRegReg(pZ->lN, iReg + REG_ORDER0), pszComment);                                           //
            GenAsm("", "movw", OperandRegReg(pZ->lN + 2, iReg + REG_ORDER2), "");                                               //
            return;                                                                                                             //
        }

    case ACCESS_IO:                      //  [NS]  Special Function register
        pszComment = _CommentString(1, "I/O store %s", pZ->pszS);                                                               //
        GenAsm("", "out", OperandImmediateReg((UCHAR)pZ->lN, iReg + REG_ORDER0), pszComment);                                   //
        return;                                                                                                                 //

    case ACCESS_CONST:                                                                                                          // Constant value
    case ACCESS_GLOBAL_ROM:              //  [NS]  global symbol but in ROM memory
    case ACCESS_POINTER_ROM:             //  [NS]  A pointer has been collected into Z ready to be de-referenced but it's in ROM memory.

    default:
        ASSERT(0);
    }
}


/* eof */

