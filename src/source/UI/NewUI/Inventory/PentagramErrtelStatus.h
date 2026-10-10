#pragma once

#include <cstdint>

inline constexpr int kErrtelSlotCount = 5;

inline const wchar_t* const PentagramErrtelSlotNames[kErrtelSlotCount] =
{
    L"Anger", L"Blessing", L"Integrity", L"Divinity", L"Gale"
};

struct PentagramErrtelSlotStatus
{
    std::uint8_t Rank = 0;
    std::uint8_t Level = 0;
    std::uint8_t OptionNumber = 0;
};

struct PentagramErrtelStatus
{
    bool Equipped = false;
    bool OptionsKnown = false;
    std::uint8_t PentagramLevel = 0;
    PentagramErrtelSlotStatus Slots[kErrtelSlotCount];
};

inline PentagramErrtelStatus g_PentagramErrtelStatus;
