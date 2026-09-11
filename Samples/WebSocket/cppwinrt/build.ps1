# build.ps1
Param(
    [ValidateSet("Debug", "Release", "RelWithDebInfo")]
    [String]$config="Debug"
)
if(-not (Get-Command msbuild -ErrorAction SilentlyContinue))
{
    $vswhere = "${Env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe";
    & $vswhere -find **/Microsoft.VisualStudio.DevShell.dll | Import-Module;
    Enter-VsDevShell -SetDefaultWindowTitle -InstallPath (& $vswhere -property installationPath) -StartInPath $pwd -Arch amd64 -HostArch amd64
}
if ($pwd.Path -notmatch "Samples.WebSocket.cppwinrt") { cd C:/localrepos/Windows-universal-samples/Samples/WebSocket/cppwinrt }
Get-AppxPackage *WebSocket* | Remove-AppxPackage
clear; msbuild -p:Platform=x64 -p:Configuration=$config -p:RestorePackagesConfig=true WebSocket.sln -t:"Restore;Build" -m
if (-not (Test-Path $Env:TMP/Execute-AppxRecipe.ps1))
{
    iwr -Uri https://gist.githubusercontent.com/MiguelBarro/6c993b519e1b2a0c2406357194f66489/raw/1d7a20861e43a07fbd501eb01971058730cb7756/Execute-AppxRecipe.ps1 -OutFile $Env:TMP/Execute-AppxRecipe.ps1
}
& $env:TMP/Execute-AppxRecipe.ps1 -AppxRecipePath .\x64\$config\WebSocket\WebSocket.build.appxrecipe -LayoutPath x64\$config\WebSocket\AppX -Force
pushd x64\$config\WebSocket\AppX 
Add-AppxPackage -Register AppxManifest.xml
popd
                    
# cdbx64 -plmPackage Microsoft.SDKSamples.WebSocket.CPPWINRT_1.0.0.0_x64__8wekyb3d8bbwe -plmApp App
# explorer.exe shell:appsFolder\Microsoft.SDKSamples.WebSocket.CPPWINRT_8wekyb3d8bbwe!App
# start shell:appsFolder\Microsoft.SDKSamples.WebSocket.CPPWINRT_8wekyb3d8bbwe!App
# Start-Process shell:appsFolder\Microsoft.SDKSamples.WebSocket.CPPWINRT_8wekyb3d8bbwe!App
