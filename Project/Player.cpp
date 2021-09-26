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
m_bDead(false) {
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
	//プレイヤーテクスチャの読み込み
	if (!m_Tex.Load("player.png")) { return false; }
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

	return FALSE;
}

/// <summary>
/// 初期化
/// </summary>
void CPlayer::Initialize() {
	Load();
	m_bReverse = false;
	m_Pos = Vector2(0.0f, 0.0f);
	m_Move = Vector2(0.0f, 0.0f);
	m_bMove = false;
	m_JumpCount = 0;
	m_bJumping = false;
	m_bDead = false;
}

/// <summary>
/// 更新
/// </summary>
void CPlayer::Update() {
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
	else
	{
		UpdateKey();
	}
	UpdateMove();
	m_Pos += m_Move;
	//アニメーションの更新
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
	//ステージができるまで床を固定
	if (m_Pos.y > g_pGraphics->GetTargetHeight() - 200)
	{
		m_Pos.y = g_pGraphics->GetTargetHeight() - 200;
		m_Move.y = 0;
		if (m_bJumping)
		{
			m_bJumping = false;
			m_Motion.ChangeMotion(MOTION_JUMPEND);
		}
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
	//Spaceキーでジャンプ
	if (g_pInput->IsKeyPush(MOFKEY_SPACE) && m_JumpCount < MAXJUMPCOUNT)
	{
		m_bJumping = true;
		m_JumpCount++;
		m_Move.y = PLAYER_JUMP;
		m_Motion.ChangeMotion(MOTION_JUMPSTART);
	}
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
/// 描画
/// </summary>
void CPlayer::Render(Vector2 world) {
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
}

/// <summary>
/// 解放
/// </summary>
void CPlayer::Release(void) {
	m_Tex.Release();
	m_Motion.Release();
}