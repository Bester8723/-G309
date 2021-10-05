/*************************************************************************//*!

					@file	SceneBase.h
					@brief	シーン基礎。

															@author	池上　綾香
*//**************************************************************************/
#pragma once
#include	"Mof.h"
class CSceneBase {
protected:
	bool				m_bEnd;						//シーン終了フラグ
	bool				m_bChange;					//シーン遷移フラグ
	int					m_NextScene;				//次のシーン
	float				m_BlackAlpha;				//黒い画面のアルファ値
	CRectangle			m_WindowRect;				//黒い画面の矩形
	float				m_BlackFadeTime;			//黒い画面のフェード時間

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
	//黒い画面の矩形を取得
	CRectangle GetWindowRect(void) {
		return CRectangle(0, 0, g_pGraphics->GetTargetWidth(), g_pGraphics->GetTargetHeight());
	}
	//次のシーンを取得
	int GetNextScene(void) { return m_NextScene; }
	//シーンは終了したか
	bool IsEnd(void) { return m_bEnd; }
	//シーンは遷移するか
	bool IsChange(void) { return m_bChange; }
	//次のシーンに遷移する
	void SetNextScene(int sceneNo) {
		m_bChange = true;
		m_NextScene = sceneNo;
	}
};