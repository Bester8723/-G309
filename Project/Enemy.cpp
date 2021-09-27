/*************************************************************************//*!

					@file	Enemy.cpp
					@brief	敵。

															@author	池上　綾香
*//**************************************************************************/
#include "Enemy.h"

/// <summary>
/// コンストラクタ
/// </summary>
CEnemy::CEnemy() :
m_pTexture(NULL),
m_Motion(),
m_Type(),
m_Pos(0.0f, 0.0f),
m_Move(0.0f, 0.0f),
m_bShow(false),
m_bReverse(false),
m_SrcRect(),
m_HP(ENEMY_INI_HP),
m_DamageWait(0),
m_pEffectManager(NULL) {
}

/// <summary>
/// デストラクタ
/// </summary>
CEnemy::~CEnemy() {
	Release();
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="pos">位置座標</param>
/// <param name="type">敵のタイプ</param>
void CEnemy::Initialize(Vector2 pos, int type) {
	m_Type = type;
	m_Pos = pos;
	m_Move.x = -3.0f;
	m_Move.y = 0.0f;
	m_bReverse = true;
	m_bShow = true;
	m_HP = 10;
	m_DamageWait = 0;

	SpriteAnimationCreate anim[] = {
		{
			"移動",
			0,0,
			60,64,
			TRUE,{ { 5,0,0 },{ 5,1,0 },{ 5,2,0 },{ 5,3,0 }, }
		},
		{
			"ダメージ",
			0,210,
			60,64,
			FALSE,{{ 20,0,0 }}
		},
	};
	m_Motion.Create(anim, MOTION_COUNT);
}

/// <summary>
/// 更新
/// </summary>
void CEnemy::Update() {
	//非表示
	if (!m_bShow)
	{
		return;
	}
	//ダメージ中の動作
	if (m_Motion.GetMotionNo() == MOTION_DAMAGE)
	{
		//終了で待機に戻す
		if (m_Motion.IsEndMotion())
		{
			m_Motion.ChangeMotion(MOTION_MOVE);
			if (m_HP <= 0)
			{
				m_bShow = false;
				//爆発エフェクトを発生させる
				Vector2 startPos = Vector2(m_Pos.x + m_SrcRect.GetWidth() * 0.5f, m_Pos.y + m_SrcRect.GetHeight() * 0.5f);
				m_pEffectManager->Start(startPos, EFC_EXPLOSION01);
			}
			m_Move.x = ((m_bReverse) ? -3.0f : 3.0f);
		}
		else
		{
			if (m_Move.x > 0)
			{
				m_Move.x -= 0.2f;
				if (m_Move.x <= 0)
				{
					m_Move.x = 0;
				}
			}
			else if (m_Move.x < 0)
			{
				m_Move.x += 0.2f;
				if (m_Move.x >= 0)
				{
					m_Move.x = 0;
				}
			}
		}
	}
	//重力により少しずつ下がる
	m_Move.y += GRAVITY;
	if (m_Move.y >= 20.0f) { m_Move.y = 20.0f; }
	//実際に座標を移動させる
	m_Pos.x += m_Move.x;
	m_Pos.y += m_Move.y;
	//アニメーションの更新
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
	//ダメージのインターバルを減らす
	if (m_DamageWait > 0)
	{
		m_DamageWait--;
	}
}

/// <summary>
/// ステージとの当たり判定
/// </summary>
/// <param name="buried">埋まり量</param>
void CEnemy::CollisionStage(Vector2 buried) {
	m_Pos += buried;
	//落下中の下埋まり、ジャンプ中の上埋まりの場合は移動を初期化する。
	if (buried.y < 0 && m_Move.y > 0)
	{
		m_Move.y = 0;
	}
	else if (buried.y > 0 && m_Move.y < 0)
	{
		m_Move.y = 0;
	}
	//左移動中の左埋まり、右移動中の右埋まりの場合は移動を初期化する。
	if (buried.x < 0 && m_Move.x > 0)
	{
		m_Move.x *= -1;
		m_bReverse = true;
	}
	else if (buried.x > 0 && m_Move.x < 0)
	{
		m_Move.x *= -1;
		m_bReverse = false;
	}
}

/// <summary>
/// 描画
/// </summary>
/// <param name="world">ワールドの変化</param>
void CEnemy::Render(Vector2 world) {
	//非表示
	if (!m_bShow)
	{
		return;
	}
	//インターバル２　フレームごとに描画をしない
	if (m_DamageWait % 4 >= 2)
	{
		return;
	}
	//描画矩形
	CRectangle dr = m_SrcRect;
	//反転フラグがONの場合描画矩形を反転させる
	if (m_bReverse)
	{
		float tmp = dr.Right;
		dr.Right = dr.Left;
		dr.Left = tmp;
	}
	//テクスチャの描画
	m_pTexture->Render(m_Pos.x - world.x, m_Pos.y - world.y, dr);
}

/// <summary>
/// デバッグ描画
/// </summary>
/// <param name="world"></param>
void CEnemy::RenderDebug(Vector2 world) {
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
void CEnemy::Release() {
	m_Motion.Release();
}

/// <summary>
/// ダメージ処理
/// </summary>
/// <param name="dmg">ダメージ量</param>
/// <param name="bRev">反転フラグ</param>
void CEnemy::Damage(int dmg, bool bRev) {
	m_HP -= dmg;
	m_DamageWait = ENEMY_DAMAGEWAIT;
	if (bRev)
	{
		m_Move.x -= 5.0f;
		m_bReverse = false;
	}
	else
	{
		m_Move.x = 5.0f;
		m_bReverse = true;
	}
	m_Motion.ChangeMotion(MOTION_DAMAGE);
	//ダメージエフェクトを発生させる
	Vector2 startPos = Vector2(m_Pos.x + m_SrcRect.GetWidth() * 0.5f, m_Pos.y + m_SrcRect.GetHeight() * 0.5f);
	m_pEffectManager->Start(startPos, EFC_DAMAGE);
}