/*************************************************************************//*!

					@file	SceneTitle.cpp
					@brief	�^�C�g����ʁB

															@author	�r��@����
*//**************************************************************************/
#include "SceneTitle.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
CSceneTitle::CSceneTitle() : 
CSceneBase(),
m_BackTex(),
m_TitleLogo(),
m_StartButton() {
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CSceneTitle::~CSceneTitle() {
}

/// <summary>
/// �ǂݍ���
/// </summary>
/// <returns>�����Ftrue, ���s�Ffalse</returns>
bool CSceneTitle::Load() {
	if (!m_BackTex.Load("Texture/Title/title_BackGround.png"))	{ return FALSE; }
	if (!m_TitleLogo.Load("Texture/Title/Logo_Title.png"))		{ return FALSE; }
	if (!m_StartButton.Load("Texture/Title/Btn_GameStart.png")) { return FALSE; }
	return TRUE;
}

/// <summary>
/// ������
/// </summary>
void CSceneTitle::Initialize() {
	InitializeBase();
}

/// <summary>
/// �X�V
/// </summary>
void CSceneTitle::Update() {
	UpdateBase();
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		SetNextScene(SCENENO_MODESELECT);
	}
}

/// <summary>
/// �`��
/// </summary>
void CSceneTitle::Render(void) {
	m_BackTex.Render(0, 0);
	Vector2 halfPos(g_pGraphics->GetTargetWidth() * 0.5f, g_pGraphics->GetTargetHeight() * 0.5f);
	m_TitleLogo.Render(halfPos.x, halfPos.y * 0.5f, TEXALIGN_CENTERCENTER);
	m_StartButton.Render(halfPos.x, halfPos.y * 1.5f, TEXALIGN_CENTERCENTER);
	RenderBase();
}

/// <summary>
/// �f�o�b�O�`��
/// </summary>
void CSceneTitle::RenderDebug(void) {
	CGraphicsUtilities::RenderString(10, 10, "�^�C�g�����");
}

/// <summary>
/// ���
/// </summary>
void CSceneTitle::Release(void) {
	m_BackTex.Release();
	m_TitleLogo.Release();
	m_StartButton.Release();
}