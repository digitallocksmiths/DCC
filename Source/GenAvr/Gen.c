// # $URL: https://eboracum-vss.digitallocksmiths.local/svn/Dls/Sean/RoyalHolloway/CC_Avr/Source/Gen.c $
// # $Revision: 397 $


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>
#include "..\Utilities\Console.h"

#include "..\lex.h"
#include "..\typectrl.h"
//#include "expr.h"
#include "GenAsm.h"
#include "Gen.h"
#include "..\main.h"


#define GEN_PREFIX "L"
static WORD GenCount = 0;

LPSTR GenLabel(LPSTR PreFix) {
	LPSTR Label = New(strlen(GEN_PREFIX)+strlen(PreFix)+6+1);
	sprintf(Label, GEN_PREFIX "%s%06ld", PreFix, GenCount++);
	return Label;
 }


static int Pad2(char *pszLine, int n) {
    int nCount = 0;
    while (n > 0) {
        nCount += sprintf(&pszLine[nCount], " ");
        n--;
    }
    return nCount;
}


static char szLine[1024];

void GenAsmOut(LPSTR pszLabel, LPSTR pszOpcode, LPSTR pszOperand, LPSTR pszComment, BOOL fNL, BOOL fGlobal) {
    int n;

    if (fGlobal && (pszLabel != NULL) && (*pszLabel != '\0')) {
        n = 0;
        n += Pad2(&szLine[n], LABEL_WIDTH);
        n += sprintf(&szLine[n], " .global");
        n += Pad2(&szLine[n], LABEL_WIDTH + OPCODE_WIDTH - n);
        n += sprintf(&szLine[n], " %s\n", pszLabel);
        if (CmdLine.fEcho) {
            ConsolePrintf(CON_CYAN, szLine);
        }
        fprintf(hGlbOut, szLine);
    }


    n = 0;
    if ((pszLabel != NULL) && (*pszLabel != '\0')) {
        n += sprintf(&szLine[n], "%s:", pszLabel);
    }

    if ((pszOpcode != NULL) && (*pszOpcode != '\0')) {
        n += Pad2(&szLine[n], LABEL_WIDTH - n);
        n += sprintf(&szLine[n], " %s", pszOpcode);
    }

    if ((pszOperand != NULL) && (*pszOperand != '\0')) {
        n += Pad2(&szLine[n], LABEL_WIDTH + OPCODE_WIDTH - n);
        n += sprintf(&szLine[n], " %s", pszOperand);
    }

    if (pszComment != NULL) {
        n += Pad2(&szLine[n], LABEL_WIDTH + OPCODE_WIDTH + OPERAND_WIDTH - n);
        n += sprintf(&szLine[n], "; %s", pszComment);
        if (fNL) {
            n += sprintf(&szLine[n], "\n");
        }
    }
    else {
        n += sprintf(&szLine[n], "\n");
    }
    if (CmdLine.fEcho) {
        ConsolePrintf(CON_CYAN, szLine);
    }
    fprintf(hGlbOut, szLine);




}


BOOL GenIsData(WORD nUse) {
    switch (nUse) {
    case DecSpec:
    case DecPtr:
    case DecArray:  return TRUE;
    case DecId:
    case DecFunc:   return FALSE;
    default:
        Error(FATAL, "GenIsData() unknown use");
    }
    return FALSE;
}

BOOL    GenIsFunction(WORD nUse) {
    switch (nUse) {
    case DecSpec:
    case DecPtr:
    case DecArray:
    case DecId:     return FALSE;
    case DecFunc:   return TRUE;
    default:
        Error(FATAL, "GenIsFunction() unknown use");
    }
    return FALSE;
}



void    GenIntro(void) {
    GenAsm("", "",                         "",               "DCC AVR Output");
    GenAsm("", ".extern",                  ASM_TRAP_OPERAND, "");
    GenAsm("", "",                         "",               NULL);
    GenAsm("", "#define _IO_SPL   0x3D",   "",               NULL);
    GenAsm("", "#define _IO_SPH   0x3E\n", "",               NULL);
    //GenAsm("", "", "", "\n");
}

void    GenTail(void) {
    GenAsm("", "", "", "");
    GenAsm("",       ".end", "", "End of generated code.");
    GenAsm("", "; eof", "", "");
}

/* eof */
