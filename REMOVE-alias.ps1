$tools = @("cat","clear","cp","df","du","env","ls","mv","notify","open","pwd","rm","rmdir","sleep","sptest","stat","touch","tree","which","whoami","yes")

foreach ($t in $tools) {
    if (Test-Path $exe) {

        if (Get-Alias $t -ErrorAction SilentlyContinue) {
            Remove-Item "alias:$t" -ErrorAction SilentlyContinue
        }
    }
}