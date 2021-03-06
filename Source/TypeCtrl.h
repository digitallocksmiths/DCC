// # $URL: https://eboracum-vss.digitallocksmiths.local/svn/Dls/Sean/RoyalHolloway/CC_Avr/Source/TypeCtrl.h $
// # $Revision: 773 $


#ifndef __SKC_TYPECTRL_H__
#define __SKC_TYPECTRL_H__

#ifdef DEBUG_INCLUDE_FILES 
#pragma message("     including " __FILE__)
#endif // DEBUG_INCLUDE_FILES


// high             : Pn                    ; 
//                  : ...                   ; 
//                  : P1                    ;   FP - FRAME_OVERHEAD - sizeof(P0) - sizeof(P1)
//                  : P0                    ;   FP - FRAME_OVERHEAD - sizeof(P0)
//                  : Return Address[2]     ;   // FRAME_OVERHEAD = 4
//                  : Preserved FP[2]       ;   //
//       FP -->     : L0                    ;   FP
//                  : L1                    ;   FP + sizeof(L0)
//                  : ...                   ;   FP + sizeof(L0) + sizeof(L1)
//                  : Lm                    ; 
// low   SP -->     :                       ; 
//



/* ****************** */
/* Data Element Sizes */
/* ****************** */

#define    SIZE_VOID            0           // basic types
#define    SIZE_CHAR            1
#define    SIZE_INT             2
#define    SIZE_SHORT           2
#define    SIZE_LONG            4
#define    SIZE_FLOAT           8
#define    SIZE_DOUBLE         16
#define    SIZE_LONGDOUBLE     32
#define    SIZE_BOOL            1

#define    SIZE_ENUM            SIZE_SHORT
#define    SIZE_FUNC            SIZE_SHORT           // reference types
#define    SIZE_PTR_DEFAULT     SIZE_SHORT
#define    SIZE_PTR_CONST       SIZE_SHORT
#define    SIZE_PTR_VOLATILE    SIZE_SHORT
#define    SIZE_PTR_NEAR        SIZE_SHORT
#define    SIZE_PTR_FAR         SIZE_SHORT
                                                                            
// Stack is "empty decrementing" 
//   109    +7   P2
//   108    +6   p1h
//   107    +5   p1l
//   106    +4   ret_addrh
//   105    +3   ret_addrl
//   104    +2   pres_fph
//   103    +1   pres_fpl
//   102  FP     l1
//   101    -1   l2h
//   100    -2   l2l
//    99  SP     <empty>

#define    FRAME_OVERHEAD       (ASM_CALL_RET_ADDR_SIZE+SIZE_PTR_DEFAULT+1)         // frame is return address and caller's frame pointer
#define    GLOBAL_VAR           (0x7FFF)                                            // used for iOffset. No varaible can be here within the frame overhead data



/* *************** */
/* Type structures */
/* *************** */
// forward ref from Expr.h
typedef struct TagExprNode TExprNode;                           // Expression Nodes
typedef TExprNode * TPExprNode;
typedef struct TagStatement TStatement;                         // Statement node
typedef TStatement * TPStatement;




typedef enum {
    DecId_Used = 1,                 // set if the pszInitializedStr contents are used in a defined variable initialization. In this case there is no need to keep the original contents in memory.
    DecId_Refed = 2,                // Set if the pszInitializedStr is referenced. In this case the contents need to be in memory to be pointed at.
    DecId_UsedFlag_Local = 4,       // Set if the variable is used in an expression.
    DecId_UsedFlag_Assigned = 8     // Set if a variable is assigned within and expression.
} TDecIdUsedFlags;

typedef enum { DecSpec, DecId, DecPtr, DecArray, DecFunc } TUsage;

typedef struct TagDeclSpec TDeclSpec;
typedef TDeclSpec * TPDeclSpec;
struct TagDeclSpec {
    TUsage          Usage;                  // indicate the relevant structure type in the following union
    TPDeclSpec      pChain;                 // link to the next element in the list.
    union {
        struct  {
            WORD    Class;                  // Base Type     !! Keep DecSpec first in union for initialization !! 
            WORD    Type;
            WORD    wQual;
            LPVOID  pPtr;                   // pointer used for structures, enums, etc.
        } DecSpec;
        struct {
            LPSTR           pszName;                // Identifier
            TDecIdUsedFlags UsedFlags;              //      flags to indicate when the variable is used.
            LPSTR           pszInitializedStr;      //      if it was initialized by a string
            TPExprNode      pInitializer;           //      record of initialization data.
            TPDeclSpec      pTarget;                //      Type information here              
            TPDeclSpec      pBrother;               //      Identifiers in this group
            int             iOffset;                //      gentime offset. in a chain of identifiers this is the memory offset of this variable.
            //int             iIndex;               //      parsetime var count
        } DecId;
        struct {                                    // Pointers           
            //WORD        wClass;
            WORD        wQual;            
            TPDeclSpec  pTarget;
        } DecPtr;
        struct {                            // Arrays
            DWORD       Size;
            TPDeclSpec  pTarget;
        } DecArray;
        struct {                            // Function
            TPDeclSpec      pPList;         //      parameters
            TPDeclSpec      pIdList;        //      K&R parameters
            TPDeclSpec      pReturnType;    //      return type
            TPStatement     pBody;          //      statement list
        } DecFunc;
    } Use;
 };

/* ********** */
/* Base Types */
/* ********** */

#define ClassAUTO       (1<<0)              //  0x01
#define ClassREGISTER   (1<<1)              //  0x02
#define ClassSTATIC     (1<<2)              //  0x04
#define ClassEXTERN     (1<<3)              //  0x08
#define ClassTYPEDEF    (1<<4)              //  0x10
#define ClassALL        (0x1F)

#define TypeVOID        (1<<0)              //  0x0001
#define TypeCHAR        (1<<1)              //  0x0002
#define TypeSHORT       (1<<2)              //  0x0004
#define TypeINT         (1<<3)              //  0x0008
#define TypeLONG        (1<<4)              //  0x0010
#define TypeFLOAT       (1<<5)              //  0x0020
#define TypeDOUBLE      (1<<6)              //  0x0040
#define TypeSIGNED      (1<<7)              //  0x0080
#define TypeUNSIGNED    (1<<8)              //  0x0100
#define TypeSTRUCT      (1<<9)              //  0x0200
#define TypeENUM        (1<<10)             //  0x0400
#define TypeTYPEDEF     (1<<11)             //  0x0800
#define TypeBOOL        (1<<12)             //  0x1000          // sk extension
#define TypeALL (0x1FFF)

#define QualCONST       (1<<0)              //  0x01
#define QualVOLATILE    (1<<1)              //  0x02
#define QualNEAR        (1<<2)              //  0x04
#define QualFAR         (1<<3)              //  0x08
#define QualNORETURN    (1<<4)              //  0x10          // sk extension
#define QualUNDEFENDEF  (1<<5)              //  0x20          // sk extension
#define QualALL         (0x3F)

extern TPDeclSpec  GlobalTypes;
extern TPDeclSpec  GlobalObjects;
extern TPDeclSpec  ParameterObjects;
extern TPDeclSpec  LObjects;


//  0x10
TPDeclSpec NewSpecClass(WORD Class);
TPDeclSpec NewSpecType(WORD Type, LPVOID unPtr);
TPDeclSpec NewSpecQual(WORD Qual);
TPDeclSpec ConcatDeclSpec(TPDeclSpec Old, TPDeclSpec New);

TPDeclSpec ConcatDeclSpecTypes(TPDeclSpec Old, TPDeclSpec New);
TPDeclSpec ConcatDeclSpecQualifiers(TPDeclSpec Old, TPDeclSpec New);
TPDeclSpec ConcatDeclSpecClass(TPDeclSpec Old, TPDeclSpec New);


/* ********************************************* */

TPDeclSpec  NewIdentifier(LPSTR Name);
TPDeclSpec  NewPointer(TPDeclSpec Qualifier, TPDeclSpec Target);
TPDeclSpec  NewArray(TPDeclSpec Decl, TPExprNode Expr);

TPDeclSpec  Glb_pCurrenFunction;                                                                        // this is the function currently being parsed. This helps verify any 'return' statements we find.
TPDeclSpec  DeclNewFunc(TPDeclSpec Decl, TPDeclSpec PList, TPDeclSpec IdList);
void        FuncParams(TPDeclSpec pFuncType, TPDeclSpec Func);                                         // make the parameters from the parameter.
TPDeclSpec  FunctionBody(TPDeclSpec Func, TPDeclSpec pIdList, TPStatement pBody );

//TPDeclSpec  AppendBrothers(TPDeclSpec a, TPDeclSpec b);

//TPDeclSpec DeclVarAddType(TPDeclSpec pIdList, TPDeclSpec pSpec);            // Add type to all the variables in the list.
TPDeclSpec  DeclVarAddBrother(TPDeclSpec pA, TPDeclSpec pB);                 // Add a variable to the list of variables.
TPDeclSpec  DeclAddVarToParameterList(TPDeclSpec pA, TPDeclSpec pB);        // Add a variable to the list of parameter variables. (Order is reversed).


TPDeclSpec  AppendDecl(TPDeclSpec a, TPDeclSpec b);
TPDeclSpec  MakeBrother(TPDeclSpec a, TPDeclSpec b);
TPDeclSpec  AddInitializer(TPDeclSpec pDecl, TPExprNode pInit);
TPDeclSpec  AddInitializerStr(TPDeclSpec pDec, LPSTR pStr);


DWORD       CalcSizeOf(TPDeclSpec unPtr);                     // storage required
BOOL        CompDecl(TPDeclSpec a, TPDeclSpec b);           // ? Same Type
BOOL        TypeIsIntegral(TPDeclSpec pType);               // can type be represented as an integer
BOOL        TypeIsSigned(TPDeclSpec pType);
BOOL        TypeIsUnsigned(TPDeclSpec pType);


void        ParseDeclSpec(int iDepth, TPDeclSpec unPtr, BOOL DoBrothers);
  
/********************/
/* ENUM descriptors */
/********************/

typedef struct TagEnumElement TEnumElement;
typedef TEnumElement * TPEnumElement;
struct TagEnumElement {
        LPSTR           pszElementName;
        BOOL            fAssigned;
        DWORD           dwValue;
        TPEnumElement   pNext;
};

typedef struct TagEnumSet TEnumSet;
typedef TEnumSet * TPEnumSet;
struct TagEnumSet {
        LPSTR           pszSetName;
        TPEnumElement   pElements;
        TPEnumSet       pNext;
};


TPEnumElement   EnumElementMake(LPSTR pszName, TPExprNode pExpr);
TPEnumElement   EnumElementAdd(TPEnumElement pList, TPEnumElement pNew);
TPEnumElement   EnumElementFind(LPSTR pszName);
TPEnumSet       EnumSetAdd(LPSTR szName, TPEnumElement pElements);

void            EnumElementPrintList(TPEnumElement pEl);
void            EnumSetPrint(int iDepth, TPEnumSet pSet);
void            EnumSetPrintList(int iDepth);

/****************************/
/* STRUCT/UNION descriptors */
/****************************/

typedef struct TagStructSet TStructSet;
typedef TStructSet * TPStructSet;
struct TagStructSet {
         LPSTR          szSetName;
         BOOL           fUnion;
         TPDeclSpec     pElements;
         TPStructSet    pNext;
};

TPStructSet     AddStructSet(LPSTR Name, BOOL Union, TPDeclSpec Elements);
int             CalcStructElementOffset(TPStructSet Struct, LPSTR Field);
TPDeclSpec      CalcStructElementType(TPStructSet Struct, LPSTR Field);

void            PrintStructSets(int iDepth);

/* ***************************************************************** */
/*  Declarations  */
/* ************** */

void        Declaration(TPDeclSpec unPtr);
void        DeclareParameters(TPDeclSpec pDecl);
void        DeclareLocal(TPDeclSpec pDecl);
void        UndeclareParameters(TPDeclSpec pDecl);
void        UndeclareLocals(TPDeclSpec pDecl);


TPDeclSpec  FindType(LPSTR Name);
TPDeclSpec  FindGlobalObject(LPSTR Name);
TPDeclSpec  FindParameterObject(LPSTR Name);
TPDeclSpec  FindLocalObject(LPSTR Name);

BOOL TypeIsIntegral(TPDeclSpec Type);
BOOL IsRealType(TPDeclSpec Type);

BOOL        IsTypeQualifier(TPDeclSpec pTarget, int Qualifier);
#define     IsTypeQualifierConst(pTarget)       IsTypeQualifier(pTarget, QualCONST)
#define     IsTypeQualifierVolatile(pTarget)    IsTypeQualifier(pTarget, QualVOLATILE)
#define     IsTypeQualifierNear(pTarget)        IsTypeQualifier(pTarget, QualNEAR)
#define     IsTypeQualifierFar(pTarget)         IsTypeQualifier(pTarget, QualFAR)


void    ListGlobalTypes(void);
void    ListGlobalObjects(void);
void    ListParameterObjects(void);
void    ListLocalObjects(void);

LPSTR DescClassString(WORD c);
LPSTR DescTypeString(WORD q);
LPSTR DescQualString(WORD q);

LPSTR DescFullTypeString(int iPos, TPDeclSpec pDecl);


#define FnIsUndefended(wFnQualifier) ((wFnQualifier & QualUNDEFENDEF) == QualUNDEFENDEF)



BOOL    TypeIsExtern(TPDeclSpec pTarget);

#endif // __SKC_TYPECTRL_H__

/* eof */
