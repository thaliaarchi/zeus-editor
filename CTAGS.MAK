# Microsoft Visual C++ generated build script - Do not modify

PROJ = CTAGS
DEBUG = 0
PROGTYPE = 6
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\WORK\CTAGS\
USEMFC = 0
CC = cl
CPP = cl
CXX = e Viewer: Tools
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC = CTAGS.C     
FIRSTCPP =             
RC = rc
CFLAGS_D_DEXE = /nologo /W3 /FR /G2 /Zi /D_DEBUG /Od /AM /D_DOS /Fd"CTAGS.PDB"
CFLAGS_R_DEXE = /nologo /W3 /FR /G2 /DNDEBUG /Gs /Ox /AM /D_DOS
LFLAGS_D_DEXE = /NOLOGO /ONERROR:NOEXE /NOI /CO /STACK:5120
LFLAGS_R_DEXE = /NOLOGO /ONERROR:NOEXE /NOI /STACK:5120
LIBS_D_DEXE = oldnames mlibce
LIBS_R_DEXE = oldnames mlibce
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
OBJS_EXT = 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_DEXE)
LFLAGS = $(LFLAGS_D_DEXE)
LIBS = $(LIBS_D_DEXE)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_DEXE)
LFLAGS = $(LFLAGS_R_DEXE)
LIBS = $(LIBS_R_DEXE)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = CTAGS.SBR


CTAGS_DEP = c:\work\ctags\config.h \
	c:\work\ctags\wildcard.c


all:	$(PROJ).EXE $(PROJ).BSC

CTAGS.OBJ:	CTAGS.C $(CTAGS_DEP)
	$(CC) $(CFLAGS) $(CCREATEPCHFLAG) /c CTAGS.C

$(PROJ).EXE::	CTAGS.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
CTAGS.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
