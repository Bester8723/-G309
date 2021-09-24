/*************************************************************************//*!

					@file	SceneStageSelect.cpp
					@brief	ステージセレクト画面。

															@author	池上　綾香
*//**************************************************************************/
#include "SceneStageSelect.h"

/// <summary>
/// コンストラクタ
/// </summary>
CSceneStageSelect::CSceneStageSelect() {
}

/// <summary>
/// デストラクタ
/// </summary>
CSceneStageSelect::~CSceneStageSelect() {
}

/// <summary>
/// 読み込み
/// </summary>
/// <returns>成功：true, 失敗：false</returns>
bool CSceneStageSelect::Load() {
	return false;
}

/// <summary>
/// 初期化
/// </summary>
void CSceneStageSelect::Initialize() {
}

/// <summary>
/// 更新
/// </summary>
void CSceneStageSelect::Update() {
}

/// <summary>
/// 描画
/// </summary>
void CSceneStageSelect::Render(void) {
}

/// <summary>
/// デバッグ描画
/// </summary>
void CSceneStageSelect::RenderDebug(void) {
	CGraphicsUtilities::RenderString(10, 10, "ゲーム画面");
}

/// <summary>
/// 解放
/// </summary>
void CSceneStageSelect::Release(void) {
}