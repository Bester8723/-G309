/*************************************************************************//*!

					@file	SceneReselt.h
					@brief	リザルト画面。

															@author	池上　綾香
*//**************************************************************************/
#pragma once
#include	"SceneBase.h"
#include	"GameEndManager.h"

class CSceneResult : public CSceneBase {
private:
	int			m_GameEndNo;				//ゲーム終了番号
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