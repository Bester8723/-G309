/*************************************************************************//*!

					@file	SceneReselt.cpp
					@brief	���U���g��ʁB

															@author	�r��@����
*//**************************************************************************/
#include "SceneResult.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
CSceneResult::CSceneResult() {
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
}

/// <summary>
/// �X�V
/// </summary>
void CSceneResult::Update() {
}

/// <summary>
/// �`��
/// </summary>
void CSceneResult::Render(void) {
	CGraphicsUtilities::RenderFillRect(0, 0, 100, 100, MOF_COLOR_RED);
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