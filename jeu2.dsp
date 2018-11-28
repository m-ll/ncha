# Microsoft Developer Studio Project File - Name="jeu2" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=jeu2 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "jeu2.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "jeu2.mak" CFG="jeu2 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "jeu2 - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "jeu2 - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "jeu2 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "jeu2 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MD /W3 /WX /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib SDL.lib SDLmain.lib SDL_mixer.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "jeu2 - Win32 Release"
# Name "jeu2 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "sprite cpp"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\bg.cpp
# End Source File
# Begin Source File

SOURCE=.\decor.cpp
# End Source File
# Begin Source File

SOURCE=.\decor_obj.cpp
# End Source File
# Begin Source File

SOURCE=.\ennemi.cpp
# End Source File
# Begin Source File

SOURCE=.\hero.cpp
# End Source File
# Begin Source File

SOURCE=.\perso.cpp
# End Source File
# Begin Source File

SOURCE=.\sprite.cpp
# End Source File
# End Group
# Begin Group "mvt cpp"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\bottom.cpp
# End Source File
# Begin Source File

SOURCE=.\left.cpp
# End Source File
# Begin Source File

SOURCE=.\mvt.cpp
# End Source File
# Begin Source File

SOURCE=.\right.cpp
# End Source File
# Begin Source File

SOURCE=.\top.cpp
# End Source File
# Begin Source File

SOURCE=.\tourner.cpp
# End Source File
# End Group
# Begin Group "sound cpp"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\music.cpp
# End Source File
# Begin Source File

SOURCE=.\sound.cpp
# End Source File
# End Group
# Begin Group "thread cpp"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\th_boule.cpp
# End Source File
# Begin Source File

SOURCE=.\th_ennemi.cpp
# End Source File
# Begin Source File

SOURCE=.\th_jauge.cpp
# End Source File
# Begin Source File

SOURCE=.\th_piece.cpp
# End Source File
# Begin Source File

SOURCE=.\th_saut.cpp
# End Source File
# Begin Source File

SOURCE=.\thread.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\all_ennemi.cpp
# End Source File
# Begin Source File

SOURCE=.\bete.cpp
# End Source File
# Begin Source File

SOURCE=.\crypte_bmp.cpp
# End Source File
# Begin Source File

SOURCE=.\font.cpp
# End Source File
# Begin Source File

SOURCE=..\jeu2\frame.cpp
# End Source File
# Begin Source File

SOURCE=.\matrice.cpp
# End Source File
# Begin Source File

SOURCE=.\princ.cpp
# End Source File
# Begin Source File

SOURCE=.\stage.cpp
# End Source File
# Begin Source File

SOURCE=.\surface.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "mvt"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\bottom.h
# End Source File
# Begin Source File

SOURCE=.\left.h
# End Source File
# Begin Source File

SOURCE=.\mvt.h
# End Source File
# Begin Source File

SOURCE=.\right.h
# End Source File
# Begin Source File

SOURCE=.\top.h
# End Source File
# Begin Source File

SOURCE=.\tourner.h
# End Source File
# End Group
# Begin Group "sprite"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\bg.h
# End Source File
# Begin Source File

SOURCE=.\decor.h
# End Source File
# Begin Source File

SOURCE=.\decor_obj.h
# End Source File
# Begin Source File

SOURCE=.\ennemi.h
# End Source File
# Begin Source File

SOURCE=.\hero.h
# End Source File
# Begin Source File

SOURCE=.\perso.h
# End Source File
# Begin Source File

SOURCE=.\sprite.h
# End Source File
# End Group
# Begin Group "thread"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\th_boule.h
# End Source File
# Begin Source File

SOURCE=.\th_ennemi.h
# End Source File
# Begin Source File

SOURCE=.\th_jauge.h
# End Source File
# Begin Source File

SOURCE=.\th_piece.h
# End Source File
# Begin Source File

SOURCE=.\th_saut.h
# End Source File
# Begin Source File

SOURCE=.\thread.h
# End Source File
# End Group
# Begin Group "sound"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\music.h
# End Source File
# Begin Source File

SOURCE=.\sound.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\all_ennemi.h
# End Source File
# Begin Source File

SOURCE=.\bete.h
# End Source File
# Begin Source File

SOURCE=.\crypte_bmp.h
# End Source File
# Begin Source File

SOURCE=.\font.h
# End Source File
# Begin Source File

SOURCE=..\jeu2\frame.h
# End Source File
# Begin Source File

SOURCE=.\matrice.h
# End Source File
# Begin Source File

SOURCE=.\stage.h
# End Source File
# Begin Source File

SOURCE=.\surface.h
# End Source File
# Begin Source File

SOURCE=..\jeu2\type.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Group "icone"

# PROP Default_Filter "*.bmp"
# Begin Source File

SOURCE=.\Debug\data\icone\pisuke.bmp
# End Source File
# Begin Source File

SOURCE=.\Debug\data\icone\turbo.bmp
# End Source File
# End Group
# End Group
# End Target
# End Project
