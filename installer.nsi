# This installs two files, app.exe and logo.ico, creates a start menu shortcut, builds an uninstaller, and
# adds uninstall information to the registry for Add/Remove Programs
 
# To get started, put this script into a folder with the two files (app.exe, logo.ico, and license.rtf -
# You'll have to create these yourself) and run makensis on it
 
# If you change the names "app.exe", "logo.ico", or "license.rtf" you should do a search and replace - they
# show up in a few places.
# All the other settings can be tweaked by editing the !defines at the top of this script
!define APPNAME "Morphling"
!define COMPANYNAME "MorphlingDev"
!define DESCRIPTION "Roguelike"
Name "Morphling Installer"
# These three must be integers
!define VERSIONMAJOR 0
!define VERSIONMINOR 0
!define VERSIONBUILD 69
# These will be displayed by the "Click here for support information" link in "Add/Remove Programs"
# It is possible to use "mailto:" links in here to open the email client
!define HELPURL "https://github.com/morphlingdev/Morphling/wiki" # "Support Information" link
!define UPDATEURL "https://github.com/morphlingdev/Morphling" # "Product Updates" link
!define ABOUTURL "https://github.com/morphlingdev" # "Publisher" link
# This is the size (in kB) of all the files copied into "Program Files"
!define INSTALLSIZE 4136
 
RequestExecutionLevel admin ;Require admin rights on NT6+ (When UAC is turned on)
 
InstallDir "$PROGRAMFILES\${APPNAME}"
 
# rtf or txt file - remember if it is txt, it must be in the DOS text format (\r\n)
LicenseData "license.rtf"
# This will be in the installer/uninstaller's title bar
Name "${APPNAME}"
Icon "icon.ico"
outFile "Morphling-Setup.exe"
 
!include LogicLib.nsh
!include "MUI.nsh"

!insertmacro MUI_PAGE_WELCOME
page license
page directory
page instfiles
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_LANGUAGE "English"

!macro VerifyUserIsAdmin
UserInfo::GetAccountType
pop $0
${If} $0 != "admin" ;Require admin rights on NT4+
        messageBox mb_iconstop "Administrator rights required!"
        setErrorLevel 740 ;ERROR_ELEVATION_REQUIRED
        quit
${EndIf}
!macroend

function .onInit
	setShellVarContext all
	!insertmacro VerifyUserIsAdmin
functionEnd


section "install"

SetOutPath "$INSTDIR"

file "morphling.exe"
file "icon.ico"
file "zlib1.dll"
file "tiles.png"
file "sprites.png"
file "SDL_ttf.dll"
file "SDL_image.dll"
file "SDL.dll"
file "README"
file "license.rtf"
file "libtiff-3.dll"
file "libpng12-0.dll"
file "libfreetype-6.dll"
file "jpeg.dll"
file "icon.bmp"
file "DejaVuSansMono.ttf"
file "DejaVuSans.ttf"
file "AUTHORS"

writeUninstaller "$INSTDIR\uninstall.exe"

createDirectory "$SMPROGRAMS\Morphling"

CreateShortCut "$SMPROGRAMS\Morphling\Morphling.lnk" "$INSTDIR\morphling.exe" "" "$INSTDIR\icon.ico"
CreateShortCut "$DESKTOP\Morphling.lnk" "$INSTDIR\morphling.exe" "" "$INSTDIR\icon.ico"

# Registry information for add/remove programs
WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "DisplayName" "${APPNAME}"
WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "UninstallString" "$INSTDIR\uninstall.exe"
WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "QuietUninstallString" "$INSTDIR\uninstall.exe /S"
WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "InstallLocation" "$INSTDIR"
WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "DisplayIcon" "$INSTDIR\logo.ico"
WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "Publisher" "${COMPANYNAME}"
WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "HelpLink" "${HELPURL}"
WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "URLUpdateInfo" "${UPDATEURL}"
WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "URLInfoAbout" "${ABOUTURL}"
WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "DisplayVersion" "${VERSIONMAJOR}.${VERSIONMINOR}.${VERSIONBUILD}"
WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "VersionMajor" "${VERSIONMAJOR}"
WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "VersionMinor" "${VERSIONMINOR}"
# There is no option for modifying or repairing the install
WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "NoModify" 1
WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "NoRepair" 1
# Set the INSTALLSIZE constant (!defined at the top of this script) so Add/Remove Programs can accurately report the size
WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "EstimatedSize" ${INSTALLSIZE}

sectionEnd

function un.onInit
	SetShellVarContext all
 
	#Verify the uninstaller - last chance to back out
	MessageBox MB_OKCANCEL "Permanantly remove ${APPNAME}?" IDOK next
		Abort
	next:
	!insertmacro VerifyUserIsAdmin
functionEnd

section "uninstall"
 
	# Remove Start Menu launcher
	delete "$SMPROGRAMS\Morphling\Morphling.lnk"
	delete "$DESKTOP\Morphling.lnk"
	# Try to remove the Start Menu folder - this will only happen if it is empty
	rmDir "$SMPROGRAMS\Morphling"
 
	# Remove files
	delete $INSTDIR\morphling.exe
	delete $INSTDIR\icon.ico
	delete $INSTDIR\zlib1.dll
	delete $INSTDIR\tiles.png
	delete $INSTDIR\sprites.png
	delete $INSTDIR\SDL_ttf.dll
	delete $INSTDIR\SDL_image.dll
	delete $INSTDIR\SDL.dll
	delete $INSTDIR\README
	delete $INSTDIR\license.rtf
	delete $INSTDIR\libtiff-3.dll
	delete $INSTDIR\libpng12-0.dll
	delete $INSTDIR\libfreetype-6.dll
	delete $INSTDIR\jpeg.dll
	delete $INSTDIR\icon.bmp
	delete $INSTDIR\DejaVuSansMono.ttf
	delete $INSTDIR\DejaVuSans.ttf
	delete $INSTDIR\AUTHORS
 
	# Always delete uninstaller as the last action
	delete $INSTDIR\uninstall.exe
 
	# Try to remove the install directory - this will only happen if it is empty
	rmDir $INSTDIR
 
	# Remove uninstaller information from the registry
	DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}"
sectionEnd
