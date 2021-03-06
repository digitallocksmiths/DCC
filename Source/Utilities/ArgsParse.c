// # ---------------------------------------------------------------------------------------------
// #  $URL:  $
// # ---------------------------------------------------------------------------------------------
// #  File:                  $Id:  $
// #  Last committed:  $Revision:  $
// # ---------------------------------------------------------------------------------------------

// Title: ArgsParse.c
// 
//  Implementation details.
//
//

#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <stdio.h>
#include <assert.h>


//#include "Registry.h"
#include "Argsparse.h"

static char * aFiles[ARGS_MAX_FILES];

// ##########################################################################
// #  Function: UnknownArg
// #        *public*, Wibble.
// #
// #
// #  Parameters:
// #        wibble - wibble.
// #
// #  Returns:
// #        wibble.
// #
// #  See Also:
// #        <wibble>
// #
// ######################################################################### 
static void UnknownArg(char *pArg) {
    fprintf(stderr, "Unknown command line parameter %s\n", pArg);
}


// ##########################################################################
// #  Function: HexDump
// #        *public*, Wibble.
// #
// #
// #  Parameters:
// #        wibble - wibble.
// #
// #  Returns:
// #        wibble.
// #
// #  See Also:
// #        <wibble>
// #
// ######################################################################### 
static void HexDump(unsigned char *pcHex1, int nLen) {
    while (nLen--) {
        printf("%02x ", *pcHex1++);
    }
}

// ##########################################################################
// #  Function: PrintHelp
// #        *public*, Wibble.
// #
// #
// #  Parameters:
// #        wibble - wibble.
// #
// #  Returns:
// #        wibble.
// #
// #  See Also:
// #        <wibble>
// #
// ######################################################################### 
static void PrintHelp(char *pProgram,TArgParam *pParams) {
    TArgParam *pTmpParams;
    char *pS;
    char *pHelpMsg;

    pS = pProgram;                                                                          // Strip the baDir infor from the file name.
    while (*pS != '\0') {
        if (*pS++ == '\\') {
            pProgram = pS;
        }
    }

    for (pTmpParams = pParams; pTmpParams->type != ARG_END; pTmpParams++);                  // fine the extra help message on the END tag.
    pHelpMsg = pTmpParams->pcHelpString;


    printf("\n\n%s %s\n    Options\n      -h         : This Help message\n", pProgram, pHelpMsg);

    pTmpParams = pParams;                                                                   // Search all Options for a match
    while (pTmpParams->type != ARG_END) {                                                   //
        if (pTmpParams->pcKey[strlen(pTmpParams->pcKey) - 1] == '=') {
            printf("   %6s", pTmpParams->pcKey);
        }
        else {
            printf("  %6s ", pTmpParams->pcKey);
        }

        switch (pTmpParams->type) {
            case ARG_FLAG:      printf("        : ");   break;
            case ARG_CHAR:      printf("<char>  : ");   break;
            case ARG_INT:       printf("<number>: ");   break;
            case ARG_STRING:    printf("<string>: ");   break;
            case ARG_HEX:       printf("<hex>   : ");   break;
            default:            assert(FALSE); // Impossible
        }
        printf(pTmpParams->pcHelpString, pTmpParams->pcDefault);
        printf("\n");
        pTmpParams++;                                                                       // next
    }
    printf("\n\n");
}



// ##########################################################################
// #  Function: ReadFlag
// #        *public*, Wibble.
// #
// #
// #  Parameters:
// #        wibble - wibble.
// #
// #  Returns:
// #        wibble.
// #
// #  See Also:
// #        <wibble>
// #
// ######################################################################### 
static unsigned char ReadFlag(char *pValue) {
    if (pValue == 0) {
        return 0;
    }
    if (*pValue == '0') return 0;
    else                return 1;
}


// ##########################################################################
// #  Function: ReadChar
// #        *public*, Wibble.
// #
// #
// #  Parameters:
// #        wibble - wibble.
// #
// #  Returns:
// #        wibble.
// #
// #  See Also:
// #        <wibble>
// #
// ######################################################################### 
static int ReadChar(char *pValue) {
    char c=0;
    if (pValue == 0) {
        return 0;
    }
    if (*pValue == 0) {
        return '0';
    }
    else {
        return *pValue;
    }
}

// ##########################################################################
// #  Function: ReadInt
// #        *public*, Wibble.
// #
// #
// #  Parameters:
// #        wibble - wibble.
// #
// #  Returns:
// #        wibble.
// #
// #  See Also:
// #        <wibble>
// #
// ######################################################################### 
static int ReadInt(char *pValue) {
    int i=0;
    if (pValue == 0) {
        return 0;
    }
    if ((pValue[0] == '0') && ((pValue[1] == 'x') || (pValue[1] == 'X') )) {           // Hex
        sscanf(pValue+2, "%x", &i);
    }
    else {
        i = atoi(pValue);                                                                // Decimal
    }
    return i;
}

// ##########################################################################
// #  Function: ReadString
// #        *public*, Wibble.
// #
// #
// #  Parameters:
// #        wibble - wibble.
// #
// #  Returns:
// #        wibble.
// #
// #  See Also:
// #        <wibble>
// #
// ######################################################################### 
static char * ReadString(char *pValue) {
    char * pS;
    if (pValue == NULL) {
        pS = (char*)malloc(1);
        *pS = 0;
        return pS;
    }

    pS = (char *)malloc(strlen(pValue)+1);
    strcpy(pS, pValue);
    return pS;
}

// ##########################################################################
// #  Function: ReadHex
// #        *public*, Wibble.
// #
// #
// #  Parameters:
// #        wibble - wibble.
// #
// #  Returns:
// #        wibble.
// #
// #  See Also:
// #        <wibble>
// #
// ######################################################################### 
static unsigned char * ReadHex(char *pValue) {

    unsigned char * pS;

    if (pValue == NULL) {
        pS = (char*)malloc(1);
        *pS = 0;
        return pS;
    }

    pS = (unsigned char *)malloc(1+ strlen(pValue)/2);
    for (*pS = 0; sscanf(pValue, "%02hhx", &pS[*pS+1]) == 1; (*pS)++, pValue+=2);
    return pS;
}


// ##########################################################################
// #  Function: ArgsParse
// #        *public*, Wibble.
// #
// #
// #  Parameters:
// #        wibble - wibble.
// #
// #  Returns:
// #        wibble.
// #
// #  See Also:
// #        <wibble>
// #
// ######################################################################### 
char * * ArgsParse(int argc, char * argv[], TArgParam *pParams) {
    int i;
    int nFileCount;
    TArgParam *pTmpParams;
    char        baFilename[_MAX_FNAME];
    //HKEY        hReg;

    _splitpath(argv[0], NULL, NULL, baFilename, NULL);

    //hReg = RegOpen(baFilename);
    pTmpParams = pParams;                                                                                       // Set up the defaults 
    while (pTmpParams->type != ARG_END) {                                                                       // for all declared parameters. Get from Registry. 
        switch (pTmpParams->type) {                                                                             // if not in registry then use the default supplied and set the registry.
        case ARG_FLAG:       *(int *)(pTmpParams->pVar)       = (int)(ReadInt(pTmpParams->pcDefault) ? 1 : 0);  break;
            case ARG_CHAR:      *(char *)(pTmpParams->pVar)   = (char)ReadChar(pTmpParams->pcDefault);          break;
            case ARG_INT:       *(int *)(pTmpParams->pVar)    = (int)ReadInt(pTmpParams->pcDefault);            break;
            case ARG_STRING:    *(char * *)(pTmpParams->pVar) = (char *)ReadString(pTmpParams->pcDefault);      break;
            case ARG_HEX:       *(char * *)(pTmpParams->pVar) = (char *)ReadHex(pTmpParams->pcDefault);         break;
            default:            assert(FALSE); // Impossible
        }
        pTmpParams++;
    }

    for (i=0; i<ARGS_MAX_FILES; i++) {                                                      // Set up default files all NULL
        aFiles[i] = NULL;
    }
    nFileCount = 0;

    for(i = 1; i< argc; i++) {                                                                  // For all Arguments 1..n-1

        if ((strcmp(argv[i], "?") == 0)  ||                                                                     // We always offer help varients.
            (strcmp(argv[i], "-?") == 0) ||                                                                     //
            (strcmp(argv[i], "-H") == 0) ||                                                                     //
            (strcmp(argv[i], "-h")== 0)) {                                                                      //
                PrintHelp(argv[0], pParams);                                                                    //
                continue;                                                                                       //
        }                                                                                                       //

        pTmpParams = pParams;                                                                                   // Search all Options for a match
        while (pTmpParams->type != ARG_END) {                                                                   //
            if (strncmp(argv[i], pTmpParams->pcKey, strlen(pTmpParams->pcKey)) == 0) {                          // Hit if argv[x] in Params table
                break;                                                                                          //
            }                                                                                                   //
            pTmpParams++;                                                                                       // next
        }                                                                                                       // fall out pointing to end if no match found.

        switch (pTmpParams->type) {
            case ARG_FLAG:      *(int *)(pTmpParams->pVar) = !ReadInt(pTmpParams->pcDefault);
                                break;
            case ARG_CHAR:      *(char*)(pTmpParams->pVar)   =  *(char*)(argv[i]+strlen(pTmpParams->pcKey));    
                                //RegWriteU32(hReg, pTmpParams->pcName, *(pgs8)(pTmpParams->pVar));
                                break;
            case ARG_INT:       *(char*)(pTmpParams->pVar)  =  ReadInt(argv[i]+strlen(pTmpParams->pcKey));
                                //RegWriteU32(hReg, pTmpParams->pcName, *(pgs32)(pTmpParams->pVar));
                                break;
            case ARG_STRING:    *(char * *)(pTmpParams->pVar)  =  ReadString(argv[i]+strlen(pTmpParams->pcKey));
                                //RegWriteString(hReg, pTmpParams->pcName, *(pgpgs8)(pTmpParams->pVar));
                                break;
            case ARG_HEX:       *(char * *)(pTmpParams->pVar)  =  ReadHex(argv[i]+strlen(pTmpParams->pcKey));
                                //RegWriteHex(hReg, pTmpParams->pcName, *(pgpgu8)(pTmpParams->pVar));
                                break;
            case ARG_END:       if (*argv[i] == '-') {
                                    UnknownArg(argv[i]);
                                } 
                                else if (nFileCount<ARGS_MAX_FILES) {
                                    aFiles[nFileCount] = (char*)malloc(strlen(argv[i])+1);
                                    strcpy( aFiles[nFileCount], argv[i]); 
                                    nFileCount++;
                                }
                                else {
                                    ;   // ignoring excess files.
                                }
                                break;

            default:            assert(FALSE); // Impossible
        }
    }

    return aFiles;
}


// ##########################################################################
// #  Function: ArgsDumpParams
// #        *public*, Wibble.
// #
// #
// #  Parameters:
// #        wibble - wibble.
// #
// #  Returns:
// #        wibble.
// #
// #  See Also:
// #        <wibble>
// #
// ######################################################################### 
void ArgsDumpParams(TArgParam *pParams, char * aFiles[]) {
    TArgParam *pTmpParams;
    int i;

    pTmpParams = pParams+1;                                                                 // Set up the defaults 
    while (pTmpParams->type != ARG_END) {                                                   // for all declared parameters.
        switch (pTmpParams->type) {
        case ARG_FLAG:      printf("%s = %s", pTmpParams->pcName,  (*(unsigned char *)pTmpParams->pVar)?"TRUE":"FALSE");    break;
        case ARG_CHAR:      printf("%s = '%c'", pTmpParams->pcName,  *(char *)pTmpParams->pVar);                               break;
        case ARG_INT:       printf("%s = %d", pTmpParams->pcName,  *(int *)pTmpParams->pVar);                               break;
        case ARG_STRING:    printf("%s = \"%s\"", pTmpParams->pcName,  *(char**)(pTmpParams->pVar));                                       break;
        case ARG_HEX:       printf("%s = ",   pTmpParams->pcName); HexDump((*(unsigned char **)(pTmpParams->pVar))+1, **(unsigned char **)(pTmpParams->pVar)); break;
        default:            assert(FALSE); // Impossible
        }
        printf("\n");
        pTmpParams++;
    }

    if (aFiles) {
        for (i=0; i<ARGS_MAX_FILES; i++) {
            if (aFiles[i] != NULL) {
                printf("File%d = %s\n", i, aFiles[i]); 
            }
        }
    }
    printf("\n");
}

// eof $Workfile: ArgsParse.c $
