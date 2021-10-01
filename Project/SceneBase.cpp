/*************************************************************************//*!

					@file	SceneBase.cpp
					@brief	シーン基礎。

															@author	池上　綾香
*//**************************************************************************/
#include "SceneBase.h"

/// <summary>
/// コンストラクタ
/// </summary>
CSceneBase::CSceneBase() :
m_bEnd(false),
m_bChange(false),
m_NextScene(0),
m_BlackAlpha(255.0f),
m_WindowRect(),
m_BlackFadeTime(0.0f) {
}

/// <summary>
/// デストラクタ
/// </summary>
CSceneBase::~CSceneBase() {
}

/// <summary>
/// 初期化共通部
/// </summary>
void CSceneBase::InitializeBase() {
	//読み込み
	Load();
	//フラグ類の初期化
	m_bEnd = false;
	m_bChange = false;
	//値の初期化
	m_BlackAlpha = 255.0f;
	m_BlackFadeTime = 30.0f;
}

/// <summary>
/// 更新共通部
/// </summary>
void CSceneBase::UpdateBase() {
	//シーン遷移フラグが立っているとき、黒い画面を描画
	if (IsChange() && !IsEnd())
	{
		m_BlackAlpha += 255 / m_BlackFadeTime;
		if (m_BlackAlpha > 255)
		{
			m_BlackAlpha = 255;
			m_bEnd = true;
		}
	}
	//シーン遷移フラグが立っていないのに黒い画面が描画されている場合は、
	//徐々にアルファ値を減らす
	else if (m_BlackAlpha > 0 && !IsChange())
	{
		m_BlackAlpha -= 255 / m_BlackFadeTime;
		if (m_BlackAlpha < 0) { m_BlackAlpha = 0; }
	}
}

/// <summary>
/// 描画共通部
/// </summary>
void CSceneBase::RenderBase() {
	//黒い画面
	CGraphicsUtilities::RenderFillRect(GetWindowRect(), MOF_ALPHA_BLACK((int)m_BlackAlpha));
}