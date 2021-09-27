/*************************************************************************//*!

					@file	Item.cpp
					@brief	アイテム。

															@author	池上　綾香
*//**************************************************************************/
#include "Item.h"
#include	"Item.h"

/// <summary>
/// コンストラクタ
/// </summary>
CItem::CItem() :
m_pTexture(NULL),
m_Motion(),
m_Type(),
m_Pos(0.0f, 0.0f),
m_Move(0.0f, 0.0f),
m_bShow(false),
m_SrcRect() {
}

/// <summary>
/// デストラクタ
/// </summary>
CItem::~CItem() {
	Release();
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="pos">位置座標</param>
/// <param name="type">アイテムのタイプ</param>
void CItem::Initialize(Vector2 pos, int type) {
	m_Type = type;
	m_Pos = pos;
	m_Move = Vector2(0.0f, 0.0f);
	m_bShow = true;

	//アニメーションを作成
	SpriteAnimationCreate anim = {
		"アイテム",
		0,0,
		32,32,
		TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0}}
	};
	m_Motion.Create(anim);
}

/// <summary>
/// 更新
/// </summary>
void CItem::Update() {
	//非表示
	if (!m_bShow)
	{
		return;
	}
	//実際に座標を移動させる
	m_Pos += m_Move;
	//アニメーションの更新
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
}

/// <summary>
/// ステージとの当たり判定
/// </summary>
/// <param name="buried">埋まり量</param>
void CItem::CollisionStage(Vector2 buried) {
	m_Pos += buried;
}

/// <summary>
/// 描画
/// </summary>
/// <param name="world">ワールドの変化</param>
void CItem::Render(Vector2 world) {
	//非表示
	if (!m_bShow)
	{
		return;
	}
	//テクスチャの描画
	m_pTexture->Render(m_Pos.x - world.x, m_Pos.y - world.y, m_SrcRect);
}

/// <summary>
/// デバッグ描画
/// </summary>
/// <param name="world">ワールドの変化</param>
void CItem::RenderDebug(Vector2 world) {
	//非表示
	if (!m_bShow)
	{
		return;
	}
	//当たり判定の表示
	CRectangle hr = GetRect();
	CGraphicsUtilities::RenderRect(
		hr.Left - world.x, hr.Top - world.y, 
		hr.Right - world.x, hr.Bottom - world.y, MOF_XRGB(255, 0, 0));
}

/// <summary>
/// 解放
/// </summary>
void CItem::Release() {
	m_Motion.Release();
}