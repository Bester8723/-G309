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
CSceneBase(),
m_GameEndNo(0),
m_BackTex(),
m_BoardTex(),
m_ResultTex() {
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
	if (!m_BackTex.Load("Texture/Result/result_BackGround.png"))	{ return FALSE; }
	if (!m_BoardTex.Load("Texture/Result/ResultPaper.png"))			{ return FALSE; }
	char* str;
	switch (m_GameEndNo)
	{
	case GAMEENDNO_CONTINUE: break;
	case GAMEENDNO_CLEAR:	str = "Texture/Result/GameClearStr.png";		break;
	case GAMEENDNO_HP:		str = "Texture/Result/GameOverStr_HP.png";		break;
	case GAMEENDNO_JEWEL:	str = "Texture/Result/GameOverStr_Jewel.png";	break;
	case GAMEENDNO_GAS:		str = "Texture/Result/GameOverStr_Gas.png";		break;
	default: break;
	}
	if (!m_ResultTex.Load(str)) { return FALSE; }

	return TRUE;
}

/// <summary>
/// 初期化
/// </summary>
void CSceneResult::Initialize() {
	//ゲーム終了番号を取得
	m_GameEndNo = CGameEndManager::Instance().GetGameEndCondition();
	InitializeBase();
}

/// <summary>
/// 更新
/// </summary>
void CSceneResult::Update() {
	UpdateBase();

	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		CGameEndManager::Instance().SetGameEndCondition(GAMEENDNO_CONTINUE);
		SetNextScene(SCENENO_MODESELECT);
	}
}

/// <summary>
/// 描画
/// </summary>
void CSceneResult::Render(void) {
	m_BackTex.Render(0, 0);
	m_BoardTex.Render(200, 100);
	m_ResultTex.Render(300, 150);
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
	m_BackTex.Release();
	m_BoardTex.Release();
	m_ResultTex.Release();
}