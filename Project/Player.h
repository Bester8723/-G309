/*************************************************************************//*!

					@file	Player.h
					@brief	�v���C���[�B

															@author	�r��@����
*//**************************************************************************/
#pragma once
#include	"Mof.h"

#define		PLAYER_SPEED			0.3f			//�ړ����x
#define		PLAYER_MAXSPEED			10.0f			//�ړ��ő呬�x
#define		PLAYER_JUMP				-10.0f			//�W�����v����
#define		MAXJUMPCOUNT			2				//�ő�W�����v��
#define		GRAVITY					0.3f			//�d��
#define		MAXGRAVITY				20.0f			//�ő�d�͉���

class CPlayer {
private:
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
	void Initialize();
	void Update();
	void UpdateKey();
	void UpdateMove();
	void Render(Vector2 world);
	void RenderDebug(Vector2 world);
	void Release();
};