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
m_bShow(false),
m_bDead(false),
m_bReverse(false),
m_SrcRect(),
ENEMY_DAMAGESPEED(0.0f),
m_pEffectManager(NULL),
ENEMY_INI_POS(0.0f, 0.0f),
ENEMY_QUAKE(0.0f),
ENEMY_INI_SPEED(0.0f),
m_MoveSpeed(0.0f),
m_MoveTime(0.0f) {
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
	m_bReverse = true;
	m_bShow = true;
	m_bDead = false;

	ENEMY_INI_POS = m_Pos;
	ENEMY_QUAKE = 120.0f;
	m_MoveTime = 0.0f;
	switch (m_Type)
	{
	case	ENEMYTYPE_HORIZONTAL:	ENEMY_INI_SPEED = 3.0f;		break;
	case	ENEMYTYPE_VERTICAL:		ENEMY_INI_SPEED = 5.0f;		break;
	default:						ENEMY_INI_SPEED = 3.0f;		break;
	}
	m_MoveSpeed = ENEMY_INI_SPEED;
	ENEMY_DAMAGESPEED = ENEMY_INI_SPEED * 1.5f;

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
			FALSE,{{ 10,0,0 }}
		},
	};
	m_Motion.Create(anim, MOTION_COUNT);
}

/// <summary>
/// 更新
/// </summary>
void CEnemy::Update() {
	if (!m_bShow)
	{
		return;
	}
	//ダメージ中の動作
	if (m_Motion.GetMotionNo() == MOTION_DAMAGE)
	{
		if (m_Motion.IsEndMotion())
		{
			m_bShow = false;
			//爆発エフェクトを発生させる
			Vector2 startPos = Vector2(m_Pos.x + m_SrcRect.GetWidth() * 0.5f, m_Pos.y + m_SrcRect.GetHeight() * 0.5f);
			m_pEffectManager->Start(startPos, EFC_EXPLOSION01);
			return;
		}
		else
		{
			m_Pos.y += m_MoveSpeed;
		}
	}
	else
	{
		m_MoveTime += 0.01f;
		if (m_MoveTime > MOF_MATH_2PI)
		{
			m_MoveTime -= MOF_MATH_2PI;
		}
		CVector2 pos = m_Pos;
		if (m_Type == ENEMYTYPE_HORIZONTAL)
		{
			m_Pos.x = ENEMY_INI_POS.x + sin(m_MoveTime * m_MoveSpeed) * ENEMY_QUAKE;
			if ((m_Pos.x - pos.x) > 0)
			{
				m_bReverse = false;
			}
			else if ((m_Pos.x - pos.x) < 0)
			{
				m_bReverse = true;
			}
		}
		else
		{
			m_Pos.y = ENEMY_INI_POS.y + sin(m_MoveTime * m_MoveSpeed) * ENEMY_QUAKE;
		}
	}

	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
}

/// <summary>
/// ステージとの当たり判定
/// </summary>
/// <param name="buried">埋まり量</param>
void CEnemy::CollisionStage(Vector2 buried) {
	if (m_bDead)
	{
		return;
	}
	m_Pos += buried;
}

/// <summary>
/// 描画
/// </summary>
/// <param name="world">ワールドの変化</param>
void CEnemy::Render(Vector2 world) {
	if (!m_bShow)
	{
		return;
	}
	//描画矩形
	CRectangle dr = m_SrcRect;
	if (m_bReverse)
	{
		float tmp = dr.Right;
		dr.Right = dr.Left;
		dr.Left = tmp;
	}
	m_pTexture->Render(m_Pos.x - world.x, m_Pos.y - world.y, dr);
}

/// <summary>
/// デバッグ描画
/// </summary>
/// <param name="world"></param>
void CEnemy::RenderDebug(Vector2 world) {
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
void CEnemy::Damage() {
	if (m_bDead)
	{
		return;
	}
	m_Motion.ChangeMotion(MOTION_DAMAGE);
	m_bDead = true;
	m_MoveSpeed = ENEMY_FALLSPEED;
	//ダメージエフェクトを発生させる
	Vector2 startPos = Vector2(m_Pos.x + m_SrcRect.GetWidth() * 0.5f, m_Pos.y + m_SrcRect.GetHeight() * 0.5f);
	m_pEffectManager->Start(startPos, EFC_DAMAGE);
}