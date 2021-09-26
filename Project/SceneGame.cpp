/*************************************************************************//*!

					@file	SceneGame.cpp
					@brief	�Q�[����ʁB

															@author	�r��@����
*//**************************************************************************/
#include "SceneGame.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
CSceneGame::CSceneGame() : 
CSceneBase(),
m_Player() {
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
	m_Player.Initialize();
}

/// <summary>
/// �X�V
/// </summary>
void CSceneGame::Update() {
	m_Player.Update();
}

/// <summary>
/// �`��
/// </summary>
void CSceneGame::Render(void) {
	m_Player.Render(Vector2(0, 0));
}

/// <summary>
/// �f�o�b�O�`��
/// </summary>
void CSceneGame::RenderDebug(void) {
	CGraphicsUtilities::RenderString(10, 10, "�Q�[�����");
	m_Player.RenderDebug(Vector2(0, 0));
}

/// <summary>
/// ���
/// </summary>
void CSceneGame::Release(void) {
	m_Player.Release();
}