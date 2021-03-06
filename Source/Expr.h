// # $URL: https://eboracum-vss.digitallocksmiths.local/svn/Dls/Sean/RoyalHolloway/CC_Avr/Source/Expr.h $
// # $Revision: 426 $


#ifndef __SKC_EXPRESSIONS_H__
#define __SKC_EXPRESSIONS_H__

#ifdef DEBUG_INCLUDE_FILES 
#pragma message("     including " __FILE__)
#endif // DEBUG_INCLUDE_FILES


/* *************** */
/* Type structures */
/* *************** */

typedef enum {      uConst,  uVar,    uUnary,  uBinary,uTernary,
                    uCast,
                    uAssign, uInit,   uArrow, uDot,
                    uArray,  uFunc,
                    uIoreg
             } ExprUsage;

typedef enum {      unMinus,  unPlus,   unNeg,    unPostInc,unPreInc,
                    unPostDec,unPreDec, unSizeOf, unAddr,   unPtr,
                    unNot
             } TIdExprUnOp;

typedef enum {      binNop,
                    binAdd,    binSub,    binMul,    binDiv,    binMod,
                    binAnd,    binOr,     binXor,    binCEQ,    binCNE,
                    binCLT,    binCLE,    binCGT,    binCGE,    binLAnd,
                    binLOr,    binShr,    binShl
             } TIdExprBiOp;


typedef enum {
    Cast_c2s, Cast_c2l, Cast_s2l, Cast_b2s, Cast_b2l, Cast_u2l, Cast_l2s, Cast_l2b, Cast_l2f, Cast_s2b, Cast_s2f, Cast_b2f
} TCast;

typedef enum {      CondExp
             } TIdExprTriOp;

//typedef enum {      AsNop,  AsAdd,  AsSub,  AsMul,  AsDiv,
//                    AsMod,  AsBAnd, AsBOr,  AsBXor, AsSR,
//                    AsSL
//             } TIdExprAssign;

typedef struct TagExprNode TExprNode;
typedef TExprNode  * TPExprNode;
struct TagExprNode {
    ExprUsage       Usage;
    TPDeclSpec      pType;
    TPExprNode      pSibling;                   // initializer list or comma separated multiple expression
    TPExprNode      pPreviousArg;               // reverse order list of function call parameters
    union {
        struct {
            LONG        lInteger;
        } Const;
        struct {
            WORD        nReg;
            LPSTR       pszName;
        } Ioreg;
        struct {
            LPSTR       pszIdentifier;          // name
            TPDeclSpec  pDecId;                 // DecId
        } Var;
        struct {
            TIdExprUnOp Op;
            TPExprNode  pOperand;
        } Unary;
        struct {
            TIdExprBiOp Op;
            TPExprNode  pLeft;
            TPExprNode  pRight;
        } Binary;
        struct {
            WORD        Op;
            TPExprNode  pFirst;
            TPExprNode  pSecond;
            TPExprNode  pThird;
        } Ternary;
        struct {
            WORD        Op;
            TPExprNode  pLval;
            TPExprNode  pRval;
        } Assign;
        struct {
            TCast       Op;
            TPExprNode  pTarget;
        } Cast;
        struct {
            TPExprNode  pAssignment;
            TPExprNode  pChildren;
        } Init;
        struct {
            TPExprNode  pRecord;
            LPSTR       pszField;       // field name
            int         iOffset;        // field offset
        } Arrow;
        struct {
            TPExprNode  pRecord;
            LPSTR       pszField;       // field name
            int         iOffset;        // field offset
        } Dot;
        struct {
            TPExprNode  pVector;
            TPExprNode  pIndex;
        } Array;
        struct {
            TPExprNode  pFunc;
            TPExprNode  pParams;
        } Func;
    } Use;
 };

#define TypeNUMERIC (TypeCHAR | TypeSHORT | TypeINT | TypeLONG | TypeSIGNED | TypeUNSIGNED)

#define IsStruct(n)    (((n)->Usage == DecSpec) &&  ((n)->Use.DecSpec.Type & TypeSTRUCT))
#define IsSimple(n)    (((n)->Usage == DecSpec) && !((n)->Use.DecSpec.Type & TypeSTRUCT))
#define IsUnsigned(n)  (((n)->Usage == DecSpec) &&  ((n)->Use.DecSpec.Type & TypeUNSIGNED))
#define IsSigned(n)    (((n)->Usage == DecSpec) && !((n)->Use.DecSpec.Type & TypeUNSIGNED))
#define IsBoolean(n)   (((n)->Usage == DecSpec) && ((n)->Use.DecSpec.Type & TypeBOOL))
#define IsPointer(n)    ((n)->Usage == DecPtr)
#define IsArray(n)      ((n)->Usage == DecArray)
#define IsFunc(n)       ((n)->Usage == DecFunc)
#define IsReference(n)  (IsPointer(n) || IsArray(n))
#define IsPtrStruct(n)  (IsPointer(n) && IsStruct((n)->Use.DecPtr.pTarget))
//#define IsNumeric(n)   (((n)->Usage == DecSpec) && ((n)->Use.DecSpec.Type & TypeNUMERIC))


LONG        ExprTypeConvertConst(TPDeclSpec NewType, TPDeclSpec OldType, LONG Const);
TPDeclSpec  ExprResultingType(TPDeclSpec pLeft, TPDeclSpec pRight);

TPExprNode  ExprMakeConstC( LONG   Value);
TPExprNode  ExprMakeConstI(LONG   Value);
TPExprNode  ExprMakeConstF( DOUBLE Value);
TPExprNode  ExprMakeConstS( LPSTR  Value);
TPExprNode  ExprMakeVar(    LPSTR  Var);
TPExprNode  ExprMakeIoReg(LONG   Value, LPSTR pszName);

TPExprNode  ExprMakeUnaryNode(  TIdExprUnOp  Op, TPExprNode Node);
TPExprNode  ExprMakeBinaryNode( TIdExprBiOp  Op, TPExprNode Left,  TPExprNode Right);
TPExprNode  ExprMakeTernaryNode(TIdExprTriOp Op, TPExprNode First, TPExprNode Second, TPExprNode Third);
TPExprNode  ExprMakeArrowNode(  TPExprNode   Left,  LPSTR Field);
TPExprNode  ExprMakeDotNode(    TPExprNode   Left,  LPSTR Field);
TPExprNode  ExprMakeArrayNode(  TPExprNode   Vec,   TPExprNode Ind);
TPExprNode  ExprMakeFuncNode(   TPExprNode   Fn,    TPExprNode Params);
TPExprNode  ExprMakeAssignNode( TIdExprBiOp  Op, TPExprNode Lval, TPExprNode Rval);
TPExprNode  ExprMakeCastNode(   TPDeclSpec Type,  TPExprNode Node);

TPExprNode  ExprMakeInitNode(TPExprNode Node);
TPExprNode  ExprMakeInitList(TPExprNode Node);
void        ExprPrintInit(TPExprNode n);

TPExprNode  ExprConcat(TPExprNode pNode, TPExprNode pSibling);      // comma expression list
TPExprNode  ExprConcatArgs(TPExprNode pNode, TPExprNode pArg);      // Function call argument comma list

DWORD       ExprConstInt(TPExprNode E);
DOUBLE      ExprConstFloat(TPExprNode E);
LPSTR       ExprConstString(TPExprNode E);

void        ExprCleanUp(TPExprNode n);

BOOL        ExprIsVarGlobal(TPExprNode pExpr);
BOOL        ExprIsVarLocal(TPExprNode pExpr);


#endif // __SKC_EXPRESSIONS_H__

/* eof */

