;--------------------------------
;Include Modern UI

  !include "MUI2.nsh"
  !include "config_windows_pack.nsh"

;--------------------------------
;Start

  !define MUI_FILE ${GAME_NAME}
  !define MUI_PRODUCT ${GAME_NAME}

;--------------------------------
;General

  ;Name and file
  Name ${GAME_NAME}
  OutFile ${INSTALLER_NAME}

 ; !define MUI_ICON "settings.png"

  ;Default installation folder
  InstallDir "$LOCALAPPDATA\${GAME_NAME}"
  
  ;Get installation folder from registry if available
  InstallDirRegKey HKCU "Software\${GAME_NAME}" ""

  ;Request application privileges for Windows Vista
  RequestExecutionLevel user

;--------------------------------
;Interface Settings

  !define MUI_ABORTWARNING
  !define MUI_WELCOMEPAGE
;--------------------------------
;Pages

  !insertmacro MUI_PAGE_LICENSE "license.txt"
  !insertmacro MUI_PAGE_COMPONENTS
  !insertmacro MUI_PAGE_DIRECTORY
  !insertmacro MUI_PAGE_INSTFILES
  
  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES
  
;--------------------------------
;Languages
 
  !insertmacro MUI_LANGUAGE "English"

;--------------------------------
;Installer Sections

Section "Install Section" SecDummy

  SetOutPath "$INSTDIR"
  
  ;ADD YOUR OWN FILES HERE...
  ;File "${MUI_FILE}.exe"
  ;FILE "${MUI_FILE}.ini"
  SetOutPath "$INSTDIR\assets"
  File /r "game\assets\*.*"

  SetOutPath "$INSTDIR"
  File "build\${EXECUTABLE_NAME}.exe"

  SetOutPath "$INSTDIR"
  File /r "build\libs\*.*"

  ;Store installation folder
  WriteRegStr HKCU "Software\${GAME_NAME}" "" $INSTDIR
  
  ;Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"

  ;Create desktop shortcut
  CreateShortCut "$DESKTOP\${MUI_PRODUCT}.lnk" "$INSTDIR\${MUI_FILE}.exe" ""

SectionEnd

;--------------------------------
;Descriptions

  ;Language strings
  LangString DESC_SecDummy ${LANG_ENGLISH} "Main files to run game."

  ;Assign language strings to sections
  !insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
    !insertmacro MUI_DESCRIPTION_TEXT ${SecDummy} $(DESC_SecDummy)
  !insertmacro MUI_FUNCTION_DESCRIPTION_END

;--------------------------------
;Uninstaller Section

Section "Uninstall"

  ;ADD YOUR OWN FILES HERE...

  Delete "$INSTDIR\Uninstall.exe"

  RMDir /r "$INSTDIR"

  DeleteRegKey /ifempty HKCU "Software\${GAME_NAME}"

SectionEnd
