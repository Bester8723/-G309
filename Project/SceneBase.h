/*************************************************************************//*!

					@file	SceneBase.h
					@brief	シーン基礎。

															@author	池上　綾香
*//**************************************************************************/
#pragma once
class CSceneBase {
protected:
	bool				m_bEnd;						//シーン終了フラグ
	bool				m_bChange;					//シーン遷移フラグ
	int					m_NextScene;				//次のシーン

public:
	CSceneBase();
	virtual ~CSceneBase();
	virtual bool Load() = 0;
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Render(void) = 0;
	virtual void RenderDebug(void) = 0;
	virtual void Release(void) = 0;
	//次のシーンを取得
	int GetNextScene(void) { return m_NextScene; }
	//シーンは終了したか
	bool IsEnd(void) { return m_bEnd; }
	//シーンは遷移するか
	bool IsChange(void) { return m_bChange; }
};