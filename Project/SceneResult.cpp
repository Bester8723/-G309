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
m_GameEndNo(0),
m_BackTex(),
m_BoardTex() {
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
	CUtilities::SetCurrentDirectory("Resource\Texture\Result");
	if (!m_BoardTex.Load("result_titleText.png")) { return FALSE; }

	return TRUE;
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

	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		CGameEndManager::Instance().SetGameEndCondition(GAMEENDNO_CONTINUE);
		SetNextScene(SCENENO_GAME);
	}
}

/// <summary>
/// �`��
/// </summary>
void CSceneResult::Render(void) {
	m_BoardTex.Render(0, 0);
	//���ʕ�
	RenderBase();
}

/// <summary>
/// �f�o�b�O�`��
/// </summary>
void CSceneResult::RenderDebug(void) {
}

/// <summary>
/// ���
/// </summary>
void CSceneResult::Release(void) {
	m_BoardTex.Release();
}