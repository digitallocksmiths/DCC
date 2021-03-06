// # $URL: https://eboracum-vss.digitallocksmiths.local/svn/Dls/Sean/RoyalHolloway/CC_Avr/Source/GenStatements.h $
// # $Revision: 401 $


#ifndef __SKC_GEN_STATEMENTS_H__
#define __SKC_GEN_STATEMENTS_H__

#ifdef DEBUG_INCLUDE_FILES 
#pragma message("     including " __FILE__)
#endif // DEBUG_INCLUDE_FILES



//============================================================================================
// (Would be )Protected functions

void	GenStatementIntro(FILE* hOut, TPStatement pStat, LPSTR pszFn, LPSTR pszAction, LPSTR pszExtraComment);
LPSTR	GenStatementLabel(LPSTR pszFn, LPSTR pszLab);
void	GenStatements(FILE* hOut, int iDepth, TPStatement pStat, LPSTR pszFunctionName, LPSTR pszExitLabel, LPSTR pszBreakLabel, LPSTR pszContinueLabel); 


//============================================================================================
// Public functions


void        GenStatementPrettyPrint(int iDepth, TPStatement pStat, BOOL fNext);


//int    _GenParameterCostStatement(int iMax, TPStatement pStat);
BOOL        _GenDetectNestedCall(TPStatement pStat);

void        GenText(TPDeclSpec pDeclList);



#endif // __SKC_GEN_STATEMENTS_H__

/* eof */
