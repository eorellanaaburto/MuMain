#include "App/stdafx.h"

#include <array>
#include <doctest.h>

#include "UI/NewUI/Inventory/NewUIItemMng.h"

TEST_CASE("extended item packet preserves the guardian option [ui][items]")
{
    std::array<BYTE, 5> itemData{ 0x50, 0x0C, 10, 131, ItemOptionFlags::HasGuardian };

    const auto item = ParseItemData(itemData);

    CHECK(item.Group == 5);
    CHECK(item.Number == 12);
    CHECK(item.HasGuardianOption);

    itemData[4] = ItemOptionFlags::None;
    CHECK_FALSE(ParseItemData(itemData).HasGuardianOption);
}
