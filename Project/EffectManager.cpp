/*************************************************************************//*!

					@file	EffectManager.cpp
					@brief	エフェクト管理。

															@author	池上　綾香
*//**************************************************************************/
#include "EffectManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
CEffectManager::CEffectManager() {
}

/// <summary>
/// デストラクタ
/// </summary>
CEffectManager::~CEffectManager() {
}

/// <summary>
/// 読み込み
/// </summary>
/// <returns>成功すればtrue, 失敗すればfalse</returns>
bool CEffectManager::Load() {
	char* name[] = {
		"Texture/Effect/effect01.png",
		"Texture/Effect/effect02.png",
		"Texture/Effect/effect03.png",
	};
	for (int i = 0; i < EFC_TYPECOUNT; i++)
	{
		if (!m_Texture[i].Load(name[i]))
		{
			return FALSE;
		}
	}
	return TRUE;
}

/// <summary>
/// 初期化
/// </summary>
void CEffectManager::Initialize() {
	//エフェクトの基礎設定
	for (int j = 0; j < EFC_TYPECOUNT; j++)
	{
		for (int i = 0; i < EFFECTCOUNT; i++)
		{
			m_Effect[i][j].SetTexture(&m_Texture[j]);
			m_Effect[i][j].Initialize(j);
		}
	}
}

/// <summary>
/// 開始
/// 座標を設定してモーションを開始する。
/// </summary>
/// <param name="pos">座標</param>
/// <param name="type">エフェクトタイプ</param>
/// <returns>エフェクトのポインタ</returns>
CEffect* CEffectManager::Start(Vector2 pos, int type) {
	for (int i = 0; i < EFFECTCOUNT; i++)
	{
		//未使用のエフェクトかどうか確認
		if (m_Effect[i][type].GetShow())
		{
			continue;
		}
		//エフェクトのStartを呼び出す
		m_Effect[i][type].Start(pos);
		//開始したエフェクトのポインタを返す
		return &m_Effect[i][type];
	}
	return NULL;
}

/// <summary>
/// 更新
/// </summary>
void CEffectManager::Update() {
	for (int j = 0; j < EFC_TYPECOUNT; j++)
	{
		for (int i = 0; i < EFFECTCOUNT; i++)
		{
			m_Effect[i][j].Update();
		}
	}
}

/// <summary>
/// 描画
/// </summary>
/// <param name="world">ワールドの変化</param>
void CEffectManager::Render(Vector2 world) {
	for (int j = 0; j < EFC_TYPECOUNT; j++)
	{
		for (int i = 0; i < EFFECTCOUNT; i++)
		{
			m_Effect[i][j].Render(world);
		}
	}
}

/// <summary>
/// デバッグ描画
/// </summary>
/// <param name="world">ワールドの変化</param>
void CEffectManager::RenderDebug(Vector2 world) {
	for (int j = 0; j < EFC_TYPECOUNT; j++)
	{
		for (int i = 0; i < EFFECTCOUNT; i++)
		{
			m_Effect[i][j].RenderDebug(world);
		}
	}
}

/// <summary>
/// 解放
/// </summary>
void CEffectManager::Release() {
	for (int j = 0; j < EFC_TYPECOUNT; j++)
	{
		for (int i = 0; i < EFFECTCOUNT; i++)
		{
			m_Effect[i][j].Release();
		}
		m_Texture[j].Release();
	}
}