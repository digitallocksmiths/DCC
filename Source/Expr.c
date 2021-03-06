// # $URL: https://eboracum-vss.digitallocksmiths.local/svn/Dls/Sean/RoyalHolloway/CC_Avr/Source/Expr.c $
// # $Revision: 773 $


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
#include "GenAvr\Gen.h"
#include "main.h"
#include "C_Yacced.tab.h"


/* ******************************************************* */
/*  General Expression Housekeeping  */
/* ********************************* */

static TPExprNode
NewExprNode(ExprUsage Use) {
    TPExprNode NewEl;
    NewEl = New(sizeof(TExprNode));
    NewEl->Usage    = Use;
    NewEl->pType    = NULL;
    NewEl->pSibling = NULL;
    return NewEl;
 }

TPExprNode
ExprMakeConstC(LONG Value) {
    TPExprNode New;
    New = NewExprNode(uConst);
    New->pType = NewSpecType(TypeCHAR,NULL);
    New->Use.Const.lInteger = Value;
    return New;
 }


TPExprNode  ExprMakeIoReg(LONG   Value, LPSTR pszName) {
    TPExprNode New;
    New = NewExprNode(uIoreg);
    New->pType = NewSpecType(TypeUNSIGNED | TypeCHAR, NULL);
    New->Use.Ioreg.nReg = (WORD)Value;
    New->Use.Ioreg.pszName = pszName;
    return New;
}


TPExprNode ExprMakeConstI(LONG Value) {
    TPExprNode New;
    New = NewExprNode(uConst);
    if      ((SCHAR_MIN <= Value) && (Value <= SCHAR_MAX)) New->pType = NewSpecType(TypeSIGNED | TypeCHAR, NULL);
    else if ((0 <= Value) && (Value <= UCHAR_MAX))         New->pType = NewSpecType(TypeUNSIGNED | TypeCHAR, NULL);
    else if ((SHRT_MIN <= Value) && (Value <= SHRT_MAX))   New->pType = NewSpecType(TypeSIGNED | TypeSHORT, NULL);
    else if ((0 <= Value) && (Value <= USHRT_MAX))         New->pType = NewSpecType(TypeUNSIGNED | TypeSHORT, NULL);
    else if ((LONG_MIN <= Value) && (Value <= LONG_MAX))   New->pType = NewSpecType(TypeSIGNED | TypeLONG, NULL);
    else                                                   New->pType = NewSpecType(TypeUNSIGNED | TypeLONG, NULL);
    New->Use.Const.lInteger = Value;
    return New;
 }

TPExprNode
ExprMakeConstF(DOUBLE Value) {
    Error(WARNING0, "Floating point numbers are not supported.");
    return ExprMakeConstI((LONG)Value);
 }


#pragma message("    ExprMakeConstS: Should flag the contents as constant.")
// or the data generator should place the data whereever the associated variable thinks it lives.");
TPExprNode ExprMakeConstS(LPSTR Str) {
    LPSTR Lab = GenLabel("Str");
    TPDeclSpec p;
    p = NewIdentifier(Lab);
    p = NewArray(p,NULL);
    p->Use.DecId.pTarget->Use.DecArray.Size = (DWORD)strlen(Str)+1;
    p = AddInitializerStr(p,Str);
    p = AppendDecl(p,NewSpecType(TypeCHAR,NULL));
    Declaration(p);
    return ExprMakeVar(Lab);
 }

TPExprNode ExprMakeVar(LPSTR Variable) {                                        // new node to read a variable
    TPExprNode pNew;
    TPDeclSpec pV;
    pNew = NewExprNode(uVar);                                                   // new variable node
    pNew->Use.Var.pszIdentifier = Variable;                                     // the name is recorded here. 

    pV   = FindLocalObject(Variable);                                           // is it a local?
    if (pV != NULL) {                                                           //
        ASSERT(pV->Usage == DecId);                                             //
        pV->Use.DecId.UsedFlags |= DecId_UsedFlag_Local;                        // mark it as used
        //if ((pV->Use.DecId.UsedFlags & DecId_UsedFlag_Assigned) == 0) {                                             // test to see if this variable has had its contents set.
        //    Error(WARNING0, "Variable '%s' may be used before it is assigned a value\n", pV->Use.DecId.pszName);    // 
        //    pV->Use.DecId.UsedFlags |= DecId_UsedFlag_Assigned;                                                     // fake assignmnet will shut up future simlar complaints
        //}                                                                                                           //
        pNew->Use.Var.pDecId = pV;                                              //
        pNew->pType = pV->Use.DecId.pTarget;                                    // type is defined here.
        return pNew;                                                            //
    }                                                                           //

    pV = FindParameterObject(Variable);                                         // if not then is it a parameter ?
    if (pV != NULL) {                                                           //
        ASSERT(pV->Usage == DecId);                                             //
        pNew->Use.Var.pDecId = pV;                                              //
        pNew->pType = pV->Use.DecId.pTarget;                                    // type is defined here.
        return pNew;                                                            //
    }                                                                           //
    
    pV = FindGlobalObject(Variable);                                            // if not then is it a global ?
    if (pV != NULL) {                                                           //
        pNew->Use.Var.pDecId = NULL; GLOBAL_VAR;                                // NULL means it's global
        pNew->pType = pV->Use.DecId.pTarget;                                    // type is defined here.
        return pNew;                                                            //
    }                                                                           //

    Error(ERROR0, "Unknown Variable '%s'.", Variable);                          // if not then it's an unidentified variable
    pNew->Use.Var.pDecId = NULL;                                                // NULL means it's global (no code will be generated after the error though!)
    pNew->pType = NewSpecType(TypeINT, NULL);                                   // fake integer type
    return pNew;                                                                //
}

/* *************************************************** */

// #define IsStruct(n)    (((n)->Usage == DecSpec) &&  ((n)->Use.DecSpec.Type & TypeSTRUCT))
// #define IsSimple(n)    (((n)->Usage == DecSpec) && !((n)->Use.DecSpec.Type & TypeSTRUCT))
// #define IsUnsigned(n)  (((n)->Usage == DecSpec) &&  ((n)->Use.DecSpec.Type & TypeUNSIGNED))
// #define IsSigned(n)    (((n)->Usage == DecSpec) && !((n)->Use.DecSpec.Type & TypeUNSIGNED))
// #define IsPointer(n)    ((n)->Usage == DecPtr)
// #define IsArray(n)      ((n)->Usage == DecArray)
// #define IsFunc(n)       ((n)->Usage == DecFunc)
// #define IsReference(n)  (IsPointer(n) || IsArray(n))
// #define IsPtrStruct(n)  (IsPointer(n) && IsStruct((n)->Use.DecPtr.pTarget))

/* *************************************************** */
      
// TDeclSpec    Std_Ubyte   = { DecSpec, NULL, { 0, TypeUNSIGNED|TypeCHAR, 0, NULL } } ;
// TDeclSpec    Std_Sbyte   = { DecSpec, NULL, { 0, TypeSIGNED|TypeCHAR,   0, NULL } } ;
// TDeclSpec    Std_Uword   = { DecSpec, NULL, { 0, TypeUNSIGNED|TypeSHORT,0, NULL } } ;
// TDeclSpec    Std_Sword   = { DecSpec, NULL, { 0, TypeSIGNED|TypeSHORT,  0, NULL } } ;
// TDeclSpec    Std_Ulong   = { DecSpec, NULL, { 0, TypeUNSIGNED|TypeLONG, 0, NULL } } ;
// TDeclSpec    Std_Slong   = { DecSpec, NULL, { 0, TypeSIGNED|TypeLONG,   0, NULL } } ;

// TPDeclSpec  LpStd_Ubyte = &Std_Ubyte;
// TPDeclSpec  LpStd_Sbyte = &Std_Sbyte;
// TPDeclSpec  LpStd_Uword = &Std_Uword;
// TPDeclSpec  LpStd_Sword = &Std_Sword;
// TPDeclSpec  LpStd_Ulong = &Std_Ulong;
// TPDeclSpec  LpStd_Slong = &Std_Slong;




//static LpExprNode
//Cast(LpExprNode Left, LpDeclSpec Newtype) {
//#pragma message("Cast:  insert convert operand size code.")
//    return Left;
//}

///* ************************************************************ */
///*  pointer and node return the smallest integral pointer type  */
///* ************************************************************ */
//
//static LpDeclSpec
//CastToValidPointer(LpDeclSpec Ptr) {
//    if      (CalcSizeOf(Ptr) <= SIZE_CHAR)  return NewSpecType(TypeUNSIGNED|TypeCHAR,NULL);
//    else if (CalcSizeOf(Ptr) <= SIZE_SHORT) return NewSpecType(TypeUNSIGNED|TypeSHORT,NULL);
//    else                                    return NewSpecType(TypeUNSIGNED|TypeLONG,NULL);
//}

///* ************************************************************ */
///*  Make a binary node and insert the required castings         */
///* ************************************************************ */
//
//static LpExprNode
//FixCastings(LpExprNode New, LpExprNode Left, LpExprNode Right) {
//    if (!CompDecl(New->Type,Left->Type))  Left = MakeCastNode(New->Type, Left);
//    if (!CompDecl(New->Type,Right->Type)) Right= MakeCastNode(New->Type, Right);
//    New->Use.Binary.Left  = Left;
//    New->Use.Binary.Right = Right;
//    return New;
// }

/* ************************************************** */
/*  Unary  */
/* ******* */

static TPExprNode
NewUnary(WORD Op,  TPExprNode Node) {
    TPExprNode New;
    New = NewExprNode(uUnary);
    New->Use.Unary.Op = Op;             // operation  
    New->Use.Unary.pOperand = Node;      // target of operation
    New->pType = Node->pType;             // assume no change in type.
    return New;
 }
 
static TPExprNode
UMinus(TPExprNode Node) {
    TPExprNode New;
    if (!IsSimple(Node->pType)) {
        Error(WARNING0, "Unary arithmetic is only posible on simple types.");
        return Node;
    }
    if (Node->Usage == uConst)  {
        Node->Use.Const.lInteger = -(Node->Use.Const.lInteger);
        return Node;
    } else {
        New = NewUnary(unMinus, Node);
        return  New;
    }
 }
 
static TPExprNode
UPlus(TPExprNode Node) {
    if (!IsSimple(Node->pType)) {
        Error(WARNING0, "Unary arithmetic is only posible on simple types.");
        return Node;
    }
    return Node;
 }
 
static TPExprNode
UNeg(TPExprNode Node) {
    TPExprNode New;
    if (!IsSimple(Node->pType)) {
        Error(WARNING0, "Unary arithmetic is only posible on simple types.");
        return Node;
    }
    if (Node->Usage == uConst)  {
        Node->Use.Const.lInteger = ~(Node->Use.Const.lInteger);
        return Node;
    } else {
        New = NewUnary(unNeg, Node);
        return  New;
    }
 }
 
static TPExprNode
UNot(TPExprNode Node) {
    TPExprNode New;
    if (IsStruct(Node->pType)) {
        Error(WARNING0, "Unary logic is not possible on struct/union.");
        return Node;
    }
    if (Node->Usage == uConst)  {
        Node->Use.Const.lInteger = !(Node->Use.Const.lInteger);
        return Node;
    } else {
        TPDeclSpec NewType = NewSpecType(TypeBOOL, NULL);
        New = NewUnary(unNot, ExprMakeCastNode(NewType, Node));
        New->pType = NewType;
        return  New;
    }
 }
 
static TPExprNode
UPostInc(TPExprNode Node) {
    TPExprNode New;
    if (IsStruct(Node->pType)) {
        Error(WARNING0, "Cannot perform '++'/'--' on a structure.");
        return Node;
    }
    if (Node->Usage == uConst)  {
        Error(ERROR0, "'++' or '--' on a Constant is bit dumb.");
        return Node;
    } else {
        New = NewUnary(unPostInc, Node);
        return  New;
    }
 }
 
static TPExprNode
UPreInc(TPExprNode Node) {
    TPExprNode New;
    if (IsStruct(Node->pType)) {
        Error(WARNING0, "Cannot perform '++'/'--' on a structure.");
        return Node;
    }
    if (Node->Usage == uConst)  {
        Error(ERROR0, "'++' or '--' on a Constant is bit dumb.");
        return Node;
    } else {
        New = NewUnary(unPreInc, Node);
        return  New;
    }
 }
 
static TPExprNode
UPostDec(TPExprNode Node) {
    TPExprNode New;
    if (IsStruct(Node->pType)) {
        Error(WARNING0, "Cannot perform '++'/'--' on a structure.");
        return Node;
    }
    if (Node->Usage == uConst)  {
        Error(ERROR0, "'++' or '--' on a Constant is bit dumb.");
        return Node;
    } else {
        New = NewUnary(unPostDec, Node);
        return  New;
    }
 }
 
static TPExprNode
UPreDec(TPExprNode Node) {
    TPExprNode New;
    if (IsStruct(Node->pType)) {
        Error(WARNING0, "Cannot perform '++'/'--' on a structure.");
        return Node;
    }
    if (Node->Usage == uConst)  {
        Error(ERROR0, "'++' or '--' on a Constant is bit dumb.");
        return Node;
    } else {
        New = NewUnary(unPreDec, Node);
        return  New;
    }
 }
 
static TPExprNode
USizeof(TPExprNode Node) {
    return ExprMakeConstI(CalcSizeOf(Node->pType));
 }
 
static TPExprNode
UAddr(TPExprNode Node) {
    TPExprNode New;

//    ASSERT(Node->pType != NULL);
//    if (Node->pType->Usage == DecPtr) {                                     // wanting & of * of X
//        return ExprMakeCastNode(Node->pType->Use.DecPtr.pTarget, Node);     //  this is X
//    }

    if (Node->Usage == uConst) {
        Error(ERROR0, "Address of a numeric constant is meaningless.");
        return Node;
    }
//    if (Node->Usage == uUnary && Node->Use.Unary.Op == unPtr) {             // wanting & of * of X
//        return Node->Use.Unary.pOperand;                                    //  this is X
//    }
    

    New = NewUnary(unAddr, Node);
    if (Node->pType->Usage == DecArray) {                                     // fool C using &A to mean &A[0]
        New->pType = NewPointer(NULL, Node->pType->Use.DecArray.pTarget);
    }
    else {
        New->pType = NewPointer(NULL, Node->pType);
    }
    return  New;

 }

                          
static TPExprNode
UPtr(TPExprNode Node) {
    TPExprNode New;
    if (Node->pType->Usage == DecPtr) {
        New = NewUnary(unPtr, Node);
        New->pType = Node->pType->Use.DecPtr.pTarget;
        return  New;
    } else if (Node->pType->Usage == DecArray) {
        New = NewUnary(unPtr, Node);
        New->pType = Node->pType->Use.DecArray.pTarget;
        return  New;
    } else {
        Error(ERROR0, "De-Reference of a Non pointer type.");
        return Node;
    }
 }


TPExprNode
ExprMakeUnaryNode(TIdExprUnOp Op,  TPExprNode Node) {
    switch (Op) {
        case    unMinus:      return UMinus(Node);
        case    unPlus:       return UPlus(Node);
        case    unNeg:        return UNeg(Node);
        case    unNot:        return UNot(Node);
        case    unPostInc:    return UPostInc(Node);
        case    unPreInc:     return UPreInc(Node);
        case    unPostDec:    return UPostDec(Node);
        case    unPreDec:     return UPreDec(Node);
        case    unSizeOf:     return USizeof(Node);
        case    unAddr:       return UAddr(Node);
        case    unPtr:        return UPtr(Node);
        default:            Error(FATAL, "MakeUnaryNode(): UnKnown Unary Operator %d\n", Op);
                            return Node;
    }
 }

/* ************************************************** */
/*  Binary  */
/* ******** */

TPDeclSpec ExprResultingType(TPDeclSpec pLeft, TPDeclSpec pRight) {
//    printf("Left  = "); ParseDeclSpec(0, pLeft, FALSE);
//    printf("Right = "); ParseDeclSpec(0, pRight, FALSE);
    
    if ((pLeft->Usage == DecPtr) && (pRight->Usage == DecPtr)) {                // ptr : prt  => Only == is possible
        Error(ERROR1, "ResultingType(): Arithmetic on two pointers");
        return pLeft;
    }
    if (IsStruct(pLeft) || IsStruct(pRight)) {                                   //  can't cope with structures either.
        Error(ERROR1, "ResultingType(): Can't do Arithmetic on structures");
        return pLeft;
    }

    if ((pLeft->Usage == DecPtr) && (pRight->Usage == DecSpec)) {               // ptr : base => ptr
        return pLeft;
    }
    if ((pLeft->Usage == DecSpec) && (pRight->Usage == DecPtr)) {               // base : ptr => ptr
        return pRight;
    }
    if ((pLeft->Usage == DecSpec) && (pRight->Usage == DecSpec)) {              // base : base => biggest of the two
        if (CalcSizeOf(pLeft) > CalcSizeOf(pRight)) {                           //
            return pLeft;
        }
        if (CalcSizeOf(pLeft) < CalcSizeOf(pRight)) {
            return pRight;
        }
        return pLeft;
    }
    Error(ERROR1, "ResultingType(): Casting uncastable types.");
    ASSERT(FALSE); // should not get here.
    return pLeft;
}


static TPExprNode
NewBinary(TPDeclSpec pType, WORD Op,  TPExprNode Left, TPExprNode Right) {
    TPExprNode New;
    New = NewExprNode(uBinary);
    New->Use.Binary.Op    = Op;                         // operation  
    New->Use.Binary.pLeft  = Left;                      // target of operation
    New->Use.Binary.pRight = Right;                     // target of operation
    New->pType = pType;
    return New;
 }

static TPExprNode Badd (TPExprNode Left, TPExprNode Right);
static TPExprNode Bsub (TPExprNode Left, TPExprNode Right);
static TPExprNode Bmul (TPExprNode Left, TPExprNode Right);
static TPExprNode Bdiv (TPExprNode Left, TPExprNode Right);
static TPExprNode Bmod (TPExprNode Left, TPExprNode Right);
static TPExprNode Bband(TPExprNode Left, TPExprNode Right);
static TPExprNode Bbor (TPExprNode Left, TPExprNode Right);
static TPExprNode Bbxor(TPExprNode Left, TPExprNode Right);
static TPExprNode Bceq (TPExprNode Left, TPExprNode Right);
static TPExprNode Bcne (TPExprNode Left, TPExprNode Right);
static TPExprNode Bclt (TPExprNode Left, TPExprNode Right);
static TPExprNode Bcle (TPExprNode Left, TPExprNode Right);
static TPExprNode Bcgt (TPExprNode Left, TPExprNode Right);
static TPExprNode Bcge (TPExprNode Left, TPExprNode Right);
static TPExprNode Bland(TPExprNode Left, TPExprNode Right);
static TPExprNode Blor (TPExprNode Left, TPExprNode Right);
static TPExprNode Bbsr (TPExprNode Left, TPExprNode Right);
static TPExprNode Bbsl (TPExprNode Left, TPExprNode Right);



static TPExprNode Badd (TPExprNode Left, TPExprNode Right) {
    TPExprNode New;
    TPDeclSpec NewType;
    if (IsStruct(Left->pType) || IsStruct(Right->pType)) {                                      // we can't add structures
        Error(ERROR0, "Addition of Structures is not possible.");
        return Left;
    }
    if (IsReference(Left->pType) && IsReference(Right->pType)) {                                // we can't add two references
        Error(ERROR0, "Addition of References is not possible.");
        return Left;
    }
    if (IsSimple(Left->pType) && IsReference(Right->pType)) {                                   // if one simple and one ref (swap them)
        New   = Right;
        Right = Left;
        Left  = New;
        /* fall through (then pass) next test */                                                //           
    }
    if (IsReference(Left->pType) && IsSimple(Right->pType)) {                                   // Left reference and right simple 
        if (IsPointer(Left->pType)) {
            Right = Bmul(Right, ExprMakeConstI(CalcSizeOf(Left->pType->Use.DecPtr.pTarget)));   //       simple * sizeof what we point to
            Right = ExprMakeCastNode(NewSpecType(TypeSIGNED | TypeSHORT, NULL), Right);
            return NewBinary(Left->pType, binAdd, Left, Right);
        }
        else {
            ASSERT(Left->pType->Usage == DecArray); // never?
            Right = Bmul(Right, ExprMakeConstI(CalcSizeOf(Left->pType->Use.DecArray.pTarget))); //    or simple * size of array element.
            Right = ExprMakeCastNode(NewSpecType(TypeSIGNED | TypeSHORT, NULL), Right);
            return NewBinary(NewPointer(NULL, Left->pType->Use.DecArray.pTarget), binAdd, UAddr(Left), Right);
            //return NewBinary(Left->pType, binAdd, UAddr(Left), Right);
        }
    }
    
    ASSERT(IsSimple(Left->pType) && IsSimple(Right->pType));
    if (Left->Usage == uConst && Right->Usage == uConst) {
        Left->Use.Const.lInteger += Right->Use.Const.lInteger;
        ExprCleanUp(Right);
        return Left;
    } 

    NewType = ExprResultingType(Left->pType,Right->pType);
    Left    = ExprMakeCastNode(NewType, Left);
    Right   = ExprMakeCastNode(NewType, Right);
    return NewBinary(NewType, binAdd,Left,Right);
 }

static TPExprNode Bsub(TPExprNode Left, TPExprNode Right) {
    TPExprNode New;
    TPDeclSpec NewType;

    if (IsStruct(Left->pType) || IsStruct(Right->pType)) {                                          // aritmetic on structures is not possibel
        Error(ERROR0, "Subtraction of Structures is not possible.");
        return Left;
    }
    if (IsReference(Left->pType) && IsReference(Right->pType)) {                                    // can't sutract dissimilar pointers.
        if (!CompDecl(Left->pType, Right->pType)) {
            Error(ERROR0, "Subtraction of dissimilar references is not possible.");
            return Left;
        }
        if (Left->Usage == uConst && Right->Usage == uConst) {
            Left->Use.Const.lInteger -= Right->Use.Const.lInteger;
            Left->Use.Const.lInteger /= CalcSizeOf(Right->pType->Use.DecPtr.pTarget);
            ExprMakeCastNode(NewSpecType(TypeINT, NULL), Left); 
            ExprCleanUp(Right);
            return Left;
        }
        else {

            LONG lSize;
            TPDeclSpec pT = NewSpecType(TypeINT, NULL);
            switch (Left->pType->Usage) {
            case DecArray:  New = NewBinary(pT, binSub, Left, Right);
                            lSize = CalcSizeOf(Left->pType->Use.DecArray.pTarget);
                            break;
            case DecPtr:    New = NewBinary(pT, binSub, Left, Right);
                            lSize = CalcSizeOf(Left->pType->Use.DecPtr.pTarget);
                            break;
            default:
                New = NULL;
                Error(FATAL, "Ref or Array expected.");
            }

            New = NewBinary(pT, binDiv, New, ExprMakeCastNode(pT, ExprMakeConstI(lSize)));
            return New;
        }
    }
    if (IsReference(Right->pType)) {                                                                                            // cant subtract a reference from  non ref.
        Error(ERROR0, "Subtraction of a reference is not possible.");
        return Left;
    }
    if (IsReference(Left->pType) && IsSimple(Right->pType)) {                                                                   // right is a multiple of sizeof elements
        if (IsPointer(Left->pType)) Right = Bmul(Right, ExprMakeConstI(CalcSizeOf(Left->pType->Use.DecPtr.pTarget)));
        else                        Right = Bmul(Right, ExprMakeConstI(CalcSizeOf(Left->pType->Use.DecArray.pTarget)));
        /* fall through to simple sub */
    }

    //ASSERT(IsSimple(Left->pType) && IsSimple(Right->pType));
    if (Left->Usage == uConst && Right->Usage == uConst) {
        Left->Use.Const.lInteger -= Right->Use.Const.lInteger;
        ExprCleanUp(Right);
        return Left;
    }

    NewType = ExprResultingType(Left->pType, Right->pType);
    Left = ExprMakeCastNode(NewType, Left);
    Right = ExprMakeCastNode(NewType, Right);
    return NewBinary(NewType, binSub, Left, Right);

}

static TPExprNode Bmul (TPExprNode Left, TPExprNode Right) {
    TPDeclSpec NewType;
    if (!IsSimple(Left->pType) || !IsSimple(Right->pType)) {
            Error(ERROR0, "Multiplication of non-simple types is not possible.");
            return Left;
    }

    NewType = ExprResultingType(Left->pType,Right->pType);
    
    if (Left->Usage == uConst && Right->Usage == uConst) {
        Left->Use.Const.lInteger   *= Right->Use.Const.lInteger;
        Left->pType = NewType;
        ExprCleanUp(Right);
        return Left;
    } 

    Left    = ExprMakeCastNode(NewType,Left);
    Right   = ExprMakeCastNode(NewType,Right);
    return NewBinary(NewType, binMul, Left, Right);
 }

static TPExprNode Bdiv (TPExprNode Left, TPExprNode Right) {
    TPDeclSpec NewType;
    if (!IsSimple(Left->pType) || !IsSimple(Right->pType)) {
            Error(ERROR0, "Division of non-simple types is not possible.");
            return Left;
    }
    if (Left->Usage == uConst && Right->Usage == uConst) {
        if (Right->Use.Const.lInteger == 0) {
            Error(ERROR1, "Division by zero.");
            Left->Use.Const.lInteger = -1;
            return Left;
        }
        Left->Use.Const.lInteger /= Right->Use.Const.lInteger;
        ExprCleanUp(Right);
        return Left;
    } 

    NewType = ExprResultingType(Left->pType,Right->pType);
    Left    = ExprMakeCastNode(NewType,Left);
    Right   = ExprMakeCastNode(NewType,Right);
    return NewBinary(NewType, binDiv,Left,Right);
 }


static TPExprNode Bmod (TPExprNode Left, TPExprNode Right) {
    TPDeclSpec NewType;
    if (!IsSimple(Left->pType) || !IsSimple(Right->pType)) {
            Error(ERROR0, "Modulus of non-simple types is not possible.");
            return Left;
    }
    if (Left->Usage == uConst && Right->Usage == uConst) {
        Left->Use.Const.lInteger %= Right->Use.Const.lInteger;
        ExprCleanUp(Right);
        return Left;
    } 

    NewType = ExprResultingType(Left->pType,Right->pType);
    Left    = ExprMakeCastNode(NewType,Left);
    Right   = ExprMakeCastNode(NewType,Right);
    return NewBinary(NewType, binMod,Left,Right);
 }


static TPExprNode Bband(TPExprNode Left, TPExprNode Right) {
    TPDeclSpec NewType;
    if (!IsSimple(Left->pType) || !IsSimple(Right->pType)) {
            Error(ERROR0, "Bitwise-And of non-simple types is not possible.");
            return Left;
    }
    if (Left->Usage == uConst && Right->Usage == uConst) {
        Left->Use.Const.lInteger &= Right->Use.Const.lInteger;
        ExprCleanUp(Right);
        return Left;
    } else {
#pragma message("Optimize And")
        NewType = ExprResultingType(Left->pType,Right->pType);
        Left    = ExprMakeCastNode(NewType,Left);
        Right   = ExprMakeCastNode(NewType,Right);
        return NewBinary(NewType, binAnd,Left,Right);
    }
 }

static TPExprNode Bbor (TPExprNode Left, TPExprNode Right) {
    TPDeclSpec NewType;
    if (!IsSimple(Left->pType) || !IsSimple(Right->pType)) {
            Error(ERROR0, "Bitwise-Or of non-simple types is not possible.");
            return Left;
    }
    if (Left->Usage == uConst && Right->Usage == uConst) {
        Left->Use.Const.lInteger |= Right->Use.Const.lInteger;
        ExprCleanUp(Right);
        return Left;
    } else {
#pragma message("Optimize Or")
        NewType = ExprResultingType(Left->pType,Right->pType);
        Left    = ExprMakeCastNode(NewType,Left);
        Right   = ExprMakeCastNode(NewType,Right);
        return NewBinary(NewType, binOr,Left,Right);
    }
 }

static TPExprNode Bbxor(TPExprNode Left, TPExprNode Right) {
    TPDeclSpec NewType;
    if (!IsSimple(Left->pType) || !IsSimple(Right->pType)) {
            Error(ERROR0, "Bitwise-Xor of non-simple types is not possible.");
            return Left;
    }
    if (Left->Usage == uConst && Right->Usage == uConst) {
        Left->Use.Const.lInteger ^= Right->Use.Const.lInteger;
        ExprCleanUp(Right);
        return Left;
    } else {
#pragma message("Optimize Xor")
        NewType = ExprResultingType(Left->pType,Right->pType);
        Left    = ExprMakeCastNode(NewType,Left);
        Right   = ExprMakeCastNode(NewType,Right);
        return NewBinary(NewType, binXor,Left,Right);
    }
 }

static TPExprNode Bbsr (TPExprNode Left, TPExprNode Right) {
    if (!IsSimple(Left->pType) || !IsSimple(Right->pType)) {
            Error(ERROR0, "Shift-Right of non-simple types is not possible.");
            return Left;
    }
    if (Left->Usage == uConst && Right->Usage == uConst) {
        Left->Use.Const.lInteger >>= Right->Use.Const.lInteger;
        ExprCleanUp(Right);
        return Left;
    } else {
        return NewBinary(Left->pType, binShr,Left,Right);
    }
 }

static TPExprNode Bbsl (TPExprNode Left, TPExprNode Right) {
    if (!IsSimple(Left->pType) || !IsSimple(Right->pType)) {
            Error(ERROR0, "Shift-Left of non-simple types is not possible.");
            return Left;
    }
    if (Left->Usage == uConst && Right->Usage == uConst) {
        Left->Use.Const.lInteger <<= Right->Use.Const.lInteger;
        ExprCleanUp(Right);
        return Left;
    } else {
        return NewBinary(Left->pType, binShl,Left,Right);
    }
 }

static TPExprNode
Bceq (TPExprNode Left, TPExprNode Right) {
    TPDeclSpec NewType;
    if (IsStruct(Left->pType)  || IsStruct(Right->pType)) {
        Error(ERROR0, "Comparison of structures is not possible.");                                           
        return Left;
    }                                                                                                      
    if ((IsReference(Left->pType)  && IsSimple(Right->pType)) ||                                             
        (IsSimple(Left->pType)     && IsReference(Right->pType))) {                                          
            Error(ERROR0, "Comparison a reference to a non-reference is not possible.");                     
            return Left;
    }

    if ((Left->pType->Usage == DecPtr) && (Right->pType->Usage == DecPtr)) {                // ptr : prt  => Only == is possible
        NewType = Left->pType;
    }
    else {
        NewType = ExprResultingType(Left->pType, Right->pType);
    }
    
    Left = ExprMakeCastNode(NewType, Left);
    Right = ExprMakeCastNode(NewType, Right);

    NewType = NewSpecType(TypeBOOL, NULL);
    return NewBinary(NewType, binCEQ, Left, Right);
}

static TPExprNode
Bcne (TPExprNode Left, TPExprNode Right) {
    TPDeclSpec NewType;
    if (IsStruct(Left->pType)  || IsStruct(Right->pType)) {
        Error(ERROR0, "Comparison of structures is not possible.");
        return Left;
    }
    if ((IsReference(Left->pType)  && IsSimple(Right->pType)) ||
        (IsSimple(Left->pType)     && IsReference(Right->pType))) {
            Error(ERROR0, "Comparison a reference to a non-reference is not possible.");
            return Left;
    }

    if ((Left->pType->Usage == DecPtr) && (Right->pType->Usage == DecPtr)) {                // ptr : prt   != is possible
        NewType = Left->pType;
    }
    else {
        NewType = ExprResultingType(Left->pType, Right->pType);
    }

    Left = ExprMakeCastNode(NewType, Left);
    Right = ExprMakeCastNode(NewType, Right);

    NewType = NewSpecType(TypeBOOL, NULL);
    return NewBinary(NewType, binCNE, Left, Right);
}                                                                                                          

static TPExprNode
Bclt (TPExprNode Left, TPExprNode Right) {
    TPDeclSpec NewType;
    if (IsStruct(Left->pType)  || IsStruct(Right->pType)) {                                              
       Error(ERROR0, "Comparison of structures is not possible.");                                       
        return Left;                                                                                     
    }                                                                                                    
    if ((IsReference(Left->pType)  && IsSimple(Right->pType)) ||                                         
        (IsSimple(Left->pType)     && IsReference(Right->pType))) {                                      
            Error(ERROR0, "Comparison a reference to a non-reference is not possible.");                 
            return Left;                                                                                 
    }                                                                                                    

    if ((Left->pType->Usage == DecPtr) && (Right->pType->Usage == DecPtr)) {                // ptr : prt   < is possible
        NewType = Left->pType;
    }
    else {
        NewType = ExprResultingType(Left->pType, Right->pType);
    }

    Left = ExprMakeCastNode(NewType, Left);
    Right = ExprMakeCastNode(NewType, Right);
    
    NewType = NewSpecType(TypeBOOL, NULL);
    return NewBinary(NewType, binCLT, Left, Right);
}                                                                                                          

static TPExprNode
Bcle (TPExprNode Left, TPExprNode Right) {
    TPDeclSpec NewType;
    if (IsStruct(Left->pType)  || IsStruct(Right->pType)) {                                                
        Error(ERROR0, "Comparison of structures is not possible.");                                        
        return Left;                                                                                       
    }                                                                                                      
    if ((IsReference(Left->pType)  && IsSimple(Right->pType)) ||                                           
        (IsSimple(Left->pType)     && IsReference(Right->pType))) {                                        
            Error(ERROR0, "Comparison a reference to a non-reference is not possible.");                   
            return Left;                                                                                   
    }                                                                                                      

    if ((Left->pType->Usage == DecPtr) && (Right->pType->Usage == DecPtr)) {                // ptr : prt   <= is possible
        NewType = Left->pType;
    }
    else {
        NewType = ExprResultingType(Left->pType, Right->pType);
    }

    Left = ExprMakeCastNode(NewType, Left);
    Right = ExprMakeCastNode(NewType, Right);

    NewType = NewSpecType(TypeBOOL, NULL);
    return NewBinary(NewType, binCLE, Left, Right);
}                                                                                                        

static TPExprNode
Bcgt (TPExprNode Left, TPExprNode Right) {
    TPDeclSpec NewType;
    if (IsStruct(Left->pType)  || IsStruct(Right->pType)) {                                              
       Error(ERROR0, "Comparison of structures is not possible.");                                       
        return Left;                                                                                     
    }                                                                                                    
    if ((IsReference(Left->pType)  && IsSimple(Right->pType)) ||                                         
        (IsSimple(Left->pType)     && IsReference(Right->pType))) {                                      
            Error(ERROR0, "Comparison a reference to a non-reference is not possible.");                 
            return Left;                                                                                 
    }                                                                                                    

    if ((Left->pType->Usage == DecPtr) && (Right->pType->Usage == DecPtr)) {                // ptr : prt   > is possible
        NewType = Left->pType;
    }
    else {
        NewType = ExprResultingType(Left->pType, Right->pType);
    }

    Left = ExprMakeCastNode(NewType, Left);
    Right = ExprMakeCastNode(NewType, Right);

    NewType = NewSpecType(TypeBOOL, NULL);
    return NewBinary(NewType, binCGT, Left, Right);
}                                                                                                         

static TPExprNode
Bcge (TPExprNode Left, TPExprNode Right) {
    TPDeclSpec NewType;
    if (IsStruct(Left->pType)  || IsStruct(Right->pType)) {                                               
       Error(ERROR0, "Comparison of structures is not possible.\n","");                                   
        return Left;                                                                                      
    }                                                                                                     
    if ((IsReference(Left->pType)  && IsSimple(Right->pType)) ||                                          
        (IsSimple(Left->pType)     && IsReference(Right->pType))) {                                       
            Error(ERROR0, "Comparison a reference to a non-reference is not possible.");                  
            return Left;                                                                                  
    }                                                                                                     

    if ((Left->pType->Usage == DecPtr) && (Right->pType->Usage == DecPtr)) {                // ptr : prt   >= is possible
        NewType = Left->pType;
    }
    else {
        NewType = ExprResultingType(Left->pType, Right->pType);
    }

    Left = ExprMakeCastNode(NewType, Left);
    Right = ExprMakeCastNode(NewType, Right);

    NewType = NewSpecType(TypeBOOL, NULL);
    return NewBinary(NewType, binCGE, Left, Right);
}                                                                                                     



static TPExprNode
Bland(TPExprNode Left, TPExprNode Right) {
    TPDeclSpec NewType;
    if (IsStruct(Left->pType)  || IsStruct(Right->pType)) {                                           
       Error(ERROR0, "Logical Operations on structures is not possible.");                            
        return Left;                                                                                  
    }                                                                                                 
    if (Left->Usage == uConst && Right->Usage == uConst) {
        Left->Use.Const.lInteger = Left->Use.Const.lInteger && Right->Use.Const.lInteger;
        Left->pType->Use.DecSpec.Type = TypeBOOL;
        ExprCleanUp(Right);
        return Left;
    } else {
        NewType = NewSpecType(TypeBOOL, NULL);
        return NewBinary(NewType, binLAnd, ExprMakeCastNode(NewType, Left), ExprMakeCastNode(NewType, Right));
    }
}                                                                                                          

static TPExprNode
Blor (TPExprNode Left, TPExprNode Right) {
    TPDeclSpec NewType;
    if (IsStruct(Left->pType)  || IsStruct(Right->pType)) {                                                
       Error(ERROR0, "Logical Operations on structures is not possible.");                                 
        return Left;                                                                                       
    }                                                                                                      
    if (Left->Usage == uConst && Right->Usage == uConst) {
        Left->Use.Const.lInteger = Left->Use.Const.lInteger || Right->Use.Const.lInteger;
        Left->pType->Use.DecSpec.Type = TypeBOOL;
        ExprCleanUp(Right);
        return Left;
    } else {
        NewType = NewSpecType(TypeBOOL, NULL);
        return NewBinary(NewType, binLOr, ExprMakeCastNode(NewType, Left), ExprMakeCastNode(NewType, Right));
    }
}


TPExprNode
ExprMakeBinaryNode(TIdExprBiOp Op, TPExprNode Left, TPExprNode Right) {
    switch (Op) {
        case    binAdd:    return Badd (Left,Right);
        case    binSub:    return Bsub (Left,Right);
        case    binMul:    return Bmul (Left,Right);
        case    binDiv:    return Bdiv (Left,Right);
        case    binMod:    return Bmod (Left,Right);
        case    binAnd:    return Bband(Left,Right);
        case    binOr:     return Bbor (Left,Right);
        case    binXor:    return Bbxor(Left,Right);
        case    binCEQ:    return Bceq (Left,Right);
        case    binCNE:    return Bcne (Left,Right);
        case    binCLT:    return Bclt (Left,Right);
        case    binCLE:    return Bcle (Left,Right);
        case    binCGT:    return Bcgt (Left,Right);
        case    binCGE:    return Bcge (Left,Right);
        case    binLAnd:   return Bland(Left,Right);
        case    binLOr:    return Blor (Left,Right);
        case    binShr:    return Bbsr (Left,Right);
        case    binShl:    return Bbsl (Left,Right);
        default:        Error(FATAL, "MakeBinaryNode: UnKnown Binary Operator %d\n", Op);
                        return Left;
    }
 }



/* ************************************************** */
/*  Ternary  */
/* ********* */

TPExprNode
TernaryCondExp(TPExprNode First, TPExprNode Second, TPExprNode Third) {
    TPExprNode New;
    if (First->Usage == uConst) {
        if (First->Use.Const.lInteger) {
            ExprCleanUp(First);
            ExprCleanUp(Third);
            return Second;
        } else {
            ExprCleanUp(First);
            ExprCleanUp(Second);
            return Third;
        }
    }

    New = NewExprNode(uTernary);
    New->pType = ExprResultingType(Second->pType,Third->pType);
    New->Use.Ternary.Op     = CondExp;
    New->Use.Ternary.pFirst  = ExprMakeCastNode(NewSpecType(TypeBOOL, NULL), First);
    New->Use.Ternary.pSecond = ExprMakeCastNode(New->pType,Second);
    New->Use.Ternary.pThird  = ExprMakeCastNode(New->pType,Third);
    return New;
 }

TPExprNode
ExprMakeTernaryNode(TIdExprTriOp Op,  TPExprNode First, TPExprNode Second, TPExprNode Third) {
    switch (Op) {
        case  CondExp:  return TernaryCondExp(First,Second,Third);
                        break;
        default:        Error(FATAL, "MakeTernaryNode: UnKnown Ternary Operator %d\n", Op);
                        return First;
    }
}



/* *************************************************************************** */
/*  Action Nodes                                                               */
/*  need some run time action to be performed in order to determin the result  */
/* *************************************************************************** */


    

TPExprNode ExprMakeDotNode(TPExprNode pLeft,  LPSTR pszField) {
    TPExprNode pNode;
    TPExprNode pRight;
    TPDeclSpec pFieldType;

    //GenExpressionPrettyPrint(0, pLeft);


    int iOffset;
    if (!IsStruct(pLeft->pType)) {
        Error(ERROR0, "Dot expected to be preceeded by a Struct/Union.");
        return pLeft;
    }

    TPStructSet pStruct = pLeft->pType->Use.DecSpec.pPtr;

    ASSERT(pLeft->pType->Usage == DecSpec);
    iOffset = CalcStructElementOffset(pStruct, pszField);
    if (iOffset < 0) {
        Error(ERROR0, "Unknown struct/union field '%s'.",pszField);
        return pLeft;
    }
    pFieldType = CalcStructElementType(pStruct, pszField);                                          // a.b  ==> *((&a)+offsetof(b))

    pRight = ExprMakeConstI(iOffset);                                                               // offsetof(b)
    //GenExpressionPrettyPrint(0, pRight);

    pRight = ExprMakeCastNode(NewSpecType(TypeSIGNED | TypeSHORT, NULL), pRight);                   // offsetof(b)
    //GenExpressionPrettyPrint(0, pRight);

    pNode = UAddr(pLeft);                                                                           // (&a)
    //GenExpressionPrettyPrint(0, pNode);

    pNode = NewBinary(NewPointer(NULL, pFieldType), binAdd, pNode, pRight);                         // ((&a) + offset(b))
    //GenExpressionPrettyPrint(0, pNode);

    pNode =  UPtr(pNode);                                                                           // *((&a) + offset(b))
    //GenExpressionPrettyPrint(0, pNode);
    
    return pNode;


    // New = NewExprNode(uDot);
    // New->pType = CalcStructElementType(pLeft->pType->Use.DecSpec.pPtr, pszField);
    // New->Use.Dot.pRecord = pLeft;
    // New->Use.Dot.pszField  = pszField;
    // New->Use.Dot.iOffset = iOffset;
    // return New;  
}

TPExprNode
ExprMakeArrowNode(TPExprNode pLeft,  LPSTR pszField) {
    TPExprNode pNode;
    TPExprNode pRight;
    TPDeclSpec pFieldType;
    
    int iOffset;
    if (!IsPtrStruct(pLeft->pType)) {
        Error(ERROR0, "Arrow expected to be preceeded by a Pointer to Struct/Union.");
        return pLeft;
    }
    ASSERT(pLeft->pType->Usage == DecPtr);
    ASSERT(pLeft->pType->Use.DecPtr.pTarget && pLeft->pType->Use.DecPtr.pTarget->Usage == DecSpec);

    iOffset = CalcStructElementOffset(pLeft->pType->Use.DecPtr.pTarget->Use.DecSpec.pPtr, pszField);
    if (iOffset < 0) {
        Error(ERROR0, "Unknown struct/union field '%s'.", pszField);
        return pLeft;
    }


    pFieldType = CalcStructElementType(pLeft->pType->Use.DecPtr.pTarget->Use.DecSpec.pPtr, pszField);           // a->b ==>  *((@a)+offsetof(b))

    pRight = ExprMakeConstI(iOffset);                                                                           // offsetof(b)
    //GenExpressionPrettyPrint(0, pRight);

    pRight = ExprMakeCastNode(NewSpecType(TypeSIGNED | TypeSHORT, NULL), pRight);                               // offsetof(b)
    //GenExpressionPrettyPrint(0, pRight);

    pNode = NewBinary(NewPointer(NULL, pFieldType), binAdd, pLeft, pRight);                                     // ((@a) + offset(b))
    //GenExpressionPrettyPrint(0, pNode);

    pNode = UPtr(pNode);                                                                                        // *((&a) + offset(b))
    //GenExpressionPrettyPrint(0, pNode);

    return pNode;


    // New = NewExprNode(uArrow);
    // New->pType = CalcStructElementType(Left->pType->Use.DecPtr.pTarget->Use.DecSpec.pPtr, Field);
    // New->Use.Arrow.pRecord = Left;
    // New->Use.Arrow.pszField  = Field;
    // New->Use.Arrow.iOffset = iOffset;
    // return New;  
}


TPExprNode ExprMakeArrayNode(TPExprNode Vec,  TPExprNode Ind) {

    if (!IsReference(Vec->pType) && IsSimple(Ind->pType)) {
        Error(ERROR0, "Reference expected before [...].");
        return Vec;
    }

    TPExprNode Right;
    if (IsPointer(Vec->pType)) {
        Right = Bmul(Ind, ExprMakeConstI(CalcSizeOf(Vec->pType->Use.DecPtr.pTarget))); //    or simple * size of array element.
        Right = ExprMakeCastNode(NewSpecType(TypeSIGNED | TypeSHORT, NULL), Right);
        return UPtr(NewBinary(Vec->pType, binAdd, Vec, Right));
    }

    if (IsArray(Vec->pType)) {
        Right = Bmul(Ind, ExprMakeConstI(CalcSizeOf(Vec->pType->Use.DecArray.pTarget))); //    or simple * size of array element.
        Right = ExprMakeCastNode(NewSpecType(TypeSIGNED | TypeSHORT, NULL), Right);
        return UPtr(NewBinary(NewPointer(NULL, Vec->pType->Use.DecArray.pTarget), binAdd, UAddr(Vec), Right));

    }
    Error(FATAL, "ExprMakeArrayNode: This can't happen!");
    return NULL;

 }


 TPExprNode ExprMakeFuncNode(TPExprNode pFunc, TPExprNode pParams) {
    TPExprNode pNew;
    TPDeclSpec pDefnParameterList;
    TPDeclSpec pDpl;
    //LPSTR      pszIdentifier;
    
    pNew = NewExprNode(uFunc);

    if (IsFunc(pFunc->pType)) {
        //pszIdentifier = pFunc->Use.Var.pszIdentifier;
        pDefnParameterList = pFunc->pType->Use.DecFunc.pPList;
        pNew->pType = pFunc->pType->Use.DecFunc.pReturnType;
    }
    else if (IsPointer(pFunc->pType) && IsFunc(pFunc->pType->Use.DecPtr.pTarget)) {
        //pszIdentifier = "";
        pDefnParameterList = pFunc->pType->Use.DecPtr.pTarget->Use.DecFunc.pPList;
        pNew->pType = pFunc->pType->Use.DecPtr.pTarget->Use.DecFunc.pReturnType;
    }
    else {
         Error(ERROR0, "Function expected before (...).");
         return pFunc;
    }
    pNew->Use.Func.pFunc = pFunc;                  // Funky !
    pNew->Use.Func.pParams = pParams;


     BOOL fElipsis = FALSE;

     TPExprNode pInvokationParameterList = pParams;                                                                                                     // Count the caller's parameters.
     int iCallParameters;                                                                                                                               //        
     for (iCallParameters = 0; pInvokationParameterList != NULL; iCallParameters++, pInvokationParameterList = pInvokationParameterList->pPreviousArg); //

     int        iDefnParamaters;
     
     iDefnParamaters = 0;                                                                                                                               //
     pDpl = pDefnParameterList;                                                                                                                         // Count the expected parameters
     for (; pDpl != NULL; iDefnParamaters++, pDpl = pDpl->Use.DecId.pBrother) {                                                                         //
         if ((pDpl->Use.DecId.pTarget->Usage == DecSpec) &&                                                                                             //
             (pDpl->Use.DecId.pTarget->Use.DecSpec.Type == TypeVOID)) {                                                                                 // void is special case 1 param expecting zero!
             if (!(iDefnParamaters == 0 && pDpl->Use.DecId.pBrother == NULL)) {                                                                         // void  should be the only parameter if the grammar works OK
                Error(ERROR0, "Compiler internal logic is screwed.");                                                                                   //
             }                                                                                                                                          //
             break;                                                                                                                                     //
         }                                                                                                                                              //
         if (strcmp(pDpl->Use.DecId.pszName, "...") == 0) {                                                                                             //
             fElipsis |= (strcmp(pDpl->Use.DecId.pszName, "...") == 0);                                                                                 //
             iDefnParamaters--;                                                                                                                         //
         }                                                                                                                                              //
     }                                                                                                                                                  //

     if (iDefnParamaters > iCallParameters) {                                                                                                           // Error too few
         Error(ERROR0, "Function expects %d parameter%s. This invocation has %d.", iDefnParamaters, (iDefnParamaters==1)?"":"s", iCallParameters);      //
         return pNew;                                                                                                                                   //
     }                                                                                                                                                  //

     if (iCallParameters > iDefnParamaters) {
         if (!fElipsis) {
             Error(ERROR0, "Function expects %d parameter%s. This invocation has %d.", iDefnParamaters, (iDefnParamaters == 1) ? "" : "s", iCallParameters);
         }
     }

     TPExprNode *ppInvokationParameterList;
     ppInvokationParameterList = &pNew->Use.Func.pParams;

      while (iCallParameters > iDefnParamaters) {                                                                                                   // skip over the excess parameters.
          ppInvokationParameterList = &(*ppInvokationParameterList)->pPreviousArg;
          iCallParameters--;
      }

      pDpl = pDefnParameterList;                                                                                                                    // formal defn parameters. used to ensure type compliance of each parameter.
      if (fElipsis) {                                                                                                                               // elipise can be ignored.
          pDpl = pDpl->Use.DecId.pBrother;                                                                                                          //      so cut it off here if we have it..
      }                                                                                                                                             //

      while (iCallParameters > 0) {                                                                                                                 // ensure type compliance for the remaining parameters.
          ASSERT(pDpl->Usage == DecId);                                                                                                             //
          ASSERT(pDpl->Use.DecId.pTarget);                                                                                                          //
                                                                                                                                                    //
          TPExprNode pNext = (*ppInvokationParameterList)->pPreviousArg;                                                                            // cater for insertion of a cast here.
          (*ppInvokationParameterList)->pPreviousArg = NULL;                                                                                        //
          (*ppInvokationParameterList) = ExprMakeCastNode(pDpl->Use.DecId.pTarget, (*ppInvokationParameterList));                                   //
          (*ppInvokationParameterList)->pPreviousArg = pNext;                                                                                       //
                                                                                                                                                    //
          ppInvokationParameterList = &(*ppInvokationParameterList)->pPreviousArg;                                                                  // Move on to next 
          pDpl = pDpl->Use.DecId.pBrother;                                                                                                          //
          iCallParameters--;                                                                                                                        //
      }                                                                                                                                             //

     return pNew;
 }


 /* ************************************************** */
 /*  Assignment */
 /* *********** */
 TPExprNode  ExprMakeAssignNode(TIdExprBiOp Op, TPExprNode Lval, TPExprNode Rval) {
     TPExprNode New;

     if (IsTypeQualifierConst(Lval->pType)) {
         Error(WARNING1, "Assignment to const will fail. Don't do it.");
         return Rval;
     }

     if ((Lval->pType->Usage != DecSpec) && (Lval->pType->Usage != DecPtr)) {          // assignee must be base type of somthing we point at.
         Error(WARNING1, "This assignment is not to a variable or de-referenced pointer.");
         return Rval;
     }

     New = NewExprNode(uAssign);
     New->pType = Lval->pType;
     New->Use.Assign.Op = Op;
     New->Use.Assign.pLval = Lval;
     New->Use.Assign.pRval = ExprMakeCastNode(Lval->pType, Rval);                                   // arithmetic preserves the target's type.
     return New;
 }

 /* ************************************************** */
 /*  Cast  */
 /* ****** */
 LONG ExprTypeConvertConst(TPDeclSpec NewType, TPDeclSpec OldType, LONG Const) {
     WORD SzOld, SzNew;
     if (IsStruct(NewType) || IsStruct(OldType)) {
         Error(ERROR0, "Casting to/from struct is not possible.");
         return 0L;
     }
     SzOld = (WORD)CalcSizeOf(OldType);
     SzNew = (WORD)CalcSizeOf(NewType);
     if (IsReference(NewType) && IsReference(OldType) && (SzOld != SzNew)) {
         Error(WARNING0, "Conversion between near & far pointers.");
     }
     if (!(IsReference(NewType) || IsReference(OldType))) {
         if (SzNew > SzOld) {                                            // Cast up
             if (OldType->Use.DecSpec.Type & TypeUNSIGNED) {
                 switch (SzOld) {                                        // Cast up Unsigned
                 case 1: Const &= 0x000000ff; break;
                 case 2: Const &= 0x0000ffff; break;
                 case 3: Const &= 0x00ffffff; break;
                 case 4: Const &= 0xffffffff; break;
                 default: Error(ERROR0, "Casting unsigned constant from an unsupported size.");
                 }
             }
             else {                                                    // Cast up signed
                 switch (SzOld) {
                 case 1: if (Const & 0x00000080) Const |= 0xffffff00; else Const &= 0x000000ff; break;
                 case 2: if (Const & 0x00008000) Const |= 0xffff0000; else Const &= 0x0000ffff; break;
                 case 3: if (Const & 0x00800000) Const |= 0xff000000; else Const &= 0x00ffffff; break;
                 case 4: if (Const & 0x80000080) Const |= 0x00000000; else Const &= 0xffffffff; break;
                 default: Error(ERROR0, "Casting signed constant from an unsupported size.");
                 }
             }
         }
         else if (IsBoolean(NewType)) {  // size eqal or shorter. Normally we would just truncate but BOOL is a special case.
             switch (SzOld) {
             case 1: Const = (Const & 0x000000ff) ? 1 : 0; break;
             case 2: Const = (Const & 0x0000ffff) ? 1 : 0; break;
             case 3: Const = (Const & 0x00ffffff) ? 1 : 0; break;
             case 4: Const = (Const & 0xffffffff) ? 1 : 0; break;
             default: Error(ERROR0, "Casting signed constant from an unsupported size.");
             }
         }
     }
//     switch (SzNew) {
//     case 1: Const &= 0x000000ff; break;
//     case 2: Const &= 0x0000ffff; break;
//     case 3: Const &= 0x00ffffff; break;
//     case 4: Const &= 0xffffffff; break;
//     default: Error(ERROR0, "Casting constant to an unsupported size.");
//     }
     return Const;
 }

 static BOOL CompatibleTypes(TPDeclSpec pType1, TPDeclSpec pType2) {            // TRUE if no cast is needed. FALSE if cast is required.
     ASSERT(pType1);
     ASSERT(pType2);

     if ((pType1->Usage == DecSpec) && (pType1->Use.DecSpec.Type == TypeVOID))  {                                          // cast to void. do nothing.
         return TRUE;
     }
     if  ((pType2->Usage == DecSpec) && (pType2->Use.DecSpec.Type == TypeVOID)) {                                          // cast from void is not possib;e
         Error(ERROR1, "CompatibleTypes(): Arithmetic on a void value is impossible");
         return FALSE;
     }
     if ((pType1->Usage == DecSpec) && (pType2->Usage == DecSpec)) {                                                        // Both basic types
         if (pType1->Use.DecSpec.Type == pType2->Use.DecSpec.Type) {                                                        //      perfect match
             return TRUE;
         }
         if (((pType1->Use.DecSpec.Type & TypeUNSIGNED) ^ (pType2->Use.DecSpec.Type&TypeUNSIGNED)) == TypeUNSIGNED) {       //      one SIGNED one UNSIGNED
             //Error(WARNING0, "CompatibleTypes(): Arithmetic with Signed & Unsigned inputs");
             return FALSE;
         }
         if (((pType1->Use.DecSpec.Type | pType2->Use.DecSpec.Type) & (TypeSHORT | TypeINT)) == (TypeSHORT | TypeINT)) {    //      INT & SHORT are the same.
             return TRUE;
         }
         if (((pType1->Use.DecSpec.Type | pType2->Use.DecSpec.Type) & (TypeFLOAT | TypeDOUBLE)) != 0) {                     //      unsuported type
             Error(ERROR0, "CompatibleTypes(): float and double are not suported (yet)");
             return FALSE;
         }
     }
     return FALSE;                                                                                                          //      cast will be needed.
}


TPExprNode ExprMakeCastNode(TPDeclSpec pType, TPExprNode pNode) {
    TPExprNode New = NULL;

    ASSERT(pType && ((pType->Usage == DecSpec) || (pType->Usage == DecPtr)));

    if (pNode->Usage == uConst) {                                                                           // for constants we can do it on the spot/
        pNode->Use.Const.lInteger = ExprTypeConvertConst(pType, pNode->pType, pNode->Use.Const.lInteger);   // tweak the data.
        pNode->pType = pType;                                                                               // redefine its type.
        return pNode;                                                                                       //
    } 

    if (CompatibleTypes(pType, pNode->pType)) {                                                             // if it's compatible (e.g. int and short)
#pragma message ("    **** should we change the node's type here?")                                         //
        return pNode;                                                                                       //      there's nothing to do...
    }                                                                                                       //

    if ((pType->Usage == DecPtr) && 
        ((pNode->pType->Usage == DecArray)) || (pNode->pType->Usage == DecFunc)) {
            pNode = NewUnary(unAddr, pNode);
            pNode->pType = pType;
    }



    DWORD dwSizeNew = CalcSizeOf(pType);                                                            
    DWORD dwSizeOld = CalcSizeOf(pNode->pType);

     if (IsBoolean(pType)) {                                                     // special case BOOL. we want a 'to bool' cast node even when char is the input.
        New = NewExprNode(uCast);                                               //          to bool/flag
        New->pType = pType;
        New->Use.Cast.pTarget = pNode;
        switch (dwSizeOld) {
            case 1: New->Use.Cast.Op = Cast_b2f; break;
            case 2: New->Use.Cast.Op = Cast_s2f; break;
            case 4: New->Use.Cast.Op = Cast_l2f; break;                         //
        default:  Error(FATAL, "ExprMakeCastNode(); something silly to flag");  //          to trouble
        }
        return New;
    }

    if (dwSizeNew == dwSizeOld) {                                               // ** size not changing **
        pNode->pType = pType;                                                   //      change the type but no action needed.
        return pNode;                                                           //      no action
    }                                                                           //


    if (dwSizeNew > dwSizeOld) {                                                // ** Increasing **
        if (IsSigned(pNode->pType)) {                                           //
            if (dwSizeOld == 1) {                                               //      from Char
                switch (dwSizeNew) {                                            //
                case 2: New = NewExprNode(uCast);                               //          to short
                        New->Use.Cast.Op = Cast_c2s;                            //
                        break;                                                  //
                case 4: New = NewExprNode(uCast);                               //          to long
                        New->Use.Cast.Op = Cast_c2l;                            //
                        break;                                                  //
                default:                                                        //
                    Error(FATAL, "ExprMakeCastNode(); s8 to something silly");  //          to trouble
                }                                                               //
            }                                                                   //
            else if (dwSizeOld == 2) {                                          //      from Short
                switch (dwSizeNew) {                                            //
                case 4: New = NewExprNode(uCast);                               //          to long
                    New->Use.Cast.Op = Cast_s2l;                                //
                    break;                                                      //
                default:                                                        //
                    Error(FATAL, "ExprMakeCastNode(); s16 to something silly"); //          to trouble
                }                                                               //
            }                                                                   //
            else {                                                              //      from problem
                Error(FATAL, "ExprMakeCastNode(); from something silly");       //
            }                                                                   //
        }                                                                       //
        else {                                                                  //
            if (dwSizeOld == 1) {                                               //      from unsigned char
                switch (dwSizeNew) {                                            //
                case 2: New = NewExprNode(uCast);                               //          to short
                        New->Use.Cast.Op = Cast_b2s;                            //
                        break;                                                  //
                case 4: New = NewExprNode(uCast);                               //          to long
                        New->Use.Cast.Op = Cast_b2l;                            //
                        break;                                                  //
                default:                                                        //
                    Error(FATAL, "ExprMakeCastNode(); u8 to something silly");  //          to trouble
                }                                                               //
            }                                                                   //
            else if (dwSizeOld == 2) {                                          //      from unsigned Short
                switch (dwSizeNew) {                                            //
                case 4: New = NewExprNode(uCast);                               //          to long
                        New->Use.Cast.Op = Cast_u2l;                            //
                        break;                                                  //
                default:                                                        //
                    Error(FATAL, "ExprMakeCastNode(); u16 to something silly"); //          to trouble
                }                                                               //
            }                                                                   //
            else {                                                              //
                Error(FATAL, "ExprMakeCastNode(); from something silly");       //      from unsigned problem
            }                                                                   //
        }                                                                       //
    }
    else {                                                                      // ** Shrinking **
        if (dwSizeOld == 4) {                                                   //      from long
            switch (dwSizeNew) {                                                //
            case 2: New = NewExprNode(uCast);                                   //          to short
                New->Use.Cast.Op = Cast_l2s;                                    //
                break;                                                          //
            case 1: New = NewExprNode(uCast);                                   //          to byte
                New->Use.Cast.Op = Cast_l2b;                                    //
                break;                                                          //
            default:                                                            //
                Error(FATAL, "ExprMakeCastNode(); long to something silly");    //          to trouble
            }                                                                   //
        }
        else if (dwSizeOld == 2) {                                              //      from short
            switch (dwSizeNew) {                                                //
            case 1: New = NewExprNode(uCast);                                   //          to byte
                New->Use.Cast.Op = Cast_s2b;                                    //
                break;                                                          //
            default:                                                            //
                Error(FATAL, "ExprMakeCastNode(); short to something silly");   //          to trouble
            }                                                                   //
        }                                                                       //
        else {                                                                  //
            Error(FATAL, "ExprMakeCastNode(); shrinking silly size");           //      from trouble
        }                                                                       //
    }
    ASSERT(New != NULL);
    New->pType = pType;
    New->Use.Cast.pTarget = pNode;
    return New;
    
 }


TPExprNode ExprMakeInitNode(TPExprNode pNode) {         // initializer element
    TPExprNode pNew;
    pNew = NewExprNode(uInit);
    pNew->Use.Init.pAssignment = pNode;
    //pNew->Use.Init.pSibling    = NULL;
    pNew->Use.Init.pChildren   = NULL;
    return pNew;
}

TPExprNode ExprMakeInitList(TPExprNode pNode) {         // braketed set of elements
    TPExprNode pNew;
    pNew = NewExprNode(uInit);
    pNew->Use.Init.pAssignment = NULL;
    //pNew->Use.Init.pSibling    = NULL;
    pNew->Use.Init.pChildren   = pNode;
    return pNew;
}

/*
TPExprNode ExprInitConcat(TPExprNode pNode, TPExprNode pSibling) {
    TPExprNode n;
    for (n=pNode; n->Use.Init.pSibling; n=n->Use.Init.pSibling);
    n->Use.Init.pSibling = pSibling;
    return pNode;
}
*/

TPExprNode  ExprConcat(TPExprNode pNode, TPExprNode pSibling) {     // comma separated multiple expression or an initializer list.
    TPExprNode n;
    for (n = pNode; n->pSibling; n = n->pSibling);
    n->pSibling = pSibling;
    return pNode;
}

TPExprNode  ExprConcatArgs(TPExprNode pNode, TPExprNode pArg) {     // build the function call parameter list. (reverse order; as per call evaluation)
    ASSERT(pArg->pPreviousArg == NULL);
    pArg->pPreviousArg = pNode;
    return pArg;
}


/* ****************************************************************** */

DWORD ExprConstInt(TPExprNode E) {
    if (E->Usage != uConst) {
        Error(ERROR0, "Initializer must be a Constant value.");
        return 0L;
    }
    return E->Use.Const.lInteger;
 }


/* ****************************************************************** */

void
ExprCleanUp(TPExprNode n) {
    switch (n->Usage) {
        case    uConst:
        case    uVar:       break;
        case    uUnary:     ExprCleanUp(n->Use.Unary.pOperand);
                            break;
        case    uBinary:    ExprCleanUp(n->Use.Binary.pLeft);
                            ExprCleanUp(n->Use.Binary.pRight);
                            break;
        case    uTernary:   ExprCleanUp(n->Use.Ternary.pFirst);
                            ExprCleanUp(n->Use.Ternary.pSecond);
                            ExprCleanUp(n->Use.Ternary.pThird);
                            break;
        default:            Error(FATAL, "CleanUp: More to clean ! [%d]\n", n->Usage);
                            break;
    }
    Dispose(n);
}



BOOL ExprIsVarGlobal(TPExprNode pExpr) {
    ASSERT(pExpr->Usage == uVar);
    return (pExpr->Use.Var.pDecId == NULL);
}

BOOL ExprIsVarLocal(TPExprNode pExpr) {
    ASSERT(pExpr->Usage == uVar);
    return (pExpr->Use.Var.pDecId != NULL);
}




/* eof */

