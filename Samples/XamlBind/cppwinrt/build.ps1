# build.ps1
if(-not (Get-Command msbuild -ErrorAction SilentlyContinue))
{
    $vswhere = "${Env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe";
    & $vswhere -find **/Microsoft.VisualStudio.DevShell.dll | Import-Module;
    Enter-VsDevShell -SetDefaultWindowTitle -InstallPath (& $vswhere -property installationPath) -StartInPath $pwd -Arch amd64 -HostArch amd64
}
if ($pwd.Path -notmatch "Samples.XamlBind.cppwinrt") { cd /repos/Windows-universal-samples/Samples/XamlBind/cppwinrt }
Get-AppxPackage *xBindSampleCPP* -ErrorAction SilentlyContinue | Remove-AppxPackage
clear; msbuild -p:Platform=x64 -p:RestorePackagesConfig=true -p:Configuration=Debug xBindSampleCPP.sln -t:"Restore;Build" -m
if (-not (Test-Path $Env:TMP/Execute-AppxRecipe.ps1))
{
    iwr -Uri https://gist.githubusercontent.com/MiguelBarro/6c993b519e1b2a0c2406357194f66489/raw/1d7a20861e43a07fbd501eb01971058730cb7756/Execute-AppxRecipe.ps1 -OutFile $Env:TMP/Execute-AppxRecipe.ps1
}
& $env:TMP/Execute-AppxRecipe.ps1 -AppxRecipePath .\x64\Debug\xBindSampleCPP\xBindSampleCPP.build.appxrecipe -LayoutPath x64\Debug\xBindSampleCPP\AppX -Force
pushd x64\Debug\xBindSampleCPP\AppX 
Add-AppxPackage -Register AppxManifest.xml
popd

# cdbx64 -plmPackage Microsoft.SDKSamples.xBindSampleCPP.CPP_1.0.0.0_x64__8wekyb3d8bbwe -plmApp xBindSampleCPP.App
# explorer.exe shell:appsFolder\Microsoft.SDKSamples.xBindSampleCPP.CPP_8wekyb3d8bbwe!xBindSampleCPP.App
# start shell:appsFolder\Microsoft.SDKSamples.xBindSampleCPP.CPP_8wekyb3d8bbwe!xBindSampleCPP.App
# Start-Process shell:appsFolder\Microsoft.SDKSamples.xBindSampleCPP.CPP_8wekyb3d8bbwe!xBindSampleCPP.App
