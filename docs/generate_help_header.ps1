$txtFile = "ochelp.txt"
$headerFile = "ochelp_data.h"

if (Test-Path $txtFile) {
    $content = Get-Content $txtFile -Raw
    # Escape backslashes and quotes
    $content = $content.Replace('\', '\\').Replace('"', '\"').Replace("`r", "")
    
    # Split by lines and format as C string literals
    $lines = $content.Split("`n")
    $cString = "const char *help_text = `n"
    foreach ($line in $lines) {
        $cString += "    `"$($line)\n`"`n"
    }
    $cString += "    ;"

    $headerContent = @"
/* Automatically generated from $txtFile */
#ifndef O_HELP_DATA_H
#define O_HELP_DATA_H

$cString

#endif
"@
    Set-Content -Path $headerFile -Value $headerContent
    Write-Host "Generated $headerFile from $txtFile"
} else {
    Write-Error "$txtFile not found!"
}
