# Detect architecture
$arch = if ([Environment]::Is64BitOperatingSystem) { "x64" } else { "x86" }

$url = "https://github.com/yohanesokta/octa_core_utils/releases/download/1.0/$arch-release-windows.zip"
$zip = "$env:TEMP\octacore-$arch.zip"
$installDir = "$env:APPDATA\octacore"

if (!(Test-Path $installDir)) {
    New-Item -ItemType Directory -Path $installDir | Out-Null
}

Invoke-WebRequest $url -OutFile $zip
Expand-Archive $zip -DestinationPath $installDir -Force
Write-Host "Installed to $installDir"

$userPath = [Environment]::GetEnvironmentVariable("PATH", "User")

if ($userPath -notlike "*$installDir*") {
    [Environment]::SetEnvironmentVariable(
        "PATH",
        "$userPath;$installDir",
        "User"
    )
}

if (!(Test-Path $PROFILE)) {
    New-Item -ItemType File -Path $PROFILE -Force | Out-Null
}

$profileContent = Get-Content $PROFILE -Raw -ErrorAction SilentlyContinue

$marker = "# OCTACORE TOOLS"

if ($profileContent -notmatch "OCTACORE TOOLS") {

$script = @"

# OCTACORE TOOLS
`$tools = @("cat","clear","cp","df","du","env","ls","mv","notify","open","pwd","rm","rmdir","sleep","sptest","stat","touch","tree","which","whoami","yes")

foreach (`$t in `$tools) {
    if (Get-Alias `$t -ErrorAction SilentlyContinue) {
        Remove-Item "alias:`$t" -ErrorAction SilentlyContinue
    }
}

"@

Add-Content $PROFILE $script
}

Write-Host "PowerShell profile updated at $PROFILE. Please restart your terminal to apply changes."