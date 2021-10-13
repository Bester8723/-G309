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
m_bDead(false),
m_HP(PLAYER_INI_HP),
m_JewelCount(0),
m_DamageWait(0),
m_pEffectManager(NULL),
m_pEndEffect(NULL) {
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
	if (!m_Tex.Load("Texture/Game/Player.png")) { return FALSE; }
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
	m_SrcRect = m_Motion.GetSrcRect();

	return TRUE;
}

/// <summary>
/// ������
/// </summary>
/// <param name="world">���[���h�̏����ω��l</param>
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
/// �X�V
/// </summary>
void CPlayer::Update(Vector2 gas) {
	//ᏋC�ɖ��܂�ƏI��
	if (m_Pos.y + m_SrcRect.GetHeight() * 0.5f > gas.y)
	{
		m_bDead = true;
		CGameEndManager::Instance().SetGameEndCondition(GAMEENDNO_GAS);
	}
	//HP���Ȃ��Ȃ�Ɣ����̏I����ҋ@���ďI��
	if (m_HP <= 0)
	{
		if (!m_pEndEffect || !m_pEndEffect->GetShow())
		{
			m_bDead = true;
			CGameEndManager::Instance().SetGameEndCondition(GAMEENDNO_HP);
		}
		return;
	}
	//�ړ��t���O
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
	//����ȊO�A�L�[���͍X�V
	else
	{
		UpdateKey();
	}
	//�ړ��X�V
	UpdateMove();
	m_Pos += m_Move;
	m_Pos.x = MOF_CLIPING(m_Pos.x, 0, SCREEN_WIDTH - m_SrcRect.GetWidth());
	//�A�j���[�V�����̍X�V
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
	//�_���[�W�ҋ@���Ԃ�i�߂�
	if (m_DamageWait > 0)
	{
		m_DamageWait--;
	}

	//�f�o�b�O�X�V
	if (CDebugManager::Instance().GetDebugFlg())
	{
		UpdateDebug();
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
	//�W�����v
	if (g_pInput->IsKeyPush(MOFKEY_W) && m_JumpCount < PLAYER_MAXJUMPCOUNT)
	{
		Jump();
	}
}

/// <summary>
/// �W�����v
/// </summary>
void CPlayer::Jump() {
	m_bJumping = true;
	m_JumpCount++;
	m_Move.y = PLAYER_JUMP;
	m_Motion.ChangeMotion(MOTION_JUMPSTART);
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
/// �f�o�b�O�X�V
/// </summary>
void CPlayer::UpdateDebug() {
	//�P�L�[��HP��MAX�ɂ���
	if (g_pInput->IsKeyPush(MOFKEY_1))
	{
		m_HP = PLAYER_MAX_HP;
	}
}

/// <summary>
/// �`��
/// </summary>
void CPlayer::Render(Vector2 world) {
	//�C���^�[�o���Q
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
	//�e�N�X�`���̕`��
	m_Tex.Render(m_Pos.x - world.x, m_Pos.y - world.y, dr);
}

/// <summary>
/// �f�o�b�O�`��
/// </summary>
void CPlayer::RenderDebug(Vector2 world) {
	//�����蔻��̕\��
	CRectangle hr = GetRect();
	CGraphicsUtilities::RenderRect(
		hr.Left - world.x, hr.Top - world.y,
		hr.Right - world.x, hr.Bottom - world.y, MOF_COLOR_BLUE);
	//�U���͈͂̕\��
	hr = GetAttackRect();
	CGraphicsUtilities::RenderRect(
		hr.Left - world.x, hr.Top - world.y,
		hr.Right - world.x, hr.Bottom - world.y, MOF_COLOR_GREEN);
	//HP�\��
	CGraphicsUtilities::RenderString(10, 35, "HP : %d", m_HP);
	CGraphicsUtilities::RenderString(10, 60, "Jewel : %d", m_JewelCount);
}

/// <summary>
/// ���
/// </summary>
void CPlayer::Release(void) {
	m_Tex.Release();
	m_Motion.Release();
}

/// <summary>
/// �X�e�[�W�Ƃ̓����蔻��
/// </summary>
/// <param name="buried">���܂��</param>
void CPlayer::CollisionStage(Vector2 buried) {
	m_Pos += buried;
	//�������̉����܂�A�W�����v���̏㖄�܂�̏ꍇ�͈ړ�������������B
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
	//���ړ����̍����܂�A�E�ړ����̉E���܂�̏ꍇ�͈ړ�������������B
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
/// �G�Ƃ̓����蔻��
/// </summary>
/// <param name="ene">������s���G</param>
/// <returns>�������Ă����true, �������Ă��Ȃ����false</returns>
bool CPlayer::CollisionEnemy(CEnemy& ene) {
	if (ene.IsDead() || m_HP <= 0 || m_DamageWait > 0)
	{
		return FALSE;
	}

	CRectangle prec;
	CRectangle erec = ene.GetRect();

	//�G�̋�`�Ǝ����̍U����`�œG���_���[�W
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
	//�������_���[�W
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
			//�����G�t�F�N�g�𔭐�������
			Vector2 startPos = Vector2(m_Pos.x + m_SrcRect.GetWidth() * 0.5f, m_Pos.y + m_SrcRect.GetHeight() * 0.5f);
			m_pEndEffect = m_pEffectManager->Start(startPos, EFC_EXPLOSION02);
		}
		else
		{
			//�_���[�W�G�t�F�N�g�𔭐�������
			Vector2 startPos = Vector2(m_Pos.x + m_SrcRect.GetWidth() * 0.5f, m_Pos.y + m_SrcRect.GetHeight() * 0.5f);
			m_pEffectManager->Start(startPos, EFC_DAMAGE);
		}
		return TRUE;
	}

	return FALSE;
}

/// <summary>
/// �A�C�e���Ƃ̓����蔻��
/// </summary>
/// <param name="itm">������s���A�C�e��</param>
/// <returns>�������Ă����true, �������Ă��Ȃ����false</returns>
bool CPlayer::CollisionItem(CItem& itm) {
	if (!itm.GetShow())
	{
		return FALSE;
	}
	CRectangle prec = GetRect();
	CRectangle irec = itm.GetRect();
	//�A�C�e���̋�`�Ǝ����̋�`�œ����蔻��
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