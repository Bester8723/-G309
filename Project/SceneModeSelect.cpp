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
m_StoryBgTex(),
m_EndlessBgTex(),
m_StoryOnButton(),
m_StoryOffButton(),
m_EndlessOnButton(),
m_EndlessOffButton(),
m_ModeSelectNo(0) {
}

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
}

/// <summary>
/// 更新
/// </summary>
void CSceneModeSelect::Update() {
	UpdateBase();

	if (g_pInput->IsKeyPush(MOFKEY_UP))
	{

	}
}

/// <summary>
/// 描画
/// </summary>
void CSceneModeSelect::Render(void) {

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