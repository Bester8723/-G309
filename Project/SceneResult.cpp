/*************************************************************************//*!

					@file	SceneReselt.cpp
					@brief	リザルト画面。

															@author	池上　綾香
*//**************************************************************************/
#include "SceneResult.h"

/// <summary>
/// コンストラクタ
/// </summary>
CSceneResult::CSceneResult() :
m_GameEndNo(0),
m_BackTex(),
m_BoardTex() {
}

/// <summary>
/// デストラクタ
/// </summary>
CSceneResult::~CSceneResult() {
}

/// <summary>
/// 読み込み
/// </summary>
/// <returns>成功：true, 失敗：false</returns>
bool CSceneResult::Load() {
	CUtilities::SetCurrentDirectory("Resource\Texture\Result");
	if (!m_BoardTex.Load("result_titleText.png")) { return FALSE; }

	return TRUE;
}

/// <summary>
/// 初期化
/// </summary>
void CSceneResult::Initialize() {
	//共通部
	InitializeBase();
	//ゲーム終了番号を取得
	m_GameEndNo = CGameEndManager::Instance().GetGameEndCondition();
}

/// <summary>
/// 更新
/// </summary>
void CSceneResult::Update() {
	//共通部
	UpdateBase();

	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		CGameEndManager::Instance().SetGameEndCondition(GAMEENDNO_CONTINUE);
		SetNextScene(SCENENO_GAME);
	}
}

/// <summary>
/// 描画
/// </summary>
void CSceneResult::Render(void) {
	m_BoardTex.Render(0, 0);
	//共通部
	RenderBase();
}

/// <summary>
/// デバッグ描画
/// </summary>
void CSceneResult::RenderDebug(void) {
}

/// <summary>
/// 解放
/// </summary>
void CSceneResult::Release(void) {
	m_BoardTex.Release();
}