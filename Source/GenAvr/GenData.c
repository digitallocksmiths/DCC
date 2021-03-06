// # $URL: https://eboracum-vss.digitallocksmiths.local/svn/Dls/Sean/RoyalHolloway/CC_Avr/Source/GenData.c $
// # $Revision: 397 $


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>
#include "..\Utilities\Console.h"

#include "..\lex.h"
#include "..\typectrl.h"
#include "..\expr.h"
#include "GenAsm.h"
#include "Gen.h"
#include "GenData.h"
#include "..\main.h"


static LPSTR sign_unsign(WORD T) {
    if ((T & TypeUNSIGNED) == TypeUNSIGNED) return "unsigned ";
    if ((T & TypeSIGNED) == TypeSIGNED)   return "signed ";
    return "";
}


#define TT(D,T) (((D) & (T)) == (T))

static char baComent[1024];

static void GenObjectComment(TPDeclSpec pDecl) {
    int n = 0;

    //printf("\n");  ParseDeclSpec(1, pDecl, FALSE);

    while (pDecl) {
        switch (pDecl->Usage) {
        case    DecId:          // Id
        case    DecFunc:        // Function 
            Error(FATAL, "GenBssObjectComment():  Unexpected Useage '%d'\n", pDecl->Usage);
            goto exit;

        case    DecArray:
            n += sprintf(&baComent[n], "Array[%ld] of ", pDecl->Use.DecArray.Size);
            pDecl = pDecl->Use.DecArray.pTarget;
            break;

        case    DecPtr:
            switch (pDecl->Use.DecPtr.wQual) {
            case QualCONST:    n += sprintf(&baComent[n], "constant pointer\n");  break;
            case QualVOLATILE: n += sprintf(&baComent[n], "volatile pointer\n");  break;
            case QualNEAR:     n += sprintf(&baComent[n], "near pointer\n");      break;
            case QualFAR:      n += sprintf(&baComent[n], "far pointer\n");       break;
            default:           n += sprintf(&baComent[n], "(generic) pointer\n");   break;
            }
            goto exit;

        case    DecSpec:
            if ((pDecl->Use.DecSpec.Type) & TypeSTRUCT) {
                TPStructSet p = pDecl->Use.DecSpec.pPtr;
                if (p->fUnion) n += sprintf(&baComent[n], "union '%s'\n", p->szSetName);
                else           n += sprintf(&baComent[n], "structure '%s'\n", p->szSetName);
            }
            else if ((pDecl->Use.DecSpec.Type) & TypeENUM) {
                TPEnumSet e = pDecl->Use.DecSpec.pPtr;
                n += sprintf(&baComent[n], "enum '%s'\n", e->pszSetName);
            }
            else if ((pDecl->Use.DecSpec.Type) & TypeTYPEDEF) {
                n += sprintf(&baComent[n], "typedef not yet supported\n");
                //ParseDeclSpec(pDecl->Use.DecSpec.Ptr, fDoBrothers); 
            }
            else {
                n += sprintf(&baComent[n], "(");
                switch (pDecl->Use.DecSpec.wQual) {
                case QualCONST:    n += sprintf(&baComent[n], "constant ");  break;
                case QualVOLATILE: n += sprintf(&baComent[n], "volatile ");  break;
                case QualNEAR:     n += sprintf(&baComent[n], "near ");      break;
                case QualFAR:      n += sprintf(&baComent[n], "far ");       break;
                default:           n += sprintf(&baComent[n], "");   break;
                }
                if   TT(pDecl->Use.DecSpec.Type, (TypeLONG | TypeDOUBLE))n += sprintf(&baComent[n], "long double");
                else if TT(pDecl->Use.DecSpec.Type, TypeDOUBLE)          n += sprintf(&baComent[n], "double");
                else if TT(pDecl->Use.DecSpec.Type, TypeFLOAT)           n += sprintf(&baComent[n], "float");
                else if TT(pDecl->Use.DecSpec.Type, TypeLONG)            n += sprintf(&baComent[n], "%slong", sign_unsign(pDecl->Use.DecSpec.Type));
                else if TT(pDecl->Use.DecSpec.Type, TypeSHORT)           n += sprintf(&baComent[n], "%sshort ", sign_unsign(pDecl->Use.DecSpec.Type));
                else if TT(pDecl->Use.DecSpec.Type, TypeINT)             n += sprintf(&baComent[n], "%sint", sign_unsign(pDecl->Use.DecSpec.Type));
                else if TT(pDecl->Use.DecSpec.Type, TypeCHAR)            n += sprintf(&baComent[n], "%schar", sign_unsign(pDecl->Use.DecSpec.Type));
                else if TT(pDecl->Use.DecSpec.Type, TypeSIGNED)          n += sprintf(&baComent[n], "signed");
                else if TT(pDecl->Use.DecSpec.Type, TypeUNSIGNED)        n += sprintf(&baComent[n], "unsigned");
                else if TT(pDecl->Use.DecSpec.Type, TypeVOID)            n += sprintf(&baComent[n], "void");
                else                                                     n += sprintf(&baComent[n], "unknown type 0x%04x", pDecl->Use.DecSpec.Type);
                n += sprintf(&baComent[n], ")\n");
            }
            goto exit;

        default:
            Error(FATAL, "GenBssObjectComment(): Unknown Useage '%d'\n", pDecl->Usage);
            return;
        }
    }

exit:
    if (CmdLine.fEcho) {
        ConsolePrintf(CON_CYAN, baComent);
    }
    fprintf(hGlbOut, baComent);

}

// ##########################################################################################
// Data segment generator


static void SetupConstInitializer(TPDeclSpec T, LPSTR pszOpcode, LPSTR pszOperand, LPSTR pszComment, __int64 nVal, LPSTR pszName) {

    ASSERT(T->Usage == DecSpec || T->Usage == DecPtr);

    switch (CalcSizeOf(T)) {

    case 1: sprintf(pszOpcode, ASM_DIRECTIVE_BYTE);                                                                             // size = byte
        if ((T->Use.DecSpec.Type & TypeUNSIGNED) == TypeUNSIGNED) sprintf(pszOperand, "%hhu", (unsigned char)(nVal & 0xFF));    //          unsigned
        else                                                      sprintf(pszOperand, "%hhd", (signed char)(nVal & 0xFF));      //          signed
        if (pszComment != NULL) {                                                                                               // ? comment wanted?
            if (isprint((unsigned char)(nVal & 0xFF))) {                                                                        //
                sprintf(pszComment, "      '%c' 0x%02x -> %s", (char)nVal, (unsigned char)(nVal & 0xFF), pszName);              //          with printable charater
            }                                                                                                                   //                
            else {                                                                                                              //
                sprintf(pszComment, "          0x%02x -> %s", (unsigned char)(nVal & 0xFF), pszName);                           //          without printable character
            }                                                                                                                   //
        }                                                                                                                       //
        return;                                                                                                                 //  return happy

    case 2: 
#ifdef ASM_DIRECTIVE_SHORT
        sprintf(pszOpcode, ASM_DIRECTIVE_SHORT);                                                                                // size = short
        if ((T->Use.DecSpec.Type & TypeUNSIGNED) == TypeUNSIGNED)  sprintf(pszOperand, "%hu", (unsigned short)(nVal & 0xFFFF)); //          unsigned
        else                                                       sprintf(pszOperand, "%hd", (signed short)(nVal & 0xFFFF));   //          signed
#else 
        sprintf(pszOpcode, ASM_DIRECTIVE_BYTE);                                                                                 // size = short
        if ((T->Use.DecSpec.Type & TypeUNSIGNED) == TypeUNSIGNED)  sprintf(pszOperand, "%hhu, %hhu", LOBYTE((unsigned short)(nVal & 0xFFFF)), HIBYTE((unsigned short)(nVal & 0xFFFF))); //          unsigned
        else                                                       sprintf(pszOperand, "%hhd, %hhd", LOBYTE((signed short)(nVal & 0xFFFF)),   LOBYTE((signed short)(nVal & 0xFFFF)));   //          signed
#endif // ASM_DIRECTIVE_SHORT
        if (pszComment != NULL) {                                                                                               // ? comment wanted?
            sprintf(pszComment, "        0x%04x -> %s", (unsigned short)(nVal & 0xFFFF), pszName);                              //
        }                                                                                                                       //
        return;                                                                                                                 //  return happy

    case 4: 
#ifdef ASM_DIRECTIVE_LONG
        sprintf(pszOpcode, ASM_DIRECTIVE_LONG); ;                                                                               // size = long
        if ((T->Use.DecSpec.Type & TypeUNSIGNED) == TypeUNSIGNED)  sprintf(pszOperand, "%u", (unsigned int)nVal);               //          unsigned
        else                                                       sprintf(pszOperand, "%d", (signed int)nVal);                 //          signed
#else
        sprintf(pszOpcode, ASM_DIRECTIVE_BYTE); ;                                                                               // size = long
        if ((T->Use.DecSpec.Type & TypeUNSIGNED) == TypeUNSIGNED)  sprintf(pszOperand, "%hhu, %hhu, %hhu, %hhu", LOBYTE(LOWORD((unsigned int)nVal)), HIBYTE(LOWORD((unsigned int)nVal)), LOBYTE(HIWORD((unsigned int)nVal)), HIBYTE(HIWORD((unsigned int)nVal)));   // unsigned
        else                                                       sprintf(pszOperand, "%hhd, %hhd, %hhd, %hhd", LOBYTE(LOWORD((signed int)nVal)),   HIBYTE(LOWORD((signed int)nVal)),   LOBYTE(HIWORD((signed int)nVal)),   HIBYTE(HIWORD((signed int)nVal)));     // signed
#endif // ASM_DIRECTIVE_LONG
        if (pszComment != NULL) {                                                                                               // ? comment wanted?
            sprintf(pszComment, "    0x%08x -> %s", (unsigned int)(nVal & 0xFFFFFFFFL), pszName);                               //
        }                                                                                                                       //
        return;                                                                                                                 //  return happy

    default: sprintf(pszOpcode, "; unknown size");                                                                              // size unknown.
        Error(FATAL, "SetupConstInitializer(): Unsuported size of variable '%s', %d", pszName, CalcSizeOf(T));
        return ;                                                                                                                //  return not happy 
    }
}


static void SetupVarInitializer(TPDeclSpec T, LPSTR pszOpcode, LPSTR pszOperand, LPSTR pszComment, LPSTR pszVar, LPSTR pszName) {       // when the operand is a string (no need to calculate it or look it up)

    ASSERT(T->Usage == DecSpec || T->Usage == DecPtr);

    sprintf(pszOperand, "%s", pszVar);
    if (pszComment != NULL) {
            sprintf(pszComment, "               -> %s",  pszName);
    }

    switch (CalcSizeOf(T)) {
    case 1: sprintf(pszOpcode, ASM_DIRECTIVE_BYTE);
        break;
    case 2: sprintf(pszOpcode, ASM_DIRECTIVE_SHORT);
        break;
    case 4: sprintf(pszOpcode, ASM_DIRECTIVE_LONG);
        break;
    default: sprintf(pszOpcode, "; unknown size");
        Error(FATAL, "SetupVarInitializer(): Unknown size of variable '%s' %d", pszName, CalcSizeOf(T));
    }
}

static DWORD InitializerCount(TPExprNode pInit) {           // get the length of the initializer list.
    DWORD n = 0;
    while (pInit != 0) {
        n++;
        pInit = pInit->pSibling;
    }
    return n;
}

// ######################################################################################################################
static void GenDataObject(LPSTR pszName, TPDeclSpec pTarget, TPExprNode pInit);     // forward declaration for recursion in struct definitions.


                                                                                    
// ##########################################################################
// #  Function: GenDataObjectString
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
static void GenDataObjectString(TPDeclSpec pTarget, LPSTR pszInit, LPSTR pszName) {         // Arrays Initialized by Strings
    char szOpcode[32];
    char szOperand[32];
    char szComment[256];
    char szName[256];
    DWORD dwPadding;

    DWORD dwIndex = 0;
    ASSERT(pTarget->Usage == DecArray);
//#pragma message("************** GenDataObjectString() where is the defined array size taken from?")



    int iNameLen = strlen(pszName);
    sprintf_s(szName, sizeof(szName), "%s[%ld]", pszName, dwIndex);

    DWORD dwArraySize = pTarget->Use.DecArray.Size;
    DWORD dwLen = strlen(pszInit)+1;                       // number of initializers
    if (dwArraySize == 0) {
        dwArraySize = dwLen;
        pTarget->Use.DecArray.Size = dwArraySize;
    }

    if (dwArraySize < dwLen) {
        //WarningGen("To many initializers", pszName);
        dwLen = dwArraySize;
    }
    dwPadding = dwArraySize - dwLen;
    
    while (dwLen--) {
        sprintf_s(&szName[iNameLen], sizeof(szName)- iNameLen, "[%ld]", dwIndex++);
        SetupConstInitializer(pTarget->Use.DecArray.pTarget, szOpcode, szOperand, szComment, *pszInit, szName);
        GenAsm(NULL, szOpcode, szOperand, szComment);
        if (dwIndex == 1) {
            memset(szName, '-', iNameLen);
        }
        pszInit++;
    }

    //sprintf_s(szComment, sizeof(szComment), "               -> packed to %lu elements", dwSize);
    memset(szName, ' ', iNameLen);
    while (dwPadding--) {
        sprintf_s(&szName[iNameLen], sizeof(szName) - iNameLen, "[%ld]", dwIndex++);
        SetupConstInitializer(pTarget->Use.DecArray.pTarget, szOpcode, szOperand, szComment, 0, szName);
        GenAsm(NULL, szOpcode, szOperand, szComment);
    }
}


// ##########################################################################
// #  Function: GenDataObjectPointer
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
static void GenDataObjectPointer(LPSTR pszName, TPDeclSpec pTarget, TPExprNode pInit) {                                                           // Initialized pointers

    char szOpcode[64];
    char szOperand[64];
    char szComment[64];

    szOpcode[0] = 0;
    szOperand[0] = 0;
    szComment[0] = 0;

    if (pInit != NULL) {
        ASSERT(pInit->Usage == uInit);
        TPExprNode Val = pInit->Use.Init.pAssignment;

        if (pInit->Use.Init.pChildren != NULL) {                            // start of bracketed set when singleton is expected
            //WarningGen("Unexpected structure in initializer data for variable/field ", pszName);
            SetupConstInitializer(pTarget, szOpcode, szOperand, szComment, 0, pszName);
        }

        if (Val->Usage == uConst) {                                                                         // Const = OK
            unsigned __int64    nVal;
            nVal = Val->Use.Const.lInteger;
            SetupConstInitializer(pTarget, szOpcode, szOperand, szComment, nVal, pszName);
            GenAsm(NULL, szOpcode, szOperand, szComment);
            return;
        }
        if ((Val->Usage == uVar) && (Val->pType->Usage == DecArray)) {                                      // var, only if it is an array = OK.
            SetupVarInitializer(pTarget, szOpcode, szOperand, szComment, Val->Use.Var.pszIdentifier, pszName);
            GenAsm(NULL, szOpcode, szOperand, szComment);
            return;
        }
        if ((Val->Usage == uVar) && (Val->pType->Usage == DecFunc)) {                                      // var, only if it is an function = OK.
            SetupVarInitializer(pTarget, szOpcode, szOperand, szComment, Val->Use.Var.pszIdentifier, pszName);
            GenAsm(NULL, szOpcode, szOperand, szComment);
            return;
        }
        if ((Val && Val->Usage == uUnary) &&                                                                // addr of var = OK
            (Val->Use.Unary.Op == unAddr)) {
            TPExprNode E = Val->Use.Unary.pOperand;
            ASSERT(E->Usage == uVar);
            SetupVarInitializer(pTarget, szOpcode, szOperand, szComment, E->Use.Var.pszIdentifier, pszName);
            GenAsm(NULL, szOpcode, szOperand, szComment);
            return;

        }
        Error(FATAL, "GenDataObjectPointer(): Non constant pointer value in initialization of ");
    }
    else {
        SetupConstInitializer(pTarget, szOpcode, szOperand, szComment, 0, pszName);
    }

    GenAsm(NULL, szOpcode, szOperand, szComment);
}

// ##########################################################################
// #  Function: GenDataObjectArray
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
static void GenDataObjectArray(LPSTR pszName, TPDeclSpec pTarget, TPExprNode pInit) {                      // *** Initialized Arrays ***
    char szName[256];

    ASSERT(pInit == NULL || pInit->Usage == uInit);
    ASSERT(pTarget->Usage == DecArray);                                                             // we have an array for sure.

    DWORD      dwSize = pTarget->Use.DecArray.Size;
    DWORD      dwInit;
    TPDeclSpec pElement = pTarget->Use.DecArray.pTarget;
    ASSERT(pElement != NULL);

                                                                                                    // Specical behavior when init is from a string  *** It's Complicated ! ***
    if ((pElement->Usage == DecSpec) &&                                                             // If its and array of simple types (not an array of arrays) && 
        ((pElement->Use.DecSpec.Type & TypeSTRUCT) == 0) &&                                         //    its not a structure  &&
        (pInit != NULL && pInit->Use.Init.pAssignment)) {                                           //    we also have initialization via assignment
        TPExprNode  pA = pInit->Use.Init.pAssignment;                                               //      
        if (pA->Usage == uVar) {                                                                    //      If we have an asignment from a variable
            TPDeclSpec V = FindGlobalObject(pA->Use.Var.pszIdentifier);                             //          we can find it ...
            if (V != NULL) {                                                                        //
                if (V->Usage == DecId && V->Use.DecId.pszInitializedStr != 0) {                     //          is this  variable initialized by a string.
                    ASSERT(pTarget->Usage == DecArray);                                             //              so far so good.
                    //if (dwSize == 0) {                                                            //              if our array has no given size then
                    //    dwSize = strlen(V->Use.DecId.pszInitializedStr) + 1;                      //                  it's the string length (incl zero terminator)
                    //    pTarget->Use.DecArray.Size = dwSize;                                      //
                    //}                                                                             //
                    GenDataObjectString(pTarget, V->Use.DecId.pszInitializedStr, pszName);    //              create the initialized data from the string data.          
                    return;
                }
            }
        }
    }

    if (pInit != NULL && pInit->Use.Init.pChildren) {                                               // would expect bracketed list of initializers (but may be missing)
        pInit = pInit->Use.Init.pChildren;
    }
    dwInit = InitializerCount(pInit);                                                               // initializer count
    if (dwSize == 0) {                                                                              // if the declared count is zero
        dwSize = dwInit;                                                                            //      we use the initializers to fix up the count.
        pTarget->Use.DecArray.Size = dwSize;                                                        //
    }
    //else if (dwSize < dwInit) {                                                                     // if more initializers than we want 
    //    WarningGen("GenDataObjectArray(): Too many initializors for ", pszName);                    //      have a good moan at the user.
    //}                                                                                               //

    int iNameLen = strlen(pszName);
    sprintf_s(szName, sizeof(szName), "%s", pszName);
    for (DWORD dwIndex = 0; dwIndex < dwSize; dwIndex++) {                                          // for all the elements we want
        sprintf_s(&szName[iNameLen], sizeof(szName)-iNameLen, "[%ld]", dwIndex);                    //      text stuff to make variable name+index
        if (dwIndex == 1) {                                                                         //
            memset(szName, '-', iNameLen);                                                          //
        }                                                                                           //
                                                                                                    //
        ASSERT(pInit == NULL || pInit->Usage == uInit);                                             //
                                                                                                    //
        GenDataObject(szName, pElement, pInit);                                               //      recurse to define each array element            
                                                                                                    //
        //pElement = pElement->Use.DecId.pBrother;                                                  //
        if (pInit != NULL) {                                                                        //      
            pInit = pInit->pSibling;                                                                //      consume one initialization parameter per array element.
        }                                                                                           //
    }
}


// ##########################################################################
// #  Function: GenDataObjectUnion
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
static void    GenDataObjectUnion(LPSTR pszName, TPDeclSpec pTarget, TPExprNode pInit) {
    char szName[256];

    ASSERT(pInit == NULL || pInit->Usage == uInit);
    ASSERT(pTarget->Usage == DecSpec);

    TPStructSet S = pTarget->Use.DecSpec.pPtr;
    TPDeclSpec pElement = S->pElements;

    if (pInit != NULL && pInit->Use.Init.pChildren) {
        pInit = pInit->Use.Init.pChildren;
    }

    DWORD dwUnionSize = CalcSizeOf(pTarget);
    DWORD dwFirstFieldSize = 0L;

    if (pElement != NULL) {
        ASSERT(pElement->Usage == DecId);
        dwFirstFieldSize = CalcSizeOf(pElement->Use.DecId.pTarget);
        sprintf_s(szName, sizeof(szName), "%s.%s", pszName, pElement->Use.DecId.pszName);
        GenDataObject(szName, pElement->Use.DecId.pTarget, pInit);
    }
    
    if (dwUnionSize > dwFirstFieldSize) {                                                       // if the field we generated is smaller than the union
        char szComment[256];
        DWORD dwPacking = dwUnionSize - dwFirstFieldSize;
        sprintf_s(szComment, sizeof(szComment), "               -> %s packed to size %lu", pszName, dwUnionSize);
        while (dwPacking--) {
            GenAsm(NULL, ASM_DIRECTIVE_BYTE, "0", szComment);
            szComment[0] = 0;
        }
    }
}

// ##########################################################################
// #  Function: GenDataObjectStructure
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
static void    GenDataObjectStructure(LPSTR pszName, TPDeclSpec pTarget, TPExprNode pInit) {           // Structure generation.
    char szName[256];
    
    ASSERT(pInit == NULL || pInit->Usage == uInit);
    ASSERT(pTarget->Usage == DecSpec);

    TPStructSet S = pTarget->Use.DecSpec.pPtr;
    TPDeclSpec pElement = S->pElements;
    
    if (pInit != NULL && pInit->Use.Init.pChildren) {
        pInit = pInit->Use.Init.pChildren;
    }

    while (pElement != NULL) {
        ASSERT(pElement->Usage == DecId);
        sprintf_s(szName, sizeof(szName), "%s.%s", pszName, pElement->Use.DecId.pszName);
        GenDataObject(szName, pElement->Use.DecId.pTarget, pInit);
        pElement = pElement->Use.DecId.pBrother;
        if (pInit != NULL) {
            pInit = pInit->pSibling;
        }
    }

}

// ##########################################################################
// #  Function: GenDataObjectEnum
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
static void    GenDataObjectEnum(FILE *hOut, LPSTR pszName, TPDeclSpec pTarget, TPExprNode pInit) {                        // Enum value
    char szOpcode[32];
    char szOperand[32];
    char szComment[128];

#pragma message("    **** GenDataObjectEnum(): improvement. Comment could be the enum symbol name?")
    ASSERT(pInit->Usage == uInit);
    TPExprNode Val = pInit->Use.Init.pAssignment;

    int        nVal;
    if (Val->Usage != uConst) {
        Error(FATAL, "GenDataObjectEnum():  Non constant interger in Enum initialization of ");
        nVal = 0;
    }
    else {
        nVal = Val->Use.Const.lInteger;
    }

    SetupConstInitializer(pTarget, szOpcode, szOperand, szComment, nVal, pszName);
    GenAsm(NULL, szOpcode, szOperand, szComment);
}

// ##########################################################################
// #  Function: GenDataObjectTypedef
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
static void    GenDataObjectTypedef(LPSTR pszName, TPDeclSpec pTarget, TPExprNode pInit) {
    Error(FATAL, "GenDataObjectTypedef(): Unimplemented");
}

// ##########################################################################
// #  Function: GenDataObjectBasetype
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
static void    GenDataObjectBasetype(LPSTR pszName, TPDeclSpec pTarget, TPExprNode pInit) {
    
    char szOpcode[32];
    char szOperand[32];
    char szComment[256];
    unsigned __int64   nVal = 0L;

    if (pInit != NULL) {
        ASSERT(pInit->Usage == uInit);
       
        if (pInit->Use.Init.pChildren != NULL) {                            // start of braketed set whee singleton is expected
            // WarningGen("Unexpected structure in initializer data for variable/field ", pszName);
            nVal = 0;
        }
        else {
            TPExprNode pVal = pInit->Use.Init.pAssignment;
            ASSERT(pVal != NULL);
            if (pVal->Usage != uConst) {
                //Error(FATAL, "GenDataObjectBasetype(): Non constant integer in initialization.");
                nVal = 0;
            }
            else {
                nVal = pVal->Use.Const.lInteger;
            }
        }
    }
    SetupConstInitializer(pTarget, szOpcode, szOperand, szComment, nVal, pszName);

    GenAsm(NULL, szOpcode, szOperand, szComment);
}


// ##########################################################################
// #  Function: GenDataObject
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
static void GenDataObject(LPSTR pszName, TPDeclSpec pTarget, TPExprNode pInit) {
    
    ASSERT(pInit == NULL || pInit->Usage == uInit);

    switch (pTarget->Usage) {
        case    DecId:          // Id
        case    DecFunc:        // Function 
            Error(FATAL, "GenDataObject():  Unexpected Useage '%d'\n", pTarget->Usage);
            return;

        case    DecArray:
            GenDataObjectArray(pszName, pTarget, pInit);
            return;

        case    DecPtr:
            GenDataObjectPointer(pszName, pTarget, pInit);
            return;

        case    DecSpec:
            // consider using BOOL IsIntegralType()????
            if ((pTarget->Use.DecSpec.Type) & TypeSTRUCT) {
                TPStructSet p = pTarget->Use.DecSpec.pPtr;
                if (p->fUnion) GenDataObjectUnion(pszName, pTarget, pInit);
                else           GenDataObjectStructure(pszName, pTarget, pInit);
                return;
            }
            else if ((pTarget->Use.DecSpec.Type) & TypeENUM) {
                TPEnumSet e = pTarget->Use.DecSpec.pPtr;
                GenDataObjectEnum(hGlbOut, pszName, pTarget, pInit);
                return;
            }
            else if ((pTarget->Use.DecSpec.Type) & TypeTYPEDEF) {
                GenDataObjectTypedef(pszName, pTarget, pInit);
                return;
            }
            else {
                GenDataObjectBasetype(pszName, pTarget, pInit);
                return;
            }
            return;

        default:
            Error(FATAL, "GenDataObject(): Unknown Useage '%d'\n", pTarget->Usage);
            return;
        }

}


// ##########################################################################
// #  Function: GenData
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
void    GenConst(TPDeclSpec pDeclList) {
    //char szOperand[32];
    TPDeclSpec pDecl;

    GenAsm(NULL, NULL, NULL, "##########################");
    GenAsm(NULL, NULL, NULL, "# Start of CONST segment #");
    GenAsm(NULL, ASM_DIRECTIVE_SEGMENT_BEGIN_CONST, "", "##########################");

    for (pDecl = pDeclList; pDecl; pDecl = pDecl->pChain) {                                 // auto generated string initializers
        if ((pDecl->Usage == DecId) &&                                                              // Must be DecId
            GenIsData(pDecl->Use.DecId.pTarget->Usage) &&                                           // Id's use must be storage rather than definition or code.
            (pDecl->Use.DecId.pszInitializedStr)) {                                                 // If sz pointer used here it's an auto-gen string.

            TPDeclSpec pTarget = pDecl->Use.DecId.pTarget;
            ASSERT(pTarget->Usage == DecArray);
            if (pDecl->Use.DecId.UsedFlags == DecId_Used) {                                         //  we can skip this initialization because the array contents will be used to initialize a defined variable array.
                ;
            }
            else if (pDecl->Use.DecId.UsedFlags == DecId_Refed) {                                   // we need a ROM copy of the data to be referenced by an initialized pointer.
                GenAsmOut(pDecl->Use.DecId.pszName, NULL, NULL, "", FALSE, TRUE);
                GenObjectComment(pTarget);
                GenDataObjectString(pTarget, pDecl->Use.DecId.pszInitializedStr, "");
            }
            else {
//                Error(FATAL, "GenConst(): odd variable UsedFlags setting  = %x", pDecl->Use.DecId.UsedFlags);
            }
        }
    }

    for (pDecl = pDeclList; pDecl; pDecl = pDecl->pChain) {
        if (pDecl->Usage == DecId) {
            //printf("++++ %s\n", pDecl->Use.DecId.pszName);
            TPDeclSpec pTarget = pDecl->Use.DecId.pTarget;

            if (GenIsData(pTarget->Usage) && IsTypeQualifierConst(pTarget)) {
                if (TypeIsExtern(pTarget)) {
                    GenAsmOut("", ".extern", pDecl->Use.DecId.pszName, "", FALSE, FALSE);
                    GenObjectComment(pTarget);
                }
                else {
                    GenAsmOut(pDecl->Use.DecId.pszName, NULL, NULL, "", FALSE, TRUE);
                    GenObjectComment(pTarget);
                    GenDataObject(pDecl->Use.DecId.pszName, pTarget, pDecl->Use.DecId.pInitializer);
                }
            }
        }
    }

    GenAsm(NULL, ASM_DIRECTIVE_SEGMENT_END, NULL, "=== End of CONST segment ===\n\n");

}


// ##########################################################################
// #  Function: GenData
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
void GenData(TPDeclSpec pDeclList) {
    char szOperand[32];
    TPDeclSpec pDecl;

    GenAsm(NULL, NULL,                              NULL,   "#########################");
    GenAsm(NULL, NULL,                              NULL,   "# Start of INIT segment #");
    GenAsm(NULL, ASM_DIRECTIVE_SEGMENT_BEGIN_INIT,  "",     "#########################");

    GenAsm("", "", "", "This is the source of the initialization data");
    for (pDecl = pDeclList; pDecl; pDecl = pDecl->pChain) {
        if (pDecl->Usage == DecId) {
            TPDeclSpec pTarget = pDecl->Use.DecId.pTarget;
            if (GenIsData(pTarget->Usage) && !IsTypeQualifierConst(pTarget) && (pDecl->Use.DecId.pInitializer)) {
                TPDeclSpec pTarget = pDecl->Use.DecId.pTarget;
                ASSERT(pTarget);
                GenAsmOut(";", pDecl->Use.DecId.pszName, NULL, "", FALSE, FALSE);
                GenObjectComment(pTarget);
                GenDataObject(pDecl->Use.DecId.pszName, pTarget, pDecl->Use.DecId.pInitializer);
            }
        }
    }

    GenAsm(NULL, NULL, NULL, "#########################");
    GenAsm(NULL, ASM_DIRECTIVE_SEGMENT_BEGIN_DATA, "", "# Start of DATA segment #");
    GenAsm(NULL, "", "", "#########################");

    GenAsm("", "", "", "This is where the initialization data will be copied to");

    for (pDecl = pDeclList; pDecl; pDecl = pDecl->pChain) {
        if (pDecl->Usage == DecId) {
            TPDeclSpec pTarget = pDecl->Use.DecId.pTarget;
            if (GenIsData(pTarget->Usage) && !IsTypeQualifierConst(pTarget) && (pDecl->Use.DecId.pInitializer)) {
                TPDeclSpec pTarget = pDecl->Use.DecId.pTarget;
                DWORD dwSz = CalcSizeOf(pDecl->Use.DecId.pTarget);
                TPDeclSpec pD = pDecl->Use.DecId.pTarget;
                while (pD && (pD->Usage != DecSpec)) {
                    if (pD->Usage == DecArray) { pD = pD->Use.DecArray.pTarget; }
                    else if (pD->Usage == DecPtr) { pD = pD->Use.DecPtr.pTarget; }
                    else if (pD->Usage == DecFunc) { pD = pD->Use.DecFunc.pReturnType; }
                    else {
                        ASSERT(0);
                    }
                }
                ASSERT(pD != NULL);
                WORD bClass = pD->Use.DecSpec.Class;
                BOOL fGlobal = ((bClass & ClassSTATIC) != ClassSTATIC);
                if (dwSz == 0) {
                    GenAsmOut(pDecl->Use.DecId.pszName, "", "", "", FALSE, fGlobal);
                }
                else {
                    sprintf(szOperand, "%4d", dwSz);
                    GenAsmOut(pDecl->Use.DecId.pszName, ASM_DIRECTIVE_SPACE, szOperand, "", FALSE, fGlobal);
                }
                GenObjectComment(pDecl->Use.DecId.pTarget);
            }
        }
    }


    GenAsm(NULL, ASM_DIRECTIVE_SEGMENT_END, NULL, "=== End of DATA segment ===\n\n");

}

// ##########################################################################################
// Bss segment generator


// ##########################################################################
// #  Function: GenBss
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
void GenBss(TPDeclSpec pDeclList) {
    char szOperand[32];
    TPDeclSpec pDecl;

    GenAsm(NULL, NULL, NULL, "########################");
    GenAsm(NULL, ASM_DIRECTIVE_SEGMENT_BEGIN_BSS, "", "# Start of BSS segment #");
    GenAsm(NULL, "", "", "########################");

    GenAsm("", "", "", "Here starts the uninitialized data");
    for (pDecl = pDeclList; pDecl; pDecl = pDecl->pChain) {
        if (pDecl->Usage == DecId) {
            TPDeclSpec pTarget = pDecl->Use.DecId.pTarget;
            if (GenIsData(pTarget->Usage) && !IsTypeQualifierConst(pTarget) && !(pDecl->Use.DecId.pInitializer) && !(pDecl->Use.DecId.pszInitializedStr)) {
                DWORD dwSz = CalcSizeOf(pDecl->Use.DecId.pTarget);
                TPDeclSpec pD = pDecl->Use.DecId.pTarget;
                while (pD && (pD->Usage != DecSpec)) {
                    if      (pD->Usage == DecArray) { pD = pD->Use.DecArray.pTarget;    }
                    else if (pD->Usage == DecPtr)   { pD = pD->Use.DecPtr.pTarget;      }
                    else if (pD->Usage == DecFunc)  { pD = pD->Use.DecFunc.pReturnType; }
                    else {
                        ASSERT(0);
                    }
                }
                ASSERT(pD != NULL);
                WORD bClass = pD->Use.DecSpec.Class;
                if ((bClass & ClassEXTERN) == ClassEXTERN) {
                    GenAsmOut("", ".extern", pDecl->Use.DecId.pszName, "", FALSE, FALSE);
                }
                else {
                    BOOL fGlobal = ((bClass & ClassSTATIC) != ClassSTATIC);
                    if (dwSz == 0) {
                        GenAsmOut(pDecl->Use.DecId.pszName, "", "", "", FALSE, fGlobal);
                    }
                    else {
                        sprintf(szOperand, "%4d", dwSz);
                        GenAsmOut(pDecl->Use.DecId.pszName, ASM_DIRECTIVE_SPACE, szOperand, "", FALSE, fGlobal);
                    }
                }
                GenObjectComment(pDecl->Use.DecId.pTarget);
            }
        }
    }

    GenAsm(NULL, ASM_DIRECTIVE_SEGMENT_END, NULL, "=== End of BSS segment ===\n\n");

}

/* eof */
