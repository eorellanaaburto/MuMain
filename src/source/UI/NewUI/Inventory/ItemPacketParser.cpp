#include "App/stdafx.h"

#include "UI/NewUI/Inventory/NewUIItemMng.h"

ItemCreationParams ParseItemData(std::span<const BYTE> itemData)
{
    ItemCreationParams params = {};

    if (itemData.size() < 5)
        return params;

    params.Group = (itemData[0] >> 4) & 0xF;
    params.Number = ((itemData[0] & 0xF) << 8) + itemData[1];
    params.Level = itemData[2];
    params.Durability = itemData[3];
    auto flags = static_cast<ItemOptionFlags>(itemData[4]);
    params.WithLuck = flags & ItemOptionFlags::HasLuck;
    params.WithSkill = flags & ItemOptionFlags::HasSkill;
    params.HasGuardianOption = flags & ItemOptionFlags::HasGuardian;

    int offset = 0;
    if (flags & ItemOptionFlags::HasOption)
    {
        params.OptionLevel = itemData[5] & 0xF;
        params.OptionType = (itemData[5] >> 4) & 0xF;
        offset++;
    }

    if (flags & ItemOptionFlags::HasExcellent)
    {
        params.ExcellentFlags = itemData[5 + offset];
        offset++;
    }

    if (flags & ItemOptionFlags::HasAncient)
    {
        params.AncientDiscriminator = itemData[5 + offset] & 0xF;
        params.AncientBonusOption = (itemData[5 + offset] >> 4) & 0xF;
        offset++;
    }

    if (flags & ItemOptionFlags::HasHarmony)
    {
        params.HasHarmonyOption = true;
        params.HarmonyOptionLevel = itemData[5 + offset] & 0xF;
        params.HarmonyOptionType = (itemData[5 + offset] >> 4) & 0xF;
        offset++;
    }

    if (flags & ItemOptionFlags::HasSockets)
    {
        params.SocketBonusOption = (itemData[5 + offset] >> 4) & 0xF;
        params.SocketCount = itemData[5 + offset] & 0xF;

        for (int i = 0; i < params.SocketCount; ++i)
        {
            params.SocketOptions[i] = itemData[6 + offset + i];
        }
    }

    return params;
}
