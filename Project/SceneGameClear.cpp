/*************************************************************************//*!

					@file	SceneGameClear.cpp
					@brief	�Q�[���N���A��ʁB

															@author	�r��@����
*//**************************************************************************/
#include "SceneGameClear.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
CSceneGameClear::CSceneGameClear() {
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CSceneGameClear::~CSceneGameClear() {
}

/// <summary>
/// �ǂݍ���
/// </summary>
/// <returns>�����Ftrue, ���s�Ffalse</returns>
bool CSceneGameClear::Load() {
	return false;
}

/// <summary>
/// ������
/// </summary>
void CSceneGameClear::Initialize() {
}

/// <summary>
/// �X�V
/// </summary>
void CSceneGameClear::Update() {
}

/// <summary>
/// �`��
/// </summary>
void CSceneGameClear::Render(void) {
}

/// <summary>
/// �f�o�b�O�`��
/// </summary>
void CSceneGameClear::RenderDebug(void) {
	CGraphicsUtilities::RenderString(10, 10, "�Q�[�����");
}

/// <summary>
/// ���
/// </summary>
void CSceneGameClear::Release(void) {
}