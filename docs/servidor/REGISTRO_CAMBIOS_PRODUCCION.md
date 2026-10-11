# Registro de cambios para producción (CT 122)

Lista de todo lo que se ha tocado para Blood Storm, Swell Life, maestrías y Adniel.
Sirve para decidir qué pasa a producción y en qué orden. Nada de esta lista se ha
aplicado a producción nuevamente salvo lo marcado como **ya aplicado**.

Regla: cada cambio a producción requiere autorización explícita con texto exacto.

## A. Servidor (CT 122)

| # | Cambio | Dónde está | Estado en producción | Requiere |
| :-- | :-- | :-- | :-- | :-- |
| S1 | Blood Storm (344) y Strengthener (346) como área alrededor del objetivo (`SkillType = 4`) | `UPDATE config."Skill"` | **Ya aplicado** (autorizado, reinicio hecho) | Nada más |
| S2 | Swell Life AG (maestría 363): código | `docs/servidor/parches/produccion_cambios_servidor.patch` (archivos `Stats.cs`, `CharacterClassInitialization.cs`, `LifeSwellEffectInitializer.cs`, `SkillList.cs`) | Pendiente | Imagen nueva + reinicio |
| S3 | Swell Life AG: filas en la base | `docs/servidor/parches/swell_life_ability_staging.sql` | Pendiente | Autorización SQL + reinicio. El `INSERT` del atributo falla si ya existe: revisar antes |
| S4 | Índice de maestrías (174 entradas nuevas + 344, 346, 363; Duel 489 corregido a 55; Fist 325 quitado) | `produccion_cambios_servidor.patch` (`GameServer/RemoteView/MasterSkillExtensions.cs`) | Pendiente | Imagen nueva + reinicio. No requiere SQL |
| S5 | Pentagrama: estado de Adniel con 21 bytes (`OpenNpcWindowPlugIn.cs`) | `produccion_cambios_servidor.patch` (`GameServer/RemoteView/NPC/OpenNpcWindowPlugIn.cs`) | Pendiente | Imagen nueva + reinicio. Requiere el cliente con el parser de 21 bytes (commit `fe63b004`) |

Notas:
- S2 y S4 vienen en el mismo parche consolidado, aplicado sobre el código que produjo la
  imagen de producción (`/root/fix-npc41`, verificado por identificadores de la DLL).
- S2 y S4 y S5 ya están en `produccion_cambios_servidor.patch` (6 archivos). Imagen de staging: `staging-full-20261011`.
- S2 cambia el comportamiento de Swell Life de 356 y 360: dejan de dar bono pasivo
  permanente y solo aplican con el buff. Confirmar en juego antes de pasar a producción.

## B. Cliente (repositorio `MuMain`, rama `codex/ct124-acheron-npcs`)

| # | Commit | Qué hace | Producción |
| :-- | :-- | :-- | :-- |
| C1 | `f5f8f0db` | Casteo y animación de maestrías, IDs de rango | Ya en la versión de producción del cliente |
| C2 | `c5f04e84`, `8c4817e1`, `8914ab4b`, `d6efea66` | Estado de Adniel, menú de Adniel, crafting por `/ecraft` | Pendiente de publicar en `Mu-S8 v3` |
| C3 | `fe63b004` | Tooltip de bonos de Errtel en el pentagrama | Requiere S5 en el servidor |
| C4 | `233ea2bf` | Blood Storm envía golpes de área (`AreaSkillHit`) | Requiere S1 (ya aplicado). Ya funciona en staging |
| C5 | `a0fe2ab0` | Script del enfriamiento de Blood Storm | Ver B1 |
| B1 | (archivo de datos, `src/bin/Data/Local/Eng/skill_eng.bmd`, ignorado por `.gitignore`) | Blood Storm 10000 → 5000 ms, Strengthener 10000 → 3000 ms | Pendiente. Reemplazar `Data\Local\Eng\skill_eng.bmd` en el cliente de producción |

Nota: el cliente de producción (`Mu-S8 v3`) no tiene ninguno de estos cambios de
C2 en adelante. Cuando se publique, habrá que distribuir el cliente nuevo a los jugadores.

## C. Solo staging (NO pasar a producción)

- Contenedor CT 123 `mu-staging` (IP 192.168.1.225), con su base y su configuración de conexión.
- Cambio de dirección pública en la base de staging (`IpResolverParameter` = 192.168.1.225,
  `AlternativePublishedPort` = 0). Producción conserva su propia dirección.
- Contraseñas de la base de staging en `/root/stg.env` de CT 123. No publicar.
- Cliente de prueba `C:\Users\Meinmundy\Downloads\Mu-STAGING` (lanzador `MU-STAGING.bat`).
- Imágenes de prueba `ag-test-20261010`, `ag-index-20261010`, `ag-index2-20261010`, `staging-full-20261011` (la actual).
- Ajuste de `ARG BUILDPLATFORM` en el Dockerfile de la copia de build (solo entorno de build).
- Plugins copiados a staging (los mismos que producción, desde las mismas rutas de CT 122).
- Respaldos del cliente de prueba: `Mu-STAGING\_backup_skill_eng_original.bmd`.

## D. Pendiente de decisión antes de producción

1. **Impactos de Blood Storm:** la base tiene 1 golpe por ataque. La referencia dice que el
   original pega dos veces. No cambiado. Decidir con prueba en juego.
2. **Combo:** Blood Storm no está en ningún paso de combo en la base. Si el original la
   usa como tercer golpe, es un cambio de base. No cambiado.
3. **Daño del Strengthener:** la base tiene 25 (la semilla dice 22). Su bono de maestría
   tiene la misma fórmula que Rageful Blow Strengthener. Confirmar en juego que el bono
   sube el daño con los puntos.
4. ~~Índice Duel 489~~ Corregido en staging a 55 (cliente).
5. ~~Fist 325~~ Quitado en staging (no existe en el árbol de Fist).
6. **Advertencias `Unknown plugin type`:** 150 en staging, 450 en producción. Mismo
   comportamiento; revisar si son configuraciones de plugins que ya no existen.
7. **Excepciones en el historial de producción:** 34 líneas en `mu-openmu`. No revisadas.

## E. Orden sugerido para producción (cuando se autorice cada paso)

1. Confirmar en staging: AG de Swell Life, árbol de maestrías, enfriamiento, daño.
2. Respaldo de la base de producción (`pg_dump`) y de la imagen actual.
3. S3: SQL de AG (con la revisión del `INSERT` existente).
4. S2 + S4: construir imagen desde `produccion_cambios_servidor.patch` y reiniciar.
5. S5 (pentagrama) va en el mismo parche que S2 y S4 (paso 4).
6. B1: reemplazar `skill_eng.bmd` en `Mu-S8 v3` y avisar a los jugadores.
7. Verificar: árbol de maestrías, Blood Storm, Swell Life, Adniel, 6 personajes.

## F. Herramientas y evidencia

- Verificación del checksum de `skill_eng.bmd`: `docs/cliente/parches/blood_storm_cooldown.js`.
- Tabla de maestrías: `docs/maestrias/tabla_maestrias.csv`.
- README del entorno de prueba: `docs/servidor/mu-staging-ct123/README.md`.
- Parches de servidor: `docs/servidor/parches/`.
