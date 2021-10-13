/*************************************************************************//*!

					@file	EffectManager.h
					@brief	エフェクト管理。

															@author	池上　綾香
*//**************************************************************************/
#pragma once
#include	"Mof.h"
#include	"Effect.h"

//管理エフェクトの数
#define				EFFECTCOUNT					5

class CEffectManager {
private:
	CEffect		m_Effect[EFFECTCOUNT][EFC_TYPECOUNT];			//エフェクト
	CTexture	m_Texture[EFC_TYPECOUNT];						//エフェクト画像
public:
	CEffectManager();
	~CEffectManager();
	bool Load();
	void Initialize();
	CEffect* Start(Vector2 pos, int type);
	void Update();
	void Render(Vector2 world);
	void RenderDebug(Vector2 world);
	void Release();
};