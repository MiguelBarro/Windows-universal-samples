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
if ($pwd.Path -notmatch "Samples.OCR.cppwinrt") { cd C:/localrepos/Windows-universal-samples/Samples/OCR/cppwinrt }
Get-AppxPackage *Transform3DAnimations* | Remove-AppxPackage
clear; msbuild -p:Platform=x64 -p:Configuration=$config -p:RestorePackagesConfig=true OCR.sln -t:"Restore;Build"
if (-not (Test-Path $Env:TMP/Execute-AppxRecipe.ps1))
{
    iwr -Uri https://gist.githubusercontent.com/MiguelBarro/6c993b519e1b2a0c2406357194f66489/raw/1d7a20861e43a07fbd501eb01971058730cb7756/Execute-AppxRecipe.ps1 -OutFile $Env:TMP/Execute-AppxRecipe.ps1
}
& $env:TMP/Execute-AppxRecipe.ps1 -AppxRecipePath .\x64\$config\OCR\OCR.build.appxrecipe -LayoutPath x64\$config\OCR\AppX -Force
pushd x64\$config\OCR\AppX 
Add-AppxPackage -Register AppxManifest.xml
popd

# cdbx64 -plmPackage Microsoft.SDKSamples.OCR.CPPWINRT_1.0.0.0_x64__6w9dh12hc1tpg -plmApp App
# explorer.exe shell:appsFolder\Microsoft.SDKSamples.OCR.CPPWINRT_6w9dh12hc1tpg!App
# start shell:appsFolder\Microsoft.SDKSamples.OCR.CPPWINRT_6w9dh12hc1tpg!App
# Start-Process shell:appsFolder\Microsoft.SDKSamples.OCR.CPPWINRT_6w9dh12hc1tpg!App
