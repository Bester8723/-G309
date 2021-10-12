/*************************************************************************//*!

					@file	EffectManager.cpp
					@brief	�G�t�F�N�g�Ǘ��B

															@author	�r��@����
*//**************************************************************************/
#include "EffectManager.h"

/**
 * �R���X�g���N�^
 *
 */
CEffectManager::CEffectManager() {
}

/**
 * �f�X�g���N�^
 *
 */
CEffectManager::~CEffectManager() {
}

/**
 * �ǂݍ���
 * ���p����e�N�X�`����ǂݍ��ށB
 */
bool CEffectManager::Load(void) {
	char* name[] = {
		"Texture/Effect/effect01.png",
		"Texture/Effect/effect02.png",
		"Texture/Effect/effect03.png",
	};
	for (int i = 0; i < EFC_TYPECOUNT; i++)
	{
		if (!m_Texture[i].Load(name[i]))
		{
			return false;
		}
	}
	return true;
}

/**
 * ������
 * �p�����[�^�[����W������������B
 */
void CEffectManager::Initialize(void) {
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

/**
 * �J�n
 * ���W��ݒ肵�ă��[�V�������J�n����B
 *
 * ����
 * [in]			px					X���W
 * [in]			py					Y���W
 * [in]			type				�G�t�F�N�g�^�C�v
 */
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

/**
 * �X�V
 *
 */
void CEffectManager::Update(void) {
	for (int j = 0; j < EFC_TYPECOUNT; j++)
	{
		for (int i = 0; i < EFFECTCOUNT; i++)
		{
			m_Effect[i][j].Update();
		}
	}
}

/**
 * �`��
 *
 * ����
 * [in]			wx					���[���h�̕ω�
 * [in]			wy					���[���h�̕ω�
 */
void CEffectManager::Render(Vector2 world) {
	for (int j = 0; j < EFC_TYPECOUNT; j++)
	{
		for (int i = 0; i < EFFECTCOUNT; i++)
		{
			m_Effect[i][j].Render(world);
		}
	}
}


/**
 * �f�o�b�O�`��
 *
 * ����
 * [in]			wx					���[���h�̕ω�
 * [in]			wy					���[���h�̕ω�
 */
void CEffectManager::RenderDebug(Vector2 world) {
	for (int j = 0; j < EFC_TYPECOUNT; j++)
	{
		for (int i = 0; i < EFFECTCOUNT; i++)
		{
			m_Effect[i][j].RenderDebug(world);
		}
	}
}

/**
 * ���
 *
 */
void CEffectManager::Release(void) {
	for (int j = 0; j < EFC_TYPECOUNT; j++)
	{
		for (int i = 0; i < EFFECTCOUNT; i++)
		{
			m_Effect[i][j].Release();
		}
		m_Texture[j].Release();
	}
}