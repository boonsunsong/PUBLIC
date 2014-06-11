# Microsoft Developer Studio Project File - Name="aspera" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=aspera - Win32 x64 console release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "aspera.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "aspera.mak" CFG="aspera - Win32 x64 console release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "aspera - Win32 x64 console release" (based on "Win32 (x86) Application")
!MESSAGE "aspera - Win32 x86 console release" (based on "Win32 (x86) Application")
!MESSAGE "aspera - Win32 x86 console debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "aspera - Win32 x64 console release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "x64\release"
# PROP BASE Intermediate_Dir "x64\release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "x64\release"
# PROP Intermediate_Dir "x64\release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W4 /WX /Ox /Ot /Oi /Ob2 /Gy /D "_CONSOLE" /D "NDEBUG" /D "_UNICODE" /D "UNICODE" /D "STRICT" /D "WIN32" /D _WIN32_WINNT=0x0600 /D _WIN32_IE=0x0600 /D "_CRT_SECURE_NO_DEPRECATE" /D "_CRT_SECURE_NO_WARNINGS" /GL /EHsc /GA /GF /GS- /c
# ADD CPP /nologo /MD /W4 /WX /Ox /Ot /Oi /Ob2 /Gy /D "_CONSOLE" /D "NDEBUG" /D "_UNICODE" /D "UNICODE" /D "STRICT" /D "WIN32" /D _WIN32_WINNT=0x0600 /D _WIN32_IE=0x0600 /D "_CRT_SECURE_NO_DEPRECATE" /D "_CRT_SECURE_NO_WARNINGS" /GL /EHsc /GA /GF /GS- /c
# SUBTRACT CPP /Og /YX /Yc /Yu
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_WIN64"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_WIN64"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:console /machine:IX86 /opt:ref /ignore:4089 /release /ltcg /machine:AMD64
# ADD LINK32 /nologo /subsystem:console /machine:IX86 /opt:ref /ignore:4089 /release /ltcg /machine:AMD64

!ELSEIF  "$(CFG)" == "aspera - Win32 x86 console release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "x86\release"
# PROP BASE Intermediate_Dir "x86\release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "x86\release"
# PROP Intermediate_Dir "x86\release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W4 /WX /Ox /Ot /Oi /Ob2 /Gy /D "_CONSOLE" /D "NDEBUG" /D "_UNICODE" /D "UNICODE" /D "STRICT" /D "WIN32" /D _WIN32_WINNT=0x0600 /D _WIN32_IE=0x0600 /D "_CRT_SECURE_NO_DEPRECATE" /D "_CRT_SECURE_NO_WARNINGS" /GL /EHsc /GA /GF /c
# ADD CPP /nologo /MD /W4 /WX /Ox /Ot /Oi /Ob2 /Gy /D "_CONSOLE" /D "NDEBUG" /D "_UNICODE" /D "UNICODE" /D "STRICT" /D "WIN32" /D _WIN32_WINNT=0x0600 /D _WIN32_IE=0x0600 /D "_CRT_SECURE_NO_DEPRECATE" /D "_CRT_SECURE_NO_WARNINGS" /GL /EHsc /GA /GF /c
# SUBTRACT CPP /Oa /Ow /Og /Os /YX /Yc /Yu
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:console /machine:IX86 /opt:ref /ignore:4089 /release /ltcg
# ADD LINK32 /nologo /subsystem:console /machine:IX86 /opt:ref /ignore:4089 /release /ltcg
# Begin Special Build Tool
TargetPath=.\x86\release\aspera.exe
SOURCE="$(InputPath)"
PostBuild_Cmds=copy $(TargetPath) D:\TEMP
# End Special Build Tool

!ELSEIF  "$(CFG)" == "aspera - Win32 x86 console debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "x86\debug"
# PROP BASE Intermediate_Dir "x86\debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "x86\debug"
# PROP Intermediate_Dir "x86\debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W4 /WX /GX /Zi /Od /I "..\sgi" /D "_CONSOLE" /D "_DEBUG" /D "_UNICODE" /D "UNICODE" /D "STRICT" /D "WIN32" /D _WIN32_WINNT=0x0600 /D _WIN32_IE=0x0600 /FR /Fd"x86\debug\aspera.pdb" /GF /c
# ADD CPP /nologo /MDd /W4 /WX /GX /Zi /Od /I "..\sgi" /D "_CONSOLE" /D "_DEBUG" /D "_UNICODE" /D "UNICODE" /D "STRICT" /D "WIN32" /D _WIN32_WINNT=0x0600 /D _WIN32_IE=0x0600 /FR /Fd"x86\debug\aspera.pdb" /GF /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:console /debug /machine:IX86
# ADD LINK32 /nologo /subsystem:console /debug /machine:IX86

!ENDIF 

# Begin Target

# Name "aspera - Win32 x64 console release"
# Name "aspera - Win32 x86 console release"
# Name "aspera - Win32 x86 console debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;def"
# Begin Source File

SOURCE=.\aspera.cpp
DEP_CPP_ASPER=\
	".\aspera.h"\
	".\trie.h"\
	

!IF  "$(CFG)" == "aspera - Win32 x64 console release"

!ELSEIF  "$(CFG)" == "aspera - Win32 x86 console release"

!ELSEIF  "$(CFG)" == "aspera - Win32 x86 console debug"

# ADD CPP /Ob2

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=.\aspera.h
# End Source File
# Begin Source File

SOURCE=.\trie.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "rc;ico;cur;bmp"
# Begin Source File

SOURCE=.\aspera.rc
# End Source File
# End Group
# End Target
# End Project
