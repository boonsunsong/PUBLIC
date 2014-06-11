# Microsoft Developer Studio Project File - Name="bromium" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=bromium - Win32 x86 debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "bromium.MAK".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "bromium.MAK" CFG="bromium - Win32 x86 debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "bromium - Win32 x64 release" (based on "Win32 (x86) Application")
!MESSAGE "bromium - Win32 x86 release" (based on "Win32 (x86) Application")
!MESSAGE "bromium - Win32 x86 release vc6" (based on "Win32 (x86) Application")
!MESSAGE "bromium - Win32 x86 debug" (based on "Win32 (x86) Application")
!MESSAGE "bromium - Win32 x86 debug wine" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "bromium - Win32 x64 release"

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
# ADD BASE CPP /nologo /MD /W3 /WX /Ot /Oy /Ob2 /Gy /D "NDEBUG" /D "_UNICODE" /D "UNICODE" /D "STRICT" /D "WIN32" /D NTDDI_VERSION=0x06030000 /D _WIN32_WINNT=0x0603 /D _WIN32_IE=0x0A00 /D "_CRT_SECURE_NO_DEPRECATE" /D "_CRT_SECURE_NO_WARNINGS" /Fp"x64\release\precomp.pch" /Yu"precomp.h" /GL /GA /GF /GS- /c
# ADD CPP /nologo /MD /W3 /WX /Ot /Oy /Ob2 /Gy /D "NDEBUG" /D "_UNICODE" /D "UNICODE" /D "STRICT" /D "WIN32" /D NTDDI_VERSION=0x06030000 /D _WIN32_WINNT=0x0603 /D _WIN32_IE=0x0A00 /D "_CRT_SECURE_NO_DEPRECATE" /D "_CRT_SECURE_NO_WARNINGS" /Fp"x64\release\precomp.pch" /Yu"precomp.h" /GL /GA /GF /GS- /c
# SUBTRACT CPP /Ox /Og /Oi
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_WIN64"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_WIN64"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:IX86 /opt:ref /ignore:4089 /release /ltcg /machine:AMD64
# ADD LINK32 /nologo /subsystem:windows /machine:IX86 /opt:ref /ignore:4089 /release /ltcg /machine:AMD64

!ELSEIF  "$(CFG)" == "bromium - Win32 x86 release"

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
# ADD BASE CPP /nologo /MD /W3 /WX /Ox /Ot /Og /Oi /Ob2 /Gy /D "NDEBUG" /D "_UNICODE" /D "UNICODE" /D "STRICT" /D "WIN32" /D NTDDI_VERSION=0x06030000 /D _WIN32_WINNT=0x0603 /D _WIN32_IE=0x0A00 /D "_CRT_SECURE_NO_DEPRECATE" /D "_CRT_SECURE_NO_WARNINGS" /Fp"x86\release\precomp.pch" /Yu"precomp.h" /GL /GA /GF /c
# ADD CPP /nologo /MD /W3 /WX /Ox /Ot /Oi /Ob2 /Gy /D "NDEBUG" /D "_UNICODE" /D "UNICODE" /D "STRICT" /D "WIN32" /D NTDDI_VERSION=0x06030000 /D _WIN32_WINNT=0x0603 /D _WIN32_IE=0x0A00 /D "_CRT_SECURE_NO_DEPRECATE" /D "_CRT_SECURE_NO_WARNINGS" /Fp"x86\release\precomp.pch" /Yu"precomp.h" /GL /GA /GF /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:IX86 /opt:ref /ignore:4089 /release /ltcg
# ADD LINK32 /nologo /subsystem:windows /machine:IX86 /opt:ref /ignore:4089 /release /ltcg

!ELSEIF  "$(CFG)" == "bromium - Win32 x86 release vc6"

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
# ADD BASE CPP /nologo /MD /W3 /WX /Ox /Ot /Og /Oi /Ob2 /Gy /D "NDEBUG" /D "_UNICODE" /D "UNICODE" /D "STRICT" /D "WIN32" /D NTDDI_VERSION=0x06000400 /D _WIN32_WINNT=0x0600 /D _WIN32_IE=0x0700 /D "_CRT_SECURE_NO_DEPRECATE" /D "_CRT_SECURE_NO_WARNINGS" /Fp"x86\release\precomp.pch" /Yu"precomp.h" /GA /GF /c
# ADD CPP /nologo /MD /W3 /WX /Ox /Ot /Oi /Ob2 /Gy /D "NDEBUG" /D "_UNICODE" /D "UNICODE" /D "STRICT" /D "WIN32" /D NTDDI_VERSION=0x06000400 /D _WIN32_WINNT=0x0600 /D _WIN32_IE=0x0700 /D "_CRT_SECURE_NO_DEPRECATE" /D "_CRT_SECURE_NO_WARNINGS" /Fp"x86\release\precomp.pch" /Yu"precomp.h" /GA /GF /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:IX86 /opt:ref /ignore:4089 /release
# ADD LINK32 gdi32.lib shell32.lib /nologo /subsystem:windows /machine:IX86 /opt:ref /ignore:4089 /release

!ELSEIF  "$(CFG)" == "bromium - Win32 x86 debug"

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
# ADD BASE CPP /nologo /MDd /W3 /WX /Zi /Od /D "_DEBUG" /D "_UNICODE" /D "UNICODE" /D "STRICT" /D "WIN32" /D NTDDI_VERSION=0x06000400 /D _WIN32_WINNT=0x0600 /D _WIN32_IE=0x0700 /D "_CRT_SECURE_NO_DEPRECATE" /D "_CRT_SECURE_NO_WARNINGS" /FR /Fp"x86\debug\precomp.pch" /Yu"precomp.h" /Fd"x86\debug\bromium.pdb" /GA /GF /c
# ADD CPP /nologo /MDd /W3 /WX /Zi /Od /D "_DEBUG" /D "_UNICODE" /D "UNICODE" /D "STRICT" /D "WIN32" /D NTDDI_VERSION=0x06000400 /D _WIN32_WINNT=0x0600 /D _WIN32_IE=0x0700 /D "_CRT_SECURE_NO_DEPRECATE" /D "_CRT_SECURE_NO_WARNINGS" /FR /Fp"x86\debug\precomp.pch" /Yu"precomp.h" /Fd"x86\debug\bromium.pdb" /GF /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:IX86
# ADD LINK32 gdi32.lib shell32.lib /nologo /subsystem:windows /debug /machine:IX86

!ELSEIF  "$(CFG)" == "bromium - Win32 x86 debug wine"

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
# ADD BASE CPP /nologo /MTd /W3 /WX /Zi /Od /D "_DEBUG" /D "_UNICODE" /D "UNICODE" /D "STRICT" /D "WIN32" /D NTDDI_VERSION=0x06000400 /D _WIN32_WINNT=0x0600 /D _WIN32_IE=0x0700 /D "_CRT_SECURE_NO_DEPRECATE" /D "_CRT_SECURE_NO_WARNINGS" /D "SECURITY_WIN32" /FR /Fd"x86\debug\bromium.pdb" /GF /c
# ADD CPP /nologo /MTd /W3 /WX /Zi /Od /D "_DEBUG" /D "_UNICODE" /D "UNICODE" /D "STRICT" /D "WIN32" /D NTDDI_VERSION=0x06000400 /D _WIN32_WINNT=0x0600 /D _WIN32_IE=0x0700 /D "_CRT_SECURE_NO_DEPRECATE" /D "_CRT_SECURE_NO_WARNINGS" /D "SECURITY_WIN32" /FR /Fd"x86\debug\bromium.pdb" /GF /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:IX86
# ADD LINK32 /nologo /subsystem:windows /debug /machine:IX86

!ENDIF 

# Begin Target

# Name "bromium - Win32 x64 release"
# Name "bromium - Win32 x86 release"
# Name "bromium - Win32 x86 release vc6"
# Name "bromium - Win32 x86 debug"
# Name "bromium - Win32 x86 debug wine"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\bromium.cpp
DEP_CPP_BROMI=\
	"..\nvidia\nvdpf.h"\
	"..\nvidia\typedef.h"\
	"..\nvidia\util.h"\
	".\bromium.h"\
	".\precomp.h"\
	
# End Source File
# Begin Source File

SOURCE=.\precomp.cpp
DEP_CPP_PRECO=\
	"..\nvidia\nvdpf.h"\
	"..\nvidia\typedef.h"\
	"..\nvidia\util.h"\
	".\bromium.h"\
	".\precomp.h"\
	

!IF  "$(CFG)" == "bromium - Win32 x64 release"

# ADD CPP /Yc"precomp.h"

!ELSEIF  "$(CFG)" == "bromium - Win32 x86 release"

# ADD CPP /Yc"precomp.h"

!ELSEIF  "$(CFG)" == "bromium - Win32 x86 release vc6"

# ADD CPP /Yc"precomp.h"

!ELSEIF  "$(CFG)" == "bromium - Win32 x86 debug"

# ADD CPP /Yc"precomp.h"

!ELSEIF  "$(CFG)" == "bromium - Win32 x86 debug wine"

# PROP Exclude_From_Build 1
# ADD BASE CPP /Yc"precomp.h"
# SUBTRACT CPP /YX /Yc

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\bromium.h
# End Source File
# Begin Source File

SOURCE=.\precomp.h

!IF  "$(CFG)" == "bromium - Win32 x64 release"

!ELSEIF  "$(CFG)" == "bromium - Win32 x86 release"

!ELSEIF  "$(CFG)" == "bromium - Win32 x86 release vc6"

!ELSEIF  "$(CFG)" == "bromium - Win32 x86 debug"

!ELSEIF  "$(CFG)" == "bromium - Win32 x86 debug wine"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\bromium.ico
# End Source File
# Begin Source File

SOURCE=.\bromium.rc
# End Source File
# End Group
# End Target
# End Project
