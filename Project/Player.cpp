/*************************************************************************//*!

					@file	Player.cpp
					@brief	プレイヤー。

															@author	池上　綾香
*//**************************************************************************/
#include "Player.h"

/// <summary>
/// コンストラクタ
/// </summary>
CPlayer::CPlayer() : 
m_Tex(),
m_SrcRect(),
m_bReverse(false),
m_Motion(),
m_Pos(0.0f, 0.0f),
m_Move(0.0f, 0.0f),
m_bMove(false),
m_JumpCount(0),
m_bJumping(false),
m_bDead(false),
m_HP(PLAYER_INI_HP),
m_JewelCount(0),
m_DamageWait(0),
m_pEffectManager(NULL),
m_pEndEffect(NULL) {
}

/// <summary>
/// デストラクタ
/// </summary>
CPlayer::~CPlayer() {
}

/// <summary>
/// 読み込み
/// </summary>
/// <returns>成功：true, 失敗：false</returns>
bool CPlayer::Load() {
	if (!m_Tex.Load("Texture/Game/Player.png")) { return FALSE; }
	//アニメーションを作成
	SpriteAnimationCreate anim[] = {
		{
			"待機",
			0,0,
			60,64,
			TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0},{5,4,0},{5,5,0},{5,6,0},{5,7,0}}
		},
		{
			"移動",
			0,70,
			60,64,
			TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0},{5,4,0},{5,5,0}}
		},
		{
			"ジャンプ開始",
			0,140,
			60,64,
			FALSE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0}}
		},
		{
			"ジャンプ終了",
			240,140,
			60,64,
			FALSE,{{2,0,0},{2,1,0}}
		},
		{
			"ダメージ",
			480,0,
			60,64,
			FALSE,{{20,0,0}}
		},
	};
	m_Motion.Create(anim, MOTION_COUNT);
	m_Motion.ChangeMotion(MOTION_WAIT);
	m_SrcRect = m_Motion.GetSrcRect();

	return TRUE;
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="world">ワールドの初期変化値</param>
void CPlayer::Initialize(Vector2 world) {
	m_bReverse = false;
	m_Pos = Vector2(world.x, world.y + g_pGraphics->GetTargetHeight() - m_SrcRect.GetHeight());
	m_Move = Vector2(0.0f, 0.0f);
	m_bMove = false;
	m_JumpCount = 0;
	m_bJumping = false;
	m_bDead = false;
	m_HP = PLAYER_INI_HP;
	m_JewelCount = 0;
	m_DamageWait = 0;
}

/// <summary>
/// 更新
/// </summary>
void CPlayer::Update(Vector2 gas) {
	//瘴気に埋まると終了
	if (m_Pos.y + m_SrcRect.GetHeight() * 0.5f > gas.y)
	{
		m_bDead = true;
		CGameEndManager::Instance().SetGameEndCondition(GAMEENDNO_GAS);
	}
	//HPがなくなると爆発の終了を待機して終了
	if (m_HP <= 0)
	{
		if (!m_pEndEffect || !m_pEndEffect->GetShow())
		{
			m_bDead = true;
			CGameEndManager::Instance().SetGameEndCondition(GAMEENDNO_HP);
		}
		return;
	}
	//移動フラグ
	m_bMove = false;
	//着地、ダメージ中の場合の動作
	if (m_Motion.GetMotionNo() == MOTION_JUMPEND || m_Motion.GetMotionNo() == MOTION_DAMAGE)
	{
		//終了で待機に戻す
		if (m_Motion.IsEndMotion())
		{
			if (m_Motion.GetMotionNo() == MOTION_JUMPEND) { m_JumpCount = 0; }
			m_Motion.ChangeMotion(MOTION_WAIT);
		}
	}
	//それ以外、キー入力更新
	else
	{
		UpdateKey();
	}
	//移動更新
	UpdateMove();
	m_Pos += m_Move;
	m_Pos.x = MOF_CLIPING(m_Pos.x, 0, SCREEN_WIDTH - m_SrcRect.GetWidth());
	//アニメーションの更新
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
	//ダメージ待機時間を進める
	if (m_DamageWait > 0)
	{
		m_DamageWait--;
	}

	//デバッグ更新
	if (CDebugManager::Instance().GetDebugFlg())
	{
		UpdateDebug();
	}
}

/// <summary>
/// キー入力による更新
/// </summary>
void CPlayer::UpdateKey(void) {
	//左
	if (g_pInput->IsKeyHold(MOFKEY_A))
	{
		m_bMove = true;
		m_bReverse = true;
		m_Move.x = MOF_CLIPING(m_Move.x - PLAYER_SPEED, -PLAYER_MAXSPEED, PLAYER_MAXSPEED);
		if (m_Motion.GetMotionNo() == MOTION_WAIT)
		{
			m_Motion.ChangeMotion(MOTION_MOVE);
		}
	}
	//右
	else if (g_pInput->IsKeyHold(MOFKEY_D))
	{
		m_bMove = true;
		m_bReverse = false;
		m_Move.x = MOF_CLIPING(m_Move.x + PLAYER_SPEED, -PLAYER_MAXSPEED, PLAYER_MAXSPEED);
		if (m_Motion.GetMotionNo() == MOTION_WAIT)
		{
			m_Motion.ChangeMotion(MOTION_MOVE);
		}
	}
	//ジャンプ
	if (g_pInput->IsKeyPush(MOFKEY_W) && m_JumpCount < PLAYER_MAXJUMPCOUNT)
	{
		Jump();
	}
}

/// <summary>
/// ジャンプ
/// </summary>
void CPlayer::Jump() {
	m_bJumping = true;
	m_JumpCount++;
	m_Move.y = PLAYER_JUMP;
	m_Motion.ChangeMotion(MOTION_JUMPSTART);
}

/// <summary>
/// 移動更新
/// </summary>
void CPlayer::UpdateMove(void) {
	//移動がなければ減速処理
	if (!m_bMove)
	{
		m_Move.x = MOF_LERP(m_Move.x, 0, PLAYER_SPEED);
		if (m_Move.x < abs(0.05f) && m_Motion.GetMotionNo() == MOTION_MOVE)
		{
			m_Motion.ChangeMotion(MOTION_WAIT);
		}
	}
	//重力の影響
	m_Move.y = MOF_CLIPING(m_Move.y + GRAVITY, PLAYER_JUMP, MAXGRAVITY);
}

/// <summary>
/// デバッグ更新
/// </summary>
void CPlayer::UpdateDebug() {
	//１キーでHPをMAXにする
	if (g_pInput->IsKeyPush(MOFKEY_1))
	{
		m_HP = PLAYER_MAX_HP;
	}
}

/// <summary>
/// 描画
/// </summary>
void CPlayer::Render(Vector2 world) {
	//インターバル２
	if (m_DamageWait % 4 >= 2)
	{
		return;
	}

	CRectangle dr = m_SrcRect;
	if (m_bReverse)
	{
		float tmp = dr.Right;
		dr.Right = dr.Left;
		dr.Left = tmp;
	}
	//テクスチャの描画
	m_Tex.Render(m_Pos.x - world.x, m_Pos.y - world.y, dr);
}

/// <summary>
/// デバッグ描画
/// </summary>
void CPlayer::RenderDebug(Vector2 world) {
	//当たり判定の表示
	CRectangle hr = GetRect();
	CGraphicsUtilities::RenderRect(
		hr.Left - world.x, hr.Top - world.y,
		hr.Right - world.x, hr.Bottom - world.y, MOF_COLOR_BLUE);
	//攻撃範囲の表示
	hr = GetAttackRect();
	CGraphicsUtilities::RenderRect(
		hr.Left - world.x, hr.Top - world.y,
		hr.Right - world.x, hr.Bottom - world.y, MOF_COLOR_GREEN);
	//HP表示
	CGraphicsUtilities::RenderString(10, 35, "HP : %d", m_HP);
	CGraphicsUtilities::RenderString(10, 60, "Jewel : %d", m_JewelCount);
}

/// <summary>
/// 解放
/// </summary>
void CPlayer::Release(void) {
	m_Tex.Release();
	m_Motion.Release();
}

/// <summary>
/// ステージとの当たり判定
/// </summary>
/// <param name="buried">埋まり量</param>
void CPlayer::CollisionStage(Vector2 buried) {
	m_Pos += buried;
	//落下中の下埋まり、ジャンプ中の上埋まりの場合は移動を初期化する。
	if (buried.y < 0 && m_Move.y > 0)
	{
		m_Move.y = 0;
		if (m_bJumping)
		{
			m_bJumping = false;
			m_Motion.ChangeMotion(MOTION_JUMPEND);
		}
	}
	else if (buried.y > 0 && m_Move.y < 0)
	{
		m_Move.y = 0;
	}
	//左移動中の左埋まり、右移動中の右埋まりの場合は移動を初期化する。
	if (buried.x < 0 && m_Move.x > 0)
	{
		m_Move.x = 0;
		if (g_pInput->IsKeyHold(MOFKEY_W))
		{
			m_Move.x = -20.0f;
			m_JumpCount = 0;
			Jump();
		}
	}
	else if (buried.x > 0 && m_Move.x < 0)
	{
		m_Move.x = 0;
		if (g_pInput->IsKeyHold(MOFKEY_W))
		{
			m_Move.x = 20.0f;
			m_JumpCount = 0;
			Jump();
		}
	}
}

/// <summary>
/// 敵との当たり判定
/// </summary>
/// <param name="ene">判定を行う敵</param>
/// <returns>当たっていればtrue, 当たっていなければfalse</returns>
bool CPlayer::CollisionEnemy(CEnemy& ene) {
	if (ene.IsDead() || m_HP <= 0 || m_DamageWait > 0)
	{
		return FALSE;
	}

	CRectangle prec;
	CRectangle erec = ene.GetRect();

	//敵の矩形と自分の攻撃矩形で敵がダメージ
	prec = GetAttackRect();
	if (prec.CollisionRect(erec) && prec.Bottom < erec.Top + erec.GetHeight() * 0.3f && m_Move.y > 0)
	{
		ene.Damage();
		m_Move.y = PLAYER_STEPONENEMY;
		m_JumpCount = 0;
		if (g_pInput->IsKeyHold(MOFKEY_W))
		{
			Jump();
			m_Move.y *= PLAYER_STEPJUMPSPEED;
		}
		return TRUE;
	}
	//自分がダメージ
	prec = GetRect();
	if (prec.CollisionRect(erec))
	{
		m_HP -= PLAYER_DAMAGE_HP;
		m_DamageWait = PLAYER_DAMAGEWAIT;
		if (prec.Left < erec.Left)
		{
			m_Move.x = -PLAYER_DAMAGESPEED;
			m_bReverse = false;
		}
		else
		{
			m_Move.x = PLAYER_DAMAGESPEED;
			m_bReverse = true;
		}
		m_Motion.ChangeMotion(MOTION_DAMAGE);
		if (m_HP <= 0)
		{
			//爆発エフェクトを発生させる
			Vector2 startPos = Vector2(m_Pos.x + m_SrcRect.GetWidth() * 0.5f, m_Pos.y + m_SrcRect.GetHeight() * 0.5f);
			m_pEndEffect = m_pEffectManager->Start(startPos, EFC_EXPLOSION02);
		}
		else
		{
			//ダメージエフェクトを発生させる
			Vector2 startPos = Vector2(m_Pos.x + m_SrcRect.GetWidth() * 0.5f, m_Pos.y + m_SrcRect.GetHeight() * 0.5f);
			m_pEffectManager->Start(startPos, EFC_DAMAGE);
		}
		return TRUE;
	}

	return FALSE;
}

/// <summary>
/// アイテムとの当たり判定
/// </summary>
/// <param name="itm">判定を行うアイテム</param>
/// <returns>当たっていればtrue, 当たっていなければfalse</returns>
bool CPlayer::CollisionItem(CItem& itm) {
	if (!itm.GetShow())
	{
		return FALSE;
	}
	CRectangle prec = GetRect();
	CRectangle irec = itm.GetRect();
	//アイテムの矩形と自分の矩形で当たり判定
	if (prec.CollisionRect(irec))
	{
		itm.SetShow(false);
		switch (itm.GetType())
		{
		case ITEMTYPE_CHARM:
			m_HP += PLAYER_DAMAGE_HP;
			if (m_HP >= PLAYER_MAX_HP)
			{
				m_HP = PLAYER_MAX_HP;
			}
			break;
		case ITEMTYPE_JEWEL:
			m_JewelCount++;
			if (m_JewelCount >= PLAYER_MAXJEWEL)
			{
				m_JewelCount = PLAYER_MAXJEWEL;
				CGameEndManager::Instance().SetGameEndCondition(GAMEENDNO_CLEAR);
			}
			break;
		default:
			break;
		}
		return TRUE;
	}
	return FALSE;
}