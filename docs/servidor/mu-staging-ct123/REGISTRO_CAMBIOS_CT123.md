# Registro de cambios en CT 123 (mu-staging)

Fecha de este registro: 2026-10-11 (noche). Entorno: staging aislado, IP 192.168.1.225.
Producción (CT 122) NO se ha tocado en esta sesión de cambios de CT 123.

## 1. Estado actual del servidor de staging
- Contenedor `mu-openmu-staging`, imagen `mu-openmu-local:illusion-temple-final-20261009`
  (la imagen de ayer, con código de Crywolf). Listener activo.
- Contenedor `mu-pg-staging` (PostgreSQL), base `openmu`.
- Plugins copiados a `/app` desde las rutas de producción (MuNpcInteraction, ElementalCrafting,
  PentagramNative, WelcomeMessage, SirLesnar, ArkaWar, MonsterWingsChaosMix en `/app/plugins/`,
  S8MasterSkillCompatibility).
- Config de conexión: `/root/stg_conn/ConnectionSettings.xml` (copiado al contenedor).
- Credenciales de la base: `/root/stg.env` (permisos 600). No publicar.

## 2. Historial de cambios en la base de staging (orden cronológico)
1. Copia de la base de producción en vivo (`pg_dump` de solo lectura de CT 122), restaurada en
   `mu-pg-staging` a las 23:07 UTC. Se cambiaron solo:
   - `config.SystemConfiguration.IpResolverParameter`: 192.168.1.220 -> 192.168.1.225
   - `config.GameServerEndpoint.AlternativePublishedPort`: 28945 -> 0
   Respaldo de ese estado: `/root/stg_transfer3/prod-live.dump` (CT 123).
   IMPORTANTE: esa copia es ANTERIOR al SQL de Swell Life AG aplicado en producción a las 00:50 UTC.
   Por eso la base de staging NO tiene las filas de AG. Para probar AG en staging hay que reaplicar
   `docs/servidor/parches/swell_life_ability_staging.sql` (repo MuMain).
2. Items de prueba agregados al personaje `Meinmundy` (cuenta `meinmundy`), inventario ItemStorage
   `7365a001-0000-7cb7-2f31-9cf2b506c6bd`, casillas 41-64: 6 Mithril Fragment (12/144), 6 Elixir
   Fragment (12/146), 5 Jewel of Chaos (12/15), 5 Jewel of Bless (14/13), 2 Jewel of Soul (14/14).
   No tienen elemento (no son Mithril 12/145 ni Elixir 12/147 creados).
3. Configuración del plugin de Crywolf (fila `PlugInConfiguration` TypeId
   `a1b2c3d4-e5f6-4789-ab12-cd34ef560001`, Id `2170ec6a-cb9b-4ee0-80b2-1801b800706c`):
   JSON cambiado de formato Newtonsoft (`$id`, `$values`) a JSON simple. Original en
   `/root/bak-ct123/cw_config_original.json`.
4. Maestrías de la Elfa (clase 11, High Elf), corrección de bono (ver sección 4).
   Respaldo de la base antes de este cambio: `/root/bak-ct123-antes-elfa-20261011/openmu-antes.dump`
   y valores antes en `valores_antes.txt` (misma carpeta).

## 3. Cambios de código (imágenes)
- Ninguno en esta sesión. La imagen actual es la de ayer (illusion-temple-final-20261009).
- Imágenes de prueba anteriores (ya no corren): `ag-test-20261010`, `ag-index-20261010`,
  `ag-index2-20261010`, `staging-full-20261011` (esta última es la que se copió a producción
  el 2026-10-11 00:48 UTC, con el parche consolidado del repo).

## 4. Corrección de maestrías de la Elfa (aplicada en staging)
Causa (verificada en código): `AttackableExtensions.cs:185` hace `dmg += (int)Attributes[GreaterDamageBonus]`
y `:94` igual con `GreaterDefenseBonus`. El buff aporta el valor base por `AddRaw`, y la maestría
usa `Multiplicate` con `(...)*5/100` = 0.05..0.44. Como `Multiplicate` multiplica directamente, el
bono queda multiplicado por 0.05 en vez de por 1.05.
Cambio: `ValueFormula` de la maestría = `1 + (` + fórmula anterior + `)`. Agregación sin cambio (Multiplicate).

| Skill | Nombre | Antes | Después |
| :-- | :-- | :-- | :-- |
| 417 | Defense Increase Str | `(0.8 + ...) * 5 / 100` | `1 + ((0.8 + ...) * 5 / 100)` |
| 420 | Attack Increase Str | idem | idem |
| 422 | Attack Increase Mastery | idem | idem |
| 423 | Defense Increase Mastery | idem | idem |

Requiere reinicio del servidor (ya hecho a las 02:30 UTC). Probar en juego: con buff de Elfa,
el bono de daño y defensa debe subir con el nivel de la maestría, no bajar.

## 5. Otros puntos del documento de pendientes (PENDIENTES.md de CT 122) - estado en staging
- 2.1 Maestrías Elfa: APLICADO en staging (sección 4).
- 2.2 Infinity Arrow Str (441): NO aplicado. El atributo `Attack Damage Increase Multiplier` (const
  base 1, 18 filas) NO tiene consumidor en el código con ese nombre (no se encontró referencia).
  Antes de tocarlo hay que confirmar qué atributo lee el daño de Infinity Arrow.
- 2.3 Twisting Slash Mastery (332): NO aplicado. El `/ 100` duplicado NO está en la base: la fórmula
  actual tiene un solo `/ 100` y el valor de nivel 1 es 1.2%. Afirmación del documento refutada
  para esta base (el `/ 100` extra lo añade un plugin solo al crear la base).
- 2.4 Beast Uppercut Mastery (555): NO aplicado. Signo negativo confirmado (valor -0.012..-0.09,
  agregación Multiplicate sobre Defense Decrement). La corrección depende de decisión de diseño.
- 2.5 Expansion of Wizardry Str (380): NO aplicado. No verificado (el atributo `Maximum Wizardry
  Base Damage` no aparece en el código con ese nombre).
- 2.6 Unidades de tasas (AttackSuccRateInc, MaximumSDincrease, PvPDefenceRateInc): pendiente de
  confirmación de diseño.

## 6. Crywolf (pendiente, sin resolver)
- Producción (CT 122): fila de plugin de Crywolf ACTIVA en la base, pero la imagen activa de
  producción NO tiene el código de Crywolf (`crywolf-20260929ah` ya no existe). Por eso no arranca.
- Staging (CT 123): la imagen de ayer SÍ tiene el código (56 referencias en GameLogic), y el
  comando `/startcw` existe en su GameLogic.dll.
- Problema actual en staging: al arrancar aparece `JsonException` en `$.Mobs.$values[0].$id`
  (3 excepciones), aunque la fila de la base ya tiene JSON simple. Hay otra fuente con el formato
  antiguo que aún no se identificó (posible copia en la configuración del juego o un archivo de
  configuración de la imagen). Pendiente de investigar.
- Pendiente de prueba del usuario: `/startcw` en Mu-STAGING.

## 7. Pendientes para el siguiente paso
1. Identificar la fuente del JSON viejo de Crywolf y corregirla (solo en staging).
2. Probar `/startcw` y el bono de la Elfa en juego.
3. Reaplicar el SQL de Swell Life AG en staging para probar AG (la base es anterior a esa SQL).
4. Decidir 2.2, 2.4 y 2.5 con respaldo de la base antes de tocar.
5. Cualquier cambio a producción requiere autorización explícita con texto exacto.

## 8. Reglas
- No modificar CT 122 desde CT 123.
- Cada cambio de base en staging: respaldo previo (`pg_dump`) en `/root/bak-ct123-*`.
- Publicar el registro y los parches en GitHub (rama codex/ct124-acheron-npcs).

## 9. Correcciones aplicadas después (2026-10-11 02:40 UTC) — estado final de la lista del PENDIENTES.md
Respaldo de la base antes de este bloque: `/root/bak-ct123-antes-441-380-555/openmu-antes.dump` (valores antes en `valores_antes.txt`).

| Skill | Nombre | Antes | Después | Motivo verificado en código |
| :-- | :-- | :-- | :-- | :-- |
| 441 | Infinity Arrow Str | agregación 1 (Multiplicate), fórmula `(1+X)/100` | agregación 0 (AddRaw), misma fórmula | El atributo `AttackDamageIncrease` ("Attack Damage Increase Multiplier") se usa como `dmg = dmg * AttackDamageIncrease` (AttackableExtensions.cs:220). Con Multiplicate el multiplicador quedaba en ~0.012. Con AddRaw queda en 1.012..1.09. |
| 380 | Expansion of Wiz Streng | `(1+X) * 0.01`, Multiplicate | `1 + (1+X) * 0.01`, Multiplicate | `MaximumWizBaseDmg` se usa en el daño mágico (AttackableExtensions.cs:845). Con Multiplicate sin base, el valor era ~0.012. Ahora es 1.012..1.09 sobre el daño base. La otra maestría que lo escribe (407) es AddRaw y no cambia. |
| 555 | Beast Uppercut Mastery | `-1 * (1+X) * 0.01`, Multiplicate | `1 - (1+X) * 0.01`, Multiplicate | `DefenseDecrement` se usa como `defense * DefenseDecrement` (AttackableExtensions.cs:94). El valor negativo volvía negativa la defensa del objetivo. Ahora reduce la defensa 1.2%..9% extra (se combina con el 0.9 de Beast Uppercut). Decisión de diseño tomada: reducción adicional, no penalización. |
| 332 | Twisting Slash Mastery | sin cambio | sin cambio | Verificado: la base tiene un solo `/ 100` y nivel 1 = 1.2% (correcto). El `/ 100` extra del documento no está en la base. |

Estado de la lista del PENDIENTES.md (CT 122):
- 2.1 Elfa (417, 420, 422, 423): APLICADO en staging (sección 4).
- 2.2 Infinity Arrow (441): APLICADO en staging (sección 9).
- 2.3 Twisting Slash Mastery (332): NO requiere cambio (verificado).
- 2.4 Beast Uppercut Mastery (555): APLICADO en staging (sección 9), con decisión de diseño indicada.
- 2.5 Expansion of Wizardry Str (380): APLICADO en staging (sección 9).
- 2.6 Unidades de tasas: sin cambio (pendiente de confirmación de diseño).

Pendiente de probar en juego: el daño de Elfa, Infinity Arrow, Expansion of Wizardry y la defensa reducida de Beast Uppercut.
El servidor de staging reinició a las 02:40 UTC: listener activo. Las 3 excepciones que siguen son las de la configuración JSON de Crywolf (sección 6), no de estos cambios.
Ningún cambio se aplicó a producción.
