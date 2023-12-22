# Get process PID and stop it
$id = (ps | findstr "pendrive" | ForEach-Object{($_ -split "\s+")[6]} | Measure-Object -Sum | Select-Object -ExpandProperty Sum)
Stop-Process -Id $id