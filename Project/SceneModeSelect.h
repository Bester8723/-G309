/*************************************************************************//*!

					@file	SceneModeSelect.h
					@brief	�X�e�[�W�Z���N�g��ʁB

															@author	�r��@����
*//**************************************************************************/
#pragma once
#include "SceneBase.h"

class CSceneModeSelect : public CSceneBase {
public:
	CSceneModeSelect();
	~CSceneModeSelect();
	bool Load()override;
	void Initialize()override;
	void Update()override;
	void Render()override;
	void RenderDebug()override;
	void Release()override;
};