// # ---------------------------------------------------------------------------------------------
// #  $URL: https://eboracum-vss.digitallocksmiths.local/svn/Dls/Sean/RoyalHolloway/CC_Avr/Source/Utilities/VersionInfo.c $
// # ---------------------------------------------------------------------------------------------
// #  File:                  $Id: VersionInfo.c 409 2020-06-17 12:57:24Z sean $
// #  Last committed:  $Revision: 409 $
// # ---------------------------------------------------------------------------------------------

// Title: VersionInfo.c
// 
//  Implementation details.
//
//

//#define _CRT_SECURE_NO_WARNINGS

//#include <dl_type.h>
#include <windows.h>
#include <stdio.h>

#include "Console.h"


#include "VersionInfo.h"

#pragma comment(linker,"/defaultlib:Version.Lib")


// ##########################################################################
// #  Function: VersionProcessInfo
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
void  VersionProcessInfo(char * argv0) {
        BOOLEAN fSuccess;
        DWORD dwVersionLen;
        LPBYTE pbVersion;
//		char szCopyrightString[80];
        DWORD dwLen;
        char * pString;
        char szPath[300];

        argv0 = _strdup((char*)argv0);
        _strupr_s((char*)argv0, strlen(argv0)+1);
        strncpy_s(szPath, sizeof(szPath), (char*)argv0, sizeof(szPath));
        if (strstr(szPath, ".EXE") == NULL) {
            strcat_s(szPath, sizeof(szPath), ".Exe");
        }

        dwVersionLen = GetFileVersionInfoSizeA(szPath, NULL);
        pbVersion = (LPBYTE)malloc(dwVersionLen);
        fSuccess = GetFileVersionInfoA(szPath, (DWORD)NULL, dwVersionLen, pbVersion);
        if (fSuccess == TRUE) {
            fSuccess = VerQueryValueA(pbVersion, "\\StringFileInfo\\080904b0\\OriginalFilename", &pString, &dwLen);
            if (fSuccess == TRUE) {
                ConsolePrintf(CON_YELLOW, "%s - ", pString);
            }

            fSuccess = VerQueryValueA(pbVersion, "\\StringFileInfo\\080904b0\\FileDescription", &pString, &dwLen);
            if (fSuccess == TRUE) {
                ConsolePrintf(CON_YELLOW+CON_BRIGHT, "%s", pString);
            }

            fSuccess = VerQueryValueA(pbVersion, "\\StringFileInfo\\080904b0\\FileVersion", &pString, &dwLen);
            if (fSuccess == TRUE) { 
                ConsolePrintf(CON_YELLOW, " - Version %s", pString);
            }
//          fSuccess = VerQueryValue(pbVersion, "\\StringFileInfo\\080904b0\\LegalCopyright", &pString, &dwLen);
//          if (fSuccess == TRUE)   {
//              strncpy(szCopyrightString, pString, min(sizeof(szCopyrightString), dwLen));
//          }
        }
        else {
            ConsolePrintf(CON_RED+CON_BRIGHT, "DAMAGED EXE!\n");
            exit(-1);
        }
        free(pbVersion);

//      printf(" - %s\n", __DATE__);
//      printf("%s\n\n", szCopyrightString);
        ConsolePrintf(CON_YELLOW, "\n");
    }


// eof $Workfile: VersionInfo.c $
