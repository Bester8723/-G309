/*************************************************************************//*!

					@file	SceneTitle.cpp
					@brief	タイトル画面。

															@author	池上　綾香
*//**************************************************************************/
#include "SceneTitle.h"

/// <summary>
/// コンストラクタ
/// </summary>
CSceneTitle::CSceneTitle() : 
CSceneBase(),
m_BackTex(),
m_TitleLogo(),
m_StartButton() {
}

/// <summary>
/// デストラクタ
/// </summary>
CSceneTitle::~CSceneTitle() {
}

/// <summary>
/// 読み込み
/// </summary>
/// <returns>成功：true, 失敗：false</returns>
bool CSceneTitle::Load() {
	if (!m_BackTex.Load("Texture/Title/title_BackGround.png"))	{ return FALSE; }
	if (!m_TitleLogo.Load("Texture/Title/Logo_Title.png"))		{ return FALSE; }
	if (!m_StartButton.Load("Texture/Title/Btn_GameStart.png")) { return FALSE; }
	return TRUE;
}

/// <summary>
/// 初期化
/// </summary>
void CSceneTitle::Initialize() {
	InitializeBase();
}

/// <summary>
/// 更新
/// </summary>
void CSceneTitle::Update() {
	UpdateBase();
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		SetNextScene(SCENENO_MODESELECT);
	}
}

/// <summary>
/// 描画
/// </summary>
void CSceneTitle::Render(void) {
	m_BackTex.Render(0, 0);
	Vector2 halfPos(g_pGraphics->GetTargetWidth() * 0.5f, g_pGraphics->GetTargetHeight() * 0.5f);
	m_TitleLogo.Render(halfPos.x, halfPos.y * 0.5f, TEXALIGN_CENTERCENTER);
	m_StartButton.Render(halfPos.x, halfPos.y * 1.5f, TEXALIGN_CENTERCENTER);
	RenderBase();
}

/// <summary>
/// デバッグ描画
/// </summary>
void CSceneTitle::RenderDebug(void) {
	CGraphicsUtilities::RenderString(10, 10, "タイトル画面");
}

/// <summary>
/// 解放
/// </summary>
void CSceneTitle::Release(void) {
	m_BackTex.Release();
	m_TitleLogo.Release();
	m_StartButton.Release();
}