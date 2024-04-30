/* wildcard.c */

/* Author:
 *	Guntram Blohm
 *	Buchenstrasse 19
 *	7904 Erbach, West Germany
 *	Tel. ++49-7305-6997
 *	sorry - no regular network connection
 */

/* this program implements wildcard expansion for elvis/dos. It works
 * like UNIX echo, but uses the dos wildcard conventions
 * (*.* matches all files, * matches files without extension only,
 * filespecs may contain drive letters, wildcards not allowed in directory
 * names).
 *
 * It is also #included into ctags.c, ref.c, ...; in this case,
 * we don't want a main function here.
 */

#include <glob.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef	WILDCARD_NO_MAIN
# include "CONFIG.H"
#endif
#include "CTYPE.H"

#define	MAXFILES	1000

void expand(char *name);
void addfile(char *buf);
int pstrcmp(const void *a, const void *b);

char *files[MAXFILES];
int nfiles;

#ifndef	WILDCARD_NO_MAIN

int main(int argc, char **argv)
{
	int i;

	_ct_init("");
	for (i=1; i<argc; i++)
		expand(argv[i]);
	if (nfiles)
		printf("%s", files[0]);
	for (i=1; i<nfiles; i++)
	{
		printf(" %s", files[i]);
	}
	putchar('\n');
	return 0;
}

#else
char **wildexpand(int *argc, char **argv)
{
	int i;
	
	for (i=0; i<*argc; i++)
		expand(argv[i]);
	*argc=nfiles;
	return files;
}	
#endif

void expand(char *name)
{
	char *filespec;
	int wildcard=0;
	glob_t findbuf;
	int err;
	char buf[80];
	int lastn;
	int i;

	strcpy(buf, name);
	for (filespec=buf; *filespec; filespec++)
		;

	while (--filespec>=buf)
	{	if (*filespec=='?' || *filespec=='*')
			wildcard=1;
		if (*filespec=='/' || *filespec=='\\' || *filespec==':')
			break;
	}
	if (!wildcard)
		addfile(buf);
	else
	{
		lastn=nfiles;
		if (!glob(buf, 0, NULL, &findbuf))
		{
			for (i=0; i<findbuf.gl_pathc; i++)
				addfile(findbuf.gl_pathv[i]);
		}
		if (lastn!=nfiles)
			qsort(files+lastn, nfiles-lastn, sizeof(char *), pstrcmp);
	}
}

void addfile(char *buf)
{
	char *p;

//	for (p=buf; *p; p++)
//		*p=tolower(*p);

	if (nfiles<MAXFILES && (files[nfiles]=(char *)calloc(strlen(buf)+1, 1))!=0)
		strcpy(files[nfiles++], buf);
}

int pstrcmp(const void *a, const void *b)
{
	return strcmp(*(const char **)a, *(const char **)b);
}
