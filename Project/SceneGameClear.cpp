/*************************************************************************//*!

					@file	SceneGameClear.cpp
					@brief	ゲームクリア画面。

															@author	池上　綾香
*//**************************************************************************/
#include "SceneGameClear.h"

/// <summary>
/// コンストラクタ
/// </summary>
CSceneGameClear::CSceneGameClear() {
}

/// <summary>
/// デストラクタ
/// </summary>
CSceneGameClear::~CSceneGameClear() {
}

/// <summary>
/// 読み込み
/// </summary>
/// <returns>成功：true, 失敗：false</returns>
bool CSceneGameClear::Load() {
	return false;
}

/// <summary>
/// 初期化
/// </summary>
void CSceneGameClear::Initialize() {
}

/// <summary>
/// 更新
/// </summary>
void CSceneGameClear::Update() {
}

/// <summary>
/// 描画
/// </summary>
void CSceneGameClear::Render(void) {
}

/// <summary>
/// デバッグ描画
/// </summary>
void CSceneGameClear::RenderDebug(void) {
	CGraphicsUtilities::RenderString(10, 10, "ゲーム画面");
}

/// <summary>
/// 解放
/// </summary>
void CSceneGameClear::Release(void) {
}