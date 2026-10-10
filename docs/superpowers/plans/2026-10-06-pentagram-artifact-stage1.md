# Pentagram Artifact Stage 1 Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Render and move an equipped Season 8 Pentagram in server slot 236 without altering the twelve classic equipment slots or the production Main.exe.

**Architecture:** Treat 236 as a special slot before any inventory/MyShop range dispatch. Keep its `ITEM` in `CNewUIMyInventory` outside `CharacterMachine->Equipment`; reuse the existing item parser, renderer, tooltip, and move request. Add a small Artifact panel to the inventory UI. The five Errtel sockets remain stage 2 after live verification.

**Tech Stack:** C++20, CMake/Ninja, MSVC Windows x64; existing OpenMU Native AOT network DLL.

**Spec:** User-provided `Texto pegado.txt` and the additional instruction to consult `MuMain_Pentagram_Artifact_SRC_PATCH.zip` conceptually.

## Global Constraints

- Preserve the current six-character client, Data/Items, SixthBalloon, login, loading, trade, and other accumulated fixes.
- Do not enlarge `MAX_EQUIPMENT_INDEX` or `CharacterMachine->Equipment`.
- Do not replace the production Main.exe with SHA256 `BE84B264D860F622DDE818ABDF69BC2F318E0E8F7CD9E27EA87D74FD3AA1BF6E`.
- Back up each modified existing file and produce `Main_Pentagram_Test.exe` separately.
- Treat the experimental ZIP only as a reference, never copy its files wholesale.

## Review Focus

- Slot 236 collides with an overly broad MyShop range check; dispatch must test the special slot first.
- Classic slots 0-11 and inventory 12-203 must retain behavior.
- The personal shop is only 8×4 slots (204-235), despite `MAX_SHOP_INVENTORY` being 8×15 for other shops.
- Failed moves must restore the picked item; the server response is authoritative.
- The panel must fit and remain usable at supported resolutions without per-frame logging.

### Task 1: Slot classification and item data

**Files:** `src/source/Core/Globals/_define.h`, `src/source/GameLogic/Items/InventoryUtils.h`, `src/source/Data/GameData/ItemData/ItemDefinition.h`, `src/source/Data/GameData/ItemData/ItemEnumNames.cpp`, `src/bin/Data/Items/Group12_Wing.json`, and a focused test.

- [ ] Add a failing classification test: 235 is MyShop, 236 is Pentagram, 237 is neither; classic boundaries remain unchanged.
- [ ] Add `PENTAGRAM_SERVER_SLOT`, `IsPentagramSlot`, and narrow personal-shop classification to its actual 32 cells.
- [ ] Append `ItemSlot::Pentagram = 236` without changing existing enum values; map `"pentagram"` in enum names and mark items 12/200-214.
- [ ] Run focused tests and JSON validation.

### Task 2: Receive and store the special item

**Files:** `src/source/Network/Server/WSclient.cpp`, `src/source/UI/NewUI/Inventory/NewUIMyInventory.h/.cpp`.

- [ ] Add focused tests for packet routing where feasible; prove the pre-change behavior fails.
- [ ] Route inventory list, move result, modify, delete and drop events for 236 before generic ranges.
- [ ] Store the decoded `ITEM` separately, preserving options and sockets, and clear it on inventory reset/character change.
- [ ] Log only item state transitions with `[PENTAGRAM-CLIENT]`.

### Task 3: Artifact panel and movement

**Files:** `src/source/UI/NewUI/Inventory/NewUIMyInventory.h/.cpp`, `src/source/UI/NewUI/Inventory/NewUIInventoryActionController.cpp`.

- [ ] Use the existing item renderer and tooltip in a compact panel beside inventory.
- [ ] Reuse `SendRequestEquipmentItem` for inventory→236 and 236→inventory, including rollback of failed moves.
- [ ] Keep classic equipment, extension, trade, and MyShop paths unchanged outside the 236 distinction.
- [ ] Verify with focused tests and source review.

### Task 4: Build and deliver test executable

**Files:** test executable output and build report only.

- [ ] Build the same Windows x64 Release configuration that produced the current Main.exe.
- [ ] Run focused and relevant regression tests; inspect errors and warnings.
- [ ] Copy only the new executable as `Main_Pentagram_Test.exe`; report path, size, SHA256 and modification date.
- [ ] Confirm the production Main.exe retains its original SHA256.

