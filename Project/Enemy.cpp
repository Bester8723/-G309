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
m_Move(0.0f, 0.0f),
m_bShow(false),
m_bReverse(false),
m_SrcRect(),
m_HP(ENEMY_INI_HP),
m_DamageWait(0),
m_pEffectManager(NULL) {
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
	m_Move.x = -3.0f;
	m_Move.y = 0.0f;
	m_bReverse = true;
	m_bShow = true;
	m_HP = 10;
	m_DamageWait = 0;

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
			FALSE,{{ 20,0,0 }}
		},
	};
	m_Motion.Create(anim, MOTION_COUNT);
}

/// <summary>
/// �X�V
/// </summary>
void CEnemy::Update() {
	//��\��
	if (!m_bShow)
	{
		return;
	}
	//�_���[�W���̓���
	if (m_Motion.GetMotionNo() == MOTION_DAMAGE)
	{
		//�I���őҋ@�ɖ߂�
		if (m_Motion.IsEndMotion())
		{
			m_Motion.ChangeMotion(MOTION_MOVE);
			if (m_HP <= 0)
			{
				m_bShow = false;
				//�����G�t�F�N�g�𔭐�������
				Vector2 startPos = Vector2(m_Pos.x + m_SrcRect.GetWidth() * 0.5f, m_Pos.y + m_SrcRect.GetHeight() * 0.5f);
				m_pEffectManager->Start(startPos, EFC_EXPLOSION01);
			}
			m_Move.x = ((m_bReverse) ? -3.0f : 3.0f);
		}
		else
		{
			if (m_Move.x > 0)
			{
				m_Move.x -= 0.2f;
				if (m_Move.x <= 0)
				{
					m_Move.x = 0;
				}
			}
			else if (m_Move.x < 0)
			{
				m_Move.x += 0.2f;
				if (m_Move.x >= 0)
				{
					m_Move.x = 0;
				}
			}
		}
	}
	//�d�͂ɂ�菭����������
	m_Move.y += GRAVITY;
	if (m_Move.y >= 20.0f) { m_Move.y = 20.0f; }
	//���ۂɍ��W���ړ�������
	m_Pos.x += m_Move.x;
	m_Pos.y += m_Move.y;
	//�A�j���[�V�����̍X�V
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
	//�_���[�W�̃C���^�[�o�������炷
	if (m_DamageWait > 0)
	{
		m_DamageWait--;
	}
}

/// <summary>
/// �X�e�[�W�Ƃ̓����蔻��
/// </summary>
/// <param name="buried">���܂��</param>
void CEnemy::CollisionStage(Vector2 buried) {
	m_Pos += buried;
	//�������̉����܂�A�W�����v���̏㖄�܂�̏ꍇ�͈ړ�������������B
	if (buried.y < 0 && m_Move.y > 0)
	{
		m_Move.y = 0;
	}
	else if (buried.y > 0 && m_Move.y < 0)
	{
		m_Move.y = 0;
	}
	//���ړ����̍����܂�A�E�ړ����̉E���܂�̏ꍇ�͈ړ�������������B
	if (buried.x < 0 && m_Move.x > 0)
	{
		m_Move.x *= -1;
		m_bReverse = true;
	}
	else if (buried.x > 0 && m_Move.x < 0)
	{
		m_Move.x *= -1;
		m_bReverse = false;
	}
}

/// <summary>
/// �`��
/// </summary>
/// <param name="world">���[���h�̕ω�</param>
void CEnemy::Render(Vector2 world) {
	//��\��
	if (!m_bShow)
	{
		return;
	}
	//�C���^�[�o���Q�@�t���[�����Ƃɕ`������Ȃ�
	if (m_DamageWait % 4 >= 2)
	{
		return;
	}
	//�`���`
	CRectangle dr = m_SrcRect;
	//���]�t���O��ON�̏ꍇ�`���`�𔽓]������
	if (m_bReverse)
	{
		float tmp = dr.Right;
		dr.Right = dr.Left;
		dr.Left = tmp;
	}
	//�e�N�X�`���̕`��
	m_pTexture->Render(m_Pos.x - world.x, m_Pos.y - world.y, dr);
}

/// <summary>
/// �f�o�b�O�`��
/// </summary>
/// <param name="world"></param>
void CEnemy::RenderDebug(Vector2 world) {
	//��\��
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
/// <param name="dmg">�_���[�W��</param>
/// <param name="bRev">���]�t���O</param>
void CEnemy::Damage(int dmg, bool bRev) {
	m_HP -= dmg;
	m_DamageWait = ENEMY_DAMAGEWAIT;
	if (bRev)
	{
		m_Move.x -= 5.0f;
		m_bReverse = false;
	}
	else
	{
		m_Move.x = 5.0f;
		m_bReverse = true;
	}
	m_Motion.ChangeMotion(MOTION_DAMAGE);
	//�_���[�W�G�t�F�N�g�𔭐�������
	Vector2 startPos = Vector2(m_Pos.x + m_SrcRect.GetWidth() * 0.5f, m_Pos.y + m_SrcRect.GetHeight() * 0.5f);
	m_pEffectManager->Start(startPos, EFC_DAMAGE);
}