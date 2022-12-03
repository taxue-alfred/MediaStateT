; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "MediaStateT"
#define MyAppVersion "1.4"
#define MyAppPublisher "TaXue"
#define MyAppURL "https://gitee.com/txwh-media-state/media-state-t"
#define MyAppExeName "MediaStateT.exe"

[Setup]
; NOTE: The value of AppId uniquely identifies this application. Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{715D181A-867B-49B9-87AF-0D09B6F0722E}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={localappdata}\Programs\{#MyAppName}
DisableProgramGroupPage=yes
; Remove the following line to run in administrative install mode (install for all users.)
PrivilegesRequired=admin
OutputDir=D:\Installer
OutputBaseFilename=MediaStateInstaller-1.4
SetupIconFile=D:\Photos\Image\az7h7-4zv50-001.ico
Compression=lzma
SolidCompression=yes
WizardStyle=modern

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "D:\Projects\PersonalProject\media-state-t\out\{#MyAppExeName}"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Projects\PersonalProject\media-state-t\out\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "D:\Projects\PersonalProject\media-state-t\out\audio_sniffer-x64.dll"; DestDir: "{app}"; Flags: ignoreversion regserver
;Source: "D:\Projects\PersonalProject\media-state-t\out\audio_sniffer-x64.dll"; DestDir: "{app}"; Flags: regtypelib
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{autoprograms}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{autodesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

