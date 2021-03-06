// # $URL: https://eboracum-vss.digitallocksmiths.local/svn/Dls/Sean/RoyalHolloway/CC_Avr/Source/GenStatements.c $
// # $Revision: 402 $


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>

#include "..\Utilities\Console.h"

#include "..\lex.h"
#include "..\typectrl.h"
#include "..\expr.h"
#include "Gen.h"
#include "GenAsm.h"
#include "..\Statements.h"
#include "..\main.h"
#include "..\ExprOptimize.h"



// ##########################################################################
// #  Function: GenReturn
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
void GenReturn(FILE *hOut, int iDepth, TPStatement pStat, LPSTR pszFunctionName, LPSTR pszExitLabel, LPSTR pszBreakLabel, LPSTR pszContinueLabel) {
    GenStatementIntro(hOut, pStat, pszFunctionName, "Return", "");

    if (pStat->Use._return.pExpr != NULL) {
#pragma message("   ToDo: Cast to return type. Either here or in the parsing of the return expression.")
        GenExpression(pStat->Use._return.pExpr);
    }
    if ((iDepth > 1) || (pStat->pNext != NULL)) {
        GenAsm("", "rjmp", pszExitLabel, "  2: Return");                    // Jmp to exit
    }
    else {
        GenAsm("", "", "", "   : Return. (by fall through)");
    }

}



/* eof */
