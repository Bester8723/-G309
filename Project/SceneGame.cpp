/*************************************************************************//*!

					@file	SceneGame.cpp
					@brief	ゲーム画面。

															@author	池上　綾香
*//**************************************************************************/
#include "SceneGame.h"

/// <summary>
/// コンストラクタ
/// </summary>
CSceneGame::CSceneGame() {
}

/// <summary>
/// デストラクタ
/// </summary>
CSceneGame::~CSceneGame() {
}

/// <summary>
/// 読み込み
/// </summary>
/// <returns>成功：true, 失敗：false</returns>
bool CSceneGame::Load() {
	return false;
}

/// <summary>
/// 初期化
/// </summary>
void CSceneGame::Initialize() {
}

/// <summary>
/// 更新
/// </summary>
void CSceneGame::Update() {
}

/// <summary>
/// 描画
/// </summary>
void CSceneGame::Render(void) {
}

/// <summary>
/// デバッグ描画
/// </summary>
void CSceneGame::RenderDebug(void) {
	CGraphicsUtilities::RenderString(10, 10, "ゲーム画面");
}

/// <summary>
/// 解放
/// </summary>
void CSceneGame::Release(void) {
}