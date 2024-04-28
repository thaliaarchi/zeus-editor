//-------------------------------------------------------------------------
//--
//-- Copyright (c) 1991-95   Xidicone Pty Ltd
//-- All rights reserved.
//--
//-------------------------------------------------------------------------

#include <stdio.h>
// #include <direct.h>
#include <stdlib.h>
#include <search.h>
#include <string.h>
#include <ctype.h>

//-------------------------------------------------------------------------

#define BOOL int

#define TRUE  1
#define FALSE 0

//-------------------------------------------------------------------------

static int  sIndent = 0;

static char szIndent[20];
static char szFullName[180];
static char szLineTemp[120];

static BOOL fFormat = 0;
static BOOL fParseSystem = 0;

static unsigned int sIndex = 0;
static char        *apszIncludeList[200];

//-------------------------------------------------------------------------

#define USAGE "usage: cinc [flags] filename\n"                      \
              "\t-s  search system include files also\n" \
              "\t-f  format the display output\n"

//-------------------------------------------------------------------------

int CheckFile(char *pszFileName)
{
   int sResult = 0;

   if (sIndex < 200)
   {
      for (int i = 0; i < (int)sIndex; ++i)
      {
         if (strcasecmp(pszFileName, apszIncludeList[i]) == 0)
         {
            sResult = 1;
            break;
         }
      }

      if (sResult == 0)
      {
         //-- add the item to the list
         apszIncludeList[sIndex] = new char[180];
         strcpy(apszIncludeList[sIndex], pszFileName);
         ++sIndex;
      }
   }
   else
   {
      printf("Error: Include structure is to complex to process\n");
      exit(-1);
   }

   //-- only process include files not in the list
   return (sResult == 0) ? TRUE : FALSE;
}

//-------------------------------------------------------------------------
//-- this will cause a GPF if the file is loaded from the output window

void IndentChange(void)
{
   if (fFormat)
   {
      sIndent = (sIndent < 5) ? sIndent : 5;
   
      switch (sIndent)
      {
         case 1:
            strcpy(szIndent, " ");
            break;
   
         case 2:
            strcpy(szIndent, "  |- ");
            break;
   
         case 3:
            strcpy(szIndent, "  |  |- ");
            break;
   
         case 4:
            strcpy(szIndent, "  |  |  |- ");
            break;
   
         default:
            strcpy(szIndent, "  |  |  |... ");
            break;
      }
   }
   else
   {
        strcpy(szIndent, " ");
   }
}

//-------------------------------------------------------------------------
//-- use this one eventually
void IndentChange1(void)
{
   if (fFormat)
   {
      sIndent = (sIndent < 5) ? sIndent : 5;
   
      switch (sIndent)
      {
         case 1:
            strcpy(szIndent, " ");
            break;
   
         case 2:
            strcpy(szIndent, "  |- ");
            break;
   
         case 3:
            strcpy(szIndent, "  |  |- ");
            break;
   
         case 4:
            strcpy(szIndent, "  |  |  |- ");
            break;
   
         default:
            strcpy(szIndent, "  |  |  |... ");
            break;
      }
   }
   else
   {
        strcpy(szIndent, " ");
   }
}

//-------------------------------------------------------------------------

void PrintLine(char *pszFile, char *pszLine, int sLine)
{
   char szFileName[150];

   //-- build up an file name with indent
   strcpy(szFileName, szIndent);
   strcat(szFileName, pszFile);

   if (fFormat)
   {
      printf("%-30.30s Line: %4.4d  |  %s", szFileName, sLine, pszLine);
   }
   else
   {
      printf("File:%-25.25s Line: %4.4d  |  %s", szFileName, sLine, pszLine);
   }
}

//-------------------------------------------------------------------------

void ParseFile(char *pszFileName, BOOL fLocal = 0)
{
   char szLine[120];

   FILE *pFile = 0;

   ++sIndent;

   //-- build up an indent string level
   IndentChange();

   //-- should we try to find the file locally
   if (fLocal == 0)
   {
      //-- try to open the file in the current directory
      pFile = fopen(pszFileName, "r");
   }

   //-- search the include path if we don't have a file
   if (pFile == 0)
   {
      //-- look for the file in the INCLUDE path
      _searchenv(pszFileName, "INCLUDE", szFullName);

      //-- try to open it
      if (szFullName[0])
      {
         pFile = fopen(szFullName, "r");
      }
   }

   int sLine = 0;

   //-- process the file if we have one
   if (pFile)
   {
      while (feof(pFile) == 0)
      {
         sLine++;

         fgets(szLine, sizeof(szLine), pFile);

         if (strncmp(szLine, "#include ", 9) == 0)
         {
            strcpy(szLineTemp, szLine);

            char *pszFile = strchr(szLine, '<');

            if (pszFile)
            {
               ++pszFile;

               //-- get the end of the file name
               char *pszEnd = strchr(pszFile, '>');
               
               if (pszEnd)
               {
                  *pszEnd = '\0';

                  //-- make sure we should process syustem files
                  if (fParseSystem)
                  {
                     //-- make sure the file has not already been processed
                     if (CheckFile(pszFile))
                     {
                        PrintLine(pszFileName, szLineTemp, sLine);
   
                        ParseFile(pszFile, 0);
                     }
                  }
                  else
                  {
                     // just print it out
                     PrintLine(pszFileName, szLineTemp, sLine);
                  }
               }
            }
            else
            {
               pszFile = strchr(szLine, '\"');

               if (pszFile)
               {
                  ++pszFile;

                  //-- get the end of the file name
                  char *pszEnd = strchr(pszFile, '\"');

                  if (pszEnd)
                  {
                     *pszEnd = '\0';

                     //-- make sure the file has not already been processed
                     if (CheckFile(pszFile))
                     {
                        PrintLine(pszFileName, szLineTemp, sLine);
   
                        ParseFile(pszFile, 1);
                     }
                  }
               }
            }
         }
      }

      fclose(pFile);
   }
   else
   {
      printf("Error when opening the file '%s'\n", pszFileName);
   }

   //-- keep track of the indent level
   --sIndent;

   //-- put out a blank line to make the output readable
   if ((fFormat) && (sIndent == 1))
   {
      printf("\n");
   }

   //-- restore the indent string level
   IndentChange();
}

//-------------------------------------------------------------------------

int main(int argc, char *argv[])
{
   int sResult = 0;
   char *pszFileName = 0;

   memset(apszIncludeList, 0, sizeof(apszIncludeList));

   if (argc == 2)
   {
      pszFileName = argv[1];
   }
   else if (argc == 3)
   {
      if (strlen(argv[1]) != 2)
      {
         printf("Unknown flag '%s'\n \n", argv[1]);
         printf(USAGE);
         exit(-1);
      }

      if ((argv[1][1] == 's') || (argv[1][1] == 'S'))
      {
         fParseSystem = TRUE;

         pszFileName = argv[2];
      }
      else if ((argv[1][1] == 'f') || (argv[1][1] == 'F'))
      {
         fFormat = TRUE;

         pszFileName = argv[2];
      }
      else
      {
         printf("Unknown flag '%s'\n \n", argv[1]);
         printf(USAGE);
         exit(-1);
      }
   }
   else if (argc == 4)
   {
      if (strlen(argv[1]) != 2)
      {
         printf("Unknown flag '%s'\n \n", argv[1]);
         printf(USAGE);
         exit(-1);
      }

      if (strlen(argv[2]) != 2)
      {
         printf("Unknown flag '%s'\n \n", argv[1]);
         printf(USAGE);
         exit(-1);
      }

      if ((argv[1][1] == 's') || (argv[1][1] == 'S'))
      {
         fParseSystem = TRUE;

         pszFileName = argv[3];
      }
      else if ((argv[1][1] == 'f') || (argv[1][1] == 'F'))
      {
         fFormat = TRUE;

         pszFileName = argv[3];
      }
      else
      {
         printf("Unknown flag '%s'\n \n", argv[1]);
         printf(USAGE);
         exit(-1);
      }

      if ((argv[2][1] == 's') || (argv[1][1] == 'S'))
      {
         fParseSystem = TRUE;

         pszFileName = argv[3];
      }
      else if ((argv[2][1] == 'f') || (argv[1][1] == 'F'))
      {
         fFormat = TRUE;

         pszFileName = argv[3];
      }
      else
      {
         printf("Unknown flag '%s'\n \n", argv[1]);
         printf(USAGE);
         exit(-1);
      }
   }
   else
   {
      printf(USAGE);
      exit(-1);
   }

   char szExt[_MAX_EXT];
   char szDir[_MAX_DIR];
   char szDrive[_MAX_DRIVE];
   char szFileName[_MAX_FNAME];

   char szPathCurrent[_MAX_DRIVE];

   //-- save the current details   
   int sDriveCurrent = _getdrive();
   getcwd(szPathCurrent, sizeof(szPathCurrent));

   //-- change to the document directory if possible
   _splitpath(pszFileName, szDrive, szDir, szFileName, szExt);

   //-- change to the disk required
   if (szDrive[0] != '\0')
   {
      char chDrive = szDrive[0];
   
      //-- make sure it is upper case
      toupper(chDrive);
      
      _chdrive(chDrive);
   }

   //-- change to the dir required
   if (szDir[0] != '\0')
   {
      //-- remove the '\' character
      int sLength = strlen(szDir);
      if (sLength > 3) szDir[sLength - 1] = '\0';

      //-- new directory
      chdir(szDir);
   }

   //-- parse the file
   printf("C/C++ Include File List for '%s'\n\n", pszFileName);

   char szTempFile[_MAX_FNAME + _MAX_EXT];

   //-- only need the filename part
   strcpy(szTempFile, szFileName);
   strcat(szTempFile, szExt);

   ParseFile(szTempFile);

   //-- release any memory we may have allocated
   for (int i = 0; i < (int)sIndex; ++i)
   {
      delete apszIncludeList[i];
   }

   //-- restore the old details
   _chdrive(sDriveCurrent);
   chdir(szPathCurrent);

   return sResult;
}

//-------------------------------------------------------------------------


