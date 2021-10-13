/*************************************************************************//*!

					@file	Effect.cpp
					@brief	�G�t�F�N�g�B

															@author	�r��@����
*//**************************************************************************/
#include "Effect.h"
#include "EffectManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
CEffect::CEffect() :
m_pTexture(NULL),
m_Motion(),
m_Pos(0.0f, 0.0f),
m_bShow(false),
m_SrcRect() {
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CEffect::~CEffect() {
}

/// <summary>
/// ������
/// </summary>
/// <param name="type">�^�C�v</param>
void CEffect::Initialize(int type) {
	m_Pos = Vector2(0, 0);
	m_bShow = false;

	switch (type)
	{
	case EFC_DAMAGE:
	{
		SpriteAnimationCreate anim[] = {
			{
				"�G�t�F�N�g",
				0, 0,
				128, 128,
				FALSE, { { 2, 0, 0 }, { 2, 1, 0 }, { 2, 2, 0 }, { 2, 3, 0 }, }
			}
		};
		m_Motion.Create(anim, 1);
		break;
	}
	case EFC_EXPLOSION01:
	{
		SpriteAnimationCreate anim[] = {
			{
				"�G�t�F�N�g",
				0, 0,
				120, 120,
				FALSE, {
					{ 3, 0, 0 }, { 3, 1, 0 }, { 3, 2, 0 }, { 3, 3, 0 }, { 3, 4, 0 },
					{ 3, 5, 0 }, { 3, 6, 0 }, { 3, 7, 0 }, { 3, 8, 0 }, { 3, 9, 0 },
					{ 3, 10, 0 }, { 3, 11, 0 }, { 3, 12, 0 }, { 3, 13, 0 }, { 3, 14, 0 }, { 3, 15, 0 }, }
			}
		};
		m_Motion.Create(anim, 1);
		break;
	}
	case EFC_EXPLOSION02:
	{
		SpriteAnimationCreate anim[] = {
			{
				"�G�t�F�N�g",
				0, 0,
				180, 180,
				FALSE, {
					{ 3, 0, 0 }, { 3, 1, 0 }, { 3, 2, 0 }, { 3, 3, 0 }, { 3, 4, 0 },
					{ 3, 5, 0 }, { 3, 6, 0 }, { 3, 7, 0 }, { 3, 8, 0 }, { 3, 9, 0 }, { 3, 10, 0 },
					{ 3, 0, 1 }, { 3, 1, 1 }, { 3, 2, 1 }, { 3, 3, 1 }, { 3, 4, 1 },
					{ 3, 5, 1 }, { 3, 6, 1 }, { 3, 7, 1 }, { 3, 8, 1 }, { 3, 9, 1 }, { 3, 10, 1 }, }
			}
		};
		m_Motion.Create(anim, 1);
		break;
	}
	}
}

/// <summary>
/// �J�n
/// ���W��ݒ肵�ă��[�V�������J�n����B
/// </summary>
/// <param name="pos">���W</param>
void CEffect::Start(Vector2 pos) {
	//�\����`���擾
	m_SrcRect = m_Motion.GetSrcRect();

	//���W��ݒ�B�w�肳�ꂽ���W���㉺���E�����ɂȂ�悤��
	m_Pos.x = pos.x - m_SrcRect.GetWidth() * 0.5f;
	m_Pos.y = pos.y - m_SrcRect.GetHeight() * 0.5f;

	//�\����Ԃ�
	m_bShow = true;

	//�ݒ肵���A�j���[�V�������Đ��J�n
	m_Motion.ChangeMotion(0);
}

/// <summary>
/// �X�V
/// </summary>
void CEffect::Update() {
	//��\��
	if (!m_bShow)
	{
		return;
	}
	//�A�j���[�V�����̍X�V
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
	//�A�j���[�V�����̏I���Ŕ�\���ɂ���
	if (m_Motion.IsEndMotion())
	{
		m_bShow = false;
	}
}

/// <summary>
/// �`��
/// </summary>
/// <param name="world">���[���h�̕ω�</param>
void CEffect::Render(Vector2 world) {
	//��\��
	if (!m_bShow)
	{
		return;
	}
	m_pTexture->Render(m_Pos.x - world.x, m_Pos.y - world.y, m_SrcRect);
}

/// <summary>
/// �f�o�b�O�`��
/// </summary>
/// <param name="world">���[���h�̕ω�</param>
void CEffect::RenderDebug(Vector2 world) {
	if (!m_bShow)
	{
		return;
	}
}

/// <summary>
/// ���
/// </summary>
void CEffect::Release() {
	m_Motion.Release();
}