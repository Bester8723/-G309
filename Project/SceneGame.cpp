/*************************************************************************//*!

					@file	SceneGame.cpp
					@brief	�Q�[����ʁB

															@author	�r��@����
*//**************************************************************************/
#include "SceneGame.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
CSceneGame::CSceneGame() {
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CSceneGame::~CSceneGame() {
}

/// <summary>
/// �ǂݍ���
/// </summary>
/// <returns>�����Ftrue, ���s�Ffalse</returns>
bool CSceneGame::Load() {
	return false;
}

/// <summary>
/// ������
/// </summary>
void CSceneGame::Initialize() {
}

/// <summary>
/// �X�V
/// </summary>
void CSceneGame::Update() {
}

/// <summary>
/// �`��
/// </summary>
void CSceneGame::Render(void) {
}

/// <summary>
/// �f�o�b�O�`��
/// </summary>
void CSceneGame::RenderDebug(void) {
	CGraphicsUtilities::RenderString(10, 10, "�Q�[�����");
}

/// <summary>
/// ���
/// </summary>
void CSceneGame::Release(void) {
}