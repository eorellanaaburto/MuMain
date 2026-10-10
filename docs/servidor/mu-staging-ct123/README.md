# MU Staging — CT 123 (`mu-staging`)

Entorno de prueba aislado del servidor MU de producción (CT 122). Sirve para
probar cambios antes de tocar producción.

## Datos del contenedor

| Campo | Valor |
| :--- | :--- |
| ID Proxmox | 123 |
| Nombre | `mu-staging` |
| IP LAN | 192.168.1.225 |
| Sistema | Ubuntu 24.04 (plantilla local), Docker 29 |
| Recursos | 4 vCPU, 8 GB RAM, disco 60 GB |
| Imagen del servidor | `mu-openmu-local:adniel-status-20261010` (igual a producción) |
| Base de datos | contenedor `mu-pg-staging`, base `openmu`, red Docker `mu-net` |

Contenedores que deben estar corriendo:
- `mu-pg-staging` (PostgreSQL)
- `mu-openmu-staging` (servidor de juego, puertos 44405/44406, 55901–55906, 28945, 55980 y 8080)

## Origen de la copia

- La base es una copia en vivo de la base de producción (`pg_dump` de solo lectura
  desde CT 122, con datos de jugadores). Hay 11 cuentas y 41 personajes.
- La imagen del servidor es la misma que corre producción.
- CT 122 no se modifica desde este trabajo. Solo se leen datos y se exportan imágenes.

**Único cambio respecto a producción:**
- `config.SystemConfiguration.IpResolverParameter`: `192.168.1.220` → `192.168.1.225`.
- `config.GameServerEndpoint.AlternativePublishedPort`: `28945` → `0`.

Sin este cambio, el cliente de staging es redirigido a la dirección pública de producción.

## Cliente de prueba

- Carpeta: `C:\Users\Meinmundy\Downloads\Mu-STAGING`.
- Lanzador: `MU-STAGING.bat`, que ejecuta `Main.exe connect /u192.168.1.225 /p44405`.
- Conexión directa, sin túnel. Se entra con la misma cuenta de producción.

## Plugins

Se copian dentro del contenedor `/app` desde las rutas de build de CT 122:

- `MuNpcInteractionPlugIn.dll` (Adniel)
- `ElementalCraftingPlugIn.dll`
- `PentagramNativePlugIn.dll`
- `WelcomeMessagePlugIn.dll`
- `SirLesnarPlugIn.dll`
- `ArkaWarPlugIn.dll`
- `S8MasterSkillCompatibilityPlugIn.dll`
- `/app/plugins/MonsterWingsChaosMixPlugIn.dll`

## Credenciales

Las credenciales de la base de este contenedor se generaron para él y se guardan en
`/root/stg.env` dentro de CT 123, con permisos 600. No se publican en el repositorio
ni en la documentación.

## Trabajo pendiente

1. **Swell Life AG (maestría 363).** Compilar el parche
   `docs/servidor/parches/swell_life_ability_mastery.patch` sobre el código fuente
   que produjo la imagen de producción. No usar `/opt/openmu-arrow-fix`: sus DLL no
   son compatibles con esta imagen. Guardar las DLL en `/root/ag_dll/` de CT 123.
2. **SQL de AG.** Aplicar `docs/servidor/parches/swell_life_ability_staging.sql` en
   la base de CT 123. La copia de producción no tiene las filas de AG.
3. **Pruebas en juego** (cuenta `meinmundy`):
   - Hablar con Adniel (ventana 41) y revisar el estado del pentagrama.
   - Crear el sexto personaje (límite 6).
   - AG de Swell Life con 0, 1, 10 y 20 puntos, con el buff activo y expirado.
   - Verificar que Blood Storm siga haciendo daño en área.
4. **Pasar a producción** solo después de las pruebas, y con autorización explícita
   con texto exacto.

## Notas

- El mensaje `Error loading shared library libgssapi_krb5.so.2` aparece en cada
  arranque y no afecta al servidor.
- Los contenedores CT 123 `mu-lab` y CT 124 `mu-season8` fueron borrados por orden
  del usuario, sin respaldo. Su contenido no se recupera.
- Restos del respaldo en `/tmp` del host Proxmox no se pudieron borrar por permisos.
  No afectan al servicio.

## Reglas de trabajo

- No modificar CT 122 desde este entorno.
- Todo cambio de código o SQL se publica en GitHub, en la rama `codex/ct124-acheron-npcs`.
- Cualquier cambio en producción requiere autorización explícita con texto exacto.
