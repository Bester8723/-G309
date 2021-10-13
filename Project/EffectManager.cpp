/*************************************************************************//*!

					@file	EffectManager.cpp
					@brief	�G�t�F�N�g�Ǘ��B

															@author	�r��@����
*//**************************************************************************/
#include "EffectManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
CEffectManager::CEffectManager() {
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CEffectManager::~CEffectManager() {
}

/// <summary>
/// �ǂݍ���
/// </summary>
/// <returns>���������true, ���s�����false</returns>
bool CEffectManager::Load() {
	char* name[] = {
		"Texture/Effect/effect01.png",
		"Texture/Effect/effect02.png",
		"Texture/Effect/effect03.png",
	};
	for (int i = 0; i < EFC_TYPECOUNT; i++)
	{
		if (!m_Texture[i].Load(name[i]))
		{
			return FALSE;
		}
	}
	return TRUE;
}

/// <summary>
/// ������
/// </summary>
void CEffectManager::Initialize() {
	//�G�t�F�N�g�̊�b�ݒ�
	for (int j = 0; j < EFC_TYPECOUNT; j++)
	{
		for (int i = 0; i < EFFECTCOUNT; i++)
		{
			m_Effect[i][j].SetTexture(&m_Texture[j]);
			m_Effect[i][j].Initialize(j);
		}
	}
}

/// <summary>
/// �J�n
/// ���W��ݒ肵�ă��[�V�������J�n����B
/// </summary>
/// <param name="pos">���W</param>
/// <param name="type">�G�t�F�N�g�^�C�v</param>
/// <returns>�G�t�F�N�g�̃|�C���^</returns>
CEffect* CEffectManager::Start(Vector2 pos, int type) {
	for (int i = 0; i < EFFECTCOUNT; i++)
	{
		//���g�p�̃G�t�F�N�g���ǂ����m�F
		if (m_Effect[i][type].GetShow())
		{
			continue;
		}
		//�G�t�F�N�g��Start���Ăяo��
		m_Effect[i][type].Start(pos);
		//�J�n�����G�t�F�N�g�̃|�C���^��Ԃ�
		return &m_Effect[i][type];
	}
	return NULL;
}

/// <summary>
/// �X�V
/// </summary>
void CEffectManager::Update() {
	for (int j = 0; j < EFC_TYPECOUNT; j++)
	{
		for (int i = 0; i < EFFECTCOUNT; i++)
		{
			m_Effect[i][j].Update();
		}
	}
}

/// <summary>
/// �`��
/// </summary>
/// <param name="world">���[���h�̕ω�</param>
void CEffectManager::Render(Vector2 world) {
	for (int j = 0; j < EFC_TYPECOUNT; j++)
	{
		for (int i = 0; i < EFFECTCOUNT; i++)
		{
			m_Effect[i][j].Render(world);
		}
	}
}

/// <summary>
/// �f�o�b�O�`��
/// </summary>
/// <param name="world">���[���h�̕ω�</param>
void CEffectManager::RenderDebug(Vector2 world) {
	for (int j = 0; j < EFC_TYPECOUNT; j++)
	{
		for (int i = 0; i < EFFECTCOUNT; i++)
		{
			m_Effect[i][j].RenderDebug(world);
		}
	}
}

/// <summary>
/// ���
/// </summary>
void CEffectManager::Release() {
	for (int j = 0; j < EFC_TYPECOUNT; j++)
	{
		for (int i = 0; i < EFFECTCOUNT; i++)
		{
			m_Effect[i][j].Release();
		}
		m_Texture[j].Release();
	}
}