/*************************************************************************//*!

					@file	SceneStageSelect.h
					@brief	�X�e�[�W�Z���N�g��ʁB

															@author	�r��@����
*//**************************************************************************/
#pragma once
#include "SceneBase.h"

class CSceneStageSelect : public CSceneBase {
public:
	CSceneStageSelect();
	~CSceneStageSelect();
	bool Load()override;
	void Initialize()override;
	void Update()override;
	void Render()override;
	void RenderDebug()override;
	void Release()override;
};