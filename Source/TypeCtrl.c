// # $URL: https://eboracum-vss.digitallocksmiths.local/svn/Dls/Sean/RoyalHolloway/CC_Avr/Source/TypeCtrl.c $
// # $Revision: 433 $


#include <conio.h>
#include <stdio.h>
#include <ctype.h>
#include <signal.h>
#include <setjmp.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <Windows.h>

//#include <ext\types.h>
#include "Utilities\Console.h"

#include "lex.h"
#include "typectrl.h"
#include "expr.h"
#include "Initializers.h"
#include "Statements.h"
#include "main.h"
#include "C_Yacced.tab.h"

#include "GenAvr\GenStatements.h" // for pretty print

/* *********************************************** */

/* *********************************************** */

/********************/
/* ENUM descriptors */
/********************/

TPEnumSet   Enums = NULL;

static BOOL
FindEnum(TPEnumElement El, LPSTR Name) {
    for (;El;El=El->pNext) {
        if (!strcmp(El->pszElementName, Name)) return TRUE;
    }
    return FALSE;
 }
    

TPEnumElement EnumElementFind(LPSTR pszName) {
    TPEnumSet       Set;
    TPEnumElement   El;
    for (Set=Enums; Set; Set=Set->pNext)
        for (El=Set->pElements; El; El=El->pNext)
            if (!strcmp(El->pszElementName, pszName))
                return El;
    return NULL;
 }
 
static BOOL
EnumDuplicate(LPSTR Name) {
    return (EnumElementFind(Name)) ? TRUE : FALSE;
 }

TPEnumElement EnumElementMake(LPSTR pszName, TPExprNode pExpr) {
    TPEnumElement NewEl;
    if (EnumDuplicate(pszName)) {
        Error(ERROR1, "Duplicate Enumeration Constant '%s'.", pszName);
    }
    NewEl = New(sizeof(TEnumElement));
    NewEl->pszElementName  = pszName;
    NewEl->fAssigned     = FALSE;
    if (pExpr) {
        NewEl->fAssigned = TRUE;
        NewEl->dwValue    = ExprConstInt(pExpr);
    }
    NewEl->pNext         = NULL;
    return NewEl;
 }


TPEnumElement EnumElementAdd(TPEnumElement pList, TPEnumElement pNew) {
    TPEnumElement Old = pList;
    if (FindEnum(pList, pNew->pszElementName)) {
        Error(ERROR1, "Repeated Enumeration Constant '%s'.", pNew->pszElementName);
    }
    if (!pList) {
        if (!pNew->fAssigned) pNew->dwValue = 0;
        return pNew;
    }
    for (;Old->pNext;Old = Old->pNext);
    Old->pNext = pNew;
    if (!pNew->fAssigned) pNew->dwValue = 1+Old->dwValue;
    pNew->pNext = NULL;
    return pList;
 }


void EnumElementPrintList(TPEnumElement pEl) {
    printf("[ ");
    for (;pEl;pEl=pEl->pNext) {
        printf("%s=%d%c ", pEl->pszElementName, pEl->dwValue, (pEl->pNext)?',':' ');
    }
    printf("] ");
 }

TPEnumSet
FindEnumSet(LPSTR Name) {
    TPEnumSet Set=Enums;
    if (!strcmp(Name,"")) return NULL;                          // always fail with anonimous Set
    for (;(Set && strcmp(Name,Set->pszSetName)); Set=Set->pNext) ;  // try find others
    return Set;
 }

TPEnumSet EnumSetAdd(LPSTR szName, TPEnumElement pElements) {
    TPEnumSet NewSet;
    if ((NewSet = FindEnumSet(szName)) == NULL) {                 // non existant so make new one
        NewSet = New(sizeof(TEnumSet));
        NewSet->pszSetName  = szName;
        NewSet->pElements = pElements;
        NewSet->pNext     = Enums;
        Enums = NewSet;
    } else {
        if (NewSet->pElements == NULL) {                         // first definition after a forward referance
            NewSet->pElements = pElements;
        } else {
            if (pElements != NULL) {                             // Attempted redefinition
                Error(ERROR0, "Redefinition of Enumerated Set '%s'.",szName);
            } else {
                ;                                               // backwards reference. OK ... do nowt
            }
                
        }
    }
    return NewSet;
 }


void EnumSetPrint(int iDepth, TPEnumSet pSet) {
    printf("Enum\t'%s'\t", pSet->pszSetName);
    EnumElementPrintList(pSet->pElements);
}

void EnumSetPrintList(int iDepth) {
    TPEnumSet Set=Enums;
    printf("EMUMS\n");
    for (;Set; Set=Set->pNext) {
        EnumSetPrint(iDepth+1, Set);
        printf("\n");
    }
    printf("\n");

}

/****************************/
/* STRUCT/UNION descriptors */
/****************************/

TPStructSet Structs = NULL;

TPStructSet
FindStructSet(LPSTR Name) {
    TPStructSet Set=Structs;
    if (!strcmp(Name,"")) return NULL;                          // always fail with anonimous Set
    for (;(Set && strcmp(Name,Set->szSetName)); Set=Set->pNext) ;  // try find others
    return Set;
}

TPStructSet
AddStructSet(LPSTR Name, BOOL Union, TPDeclSpec Elements) {
    TPStructSet NewSet;
    if ((NewSet = FindStructSet(Name)) == NULL) {               // non existant so make new one
        NewSet = New(sizeof(TStructSet));
        NewSet->szSetName  = Name;
        NewSet->fUnion    = Union;
        NewSet->pElements = Elements;
        NewSet->pNext     = Structs;
        Structs          = NewSet;
    } else {
        if ((NewSet->fUnion == Union) &&
            (NewSet->pElements == NULL)) {                       // first definition after a forward reference
            NewSet->pElements = Elements;
        } else {
            if (Elements != NULL) {                             // Attempted redefinition
                Error(ERROR0, "Redefinition of Struct/Union '%s'",Name);
            } else {
                ;                                               // backwards reference. OK ... do nowt
            }
                
        }
    }
    return NewSet;
}


static void
PrintStructSet(int iDepth, TPStructSet Set, BOOL Expand) {
    if (Set->fUnion) printf("Union\t");
    else            printf("Struct\t");
    printf("'%s'", Set->szSetName);
    if (Expand) {
        printf("\t{\n");
        ParseDeclSpec(iDepth+1, Set->pElements, TRUE);
        printf("}");
    }
}


void PrintStructSets(int iDepth) {
    TPStructSet Set = Structs;
    printf("STRUCTS\n");
    for (;Set;Set=Set->pNext) {
        PrintStructSet(iDepth+1, Set,TRUE);
        printf("\n");
    }
    printf("\n");
}


/* ******************************************************* */
/*  General Type Housekeeping  */
/* *************************** */

static TPDeclSpec
NewDeclSpec(TUsage Use) {
    TPDeclSpec NewEl;
    NewEl = New(sizeof(TDeclSpec));
    NewEl->Usage = Use;
    NewEl->pChain = NULL;
    return NewEl;
 }


static TPDeclSpec
NewSpecBlank(TUsage Use) {
    TPDeclSpec NewEl;
    NewEl = NewDeclSpec(Use);
    switch (Use) {
        case DecSpec:   NewEl->Use.DecSpec.Class  = 0;
                        NewEl->Use.DecSpec.Type   = 0;
                        NewEl->Use.DecSpec.wQual   = 0;
                        NewEl->Use.DecSpec.pPtr    = NULL;
                        break;
        default:        Error(FATAL, "NewSpecBlank: %d is unknown !\n",(int)Use);
                        break;
    }
    return NewEl;
 }

/* ******************************************************* */
/*  Basic Types  */
/* ************* */

static WORD
DeclClass( WORD Set, WORD Element) {
    if (Set && (Set != Element))
        Error(WARNING0, "More than one storage class specified");
    else
        Set |= Element;
    return Set;
 }




static WORD
DeclType(WORD Set, WORD Element) {
    if (((Element == TypeVOID)    && (Set & (         TypeCHAR|TypeINT|TypeFLOAT|TypeDOUBLE|TypeSIGNED|TypeUNSIGNED|TypeSHORT|TypeLONG))) ||
        ((Element == TypeCHAR)    && (Set & (TypeVOID|         TypeINT|TypeFLOAT|TypeDOUBLE                                           ))) ||
        ((Element == TypeINT)     && (Set & (TypeVOID|TypeCHAR|        TypeFLOAT|TypeDOUBLE                                           ))) ||
        ((Element == TypeFLOAT)   && (Set & (TypeVOID|TypeCHAR|TypeINT|          TypeDOUBLE|TypeSIGNED|TypeUNSIGNED|TypeSHORT|TypeLONG))) ||
        ((Element == TypeDOUBLE)  && (Set & (TypeVOID|TypeCHAR|TypeINT|TypeFLOAT|           TypeSIGNED|TypeUNSIGNED|TypeSHORT         ))) ||
        ((Element == TypeSHORT)   && (Set & (TypeVOID|TypeCHAR|        TypeFLOAT|TypeDOUBLE|                                  TypeLONG))) ||
        ((Element == TypeLONG)    && (Set & (TypeVOID|TypeCHAR|        TypeFLOAT|                                   TypeSHORT         ))) ||
        ((Element == TypeSIGNED)  && (Set & (TypeVOID|                 TypeFLOAT|TypeDOUBLE|           TypeUNSIGNED                   ))) ||
        ((Element == TypeUNSIGNED)&& (Set & (TypeVOID|                 TypeFLOAT|TypeDOUBLE|TypeSIGNED                                ))) ||
        ((Element == TypeENUM)    && (Set & (TypeVOID|TypeCHAR|TypeINT|TypeFLOAT|TypeDOUBLE|TypeSIGNED|TypeUNSIGNED|TypeSHORT|TypeLONG))) ||
        ((Element == TypeSTRUCT)  && (Set & (TypeVOID|TypeCHAR|TypeINT|TypeFLOAT|TypeDOUBLE|TypeSIGNED|TypeUNSIGNED|TypeSHORT|TypeLONG))) ||
        ((Element == TypeTYPEDEF) && (Set & (TypeVOID|TypeCHAR|TypeINT|TypeFLOAT|TypeDOUBLE|TypeSIGNED|TypeUNSIGNED|TypeSHORT|TypeLONG))))
            Error(WARNING0, "Type declaration contains contradictory properties");
    else Set |= Element;
    return Set;
 }

static WORD
DeclQual(WORD Set, WORD Element) {
    if ((Set == 0) || (Set == Element)) {
        return Element;
    }
    if ((Element == QualNORETURN) || (Element == QualUNDEFENDEF)) {         // its ok to add no return or undefended to an existing qualifier
        return Set | Element;
    }

    Error(WARNING0, "Type Qualification contains contradictory properties");
    return Set;
 }

static LPVOID
DeclPtr(LPVOID Set, LPVOID Element) {
    if (Set == 0) return Element;
    Error(WARNING0, "Complex Type Qualification contains contradictory properties");
    return Set;
 }

TPDeclSpec
NewSpecClass(WORD Class) {
    TPDeclSpec NewEl = NewSpecBlank(DecSpec);
    NewEl->Use.DecSpec.Class = Class;
    return NewEl;
 }  
 
TPDeclSpec NewSpecType(WORD Type, LPVOID unPtr) {
    TPDeclSpec NewEl = NewSpecBlank(DecSpec);
    NewEl->Use.DecSpec.Type = Type;
    NewEl->Use.DecSpec.pPtr  = unPtr;
    return NewEl;
 }

TPDeclSpec
NewSpecQual(WORD wQual) {
    TPDeclSpec NewEl = NewSpecBlank(DecSpec);
    NewEl->Use.DecSpec.wQual = wQual;
    return NewEl;
 }

static TPDeclSpec FindTarget(TPDeclSpec unPtr) {
    while (unPtr) {
        switch (unPtr->Usage) {
            case DecId:
                 unPtr = unPtr->Use.DecId.pTarget;
                 break;
            case DecSpec:
                 return unPtr;
            case DecPtr:
                 unPtr = unPtr->Use.DecPtr.pTarget;
                 break;
            case DecArray:
                 unPtr = unPtr->Use.DecArray.pTarget;
                 break;
            case DecFunc:
                 unPtr = unPtr->Use.DecFunc.pReturnType;
                 break;
            default:
                Error(FATAL,"FindTarget: Unknown Use [%02x]\n", unPtr->Usage);
                return unPtr;
        }
    }
    ASSERT(FALSE);
    return 0;
 }


TPDeclSpec
ConcatDeclSpec(TPDeclSpec Old, TPDeclSpec New) {
    TPDeclSpec O=FindTarget(Old);
    TPDeclSpec N=FindTarget(New);

//    printf("Old: "); ParseDeclSpec(1, Old, FALSE); 
//    printf("New: "); ParseDeclSpec(1, New, FALSE); 


    if (O->Usage != DecSpec) Error(FATAL, "ConcatDeclSpec: What 1!\n");
    if (N->Usage != DecSpec) Error(FATAL, "ConcatDeclSpec: What 2!\n");
    if (N->Use.DecSpec.Class)
        O->Use.DecSpec.Class = DeclClass(O->Use.DecSpec.Class,N->Use.DecSpec.Class); 
    if (N->Use.DecSpec.Type)
        O->Use.DecSpec.Type  = DeclType( O->Use.DecSpec.Type, N->Use.DecSpec.Type);
    if (N->Use.DecSpec.wQual)
        O->Use.DecSpec.wQual  = DeclQual( O->Use.DecSpec.wQual, N->Use.DecSpec.wQual); 
    if (N->Use.DecSpec.pPtr)
        O->Use.DecSpec.pPtr   = DeclPtr(  O->Use.DecSpec.pPtr,  N->Use.DecSpec.pPtr); 


//  printf(" =>: "); ParseDeclSpec(1, Old, FALSE); printf("\n");

    return Old;
 }


TPDeclSpec ConcatDeclSpecTypes(TPDeclSpec pType, TPDeclSpec pOld) {
//    printf("T   : "); ParseDeclSpec(1, pType, FALSE);
//    printf("pOld: "); ParseDeclSpec(1, pOld, FALSE);

    ASSERT(pOld->Usage == DecSpec);
    WORD wClass = pOld->Use.DecSpec.Class;
    WORD wType  = pOld->Use.DecSpec.Type;
    WORD wQual  = pOld->Use.DecSpec.wQual;

    switch (pType->Usage) {
    case DecSpec:   
        pType->Use.DecSpec.Class = DeclClass(pType->Use.DecSpec.Class, wClass);
        pType->Use.DecSpec.Type = DeclType(pType->Use.DecSpec.Type, wType);
        pType->Use.DecSpec.wQual = DeclQual(pType->Use.DecSpec.wQual, wQual);
        break;

    case DecPtr:
        pType->Use.DecPtr.pTarget = ConcatDeclSpecTypes(pType->Use.DecPtr.pTarget, pOld);
        break;

    case DecFunc:
        pType->Use.DecFunc.pReturnType = ConcatDeclSpecTypes(pType->Use.DecFunc.pReturnType, pOld);
        break;

        //  case DecId:        unPtr = unPtr->Use.DecId.pTarget;        break;
        //  case DecArray:  pOld->Use.DecArray.pTarget.pTarget;
    default:
        Error(FATAL, "FindTarget: Unknown Use [%02x]\n", pOld->Usage);
        return pOld;
    }

//    printf("  =>: "); ParseDeclSpec(1, pType, FALSE); printf("\n");

    return pType;
}


TPDeclSpec ConcatDeclSpecQualifiers(TPDeclSpec pQual, TPDeclSpec pOld) {

//    printf("Q   : "); ParseDeclSpec(1, pQual, FALSE);
//    printf("pOld: "); ParseDeclSpec(1, pOld, FALSE);

    ASSERT(pQual->Usage == DecSpec);

    ASSERT(pQual->Use.DecSpec.Type == 0);
    ASSERT(pQual->Use.DecSpec.Class == 0);
    WORD wQ = pQual->Use.DecSpec.wQual;                      // new Qualifier value

    switch (pOld->Usage) {
    case DecSpec:   pOld->Use.DecSpec.wQual = DeclQual(pOld->Use.DecSpec.wQual, wQ); break;
    case DecPtr:    pOld->Use.DecPtr.wQual  = DeclQual(pOld->Use.DecPtr.wQual, wQ); break;
//  case DecFunc:
//  case DecId:        unPtr = unPtr->Use.DecId.pTarget;        break;
//  case DecArray:  pOld->Use.DecArray.pTarget.pTarget;
    default:
        Error(FATAL, "FindTarget: Unknown Use [%02x]\n", pOld->Usage);
        return pOld;
    }

//    printf("  =>: "); ParseDeclSpec(1, pOld, FALSE); printf("\n");

    return pOld;
}

TPDeclSpec ConcatDeclSpecClass(TPDeclSpec pClass, TPDeclSpec pOld) {

    //printf("C   : "); ParseDeclSpec(1, pClass, FALSE);
    //printf("pOld: "); ParseDeclSpec(1, pOld, FALSE);

    ASSERT(pClass->Usage == DecSpec);

    ASSERT(pClass->Use.DecSpec.Type == 0);
    ASSERT(pClass->Use.DecSpec.wQual == 0);
    WORD wC = pClass->Use.DecSpec.Class;                      // new Class value

    switch (pOld->Usage) {
    case DecSpec:   pOld->Use.DecSpec.Class = DeclQual(pOld->Use.DecSpec.Class, wC); break;
    case DecPtr:    pOld->Use.DecPtr.pTarget = ConcatDeclSpecClass(pClass, pOld->Use.DecPtr.pTarget); break;
    case DecFunc:   pOld->Use.DecFunc.pReturnType = ConcatDeclSpecClass(pClass, pOld->Use.DecFunc.pReturnType); break;
    //  case DecId:        unPtr = unPtr->Use.DecId.pTarget;        break;
    //  case DecArray:  pOld->Use.DecArray.pTarget.pTarget;
    default:
        Error(FATAL, "FindTarget: Unknown Use [%02x]\n", pOld->Usage);
        return pOld;
    }

    //printf("  =>: "); ParseDeclSpec(1, pOld, FALSE); printf("\n");

    return pOld;
}



/* ******************************************** */

TPDeclSpec
NewPointer(TPDeclSpec Qualifier, TPDeclSpec Target) {
    WORD       q;
    if (!Qualifier) Qualifier = NewSpecQual(0);
    q = Qualifier->Use.DecSpec.wQual;
    Qualifier->Usage = DecPtr;                      // recycle as pointer
    Qualifier->Use.DecPtr.pTarget = Target;         // recycle as pointer
    Qualifier->Use.DecPtr.wQual   = q;              // recycle as pointer
    return Qualifier;
 }

TPDeclSpec
NewIdentifier(LPSTR Name) {
    TPDeclSpec N;
    N = NewDeclSpec(DecId);
    N->Use.DecId.pszName = Name;
    N->Use.DecId.pTarget = NULL;
    N->Use.DecId.pszInitializedStr = NULL;
    N->Use.DecId.pInitializer = NULL;
    N->Use.DecId.pBrother = NULL;
    N->Use.DecId.UsedFlags = 0;
    return N;
 }

TPDeclSpec NewArray(TPDeclSpec Dec, TPExprNode Expr) {
    TPDeclSpec N;
    N = NewDeclSpec(DecArray);
    if (Expr) {
        if (Expr->Usage != uConst) {
            //ParseExpr(Expr, 0);
            Error(ERROR0, "Constant required for Array Dimensions.");
            N->Use.DecArray.Size = 0;
        } else {
            N->Use.DecArray.Size = ExprConstInt(Expr);
            if ((long)N->Use.DecArray.Size < 0) {
                Error(ERROR0, "Array dimension = %ld. Must be >= 0.", N->Use.DecArray.Size);
                N->Use.DecArray.Size = 0;
            }
        }
    } else {
            N->Use.DecArray.Size = 0;
    }
    N->Use.DecArray.pTarget = NULL;
    return AppendDecl(Dec,N);
 }

TPDeclSpec DeclNewFunc(TPDeclSpec Dec, TPDeclSpec PList, TPDeclSpec IdList) {
    TPDeclSpec N;
    N = NewDeclSpec(DecFunc);
    if (PList != NULL) {
        N->Use.DecFunc.pPList = PList;
    }
    N->Use.DecFunc.pIdList = IdList;
    N->Use.DecFunc.pReturnType = NULL;
    return AppendDecl(Dec, N);
}




TPDeclSpec Glb_pCurrenFunction;                                                          // this is the function currently being parsed. This helps verify any 'return' statements we find.
// ##########################################################################
// #  Function: FuncParams
// #        Called by the parser when the parameters have been parsed.
// #  Used to convert array parameters into the appropriate pointer types.
// #  Also calculates the 'offset' of the parameter within the frame. 
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
void FuncParams(TPDeclSpec pFuncType, TPDeclSpec Func) {                            // make the parameters from the parameter.
    ASSERT(Func                    && Func->Usage == DecId);
    ASSERT(Func->Use.DecId.pTarget && Func->Use.DecId.pTarget->Usage == DecFunc);
    AppendDecl(Func->Use.DecId.pTarget, pFuncType);                                 // append will tag the type to the end of any pointer nodes tied to the function already.
    DeclareParameters(Func->Use.DecId.pTarget->Use.DecFunc.pPList);
    Glb_pCurrenFunction = Func;
}

TPDeclSpec  FunctionBody(TPDeclSpec Func, TPDeclSpec pIdList, TPStatement pBody) {
    ASSERT(Glb_pCurrenFunction == Func)
    ASSERT(Func->Usage == DecId && Func->Use.DecId.pTarget->Usage == DecFunc);
    //AppendDecl(pFunc->Use.DecId.pTarget, pType);                                // done in FuncParams above. // Append used deliberately to cater for pre-existing pointers.
    Func->Use.DecId.pTarget->Use.DecFunc.pIdList = pIdList;
    Func->Use.DecId.pTarget->Use.DecFunc.pBody = pBody;

    UndeclareParameters(Func->Use.DecId.pTarget->Use.DecFunc.pPList);

    if (pIdList != NULL) {
        Error(ERROR0, "K&R 'C' parameters are not supported yet. See source function '%s'", Func->Use.DecId.pszName);
        // pIdList is same list structure (ie id.boother-> id->brother-> etc.)
        // not simple as the param names may be in a different order 
    }
    Glb_pCurrenFunction = NULL;
    return Func;

}


TPDeclSpec AddInitializerStr(TPDeclSpec pDec, LPSTR pStr) {         // these are our pseudo variables used when anonomous strings are defined.
    if (pDec->Usage != DecId) {
        Error(FATAL, "AddInitializerStr(): Error1\n");
        return pDec;
    }
    pDec->Use.DecId.pszInitializedStr = pStr;
    //PrintInit(pStr); printf("\n");
    return pDec;
}


TPDeclSpec  AddInitializer(TPDeclSpec pDec, TPExprNode pInit) {
    if (pDec->Usage != DecId) {
        Error(FATAL, "AddInitializer(): Error1\n");
        return pDec;
    }
    pDec->Use.DecId.pInitializer = pInit;
    //PrintInit(pInit); printf("\n");
    return pDec;
 }


/*
TPDeclSpec DeclVarAddType(TPDeclSpec pIdList, TPDeclSpec pSpec) {           // Add type to all the variables in a list.
    ASSERT(pIdList && pIdList->Usage == DecId);
    ASSERT(pSpec && pSpec->Usage == DecSpec);

    TPDeclSpec pD = pIdList;
    
    while (pD != NULL) {
        ASSERT(pD && pD->Usage == DecId);
        pD->Use.DecId.pTarget = pSpec;
        pD = pD->Use.DecId.pBrother;
    }
    return pIdList;
}
*/

TPDeclSpec DeclVarAddBrother(TPDeclSpec pA, TPDeclSpec pB) {                            // Add a variable to the list of variables.
    ASSERT(pA && pA->Usage == DecId);
    ASSERT(pB && pB->Usage == DecId);

    TPDeclSpec pC;
    for (pC = pA; pC->Use.DecId.pBrother != NULL; pC = pC->Use.DecId.pBrother);
    pC->Use.DecId.pBrother = pB;
    return pA;
}

TPDeclSpec DeclAddVarToParameterList(TPDeclSpec pA, TPDeclSpec pB) {                    // Add a variable to the list of parameter variables. (Order is reversed).
    ASSERT(pA && pA->Usage == DecId);
    ASSERT(pB && pB->Usage == DecId);

    ASSERT(pB->Use.DecId.pBrother == NULL);
    pB->Use.DecId.pBrother = pA;
    return pB;
}


TPDeclSpec AppendDecl(TPDeclSpec a,TPDeclSpec b) {
    TPDeclSpec c = a;
    if (!c) return b;
    {
        if (a->Usage == DecId && b->Usage == DecId) {
            printf("a="); for (TPDeclSpec q = a; q != NULL; q = q->Use.DecId.pBrother) printf("<%s>", q->Use.DecId.pszName); printf("\n");
            printf("b="); for (TPDeclSpec q = b; q != NULL; q = q->Use.DecId.pBrother) printf("<%s>", q->Use.DecId.pszName); printf("\n");
        }
    }

    for (;;) {
        switch (c->Usage) {
            case    DecId:
                    if (c->Use.DecId.pBrother) {
                        // this adds a the same pTarget to each of a list of brothers.
                        AppendDecl(c->Use.DecId.pBrother, b);     // who calls and when. could it be simplified?          
                    }
                    if (c->Use.DecId.pTarget) {
                        c = c->Use.DecId.pTarget;
                        break;
                    }  else {
                        c->Use.DecId.pTarget = b;
                        return a;
                    }
                    break;
            case    DecSpec:
                    Error(FATAL, "AppendDecl: Trouble append to Spec\n");
                    return a;
            case    DecPtr:
                    if (c->Use.DecPtr.pTarget) {
                        c = c->Use.DecPtr.pTarget;
                        break;
                    }  else {
                        c->Use.DecPtr.pTarget = b;
                        return a;
                    }
                    break;
            case    DecArray:
                    if (c->Use.DecArray.pTarget) {
                        c = c->Use.DecArray.pTarget;
                        break;
                    }  else {
                        c->Use.DecArray.pTarget = b;
                        return a;
                    }
                    break;
            case    DecFunc:                                  // assigned more logically elsewhere
                    if (c->Use.DecFunc.pReturnType) {
                        c = c->Use.DecFunc.pReturnType;
                        break;
                    }  else {
                        c->Use.DecFunc.pReturnType = b;
                        return a;
                    }
                    break;
            default:
                Error(FATAL, "AppendDecl: Unknown Use\n");
                    break;
        }
    }
 }

TPDeclSpec MakeBrother(TPDeclSpec a,TPDeclSpec b) {
    TPDeclSpec c;
    if (a->Usage != DecId || b->Usage != DecId) {
        Error(FATAL, "MakeBrother: Error1\n");
        return a;
    }
//    {
//        printf("A="); for (TPDeclSpec q = a; q != NULL; q = q->Use.DecId.pBrother) printf("<%s>", q->Use.DecId.pszName); printf("\n");
//        printf("B="); for (TPDeclSpec q = b; q != NULL; q = q->Use.DecId.pBrother) printf("<%s>", q->Use.DecId.pszName); printf("\n");
//    }
    for (c=a; c->Use.DecId.pBrother != NULL; c=c->Use.DecId.pBrother);
    c->Use.DecId.pBrother=b;
//    {
//        printf("C="); for (TPDeclSpec q = a; q != NULL; q = q->Use.DecId.pBrother) printf("<%s>", q->Use.DecId.pszName); printf("\n");
//    }
    return a;
 }




#define putch(x) putc((x),stdout) 
 
static void
DescClass(WORD q) {
    ASSERT((q | ClassALL) == ClassALL);
    ConsolePrintf(CON_GREEN, "Class[");
    ConsolePrintf(CON_GREEN, (q & ClassAUTO)       ? "A":"_");
    ConsolePrintf(CON_GREEN, (q & ClassREGISTER)   ? "R":"_");
    ConsolePrintf(CON_GREEN, (q & ClassSTATIC)     ? "S":"_");
    ConsolePrintf(CON_GREEN, (q & ClassEXTERN)     ? "E":"_");
    ConsolePrintf(CON_GREEN, (q & ClassTYPEDEF)    ? "T":"_");
    ConsolePrintf(CON_GREEN, "]");
}

#define DESCRIPTORS_COUNT    8
#define DESCRIPTOR_SIZE    256
static char szaDescriptor[DESCRIPTORS_COUNT][DESCRIPTOR_SIZE];                      // gets rewrirtten each call! Cycled through last 8
static int  iLastDesc;

LPSTR DescClassString(WORD c) {
    iLastDesc = ((iLastDesc + 1) & (DESCRIPTORS_COUNT-1));
    char *pszClassDescriptor = szaDescriptor[iLastDesc]; 
    sprintf_s(pszClassDescriptor, DESCRIPTOR_SIZE, "Class[%c%c%c%c%c]", (c & ClassAUTO) ? 'A' : '_', (c & ClassREGISTER) ? 'R' : '_', (c & ClassSTATIC) ? 'S' : '_', (c & ClassEXTERN) ? 'E' : '_', (c & ClassTYPEDEF) ? 'T' : '_');
    return pszClassDescriptor;
}

LPSTR DescTypeString(WORD q) {
    iLastDesc = ((iLastDesc + 1) & (DESCRIPTORS_COUNT - 1));
    char *pszClassDescriptor = szaDescriptor[iLastDesc];
    int n = 0;
    ASSERT((q | TypeALL) == TypeALL);
    pszClassDescriptor[0] = 0;
    if(q & TypeUNSIGNED) n += sprintf_s(&pszClassDescriptor[n], DESCRIPTOR_SIZE - n, "unsigned ");
    if(q & TypeSIGNED)   n += sprintf_s(&pszClassDescriptor[n], DESCRIPTOR_SIZE - n, "signed ");
    if(q & TypeDOUBLE)   n += sprintf_s(&pszClassDescriptor[n], DESCRIPTOR_SIZE - n, "double ");
    if(q & TypeFLOAT)    n += sprintf_s(&pszClassDescriptor[n], DESCRIPTOR_SIZE - n, "float ");
    if(q & TypeLONG)     n += sprintf_s(&pszClassDescriptor[n], DESCRIPTOR_SIZE - n, "long ");
    if(q & TypeINT)      n += sprintf_s(&pszClassDescriptor[n], DESCRIPTOR_SIZE - n, "int ");
    if(q & TypeSHORT)    n += sprintf_s(&pszClassDescriptor[n], DESCRIPTOR_SIZE - n, "short ");
    if(q & TypeCHAR)     n += sprintf_s(&pszClassDescriptor[n], DESCRIPTOR_SIZE - n, "char ");
    if(q & TypeVOID)     n += sprintf_s(&pszClassDescriptor[n], DESCRIPTOR_SIZE - n, "void ");
    if(q & TypeBOOL)     n += sprintf_s(&pszClassDescriptor[n], DESCRIPTOR_SIZE - n, "bool ");
    return pszClassDescriptor;
}

LPSTR DescQualString(WORD q) {
    iLastDesc = ((iLastDesc + 1) & (DESCRIPTORS_COUNT - 1));
    char *pszClassDescriptor = szaDescriptor[iLastDesc];
    int n = 0;
    ASSERT((q | TypeALL) == TypeALL);
    pszClassDescriptor[0] = 0;
    if (q & QualCONST)      n += sprintf_s(&pszClassDescriptor[n], DESCRIPTOR_SIZE, "const ");
    if (q & QualVOLATILE)   n += sprintf_s(&pszClassDescriptor[n], DESCRIPTOR_SIZE, "volatile ");
    if (q & QualNEAR)       n += sprintf_s(&pszClassDescriptor[n], DESCRIPTOR_SIZE, "near ");
    if (q & QualFAR)        n += sprintf_s(&pszClassDescriptor[n], DESCRIPTOR_SIZE, "far ");
    if (q & QualNORETURN)   n += sprintf_s(&pszClassDescriptor[n], DESCRIPTOR_SIZE, "noreturn ");
    if (q & QualUNDEFENDEF) n += sprintf_s(&pszClassDescriptor[n], DESCRIPTOR_SIZE, "undefended ");
    return &pszClassDescriptor[0];
}


LPSTR DescFullTypeString(int iPos, TPDeclSpec pDecl) {
    iLastDesc = ((iLastDesc + 1) & (DESCRIPTORS_COUNT - 1));
    char *pszClassDescriptor = szaDescriptor[iLastDesc];
    ASSERT(iPos < DESCRIPTOR_SIZE - 32);                       // check for space. crash out its close to overflow.

    switch (pDecl->Usage) {
    case    DecId:          // Id
        sprintf_s(&pszClassDescriptor[iPos], DESCRIPTOR_SIZE -iPos, "%s", pDecl->Use.DecId.pszName);
        return pszClassDescriptor;
    case    DecSpec:
        if ((pDecl->Use.DecSpec.Type) & TypeSTRUCT) {
            sprintf_s(&pszClassDescriptor[iPos], DESCRIPTOR_SIZE - iPos, "Structure, %s", DescQualString(pDecl->Use.DecSpec.wQual));
            return pszClassDescriptor;
        }        //    PrintStructSet(iDepth + 1, pDecl->Use.DecSpec.pPtr, FALSE); DescQual(pDecl->Use.DecSpec.Qual); }
        else if ((pDecl->Use.DecSpec.Type) & TypeENUM) {
            sprintf_s(&pszClassDescriptor[iPos], DESCRIPTOR_SIZE - iPos, "Enum, %s", DescQualString(pDecl->Use.DecSpec.wQual));
            return pszClassDescriptor;
        }
        else if ((pDecl->Use.DecSpec.Type) & TypeTYPEDEF) { 
            iPos += sprintf_s(&pszClassDescriptor[iPos], DESCRIPTOR_SIZE - iPos, "typedef, ");
            return DescFullTypeString(iPos, pDecl->Use.DecSpec.pPtr);
        }
        else {
            sprintf_s(&pszClassDescriptor[iPos], DESCRIPTOR_SIZE - iPos, "%s%s, %s", DescQualString(pDecl->Use.DecSpec.wQual), DescTypeString(pDecl->Use.DecSpec.Type), DescClassString(pDecl->Use.DecSpec.Class));
            return pszClassDescriptor;
        }
    case    DecPtr:
        iPos += sprintf_s(&pszClassDescriptor[iPos], DESCRIPTOR_SIZE - iPos, "%sPointer to ", DescQualString(pDecl->Use.DecPtr.wQual));
        return DescFullTypeString(iPos, pDecl->Use.DecPtr.pTarget);
    case    DecArray:
        iPos += sprintf_s(&pszClassDescriptor[iPos], DESCRIPTOR_SIZE - iPos, "Array[%d] of ", pDecl->Use.DecArray.Size);
        return DescFullTypeString(iPos, pDecl->Use.DecArray.pTarget);
    case    DecFunc:
        sprintf_s(&pszClassDescriptor[iPos], DESCRIPTOR_SIZE - iPos, "Function ...");
        return pszClassDescriptor;
    default:
        Error(FATAL, "ParseDeclSpec: Unknown Use\n");
        return pszClassDescriptor;
    }
}


static void
DescType(WORD q) {
    ASSERT((q | TypeALL) == TypeALL);
    ConsolePrintf(CON_GREEN, "type[");
    ConsolePrintf(CON_GREEN, DescTypeString(q));
    // if (q & TypeUNSIGNED) ConsolePrintf(CON_GREEN, "unsigned ");
    // if (q & TypeSIGNED)   ConsolePrintf(CON_GREEN, "signed ");
    // if (q & TypeDOUBLE)   ConsolePrintf(CON_GREEN, "double ");
    // if (q & TypeFLOAT)    ConsolePrintf(CON_GREEN, "float ");
    // if (q & TypeLONG)     ConsolePrintf(CON_GREEN, "long ");
    // if (q & TypeINT)      ConsolePrintf(CON_GREEN, "int ");
    // if (q & TypeSHORT)    ConsolePrintf(CON_GREEN, "short ");
    // if (q & TypeCHAR)     ConsolePrintf(CON_GREEN, "char ");
    // if (q & TypeVOID)     ConsolePrintf(CON_GREEN, "void ");
    // if (q & TypeBOOL)     ConsolePrintf(CON_GREEN, "bool ");
    ConsolePrintf(CON_GREEN, "]");
}

static void
DescQual(WORD q) {
    ASSERT((q | QualALL) == QualALL);
    ConsolePrintf(CON_GREEN, "Qual[");
    ConsolePrintf(CON_GREEN, (q & QualCONST)   ? "C":"_");
    ConsolePrintf(CON_GREEN, (q & QualVOLATILE)? "V":"_");
    ConsolePrintf(CON_GREEN, (q & QualNEAR)    ? "N":"_");
    ConsolePrintf(CON_GREEN, (q & QualFAR)     ? "F":"_");
    ConsolePrintf(CON_GREEN, "]");
}


void ParseDeclSpec(int iDepth, TPDeclSpec pDecl, BOOL fDoBrothers) {
    ConsoleIndent(iDepth);
    if (!pDecl) {
            printf("..Null..\n");
            return;
    } else {
        switch (pDecl->Usage) {
            case    DecId:          // Id
                    ConsolePrintf(CON_YELLOW_BRIGHT, "'%s", pDecl->Use.DecId.pszName);
                    if (pDecl->Use.DecId.iOffset == GLOBAL_VAR) ConsolePrintf(CON_YELLOW_BRIGHT, "'");
                    else                                        ConsolePrintf(CON_YELLOW_BRIGHT, ":%d'", pDecl->Use.DecId.iOffset);

                    ConsolePrintf(CON_YELLOW, " UsedFlags=0x%02x\n", pDecl->Use.DecId.UsedFlags);
                    ParseDeclSpec(iDepth+1, pDecl->Use.DecId.pTarget, FALSE);
                    if (pDecl->Use.DecId.pszInitializedStr) {
                        printf("\t\tI = \"%s\"\n", pDecl->Use.DecId.pszInitializedStr);
                    }
                    if (pDecl->Use.DecId.pInitializer) {
                            printf("\t\tI = "); 
                            ExprPrintInit(pDecl->Use.DecId.pInitializer); 
                            printf("\n");
                    }
                    //ParseDeclSpec(pDecl->Use.DecId.pTarget, fDoBrothers);
                    if (fDoBrothers && pDecl->Use.DecId.pBrother) {
                        ParseDeclSpec(iDepth, pDecl->Use.DecId.pBrother, fDoBrothers);
                    }
                    return;
            case    DecSpec:
                    if      ((pDecl->Use.DecSpec.Type) & TypeSTRUCT)  { PrintStructSet(iDepth+1, pDecl->Use.DecSpec.pPtr,FALSE); DescQual(pDecl->Use.DecSpec.wQual); }
                    else if ((pDecl->Use.DecSpec.Type) & TypeENUM)    { EnumSetPrint(iDepth+1, pDecl->Use.DecSpec.pPtr);         DescQual(pDecl->Use.DecSpec.wQual); }
                    else if ((pDecl->Use.DecSpec.Type) & TypeTYPEDEF) { printf("Typedef "); ParseDeclSpec(iDepth+1, pDecl->Use.DecSpec.pPtr,fDoBrothers); }
                    else                                              { DescClass(pDecl->Use.DecSpec.Class); DescType(pDecl->Use.DecSpec.Type); DescQual(pDecl->Use.DecSpec.wQual); }
                    printf("\n");
                    return;
            case    DecPtr:
                    printf("P");  DescQual(pDecl->Use.DecPtr.wQual); printf("-> ");
                    ParseDeclSpec(iDepth + 1, pDecl->Use.DecPtr.pTarget, fDoBrothers);
                    return;
            case    DecArray:
                    printf("A[%ld]-> ", pDecl->Use.DecArray.Size);
                    ParseDeclSpec(iDepth + 1, pDecl->Use.DecArray.pTarget, fDoBrothers);
                    return;
            case    DecFunc:
                    printf("Function(\n");
                    ParseDeclSpec(iDepth + 1, pDecl->Use.DecFunc.pPList, TRUE);
                    ConsoleIndent(iDepth);
                    printf(")\n");
                    ConsoleIndent(iDepth);
                    printf("Ids(\n");
                    ParseDeclSpec(iDepth + 1, pDecl->Use.DecFunc.pIdList, TRUE);
                    ConsoleIndent(iDepth);
                    printf(")\n");
                    ConsoleIndent(iDepth);
                    printf("returning\n");
                    ParseDeclSpec(iDepth + 1, pDecl->Use.DecFunc.pReturnType, fDoBrothers);
                    GenStatementPrettyPrint(iDepth, pDecl->Use.DecFunc.pBody, TRUE);
                    return;
            default:
                Error(FATAL, "ParseDeclSpec: Unknown Use\n");
                    return;
        }
    }
}


/* ***************************************************************** */
/*  Declarations  */
/* ************** */

static TPDeclSpec
DuplicateD(TPDeclSpec unPtr) {
    TPDeclSpec New;
    New = NewDeclSpec(unPtr->Usage);
    *New = *unPtr;
    return New;
 }

static TPDeclSpec
DuplicateDecl(TPDeclSpec unPtr) {
    TPDeclSpec Start,Latest;
    if (!unPtr) return NULL;
    Start = Latest = DuplicateD(unPtr);
    while (Latest) {
        switch (Latest->Usage) {
            case DecId:
                    Latest->Use.DecId.pTarget = DuplicateD(Latest->Use.DecId.pTarget);
                    Latest = Latest->Use.DecId.pTarget;
                    break;
            case DecSpec:
                    return Start;
                    break;
            case DecPtr:
                    Latest->Use.DecPtr.pTarget = DuplicateD(Latest->Use.DecPtr.pTarget);
                    Latest = Latest->Use.DecPtr.pTarget;
                    break;
            case DecArray:
                    Latest->Use.DecArray.pTarget = DuplicateD(Latest->Use.DecArray.pTarget);
                    Latest = Latest->Use.DecArray.pTarget;
                    break;
            case DecFunc:
                    Latest->Use.DecFunc.pReturnType = DuplicateD(Latest->Use.DecFunc.pReturnType);
                    Latest = Latest->Use.DecFunc.pReturnType;
                    break;
            default:
                Error(FATAL, "DuplicateDecl: Unknown Use [%02x]\n", Latest->Usage);
                return 0L;
        }
    }
    ASSERT(FALSE);
    return 0;
}


static BOOL IsClassProperty(TPDeclSpec unPtr, WORD Property) {
    while (unPtr) {
        switch (unPtr->Usage) {
            case DecId:
                    unPtr = unPtr->Use.DecId.pTarget;
                    break;
            case DecSpec:
                    return (unPtr->Use.DecSpec.Class & Property);
                    break;
            case DecPtr:
                    unPtr = unPtr->Use.DecPtr.pTarget;
                    break;
            case DecArray:
                    unPtr = unPtr->Use.DecArray.pTarget;
                    break;
            case DecFunc:
                    unPtr = unPtr->Use.DecFunc.pReturnType;
                    break;
            default:
                Error(FATAL, "IsClassProperty: Unknown Use [%02x]\n", unPtr->Usage);
                return 0L;
        }
    }
    return FALSE;
 }

#define IsAuto(unPtr)     IsClassProperty(unPtr, ClassAUTO)
#define IsRegister(unPtr) IsClassProperty(unPtr, ClassREGISTER)
#define IsStatic(unPtr)   IsClassProperty(unPtr, ClassSTATIC)
#define IsExtern(unPtr)   IsClassProperty(unPtr, ClassEXTERN)
#define IsTypedef(unPtr)  IsClassProperty(unPtr, ClassTYPEDEF)

static void
StripClassProperty(TPDeclSpec unPtr, WORD Property) {
    while (unPtr) {
        switch (unPtr->Usage) {
            case DecId:
                    unPtr = unPtr->Use.DecId.pTarget;
                    break;
            case DecSpec: 
                    unPtr->Use.DecSpec.Class &= ~Property;
                    return;
            case DecPtr:
                    unPtr = unPtr->Use.DecPtr.pTarget;
                    break;;
            case DecArray:
                    unPtr = unPtr->Use.DecArray.pTarget;
                    break;
            case DecFunc:
                    unPtr = unPtr->Use.DecFunc.pReturnType;
                    break;
            default:
                Error(FATAL, "StripClassProperty: Unknown Use [%02x]\n", unPtr->Usage);
                return;
        }
    }
    return;
 }

#define StripAuto(unPtr)     StripClassProperty(unPtr, ClassAUTO)
#define StripRegister(unPtr) StripClassProperty(unPtr, ClassREGISTER)
#define StripStatic(unPtr)   StripClassProperty(unPtr, ClassSTATIC)
#define StripExtern(unPtr)   StripClassProperty(unPtr, ClassEXTERN)
#define StripTypedef(unPtr)  StripClassProperty(unPtr, ClassTYPEDEF)

static BOOL CompDeclStruct(TPDeclSpec a, TPDeclSpec b) {   // Compair the type to the base type eg functions, pointers, arrays of a base type.
    while (a && b) {
        if (a->Usage != b->Usage) {
            return FALSE;
        }
        switch (a->Usage) {
            case DecId:
                    a = a->Use.DecId.pTarget;
                    b = b->Use.DecId.pTarget;
                    break;
            case DecSpec:
                    return TRUE;
            case DecPtr:
                    a = a->Use.DecPtr.pTarget;
                    b = b->Use.DecPtr.pTarget;
                    break;
            case DecArray:
                    a = a->Use.DecArray.pTarget;
                    b = b->Use.DecArray.pTarget;
                    break;
            case DecFunc:
                    a = a->Use.DecFunc.pReturnType;
                    b = b->Use.DecFunc.pReturnType;
                    break;
            default:
                Error(FATAL, "CompDeclStruct: Unknown Use [%02x]\n", a->Usage);
                return FALSE;
        }
    }
    ASSERT(FALSE);
    return 0;
 }


BOOL
CompDecl(TPDeclSpec a, TPDeclSpec b) {
    for (;;) {
        if (a->Usage == DecId) {                                         // case DecId
           if (b->Usage != DecId)       return FALSE;
           else {                       a = a->Use.DecId.pTarget;
                                        b = b->Use.DecId.pTarget;
           }
        } else if (a->Usage == DecSpec) {                                // case DecSpec
           if (b->Usage != DecSpec)     return FALSE;
           else { if (a->Use.DecSpec.Type != b->Use.DecSpec.Type)                 return FALSE;
                  if (!(a->Use.DecSpec.Type & (TypeSTRUCT|TypeENUM|TypeTYPEDEF))) return TRUE;
                  if (a->Use.DecSpec.pPtr == b->Use.DecSpec.pPtr)                 return TRUE;
                  return FALSE;
           }
        } else if (a->Usage == DecPtr) {                                 // case DecPtr
           a = a->Use.DecPtr.pTarget;
           if (b->Usage == DecArray)    b = b->Use.DecArray.pTarget;
           else if (b->Usage == DecPtr) b = b->Use.DecPtr.pTarget;
           else                         return FALSE;
        } else if (a->Usage == DecArray) {                               // case DecArray
           a = a->Use.DecArray.pTarget;
           if (b->Usage == DecArray)    b = b->Use.DecArray.pTarget;
           else if (b->Usage == DecPtr) b = b->Use.DecPtr.pTarget;
           else                         return FALSE;
        } else if (a->Usage == DecFunc) {                                // case DecFunc
                                        a = a->Use.DecFunc.pReturnType;
                                        b = b->Use.DecFunc.pReturnType;
        } else {
            Error(FATAL, "CompDecl: Unknown Use [%02x]\n", a->Usage);
            return FALSE;
        }
    }
 }



static BOOL TestParams(TPDeclSpec a, TPDeclSpec b) {
    ASSERT(a->Usage == DecFunc && b->Usage == DecFunc);
    TPDeclSpec p1 = a->Use.DecFunc.pPList;                   // a param 1
    TPDeclSpec p2 = b->Use.DecFunc.pPList;                   // b param 1
    if (p1 == NULL) {                                       // Empty ? ... fill it
            a->Use.DecFunc.pPList  = p2;
            return TRUE;
    }
    if (p2 == NULL) {
            b->Use.DecFunc.pPList  = p1;
            return TRUE;
    }

    while (p1 && p2) {
        ASSERT(p1->Usage == DecId && p2->Usage == DecId);
        if (strcmp(p1->Use.DecId.pszName, "...") == 0) {    
            if (strcmp(p2->Use.DecId.pszName, "...") != 0) {           // both = Ellipsis ? 
                return FALSE;                                           // i == ... 2 != ...
            }
        }
        else if (strcmp(p2->Use.DecId.pszName, "...") == 0) {           
            return FALSE;                                               // 1 != ..., 2 == ...
        }
        else if (!CompDecl(p1, p2)) {                                   // Neither = ...
            return FALSE;                                   
        }
        p1 = p1->Use.DecId.pBrother;                                    // do the next
        p2 = p2->Use.DecId.pBrother;
    }
    return ((p1 == NULL) && (p2 == NULL));                              // match so far but was one longrt than the other.
 }



/* *************************************************** */

TPDeclSpec  GlobalTypes;
//TPDeclSpec  LocalTypes;
TPDeclSpec  GlobalObjects;
TPDeclSpec  ParameterObjects;
TPDeclSpec  LObjects;

static TPDeclSpec FindDecl(TPDeclSpec pList, LPSTR pszName) {                  // locate name in a variable list.
    for (;
        (pList != NULL && strcmp(pList->Use.DecId.pszName, pszName));
        pList = pList->pChain);
    return pList;
}

TPDeclSpec FindType(LPSTR Name) {
     TPDeclSpec L = NULL;
     //L = FindDecl(LObjects, Name);
     //if (!L) L = FindDecl(ParameterObjects, Name);
     if (!L) L = FindDecl(GlobalTypes, Name);
     if (L)  StripTypedef(L);
     return DuplicateDecl(L);
 }

 TPDeclSpec FindGlobalObject(LPSTR Name) {
     return FindDecl(GlobalObjects, Name);
 }

 TPDeclSpec  FindParameterObject(LPSTR Name) {
     return FindDecl(ParameterObjects, Name);
 }

 TPDeclSpec  FindLocalObject(LPSTR Name) {
     return FindDecl(LObjects, Name);
 }


 // ##########################################################################
 // #  Function: DefintionListAddGlobal
 // #        Add an element to a Global declaration list.
 // #
 // #       Preserve variable order and permits redefinition to remove extern property.
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
 TPDeclSpec DefintionListAddGlobal(TPDeclSpec List, TPDeclSpec Element) {
    TPDeclSpec L;                                                                          // list pointer
    TPDeclSpec pKnown, pNew;                                                               // known= search-point and new from element
    Element->pChain = NULL;
    if (List == NULL) return Element;
    for (L = List; L->pChain != NULL; L = L->pChain) {                                     // for all the elements. exit at the end or on detection of a duplicate. 
         if (!strcmp(L->Use.DecId.pszName, Element->Use.DecId.pszName)) {
             break;
         }
    }

    if (strcmp(L->Use.DecId.pszName, Element->Use.DecId.pszName)) {                        // ? Duplicate
        L->pChain = Element;                                                               //      not a duplicate.
        return List;                                                                       //      appended to the list
    }                                                                                      //      return the list

    // redefinition.
    // Permit removal of extern flag
    // keep quite if identical and extern
    if (CompDeclStruct(L, Element)) {                                                      // do we have the same type  ? Could we use use CompDecl and skip the type/qualifier tests below?

        //printf("Known : "); ParseDeclSpec(1, L->Use.DecId.pTarget, FALSE);
        //printf("New   : "); ParseDeclSpec(1, Element->Use.DecId.pTarget, FALSE);

        pKnown = FindTarget(L);
        pNew = FindTarget(Element);
        ASSERT((pKnown->Usage == DecSpec) && (pNew->Usage == DecSpec));

        LPSTR DescTypeString(WORD q);

        if (pKnown->Use.DecSpec.wQual != pNew->Use.DecSpec.wQual) {                                                                                   // Changed qualifiers 
            Error(ERROR0, "Redefiniton of %s's qualifiers. \"%s\" ==> \"%s\"", Element->Use.DecId.pszName,                                         //
                                                                                DescQualString(pKnown->Use.DecSpec.wQual),                           //
                                                                                DescQualString(pNew->Use.DecSpec.wQual));                            //      error
            return List;                                                                                                                            //      return the existing list
        }

        if ((pKnown->Use.DecSpec.Class & ~ClassEXTERN) != (pNew->Use.DecSpec.Class & ~ClassEXTERN)) {                                               // Changed Class specifier (we allow extern to be removed)
            Error(ERROR0, "Redefiniton of %s's class specification. \"%s\" ==> \"%s\"", Element->Use.DecId.pszName,                                 //
                                                                                        DescClassString(pKnown->Use.DecSpec.Class),                 //
                                                                                        DescClassString(pNew->Use.DecSpec.Class));                  //      error
            return List;                                                                                                                            //      return the existing list
        }

        if (pKnown->Use.DecSpec.Type != pNew->Use.DecSpec.Type) {                                                                                   // Changed type 
            Error(ERROR0, "Redefiniton of %s's type specification. \"%s\" ==> \"%s\"", Element->Use.DecId.pszName,                                  //
                                                                                       DescTypeString(pKnown->Use.DecSpec.Type),                    //
                                                                                       DescTypeString(pNew->Use.DecSpec.Type));                     //      error
            return List;                                                                                                                            //      return the existing list
        }

        if (((pKnown->Use.DecSpec.Type & (TypeSTRUCT | TypeENUM | TypeTYPEDEF)) != 0) && 
            (pKnown->Use.DecSpec.pPtr != pNew->Use.DecSpec.pPtr)) {                                                                                 // complicated type and different
            Error(ERROR0, "Redefiniton of %s's type specification.", Element->Use.DecId.pszName);                                                   //      error
            return List;                                                                                                                            //      return the existing list
        }

        // assert names and types match
        ASSERT((L->Usage == DecId) && (Element->Usage == DecId));
        if (Element->Use.DecId.pTarget->Usage == DecFunc) {                                                 // functions need extra attention.
            TPDeclSpec KnownFunc = L->Use.DecId.pTarget;                                                    //
            TPDeclSpec NewFunc = Element->Use.DecId.pTarget;                                                //
            if (!TestParams(KnownFunc, NewFunc)) {                                                          // Complain if the parameters change types.
                Error(ERROR0, "Redefiniton of function '%s' parameters.", Element->Use.DecId.pszName);      //   
                return List;                                                                                // 
            }
            if (KnownFunc->Use.DecFunc.pBody && NewFunc->Use.DecFunc.pBody) {                               // old and new can't both have statement lists
                Error(WARNING0, "Ignoring the redefiniton of function '%s' body.", Element->Use.DecId.pszName);          //
                return List;                                                                                //
            }
            if (NewFunc->Use.DecFunc.pBody != NULL) {                                                       // if New has a body then inherit what ever new's definition says (incl new types).
                TDeclSpec Tmp;                                                                              // Swapping contents 
                NewFunc->pChain = KnownFunc->pChain;                                                        // This means whoever points at the old stuff will now point to the new stuff.
                Tmp = *KnownFunc;                                                                           // 
                *KnownFunc = *NewFunc;                                                                      // 
                *NewFunc = Tmp;                                                                             // 
            }                                                                                               //
            return List;                                                                                    // no warning as this is pretty normal definition of a forward declaration
        }

        if (L->Use.DecId.pszInitializedStr == NULL) {                                                       // rescue the initialization data from the redefined var.
            L->Use.DecId.pszInitializedStr = Element->Use.DecId.pszInitializedStr;                          //
        }                                                                                                   //
        if (L->Use.DecId.pInitializer == NULL) {                                                            // rescue the initialization data from the redefined var.
            L->Use.DecId.pInitializer = Element->Use.DecId.pInitializer;                                    //
        }                                                                                                   //

        if ((pKnown->Use.DecSpec.Class == ClassEXTERN) ||                                                   // If there is an extern 
            (pNew->Use.DecSpec.Class == ClassEXTERN)) {                                                     //
            pKnown->Use.DecSpec.Class &= pNew->Use.DecSpec.Class;                                           // new is only extern if both were
        }                                                                                                   //
        else {                                                                                              //
            Error(WARNING0, "Ignoring the redefinition of '%s'.", Element->Use.DecId.pszName);              //
        }                                                                                                   //

    }
    return List;
 }

 // ##########################################################################
 // #  Function: DefintionListAddLocal
 // #        Add an element to a Local declaration list.
 // #
 // #       May not preserve variable order and does not tolerate extern variables.
 // #       Duplicates are tolerated.
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
 TPDeclSpec DefintionListAddLocal(TPDeclSpec pList, TPDeclSpec pElement) {
     ASSERT(pElement && pElement->Usage == DecId && pElement->pChain == NULL);
     pElement->pChain = pList;
     return pElement;
 }



 // ##########################################################################
 // #  Function: DefintionListRemoveElement
 // #        Add an element to a Local declaration list.
 // #
 // #       May not preserve variable order and does not tolerate extern variables.
 // #       Duplicates are tolerated.
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
 TPDeclSpec DefintionListRemoveElement(TPDeclSpec List, TPDeclSpec Element) {
     TPDeclSpec *pL;                                                                       // list pointer

     for (pL = &List; *pL != NULL; pL = &(*pL)->pChain) {
         if (strcmp((*pL)->Use.DecId.pszName, Element->Use.DecId.pszName) == 0) {
             if ((Element->Use.DecId.UsedFlags & DecId_UsedFlag_Local) == 0) {
                 Error(WARNING0, "Unused variable '%s'", Element->Use.DecId.pszName);
             }
             *pL = (*pL)->pChain;
             return List;
         }
     }
     // Not found but removal was requested!!!
     Error(FATAL, "DefintionListRemoveElement(): Removal of sothing that does not exist. Trouble somewhere!");
     return List;
 }



static void ListDefinitions(int iDepth, TPDeclSpec pList) {
    for (;pList; pList = pList->pChain) {
        ParseDeclSpec(0, pList, FALSE);
    }
 }

void
ListGlobalTypes(void) {
    printf("Global Types\n");
    ListDefinitions(0, GlobalTypes);
    printf("\n");
}

void
ListGlobalObjects(void) {
    printf("Global Objects\n");
    ListDefinitions(0, GlobalObjects);
    printf("\n");
}

void
ListParameterObjects(void) {
    printf("Parameter Objects\n");
    ListDefinitions(0, ParameterObjects);
    printf("\n");
}

void
ListLocalObjects(void) {
    printf("Local Objects\n");
    ListDefinitions(0, LObjects);
    printf("\n");
}

static DWORD    CalcStructSize(TPStructSet Struct);
//static BOOL     IsATypeDef(TPDeclSpec Ptr);





void Declaration(TPDeclSpec pDecl) {
    TPDeclSpec Tmp;

    while (pDecl) {
        if (!pDecl) {
            Error(FATAL, "Declaration: Declare Nothing ?\n");
            return;
        }

        if (pDecl->Usage == DecSpec) {      
            if ((pDecl->Use.DecSpec.Type == TypeSTRUCT) || (pDecl->Use.DecSpec.Type == TypeENUM)) {             // structs and enums may be anon.
                ; // OK
            }
            else {
                ASSERT(FALSE);
            }
        }
        else {
            ASSERT(pDecl && pDecl->Usage == DecId);

            pDecl->Use.DecId.iOffset = GLOBAL_VAR;

            InitializerProcess(pDecl);

            //printf("Declaration(%s)\n", pDecl->Use.DecId.pszName);
            // printf("%s\t", (Ptr->Use.DecId.Initializer) ? "Init":"");
            Tmp = pDecl->Use.DecId.pTarget;
            if (IsTypedef(Tmp)) {
                GlobalTypes = DefintionListAddGlobal(GlobalTypes, pDecl);
            }
            else {
                CalcSizeOf(Tmp); // ?is this a debug legacy or does it fixup size records?
                GlobalObjects = DefintionListAddGlobal(GlobalObjects, pDecl);
            }
        }
        pDecl = pDecl->Use.DecId.pBrother;

    }
 }

static int iFrameAllocationIndex = 1;

void DeclareParameters(TPDeclSpec pDecl) {
    ASSERT(ParameterObjects == NULL);                                                   // this should be empty. if not we have a problem somewhere else.
    ASSERT(pDecl != NULL);                                                              // this should not happen thanks to the parser.

    for (; pDecl != NULL; pDecl = pDecl->Use.DecId.pBrother) {                          // For each parameter in the list (list of brothers from the parser)
        ASSERT(pDecl && pDecl->Usage == DecId);                                         //      Sanity checking
        ASSERT(!IsTypedef(pDecl->Use.DecId.pTarget));                                   //      ditto

        if (pDecl->Use.DecId.pTarget && pDecl->Use.DecId.pTarget->Usage == DecArray) {  // pointers are used to pass array paramaters. We substitute the definition here.
            pDecl->Use.DecId.pTarget->Usage = DecPtr;
            pDecl->Use.DecId.pTarget->Use.DecPtr.pTarget = pDecl->Use.DecId.pTarget->Use.DecArray.pTarget;
            pDecl->Use.DecId.pTarget->Use.DecPtr.wQual = 0;
        }

        pDecl->Use.DecId.UsedFlags = DecId_UsedFlag_Local + DecId_UsedFlag_Assigned;    //      set flags to show the variable is used. (this silences warnings for unused vars 

        ParameterObjects = DefintionListAddLocal(ParameterObjects, pDecl);              //      add it to the parameter/local list (this param is added to the head of the pChain list)
    }
    iFrameAllocationIndex = 1;
    //printf("\nJust defined params\n");
    //ListDefinitions(4, ParameterObjects);
}

void UndeclareParameters(TPDeclSpec pDecl) {
    //ListDefinitions(0, pDecl);
    //ASSERT(iFrameAllocationOffset == 0);                                    // if !0 then free up of local has failed. > trouble somewhere.
    ASSERT(iFrameAllocationIndex == 1);                                     // if !0 then free up of local has failed. > trouble somewhere.
    while (pDecl) {
        ASSERT(pDecl && pDecl->Usage == DecId);
        ParameterObjects = DefintionListRemoveElement(ParameterObjects, pDecl);
        pDecl = pDecl->Use.DecId.pBrother;
    }
    //ListDefinitions(0, pDecl);
}

void DeclareLocal(TPDeclSpec pDecl) {

    //if (iFrameAllocationOffset == 0) {                                                            // This set of locals is the first in a new function
    if (iFrameAllocationIndex == 1) {                                                               // This set of locals is the first in a new function
        TPDeclSpec pD = pDecl;                                                                      //      we don't approve of locals having the same name
        while (pD!= NULL) {                                                                         //      as parameters unless they are within an inner
            ASSERT(pD && pD->Usage == DecId);                                                       //      bracketed statement list
            ASSERT(!IsTypedef(pD->Use.DecId.pTarget));                                              //
            if (FindParameterObject(pD->Use.DecId.pszName)) {                                       //
                Error(ERROR1, "Local redfinition of parameter '%s'", pD->Use.DecId.pszName);        //
            }                                                                                       //
            pD = pD->Use.DecId.pBrother;                                                            //
        }                                                                                           //
    }                                                                                               //

    TPDeclSpec pDa = pDecl;                                                                         // Check for redfinitions within this list
    while (pDa != NULL) {                                                                           //
        TPDeclSpec pD = pDa->Use.DecId.pBrother;                                                    //
        while (pD != NULL) {                                                                        //
            if (strcmp(pD->Use.DecId.pszName, pDa->Use.DecId.pszName) == 0) {                       //
                Error(ERROR1, "Local redfinition of local variable '%s'", pD->Use.DecId.pszName);   //
            }                                                                                       //
            pD = pD->Use.DecId.pBrother;                                                            //
        }                                                                                           //
        pDa = pDa->Use.DecId.pBrother;                                                              //
    }                                                                                               //

    while (pDecl) {
        ASSERT(pDecl && pDecl->Usage == DecId);
        ASSERT(!IsTypedef(pDecl->Use.DecId.pTarget));

        // InitializerProcess(pDecl);

        //iFrameAllocationOffset -= CalcSizeOf(pDecl->Use.DecId.pTarget);
        //pDecl->Use.DecId.iOffset = iFrameAllocationOffset+1;
        if (pDecl->Use.DecId.pInitializer != NULL) {
            ASSERT(pDecl->Use.DecId.pInitializer);
            ASSERT(pDecl->Use.DecId.pInitializer->Usage == uInit)
            ASSERT(pDecl->Use.DecId.pInitializer->Use.Init.pAssignment);
            int iSizeVar  = CalcSizeOf(pDecl->Use.DecId.pTarget);
            int iSizeInit = CalcSizeOf(pDecl->Use.DecId.pInitializer->Use.Init.pAssignment->pType);
            if (iSizeVar != iSizeInit) {
                pDecl->Use.DecId.pInitializer->Use.Init.pAssignment = ExprMakeCastNode(pDecl->Use.DecId.pTarget, pDecl->Use.DecId.pInitializer->Use.Init.pAssignment);
            }
            //printf("%s %d %d\n", pDecl->Use.DecId.pszName, CalcSizeOf(pDecl->Use.DecId.pTarget), CalcSizeOf(pDecl->Use.DecId.pInitializer->Use.Init.pAssignment->pType));
        }

        iFrameAllocationIndex++;
        LObjects = DefintionListAddLocal(LObjects, pDecl);
        pDecl = pDecl->Use.DecId.pBrother;
    }
    //printf("\nJust defined locals\n");
    //ListDefinitions(4, LObjects);
}


void UndeclareLocals(TPDeclSpec pDecl) {                                                // the locals were put in a list by the DeclareLocal function.
    while (pDecl) {
        //ListDefinitions(LObjects);
        ASSERT(pDecl && pDecl->Usage == DecId);
        //iFrameAllocationOffset += CalcSizeOf(pDecl->Use.DecId.pTarget);
        iFrameAllocationIndex--;
        LObjects = DefintionListRemoveElement(LObjects, pDecl);
        pDecl = pDecl->Use.DecId.pBrother;
    }
    //ListDefinitions(LObjects);
}



static WORD
PtrDest(TPDeclSpec Target) {
    while (Target) {
        switch (Target->Usage) {
            case DecPtr:    return Target->Use.DecPtr.wQual;        // where is the pointer ?
            case DecFunc:   return QualCONST;                       // Functions must be in constant
            case DecSpec:   return Target->Use.DecSpec.wQual;        // Where is the base type ?
            case DecArray:  Target = Target->Use.DecArray.pTarget;
                            break;
            default:        Error(FATAL, "PtrDest: Trouble [%d]\n", Target->Usage);
                            return 0;
        }
    }
    Error(FATAL, "PtrDest: Trouble ?\n");
    ASSERT(FALSE);
    return 0;
 }

 
#define TT(P,T) (((P)->Use.DecSpec.Type & (T)) == (T))

DWORD CalcSizeOf(TPDeclSpec pType) {
    if (!pType) return 0L;
    switch (pType->Usage) {
        case    DecId:          // Id
                Error(FATAL, "CalcSizeOf of DecId '%s' !!!\n", pType->Use.DecId.pszName);
                return 0L;
        case    DecPtr:
                switch (PtrDest(pType->Use.DecPtr.pTarget)) {
                    case QualCONST:         return SIZE_PTR_CONST;
                    case QualVOLATILE:      return SIZE_PTR_VOLATILE;
                    case QualNEAR:          return SIZE_PTR_NEAR;
                    case QualFAR:           return SIZE_PTR_FAR;
                    default:                return SIZE_PTR_DEFAULT;
                }
        case    DecArray:
                return pType->Use.DecArray.Size * CalcSizeOf(pType->Use.DecArray.pTarget);
        case    DecFunc:
                return SIZE_FUNC;
        case    DecSpec:
                if      ((pType->Use.DecSpec.Type) & TypeENUM)    return SIZE_ENUM;
                else if ((pType->Use.DecSpec.Type) & TypeSTRUCT)  return CalcStructSize(pType->Use.DecSpec.pPtr);
                else if ((pType->Use.DecSpec.Type) & TypeTYPEDEF) return CalcSizeOf(pType->Use.DecSpec.pPtr);
                else {
                    if TT(pType,(TypeLONG|TypeDOUBLE))    return SIZE_LONGDOUBLE;
                    if TT(pType,TypeDOUBLE)               return SIZE_DOUBLE;
                    if TT(pType,TypeFLOAT)                return SIZE_FLOAT;
                    if TT(pType,TypeLONG)                 return SIZE_LONG;
                    if TT(pType,TypeSHORT)                return SIZE_SHORT;
                    if TT(pType,TypeINT)                  return SIZE_INT;
                    if TT(pType,TypeCHAR)                 return SIZE_CHAR;
                    if TT(pType,TypeSIGNED)               return SIZE_INT;
                    if TT(pType,TypeUNSIGNED)             return SIZE_INT;
                    if TT(pType, TypeVOID)                return SIZE_VOID;
                    if TT(pType, TypeBOOL)                return SIZE_BOOL;
                    Error(FATAL, "CalcSizeOf: DecSpec.Type = %02x\n", pType->Use.DecSpec.Type);
                    return 0L;
                }
        default:
                Error(FATAL, "CalcSizeOf: Unknown Use\n");
                return 0L;
    }
}


static DWORD
CalcStructSize(TPStructSet Struct) {
    TPDeclSpec Elements = Struct->pElements;
    DWORD Total = 0L;
    if (!Elements) {
        Error(ERROR0, "Object contains undefined Struct/Union '%s'", Struct->szSetName);
    }
    if (Struct->fUnion) {
        while (Elements) {
            if (Elements->Usage != DecId) {
                Error(FATAL, "CalcStructSize: U Problem !\n");
            }
            Total = __max(Total, CalcSizeOf(Elements->Use.DecId.pTarget));
            Elements = Elements->Use.DecId.pBrother;
        }
    } else {
        while (Elements) {
            if (Elements->Usage != DecId) {
                Error(FATAL, "CalcStructSize: S Problem !\n");
            }
            Total += CalcSizeOf(Elements->Use.DecId.pTarget);
            Elements = Elements->Use.DecId.pBrother;
        }
    }
    return Total;
 }

int CalcStructElementOffset(TPStructSet pStruct, LPSTR pszField) {
    TPDeclSpec Elements = pStruct->pElements;
    int iTotal = 0;
    if (!Elements) {
        Error(ERROR0, "Object contains undefined Struct/Union '%s'", pStruct->szSetName);
    }
    if (pStruct->fUnion) {                                                                                      // Search a union
        while (Elements) {                                                                                      // for all elements
            if (Elements->Usage != DecId) {                                                                     //
                Error(FATAL, "CalcStructElementOffset: U Problem !\n");                                         //
            }                                                                                                   //
            if (!strcmp(pszField, Elements->Use.DecId.pszName)) {                                               //      find the name
                Elements->Use.DecId.iOffset = 0;                                                                //          All union members are at offset zero.
                return 0;                                                                                       //
            }                                                                                                   //
            if ((*Elements->Use.DecId.pszName == 0) &&                                                          //      anon sub structure?
                (IsStruct(Elements->Use.DecId.pTarget))) {                                                      //
                int i = CalcStructElementOffset(Elements->Use.DecId.pTarget->Use.DecSpec.pPtr, pszField);       //
                if (i >= 0) {                                                                                   //
                    return i;                                                                                   //
                }                                                                                               //
            }                                                                                                   //
            Elements = Elements->Use.DecId.pBrother;                                                            // next
        }
    } else {                                                                                                    // search a structure
        while (Elements) {                                                                                      // for all elements.
            if (Elements->Usage != DecId) {                                                                     //
                Error(FATAL, "CalcStructElementOffset: S Problem !\n");                                         //
            }                                                                                                   //
            if (!strcmp(pszField, Elements->Use.DecId.pszName)) {                                               //      find the name
                Elements->Use.DecId.iOffset = iTotal;                                                           //          All struct members are consecutive.
                return iTotal;                                                                                  //
            }                                                                                                   //
            if ((*Elements->Use.DecId.pszName == 0) &&                                                          //      anon sub structure?
                (IsStruct(Elements->Use.DecId.pTarget))) {                                                      //
                    int i = CalcStructElementOffset(Elements->Use.DecId.pTarget->Use.DecSpec.pPtr, pszField);   //
                    if (i >= 0) {                                                                               //
                        return iTotal + i;                                                                      //
                    }                                                                                           //
            }                                                                                                   //
            iTotal += CalcSizeOf(Elements->Use.DecId.pTarget);                                                  // next
            Elements = Elements->Use.DecId.pBrother;                                                            //
        }
    }
    return -1;
 }

TPDeclSpec CalcStructElementType(TPStructSet pStruct, LPSTR pszField) {
    TPDeclSpec Elements = pStruct->pElements;
    LONG Total = 0L;
    if (!Elements) {
        Error(ERROR0, "Object contains undefined Struct/Union '%s'.", pStruct->szSetName);
    }

    while (Elements) {
        if (Elements->Usage != DecId) {
            Error(FATAL, "CalcStructElementType: Problem !\n");
        }
        if (!strcmp(pszField, Elements->Use.DecId.pszName)) {
            return Elements->Use.DecId.pTarget;
        }
        if ((*Elements->Use.DecId.pszName == 0) &&                                                              //      anon sub structure?
            (IsStruct(Elements->Use.DecId.pTarget))) {                                                          //
            TPDeclSpec pD = CalcStructElementType(Elements->Use.DecId.pTarget->Use.DecSpec.pPtr, pszField);     //
            if (pD != NULL) {                                                                                   //
                return pD;                                                                                      //
            }                                                                                                   //
        }                                                                                                       //

        Elements = Elements->Use.DecId.pBrother;
    }
    return NULL;
 }

                                                            // *****************************************
                                                            // Can the Type be represented in an integer
BOOL TypeIsIntegral(TPDeclSpec pType) {                     // *****************************************
    if (!pType) {
        Error(FATAL, "IsIntegralType: Null.\n");
        return FALSE;
    }
    switch (pType->Usage) {
        case DecPtr:
        case DecArray:
        case DecFunc:   return TRUE;
        case DecSpec:   return (!(pType->Use.DecSpec.Type &
                                 (TypeVOID|TypeFLOAT|TypeDOUBLE|
                               // TypeSTRUCT|TypeENUM|
                                 TypeTYPEDEF)));
        case DecId: 
        default:        Error(FATAL, "IsIntegralType: What Usage [%d].\n",pType->Usage);
                        return FALSE;
    }
}

BOOL TypeIsSigned(TPDeclSpec pType) {
    return ((pType->Usage == DecSpec) && ((pType->Use.DecSpec.Type & (TypeUNSIGNED)) != TypeUNSIGNED));
}

BOOL TypeIsUnsigned(TPDeclSpec pType) {
    return (TypeIsIntegral(pType) && ((pType->Use.DecSpec.Type & (TypeUNSIGNED)) == TypeUNSIGNED));
}


                                                        // ***************************************
                                                        // Can the Type be represented in an Real
BOOL IsRealType(TPDeclSpec pType) {                     // ***************************************
    if (!pType) {
        Error(FATAL, "IsRealType: Null.\n");
        return FALSE;
    }
    switch (pType->Usage) {
        case DecPtr:
        case DecArray:
        case DecFunc:   return FALSE;
        case DecSpec:   return (pType->Use.DecSpec.Type &
                                (TypeFLOAT|TypeDOUBLE));
        case DecId: 
        default:        Error(FATAL, "IsRealType: What Usage [%d].\n",pType->Usage);
                        return FALSE;
    }
 }


BOOL        IsTypeQualifier(TPDeclSpec pTarget, int Qualifier) {
    ASSERT(pTarget);
    if (((pTarget->Usage == DecSpec) && ((pTarget->Use.DecSpec.wQual & Qualifier) == Qualifier)) ||
        ((pTarget->Usage == DecPtr) && ((pTarget->Use.DecPtr.wQual & Qualifier) == Qualifier))) {
        return TRUE;
    }
    if (pTarget->Usage == DecArray) {
        return (IsTypeQualifier(pTarget->Use.DecArray.pTarget, Qualifier));
    }
    return FALSE;
}




BOOL    TypeIsExtern(TPDeclSpec pTarget) {
    while (pTarget && (pTarget->Usage != DecSpec)) {
        if (pTarget->Usage == DecArray) { pTarget = pTarget->Use.DecArray.pTarget; }
        else if (pTarget->Usage == DecPtr) { pTarget = pTarget->Use.DecPtr.pTarget; }
        else if (pTarget->Usage == DecFunc) { pTarget = pTarget->Use.DecFunc.pReturnType; }
        else {
            ASSERT(0);
        }
    }
    return ((pTarget->Use.DecSpec.Class & ClassEXTERN) != 0);
}

/* eof */




