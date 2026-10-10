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
    float imageScaleX = (float)rInput.GetScreenWidth() / 1280.0f;
    float imageScaleY = (float)rInput.GetScreenHeight() / 1024.0f;

    for (int i = 0; i < 6; ++i)
    {
        const int column = i % 3;
        const int row = i / 3;
        m_asprBack[i].Create(column == 2 ? 256 : 512, row == 0 ? 512 : 223,
            BITMAP_TITLE + i, 0, NULL, 0, 0, false,
            SPR_SIZING_DATUMS_LT, imageScaleX, imageScaleY);
        m_asprBack[i].SetPosition(column * 512, 119 + row * 512);
        m_asprBack[i].Show(true);
    }
    const int borderHeights[4] = { 69, 69, 100, 100 };
    for (int i = 0; i < 4; ++i)
    {
        m_asprBack[6 + i].Create(400, borderHeights[i], BITMAP_TITLE + 6 + i,
            0, NULL, 0, 0, false, SPR_SIZING_DATUMS_LT, fScaleX, fScaleY);
        m_asprBack[6 + i].SetPosition((i % 2) * 400, i < 2 ? 0 : 500);
        m_asprBack[6 + i].Show(true);
    }
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
        const wchar_t* pieces[LDS_BACK_MAX] = {
            L"Interface\\S8IntroA01.jpg", L"Interface\\S8IntroA02.jpg",
            L"Interface\\S8IntroA03.jpg", L"Interface\\S8IntroA04.jpg",
            L"Interface\\S8IntroA05.jpg", L"Interface\\S8IntroA06.jpg",
            L"Interface\\New_lo_back_01.jpg", L"Interface\\New_lo_back_02.jpg",
            L"Interface\\lo_back_s5_03.jpg", L"Interface\\lo_back_s5_04.jpg"
        };
        for (int i = 0; i < LDS_BACK_MAX; ++i)
            LoadBitmap(pieces[i], BITMAP_TITLE + i, GL_LINEAR);

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
    for (int i = 0; i < LDS_BACK_MAX; ++i)
        ::DeleteBitmap(BITMAP_TITLE + i);

    ::ClearInput();

    g_ConsoleDebug->Write(MCD_NORMAL, L"LoadingScene_End");
}
