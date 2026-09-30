# Arena S8: corrales de Stadium

Arena es el mapa 6 y el cliente carga su colisión desde
`src/bin/Data/World7/EncTerrain7.att`. La misma cuadrícula, en el formato del
servidor, está en `src/bin/Data/World7/Terrain.att`.

Esta configuración conserva los 36 registros de monstruos y sus 264 criaturas,
además de los tres NPC/objetos existentes (267 apariciones en total). Los doce
grupos de tres especies se ordenan por nivel en los corrales, de izquierda a
derecha y de arriba hacia abajo: 47–54, 57–62, 68–72, 78, 85–92, 93–95,
102, 111–112, 117, 126–128, 134–137 y 142–145. El corral oriental largo se
usa para dos grupos. Se abren doce casillas de colisión para poder llegar a
todos los recintos desde la entrada de Arena; las texturas y objetos 3D no se
modifican.

Para aplicar estos datos en OpenMU con PostgreSQL, ejecutar
`arena-apply.sql` en la base `openmu` y reiniciar solo el servicio del juego.
El script cambia únicamente el terreno del mapa 6 y las coordenadas de los
36 registros de monstruos identificados por UUID; conserva cantidades,
definiciones y los NPC. En cada instalación cliente, copiar los dos archivos
`.att` de `src/bin/Data/World7` a `Data/World7` con el juego cerrado.

El código fuente de esta rama todavía tiene lógica de cinco espacios en
`CharSelMainWin.cpp`. El ejecutable S8 de seis espacios que se distribuyó
separadamente no debe reemplazarse con una compilación de esta rama sin
integrar primero esa lógica y verificar la interfaz de maestría S8.
