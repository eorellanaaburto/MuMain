# MU Online Season 8 - Historial de desarrollo

Proyecto cliente oficial utilizado para el servidor MU Online Season 8.

## Copia maestra

/srv/mu-client/MuMain

## Historial de cambios


## 2026-10-07 17:07:32

Equipo: EDMUNDO-INFORMA
Usuario: Usuario
Accion: sincronizacion completa hacia servidor maestro

Main.exe:
Tamaño: 21210624 bytes
SHA256: 8ACBAB5F2F6ACB101FEFFBD0968FA2C5F12DD2B8739BD4783F476BE0368EAC59

---

## 2026-10-10

Equipo: EDMUNDO-INFORMA
Usuario: Usuario
Accion: respaldo de Main.exe compilado hacia LXC 122 (proxmox-laposada), para continuar desde casa

Main.exe:
Tamaño: 21219840 bytes
SHA256: 6D88B14145DEACBA74A90E3B940BAE1D278457817AE2612C431A60A3AD3E5DD8
Copia guardada en: /root/mu-client-backups/Main-client-20261010.exe (dentro del LXC 122)

IMPORTANTE: el árbol de código fuente (src/source/*) sigue con TODOS los cambios de esta sesión
y sesiones anteriores SIN COMMITEAR a git (rama codex/ct124-acheron-npcs: 65 archivos modificados,
~7000 líneas, más 38 archivos nuevos sin agregar). Ver el informe RESUMEN_SESION_20261010.md en
el servidor para el detalle completo de qué archivos cambiaron y por qué. NO se hizo ningún commit
de git todavía — solo se respaldó el binario YA COMPILADO (este Main.exe). Si se pierde el árbol
de trabajo actual sin comitear antes, se pierde el código fuente de todos estos cambios.

---

