#include "stdafx.h"
#include "UI/NewUI/Inventory/PentagramTooltip.h"
#include "Engine/Object/ZzzInventory.h"
#include "UI/NewUI/Inventory/ErrtelBonusTable.h"
#include "UI/NewUI/Inventory/PentagramErrtelStatus.h"

namespace UI::Items::Tooltip
{
namespace
{
constexpr int kTooltipRowCount = 50;
constexpr int kSeparatorRows = 1;
constexpr int kHeaderRows = 1;

bool HasRoomForRows(int textNum, int rows)
{
    return textNum + rows <= kTooltipRowCount;
}

int AppendSlotBonus(int textNum, int slotIndex)
{
    const PentagramErrtelSlotStatus& slot = g_PentagramErrtelStatus.Slots[slotIndex];
    if (slot.Rank == 0 || !HasRoomForRows(textNum, 1))
    {
        return textNum;
    }

    const ErrtelBonusEntry* entry = FindErrtelBonus(static_cast<short>(slot.OptionNumber));
    if (entry == nullptr)
    {
        return textNum;
    }

    const int levelIndex = slot.Level < ErrtelBonusLevelCount ? slot.Level : ErrtelBonusLevelCount - 1;
    const float value = entry->Values[levelIndex];
    if (entry->Percent)
    {
        mu_swprintf(TextList[textNum], L"%ls: %ls +%.0f%%", PentagramErrtelSlotNames[slotIndex], entry->Label, value * 100.0f);
    }
    else
    {
        mu_swprintf(TextList[textNum], L"%ls: %ls +%.0f", PentagramErrtelSlotNames[slotIndex], entry->Label, value);
    }

    TextListColor[textNum] = TEXT_COLOR_GREEN;
    return textNum + 1;
}
}

int AppendPentagramErrtelBonus(int textNum)
{
    const PentagramErrtelStatus& status = g_PentagramErrtelStatus;
    if (!status.Equipped || !status.OptionsKnown)
    {
        return textNum;
    }

    if (!HasRoomForRows(textNum, kSeparatorRows + kHeaderRows))
    {
        return textNum;
    }

    mu_swprintf(TextList[textNum], L"\n");
    ++textNum;

    mu_swprintf(TextList[textNum], L"Bono Errtel (Pentagrama +%d)", static_cast<int>(status.PentagramLevel));
    TextListColor[textNum] = TEXT_COLOR_BLUE;
    ++textNum;

    for (int slotIndex = 0; slotIndex < kErrtelSlotCount; ++slotIndex)
    {
        textNum = AppendSlotBonus(textNum, slotIndex);
    }

    return textNum;
}
}
