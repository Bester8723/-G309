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
m_Move(0.0f, 0.0f),
m_Scroll(0.0f, 0.0f) {
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
	if (!m_Tex.Load("Texture/Game/Gas.png")) { return FALSE; }

	return TRUE;
}

/// <summary>
/// 初期化
/// </summary>
void CGas::Initialize(Vector2 world) {
	m_Move = Vector2(SPEEDX, -SPEEDY);
	m_Scroll = Vector2(world.x, world.y + g_pGraphics->GetTargetHeight() - STARTPOS);
}

/// <summary>
/// 更新
/// </summary>
void CGas::Update() {
	m_Scroll += m_Move;
	if (m_Scroll.y <= 0)
	{
		m_Move.y = 0;
		m_Scroll.y = 0;
	}

	//デバッグ更新
	if (CDebugManager::Instance().GetDebugFlg())
	{
		UpdateDebug();
	}
}

/// <summary>
/// デバッグ更新
/// </summary>
void CGas::UpdateDebug() {
	//２キーでガスのTrigger
	if (g_pInput->IsKeyPush(MOFKEY_2))
	{
		m_Move.y = (m_Move.y == 0) ? m_Move.y = -SPEEDY : m_Move.y = 0;
	}
}

/// <summary>
/// 描画
/// </summary>
void CGas::Render(Vector2 world) {
	int scw = g_pGraphics->GetTargetWidth();
	int wn = m_Tex.GetWidth();
	for (float x = ((int)-m_Scroll.x % wn) - wn; x < scw; x += wn)
	{
		m_Tex.Render(x - world.x, m_Scroll.y - world.y);
	}
}

/// <summary>
/// デバッグ描画
/// </summary>
void CGas::RenderDebug(Vector2 world) {
}

/// <summary>
/// 解放
/// </summary>
void CGas::Release() {
	m_Tex.Release();
}

/// <summary>
/// アイテムとの当たり判定
/// </summary>
/// <param name="itm">判定するアイテム</param>
/// <returns>埋まっていればtrue, 埋まっていなければfalse</returns>
bool CGas::CollisionItem(CItem& itm) {
	if (!itm.GetShow() || itm.GetType() != ITEMTYPE_JEWEL)
	{
		return FALSE;
	}
	if (itm.GetRect().Top > m_Scroll.y)
	{
		itm.SetShow(false);
		CGameEndManager::Instance().SetGameEndCondition(GAMEENDNO_JEWEL);
		return TRUE;
	}
	return FALSE;
}