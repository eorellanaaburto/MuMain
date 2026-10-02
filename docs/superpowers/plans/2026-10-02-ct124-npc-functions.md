# CT124 NPC Functions Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Make the requested Season 8 NPCs perform their documented functions in the CT124 lab, then validate them in one joint in-game session.

**Architecture:** Retain the working six-character client and stable server image. Treat ordinary merchants as data/configuration repairs. Implement service, quest, and event NPCs as separate protocol and gameplay features, using the existing OpenMU plugin points where possible. Never substitute a generic merchant for a combination or event NPC.

**Tech Stack:** C++/SDL MuMain client, OpenMU .NET server plugins, PostgreSQL, Docker in Proxmox CT124.

**Spec:** `C:\Users\Usuario\Documents\Codex\2026-09-30\et\outputs\Auditoria-NPC-y-mapas-CT124-2026-10-02.md`.

## Global Constraints

- Modify CT124 only; leave CT122 production untouched.
- Use `C:\Users\Usuario\Downloads\Mu-S8-CT124-cliente-original-corregido\Mu-S8-CT124`, never the Season 6 client.
- Preserve the working six-character selection and text layout.
- Test NPCs together after the batch, as requested by the user.
- Keep Castle Siege event zones and Lost Tower 1–7 out of the M list; Balgass Refuge was explicitly excluded.

## Review Focus

1. NPC click produces a valid response, with the correct UI, on this client version.
2. Shop contents appear and purchase succeeds without inventory corruption.
3. Crafting consumes exactly the specified materials and handles failure correctly.
4. Event/quest NPCs enforce tickets, levels, guild state, and event phase.
5. Server and client agree on packet IDs and window codes; login and character selection still work.

## Task 1 — Shops and spawn configuration

- [x] Compare NPC rows, shop item counts, and spawn maps in CT124.
- [x] Correct Jin's original potions/ammunition shop and add Bolt/Arrows through +7.
- [x] Configure Arena Guard's potion shop.
- [x] Add Thompson the Merchant's missing Lorencia spawn.
- [ ] Verify every ordinary merchant listed in the spec opens a populated shop and can sell at least one item during the joint game test.
- [ ] Repair any client packet or UI fault revealed by `[NpcAudit]` lines in `MuError.log`, then rebuild and repeat the shop test.

## Task 2 — Existing special service NPCs

- [ ] Validate Raul's jewel packing/unpacking against the `NpcWindow=9` protocol and item transactions; repair only the failing layer.
- [ ] Validate Guard's Land of Trials authorization against Castle Siege guild ownership.
- [ ] Validate David's lucky-item exchange and Deruvish's quest state with their documented prerequisites.
- [ ] Add focused tests for each server-side rule and verify packets with the S8 client.

## Task 3 — Missing gameplay systems

- [ ] Implement Adniel's EX700 elemental crafting window and client/server protocol, with Mithril fragment refinement, Errtel creation, and level/rank upgrades following Webzen's original recipes. Test success and failure without losing unrelated items.
- [ ] Implement Mirage's Illusion Temple entry only after the minigame and ticket validation exist; do not expose an entry that strands players.
- [ ] Implement Sir Lesnar's Arka War registration only with the corresponding guild/event state; replace the current informational plugin after the event is functional.

## Task 4 — Combined verification

- [ ] Build client and server overlays without replacing the known-good six-slot GameLogic/GameServer packet assemblies.
- [ ] Check login, six-character selection, travel, NPC interactions, purchases, recipes, and event prerequisites in one in-game session.
- [ ] Record verified NPC functions and remaining limitations in the audit report, then revoke the temporary Proxmox SSH key.
