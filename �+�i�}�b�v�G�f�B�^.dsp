# Microsoft Developer Studio Project File - Name="�ȈՃ}�b�v�G�f�B�^" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** �ҏW���Ȃ��ł������� **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=�ȈՃ}�b�v�G�f�B�^ - Win32 Debug
!MESSAGE ����͗L����Ҳ�̧�قł͂���܂���B ������ۼު�Ă�����ނ��邽�߂ɂ� NMAKE ���g�p���Ă��������B
!MESSAGE [Ҳ�̧�ق̴���߰�] ����ނ��g�p���Ď��s���Ă�������
!MESSAGE 
!MESSAGE NMAKE /f "�ȈՃ}�b�v�G�f�B�^.mak".
!MESSAGE 
!MESSAGE NMAKE �̎��s���ɍ\�����w��ł��܂�
!MESSAGE ����� ײݏ��ϸۂ̐ݒ���`���܂��B��:
!MESSAGE 
!MESSAGE NMAKE /f "�ȈՃ}�b�v�G�f�B�^.mak" CFG="�ȈՃ}�b�v�G�f�B�^ - Win32 Debug"
!MESSAGE 
!MESSAGE �I���\������� Ӱ��:
!MESSAGE 
!MESSAGE "�ȈՃ}�b�v�G�f�B�^ - Win32 Release" ("Win32 (x86) Application" �p)
!MESSAGE "�ȈՃ}�b�v�G�f�B�^ - Win32 Debug" ("Win32 (x86) Application" �p)
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "�ȈՃ}�b�v�G�f�B�^ - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x411 /d "NDEBUG"
# ADD RSC /l 0x411 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "�ȈՃ}�b�v�G�f�B�^ - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x411 /d "_DEBUG"
# ADD RSC /l 0x411 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "�ȈՃ}�b�v�G�f�B�^ - Win32 Release"
# Name "�ȈՃ}�b�v�G�f�B�^ - Win32 Debug"
# Begin Group "�O���ϐ�"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\extern.h
# End Source File
# Begin Source File

SOURCE=.\Global.h
# End Source File
# End Group
# Begin Group "SAVE_LOAD"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\File_WriteRead.cpp
# End Source File
# Begin Source File

SOURCE=.\File_WriteRead.h
# End Source File
# Begin Source File

SOURCE=.\Game_SaveLoad.cpp
# End Source File
# Begin Source File

SOURCE=.\Game_SaveLoad.h
# End Source File
# End Group
# Begin Group "�}�N��"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\define.h
# End Source File
# End Group
# Begin Group "WinProc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\WinProc.cpp
# End Source File
# Begin Source File

SOURCE=.\WinProc.h
# End Source File
# End Group
# Begin Group "Bmp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ImageSetUp.cpp
# End Source File
# Begin Source File

SOURCE=.\ImageSetUp.h
# End Source File
# End Group
# Begin Group "ChildWinProc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ChildWinProc.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildWinProc.h
# End Source File
# End Group
# Begin Group "MinMapProc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MinMapWinProc.cpp
# End Source File
# Begin Source File

SOURCE=.\MinMapWinProc.h
# End Source File
# End Group
# Begin Group "GAMESTRCUT"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\GameStruct.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Script1.rc
# End Source File
# Begin Source File

SOURCE=.\WinMain.cpp
# End Source File
# End Target
# End Project
