/*************************************************************************//*!

					@file	Player.h
					@brief	プレイヤー。

															@author	池上　綾香
*//**************************************************************************/
#pragma once
#include	"Mof.h"
#include	"DebugManager.h"
#include	"GameEndManager.h"
#include	"GameDefine.h"
#include	"Enemy.h"
#include	"Item.h"
#include	"EffectManager.h"

#define		PLAYER_SPEED			0.3f			//移動速度
#define		PLAYER_MAXSPEED			10.0f			//移動最大速度
#define		PLAYER_JUMP				-10.0f			//ジャンプ初速
#define		PLAYER_STEPONENEMY		-3.0f			//敵踏み初速
#define		PLAYER_STEPJUMPSPEED	1.3f			//ジャンプ初速に乗算
#define		PLAYER_MAXJUMPCOUNT		2				//最大ジャンプ回数
#define		PLAYER_RECTDECREASE		12				//当たり判定減衰幅
#define		PLAYER_INI_HP			100				//初期HP
#define		PLAYER_MAX_HP			160				//最大HP
#define		PLAYER_DAMAGE_HP		20				//ダメージ受HP量
#define		PLAYER_DAMAGEWAIT		30				//ダメージ待機時間
#define		PLAYER_DAMAGESPEED		5.0f			//ダメージ受時バック速度
#define		PLAYER_MAXJEWEL			1				//最大宝玉数

class CPlayer {
private:
	const float					SCREEN_WIDTH = g_pGraphics->GetTargetWidth();

	CTexture					m_Tex;
	CRectangle					m_SrcRect;
	bool						m_bReverse;
	CSpriteMotionController		m_Motion;
	CVector2					m_Pos;
	CVector2					m_Move;
	bool						m_bMove;
	int							m_JumpCount;
	bool						m_bJumping;
	bool						m_bDead;
	int							m_HP;
	int							m_JewelCount;
	int							m_DamageWait;
	CEffectManager*				m_pEffectManager;
	CEffect*					m_pEndEffect;

	//モーション種類定義
	enum tag_MOTION {
		MOTION_WAIT,
		MOTION_MOVE,
		MOTION_JUMPSTART,
		MOTION_JUMPEND,
		MOTION_DAMAGE,

		MOTION_COUNT,
	};
public:
	CPlayer();
	~CPlayer();
	bool Load();
	void Initialize(Vector2 world);
	void Update(Vector2 gas);
	void UpdateKey();
	void Jump();
	void UpdateMove();
	void UpdateDebug();
	void Render(Vector2 world);
	void RenderDebug(Vector2 world);
	void Release();
	void CollisionStage(Vector2 buried);
	bool CollisionEnemy(CEnemy& ene);
	bool CollisionItem(CItem& itm);
	CRectangle GetRect() {
		return CRectangle(
			m_Pos.x + PLAYER_RECTDECREASE, m_Pos.y + PLAYER_RECTDECREASE, 
			m_Pos.x + m_SrcRect.GetWidth() - PLAYER_RECTDECREASE, m_Pos.y + m_SrcRect.GetHeight());
	}
	CRectangle GetAttackRect() {
		return CRectangle(
			m_Pos.x + PLAYER_RECTDECREASE, m_Pos.y + m_SrcRect.GetHeight() - PLAYER_RECTDECREASE * 0.5f,
			m_Pos.x + m_SrcRect.GetWidth() - PLAYER_RECTDECREASE, m_Pos.y + m_SrcRect.GetHeight());
	}
	void SetEffectManager(CEffectManager* pmng) { m_pEffectManager = pmng; }
	bool IsDead() { return m_bDead; }
};