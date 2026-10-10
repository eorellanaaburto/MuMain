$ErrorActionPreference = 'Stop'
$Html = Join-Path $PSScriptRoot 'VISTA_PREVIA_V7.html'
if (!(Test-Path -LiteralPath $Html)) { throw "No se encontro $Html" }
Start-Process -FilePath $Html
