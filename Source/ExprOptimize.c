// # $URL: https://eboracum-vss.digitallocksmiths.local/svn/Dls/Sean/RoyalHolloway/CC_Avr/Source/ExprOptimize.c $
// # $Revision: 426 $


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
#include "Utilities\Console.h"

#include "lex.h"
#include "typectrl.h"
#include "expr.h"
//#include "GenAvr\gen.h"
#include "main.h"
#include "C_Yacced.tab.h"

#include "ExprOptimize.h"


// Deliberate NON-optimizations
//  1. var | var => var         // Repeated use of a variable name will cause repeated reads. 
//                              // Thus if the program reads something and checks it it will 
//                              // check the source value not a copy of the previously read value.
//                              // exception: a & 0 ==>0 where the result is predetermined all 
//                              // reads may be bypassed.


#pragma message("    **** Use of the BOOL fRoot parameter is not fully exploited here")
// The common case of post inc/dec uses the feature.

static TPExprNode OptimizeBinary(int iDepth, TPExprNode pN, BOOL fRoot);    // forward
static TPExprNode Optimize(int iDepth, TPExprNode pN, BOOL fRoot);          // forward decl

// ##########################################################################################################

// ##########################################################################
// #  Function: OptimizeUnaryMinus
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
static TPExprNode OptimizeUnaryMinus(int iDepth, TPExprNode pN, BOOL fRoot) {
        ASSERT(pN->Usage == uUnary);
        ASSERT(pN->Use.Unary.Op == unMinus);

        TPExprNode pSubNode = pN->Use.Unary.pOperand;

        if (pSubNode->Usage == uConst) {
            switch (CalcSizeOf(pSubNode->pType)) {
            case 1: pSubNode->Use.Const.lInteger = (long)(-(char)pSubNode->Use.Const.lInteger); break;
            case 2: pSubNode->Use.Const.lInteger = (long)(-(short)pSubNode->Use.Const.lInteger); break;
            case 4: pSubNode->Use.Const.lInteger = (long)(-(long)pSubNode->Use.Const.lInteger); break;
            default:
                Error(FATAL, "OptimizeUnaryMinus(): Whisky Tango Foxtrot");
            }
            pSubNode->pType = pN->pType;
            return pSubNode;
        }

        return pN;
}

// ##########################################################################
// #  Function: OptimizeUnaryPlus
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
static TPExprNode OptimizeUnaryPlus(int iDepth, TPExprNode pN, BOOL fRoot) {
        ASSERT(pN->Usage == uUnary);
        ASSERT(pN->Use.Unary.Op == unPlus);

        TPExprNode pSubNode = pN->Use.Unary.pOperand;

        if (pSubNode->Usage == uConst) {
            switch (CalcSizeOf(pSubNode->pType)) {
            case 1: pSubNode->Use.Const.lInteger = (long)((char)pSubNode->Use.Const.lInteger); break;
            case 2: pSubNode->Use.Const.lInteger = (long)((short)pSubNode->Use.Const.lInteger); break;
            case 4: pSubNode->Use.Const.lInteger = (long)((long)pSubNode->Use.Const.lInteger); break;
            default:
                Error(FATAL, "OptimizeUnaryPlus(): Whisky Tango Foxtrot");
            }
            pSubNode->pType = pN->pType;
            return pSubNode;
        }

        return pN;
}

// ##########################################################################
// #  Function: OptimizeUnaryNeg
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
static TPExprNode OptimizeUnaryNeg(int iDepth, TPExprNode pN, BOOL fRoot) {
        ASSERT(pN->Usage == uUnary);
        ASSERT(pN->Use.Unary.Op == unNeg);

        TPExprNode pSubNode = pN->Use.Unary.pOperand;

        if (pSubNode->Usage == uConst) {
            switch (CalcSizeOf(pSubNode->pType)) {
            case 1: pSubNode->Use.Const.lInteger = (long)(~(char)pSubNode->Use.Const.lInteger); break;
            case 2: pSubNode->Use.Const.lInteger = (long)(~(short)pSubNode->Use.Const.lInteger); break;
            case 4: pSubNode->Use.Const.lInteger = (long)(~(long)pSubNode->Use.Const.lInteger); break;
            default:
                Error(FATAL, "OptimizeUnaryNeg(): Whisky Tango Foxtrot");
            }
            pSubNode->pType = pN->pType;
            return pSubNode;
        }

        return pN;
}

// ##########################################################################
// #  Function: OptimizeUnaryPostInc
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
static TPExprNode OptimizeUnaryPostInc(int iDepth, TPExprNode pN, BOOL fRoot) {
        ASSERT(pN->Usage == uUnary);
        ASSERT(pN->Use.Unary.Op == unPostInc);

        if (fRoot == TRUE) {                                                    // if the caller does not want this result
            pN->Use.Unary.Op = unPreInc;                                        //      doing a pre-inc instead is better.
        }                                                                       //

        // Nothing else to do here.
        return pN;
}

// ##########################################################################
// #  Function: OptimizeUnaryPreInc
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
static TPExprNode OptimizeUnaryPreInc(int iDepth, TPExprNode pN, BOOL fRoot) {
        ASSERT(pN->Usage == uUnary);
        ASSERT(pN->Use.Unary.Op == unPreInc);

        // Nothing to do here.
        return pN;
}

// ##########################################################################
// #  Function: OptimizeUnaryPostDec
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
static TPExprNode OptimizeUnaryPostDec(int iDepth, TPExprNode pN, BOOL fRoot) {
        ASSERT(pN->Usage == uUnary);
        ASSERT(pN->Use.Unary.Op == unPostDec);
        
        if (fRoot == TRUE) {                                                    // if the caller does not want this result
            pN->Use.Unary.Op = unPreDec;                                        //      doing a pre-inc instead is better.
        }                                                                       //

        // Nothing else to do here.
        return pN;
}

// ##########################################################################
// #  Function: OptimizeUnaryPreDec
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
static TPExprNode OptimizeUnaryPreDec(int iDepth, TPExprNode pN, BOOL fRoot) {
        ASSERT(pN->Usage == uUnary);
        ASSERT(pN->Use.Unary.Op == unPreDec);
        
        // Nothing to do here.
        return pN;
}

// ##########################################################################
// #  Function: OptimizeUnarySizeOf
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
static TPExprNode OptimizeUnarySizeOf(int iDepth, TPExprNode pN, BOOL fRoot) {
        ASSERT(pN->Usage == uUnary);
        ASSERT(pN->Use.Unary.Op == unSizeOf);

        Error(FATAL, "OptimizeUnarySizeOf(): this should not exist!");
        return pN;
}

// ##########################################################################
// #  Function: OptimizeUnaryAddr
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
static TPExprNode OptimizeUnaryAddr(int iDepth, TPExprNode pN, BOOL fRoot) {
        ASSERT(pN->Usage == uUnary);
        ASSERT(pN->Use.Unary.Op == unAddr);
 
        // Nothing to do here.
        return pN;
}

// ##########################################################################
// #  Function: OptimizeUnaryPtr
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
static TPExprNode OptimizeUnaryPtr(int iDepth, TPExprNode pN, BOOL fRoot) {
        ASSERT(pN->Usage == uUnary);
        ASSERT(pN->Use.Unary.Op == unPtr);
        
        TPExprNode pSubNode = pN->Use.Unary.pOperand;

        if (pSubNode->Usage == uUnary && pSubNode->Use.Unary.Op == unAddr) {
            pSubNode->Use.Unary.pOperand->pType = pN->pType;
            return pSubNode->Use.Unary.pOperand;
        }

        return pN;
}

// ##########################################################################
// #  Function: OptimizeUnaryNot
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
static TPExprNode OptimizeUnaryNot(int iDepth, TPExprNode pN, BOOL fRoot) {
        ASSERT(pN->Usage == uUnary);
        ASSERT(pN->Use.Unary.Op == unNot);
        
        TPExprNode pSubNode = pN->Use.Unary.pOperand;

        if (pSubNode->Usage == uConst) {                        
            if (pSubNode->Use.Const.lInteger != 0) {
                pSubNode->Use.Const.lInteger = FALSE;
            }
            else {
                pSubNode->Use.Const.lInteger = TRUE;
            }
            pSubNode->pType = pN->pType;
            return pSubNode;
        }

        return pN;
}

// ##########################################################################
// #  Function: OptimizeUnary
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
static TPExprNode OptimizeUnary(int iDepth, TPExprNode pN, BOOL fRoot) {
    ASSERT(pN->Usage == uUnary);

    pN->Use.Unary.pOperand = Optimize(iDepth+1, pN->Use.Unary.pOperand, FALSE);

    switch (pN->Use.Unary.Op) {
    case unMinus:     return OptimizeUnaryMinus(iDepth, pN, fRoot);
    case unPlus:      return OptimizeUnaryPlus(iDepth, pN, fRoot);
    case unNeg:       return OptimizeUnaryNeg(iDepth, pN, fRoot);
    case unPostInc:   return OptimizeUnaryPostInc(iDepth, pN, fRoot);
    case unPreInc:    return OptimizeUnaryPreInc(iDepth, pN, fRoot);
    case unPostDec:   return OptimizeUnaryPostDec(iDepth, pN, fRoot);
    case unPreDec:    return OptimizeUnaryPreDec(iDepth, pN, fRoot);
    case unSizeOf:    return OptimizeUnarySizeOf(iDepth, pN, fRoot);
    case unAddr:      return OptimizeUnaryAddr(iDepth, pN, fRoot);
    case unPtr:       return OptimizeUnaryPtr(iDepth, pN, fRoot);
    case unNot:       return OptimizeUnaryNot(iDepth, pN, fRoot);
    default:
        Error(FATAL, "OptimizeUnary(): What [%d]\n", pN->Use.Unary.Op);
    }
    return pN;
}


// ##########################################################################################################

// ##########################################################################
// #  Function: OptimizeBinaryAdd
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
static TPExprNode OptimizeBinaryAdd(int iDepth, TPExprNode pN, BOOL fRoot) {
        ASSERT(pN->Usage == uBinary);
        ASSERT(pN->Use.Binary.Op == binAdd);

#define NodeIsBinary(N, Q)  ((N->Usage == uBinary) && (N->Use.Binary.Op == (Q)))
#define NodeIsConst(N)      (N->Usage == uConst)

        TPExprNode pLeft = pN->Use.Binary.pLeft;
        TPExprNode pRight = pN->Use.Binary.pRight;

        // Addition is commutative and constants on the right gives better assembler output.
        if (NodeIsConst(pLeft)) {                                                                   // left const
            pN->Use.Binary.pLeft  = pRight;                                                         // (C + x) ==> (x + C)
            pN->Use.Binary.pRight = pLeft;                                                          //
            pLeft = pN->Use.Binary.pLeft;                                                           //
            pRight = pN->Use.Binary.pRight;                                                         //
        }                                                                                           //

        if (NodeIsConst(pLeft)) {                                                                   // Left const after the earlier swap
            pN->Usage = uConst;                                                                     //      Left Const & Right Const
            pN->Use.Const.lInteger = pLeft->Use.Const.lInteger + pRight->Use.Const.lInteger;        //      (c + c) ==> c
            return pN;                                                                              //      
        }                                                                                           //

        if (NodeIsConst(pRight)) {                                                                  // Right const
            if (pRight->Use.Const.lInteger == 0) {                                                  //      Right is const zero
                pLeft->pType = pN->pType;                                                           //      (v + 0) ==> v
                return pLeft;                                                                       //
            }                                                                                       //
            if (NodeIsBinary(pLeft, binAdd)) {                                                      //      left is addition
                TPExprNode pSubLeft = pLeft->Use.Binary.pLeft;                                      //
                TPExprNode pSubRight = pLeft->Use.Binary.pRight;                                    //
                if (pSubRight->Usage == uConst) {                                                   //
                    //no need to check left = const                                                 //
                     pRight->Use.Const.lInteger += pSubRight->Use.Const.lInteger;                   //     (v +  c) + c ==> v + c
                    pN->Use.Binary.pLeft = pSubLeft;                                                //
                    return OptimizeBinary(iDepth, pN,FALSE);                                                      //
                }                                                                                   //
            }                                                                                       //
            return pN;                                                                              //
        }                                                                                           //

        if (NodeIsBinary(pRight, binAdd)) {                                                         // Right is binary addition
//          pN->Use.Binary.pRight = pRight->Use.Binary.pLeft;                                       // x + (y + z) ==> (x+y)+z
//          pRight->Use.Binary.pLeft = pN;
//          return OptimizeBinary(iDepth, pRight,FALSE);

#pragma message ("    **** OptimizeBinaryAdd(): Strict type managment here. duplicate in other optimization routines. ASAP")
            TPExprNode pN1 = pN;
            TPExprNode pN2 = pRight;

            TPExprNode x = pLeft;
            TPExprNode y = pRight->Use.Binary.pLeft;
            TPExprNode z = pRight->Use.Binary.pRight;

            pN2->Use.Binary.pLeft = x;
            pN2->Use.Binary.pRight = y;
            pN2->pType = ExprResultingType(x->pType, y->pType);
            
            pN1->Use.Binary.pLeft = OptimizeBinary(iDepth, pN2, FALSE);
            pN1->Use.Binary.pRight = z;
            pN1->pType = ExprResultingType(pN1->Use.Binary.pLeft->pType, pN1->Use.Binary.pRight->pType);

            return pN1;
        }


        if ((NodeIsBinary(pLeft, binAdd)) &&                                                        // (x+C)+y      ==> (x+y)+C  
            (pLeft->Use.Binary.pRight->Usage == uConst)) {
            TPExprNode pTmp = pLeft->Use.Binary.pRight;
            pLeft->Use.Binary.pRight = pN->Use.Binary.pRight;
            pN->Use.Binary.pRight = pTmp;
            return OptimizeBinary(iDepth, pN,FALSE);

        }

        
        return pN;
}

// ##########################################################################
// #  Function: OptimizeBinarySub
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
static TPExprNode OptimizeBinarySub(int iDepth, TPExprNode pN, BOOL fRoot) {
        ASSERT(pN->Usage == uBinary);
        ASSERT(pN->Use.Binary.Op == binSub);

        TPExprNode pLeft = pN->Use.Binary.pLeft;
        TPExprNode pRight = pN->Use.Binary.pRight;

        if (pLeft->Usage == uConst) {                                                               // left const
            if (pRight->Usage == uConst) {                                                          //      
                pN->Usage = uConst;                                                                 // Left Const & Right Const
                pN->Use.Const.lInteger = pLeft->Use.Const.lInteger - pRight->Use.Const.lInteger;    //      do the maths and return new const.
                return pN;                                                                          //
            }
            if (pRight->Usage == uBinary) {
                TPExprNode pSubLeft = pRight->Use.Binary.pLeft;
                TPExprNode pSubRight = pRight->Use.Binary.pRight;
                if (pRight->Use.Binary.Op == binSub) {
                    if (pSubLeft->Usage == uConst) {                                                //     c - ( c - v) ==> c - v
                        pLeft->Use.Const.lInteger -= pSubLeft->Use.Const.lInteger;
                        pN->Use.Binary.pRight = pSubRight;
                        return pN;
                    }
                    if (pSubRight->Usage == uConst) {                                               //     c - ( v - c) ==> c - v
                        pLeft->Use.Const.lInteger -= pSubRight->Use.Const.lInteger;
                        pN->Use.Binary.pRight = pSubLeft;
                        return pN;
                    }
                }
            }
            return pN;
        }
        if (pRight->Usage == uConst) {                                                              // Right const
            if (pRight->Use.Const.lInteger == 0) {                                                  //      Right is const zero
                pLeft->pType = pN->pType;
                return pLeft;                                                                       //      (v - 0) ==> v
            }                                                                                       //
            if (pLeft->Usage == uBinary) {
                TPExprNode pSubLeft = pLeft->Use.Binary.pLeft;
                TPExprNode pSubRight = pLeft->Use.Binary.pRight;
                if (pLeft->Use.Binary.Op == binSub) {
                    if (pSubLeft->Usage == uConst) {                                                //     (c - v) - c ==> c - v
                        pSubLeft->Use.Const.lInteger -= pRight->Use.Const.lInteger;
                        pLeft->pType = pN->pType; 
                        return pLeft;
                    }
                    if (pSubRight->Usage == uConst) {                                               //     (v -  c) - c ==> v - c
                        pSubRight->Use.Const.lInteger += pRight->Use.Const.lInteger;
                        pLeft->pType = pN->pType; 
                        return pLeft;
                    }
                }
            }
            return pN;
        }
        
        return pN;
}

// ##########################################################################
// #  Function: OptimizeBinaryMul
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
static TPExprNode OptimizeBinaryMul(int iDepth, TPExprNode pN, BOOL fRoot) {
        ASSERT(pN->Usage == uBinary);
        ASSERT(pN->Use.Binary.Op == binMul);

        TPExprNode pLeft = pN->Use.Binary.pLeft;
        TPExprNode pRight = pN->Use.Binary.pRight;

        // Multiplication is commutative and constants on the right gives better assembler output.
        if (pLeft->Usage == uConst) {                                                               // left const
            pN->Use.Binary.pLeft = pRight;                                                          //
            pRight = pN->Use.Binary.pRight = pLeft;                                                 //
            pLeft = pN->Use.Binary.pLeft;                                                           //
            pRight = pN->Use.Binary.pRight;                                                         //
        }                                                                                           //

        if (pLeft->Usage == uConst) {                                                               // Left const
            pN->Usage = uConst;                                                                     //      Left Const & Right Const
            pN->Use.Const.lInteger = pLeft->Use.Const.lInteger * pRight->Use.Const.lInteger;        //      (c + c) ==> c
            return pN;                                                                              //      
        }                                                                                           //

        if (pRight->Usage == uConst) {                                                              // Right const
            if (pRight->Use.Const.lInteger == 0) {                                                  //      Right is const zero
                pRight->pType = pN->pType;                                                          //
                return pRight;                                                                      //      (v * 0) ==> 0
            }                                                                                       
            if (pRight->Use.Const.lInteger == 1) {                                                  //      Right is const one
                pLeft->pType = pN->pType;                                                           //
                return pLeft;                                                                       //      (v * 1) ==> v
            }                                                                                       
            // if (pRight->Use.Const.lInteger == 2) {                                               //      Right is const two
            //     pN->Use.Binary.pRight = pN->Use.Binary.pLeft;                                    //      (v * 2) ==> v + v
            //     pN->Use.Binary.Op = binAdd;                                                      //
            //     return pN;                                                                       //
            // }                                                                                       
            //if ((pLeft->Usage == uBinary) &&                                                      //
            //    (pLeft->Use.Binary.Op == binMul)) {                                               //      left is multiplication
            //    TPExprNode pSubLeft = pLeft->Use.Binary.pLeft;                                    //
            //    TPExprNode pSubRight = pLeft->Use.Binary.pRight;                                  //
            //    if (pSubRight->Usage == uConst) {                                                 //
            //                                                                                      //no need to check left = const                                                 //
            //        pRight->Use.Const.lInteger *= pSubRight->Use.Const.lInteger;                  //     (v *  c) + c ==> v + c
            //        pN->Use.Binary.pLeft = pSubLeft;                                              //
            //        return OptimizeBinary(iDepth, pN, FALSE);                                     //
            //    }                                                                                 //
            //}                                                                                     //
            return pN;                                                                              //
        }                                                                                           //

        if ((pRight->Usage == uBinary) &&                                                           // Right is binary multiplication with a constant
            (pRight->Use.Binary.Op == binMul) &&                                                    //
            (pRight->Use.Binary.pRight->Usage == uConst) &&                                         //
            (pLeft->Usage == uBinary) &&                                                            // so is left.
            (pLeft->Use.Binary.Op == binMul) &&                                                     //
            (pRight->Use.Binary.pRight->Usage == uConst)) {                                         // (v+c)+(v+c) ==> (v+v)+c

            pRight->Use.Binary.pRight->Use.Const.lInteger *= pLeft->Use.Binary.pRight->Use.Const.lInteger;
            pLeft->Use.Binary.pRight = pRight->Use.Binary.pLeft;
            pN->Use.Binary.pRight = pRight->Use.Binary.pRight;
            return OptimizeBinary(iDepth, pN, FALSE);
        }

        return pN;
}

// ##########################################################################
// #  Function: OptimizeBinaryDiv
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
static TPExprNode OptimizeBinaryDiv(int iDepth, TPExprNode pN, BOOL fRoot) {
        ASSERT(pN->Usage == uBinary);
        ASSERT(pN->Use.Binary.Op == binDiv);

        TPExprNode pLeft = pN->Use.Binary.pLeft;
        TPExprNode pRight = pN->Use.Binary.pRight;

        if (pRight->Usage == uConst) {
            if (pRight->Use.Const.lInteger == 0) {                                                                  // division by zero
                Error(WARNINGX, "OptimizeBinaryDiv() detected division by zero (Substituted -1 for the result");    //
                pLeft->Use.Const.lInteger = -1;                                                                     //
                pLeft->pType = pN->pType;                                                                           //
                return pLeft;                                                                                       //
            }
            if (pRight->Use.Const.lInteger == 1) {                                                                  // division by one
                pLeft->pType = pN->pType;                                                                           //
                return pLeft;                                                                                       //
            }
            if (pLeft->Usage == uConst) {                                                                           // left & right const
                pLeft->Use.Const.lInteger /= pRight->Use.Const.lInteger;                                            //      (c / c) ==> c
                pLeft->pType = pN->pType;                                                                           //
                return pLeft;                                                                                       //      
            }
        }
        // Do not optimize beyond this binary pair.
        // integral division yields different results when the order changes.
        // a / 3 / 2 == (a/3)/2 != a/(3/2).
        return pN;
}

// ##########################################################################
// #  Function: OptimizeBinaryMod
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
static TPExprNode OptimizeBinaryMod(int iDepth, TPExprNode pN, BOOL fRoot) {
        ASSERT(pN->Usage == uBinary);
        ASSERT(pN->Use.Binary.Op == binMod);

        TPExprNode pLeft = pN->Use.Binary.pLeft;
        TPExprNode pRight = pN->Use.Binary.pRight;

        if (pRight->Usage == uConst) {
            if (pRight->Use.Const.lInteger == 0) {                                                                  // division by zero
                Error(WARNINGX, "OptimizeBinaryMod() detected division by zero (Substituted 0 for the result");     //
                pLeft->Use.Const.lInteger = 0;                                                                      //
                pLeft->pType = pN->pType;                                                                           //
                return pLeft;                                                                                       //
            }
            if (pRight->Use.Const.lInteger == 1) {                                                                  // x / 1 ==>  x rem 0
                pLeft->Use.Const.lInteger = 0;                                                                      //
                pLeft->pType = pN->pType;                                                                           //
                return pLeft;                                                                                       //
            }
            if (pLeft->Usage == uConst) {                                                                           // left & right const
                pLeft->Use.Const.lInteger %= pRight->Use.Const.lInteger;                                            //      (c % c) ==> c
                pLeft->pType = pN->pType;                                                                           //
                return pLeft;                                                                                       //      
            }
        }
        // Do not optimize beyond this binary pair.
        // integral division yields different results when the order changes.
        // a / 3 / 2 == (a/3)/2 != a/(3/2).
        return pN;
}

// ##########################################################################
// #  Function: OptimizeBinaryBAnd
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
static TPExprNode OptimizeBinaryBAnd(int iDepth, TPExprNode pN, BOOL fRoot) {
        ASSERT(pN->Usage == uBinary);
        ASSERT(pN->Use.Binary.Op == binAnd);
        
        TPExprNode pLeft = pN->Use.Binary.pLeft;
        TPExprNode pRight = pN->Use.Binary.pRight;

        // Anding is commutative and constants on the right gives better assembler output.
        if (pLeft->Usage == uConst) {                                                               // left const
            pN->Use.Binary.pLeft = pRight;                                                          //
            pRight = pN->Use.Binary.pRight = pLeft;                                                 //
            pLeft = pN->Use.Binary.pLeft;                                                           //
            pRight = pN->Use.Binary.pRight;                                                         //
        }                                                                                           //

        if (pLeft->Usage == uConst) {                                                               // Left const
            pLeft->Use.Const.lInteger &= pRight->Use.Const.lInteger;                                //      (c + c) ==> c
            pLeft->pType = pN->pType;                                                               //
            return pLeft;                                                                           //      
        }                                                                                           //

        if (pRight->Usage == uConst) {                                                              // Right const
            if (pRight->Use.Const.lInteger == 0) {                                                  //      Right is const zero
                pRight->pType = pN->pType;                                                          //
                return pRight;                                                                      //      (v & 0) ==> 0
            }                                                                                       //
            switch (CalcSizeOf(pLeft->pType)) {                                                     //      (v & ~0) ==> v
            case 1: if ((pRight->Use.Const.lInteger & 0xFF) == 0xFF) {                              //
                        pLeft->pType = pN->pType;                                                   //
                        return pLeft;                                                               //
                    }                                                                               //
                    break;                                                                          //
            case 2: if ((pRight->Use.Const.lInteger & 0xFFFF) == 0xFFFF) {                          //
                        pLeft->pType = pN->pType;                                                   //
                        return pLeft;                                                               //
                    }                                                                               //
                    break;                                                                          //
            case 4: if ((pRight->Use.Const.lInteger & 0xFFFFFFFF) == 0xFFFFFFFF) {                  //
                        pLeft->pType = pN->pType;                                                   //
                        return pLeft;                                                               //
                    }                                                                               //
                    break;                                                                          //
            }                                                                                       //
            if ((pLeft->Usage == uBinary) &&                                                        //
                (pLeft->Use.Binary.Op == binAnd)) {                                                   //      left is and
                TPExprNode pSubLeft = pLeft->Use.Binary.pLeft;                                      //
                TPExprNode pSubRight = pLeft->Use.Binary.pRight;                                    //
                if (pSubRight->Usage == uConst) {                                                   //
                                                                                                    //no need to check left = const                                                 //
                    pRight->Use.Const.lInteger &= pSubRight->Use.Const.lInteger;                    //     (v &  c) & c ==> v & c
                    pN->Use.Binary.pLeft = pSubLeft;                                                //
                    return OptimizeBinary(iDepth, pN, FALSE);                                                                      //
                }                                                                                   //
            }                                                                                       //
            return pN;                                                                              //
        }                                                                                           //

        if ((pRight->Usage == uBinary) &&                                                           // Right is binary addition with a constant
            (pRight->Use.Binary.Op == binAnd) &&                                                      //
            (pRight->Use.Binary.pRight->Usage == uConst) &&                                         //
            (pLeft->Usage == uBinary) &&                                                            // so is left.
            (pLeft->Use.Binary.Op == binAnd) &&                                                       //
            (pRight->Use.Binary.pRight->Usage == uConst)) {                                         // (v&c)&(v&c) ==> (v&v)&c

            pRight->Use.Binary.pRight->Use.Const.lInteger &= pLeft->Use.Binary.pRight->Use.Const.lInteger;
            pLeft->Use.Binary.pRight = pRight->Use.Binary.pLeft;
            pN->Use.Binary.pRight = pRight->Use.Binary.pRight;
            return OptimizeBinary(iDepth, pN, FALSE);
        }

        return pN;
}

// ##########################################################################
// #  Function: OptimizeBinaryBOr
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
static TPExprNode OptimizeBinaryBOr(int iDepth, TPExprNode pN, BOOL fRoot) {
        ASSERT(pN->Usage == uBinary);
        ASSERT(pN->Use.Binary.Op == binOr);
        
        TPExprNode pLeft = pN->Use.Binary.pLeft;
        TPExprNode pRight = pN->Use.Binary.pRight;

        // Or-ing is commutative and constants on the right gives better assembler output.
        if (pLeft->Usage == uConst) {                                                               // left const
            pN->Use.Binary.pLeft = pRight;                                                          //
            pRight = pN->Use.Binary.pRight = pLeft;                                                 //
            pLeft = pN->Use.Binary.pLeft;                                                           //
            pRight = pN->Use.Binary.pRight;                                                         //
        }                                                                                           //

        if (pLeft->Usage == uConst) {                                                               // Left const
            pLeft->Use.Const.lInteger |= pRight->Use.Const.lInteger;                                //      (c | c) ==> c
            pLeft->pType = pN->pType;                                                               //
            return pLeft;                                                                           //      
        }                                                                                           //

        if (pRight->Usage == uConst) {                                                              // Right const
            if (pRight->Use.Const.lInteger == 0) {                                                  //      Right is const zero
                pLeft->pType = pN->pType;                                                           //
                return pLeft;                                                                       //      (v | 0) ==> v
            }                                                                                       //
            switch (CalcSizeOf(pLeft->pType)) {                                                     //      (v | ~0) ==> ~0
            case 1: if ((pRight->Use.Const.lInteger & 0xFF) == 0xFF) {                              //
                        pRight->pType = pN->pType;                                                  //
                        return pRight;                                                              //
                    }                                                                               //
                    break;                                                                          //
            case 2: if ((pRight->Use.Const.lInteger & 0xFFFF) == 0xFFFF) {                          //
                        pRight->pType = pN->pType;                                                  //
                        return pRight;                                                              //
                    }                                                                               //
                    break;                                                                          //
            case 4: if ((pRight->Use.Const.lInteger & 0xFFFFFFFF) == 0xFFFFFFFF) {                  //
                        pRight->pType = pN->pType;                                                  //
                        return pRight;                                                              //
                    }                                                                               //
                    break;                                                                          //
            }                                                                                       //
            if ((pLeft->Usage == uBinary) &&                                                        //
                (pLeft->Use.Binary.Op == binOr)) {                                                    //      left is or
                TPExprNode pSubLeft = pLeft->Use.Binary.pLeft;                                      //
                TPExprNode pSubRight = pLeft->Use.Binary.pRight;                                    //
                if (pSubRight->Usage == uConst) {                                                   //no need to check left = const                                                 //
                    pRight->Use.Const.lInteger |= pSubRight->Use.Const.lInteger;                    //     (v |  c) | c ==> v | c
                    pN->Use.Binary.pLeft = pSubLeft;                                                //
                    return OptimizeBinary(iDepth, pN, FALSE);                                                      //
                }                                                                                   //
            }                                                                                       //
            return pN;                                                                              //
        }                                                                                           //

        if ((pRight->Usage == uBinary) &&                                                           // Right is binary addition with a constant
            (pRight->Use.Binary.Op == binOr) &&                                                       //
            (pRight->Use.Binary.pRight->Usage == uConst) &&                                         //
            (pLeft->Usage == uBinary) &&                                                            // so is left.
            (pLeft->Use.Binary.Op == binOr) &&                                                        //
            (pRight->Use.Binary.pRight->Usage == uConst)) {                                         // (v|c)|(v|c) ==> (v|v)|c

            pRight->Use.Binary.pRight->Use.Const.lInteger |= pLeft->Use.Binary.pRight->Use.Const.lInteger;
            pLeft->Use.Binary.pRight = pRight->Use.Binary.pLeft;
            pN->Use.Binary.pRight = pRight->Use.Binary.pRight;
            return OptimizeBinary(iDepth, pN, FALSE);
        }

        return pN;
}

// ##########################################################################
// #  Function: OptimizeBinaryBXor
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
static TPExprNode OptimizeBinaryBXor(int iDepth, TPExprNode pN, BOOL fRoot) {
        ASSERT(pN->Usage == uBinary);
        ASSERT(pN->Use.Binary.Op == binXor);
        
        TPExprNode pLeft = pN->Use.Binary.pLeft;
        TPExprNode pRight = pN->Use.Binary.pRight;

        // Or-ing is commutative and constants on the right gives better assembler output.
        if (pLeft->Usage == uConst) {                                                               // left const
            pN->Use.Binary.pLeft = pRight;                                                          //
            pRight = pN->Use.Binary.pRight = pLeft;                                                 //
            pLeft = pN->Use.Binary.pLeft;                                                           //
            pRight = pN->Use.Binary.pRight;                                                         //
        }                                                                                           //

        if (pLeft->Usage == uConst) {                                                               // Left const
            pLeft->Use.Const.lInteger ^= pRight->Use.Const.lInteger;                                //      (c | c) ==> c
            pLeft->pType = pN->pType;                                                               //
            return pLeft;                                                                           //      
        }                                                                                           //

        if (pRight->Usage == uConst) {                                                              // Right const
            if (pRight->Use.Const.lInteger == 0) {                                                  //      Right is const zero
                pLeft->pType = pN->pType;                                                           //
                return pLeft;                                                                       //      (v ^ 0) ==> v
            }                                                                                       //
            switch (CalcSizeOf(pLeft->pType)) {                                                     //      (v ^ ~0) ==> ~v
            case 1: if ((pRight->Use.Const.lInteger & 0xFF) == 0xFF) {                              //
                        pRight->Usage = uUnary;                                                     //
                        pRight->Use.Unary.Op = unNeg;                                                 //
                        pRight->Use.Unary.pOperand = pLeft;                                         //
                        pRight->pType = pLeft->pType;                                               //
                        pRight->pType = pN->pType;                                                  //
                        return pRight;                                                              //
                    }
                    break;                                                                          //
            case 2: if ((pRight->Use.Const.lInteger & 0xFFFF) == 0xFFFF) {                          //
                        pRight->Usage = uUnary;                                                     //
                        pRight->Use.Unary.Op = unNeg;                                                 //
                        pRight->Use.Unary.pOperand = pLeft;                                         //
                        pRight->pType = pLeft->pType;                                               //
                        return pRight;                                                              //
                    }                                                                               
                    break;                                                                          //
            case 4: if ((pRight->Use.Const.lInteger & 0xFFFFFFFF) == 0xFFFFFFFF) {                  //
                        pRight->Usage = uUnary;                                                     //
                        pRight->Use.Unary.Op = unNeg;                                                 //
                        pRight->Use.Unary.pOperand = pLeft;                                         //
                        pRight->pType = pLeft->pType;                                               //
                        return pRight;                                                              //
                    }
                    break;                                                                          //
            }                                                                                       //
            if ((pLeft->Usage == uBinary) &&                                                        //
                (pLeft->Use.Binary.Op == binXor)) {                                                   //      left is xor
                TPExprNode pSubLeft = pLeft->Use.Binary.pLeft;                                      //
                TPExprNode pSubRight = pLeft->Use.Binary.pRight;                                    //
                if (pSubRight->Usage == uConst) {                                                   //no need to check left = const                                                 //
                    pRight->Use.Const.lInteger ^= pSubRight->Use.Const.lInteger;                    //     (v ^  c) ^ c ==> v ^ c
                    pN->Use.Binary.pLeft = pSubLeft;                                                //
                    return OptimizeBinary(iDepth, pN, FALSE);                                                      //
                }                                                                                   //
            }                                                                                       //
            return pN;                                                                              //
        }                                                                                           //

        if ((pRight->Usage == uBinary) &&                                                           // Right is binary addition with a constant
            (pRight->Use.Binary.Op == binXor) &&                                                       //
            (pRight->Use.Binary.pRight->Usage == uConst) &&                                         //
            (pLeft->Usage == uBinary) &&                                                            // so is left.
            (pLeft->Use.Binary.Op == binXor) &&                                                        //
            (pRight->Use.Binary.pRight->Usage == uConst)) {                                         // (v^c)^(v^c) ==> (v^v)^c

            pRight->Use.Binary.pRight->Use.Const.lInteger ^= pLeft->Use.Binary.pRight->Use.Const.lInteger;
            pLeft->Use.Binary.pRight = pRight->Use.Binary.pLeft;
            pN->Use.Binary.pRight = pRight->Use.Binary.pRight;
            return OptimizeBinary(iDepth, pN, FALSE);
        }

        return pN;
}

// ##########################################################################
// #  Function: OptimizeBinaryCEQ
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
static TPExprNode OptimizeBinaryCEQ(int iDepth, TPExprNode pN, BOOL fRoot) {
        ASSERT(pN->Usage == uBinary);
        ASSERT(pN->Use.Binary.Op == binCEQ);

        TPExprNode pLeft = pN->Use.Binary.pLeft;
        TPExprNode pRight = pN->Use.Binary.pRight;

        // Conditionals must not change the order of calculation.
        // Signed/unsigned mix was reported during the 'C' parsing.
        if ((pLeft->Usage == uConst) && (pRight->Usage == uConst)) {        // left  and right are const
            ASSERT(pLeft->pType->Usage == DecSpec);
            ASSERT(pRight->pType->Usage == DecSpec);

            if (pLeft->Use.Const.lInteger == pRight->Use.Const.lInteger) {
                pLeft->Use.Const.lInteger = TRUE;
            }
            else {
                pLeft->Use.Const.lInteger = FALSE;
            }
            pLeft->pType = pN->pType;           // TypeINT;
            return pLeft;
        }

        return pN;
}

// ##########################################################################
// #  Function: OptimizeBinaryCNE
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
static TPExprNode OptimizeBinaryCNE(int iDepth, TPExprNode pN, BOOL fRoot) {
        ASSERT(pN->Usage == uBinary);
        ASSERT(pN->Use.Binary.Op == binCNE);
        
        TPExprNode pLeft = pN->Use.Binary.pLeft;
        TPExprNode pRight = pN->Use.Binary.pRight;

        // Conditionals must not change the order of calculation.
        // Signed/unsigned mix was reported during the 'C' parsing.
        if ((pLeft->Usage == uConst) && (pRight->Usage == uConst)) {        // left  and right are const
            ASSERT(pLeft->pType->Usage == DecSpec);
            ASSERT(pRight->pType->Usage == DecSpec);

            if (pLeft->Use.Const.lInteger != pRight->Use.Const.lInteger) {
                pLeft->Use.Const.lInteger = TRUE;
            }
            else {
                pLeft->Use.Const.lInteger = FALSE;
            }
            pLeft->pType = pN->pType;
            return pLeft;
        }

        return pN;
}

// ##########################################################################
// #  Function: OptimizeBinaryCLT
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
static TPExprNode OptimizeBinaryCLT(int iDepth, TPExprNode pN, BOOL fRoot) {
        ASSERT(pN->Usage == uBinary);
        ASSERT(pN->Use.Binary.Op == binCLT);

        TPExprNode pLeft = pN->Use.Binary.pLeft;
        TPExprNode pRight = pN->Use.Binary.pRight;

        // Conditionals must not change the order of calculation.
        // Signed/unsigned mix was reported during the 'C' parsing.
        if ((pLeft->Usage == uConst) && (pRight->Usage == uConst)) {        // left  and right are const
            ASSERT(pLeft->pType->Usage == DecSpec);
            ASSERT(pRight->pType->Usage == DecSpec);

            if (pLeft->Use.Const.lInteger < pRight->Use.Const.lInteger) {
                pLeft->Use.Const.lInteger = TRUE;
            }
            else {
                pLeft->Use.Const.lInteger = FALSE;
            }
            pLeft->pType = pN->pType;
            return pLeft;
        }

        return pN;
}

// ##########################################################################
// #  Function: OptimizeBinaryCLE
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
static TPExprNode OptimizeBinaryCLE(int iDepth, TPExprNode pN, BOOL fRoot) {
        ASSERT(pN->Usage == uBinary);
        ASSERT(pN->Use.Binary.Op == binCLE);

        TPExprNode pLeft = pN->Use.Binary.pLeft;
        TPExprNode pRight = pN->Use.Binary.pRight;

        // Conditionals must not change the order of calculation.
        // Signed/unsigned mix was reported during the 'C' parsing.
        if ((pLeft->Usage == uConst) && (pRight->Usage == uConst)) {        // left  and right are const
            ASSERT(pLeft->pType->Usage == DecSpec);
            ASSERT(pRight->pType->Usage == DecSpec);

            if (pLeft->Use.Const.lInteger <= pRight->Use.Const.lInteger) {
                pLeft->Use.Const.lInteger = TRUE;
            }
            else {
                pLeft->Use.Const.lInteger = FALSE;
            }
            pLeft->pType = pN->pType;
            return pLeft;
        }

        return pN;
}

// ##########################################################################
// #  Function: OptimizeBinaryCGT
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
static TPExprNode OptimizeBinaryCGT(int iDepth, TPExprNode pN, BOOL fRoot) {
        ASSERT(pN->Usage == uBinary);
        ASSERT(pN->Use.Binary.Op == binCGT);

        TPExprNode pLeft = pN->Use.Binary.pLeft;
        TPExprNode pRight = pN->Use.Binary.pRight;

        // Conditionals must not change the order of calculation.
        // Signed/unsigned mix was reported during the 'C' parsing.
        if ((pLeft->Usage == uConst) && (pRight->Usage == uConst)) {        // left  and right are const
            ASSERT(pLeft->pType->Usage == DecSpec);
            ASSERT(pRight->pType->Usage == DecSpec);

            if (pLeft->Use.Const.lInteger > pRight->Use.Const.lInteger) {
                pLeft->Use.Const.lInteger = TRUE;
            }
            else {
                pLeft->Use.Const.lInteger = FALSE;
            }
            pLeft->pType = pN->pType;
            return pLeft;
        }

        return pN;
}

// ##########################################################################
// #  Function: OptimizeBinaryCGE
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
static TPExprNode OptimizeBinaryCGE(int iDepth, TPExprNode pN, BOOL fRoot) {
        ASSERT(pN->Usage == uBinary);
        ASSERT(pN->Use.Binary.Op == binCGE);

        TPExprNode pLeft = pN->Use.Binary.pLeft;
        TPExprNode pRight = pN->Use.Binary.pRight;

        // Conditionals must not change the order of calculation.
        // Signed/unsigned mix was reported during the 'C' parsing.
        if ((pLeft->Usage == uConst) && (pRight->Usage == uConst)) {        // left  and right are const
            ASSERT(pLeft->pType->Usage == DecSpec);
            ASSERT(pRight->pType->Usage == DecSpec);

            if (pLeft->Use.Const.lInteger >= pRight->Use.Const.lInteger) {
                pLeft->Use.Const.lInteger = TRUE;
            }
            else {
                pLeft->Use.Const.lInteger = FALSE;
            }
            pLeft->pType = pN->pType;
            return pLeft;
        }

        return pN;
}

// ##########################################################################
// #  Function: OptimizeBinaryLAnd
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
static TPExprNode OptimizeBinaryLAnd(int iDepth, TPExprNode pN, BOOL fRoot) {
        ASSERT(pN->Usage == uBinary);
        ASSERT(pN->Use.Binary.Op == binLAnd);
        
        TPExprNode pLeft = pN->Use.Binary.pLeft;
        TPExprNode pRight = pN->Use.Binary.pRight;

        // Conditionals must not change the order of calculation.
        // process left to right. stop at first FALSE
        if (pLeft->Usage == uConst) {                                                                   // left is constant
            ASSERT(pLeft->pType->Usage == DecSpec);

            if (pRight->Usage == uConst) {                                                              // left and right are constant
                ASSERT(pRight->pType->Usage == DecSpec);                                                //
                                                                                                        //
                if ((pLeft->Use.Const.lInteger != FALSE) && (pRight->Use.Const.lInteger != FALSE)) {    //
                    pLeft->Use.Const.lInteger = TRUE;                                                   //
                }                                                                                       //
                else {                                                                                  //
                    pLeft->Use.Const.lInteger = FALSE;                                                  //
                }                                                                                       //
                pLeft->pType = pN->pType;                                                               //
                return pLeft;                                                                           //
            }
            else {                                                                                      // Left const. Right var
                if (pLeft->Use.Const.lInteger == FALSE) {                                               //
                    pLeft->pType = pN->pType;                                                           //
                    return pLeft;                                                                       //
                }                                                                                       //
            }                                                                                           //
            return ExprMakeCastNode(pN->pType, pRight);                                                 //
        }

        if (pRight->Usage == uConst) {                                                                  // left var and right constant
            ASSERT(pRight->pType->Usage == DecSpec);                                                    //
            if (pRight->Use.Const.lInteger != FALSE) {                                                  //
                return ExprMakeCastNode(pN->pType, pLeft);                                              //
            }                                                                                           //    
            // fall out to simple return
        }

        return pN;
}

// ##########################################################################
// #  Function: OptimizeBinaryLOr
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
static TPExprNode OptimizeBinaryLOr(int iDepth, TPExprNode pN, BOOL fRoot) {
        ASSERT(pN->Usage == uBinary);
        ASSERT(pN->Use.Binary.Op == binLOr);

        TPExprNode pLeft = pN->Use.Binary.pLeft;
        TPExprNode pRight = pN->Use.Binary.pRight;

        // Conditionals must not change the order of calculation.
        // process left to right. stop at first TRUE
        if (pLeft->Usage == uConst) {                                                                   // left is constant
            ASSERT(pLeft->pType->Usage == DecSpec);

            if (pRight->Usage == uConst) {                                                              // left and right are constant
                ASSERT(pRight->pType->Usage == DecSpec);                                                //
                                                                                                        //
                if ((pLeft->Use.Const.lInteger != FALSE) || (pRight->Use.Const.lInteger != FALSE)) {    //
                    pLeft->Use.Const.lInteger = TRUE;                                                   //
                }                                                                                       //
                else {                                                                                  //
                    pLeft->Use.Const.lInteger = FALSE;                                                  //
                }                                                                                       //
                pLeft->pType = pN->pType;                                                               //
                return pLeft;                                                                           //
            }
            else {                                                                                      // Left const. Right var
                if (pLeft->Use.Const.lInteger != FALSE) {                                               //
                    pLeft->Use.Const.lInteger = TRUE;
                    pLeft->pType = pN->pType;                                                           //
                    return pLeft;                                                                       //
                }                                                                                       //
            }                                                                                           //
            return ExprMakeCastNode(pN->pType, pRight);                                                 //
        }

        if (pRight->Usage == uConst) {                                                                  // left var and right constant
            ASSERT(pRight->pType->Usage == DecSpec);                                                    //
            if (pRight->Use.Const.lInteger == FALSE) {                                                  //
                return ExprMakeCastNode(pN->pType, pLeft);                                              //
            }                                                                                           //    
            // fall out to simple return                                                                //
        }

        return pN;
}

// ##########################################################################
// #  Function: OptimizeBinaryBSR
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
static TPExprNode OptimizeBinaryBSR(int iDepth, TPExprNode pN, BOOL fRoot) {
        ASSERT(pN->Usage == uBinary);
        ASSERT(pN->Use.Binary.Op == binShr);

        TPExprNode pLeft = pN->Use.Binary.pLeft;
        TPExprNode pRight = pN->Use.Binary.pRight;

        if (pRight->Usage == uConst) {                                                                   // Right is constant
            ASSERT(pRight->pType->Usage == DecSpec);

            if (pLeft->Usage == uConst) {                                                                // Right and left are constant
                ASSERT(pLeft->pType->Usage == DecSpec);

                if (IsSigned(pLeft->pType)) {
                    switch (CalcSizeOf(pLeft->pType)) {
                    case 1: pLeft->Use.Const.lInteger = (long)(unsigned char)(((long)(char)pLeft->Use.Const.lInteger) >> pRight->Use.Const.lInteger); break;
                    case 2: pLeft->Use.Const.lInteger = (long)(unsigned short)(((long)(short)pLeft->Use.Const.lInteger) >> pRight->Use.Const.lInteger); break;
                    case 4: pLeft->Use.Const.lInteger = (pLeft->Use.Const.lInteger >> pRight->Use.Const.lInteger); break;
                    default: Error(FATAL, "OptimizeBinaryBSR() size of left field.");
                    }
                }
                else {
                    switch (CalcSizeOf(pLeft->pType)) {
                    case 1: pLeft->Use.Const.lInteger = (long)(unsigned char)(((unsigned long)(unsigned char)pLeft->Use.Const.lInteger) >> pRight->Use.Const.lInteger); break;
                    case 2: pLeft->Use.Const.lInteger = (long)(unsigned short)(((unsigned long)(unsigned short)pLeft->Use.Const.lInteger) >> pRight->Use.Const.lInteger); break;
                    case 4: pLeft->Use.Const.lInteger = ((unsigned long)pLeft->Use.Const.lInteger) >> pRight->Use.Const.lInteger; break;
                    default: Error(FATAL, "OptimizeBinaryBSR() size of left field.");
                    }
                }
                return pLeft;
            }
            else {
                if (IsUnsigned(pLeft->pType) && (pRight->Use.Const.lInteger >= (long)(8*CalcSizeOf(pLeft->pType)))) {
                    pRight->Use.Const.lInteger = 0;
                    pRight->pType = pLeft->pType;
                    return pRight;
                }
            }
        }
        // right is variable. can't predict anything.
        return pN;
}

// ##########################################################################
// #  Function: OptimizeBinaryBSL
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
static TPExprNode OptimizeBinaryBSL(int iDepth, TPExprNode pN, BOOL fRoot) {
        ASSERT(pN->Usage == uBinary);
        ASSERT(pN->Use.Binary.Op == binShl);
        TPExprNode pLeft = pN->Use.Binary.pLeft;
        TPExprNode pRight = pN->Use.Binary.pRight;

        if (pRight->Usage == uConst) {                                                                   // Right is constant
            ASSERT(pRight->pType->Usage == DecSpec);

            if (pLeft->Usage == uConst) {                                                                // Right and left are constant
                ASSERT(pLeft->pType->Usage == DecSpec);
                switch (CalcSizeOf(pLeft->pType)) {
                case 1: pLeft->Use.Const.lInteger = (long)(unsigned char)(((unsigned long)(unsigned char)pLeft->Use.Const.lInteger) << pRight->Use.Const.lInteger); break;
                case 2: pLeft->Use.Const.lInteger = (long)(unsigned short)(((unsigned long)(unsigned short)pLeft->Use.Const.lInteger) << pRight->Use.Const.lInteger); break;
                case 4: pLeft->Use.Const.lInteger = ((unsigned long)pLeft->Use.Const.lInteger) << pRight->Use.Const.lInteger; break;
                default: Error(FATAL, "OptimizeBinaryBSR() size of left field.");
                }
                return pLeft;
            }
            else {
                if ((pRight->Use.Const.lInteger >= (long)(8 * CalcSizeOf(pLeft->pType)))) {
                    pRight->Use.Const.lInteger = 0;
                    pRight->pType = pLeft->pType;
                    return pRight;
                }
            }
        }

        // right is variable. can't predict anything.
        return pN;
}

// ##########################################################################
// #  Function: OptimizeBinary
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
static TPExprNode OptimizeBinary(int iDepth, TPExprNode pN, BOOL fRoot) {
    ASSERT(pN->Usage == uBinary);

    pN->Use.Binary.pLeft = Optimize(iDepth+1, pN->Use.Binary.pLeft, FALSE);
    pN->Use.Binary.pRight = Optimize(iDepth+1, pN->Use.Binary.pRight, FALSE);
    
    switch (pN->Use.Binary.Op) {
    case binAdd:  return OptimizeBinaryAdd(iDepth, pN, fRoot);
    case binSub:  return OptimizeBinarySub(iDepth, pN, fRoot);
    case binMul:  return OptimizeBinaryMul(iDepth, pN, fRoot);
    case binDiv:  return OptimizeBinaryDiv(iDepth, pN, fRoot);
    case binMod:  return OptimizeBinaryMod(iDepth, pN, fRoot);
    case binAnd: return OptimizeBinaryBAnd(iDepth, pN, fRoot);
    case binOr:  return OptimizeBinaryBOr(iDepth, pN, fRoot);
    case binXor: return OptimizeBinaryBXor(iDepth, pN, fRoot);
    case binCEQ:  return OptimizeBinaryCEQ(iDepth, pN, fRoot);
    case binCNE:  return OptimizeBinaryCNE(iDepth, pN, fRoot);
    case binCLT:  return OptimizeBinaryCLT(iDepth, pN, fRoot);
    case binCLE:  return OptimizeBinaryCLE(iDepth, pN, fRoot);
    case binCGT:  return OptimizeBinaryCGT(iDepth, pN, fRoot);
    case binCGE:  return OptimizeBinaryCGE(iDepth, pN, fRoot);
    case binLAnd: return OptimizeBinaryLAnd(iDepth, pN, fRoot);
    case binLOr:  return OptimizeBinaryLOr(iDepth, pN, fRoot);
    case binShr:  return OptimizeBinaryBSR(iDepth, pN, fRoot);
    case binShl:  return OptimizeBinaryBSL(iDepth, pN, fRoot);
    default:   
        Error(FATAL, "OptimizeBinary(): What [%d]\n", pN->Use.Binary.Op);
    }
    return pN;
}


static TPExprNode OptimizeTernary(int iDepth, TPExprNode pN, BOOL fRoot) {
#pragma message("    OptimizeTernary(): Needs to be optimized.")
    ASSERT(pN->Usage == uTernary);
    pN->Use.Ternary.pFirst = Optimize(iDepth + 1, pN->Use.Ternary.pFirst, FALSE);
    pN->Use.Ternary.pSecond = Optimize(iDepth + 1, pN->Use.Ternary.pSecond, FALSE);
    pN->Use.Ternary.pThird = Optimize(iDepth + 1, pN->Use.Ternary.pThird, FALSE);
    return pN;
}


static TPExprNode OptimizeDotExpr(int iDepth, TPExprNode pN, BOOL fRoot) {
#pragma message("    OptimizeDotExpr(): Needs to be optimized.")
    ASSERT(pN->Usage == uDot);
    pN->Use.Dot.pRecord = Optimize(iDepth + 1, pN->Use.Dot.pRecord, FALSE);
    return pN;
}


static TPExprNode OptimizeArrowExpr(int iDepth, TPExprNode pN, BOOL fRoot) {
#pragma message("    OptimizeArrowExpr(): Needs to be optimized.")
    ASSERT(pN->Usage == uArrow);
    pN->Use.Arrow.pRecord = Optimize(iDepth + 1, pN->Use.Arrow.pRecord, fRoot);
    return pN;
}


static TPExprNode OptimizeArrayExpr(int iDepth, TPExprNode pN, BOOL fRoot) {
#pragma message("    OptimizeArrayExpr(): Needs to be optimized.")
    ASSERT(pN->Usage == uArray);
    pN->Use.Array.pVector = Optimize(iDepth + 1, pN->Use.Array.pVector, FALSE);
    pN->Use.Array.pIndex = Optimize(iDepth + 1, pN->Use.Array.pIndex, FALSE);
    return pN;
}

static TPExprNode OptimizeFunction(int iDepth, TPExprNode pN, BOOL fRoot) {
    ASSERT(pN->Usage == uFunc);

    TPExprNode *ppInvokationParameterList = &pN->Use.Func.pParams;
    while (*ppInvokationParameterList != NULL) {
        TPExprNode pPrevious = (*ppInvokationParameterList)->pPreviousArg;
        *ppInvokationParameterList = Optimize(iDepth +1, *ppInvokationParameterList, FALSE);
        (*ppInvokationParameterList)->pPreviousArg = pPrevious;
        ppInvokationParameterList = &(*ppInvokationParameterList)->pPreviousArg;
    }
    return pN;
}


static TPExprNode OptimizeAssign(int iDepth, TPExprNode pN, BOOL fRoot) {
#pragma message("    OptimizeAssign(): Needs to be optimized.")
    ASSERT(pN->Usage == uAssign);
    pN->Use.Assign.pLval = Optimize(iDepth + 1, pN->Use.Assign.pLval, FALSE);
    pN->Use.Assign.pRval = Optimize(iDepth + 1, pN->Use.Assign.pRval, FALSE);
    return pN;
}

// ##########################################################################
// #  Function: OptimizeCast_Anything
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
static TPExprNode OptimizeCast_Anything(int iDepth, TPExprNode pN, BOOL fRoot) {

    pN->Use.Cast.pTarget = Optimize(iDepth+1, pN->Use.Cast.pTarget, FALSE);

    TPExprNode pSubNode = pN->Use.Cast.pTarget;
    if (pSubNode->Usage == uConst) {
        pSubNode->Use.Const.lInteger = ExprTypeConvertConst(pN->pType, pSubNode->pType, pSubNode->Use.Const.lInteger);
        pSubNode->pType = pN->pType;
        return pSubNode;
    }

    return pN;
}


// ####################################################################################################
// ##########################################################################
// #  Function: GenExprConditional
// #        <todo: task brief description>
// #
// #        <todo: task detailed description>
// #
// #  Parameters:
// #        TPExprNode  pN      - expression to optimize
// #        BOOL        fRoot   - Root of the expression (not a recursive call).
// #
// #  Returns:
// #        <todo: return Value>
// #
// #  Note: If we are at the root of an expression we know that the result value does not matter.
// #
// #        Eg.the expression 
// #               "a++" is equivelent to "++a" because this expression will not use the result.
// #               b = a++ cannot be treated the same way.
// #
// #  See Also:
// #
// ##########################################################################

static TPExprNode Optimize(int iDepth, TPExprNode pN, BOOL fRoot) {
    if (pN == NULL) {
        Error(FATAL, "Optimizing a NULL expression");
        return pN;
    }

//     ConsolePrintf(CON_WHITE_BRIGHT, "Optimizer  Before(%d)\n", iDepth);
//     GenExpressionPrettyPrint(iDepth*4, pN);

    switch (pN->Usage) {
    case uConst:    break; //  return pN;                           // We can't improve on a single Const value;
    case uIoreg:    break; //  return pN;                           // We can't improve on a single variable value;
    case uVar:      break; //  return pN;                           // We can't improve on a single variable value;
    case uUnary:    pN = OptimizeUnary(iDepth, pN, fRoot);           break; // Do what we can with unary opaeration.
    case uBinary:   pN = OptimizeBinary(iDepth, pN, fRoot);          break; // Do what we can with binary operations.
    case uTernary:  pN = OptimizeTernary(iDepth, pN, fRoot);         break; // Do what we can with Ternaryoperations.
    case uDot:      pN = OptimizeDotExpr(iDepth, pN, fRoot);         break; // Do what we can with structure DOT expression.
    case uArrow:    pN = OptimizeArrowExpr(iDepth, pN, fRoot);       break; // Do what we can with structure Arrow expression.
    case uArray:    pN = OptimizeArrayExpr(iDepth, pN, fRoot);       break; // Do what we can with Array expression.
    case uFunc:     pN = OptimizeFunction(iDepth, pN, fRoot);        break; // We can't improve on a function call but we can do its parameters.
    case uCast:     pN = OptimizeCast_Anything(iDepth, pN, fRoot);   break;
    case uAssign:   pN = OptimizeAssign(iDepth, pN, fRoot);          break; // Do what we can with assignments.
    default:        Error(FATAL, "ParseExpr: What [%d]\n", pN->Usage);
                    pN = NULL;
    }

//    ConsolePrintf(CON_WHITE_BRIGHT, "Optimizer  After(%d)\n", iDepth);
//    GenExpressionPrettyPrint(iDepth * 4, pN);
//    ConsolePrintf(CON_WHITE_BRIGHT, "Optimizer  End(%d)\n", iDepth);

    return pN;

}





// ##########################################################################
// #  Function: ExprOptimize
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
TPExprNode  ExprOptimize(TPExprNode pN) {

#pragma message("    **** ExprOptimize(): Could do better!")
//    ConsolePrintf(CON_WHITE_BRIGHT, "Optimizer  Before\n");
//    GenExpressionPrettyPrint(4, pN);
    
    pN = Optimize(1, pN, TRUE);
    
//    ConsolePrintf(CON_WHITE_BRIGHT, "Optimizer  After\n");    
//    GenExpressionPrettyPrint(4, pN);
//    ConsolePrintf(CON_WHITE_BRIGHT, "Optimizer  End\n");  

    return pN;
}    



/* eof */

