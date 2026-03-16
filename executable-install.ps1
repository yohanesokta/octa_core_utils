#  script to add : powershell -ExecutionPolicy Bypass -File install.ps1
$installDir = $PSScriptRoot
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

# OCTACORE TOOLS [v1.0]
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
& "$installDir\notify.exe" -i "OctaCore Tools Installed. Please restart your terminal to apply changes."