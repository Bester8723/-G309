/*************************************************************************//*!

					@file	SceneGameClear.h
					@brief	�Q�[���N���A��ʁB

															@author	�r��@����
*//**************************************************************************/
#pragma once
#include "SceneBase.h"

class CSceneGameClear : public CSceneBase {
public:
	CSceneGameClear();
	~CSceneGameClear();
	bool Load()override;
	void Initialize()override;
	void Update()override;
	void Render()override;
	void RenderDebug()override;
	void Release()override;
};