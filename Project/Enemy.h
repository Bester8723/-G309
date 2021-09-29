/*************************************************************************//*!

					@file	Enemy.h
					@brief	�G�B

															@author	�r��@����
*//**************************************************************************/
#pragma once
#include	"Mof.h"
#include	"GameDefine.h"
#include	"EffectManager.h"

#define		ENEMY_INI_HP			5				//����HP
#define		ENEMY_DAMAGEWAIT		60				//�_���[�W�ҋ@����
#define		ENEMY_RECTDECREASE		10				//�����蔻�茸����

class CEnemy {
private:
	CTexture*				m_pTexture;
	CSpriteMotionController	m_Motion;
	int						m_Type;
	CVector2				m_Pos;
	bool					m_bShow;
	bool					m_bReverse;
	CRectangle				m_SrcRect;
	int						m_HP;
	int						m_DamageWait;
	float					ENEMY_DAMAGESPEED;
	CEffectManager*			m_pEffectManager;

	CVector2				ENEMY_INI_POS;			//�����ʒu
	float					ENEMY_QUAKE;			//�ړ�����
	float					ENEMY_INI_SPEED;		//�����ړ����x
	float					m_MoveSpeed;			//�ړ����x
	float					m_MoveTime;				//���Z����

	//���[�V������ޒ�`
	enum tag_MOTION {
		MOTION_MOVE,
		MOTION_DAMAGE,

		MOTION_COUNT,
	};
	//�G�^�C�v
	enum tag_ENEMYTYPE {
		ENEMYTYPE_HORIZONTAL,
		ENEMYTYPE_VERTICAL,

		ENEMYTYPE_COUNT,
	};
public:
	CEnemy();
	~CEnemy();
	void Initialize(Vector2 pos, int type);
	void Update();
	void CollisionStage(Vector2 buried);
	void Render(Vector2 world);
	void RenderDebug(Vector2 world);
	void Release();
	void Damage(int dmg, bool bRev);
	CRectangle GetRect() {
		return CRectangle(
			m_Pos.x + ENEMY_RECTDECREASE, m_Pos.y + ENEMY_RECTDECREASE, 
			m_Pos.x + m_SrcRect.GetWidth() - ENEMY_RECTDECREASE, m_Pos.y + m_SrcRect.GetHeight());
	}
	void SetTexture(CTexture* pt) { m_pTexture = pt; }
	bool GetShow(void) { return m_bShow; }
	void SetEffectManager(CEffectManager* pmng) { m_pEffectManager = pmng; }
	int GetDamageWait(void) { return m_DamageWait; }
};