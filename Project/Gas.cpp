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
m_Pos(0.0f, 0.0f),
m_Move(0.0f, 0.0f) {
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
	CUtilities::SetCurrentDirectory("Resource\Texture\Game");
	return TRUE;
}

/// <summary>
/// ������
/// </summary>
void CGas::Initialize() {
}

/// <summary>
/// �X�V
/// </summary>
void CGas::Update() {
}

/// <summary>
/// �`��
/// </summary>
void CGas::Render() {

}

/// <summary>
/// �f�o�b�O�`��
/// </summary>
void CGas::RenderDebug() {
}

/// <summary>
/// ���
/// </summary>
void CGas::Release() {
}