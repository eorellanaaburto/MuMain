#include "stdafx.h"
#include "GameLogic/Combat/BloodStormHits.h"
#include "Engine/Object/ZzzCharacter.h"
#include "Network/Server/WSclient.h"

namespace
{
constexpr float kBloodStormHitRadiusCells = 2.0f;
constexpr int kMaxBloodStormHitTargets = 30;

bool IsInBloodStormArea(const CHARACTER& candidate, const CHARACTER& center)
{
    const float radius = kBloodStormHitRadiusCells * TERRAIN_SCALE;
    const float dx = candidate.Object.Position[0] - center.Object.Position[0];
    const float dy = candidate.Object.Position[1] - center.Object.Position[1];
    return dx * dx + dy * dy <= radius * radius;
}
}

void SendBloodStormAreaHits(WORD networkSkillId, int explicitTargetIndex, BYTE animationCounter)
{
    if (explicitTargetIndex < 0 || explicitTargetIndex >= MAX_CHARACTERS_CLIENT)
    {
        return;
    }

    const CHARACTER& center = CharactersClient[explicitTargetIndex];
    uint16_t targetIds[kMaxBloodStormHitTargets];
    BYTE animationCounters[kMaxBloodStormHitTargets];
    int targetCount = 0;

    for (int i = 0; i < MAX_CHARACTERS_CLIENT && targetCount < kMaxBloodStormHitTargets; ++i)
    {
        const CHARACTER& candidate = CharactersClient[i];
        if (!candidate.Object.Live || !IsMonster(const_cast<CHARACTER*>(&candidate)))
        {
            continue;
        }

        if (!IsInBloodStormArea(candidate, center))
        {
            continue;
        }

        targetIds[targetCount] = static_cast<uint16_t>(candidate.Key);
        animationCounters[targetCount] = animationCounter;
        ++targetCount;
    }

    if (targetCount == 0)
    {
        return;
    }

    SocketClient->ToGameServer()->SendAreaSkillHit(networkSkillId,
                                                   static_cast<BYTE>(center.PositionX),
                                                   static_cast<BYTE>(center.PositionY),
                                                   animationCounter,
                                                   targetIds,
                                                   animationCounters,
                                                   static_cast<BYTE>(targetCount));
}
