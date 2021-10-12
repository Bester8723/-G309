/*************************************************************************//*!

					@file	SceneModeSelect.cpp
					@brief	ステージセレクト画面。

															@author	池上　綾香
*//**************************************************************************/
#include "SceneModeSelect.h"

/// <summary>
/// コンストラクタ
/// </summary>
CSceneModeSelect::CSceneModeSelect() {
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
	return false;
}

/// <summary>
/// 初期化
/// </summary>
void CSceneModeSelect::Initialize() {
}

/// <summary>
/// 更新
/// </summary>
void CSceneModeSelect::Update() {
}

/// <summary>
/// 描画
/// </summary>
void CSceneModeSelect::Render(void) {
}

/// <summary>
/// デバッグ描画
/// </summary>
void CSceneModeSelect::RenderDebug(void) {
	CGraphicsUtilities::RenderString(10, 10, "ゲーム画面");
}

/// <summary>
/// 解放
/// </summary>
void CSceneModeSelect::Release(void) {
}