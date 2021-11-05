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
CSceneBase(),
m_GameEndNo(0),
m_BackTex(),
m_BoardTex(),
m_ResultTex() {
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
	if (!m_BackTex.Load("Texture/Result/result_BackGround.png"))	{ return FALSE; }
	if (!m_BoardTex.Load("Texture/Result/ResultPaper.png"))			{ return FALSE; }
	char* str;
	switch (m_GameEndNo)
	{
	case GAMEENDNO_CONTINUE: break;
	case GAMEENDNO_CLEAR:	str = "Texture/Result/GameClearStr.png";		break;
	case GAMEENDNO_HP:		str = "Texture/Result/GameOverStr_HP.png";		break;
	case GAMEENDNO_JEWEL:	str = "Texture/Result/GameOverStr_Jewel.png";	break;
	case GAMEENDNO_GAS:		str = "Texture/Result/GameOverStr_Gas.png";		break;
	default: break;
	}
	if (!m_ResultTex.Load(str)) { return FALSE; }

	return TRUE;
}

/// <summary>
/// ������
/// </summary>
void CSceneResult::Initialize() {
	//�Q�[���I���ԍ����擾
	m_GameEndNo = CGameEndManager::Instance().GetGameEndCondition();
	InitializeBase();
}

/// <summary>
/// �X�V
/// </summary>
void CSceneResult::Update() {
	UpdateBase();

	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		CGameEndManager::Instance().SetGameEndCondition(GAMEENDNO_CONTINUE);
		SetNextScene(SCENENO_MODESELECT);
	}
}

/// <summary>
/// �`��
/// </summary>
void CSceneResult::Render(void) {
	m_BackTex.Render(0, 0);
	m_BoardTex.Render(200, 100);
	m_ResultTex.Render(300, 150);
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
	m_BackTex.Release();
	m_BoardTex.Release();
	m_ResultTex.Release();
}