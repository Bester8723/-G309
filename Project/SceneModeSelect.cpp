/*************************************************************************//*!

					@file	SceneModeSelect.cpp
					@brief	�X�e�[�W�Z���N�g��ʁB

															@author	�r��@����
*//**************************************************************************/
#include "SceneModeSelect.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
CSceneModeSelect::CSceneModeSelect() : 
CSceneBase(),
m_StoryBgTex(),
m_EndlessBgTex(),
m_StoryOnButton(),
m_StoryOffButton(),
m_EndlessOnButton(),
m_EndlessOffButton(),
m_ModeNo(0) {
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CSceneModeSelect::~CSceneModeSelect() {
}

/// <summary>
/// �ǂݍ���
/// </summary>
/// <returns>�����Ftrue, ���s�Ffalse</returns>
bool CSceneModeSelect::Load() {
	if (!m_StoryBgTex.Load("Texture/Select/Bg_StoryMode.png"))			{ return FALSE; }
	if (!m_EndlessBgTex.Load("Texture/Select/Bg_EndlessMode.png"))		{ return FALSE; }
	if (!m_StoryOnButton.Load("Texture/Select/Btn_StoryOn.png"))		{ return FALSE; }
	if (!m_StoryOffButton.Load("Texture/Select/Btn_StoryOff.png"))		{ return FALSE; }
	if (!m_EndlessOnButton.Load("Texture/Select/Btn_EndlessOn.png"))	{ return FALSE; }
	if (!m_EndlessOffButton.Load("Texture/Select/Btn_EndlessOff.png"))	{ return FALSE; }
	return TRUE;
}

/// <summary>
/// ������
/// </summary>
void CSceneModeSelect::Initialize() {
	InitializeBase();
	m_ModeNo = MODENO_STORY;
}

/// <summary>
/// �X�V
/// </summary>
void CSceneModeSelect::Update() {
	UpdateBase();

	if (g_pInput->IsKeyPush(MOFKEY_UP))
	{
		m_ModeNo--;
		if (m_ModeNo < 0) { m_ModeNo = 0; }
	}
	else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
	{
		m_ModeNo++;
		if (m_ModeNo >= MODENO_COUNT) { m_ModeNo = MODENO_COUNT - 1; }
	}

	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		SetNextScene(SCENENO_GAME);
	}
}

/// <summary>
/// �`��
/// </summary>
void CSceneModeSelect::Render(void) {
	switch (m_ModeNo)
	{
	case MODENO_STORY:
		m_StoryBgTex.Render(0, 0);
		m_StoryOnButton.Render(100, 100);
		m_EndlessOffButton.Render(100, 200);
		break;
	case MODENO_ENDLESS:
		m_EndlessBgTex.Render(0, 0);
		m_StoryOffButton.Render(100, 100);
		m_EndlessOnButton.Render(100, 200);
		break;
	}

	RenderBase();
}

/// <summary>
/// �f�o�b�O�`��
/// </summary>
void CSceneModeSelect::RenderDebug(void) {
	CGraphicsUtilities::RenderString(10, 10, "���[�h�I�����");
}

/// <summary>
/// ���
/// </summary>
void CSceneModeSelect::Release(void) {
	m_StoryBgTex.Release();
	m_EndlessBgTex.Release();
	m_StoryOnButton.Release();
	m_StoryOffButton.Release();
	m_EndlessOnButton.Release();
	m_EndlessOffButton.Release();
}