/*************************************************************************//*!

					@file	Item.cpp
					@brief	�A�C�e���B

															@author	�r��@����
*//**************************************************************************/
#include "Item.h"
#include	"Item.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
CItem::CItem() :
m_pTexture(NULL),
m_Motion(),
m_Type(),
m_Pos(0.0f, 0.0f),
m_Move(0.0f, 0.0f),
m_bShow(false),
m_SrcRect() {
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CItem::~CItem() {
	Release();
}

/// <summary>
/// ������
/// </summary>
/// <param name="pos">�ʒu���W</param>
/// <param name="type">�A�C�e���̃^�C�v</param>
void CItem::Initialize(Vector2 pos, int type) {
	m_Type = type;
	m_Pos = pos;
	m_Move = Vector2(0.0f, 0.0f);
	m_bShow = true;

	//�A�j���[�V�������쐬
	SpriteAnimationCreate anim = {
		"�A�C�e��",
		0,0,
		32,32,
		TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0}}
	};
	m_Motion.Create(anim);
}

/// <summary>
/// �X�V
/// </summary>
void CItem::Update() {
	//��\��
	if (!m_bShow)
	{
		return;
	}
	//���ۂɍ��W���ړ�������
	m_Pos += m_Move;
	//�A�j���[�V�����̍X�V
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
}

/// <summary>
/// �X�e�[�W�Ƃ̓����蔻��
/// </summary>
/// <param name="buried">���܂��</param>
void CItem::CollisionStage(Vector2 buried) {
	m_Pos += buried;
}

/// <summary>
/// �`��
/// </summary>
/// <param name="world">���[���h�̕ω�</param>
void CItem::Render(Vector2 world) {
	//��\��
	if (!m_bShow)
	{
		return;
	}
	//�e�N�X�`���̕`��
	m_pTexture->Render(m_Pos.x - world.x, m_Pos.y - world.y, m_SrcRect);
}

/// <summary>
/// �f�o�b�O�`��
/// </summary>
/// <param name="world">���[���h�̕ω�</param>
void CItem::RenderDebug(Vector2 world) {
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
void CItem::Release() {
	m_Motion.Release();
}