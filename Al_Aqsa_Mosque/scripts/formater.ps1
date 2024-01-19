#https://www.red-gate.com/simple-talk/sysadmin/powershell/how-to-use-parameters-in-powershell/

param($ext = 'cpp', $tabWord = 'glPushMatrix();', $unTabWord = 'glPopMatrix();', $tab = "`t", [Parameter()][switch]$notFormated)

$directoryName = Get-Location; #or $PWD but #PSScriptRoot return the location of the script .. not the working directory

#TODO: be accurate when create tmpfile
#TODO: fix it :)
function format {
    param ($file)

    #Time O(n)
    #Space O(n)
    
    $noProblem = 1;
    $tabNum = 0;
    $tmpFile = "__";

    Copy-Item $file -Destination $tmpFile;
    Clear-Content $file

    Get-Content $tmpFile | ForEach-Object {
        $newLine = "";

        $tmpLine = $_;
        if ($notFormated.IsPresent) {
            $tmpLine = $_.Trim();
        }

        if ($tmpLine.Contains($unTabWord)) {
            # or ($tmpLine -like "*$unTapWord*") but -contains won't work
            $tabNum--;
        }
        $noProblem = $noProblem -and ($tabNum -ge 0);

        for ($i = 0; $i -lt $tabNum; $i++) {
            $newLine += $tab;
        }
        $newLine += $TmpLine;

        if ($tmpLine.Contains($tabWord)) {
            $tabNum++;
        }

        try {
            $newLine >> $file ;
        }
        catch {
            Write-Host "file $($file) is used by another process" -ForegroundColor Cyan;
            return 1;
        }
    }

    Remove-Item $tmpFile;

    $noProblem = $noProblem -and ($tabNum -eq 0);

    return $noProblem
}

# Write-Host $directoryName;
# Write-Host $PWD;
# Write-Host $PSScriptRoot;

# exit 0;

$files = Get-ChildItem $directoryName -Filter *.$ext;
$acFiles = 0;
$errFiles = 0;
# you can pipe 'Get-ChildItem' to ForEach-Object dirctly
Foreach ($file in $files) {
    if ((format($file))) {
        Write-Host "$($file) has no errors" -ForegroundColor green
        $acFiles++;
    }
    else {
        Write-Host "$($file) has unequal number of $($tabWord) and $($unTabWord) strings" -ForegroundColor Red;
        $errFiles++;
    }
}

Write-Host "$($acFiles + $errFiles) file(s) fixed. $($errFiles) with errors and $($acFiles) without!" -ForegroundColor Cyan;

exit 0;