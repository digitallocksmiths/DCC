// # $URL: https://eboracum-vss.digitallocksmiths.local/svn/Dls/Sean/RoyalHolloway/CC_Avr/Source/GenExpression.h $
// # $Revision: 387 $


#ifndef __SKC_GEN_MEMORY_ACCESS_H__
#define __SKC_GEN_MEMORY_ACCESS_H__

#ifdef DEBUG_INCLUDE_FILES 
#pragma message("     including " __FILE__)
#endif // DEBUG_INCLUDE_FILES


typedef enum {                      // Read/write access to...
    ACCESS_CONST,                   //  [N ]  Constant value
    ACCESS_REG,                     //  [NS]  Register          
    ACCESS_IO,                      //  [ S]  Special Function register
    ACCESS_GLOBAL,                  //  [NS]  global symbol normal (RAM/Data access)
    ACCESS_GLOBAL_ROM,              //  [NS]  global symbol but in ROM memory
    ACCESS_GLOBAL_ADDRESS,          //  [ S]  global symbol's address wanted.
    ACCESS_FRAME,                   //  [NS]  local or parameter variable.
    ACCESS_FRAME_ADDRESS,           //  [NS]  local or paramterer's address is wanted
    ACCESS_POINTER,                 //  [NS]  A pointer has been collected into Z ready to be de-referenced.
    ACCESS_POINTER_ROM,             //  [NS]  A pointer has been collected into Z ready to be de-referenced but it's in ROM memory.
} TMemAccessMethod;

typedef struct MemAccess {
    TMemAccessMethod Method;        // Indicator of the access mechanism required.
    UCHAR            bVarSize;      // 
    LONG             lN;            // Used when displacements or indicies or values are needed
    LPSTR            pszS;          // Used when symbolic names are required
} TMemAccess, *TPMemAccess;


void       FetchOptions(int iReg, TPExprNode pExpr, TPMemAccess pZ);
void       FetchLoad(TPMemAccess pZ, int iReg);
void       FetchStore(TPMemAccess pZ, int iReg);


#endif // __SKC_GEN_MEMORY_ACCESS_H__

/* eof */


