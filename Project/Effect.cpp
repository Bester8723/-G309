/*************************************************************************//*!

					@file	Effect.cpp
					@brief	エフェクト。

															@author	池上　綾香
*//**************************************************************************/
#include "Effect.h"
#include "EffectManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
CEffect::CEffect() :
m_pTexture(NULL),
m_Motion(),
m_Pos(0.0f, 0.0f),
m_bShow(false),
m_SrcRect() {
}

/// <summary>
/// デストラクタ
/// </summary>
CEffect::~CEffect() {
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="type">タイプ</param>
void CEffect::Initialize(int type) {
	m_Pos = Vector2(0, 0);
	m_bShow = false;

	switch (type)
	{
	case EFC_DAMAGE:
	{
		SpriteAnimationCreate anim[] = {
			{
				"エフェクト",
				0, 0,
				128, 128,
				FALSE, { { 2, 0, 0 }, { 2, 1, 0 }, { 2, 2, 0 }, { 2, 3, 0 }, }
			}
		};
		m_Motion.Create(anim, 1);
		break;
	}
	case EFC_EXPLOSION01:
	{
		SpriteAnimationCreate anim[] = {
			{
				"エフェクト",
				0, 0,
				120, 120,
				FALSE, {
					{ 3, 0, 0 }, { 3, 1, 0 }, { 3, 2, 0 }, { 3, 3, 0 }, { 3, 4, 0 },
					{ 3, 5, 0 }, { 3, 6, 0 }, { 3, 7, 0 }, { 3, 8, 0 }, { 3, 9, 0 },
					{ 3, 10, 0 }, { 3, 11, 0 }, { 3, 12, 0 }, { 3, 13, 0 }, { 3, 14, 0 }, { 3, 15, 0 }, }
			}
		};
		m_Motion.Create(anim, 1);
		break;
	}
	case EFC_EXPLOSION02:
	{
		SpriteAnimationCreate anim[] = {
			{
				"エフェクト",
				0, 0,
				180, 180,
				FALSE, {
					{ 3, 0, 0 }, { 3, 1, 0 }, { 3, 2, 0 }, { 3, 3, 0 }, { 3, 4, 0 },
					{ 3, 5, 0 }, { 3, 6, 0 }, { 3, 7, 0 }, { 3, 8, 0 }, { 3, 9, 0 }, { 3, 10, 0 },
					{ 3, 0, 1 }, { 3, 1, 1 }, { 3, 2, 1 }, { 3, 3, 1 }, { 3, 4, 1 },
					{ 3, 5, 1 }, { 3, 6, 1 }, { 3, 7, 1 }, { 3, 8, 1 }, { 3, 9, 1 }, { 3, 10, 1 }, }
			}
		};
		m_Motion.Create(anim, 1);
		break;
	}
	}
}

/// <summary>
/// 開始
/// 座標を設定してモーションを開始する。
/// </summary>
/// <param name="pos">座標</param>
void CEffect::Start(Vector2 pos) {
	//表示矩形を取得
	m_SrcRect = m_Motion.GetSrcRect();

	//座標を設定。指定された座標が上下左右中央になるように
	m_Pos.x = pos.x - m_SrcRect.GetWidth() * 0.5f;
	m_Pos.y = pos.y - m_SrcRect.GetHeight() * 0.5f;

	//表示状態に
	m_bShow = true;

	//設定したアニメーションを再生開始
	m_Motion.ChangeMotion(0);
}

/// <summary>
/// 更新
/// </summary>
void CEffect::Update() {
	//非表示
	if (!m_bShow)
	{
		return;
	}
	//アニメーションの更新
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
	//アニメーションの終了で非表示にする
	if (m_Motion.IsEndMotion())
	{
		m_bShow = false;
	}
}

/// <summary>
/// 描画
/// </summary>
/// <param name="world">ワールドの変化</param>
void CEffect::Render(Vector2 world) {
	//非表示
	if (!m_bShow)
	{
		return;
	}
	m_pTexture->Render(m_Pos.x - world.x, m_Pos.y - world.y, m_SrcRect);
}

/// <summary>
/// デバッグ描画
/// </summary>
/// <param name="world">ワールドの変化</param>
void CEffect::RenderDebug(Vector2 world) {
	if (!m_bShow)
	{
		return;
	}
}

/// <summary>
/// 解放
/// </summary>
void CEffect::Release() {
	m_Motion.Release();
}