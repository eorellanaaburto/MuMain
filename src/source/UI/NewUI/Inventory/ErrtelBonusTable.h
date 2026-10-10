#pragma once

// Generado desde Persistence/Initialization/VersionSeasonSix/Items/Pentagrams.cs (CreateErrtel*Options).
// Un nivel por indice (0..10). Los valores fraccionarios se muestran como porcentaje.

inline constexpr int ErrtelBonusLevelCount = 11;

struct ErrtelBonusEntry
{
    short Number;
    const wchar_t* Label;
    bool Percent;
    float Values[ErrtelBonusLevelCount];
};

inline const ErrtelBonusEntry ErrtelBonusTable[] =
{
    { 0, L"Dano elemental", false, { 30.0f, 33.0f, 38.0f, 45.0f, 54.0f, 65.0f, 78.0f, 93.0f, 113.0f, 138.0f, 168.0f } },
    { 10, L"Dano elemental vs Fuego", true, { 0.05f, 0.06f, 0.07f, 0.08f, 0.09f, 0.1f, 0.12f, 0.14f, 0.16f, 0.18f, 0.2f } },
    { 11, L"Dano elemental vs Agua", true, { 0.05f, 0.06f, 0.07f, 0.08f, 0.09f, 0.1f, 0.12f, 0.14f, 0.16f, 0.18f, 0.2f } },
    { 12, L"Dano elemental vs Tierra", true, { 0.05f, 0.06f, 0.07f, 0.08f, 0.09f, 0.1f, 0.12f, 0.14f, 0.16f, 0.18f, 0.2f } },
    { 13, L"Dano elemental vs Viento", true, { 0.05f, 0.06f, 0.07f, 0.08f, 0.09f, 0.1f, 0.12f, 0.14f, 0.16f, 0.18f, 0.2f } },
    { 14, L"Dano elemental vs Oscuridad", true, { 0.05f, 0.06f, 0.07f, 0.08f, 0.09f, 0.1f, 0.12f, 0.14f, 0.16f, 0.18f, 0.2f } },
    { 20, L"Dano elemental PvP", false, { 30.0f, 35.0f, 43.0f, 54.0f, 66.0f, 80.0f, 97.0f, 117.0f, 142.0f, 172.0f, 207.0f } },
    { 21, L"Dano elemental PvM", false, { 30.0f, 35.0f, 43.0f, 54.0f, 66.0f, 80.0f, 97.0f, 117.0f, 142.0f, 172.0f, 207.0f } },
    { 30, L"Dano elemental a distancia", false, { 30.0f, 35.0f, 43.0f, 54.0f, 66.0f, 80.0f, 97.0f, 117.0f, 142.0f, 172.0f, 207.0f } },
    { 31, L"Dano elemental cuerpo a cuerpo", false, { 30.0f, 35.0f, 43.0f, 54.0f, 66.0f, 80.0f, 97.0f, 117.0f, 142.0f, 172.0f, 207.0f } },
    { 40, L"Prob. dano critico elemental PvP", true, { 0.05f, 0.06f, 0.07f, 0.08f, 0.09f, 0.1f, 0.12f, 0.14f, 0.16f, 0.18f, 0.2f } },
    { 41, L"Prob. dano critico elemental PvM", true, { 0.05f, 0.06f, 0.07f, 0.08f, 0.09f, 0.1f, 0.12f, 0.14f, 0.16f, 0.18f, 0.2f } },
    { 50, L"Defensa elemental", false, { 10.0f, 13.0f, 17.0f, 22.0f, 28.0f, 35.0f, 43.0f, 52.0f, 62.0f, 73.0f, 85.0f } },
    { 60, L"Defensa elemental vs Fuego", true, { 0.05f, 0.06f, 0.07f, 0.08f, 0.09f, 0.1f, 0.12f, 0.14f, 0.16f, 0.18f, 0.2f } },
    { 61, L"Defensa elemental vs Agua", true, { 0.05f, 0.06f, 0.07f, 0.08f, 0.09f, 0.1f, 0.12f, 0.14f, 0.16f, 0.18f, 0.2f } },
    { 62, L"Defensa elemental vs Tierra", true, { 0.05f, 0.06f, 0.07f, 0.08f, 0.09f, 0.1f, 0.12f, 0.14f, 0.16f, 0.18f, 0.2f } },
    { 63, L"Defensa elemental vs Viento", true, { 0.05f, 0.06f, 0.07f, 0.08f, 0.09f, 0.1f, 0.12f, 0.14f, 0.16f, 0.18f, 0.2f } },
    { 64, L"Defensa elemental vs Oscuridad", true, { 0.05f, 0.06f, 0.07f, 0.08f, 0.09f, 0.1f, 0.12f, 0.14f, 0.16f, 0.18f, 0.2f } },
    { 70, L"Defensa elemental PvP", false, { 10.0f, 13.0f, 17.0f, 22.0f, 28.0f, 35.0f, 43.0f, 52.0f, 62.0f, 73.0f, 85.0f } },
    { 71, L"Defensa elemental PvM", false, { 10.0f, 13.0f, 17.0f, 22.0f, 28.0f, 35.0f, 43.0f, 52.0f, 62.0f, 73.0f, 85.0f } },
    { 80, L"Defensa elemental a distancia", false, { 10.0f, 13.0f, 17.0f, 22.0f, 28.0f, 35.0f, 43.0f, 52.0f, 62.0f, 73.0f, 85.0f } },
    { 81, L"Defensa elemental cuerpo a cuerpo", false, { 10.0f, 13.0f, 17.0f, 22.0f, 28.0f, 35.0f, 43.0f, 52.0f, 62.0f, 73.0f, 85.0f } },
    { 90, L"Multiplicador dano elemental PvP", true, { 0.05f, 0.06f, 0.07f, 0.08f, 0.09f, 0.1f, 0.12f, 0.14f, 0.16f, 0.18f, 0.2f } },
    { 91, L"Multiplicador dano elemental PvM", true, { 0.05f, 0.06f, 0.07f, 0.08f, 0.09f, 0.1f, 0.12f, 0.14f, 0.16f, 0.18f, 0.2f } },
    { 100, L"Tasa de acierto elemental", true, { 0.05f, 0.06f, 0.07f, 0.08f, 0.09f, 0.1f, 0.12f, 0.14f, 0.16f, 0.18f, 0.2f } },
    { 110, L"Dano elemental vs Fuego", true, { 0.05f, 0.06f, 0.07f, 0.08f, 0.09f, 0.1f, 0.12f, 0.14f, 0.16f, 0.18f, 0.2f } },
    { 111, L"Dano elemental vs Agua", true, { 0.05f, 0.06f, 0.07f, 0.08f, 0.09f, 0.1f, 0.12f, 0.14f, 0.16f, 0.18f, 0.2f } },
    { 112, L"Dano elemental vs Tierra", true, { 0.05f, 0.06f, 0.07f, 0.08f, 0.09f, 0.1f, 0.12f, 0.14f, 0.16f, 0.18f, 0.2f } },
    { 113, L"Dano elemental vs Viento", true, { 0.05f, 0.06f, 0.07f, 0.08f, 0.09f, 0.1f, 0.12f, 0.14f, 0.16f, 0.18f, 0.2f } },
    { 114, L"Dano elemental vs Oscuridad", true, { 0.05f, 0.06f, 0.07f, 0.08f, 0.09f, 0.1f, 0.12f, 0.14f, 0.16f, 0.18f, 0.2f } },
    { 120, L"Dano elemental PvP", false, { 30.0f, 35.0f, 43.0f, 54.0f, 66.0f, 80.0f, 97.0f, 117.0f, 142.0f, 172.0f, 207.0f } },
    { 121, L"Dano elemental PvM", false, { 30.0f, 35.0f, 43.0f, 54.0f, 66.0f, 80.0f, 97.0f, 117.0f, 142.0f, 172.0f, 207.0f } },
    { 130, L"Dano elemental a distancia", false, { 30.0f, 35.0f, 43.0f, 54.0f, 66.0f, 80.0f, 97.0f, 117.0f, 142.0f, 172.0f, 207.0f } },
    { 131, L"Dano elemental cuerpo a cuerpo", false, { 30.0f, 35.0f, 43.0f, 54.0f, 66.0f, 80.0f, 97.0f, 117.0f, 142.0f, 172.0f, 207.0f } },
    { 140, L"Multiplicador dano elemental PvP", true, { 0.05f, 0.07f, 0.09f, 0.11f, 0.13f, 0.15f, 0.18f, 0.21f, 0.24f, 0.27f, 0.3f } },
    { 141, L"Multiplicador dano elemental PvM", true, { 0.05f, 0.07f, 0.09f, 0.11f, 0.13f, 0.15f, 0.18f, 0.21f, 0.24f, 0.27f, 0.3f } },
    { 150, L"Tasa de defensa elemental", true, { 0.05f, 0.06f, 0.07f, 0.08f, 0.09f, 0.1f, 0.12f, 0.14f, 0.16f, 0.18f, 0.2f } },
    { 160, L"Defensa elemental vs Fuego", true, { 0.05f, 0.06f, 0.07f, 0.08f, 0.09f, 0.1f, 0.12f, 0.14f, 0.16f, 0.18f, 0.2f } },
    { 161, L"Defensa elemental vs Agua", true, { 0.05f, 0.06f, 0.07f, 0.08f, 0.09f, 0.1f, 0.12f, 0.14f, 0.16f, 0.18f, 0.2f } },
    { 162, L"Defensa elemental vs Tierra", true, { 0.05f, 0.06f, 0.07f, 0.08f, 0.09f, 0.1f, 0.12f, 0.14f, 0.16f, 0.18f, 0.2f } },
    { 163, L"Defensa elemental vs Viento", true, { 0.05f, 0.06f, 0.07f, 0.08f, 0.09f, 0.1f, 0.12f, 0.14f, 0.16f, 0.18f, 0.2f } },
    { 164, L"Defensa elemental vs Oscuridad", true, { 0.05f, 0.06f, 0.07f, 0.08f, 0.09f, 0.1f, 0.12f, 0.14f, 0.16f, 0.18f, 0.2f } },
    { 170, L"Defensa elemental PvP", false, { 10.0f, 13.0f, 17.0f, 22.0f, 28.0f, 35.0f, 43.0f, 52.0f, 62.0f, 73.0f, 85.0f } },
    { 171, L"Defensa elemental PvM", false, { 10.0f, 13.0f, 17.0f, 22.0f, 28.0f, 35.0f, 43.0f, 52.0f, 62.0f, 73.0f, 85.0f } },
    { 180, L"Defensa elemental a distancia", false, { 10.0f, 13.0f, 17.0f, 22.0f, 28.0f, 35.0f, 43.0f, 52.0f, 62.0f, 73.0f, 85.0f } },
    { 181, L"Defensa elemental cuerpo a cuerpo", false, { 10.0f, 13.0f, 17.0f, 22.0f, 28.0f, 35.0f, 43.0f, 52.0f, 62.0f, 73.0f, 85.0f } },
    { 190, L"Reduccion dano elemental PvP", true, { 0.05f, 0.07f, 0.09f, 0.11f, 0.13f, 0.15f, 0.18f, 0.21f, 0.24f, 0.27f, 0.3f } },
    { 191, L"Reduccion dano elemental PvM", true, { 0.05f, 0.07f, 0.09f, 0.11f, 0.13f, 0.15f, 0.18f, 0.21f, 0.24f, 0.27f, 0.3f } },
    { 200, L"Prob. ralentizar elemental", true, { 0.01f, 0.02f, 0.03f, 0.04f, 0.05f, 0.06f, 0.07f, 0.08f, 0.1f, 0.12f, 0.15f } },
    { 210, L"Fuerza", false, { 10.0f, 15.0f, 20.0f, 25.0f, 30.0f, 35.0f, 40.0f, 45.0f, 50.0f, 55.0f, 60.0f } },
    { 211, L"Agilidad", false, { 10.0f, 15.0f, 20.0f, 25.0f, 30.0f, 35.0f, 40.0f, 45.0f, 50.0f, 55.0f, 60.0f } },
    { 212, L"Energia", false, { 10.0f, 15.0f, 20.0f, 25.0f, 30.0f, 35.0f, 40.0f, 45.0f, 50.0f, 55.0f, 60.0f } },
    { 213, L"Vitalidad", false, { 10.0f, 15.0f, 20.0f, 25.0f, 30.0f, 35.0f, 40.0f, 45.0f, 50.0f, 55.0f, 60.0f } },
    { 220, L"Vida maxima", false, { 20.0f, 25.0f, 30.0f, 35.0f, 40.0f, 50.0f, 60.0f, 70.0f, 80.0f, 90.0f, 100.0f } },
    { 221, L"Mana maximo", false, { 20.0f, 25.0f, 30.0f, 35.0f, 40.0f, 50.0f, 60.0f, 70.0f, 80.0f, 90.0f, 100.0f } },
    { 222, L"AG maxima", false, { 20.0f, 25.0f, 30.0f, 35.0f, 40.0f, 50.0f, 60.0f, 70.0f, 80.0f, 90.0f, 100.0f } },
    { 223, L"SD maximo", false, { 500.0f, 550.0f, 600.0f, 650.0f, 700.0f, 750.0f, 800.0f, 850.0f, 900.0f, 950.0f, 1000.0f } },
    { 230, L"Prob. dano excelente elemental PvP", true, { 0.05f, 0.06f, 0.07f, 0.08f, 0.09f, 0.1f, 0.12f, 0.14f, 0.16f, 0.18f, 0.2f } },
    { 231, L"Prob. dano excelente elemental PvM", true, { 0.05f, 0.06f, 0.07f, 0.08f, 0.09f, 0.1f, 0.12f, 0.14f, 0.16f, 0.18f, 0.2f } },
    { 240, L"Prob. debuff elemental", true, { 0.01f, 0.01f, 0.01f, 0.01f, 0.01f, 0.01f, 0.01f, 0.01f, 0.01f, 0.01f, 0.01f } },
};

inline const ErrtelBonusEntry* FindErrtelBonus(short number)
{
    for (const ErrtelBonusEntry& entry : ErrtelBonusTable)
    {
        if (entry.Number == number)
        {
            return &entry;
        }
    }

    return nullptr;
}
