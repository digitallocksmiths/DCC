// # $URL: https://eboracum-vss.digitallocksmiths.local/svn/Dls/Sean/RoyalHolloway/CC_Avr/Source/Gen.h $
// # $Revision: 397 $


#ifndef __SKC_GEN_H__
#define __SKC_GEN_H__

#ifdef DEBUG_INCLUDE_FILES 
#pragma message("     including " __FILE__)
#endif // DEBUG_INCLUDE_FILES


//============================================================================================
// ASM directives

#define ASM_DIRECTIVE_SEGMENT_BEGIN_TEXT  ".section    .text"           //  Executable 
#define ASM_DIRECTIVE_SEGMENT_BEGIN_CONST ".section    CONST, \"a\""    //  Constant data
#define ASM_DIRECTIVE_SEGMENT_BEGIN_INIT  ".section    INIT,  \"a\""    //  Initialization data to be copied to DATA
#define ASM_DIRECTIVE_SEGMENT_BEGIN_DATA  ".section    .data"           //  Initialized data variables
#define ASM_DIRECTIVE_SEGMENT_BEGIN_BSS   ".section    .bss"            //  Uninitialized data variables (set to zero at bootstrap)


#define ASM_DIRECTIVE_SEGMENT_END   ";.endseg"                  // end a segment            (operand is empty)"

#define ASM_DIRECTIVE_SPACE         ".space"                    // reserves uninitialized space       (operand is the count of bytes to be reserved)"
#define ASM_DIRECTIVE_BYTE          ".byte"                     // defines an initialized byte value  (operand is a single 8 bit )"
#define ASM_DIRECTIVE_SHORT         ".word"                     // defines an initialized word value  (operand is a single 16 bit value )"
#define ASM_DIRECTIVE_LONG          ".long"                     // defines an initialized dword value (operand is a single 32 bit value )"


#define ASM_TRAP_OPCODE             "jmp"                       // Trap behaviour
#define ASM_TRAP_OPERAND            "SysTrap"                   //  

#define ASM_CALL_OPCODE             "call"                      // use rcall for tiny
#define ASM_CALL_RET_ADDR_SIZE      3                           // size of address pushed by Call  (tiny = 2)

//============================================================================================
// ASM file layout control

#define LABEL_WIDTH   20            // label[width] :: opcode[width] :: operand[width] :: "; " :: comment[]
#define OPCODE_WIDTH  10
#define OPERAND_WIDTH 30


#define REG_DEFENDER  16                    //  used to defent call and return


#define REG_ORDER0     0                    // even
#define REG_ORDER1     (REG_ORDER0+1)       // next
#define REG_ORDER2     2                    // even
#define REG_ORDER3     (REG_ORDER2+1)       // next

#define REG_ACC       20                            // 20,21,22,23 used as the accumulator      (should be 32 bit aligned)
#define REG_ACC0      (REG_ACC+REG_ORDER0)
#define REG_ACC1      (REG_ACC+REG_ORDER1)
#define REG_ACC2      (REG_ACC+REG_ORDER2)
#define REG_ACC3      (REG_ACC+REG_ORDER3)

#define REG_TMP       24                            // 24,25,26,27 used as the temp/working register
#define REG_TMP0      (REG_TMP+REG_ORDER0)
#define REG_TMP1      (REG_TMP+REG_ORDER1)
#define REG_TMP2      (REG_TMP+REG_ORDER2)
#define REG_TMP3      (REG_TMP+REG_ORDER3)

//============================================================================================
// Public functions

BOOL    GenIsData(WORD nUse);
BOOL    GenIsFunction(WORD nUse);

LPSTR   GenLabel(LPSTR PreFix);
void    GenAsmOut(LPSTR pszLabel, LPSTR pszOpcode, LPSTR pszOperand, LPSTR pszComment, BOOL fNL, BOOL fGlobal);

void    GenIntro(void);
void    GenTail(void);

#include "GenData.h"
#include "GenExpression.h"
#include "GenStatements.h"

#endif // __SKC_GEN_H__

/* eof */
