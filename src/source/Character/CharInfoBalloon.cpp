//*****************************************************************************
// File: CharInfoBalloon.cpp
//*****************************************************************************

#include "stdafx.h"
#include "CharInfoBalloon.h"
#include "Render/Textures/ZzzOpenglUtil.h"
#include "Engine/Object/ZzzInterface.h"
#include "UI/Legacy/UIControls.h"
#include "CharacterManager.h"
#include "I18N/All.h"

#include <algorithm>
#include <array>
#include <cwchar>

#include "Camera/CameraProjection.h"

namespace
{
    template <std::size_t N>
    void CopyWideString(wchar_t (&destination)[N], const wchar_t* source)
    {
        if (source == nullptr)
        {
            destination[0] = L'\0';
            return;
        }

        std::wcsncpy(destination, source, N - 1);
        destination[N - 1] = L'\0';
    }

    struct GuildStatusText
    {
        std::uint8_t status;
        int textIndex;
    };

    constexpr std::array<GuildStatusText, 5> kGuildStatusTexts{ {
        {   0, 1330 },
        {  32, 1302 },
        {  64, 1301 },
        { 128, 1300 },
        { 255, 488 },
    } };

    DWORD ResolveNameColor(std::uint8_t controlCode)
    {
        if (controlCode & CTLCODE_01BLOCKCHAR)
            return ARGB(255, 0, 255, 255);
        if (controlCode & (CTLCODE_02BLOCKITEM | CTLCODE_10ACCOUNT_BLOCKITEM))
            return CLRDW_BR_ORANGE;
        if (controlCode & CTLCODE_04FORTV)
            return CLRDW_WHITE;
        if (controlCode & (CTLCODE_08OPERATOR | CTLCODE_20OPERATOR))
            return ARGB(255, 255, 0, 0);

        return CLRDW_WHITE;
    }

    int ResolveGuildTextIndex(std::uint8_t guildStatus)
    {
        const auto it = std::lower_bound(
            kGuildStatusTexts.begin(),
            kGuildStatusTexts.end(),
            guildStatus,
            [](const GuildStatusText& entry, std::uint8_t status) { return entry.status < status; });

        return (it != kGuildStatusTexts.end() && it->status == guildStatus) ? it->textIndex : 0;
    }
}

CCharInfoBalloon::CCharInfoBalloon() : m_pCharInfo(nullptr)
{
    I18N::RegisterLocaleObserver(&CCharInfoBalloon::OnLocaleChanged, this);
}

CCharInfoBalloon::~CCharInfoBalloon()
{
    I18N::UnregisterLocaleObserver(&CCharInfoBalloon::OnLocaleChanged, this);
}

void CCharInfoBalloon::OnLocaleChanged(void* ctx) noexcept
{
    auto* self = static_cast<CCharInfoBalloon*>(ctx);
    if (self->m_pCharInfo != nullptr)
    {
        self->SetInfo();
    }
}

void CCharInfoBalloon::Create(CHARACTER* pCharInfo)
{
    CSprite::Create(118, 54, BITMAP_LOG_IN + 7, 0, nullptr, 59, 54);

    m_pCharInfo = pCharInfo;
    m_dwNameColor = 0;
    std::fill(std::begin(m_szName), std::end(m_szName), L'\0');
    std::fill(std::begin(m_szGuild), std::end(m_szGuild), L'\0');
    std::fill(std::begin(m_szClass), std::end(m_szClass), L'\0');
}

void CCharInfoBalloon::Render()
{
    const bool isSixthCharacter = m_pCharInfo == &CharactersClient[5];
    static bool sixthBalloonLogged = false;
    if (isSixthCharacter && !sixthBalloonLogged)
    {
        g_ErrorReport.Write(L"[SixthBalloon] created=%d live=%d show=%d name=%ls\r\n",
            m_pCharInfo != nullptr, m_pCharInfo->Object.Live, CSprite::m_bShow, m_pCharInfo->ID);
        sixthBalloonLogged = true;
    }
    if (m_pCharInfo == nullptr)
        return;

    // Character data can arrive before the sixth balloon is initialized.
    // Refresh a hidden balloon when its character becomes available.
    if (!CSprite::m_bShow && m_pCharInfo->Object.Live)
        SetInfo();
    if (!CSprite::m_bShow)
        return;

    vec3_t afPos;
    VectorCopy(m_pCharInfo->Object.Position, afPos);
    afPos[2] += 350.0f;

    int nPosX, nPosY;
    CameraProjection::WorldToScreen(g_Camera, afPos, &nPosX, &nPosY);

    // Keep the entire balloon visible, including the sixth character's label.
    const int spriteW = CSprite::GetWidth();
    const int spriteH = CSprite::GetHeight();
    const int halfWidth = spriteW / 2;
    CSprite::SetPosition(
        std::clamp(int(nPosX * g_fScreenRate_x), halfWidth, std::max(halfWidth, int(WindowWidth) - halfWidth)),
        std::clamp(int(nPosY * g_fScreenRate_y), 0, std::max(0, int(WindowHeight) - spriteH))
    );
    if (isSixthCharacter && sixthBalloonLogged)
    {
        static bool sixthPositionLogged = false;
        if (!sixthPositionLogged)
        {
            g_ErrorReport.Write(L"[SixthBalloon] projection=%d,%d sprite=%d,%d size=%d,%d window=%u,%u\r\n",
                nPosX, nPosY, CSprite::GetXPos(), CSprite::GetYPos(), spriteW, spriteH,
                WindowWidth, WindowHeight);
            sixthPositionLogged = true;
        }
    }
    CSprite::Render();

    g_pRenderText->SetFont(g_hFixFont);
    g_pRenderText->SetBgColor(0);

    const int spriteX = CSprite::GetXPos();
    const int spriteY = CSprite::GetYPos();
    // The bitmap is 118 pixels wide. Give the text renderer the width of its
    // visible interior so long class names are scaled to fit the frame.
    const int nTextPosX = int((spriteX + 5) / g_fScreenRate_x);
    const int textWidth = int((spriteW - 10) / g_fScreenRate_x);

    g_pRenderText->SetTextColor(m_dwNameColor);
    g_pRenderText->RenderText(
        nTextPosX,
        int((spriteY + 6) / g_fScreenRate_y),
        m_szName,
        textWidth,
        0,
        RT3_SORT_CENTER
    );

    g_pRenderText->SetTextColor(CLRDW_WHITE);
    g_pRenderText->RenderText(
        nTextPosX,
        int((spriteY + 22) / g_fScreenRate_y),
        m_szGuild,
        textWidth,
        0,
        RT3_SORT_CENTER
    );

    g_pRenderText->SetTextColor(CLRDW_BR_ORANGE);
    g_pRenderText->RenderText(
        nTextPosX,
        int((spriteY + 38) / g_fScreenRate_y),
        m_szClass,
        textWidth,
        0,
        RT3_SORT_CENTER
    );
}

void CCharInfoBalloon::SetInfo()
{
    if (m_pCharInfo == nullptr)
        return;

    if (!m_pCharInfo->Object.Live)
    {
        CSprite::m_bShow = false;
        return;
    }

    CSprite::m_bShow = true;

    m_dwNameColor = ResolveNameColor(m_pCharInfo->CtlCode);

    CopyWideString(m_szName, m_pCharInfo->ID);

    const int guildTextIndex = ResolveGuildTextIndex(m_pCharInfo->GuildStatus);
    mu_swprintf_s(m_szGuild, L"(%ls)", I18N::Game::Lookup(guildTextIndex));
    mu_swprintf_s(m_szClass, L"%ls %d",
        gCharacterManager.GetCharacterClassText(m_pCharInfo->Class),
        m_pCharInfo->Level);
}
