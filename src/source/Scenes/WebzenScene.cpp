///////////////////////////////////////////////////////////////////////////////
// WebzenScene.cpp - Webzen title/intro scene implementation
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WebzenScene.h"
#include "SceneCore.h"
#include "Core/Platform/ScopedSystemCursor.h"
#include "Render/Textures/ZzzOpenglUtil.h"
#include "Render/Textures/ZzzTexture.h"
#include "Engine/Object/ZzzInterface.h"
#include "Engine/Object/ZzzOpenData.h"
#include "UI/Legacy/UIMng.h"
#include "UI/NewUI/NewUISystem.h"

// External declarations
extern EGameScene SceneFlag;
extern CErrorReport g_ErrorReport;

constexpr int TITLE_BITMAP_PATTERN = BITMAP_TITLE + 5;
static void LoadTitleBitmaps()
{
    LoadBitmap(L"Interface\\New_lo_back_01.jpg", BITMAP_TITLE, GL_LINEAR);
    LoadBitmap(L"Interface\\New_lo_back_02.jpg", BITMAP_TITLE + 1, GL_LINEAR);
    LoadBitmap(L"Interface\\lo_lo.jpg", BITMAP_TITLE + 5, GL_LINEAR, GL_REPEAT);
    LoadBitmap(L"Interface\\lo_back_s5_03.jpg", BITMAP_TITLE + 6, GL_LINEAR);
    LoadBitmap(L"Interface\\lo_back_s5_04.jpg", BITMAP_TITLE + 7, GL_LINEAR);
    const wchar_t* pieces[6] = {
        L"Interface\\S8IntroA01.jpg", L"Interface\\S8IntroA02.jpg",
        L"Interface\\S8IntroA03.jpg", L"Interface\\S8IntroA04.jpg",
        L"Interface\\S8IntroA05.jpg", L"Interface\\S8IntroA06.jpg"
    };
    for (int i = 0; i < 6; ++i)
        LoadBitmap(pieces[i], BITMAP_TITLE + 8 + i, GL_LINEAR);
}

/**
 * @brief Unloads all title scene bitmaps.
 */
static void UnloadTitleBitmaps()
{
    DeleteBitmap(BITMAP_TITLE);
    DeleteBitmap(BITMAP_TITLE + 1);
    DeleteBitmap(TITLE_BITMAP_PATTERN);
    DeleteBitmap(BITMAP_TITLE + 6);
    DeleteBitmap(BITMAP_TITLE + 7);
    for (int i = 0; i < 6; ++i)
        DeleteBitmap(BITMAP_TITLE + 8 + i);
}

/**
 * @brief Webzen title/intro scene - displays loading screen and transitions to login.
 * @param hDC Device context for rendering
 */
void WebzenScene(HDC hDC)
{
    CUIMng& rUIMng = CUIMng::Instance();

    if (!OpenFont())
    {
        return;
    }
    ClearInput();

    LoadTitleBitmaps();

    rUIMng.CreateTitleSceneUI();

    FogEnable = false;

    ::EnableAlphaTest();
    {
        // The game draws no cursor while it loads.
        const Core::Platform::ScopedSystemCursor cursor;
        OpenBasicData(hDC);
        g_pNewUISystem->LoadMainSceneInterface();
        CUIMng::Instance().RenderTitleSceneUI(hDC, 11, 11);
    }

    rUIMng.ReleaseTitleSceneUI();
    UnloadTitleBitmaps();

    g_ErrorReport.Write(L"> Loading ok.\r\n");

    SceneFlag = LOG_IN_SCENE;
}
