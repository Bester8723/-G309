/*************************************************************************//*!

					@file	Player.h
					@brief	�v���C���[�B

															@author	�r��@����
*//**************************************************************************/
#pragma once
#include	"Mof.h"
#include	"GameDefine.h"
#include	"Enemy.h"
#include	"Item.h"
#include	"EffectManager.h"

#define		PLAYER_SPEED			0.3f			//�ړ����x
#define		PLAYER_MAXSPEED			10.0f			//�ړ��ő呬�x
#define		PLAYER_JUMP				-10.0f			//�W�����v����
#define		PLAYER_MAXJUMPCOUNT		2				//�ő�W�����v��
#define		PLAYER_RECTDECREASE		12				//�����蔻�茸����
#define		PLAYER_INI_HP			5				//����HP
#define		PLAYER_DAMAGEWAIT		60				//�_���[�W�ҋ@����

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
	int							m_DamageWait;
	CEffectManager*				m_pEffectManager;
	CEffect*					m_pEndEffect;

	//���[�V������ޒ�`
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
	void Update();
	void UpdateKey();
	void UpdateMove();
	void Render(Vector2 world);
	void RenderDebug(Vector2 world);
	void Release();
	CRectangle GetRect() {
		return CRectangle(
			m_Pos.x + PLAYER_RECTDECREASE, m_Pos.y + PLAYER_RECTDECREASE, 
			m_Pos.x + m_SrcRect.GetWidth() - PLAYER_RECTDECREASE, m_Pos.y + m_SrcRect.GetHeight());
	}
	void SetEffectManager(CEffectManager* pmng) { m_pEffectManager = pmng; }
	void CollisionStage(Vector2 buried);
	bool CollisionEnemy(CEnemy& ene);
	bool CollisionItem(CItem& itm);
};