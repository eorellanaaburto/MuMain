$D = "C:\Users\Usuario\Downloads"
$P = Join-Path $D "MU_S8_HUD_S15_CONCEPTO_V1"
$Html = Join-Path $P "VISTA_PREVIA_HUD_S8.html"
if (-not (Test-Path -LiteralPath $Html)) { throw "No se encuentra: $Html" }
Start-Process -FilePath $Html
Write-Host "Vista previa abierta. NO se ha modificado el cliente de MU." -ForegroundColor Green
