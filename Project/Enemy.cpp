/*************************************************************************//*!

					@file	Enemy.cpp
					@brief	�G�B

															@author	�r��@����
*//**************************************************************************/
#include "Enemy.h"

/// <summary>
/// �R���X�g���N�^
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
/// �f�X�g���N�^
/// </summary>
CEnemy::~CEnemy() {
	Release();
}

/// <summary>
/// ������
/// </summary>
/// <param name="pos">�ʒu���W</param>
/// <param name="type">�G�̃^�C�v</param>
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
			"�ړ�",
			0,0,
			60,64,
			TRUE,{ { 5,0,0 },{ 5,1,0 },{ 5,2,0 },{ 5,3,0 }, }
		},
		{
			"�_���[�W",
			0,210,
			60,64,
			FALSE,{{ 10,0,0 }}
		},
	};
	m_Motion.Create(anim, MOTION_COUNT);
}

/// <summary>
/// �X�V
/// </summary>
void CEnemy::Update() {
	if (!m_bShow)
	{
		return;
	}
	//�_���[�W���̓���
	if (m_Motion.GetMotionNo() == MOTION_DAMAGE)
	{
		if (m_Motion.IsEndMotion())
		{
			m_bShow = false;
			//�����G�t�F�N�g�𔭐�������
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
/// �X�e�[�W�Ƃ̓����蔻��
/// </summary>
/// <param name="buried">���܂��</param>
void CEnemy::CollisionStage(Vector2 buried) {
	if (m_bDead)
	{
		return;
	}
	m_Pos += buried;
}

/// <summary>
/// �`��
/// </summary>
/// <param name="world">���[���h�̕ω�</param>
void CEnemy::Render(Vector2 world) {
	if (!m_bShow)
	{
		return;
	}
	//�`���`
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
/// �f�o�b�O�`��
/// </summary>
/// <param name="world"></param>
void CEnemy::RenderDebug(Vector2 world) {
	if (!m_bShow)
	{
		return;
	}
	//�����蔻��̕\��
	CRectangle hr = GetRect();
	CGraphicsUtilities::RenderRect(
		hr.Left - world.x, hr.Top - world.y, 
		hr.Right - world.x, hr.Bottom - world.y, MOF_XRGB(255, 0, 0));
}

/// <summary>
/// ���
/// </summary>
void CEnemy::Release() {
	m_Motion.Release();
}

/// <summary>
/// �_���[�W����
/// </summary>
void CEnemy::Damage() {
	if (m_bDead)
	{
		return;
	}
	m_Motion.ChangeMotion(MOTION_DAMAGE);
	m_bDead = true;
	m_MoveSpeed = ENEMY_FALLSPEED;
	//�_���[�W�G�t�F�N�g�𔭐�������
	Vector2 startPos = Vector2(m_Pos.x + m_SrcRect.GetWidth() * 0.5f, m_Pos.y + m_SrcRect.GetHeight() * 0.5f);
	m_pEffectManager->Start(startPos, EFC_DAMAGE);
}