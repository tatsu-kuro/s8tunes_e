# Microsoft Developer Studio Project File - Name="s8tune" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** 編集しないでください **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=s8tune - Win32 Debug
!MESSAGE これは有効なﾒｲｸﾌｧｲﾙではありません。 このﾌﾟﾛｼﾞｪｸﾄをﾋﾞﾙﾄﾞするためには NMAKE を使用してください。
!MESSAGE [ﾒｲｸﾌｧｲﾙのｴｸｽﾎﾟｰﾄ] ｺﾏﾝﾄﾞを使用して実行してください
!MESSAGE 
!MESSAGE NMAKE /f "s8tune.mak".
!MESSAGE 
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "s8tune.mak" CFG="s8tune - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "s8tune - Win32 Release" ("Win32 (x86) Application" 用)
!MESSAGE "s8tune - Win32 Debug" ("Win32 (x86) Application" 用)
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "s8tune - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x411 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 winmm.lib tags.lib bass_aac.lib bassenc.lib basswma.lib bass.lib bass_fx.lib kernel32.lib user32.lib comdlg32.lib gdi32.lib /nologo /subsystem:windows /machine:I386 /out:"Release/s8Tunes.exe"

!ELSEIF  "$(CFG)" == "s8tune - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x411 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 winmm.lib tags.lib bass_aac.lib bassenc.lib basswma.lib bass.lib bass_fx.lib kernel32.lib user32.lib comdlg32.lib gdi32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"Debug/s8Tunes.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "s8tune - Win32 Release"
# Name "s8tune - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AddThread.cpp
# End Source File
# Begin Source File

SOURCE=.\HelpDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Rename.cpp
# End Source File
# Begin Source File

SOURCE=.\s8tune.cpp
# End Source File
# Begin Source File

SOURCE=.\s8tune.rc
# End Source File
# Begin Source File

SOURCE=.\s8tuneDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\s8tuneView.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AddThread.h
# End Source File
# Begin Source File

SOURCE=.\HelpDlg.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Rename.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\s8tune.h
# End Source File
# Begin Source File

SOURCE=.\s8tuneDoc.h
# End Source File
# Begin Source File

SOURCE=.\s8tuneView.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\curdrop.cur
# End Source File
# Begin Source File

SOURCE=.\res\curdrop1.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\kensong.bmp
# End Source File
# Begin Source File

SOURCE=.\res\pause.bmp
# End Source File
# Begin Source File

SOURCE=.\res\pause1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\pause2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\pause3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\pause4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\play.bmp
# End Source File
# Begin Source File

SOURCE=.\res\play1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\play11.bmp
# End Source File
# Begin Source File

SOURCE=.\res\record1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\s8tune.ico
# End Source File
# Begin Source File

SOURCE=.\res\s8tune.rc2
# End Source File
# Begin Source File

SOURCE=.\res\s8tuneDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\saveab1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\seta1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\setb1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\speaker.bmp
# End Source File
# Begin Source File

SOURCE=.\res\speaker1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\speaker2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tonext.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tonext1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tonow.bmp
# End Source File
# Begin Source File

SOURCE=.\res\totop.bmp
# End Source File
# Begin Source File

SOURCE=.\res\totop1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\volume.bmp
# End Source File
# Begin Source File

SOURCE=.\res\volume1.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
