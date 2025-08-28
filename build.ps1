# $buildEXE = "C:\Program Files\Microsoft Visual Studio\2022\Community\Msbuild\Current\Bin\amd64\MSBuild.exe"
$buildEXE = "C:\Program Files\Microsoft Visual Studio\2022\Community\Msbuild\Current\Bin\amd64\MSBuild.exe"

try {
    Start-Process -FilePath "$buildEXE" -ArgumentList "opengl-experiments.sln","/t:Build","/p:Configuration=Debug" -ErrorAction Stop -Wait -ErrorVariable err -NoNewWindow -RedirectStandardOutput "build.log"
} catch {
    Write-Output $err
    exit
}

$successString = Get-ChildItem "build.log" | Select-String -Pattern "0 Error\(s\)"
$errorString = Get-ChildItem "build.log" | Select-String -Pattern "\d+ Error"

if ($successString.Length -eq 0 -and $errorString.Length -gt 0) {
    Get-Content "build.log"
    exit
}

echo "Success!"

Start-Sleep -Seconds 1

.\x64\Debug\"opengl-experiments.exe"

