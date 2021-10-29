/*************************************************************************//*!

					@file	SceneModeSelect.cpp
					@brief	ステージセレクト画面。

															@author	池上　綾香
*//**************************************************************************/
#include "SceneModeSelect.h"

/// <summary>
/// コンストラクタ
/// </summary>
CSceneModeSelect::CSceneModeSelect() : 
CSceneBase(),
m_StoryBgTex(),
m_EndlessBgTex(),
m_StoryOnButton(),
m_StoryOffButton(),
m_EndlessOnButton(),
m_EndlessOffButton(),
m_NowModeNo(0),
m_NextModeNo(0),
m_bChangeMode(false),
m_BgAlpha(0.0f) 
{}

/// <summary>
/// デストラクタ
/// </summary>
CSceneModeSelect::~CSceneModeSelect() {
}

/// <summary>
/// 読み込み
/// </summary>
/// <returns>成功：true, 失敗：false</returns>
bool CSceneModeSelect::Load() {
	if (!m_StoryBgTex.Load("Texture/Select/Bg_StoryMode.png"))			{ return FALSE; }
	if (!m_EndlessBgTex.Load("Texture/Select/Bg_EndlessMode.png"))		{ return FALSE; }
	if (!m_StoryOnButton.Load("Texture/Select/Btn_StoryOn.png"))		{ return FALSE; }
	if (!m_StoryOffButton.Load("Texture/Select/Btn_StoryOff.png"))		{ return FALSE; }
	if (!m_EndlessOnButton.Load("Texture/Select/Btn_EndlessOn.png"))	{ return FALSE; }
	if (!m_EndlessOffButton.Load("Texture/Select/Btn_EndlessOff.png"))	{ return FALSE; }
	return TRUE;
}

/// <summary>
/// 初期化
/// </summary>
void CSceneModeSelect::Initialize() {
	InitializeBase();
	m_NowModeNo = MODENO_STORY;
	m_NextModeNo = MODENO_STORY;
	m_bChangeMode = false;
	m_BgAlpha = 0.0f;
}

/// <summary>
/// 更新
/// </summary>
void CSceneModeSelect::Update() {
	UpdateBase();

	//モード切替時、黒画面を挟む
	if (m_bChangeMode)
	{
		m_BgAlpha += 255 / 15.0f;
		if (m_BgAlpha > 255)
		{
			m_BgAlpha = 255;
			m_bChangeMode = false;
			m_NowModeNo = m_NextModeNo;
		}
	}
	else if (m_BgAlpha > 0 && !m_bChangeMode)
	{
		m_BgAlpha -= 255 / 15.0f;
		if (m_BgAlpha < 0) { m_BgAlpha = 0; }
	}

	//モード切替中は操作を受け付けない
	if (m_BgAlpha > 0)
	{
		return;
	}

	//上下キーでモード切替操作
	if (g_pInput->IsKeyPush(MOFKEY_UP))
	{
		m_NextModeNo = MOF_CLIPING(m_NowModeNo - 1, 0, MODENO_COUNT - 1);
		if (m_NextModeNo != m_NowModeNo){ m_bChangeMode = true; }
	}
	else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
	{
		m_NextModeNo = MOF_CLIPING(m_NowModeNo + 1, 0, MODENO_COUNT - 1);
		if (m_NextModeNo != m_NowModeNo) { m_bChangeMode = true; }
	}
	//Enterキーでゲームシーンへ遷移
	else if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		CGameModeManager::Instance().SetPlayMode(m_NowModeNo);
		SetNextScene(SCENENO_GAME);
	}
}

/// <summary>
/// 描画
/// </summary>
void CSceneModeSelect::Render(void) {
	switch (m_NowModeNo)
	{
	case MODENO_STORY:
		m_StoryBgTex.Render(0, 0);
		m_StoryOnButton.Render(100, 100);
		m_EndlessOffButton.Render(100, 200);
		break;
	case MODENO_ENDLESS:
		m_EndlessBgTex.Render(0, 0);
		m_StoryOffButton.Render(100, 100);
		m_EndlessOnButton.Render(100, 200);
		break;
	}
	//黒画面
	CGraphicsUtilities::RenderFillRect(GetWindowRect(), MOF_ALPHA_BLACK((int)m_BgAlpha));
	RenderBase();
}

/// <summary>
/// デバッグ描画
/// </summary>
void CSceneModeSelect::RenderDebug(void) {
	CGraphicsUtilities::RenderString(10, 10, "モード選択画面");
}

/// <summary>
/// 解放
/// </summary>
void CSceneModeSelect::Release(void) {
	m_StoryBgTex.Release();
	m_EndlessBgTex.Release();
	m_StoryOnButton.Release();
	m_StoryOffButton.Release();
	m_EndlessOnButton.Release();
	m_EndlessOffButton.Release();
}