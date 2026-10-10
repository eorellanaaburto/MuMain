#include "App/stdafx.h"

#include <doctest.h>

#include "GameLogic/Items/InventoryUtils.h"

TEST_CASE("pentagram slot is separate from personal shop and inventory [ui][items]")
{
    CHECK(IsMainInventorySlot(12));
    CHECK(IsMainInventorySlot(75));
    CHECK(IsInventoryExtensionSlot(76));
    CHECK(IsInventoryExtensionSlot(203));
    CHECK(IsMyShopSlot(204));
    CHECK(IsMyShopSlot(235));
    CHECK_FALSE(IsMyShopSlot(236));
    CHECK(IsPentagramSlot(236));
    CHECK_FALSE(IsPentagramSlot(235));
    CHECK_FALSE(IsPentagramSlot(237));
}
