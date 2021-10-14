/*************************************************************************//*!

					@file	Gas.cpp
					@brief	ᏋC�B

															@author	�r��@����
*//**************************************************************************/
#include "Gas.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
CGas::CGas() : 
m_Tex(),
m_Move(0.0f, 0.0f),
m_Scroll(0.0f, 0.0f) {
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CGas::~CGas() {
}

/// <summary>
/// �ǂݍ���
/// </summary>
/// <returns>�����Ftrue, ���s�Ffalse</returns>
bool CGas::Load() {
	if (!m_Tex.Load("Texture/Game/Gas.png")) { return FALSE; }

	return TRUE;
}

/// <summary>
/// ������
/// </summary>
void CGas::Initialize(Vector2 world) {
	m_Move = Vector2(SPEEDX, -SPEEDY);
	m_Scroll = Vector2(world.x, world.y + g_pGraphics->GetTargetHeight() - STARTPOS);
}

/// <summary>
/// �X�V
/// </summary>
void CGas::Update() {
	m_Scroll += m_Move;
	if (m_Scroll.y <= 0)
	{
		m_Move.y = 0;
		m_Scroll.y = 0;
	}

	//�f�o�b�O�X�V
	if (CDebugManager::Instance().GetDebugFlg())
	{
		UpdateDebug();
	}
}

/// <summary>
/// �f�o�b�O�X�V
/// </summary>
void CGas::UpdateDebug() {
	//�Q�L�[�ŃK�X��Trigger
	if (g_pInput->IsKeyPush(MOFKEY_2))
	{
		m_Move.y = (m_Move.y == 0) ? m_Move.y = -SPEEDY : m_Move.y = 0;
	}
}

/// <summary>
/// �`��
/// </summary>
void CGas::Render(Vector2 world) {
	int scw = g_pGraphics->GetTargetWidth();
	int wn = m_Tex.GetWidth();
	for (float x = ((int)-m_Scroll.x % wn) - wn; x < scw; x += wn)
	{
		m_Tex.Render(x - world.x, m_Scroll.y - world.y);
	}
}

/// <summary>
/// �f�o�b�O�`��
/// </summary>
void CGas::RenderDebug(Vector2 world) {
}

/// <summary>
/// ���
/// </summary>
void CGas::Release() {
	m_Tex.Release();
}

/// <summary>
/// �A�C�e���Ƃ̓����蔻��
/// </summary>
/// <param name="itm">���肷��A�C�e��</param>
/// <returns>���܂��Ă����true, ���܂��Ă��Ȃ����false</returns>
bool CGas::CollisionItem(CItem& itm) {
	if (!itm.GetShow() || itm.GetType() != ITEMTYPE_JEWEL)
	{
		return FALSE;
	}
	if (itm.GetRect().Top > m_Scroll.y)
	{
		itm.SetShow(false);
		CGameEndManager::Instance().SetGameEndCondition(GAMEENDNO_JEWEL);
		return TRUE;
	}
	return FALSE;
}