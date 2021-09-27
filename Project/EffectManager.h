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
	//エフェクト
	CEffect		m_Effect[EFFECTCOUNT][EFC_TYPECOUNT];
	//エフェクト画像
	CTexture	m_Texture[EFC_TYPECOUNT];
public:
	CEffectManager();
	~CEffectManager();
	bool Load(void);
	void Initialize(void);
	CEffect* Start(Vector2 pos, int type);
	void Update(void);
	void Render(Vector2 world);
	void RenderDebug(Vector2 world);
	void Release(void);
};