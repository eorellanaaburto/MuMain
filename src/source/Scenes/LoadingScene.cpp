//*****************************************************************************
// File: LoadingScene.cpp
//*****************************************************************************

#include "stdafx.h"

#include "LoadingScene.h"

#include "Core/Input/Input.h"
#include "UI/Legacy/UIMng.h"
#include "Render/Renderer/MuRenderer.h"
#include "Render/Textures/ZzzOpenglUtil.h"
#include "Render/Textures/ZzzTexture.h"
#include "SceneCore.h"
#include "Engine/Object/ZzzInterface.h"
#include "SceneCommon.h"
#include "UI/NewUI/Dialogs/ReconnectDialog.h"


#ifdef _EDITOR
#include "Core/MuEditorCore.h"
#endif

CLoadingScene::CLoadingScene()
{
}

CLoadingScene::~CLoadingScene()
{
}

void CLoadingScene::Create()
{
    CInput rInput = CInput::Instance();
    float fScaleX = (float)rInput.GetScreenWidth() / 800.0f;
    float fScaleY = (float)rInput.GetScreenHeight() / 600.0f;

    int anHeight[LDS_BACK_MAX] = { 512, 512, 88, 88 };
    for (int i = 0; i < LDS_BACK_MAX; ++i)
    {
        m_asprBack[i].Create(400, anHeight[i], BITMAP_TITLE + i, 0, NULL, 0, 0, false,
            SPR_SIZING_DATUMS_LT, fScaleX, fScaleY);
        m_asprBack[i].Show(true);
    }

    m_asprBack[1].SetPosition(400, 0, X);
    m_asprBack[2].SetPosition(0, 512, Y);
    m_asprBack[3].SetPosition(400, 512);
}

void CLoadingScene::Release()
{
    for (int i = 0; i < LDS_BACK_MAX; ++i)
        m_asprBack[i].Release();
}

void CLoadingScene::Render()
{
    for (int i = 0; i < LDS_BACK_MAX; ++i)
    {
        m_asprBack[i].Render();
    }
}

// External variables
extern int LoadingWorld;
extern bool FogEnable;
extern EGameScene SceneFlag;

void LoadingScene(HDC hDC)
{
    g_ConsoleDebug->Write(MCD_NORMAL, L"LoadingScene_Start");

    CUIMng& rUIMng = CUIMng::Instance();
    if (!InitLoading)
    {
        LoadingWorld = 9999999;

        InitLoading = true;
        // Alternate the supplied Season 8 artwork each time a world loads.
        static unsigned int artwork = 0;
        const bool secondArtwork = (artwork++ % 2) != 0;
        const wchar_t* pieces[2][4] = {
            {L"Interface\\S8LoadA01.jpg", L"Interface\\S8LoadA02.jpg",
             L"Interface\\S8LoadA03.jpg", L"Interface\\S8LoadA04.jpg"},
            {L"Interface\\S8LoadB01.jpg", L"Interface\\S8LoadB02.jpg",
             L"Interface\\S8LoadB03.jpg", L"Interface\\S8LoadB04.jpg"}
        };
        for (int i = 0; i < 4; ++i)
            LoadBitmap(pieces[secondArtwork ? 1 : 0][i], BITMAP_TITLE + i, GL_LINEAR);

        ::StopMp3(MUSIC_LOGIN_THEME);

        rUIMng.m_pLoadingScene = new CLoadingScene;
        rUIMng.m_pLoadingScene->Create();
    }

    FogEnable = false;
    ::BeginOpengl();
    mu::GetRenderer().ClearScreen();
    ::BeginBitmap();

    rUIMng.m_pLoadingScene->Render();

    ::EndBitmap();
    ::EndOpengl();
#ifdef _EDITOR
    // Always render ImGui (shows "Open Editor" button when closed, or full UI when open)
    g_MuEditorCore.Render();

    // Render game cursor on top of ImGui if not hovering UI
    extern bool g_bRenderGameCursor;
    if (g_bRenderGameCursor)
    {
        BeginBitmap();
        RenderCursor();
        EndBitmap();
    }
#endif
    UI::Reconnect::RenderDialog();

    SAFE_DELETE(rUIMng.m_pLoadingScene);

    SceneFlag = MAIN_SCENE;
    for (int i = 0; i < 4; ++i)
        ::DeleteBitmap(BITMAP_TITLE + i);

    ::ClearInput();

    g_ConsoleDebug->Write(MCD_NORMAL, L"LoadingScene_End");
}
