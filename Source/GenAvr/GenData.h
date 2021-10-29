// # $URL: https://eboracum-vss.digitallocksmiths.local/svn/Dls/Sean/RoyalHolloway/CC_Avr/Source/GenData.h $
// # $Revision: 397 $


#ifndef __SKC_GENDATA_H__
#define __SKC_GENDATA_H__

#ifdef DEBUG_INCLUDE_FILES 
#pragma message("     including " __FILE__)
#endif // DEBUG_INCLUDE_FILES



//============================================================================================
// Public functions

void    GenConst(TPDeclSpec pDecl);
void    GenData(TPDeclSpec pDecl);
void    GenBss(TPDeclSpec pDecl);


#endif // __SKC_GENDATA_H__

/* eof */