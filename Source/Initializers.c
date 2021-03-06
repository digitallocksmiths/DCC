// # $URL: https://eboracum-vss.digitallocksmiths.local/svn/Dls/Sean/RoyalHolloway/CC_Avr/Source/Initializers.c $
// # $Revision: 424 $


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>

#include "lex.h"
#include "typectrl.h"
#include "expr.h"
#include "GenAvr\Gen.h"
#include "main.h"

// parses initializers.
// reports errors / warnings and fixed any undefined array sizes if/when init data is present.


// ##########################################################################################
static DWORD InitializerCount(TPExprNode pInit) {           // get the length of the initializer list.
    DWORD n = 0;
    while (pInit != 0) {
        n++;
        pInit = pInit->pSibling;
    }
    return n;
}

// ######################################################################################################################
static void InitializerObject(TPDeclSpec pTarget, TPExprNode pInit, BOOL *pfWarnIfExcessFound);     // forward declaration for recursion in struct definitions.

// ##########################################################################
// #  Function: InitializerObjectArray
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
static void InitializerObjectArray(TPDeclSpec pTarget, TPExprNode pInit, BOOL *pfWarnIfExcessFound) {                 // *** Initialized Arrays ***
                                                                                                                    
    ASSERT(pInit == NULL || pInit->Usage == uInit);                                                                 
    ASSERT(pTarget->Usage == DecArray);                                                                             // we have an array for sure.
                                                                                                                    
    DWORD      dwSize = pTarget->Use.DecArray.Size;                                                                 
    DWORD      dwInit;                                                                                              
    TPDeclSpec pElement = pTarget->Use.DecArray.pTarget;                                                            
    ASSERT(pElement != NULL);                                                                                       
                                                                                                                    
                                                                                                                    // Specical behavior when init is from a string  *** It's Complicated ! ***
    if ((pElement->Usage == DecSpec) &&                                                                             // If its and array of simple types (not an array of arrays) && 
        ((pElement->Use.DecSpec.Type & TypeSTRUCT) == 0) &&                                                         //    its not a structure  &&
        (pInit != NULL && pInit->Use.Init.pAssignment)) {                                                           //    we also have initialization via assignment
        TPExprNode  pA = pInit->Use.Init.pAssignment;                                                               //      
        if (pA->Usage == uVar) {                                                                                    //      If we have an asignment from a variable
            TPDeclSpec V = FindGlobalObject(pA->Use.Var.pszIdentifier);                                             //          we can find it ...
            if (V != NULL) {                                                                                        //
                if (V->Usage == DecId && V->Use.DecId.pszInitializedStr != 0) {                                     //          is this  variable initialized by a string.
                    ASSERT(pTarget->Usage == DecArray);                                                             //              so far so good.
                    V->Use.DecId.UsedFlags = DecId_Used;                                                            //              This array will be initialized to the temporary string. So no need to create this string in 'Gen'.
                    DWORD dwInitSize = strlen(V->Use.DecId.pszInitializedStr) + 1;                                  //              initializers = it's the string length (incl zero terminator)
                    if (dwSize == 0) {                                                                              //              if our array has no given size then
                        pTarget->Use.DecArray.Size = dwInitSize;                                                    //
                    }                                                                                               //
                    if (*pfWarnIfExcessFound && pTarget->Use.DecArray.Size < dwInitSize) {                          //
                        Error(WARNING1, "InitializerObjectArray(): Too many initializers. excess will be ignored.", "");   //
                        *pfWarnIfExcessFound = FALSE;                                                               //
                    }                                                                                               //
                    return;                                                                                         //
                }                                                                                                   
            }                                                                                                       
        }                                                                                                           
    }                                                                                                               
                                                                                                                    
    if (pInit != NULL && pInit->Use.Init.pChildren) {                                                               // would expect bracketed list of initializers (but may be missing)
        pInit = pInit->Use.Init.pChildren;                                                                          
    }                                                                                                               
    dwInit = InitializerCount(pInit);                                                                               // initializer count
    if (dwSize == 0) {                                                                                              // if the declared count is zero
        dwSize = dwInit;                                                                                            //      we use the initializers to fix up the count.
        pTarget->Use.DecArray.Size = dwSize;                                                                        //
    }                                                                                                               
    else if (*pfWarnIfExcessFound && dwSize < dwInit) {                                                             // if more initializers than we want 
        Error(WARNING1, "InitializerObjectArray(): Too many initializers. excess will be ignored.", "");                   //      have a good moan at the user.
        *pfWarnIfExcessFound = FALSE;                                                                               //
    }                                                                                                               //
                                                                                                                    
    for (DWORD dwIndex = 0; dwIndex < dwSize; dwIndex++) {                                                          // for all the elements we want
        InitializerObject(pElement, pInit, pfWarnIfExcessFound);                                                    //      recurse to define each array element            
        if (pInit != NULL) {                                                                                        //      
            pInit = pInit->pSibling;                                                                                //      consume one initialization parameter per array element.
        }                                                                                                           //
    }
}

// ##########################################################################
// #  Function: InitializerObjectUnion
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
static void    InitializerObjectUnion(TPDeclSpec pTarget, TPExprNode pInit, BOOL *pfWarnIfExcessFound) {

    ASSERT(pInit == NULL || pInit->Usage == uInit);
    ASSERT(pTarget->Usage == DecSpec);

    TPStructSet S = pTarget->Use.DecSpec.pPtr;
    TPDeclSpec pElement = S->pElements;

    if (pInit != NULL && pInit->Use.Init.pChildren) {
        pInit = pInit->Use.Init.pChildren;
    }

    if (pElement != NULL) {
        ASSERT(pElement->Usage == DecId);
        InitializerObject(pElement->Use.DecId.pTarget, pInit, pfWarnIfExcessFound);
    }
    #pragma message("warn XS here")
}

// ##########################################################################
// #  Function: InitializerObjectStructure
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
static void    InitializerObjectStructure(TPDeclSpec pTarget, TPExprNode pInit, BOOL *pfWarnIfExcessFound) {           // Structure generation.
   
    ASSERT(pInit == NULL || pInit->Usage == uInit);
    ASSERT(pTarget->Usage == DecSpec);

    TPStructSet S = pTarget->Use.DecSpec.pPtr;
    TPDeclSpec pElement = S->pElements;
    
    if (pInit != NULL && pInit->Use.Init.pChildren) {
        pInit = pInit->Use.Init.pChildren;
    }

    while (pElement != NULL) {
        ASSERT(pElement->Usage == DecId);
        InitializerObject(pElement->Use.DecId.pTarget, pInit, pfWarnIfExcessFound);
        pElement = pElement->Use.DecId.pBrother;
        if (pInit != NULL) {
            pInit = pInit->pSibling;
        }
    }
#pragma message("warn XS here")

}


// ##########################################################################
// #  Function: InitializerObject
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
static void InitializerObject(TPDeclSpec pTarget, TPExprNode pInit, BOOL *pfWarnIfExcessFound) {
    
    ASSERT(pInit == NULL || pInit->Usage == uInit);

    switch (pTarget->Usage) {
        case    DecId:          // Id
        case    DecFunc:        // Function 
            Error(FATAL, "InitializerObject():  Unexpected Usage '%d'\n", pTarget->Usage);
            return;

        case    DecArray:
            InitializerObjectArray(pTarget, pInit, pfWarnIfExcessFound);
            return;

        case    DecPtr:
            if (pInit != NULL) {
                ASSERT(pInit->Usage == uInit);
                TPExprNode Val = pInit->Use.Init.pAssignment;
                if (pInit->Use.Init.pChildren != NULL) {                            // start of bracketed set when singleton is expected
                    Error(ERROR1, "InitializerObject(): Unexpected structure in initializer data for variable/field ", "");
                    return;
                }
                if (Val && Val->Usage == uConst) {
                    return;
                }
                if (Val && Val->Usage == uVar) {
                    if (Val->pType->Usage == DecArray) {
                        TPDeclSpec pD = FindGlobalObject(Val->Use.Var.pszIdentifier);
                        if (pD != NULL) {                                                       // this array is used to initialize a pointer so we need to keep it.
                            ASSERT(pD->Usage == DecId);
                            pD->Use.DecId.UsedFlags = DecId_Refed;
                        }
                    }
                    return;
                }
                // also permit addr of var
                if (Val && Val->Usage == uUnary) {
                    if (Val->Use.Unary.Op == unAddr) {
                        TPExprNode E = Val->Use.Unary.pOperand;
                        ASSERT(E != NULL);
                        if (E->Usage == uVar) {
                            return;
                        }
                    }
                }
                //ParseExpr(Val, 1);
                Error(ERROR1, "InitializerObject(): Illegal static initialization.", NULL);
            }
            return;

        case    DecSpec:
            if ((pTarget->Use.DecSpec.Type) & TypeSTRUCT) {
                TPStructSet p = pTarget->Use.DecSpec.pPtr;
                if (p->fUnion) InitializerObjectUnion(pTarget, pInit, pfWarnIfExcessFound);
                else           InitializerObjectStructure(pTarget, pInit, pfWarnIfExcessFound);
                return;
            }
            else if ((pTarget->Use.DecSpec.Type) & TypeENUM) {
                //TPEnumSet e = pTarget->Use.DecSpec.pPtr;
                //InitializerObjectEnum(pTarget, pInit);
                return;
            }
            else if ((pTarget->Use.DecSpec.Type) & TypeTYPEDEF) {
                //InitializerObjectTypedef(pTarget, pInit);
                return;
            }
            else {
                //InitializerObjectBasetype(pTarget, pInit);

                if (pInit != NULL) {
                    ASSERT(pInit->Usage == uInit);

                    if (pInit->Use.Init.pChildren != NULL) {                            // start of braketed set when singleton is expected
                        Error(ERROR1, "Unexpected structure in initializer data for variable/field ", "");
                    }
                    else {
                        TPExprNode pVal = pInit->Use.Init.pAssignment;
                        ASSERT(pVal != NULL);
                        if (pVal->Usage != uConst) {
                            Error(ERROR1, "GenDataObjectBasetype(): Non constant integer in initialization.");
                        }
                    }
                }
                return;
            }
            return;

        default:
            Error(FATAL,"InitializerObject(): Unknown Useage '%d'\n", pTarget->Usage);
            return;
        }

}


// ##########################################################################
// #  Function: InitializerProcess
// #        *public* <todo: task brief description>
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
void InitializerProcess(TPDeclSpec pDecl) {
    BOOL fWarnExcess = TRUE;
    if (pDecl->Usage == DecId) {
        ASSERT(pDecl->Use.DecId.pTarget != NULL);
        if (GenIsData(pDecl->Use.DecId.pTarget->Usage) &&
            (pDecl->Use.DecId.pInitializer)) {
            InitializerObject(pDecl->Use.DecId.pTarget, pDecl->Use.DecId.pInitializer, &fWarnExcess);
        }
    }
}

/* eof */
