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

//#include <ext\types.h>
#include "..\Utilities\Console.h"

#include "..\lex.h"
#include "..\typectrl.h"
#include "..\expr.h"
//#include "ExprOptimize.h"
#include "gen.h"
#include "..\main.h"
//#include "C_Yacced.tab.h"

#include "GenAsm.h"


//static FILE *hGlbOut;


// ############################################################################################
LPSTR OperandImmediateImmediate(unsigned char bV1, unsigned char bV2) {
    static char caRegVal[16];
    sprintf_s(caRegVal, sizeof(caRegVal), "0x%02x, 0x%02x", bV1, bV2);
    return caRegVal;
}

LPSTR OperandRegImmediate(int iR1, unsigned char bVal) {
    static char caRegVal[16];
    sprintf_s(caRegVal, sizeof(caRegVal), "r%d, 0x%02x", iR1, bVal);
    return caRegVal;
}

LPSTR OperandImmediateReg(unsigned char bVal, int iR1) {
    static char caRegVal[16];
    sprintf_s(caRegVal, sizeof(caRegVal), "0x%02x, r%d", bVal, iR1);
    return caRegVal;
}

LPSTR OperandRegProgVar(int iR1, LPSTR pszVar) {
    static char caRegStr[256];
    if ((iR1 & 0x01) == 0) {
        sprintf_s(caRegStr, sizeof(caRegStr), "r%d, pm_lo8(%s)", iR1, pszVar);
    }
    else {
        sprintf_s(caRegStr, sizeof(caRegStr), "r%d, pm_hi8(%s)", iR1, pszVar);
    }
    return caRegStr;
}

LPSTR OperandRegVar(int iR1, LPSTR pszVar) {
    static char caRegStr[256];
    if ((iR1 & 0x01) == 0) {
        sprintf_s(caRegStr, sizeof(caRegStr), "r%d, lo8(%s)", iR1, pszVar);
    }
    else {
        sprintf_s(caRegStr, sizeof(caRegStr), "r%d, hi8(%s)", iR1, pszVar);
    }
    return caRegStr;
}

LPSTR OperandRegStr(int iR1, LPSTR pszStr) {
    static char caRegVal[128];
    sprintf_s(caRegVal, sizeof(caRegVal), "r%d, %s", iR1, pszStr);
    return caRegVal;
}

LPSTR OperandRegStrDisp(int iR1, LPSTR pszStr, int iDisp) {
    static char caRegVal[128];
    sprintf_s(caRegVal, sizeof(caRegVal), "r%d, %s+%d", iR1, pszStr, iDisp);
    return caRegVal;
}

LPSTR OperandStrReg(LPSTR pszStr, int iR1) {
    static char caRegVal[128];
    sprintf_s(caRegVal, sizeof(caRegVal), "%s, r%d", pszStr, iR1);
    return caRegVal;
}

LPSTR OperandStrDispReg(LPSTR pszStr, int iDisp, int iR1) {
    static char caRegVal[128];
    sprintf_s(caRegVal, sizeof(caRegVal), "%s+%d, r%d", pszStr, iDisp, iR1);
    return caRegVal;
}

LPSTR OperandRegDisp(int iR1, LPSTR pszStr, int iDisp) {
    static char caRegVal[128];
    if (iDisp > 63) {
        // Error(ERRORX, "OperandRegDisp(): Local variable displacment is > 63. No can do.");
#pragma message("    **** DEBUG:   Fudge for massive frames. generates faulty code!")
        Error(WARNINGX, "OperandRegDisp(): Local variable displacment is > 63. No can do.");
        iDisp = 63;
    }
    sprintf_s(caRegVal, sizeof(caRegVal), "r%d, %s+%d", iR1, pszStr, iDisp);
    return caRegVal;
}

LPSTR OperandDispReg(LPSTR pszStr, int iDisp, int iR1) {
    static char caValReg[128];
    if (iDisp > 63) {
        // Error(ERRORX, "OperandDispReg(): Local variable displacment is > 64. No can do.");
#pragma message("    **** DEBUG:   Fudge for massive frames. generates faulty code!")
        Error(WARNINGX, "OperandDispReg(): Local variable displacment is > 64. No can do.");
        iDisp = 63;
    }
    sprintf_s(caValReg, sizeof(caValReg), "%s+%d, r%d", pszStr, iDisp, iR1);
    return caValReg;
}

LPSTR OperandReg(int iR) {
    static char caRegPair[128];
    sprintf_s(caRegPair, sizeof(caRegPair), "r%d", iR);
    return caRegPair;
}

LPSTR OperandRegReg(int iR1, int iR2) {
    static char caRegReg[128];
    sprintf_s(caRegReg, sizeof(caRegReg), "r%d, r%d", iR1, iR2);
    return caRegReg;
}


LPSTR OperandFreeform(LPSTR pszF, ...) {
    static char caRegReg[128];
    va_list ArgList;
    va_start(ArgList, pszF);
    _vsnprintf_s(caRegReg, sizeof(caRegReg), _TRUNCATE, pszF, ArgList);
    return caRegReg;
}



LPSTR CommentNumber(int iCycles, LPSTR pszT, long lValue) {
    static char caComment[256];
    if (iCycles == 0) {
        sprintf_s(caComment, sizeof(caComment), "   : %s%ld", pszT, lValue);
    }
    else {
        sprintf_s(caComment, sizeof(caComment), "%3d: %s%ld", iCycles, pszT, lValue);
    }
    return caComment; 
}

LPSTR CommentString(int iCycles, LPSTR pszT, LPSTR pszM) {
    static char caComment[256];
    if (iCycles == 0) {
        sprintf_s(caComment, sizeof(caComment), "   : %s%s", pszT, pszM);
    }
    else {
        sprintf_s(caComment, sizeof(caComment), "%3d: %s%s", iCycles, pszT, pszM);
    }
    return caComment;
}


LPSTR CommentFreeform(LPSTR pszF, ...) {
    static char caRegReg[128];
    va_list ArgList;
    va_start(ArgList, pszF);
    _vsnprintf_s(caRegReg, sizeof(caRegReg), _TRUNCATE, pszF, ArgList);
    return caRegReg;
}


void DefendConditionalBranch(LPSTR pszOp, LPSTR pszNotOp) {
    if (CmdLine.iDefendConditionals > 0) {                                                                              // Defensive code.
        LPSTR pszTmp      = GenLabel("_Dft_");                                                                          //
        LPSTR pszComment = CommentFreeform("1/2: not-%s defence", pszOp);

        GenAsmOut(NULL, pszNotOp, pszTmp, pszComment, TRUE, FALSE);                                                     //
        GenAsmOut("", ASM_TRAP_OPCODE, ASM_TRAP_OPERAND, "   : Defence against instruction skipping", TRUE, FALSE);     // Skipping the jump will trap
        for (int i = 1; i < CmdLine.iDefendConditionals; i++) {                                                         // Skipping the trap will trap....
            GenAsmOut("", ASM_TRAP_OPCODE, ASM_TRAP_OPERAND, "   :", TRUE, FALSE);                                      //
        }                                                                                                               //
        GenAsmOut(pszTmp, "", "", "   : defended fall through.", TRUE, FALSE);                                          //
        Dispose(pszTmp);                                                                                                //
    }                                                                                                                   //

}


void GenAsm(LPSTR pszLabel, LPSTR pszOpcode, LPSTR pszOperand, LPSTR pszComment) {                                          // always to the same file and always needs NL and it's non global.
    GenAsmOut(pszLabel, pszOpcode, pszOperand, pszComment, TRUE, FALSE);

    if (pszOpcode != NULL) {                                                                                                        // Opcode is valid...
                                                                                                                                    //
        if (strcmp(pszOpcode, "rjmp") == 0) {                                                                                       // RJMP 
            if (CmdLine.iDefendBranches > 0) {                                                                                      //      Defensive code.
                GenAsmOut("", ASM_TRAP_OPCODE, ASM_TRAP_OPERAND, "   : rjmp - Defence against instruction skipping", TRUE, FALSE);  //      Skipping the jump will trap
                for (int i = 1; i < CmdLine.iDefendBranches; i++) {                                                                 //      Skipping the trap will trap....
                    GenAsmOut("", ASM_TRAP_OPCODE, ASM_TRAP_OPERAND, "   :", TRUE, FALSE);                                          //
                }                                                                                                                   //
            }                                                                                                                       //
        }

        if (CmdLine.iDefendConditionals != 0) {                                                                                     // Defended conditional branches.
            if (strcmp(pszOpcode, "brbs") == 0) {                                                                                   // BRBS
                DefendConditionalBranch("brbs", "brbc");
            }
            else if (strcmp(pszOpcode, "brbc") == 0) {                                                                              // BRBC
                DefendConditionalBranch("brbc", "brbs");
            }
            else if (strcmp(pszOpcode, "breq") == 0) {                                                                              // BREQ
                DefendConditionalBranch("breq", "brne");
            }
            else if (strcmp(pszOpcode, "brne") == 0) {                                                                              // BRNE
                DefendConditionalBranch("brne", "breq");
            }
            else if (strcmp(pszOpcode, "brcs") == 0) {                                                                              // BRCS
                DefendConditionalBranch("brcs", "brcc");
            }
            else if (strcmp(pszOpcode, "brcc") == 0) {                                                                              // BRCC
                DefendConditionalBranch("brcc", "brcs");
            }
            else if (strcmp(pszOpcode, "brsh") == 0) {                                                                              // BRSH
                DefendConditionalBranch("brsh", "brlo");
            }
            else if (strcmp(pszOpcode, "brlo") == 0) {                                                                              // BRLO
                DefendConditionalBranch("brlo", "brsh");
            }
            else if (strcmp(pszOpcode, "brmi") == 0) {                                                                              // BRMI
                DefendConditionalBranch("brmi", "brpl");
            }
            else if (strcmp(pszOpcode, "brpl") == 0) {                                                                              // BRPL
                DefendConditionalBranch("brpl", "brmi");
            }
            else if (strcmp(pszOpcode, "brge") == 0) {                                                                              // BRGE
                DefendConditionalBranch("brge", "brlt");
            }
            else if (strcmp(pszOpcode, "brlt") == 0) {                                                                              // BRLT
                DefendConditionalBranch("brlt", "brge");
            }
            else if (strcmp(pszOpcode, "brhs") == 0) {                                                                              // BRHS
                DefendConditionalBranch("brhs", "brhc");
            }
            else if (strcmp(pszOpcode, "brhc") == 0) {                                                                              // BRHC
                DefendConditionalBranch("brhc", "brhs");
            }
            else if (strcmp(pszOpcode, "brts") == 0) {                                                                              // BRTS
                DefendConditionalBranch("brts", "brtc");
            }
            else if (strcmp(pszOpcode, "brtc") == 0) {                                                                              // BRTC
                DefendConditionalBranch("brtc", "brts");
            }
            else if (strcmp(pszOpcode, "brvs") == 0) {                                                                              // BRVS
                DefendConditionalBranch("brvs", "brvc");
            }
            else if (strcmp(pszOpcode, "brvc") == 0) {                                                                              // BRVC
                DefendConditionalBranch("brvc", "brvs");
            }
            else if (strcmp(pszOpcode, "brie") == 0) {                                                                              // BRIE
                DefendConditionalBranch("brie", "brid");
            }
            else if (strcmp(pszOpcode, "brid") == 0) {                                                                              // BRID
                DefendConditionalBranch("brid", "brie");
            }
        }
    }


}




// #################################################################################################

/* eof */

