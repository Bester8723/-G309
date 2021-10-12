/*************************************************************************//*!

					@file	Gas.cpp
					@brief	瘴気。

															@author	池上　綾香
*//**************************************************************************/
#include "Gas.h"

/// <summary>
/// コンストラクタ
/// </summary>
CGas::CGas() : 
m_Tex(),
m_Pos(0.0f, 0.0f),
m_Move(0.0f, 0.0f) {
}

/// <summary>
/// デストラクタ
/// </summary>
CGas::~CGas() {
}

/// <summary>
/// 読み込み
/// </summary>
/// <returns>成功：true, 失敗：false</returns>
bool CGas::Load() {
	CUtilities::SetCurrentDirectory("Resource\Texture\Game");
	return TRUE;
}

/// <summary>
/// 初期化
/// </summary>
void CGas::Initialize() {
}

/// <summary>
/// 更新
/// </summary>
void CGas::Update() {
}

/// <summary>
/// 描画
/// </summary>
void CGas::Render() {

}

/// <summary>
/// デバッグ描画
/// </summary>
void CGas::RenderDebug() {
}

/// <summary>
/// 解放
/// </summary>
void CGas::Release() {
}