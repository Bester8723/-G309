/*************************************************************************//*!

					@file	SceneBase.cpp
					@brief	�V�[����b�B

															@author	�r��@����
*//**************************************************************************/
#include "SceneBase.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
CSceneBase::CSceneBase() :
m_bEnd(false),
m_bChange(false),
m_NextScene(0),
m_BlackAlpha(255.0f),
m_WindowRect(),
m_BlackFadeTime(0.0f) {
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CSceneBase::~CSceneBase() {
}

/// <summary>
/// ���������ʕ�
/// </summary>
void CSceneBase::InitializeBase() {
	//�ǂݍ���
	Load();
	//�t���O�ނ̏�����
	m_bEnd = false;
	m_bChange = false;
	//�l�̏�����
	m_BlackAlpha = 255.0f;
	m_BlackFadeTime = 30.0f;
}

/// <summary>
/// �X�V���ʕ�
/// </summary>
void CSceneBase::UpdateBase() {
	//�V�[���J�ڃt���O�������Ă���Ƃ��A������ʂ�`��
	if (IsChange() && !IsEnd())
	{
		m_BlackAlpha += 255 / m_BlackFadeTime;
		if (m_BlackAlpha > 255)
		{
			m_BlackAlpha = 255;
			m_bEnd = true;
		}
	}
	//�V�[���J�ڃt���O�������Ă��Ȃ��̂ɍ�����ʂ��`�悳��Ă���ꍇ�́A
	//���X�ɃA���t�@�l�����炷
	else if (m_BlackAlpha > 0 && !IsChange())
	{
		m_BlackAlpha -= 255 / m_BlackFadeTime;
		if (m_BlackAlpha < 0) { m_BlackAlpha = 0; }
	}
}

/// <summary>
/// �`�拤�ʕ�
/// </summary>
void CSceneBase::RenderBase() {
	//�������
	CGraphicsUtilities::RenderFillRect(GetWindowRect(), MOF_ALPHA_BLACK((int)m_BlackAlpha));
}