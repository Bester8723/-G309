/*************************************************************************//*!

					@file	SceneReselt.cpp
					@brief	���U���g��ʁB

															@author	�r��@����
*//**************************************************************************/
#include "SceneResult.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
CSceneResult::CSceneResult() :
m_GameEndNo(0) {
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CSceneResult::~CSceneResult() {
}

/// <summary>
/// �ǂݍ���
/// </summary>
/// <returns>�����Ftrue, ���s�Ffalse</returns>
bool CSceneResult::Load() {
	return false;
}

/// <summary>
/// ������
/// </summary>
void CSceneResult::Initialize() {
	//���ʕ�
	InitializeBase();
	//�Q�[���I���ԍ����擾
	m_GameEndNo = CGameEndManager::Instance().GetGameEndCondition();
}

/// <summary>
/// �X�V
/// </summary>
void CSceneResult::Update() {
	//���ʕ�
	UpdateBase();
}

/// <summary>
/// �`��
/// </summary>
void CSceneResult::Render(void) {
	//���ʕ�
	RenderBase();
}

/// <summary>
/// �f�o�b�O�`��
/// </summary>
void CSceneResult::RenderDebug(void) {
	CGraphicsUtilities::RenderString(10, 10, "���U���g���");
}

/// <summary>
/// ���
/// </summary>
void CSceneResult::Release(void) {
}