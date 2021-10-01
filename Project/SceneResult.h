/*************************************************************************//*!

					@file	SceneReselt.h
					@brief	���U���g��ʁB

															@author	�r��@����
*//**************************************************************************/
#pragma once
#include	"SceneBase.h"
#include	"GameEndManager.h"

class CSceneResult : public CSceneBase {
private:
	int				m_GameEndNo;			//�Q�[���I���ԍ�
	CTexture		m_BackTex;				//�w�i�e�N�X�`��
	CTexture		m_BoardTex;				//�X�R�A�e�N�X�`��
public:
	CSceneResult();
	~CSceneResult();
	bool Load()override;
	void Initialize()override;
	void Update()override;
	void Render()override;
	void RenderDebug()override;
	void Release()override;
};