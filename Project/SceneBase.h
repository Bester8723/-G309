/*************************************************************************//*!

					@file	SceneBase.h
					@brief	�V�[����b�B

															@author	�r��@����
*//**************************************************************************/
#pragma once
class CSceneBase {
protected:
	bool				m_bEnd;						//�V�[���I���t���O
	bool				m_bChange;					//�V�[���J�ڃt���O
	int					m_NextScene;				//���̃V�[��

public:
	CSceneBase();
	virtual ~CSceneBase();
	virtual bool Load() = 0;
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Render(void) = 0;
	virtual void RenderDebug(void) = 0;
	virtual void Release(void) = 0;
	//���̃V�[�����擾
	int GetNextScene(void) { return m_NextScene; }
	//�V�[���͏I��������
	bool IsEnd(void) { return m_bEnd; }
	//�V�[���͑J�ڂ��邩
	bool IsChange(void) { return m_bChange; }
};