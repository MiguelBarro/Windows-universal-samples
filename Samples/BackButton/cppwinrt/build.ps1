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
if ($pwd.Path -notmatch "Samples.SystemBack.cppwinrt") { cd C:/localrepos/Windows-universal-samples/Samples/SystemBack/cppwinrt }
Get-AppxPackage *SystemBack* | Remove-AppxPackage
clear; msbuild -p:Platform=x64 -p:Configuration=$config -p:RestorePackagesConfig=true SystemBack.slnx -t:"Restore;Build"
if (-not (Test-Path $Env:TMP/Execute-AppxRecipe.ps1))
{
    iwr -Uri https://gist.githubusercontent.com/MiguelBarro/6c993b519e1b2a0c2406357194f66489/raw/1d7a20861e43a07fbd501eb01971058730cb7756/Execute-AppxRecipe.ps1 -OutFile $Env:TMP/Execute-AppxRecipe.ps1
}
& $env:TMP/Execute-AppxRecipe.ps1 -AppxRecipePath .\x64\$config\SystemBack\SystemBack.build.appxrecipe -LayoutPath x64\$config\SystemBack\AppX -Force
pushd x64\$config\SystemBack\AppX 
Add-AppxPackage -Register AppxManifest.xml
popd

# $publisherid = (Get-AppxPackage *SystemBack*).PublisherId
# cdbx64 -plmPackage Microsoft.SDKSamples.SystemBack.cppwinrt_1.0.0.0_x64__$publisherid -plmApp App
# explorer.exe shell:appsFolder\Microsoft.SDKSamples.SystemBack.CPPWINRT_$publisherid!App
# start shell:appsFolder\Microsoft.SDKSamples.SystemBack.CPPWINRT_$publisherid!App
# Start-Process shell:appsFolder\Microsoft.SDKSamples.SystemBack.CPPWINRT_$publisherid!App
