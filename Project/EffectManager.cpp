/*************************************************************************//*!

					@file	EffectManager.cpp
					@brief	エフェクト管理。

															@author	池上　綾香
*//**************************************************************************/
#include "EffectManager.h"

/**
 * コンストラクタ
 *
 */
CEffectManager::CEffectManager() {
}

/**
 * デストラクタ
 *
 */
CEffectManager::~CEffectManager() {
}

/**
 * 読み込み
 * 利用するテクスチャを読み込む。
 */
bool CEffectManager::Load(void) {
	char* name[] = {
		"Texture/Effect/effect01.png",
		"Texture/Effect/effect02.png",
		"Texture/Effect/effect03.png",
	};
	for (int i = 0; i < EFC_TYPECOUNT; i++)
	{
		if (!m_Texture[i].Load(name[i]))
		{
			return false;
		}
	}
	return true;
}

/**
 * 初期化
 * パラメーターや座標を初期化する。
 */
void CEffectManager::Initialize(void) {
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

/**
 * 開始
 * 座標を設定してモーションを開始する。
 *
 * 引数
 * [in]			px					X座標
 * [in]			py					Y座標
 * [in]			type				エフェクトタイプ
 */
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

/**
 * 更新
 *
 */
void CEffectManager::Update(void) {
	for (int j = 0; j < EFC_TYPECOUNT; j++)
	{
		for (int i = 0; i < EFFECTCOUNT; i++)
		{
			m_Effect[i][j].Update();
		}
	}
}

/**
 * 描画
 *
 * 引数
 * [in]			wx					ワールドの変化
 * [in]			wy					ワールドの変化
 */
void CEffectManager::Render(Vector2 world) {
	for (int j = 0; j < EFC_TYPECOUNT; j++)
	{
		for (int i = 0; i < EFFECTCOUNT; i++)
		{
			m_Effect[i][j].Render(world);
		}
	}
}


/**
 * デバッグ描画
 *
 * 引数
 * [in]			wx					ワールドの変化
 * [in]			wy					ワールドの変化
 */
void CEffectManager::RenderDebug(Vector2 world) {
	for (int j = 0; j < EFC_TYPECOUNT; j++)
	{
		for (int i = 0; i < EFFECTCOUNT; i++)
		{
			m_Effect[i][j].RenderDebug(world);
		}
	}
}

/**
 * 解放
 *
 */
void CEffectManager::Release(void) {
	for (int j = 0; j < EFC_TYPECOUNT; j++)
	{
		for (int i = 0; i < EFFECTCOUNT; i++)
		{
			m_Effect[i][j].Release();
		}
		m_Texture[j].Release();
	}
}