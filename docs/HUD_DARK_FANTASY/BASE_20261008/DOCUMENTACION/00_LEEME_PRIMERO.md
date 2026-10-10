# HUD DARK FANTASY FINAL — PAQUETE B, BASE DE IMPLEMENTACIÓN

**Estado del paquete:** especificación completa, artes de referencia y scripts de preparación/compilación/instalación segura.

**NO es un HUD nuevo 100 % implementado en MU.** Las imágenes son conceptos compuestos que tienen píxeles del escenario y textos ilustrativos. NO deben renombrarse a OZJ/OZD ni instalarse en `Data/Interface`.

## Qué contiene

- `REFERENCIAS/`: las dos imágenes Dark Fantasy elegidas y ocho recortes para guiar la recreación de texturas y componentes.
- `DOCUMENTACION/`: inventario de componentes, archivos y mapa de implementación.
- `SCRIPTS/01_PREPARAR_Y_RESPALDAR.ps1`: crea un respaldo acotado del cliente de pruebas y del código actual; guarda el arte en `MuMain/docs/HUD_DARK_FANTASY`.
- `SCRIPTS/02_INSTALAR_RECURSOS_FINALES.ps1`: instalador con validación, **solo cuando** el manifiesto de recursos definitivos tenga archivos de juego compatibles y hashes reales.
- `SCRIPTS/03_COMPILAR_RELEASE_PRUEBA.ps1`: recompila el código fuente ACTUAL e instala el ejecutable en `Mu-S8 COMPILADO PRUEBA`, con respaldo.
- `SCRIPTS/04_REVERTIR.ps1`: restaura archivos desde un respaldo explícito creado por 01, 02 o 03.
- `SCRIPTS/05_ESTADO.ps1`: comprueba si existen las rutas y muestra SHA-256.
- `PRODUCCION/`: contrato de entrega y manifiesto vacío; **faltan los atlas gráficos finales y cambios completos de C++**.

## Rutas usadas

- Código: `C:\Users\Usuario\Documents\Codex\2026-09-30\et\work\MuMain`
- Cliente de pruebas: `C:\Users\Usuario\Downloads\Mu-S8 COMPILADO PRUEBA`
- Cliente funcional: `C:\Users\Usuario\Downloads\Mu-S8 V2` (**nunca se sobrescribe**).

## Primera acción segura

Abrir PowerShell en Descargas, expandir ZIP y ejecutar `SCRIPTS/01_PREPARAR_Y_RESPALDAR.ps1`.

La siguiente tarea de desarrollo es crear texturas funcionales **específicas para la geometría de cada sprite** y un parche C++ revisado contra el estado actual de `MuMain`. No es seguro interpolar el código faltante ni fingir que la maqueta de imagen es un paquete funcional.
