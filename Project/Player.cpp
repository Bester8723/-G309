/*************************************************************************//*!

					@file	Player.cpp
					@brief	�v���C���[�B

															@author	�r��@����
*//**************************************************************************/
#include "Player.h"

/// <summary>
/// �R���X�g���N�^
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
/// �f�X�g���N�^
/// </summary>
CPlayer::~CPlayer() {
}

/// <summary>
/// �ǂݍ���
/// </summary>
/// <returns>�����Ftrue, ���s�Ffalse</returns>
bool CPlayer::Load() {
	//�v���C���[�e�N�X�`���̓ǂݍ���
	if (!m_Tex.Load("player.png")) { return false; }
	//�A�j���[�V�������쐬
	SpriteAnimationCreate anim[] = {
		{
			"�ҋ@",
			0,0,
			60,64,
			TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0},{5,4,0},{5,5,0},{5,6,0},{5,7,0}}
		},
		{
			"�ړ�",
			0,70,
			60,64,
			TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0},{5,4,0},{5,5,0}}
		},
		{
			"�W�����v�J�n",
			0,140,
			60,64,
			FALSE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0}}
		},
		{
			"�W�����v�I��",
			240,140,
			60,64,
			FALSE,{{2,0,0},{2,1,0}}
		},
		{
			"�_���[�W",
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
/// ������
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
/// �X�V
/// </summary>
void CPlayer::Update() {
	m_bMove = false;
	//���n�A�_���[�W���̏ꍇ�̓���
	if (m_Motion.GetMotionNo() == MOTION_JUMPEND || m_Motion.GetMotionNo() == MOTION_DAMAGE)
	{
		//�I���őҋ@�ɖ߂�
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
	//�A�j���[�V�����̍X�V
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
	//�X�e�[�W���ł���܂ŏ����Œ�
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
/// �L�[���͂ɂ��X�V
/// </summary>
void CPlayer::UpdateKey(void) {
	//��
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
	//�E
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
	//Space�L�[�ŃW�����v
	if (g_pInput->IsKeyPush(MOFKEY_SPACE) && m_JumpCount < MAXJUMPCOUNT)
	{
		m_bJumping = true;
		m_JumpCount++;
		m_Move.y = PLAYER_JUMP;
		m_Motion.ChangeMotion(MOTION_JUMPSTART);
	}
}

/// <summary>
/// �ړ��X�V
/// </summary>
void CPlayer::UpdateMove(void) {
	//�ړ����Ȃ���Ό�������
	if (!m_bMove)
	{
		m_Move.x = MOF_LERP(m_Move.x, 0, PLAYER_SPEED);
		if (m_Move.x < abs(0.05f) && m_Motion.GetMotionNo() == MOTION_MOVE)
		{
			m_Motion.ChangeMotion(MOTION_WAIT);
		}
	}
	//�d�͂̉e��
	m_Move.y = MOF_CLIPING(m_Move.y + GRAVITY, PLAYER_JUMP, MAXGRAVITY);
}

/// <summary>
/// �`��
/// </summary>
void CPlayer::Render(Vector2 world) {
	CRectangle dr = m_SrcRect;
	if (m_bReverse)
	{
		float tmp = dr.Right;
		dr.Right = dr.Left;
		dr.Left = tmp;
	}
	//�e�N�X�`���̕`��
	m_Tex.Render(m_Pos.x - world.x, m_Pos.y - world.y, dr);
}

/// <summary>
/// �f�o�b�O�`��
/// </summary>
void CPlayer::RenderDebug(Vector2 world) {
}

/// <summary>
/// ���
/// </summary>
void CPlayer::Release(void) {
	m_Tex.Release();
	m_Motion.Release();
}