/*************************************************************************//*!

					@file	SceneBase.h
					@brief	�V�[����b�B

															@author	�r��@����
*//**************************************************************************/
#pragma once
#include	"Mof.h"
class CSceneBase {
protected:
	bool				m_bEnd;						//�V�[���I���t���O
	bool				m_bChange;					//�V�[���J�ڃt���O
	int					m_NextScene;				//���̃V�[��
	float				m_BlackAlpha;				//������ʂ̃A���t�@�l
	CRectangle			m_WindowRect;				//������ʂ̋�`
	float				m_BlackFadeTime;			//������ʂ̃t�F�[�h����

public:
	CSceneBase();
	virtual ~CSceneBase();
	virtual bool Load() = 0;
	virtual void Initialize() = 0;
	void InitializeBase();
	virtual void Update() = 0;
	void UpdateBase();
	virtual void Render(void) = 0;
	void RenderBase();
	virtual void RenderDebug(void) = 0;
	virtual void Release(void) = 0;
	//������ʂ̋�`���擾
	CRectangle GetWindowRect(void) {
		return CRectangle(0, 0, g_pGraphics->GetTargetWidth(), g_pGraphics->GetTargetHeight());
	}
	//���̃V�[�����擾
	int GetNextScene(void) { return m_NextScene; }
	//�V�[���͏I��������
	bool IsEnd(void) { return m_bEnd; }
	//�V�[���͑J�ڂ��邩
	bool IsChange(void) { return m_bChange; }
	//���̃V�[���ɑJ�ڂ���
	void SetNextScene(int sceneNo) {
		m_bChange = true;
		m_NextScene = sceneNo;
	}
};